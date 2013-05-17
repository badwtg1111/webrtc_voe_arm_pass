/*
 * =====================================================================================
 *
 *       Filename:  phone_proxy.cc
 *
 *    Description:  phone proxy for PAD or Handset
 *
 *        Version:  1.0
 *        Created:  05/03/2013 04:07:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (chen.chunsheng badwtg1111@hotmail.com), 
 *   Organization:  handaer
 *
 * =====================================================================================
 */
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/epoll.h>
#include <assert.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>
#include "phone_thread_wrapper.h"

#include "phone_proxy.h"

using namespace webrtc;
using namespace std;
namespace handaer{

PhoneProxy::timer_info_t PhoneProxy::timer_info_g[PhoneProxy::CLIENT_NUM];


PhoneProxy::PhoneProxy()
	:	_ptrThreadPhoneProxy(NULL),
		_phoneProxyThreadId(0),	
		_phoneProxyRunning(false),	
		_ptrThreadHeartBeating(NULL),
		_heartBeatingThreadId(0),	
		_heartBeatingisRunning(false),
		pcs(NULL),
		timer(NULL),
		_ms_datas(NULL),
		server_port(-1),
		payload_type(-1),
		serv_listen_sockfd(-1),
		_phone_control_service_event(DEFAULT_INCOMING) {
	
	phone_proxy_fd[0] = -1;
	phone_proxy_fd[1] = -1;

	memset(ci, 0 ,sizeof(ci));
	for (int i=0; i<CLIENT_NUM ; i++) {
		ci[i].client_fd = -1;
		ci[i].id = -1;
		
	}
	
	memset(&_cli_req, 0, sizeof(cli_request_t));
	_cli_req.cmd = DEFAULT;

	

}

PhoneProxy::~PhoneProxy(){
	phoneProxyExit();

}


int PhoneProxy::listenOnServerSocket(int port){
	int listen_fd, on, ret;	
	struct sockaddr_in srv_addr;
	
	listen_fd = socket(PF_INET, SOCK_STREAM, 0);
	if(listen_fd < 0) {
		perror("cannot create listening socket: ");
		exit (-1);
	}
	cout << "socket success" << endl;
	
	/* Enable address reuse */
	on = 1;	
	ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	//fill server addr info
	memset(&srv_addr, 0, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	srv_addr.sin_port = htons(port);
	
	ret = bind(listen_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	if(ret == -1){
		perror("cannot bind server socket: ");
		close(listen_fd);
		exit (-1);
	}
	cout << "bind success" << endl;

	//listen
	ret = listen(listen_fd, BACK_LOG);	
	if(ret == -1) {
		perror("cannot listen the client connect request: ");
		close(listen_fd);
		exit (-1);
	}
	cout << "listen success" << endl;

	serv_listen_sockfd = listen_fd;
	cout << __FUNCTION__ << " : " << serv_listen_sockfd << endl;

	return listen_fd;
}

int PhoneProxy::my_accept(struct sockaddr *addr, socklen_t *addrlen){
	int com_fd;	
	com_fd = accept(serv_listen_sockfd, addr, addrlen);	
	if (com_fd < 0) {
		if (errno == EINTR) {
			cout << __FUNCTION__ << " : " << serv_listen_sockfd << endl;
			perror("EINTR Error: ");
			return (-EINTR);
		} else {
			perror("cannot accept client connect request: ");
			close(serv_listen_sockfd);
			exit (-1);
		}
	}
	cout << "com_fd = " << com_fd << endl;

	return com_fd;
}

int PhoneProxy::accepting_loop(bool yes_no){	
	struct sockaddr_in clt_addr;
	socklen_t clt_len;
	int clt_sockfd;
	while (yes_no) {
		usleep(30 * 1000);
		clt_len = sizeof(clt_addr);
		clt_sockfd = my_accept((struct sockaddr *)&clt_addr, &clt_len);
		if(clt_sockfd == -EINTR){
			continue;
		}
		char *new_ip = NULL;
		struct in_addr ia = clt_addr.sin_addr; //(int)ip
		new_ip = inet_ntoa(ia);
		
		for(int i=0; i<CLIENT_NUM ; i++){
			
			if(ci[i].client_fd == -1){
				ci[i].client_fd = clt_sockfd;
				
				memset(ci[i].client_ip, 0, sizeof(ci[i].client_ip));
				memcpy(ci[i].client_ip, new_ip, strlen(new_ip)+1);
				cout << " f: " << __FUNCTION__
					 << " l: " << __LINE__
					 << " client_ip = " << ci[i].client_ip
					 << " client_num = " << i << endl;

				if(ci[i].timer_setting == false){
					ci[i].timer_setting = true;				
					ci[i].old_timer_counter = ci[i].timer_counter = 0;
					ci[i].exit_threshold = 0;
					setClientTimer(&ci[i], 10, recycleClient, &ci[i], this);
				}

				int ret;	
				ret = fcntl(clt_sockfd, F_GETFL, 0);  
				fcntl(clt_sockfd, F_SETFL, ret | O_NONBLOCK);  


				struct epoll_event ev;
				ev.events = EPOLLIN;
				ev.data.ptr = &ci[i];
				if(epoll_ctl(epollfd, EPOLL_CTL_ADD, clt_sockfd, &ev) == -1){
					perror("epoll_ctl : client_fd ");
					exit (-1);
				}


				
				break;
				
			}
		}	
		for(int i=0; i<CLIENT_NUM; i++){
			cout << i << " " << ci[i].client_fd << endl;
		}
	}
	
	return 0;
}


PhoneProxy::PstnCmdEnum PhoneProxy::getCmdtypeFromString(char *cmd_str){
	PstnCmdEnum cmdtype;
	
	if (strncmp(cmd_str, "OPTION_", 7) == 0) {
		cmdtype = HEARTBEAT;	
	} else if (strncmp(cmd_str, "DIALING", 7) == 0) {
		cmdtype = DIALING;
	} else if (strncmp(cmd_str, "OFFHOOK", 7) == 0) {
		cmdtype = OFFHOOK;	
	} else if (strncmp(cmd_str, "ONHOOK_", 7) == 0) {
		cmdtype = ONHOOK;		
	} else if (strncmp(cmd_str, "DTMFSND", 7) == 0) {
		cmdtype = DTMF_SEND;	
	} else if (strncmp(cmd_str, "FLASH__", 7) == 0) {
		cmdtype = FLASH;
	} else if (strncmp(cmd_str, "MUTE___", 7) == 0) {
		cmdtype = MUTE;	
	} else if (strncmp(cmd_str, "QUERY__", 7) == 0) {	
		cmdtype = QUERY;
	} else if (strncmp(cmd_str, "LOGIN__", 7) == 0) {
		cmdtype = LOGIN;	
	} else if (strncmp(cmd_str, "LOGOUT_", 7) == 0) {
		cmdtype = LOG_OUT;	
	} else if (strncmp(cmd_str, "LOGOUTA", 7) == 0) {
		cmdtype = LOGOUTALL;	
	} else if (strncmp(cmd_str, "SWTOSON", 7) == 0) {
		cmdtype = SWITCHTOSONMACHINE;	
	} else if (strncmp(cmd_str, "SWOFFHK", 7) == 0) {
		cmdtype = SWITCHOFFHOOK;	
	} else if (strncmp(cmd_str, "SWONHOK", 7) == 0) {
		cmdtype = SWITCHONHOOK;
	} else if (strncmp(cmd_str, "SWIBACK", 7) == 0) {
		cmdtype = SWITCHBACK;	
	} else if (strncmp(cmd_str, "TB_DIAL", 7) == 0) {
		cmdtype = TALKBACKDIALING;
	} else if (strncmp(cmd_str, "TB_OFHK", 7) == 0) {
		cmdtype = TALKBACKOFFHOOK;
	} else if (strncmp(cmd_str, "TB_ONHK", 7) == 0) {
		cmdtype = TALKBACKONHOOK;	
	} else 	{
		cout << "command undefined" << endl;
		cmdtype = UNDEFINED;
	}

	return cmdtype;	
}

int PhoneProxy::netWrite(int fd,const void *buffer,int length){
	int bytes_left; 
	int written_bytes; 
	const char *ptr;
	ptr = (const char *)buffer; 
	bytes_left = length; 
	while(bytes_left > 0) { 
		//begin to write
		written_bytes = write(fd,ptr,bytes_left); 
		if(written_bytes <= 0) { //error       
			if(errno == EINTR) //interrupt error, we continue writing
				written_bytes = 0; 
			else             //other error, exit 
				return (-1); 
		} 
		bytes_left -= written_bytes; 
		ptr += written_bytes;     //from where left,  continue writing
	} 
	return (0); 
}

int PhoneProxy::netRead(int fd,void *buffer,int length){
	int bytes_left; 
	int bytes_read; 
	char *ptr;	
    ptr = (char *)buffer;
	bytes_left = length; 
	while(bytes_left > 0) { 
		bytes_read = read(fd,ptr,bytes_left); 
		if(bytes_read < 0) { 
			if(errno == EINTR){ 
				bytes_read = 0;
				perror("net_read error EINTR: ");
			}else {
				perror("net_read error other: ");
				return (-1);
			}
		} else if (bytes_read == 0) {
			perror("net_read bytes = 0 : ");
			break; 
		}
		bytes_left -= bytes_read; 
		ptr += bytes_read; 
	} 
	
	return (length - bytes_left); 
}

//buffer end with '\n' (in count) and then '\0'(out of count)
ssize_t PhoneProxy::netReadLine(int fd,void *buffer,size_t maxlen){
	ssize_t 	n;
	if ( (n = readline(fd, buffer, maxlen)) < 0)
		perror("readline error: ");
	return(n);	
}

// head      id     length       cmd        arg_len      argument (64)       terminator
//HEADS    1	     022    	DIALING	   012       913146672056         \n

int PhoneProxy::parseClient(cli_info_t *ci_){

	cout << __FUNCTION__ << " : " << __LINE__ << endl;
	cout << "client_fd : " << ci_->client_fd << endl;
	ssize_t nread;
	char buff[MAX_LEN_PCLI] = {0};
	char *pbuff = buff;
	
	nread = netReadLine(ci_->client_fd, buff, MAX_LEN_PCLI);
	cout << __FUNCTION__ << " : " << __LINE__ << endl;
	cout << "nread : " << nread << endl;
	if(nread < 0){
		destroyClient(ci_);
		return (-1);
	}
	if(nread == 0){
		destroyClient(ci_);
		return (-1);
	}
	
	memset(&_cli_req, 0, sizeof(cli_request_t));
	memcpy(_cli_req.head, pbuff, 5);
	if(strcmp(_cli_req.head, "HEADS") != 0){
		memset(&_cli_req, 0, sizeof(cli_request_t));
		return -1;
	}

	_cli_req.fd = ci_->client_fd;
	ci_->id = _cli_req.id = pbuff[5];
	
	
	char length[4] = {0};
	char arg_len[4] = {0};
	memcpy(length, pbuff+6, 3);
	memcpy(arg_len, pbuff+16, 3);

	_cli_req.length = atoi(length);
	_cli_req.arglen = atoi(arg_len);
	if(_cli_req.length - _cli_req.arglen != 10){
		memset(&_cli_req, 0, sizeof(cli_request_t));
		return -1;
	}

	char cmd[8] = {0};
	memcpy(cmd, pbuff+9, 7);
	_cli_req.cmd = getCmdtypeFromString(cmd);
	if(_cli_req.cmd == UNDEFINED){
		memset(&_cli_req, 0, sizeof(cli_request_t));
		return -1;
	}

	memcpy(_cli_req.arg, pbuff+19, _cli_req.arglen);

	return 0;
}
		
int PhoneProxy::handleClient(cli_info_t *ci_){
	if(ci_->client_fd == -1){
		cout << "the client is exit" << endl;
		return (-1);
	}
	char send_buf[MAX_LEN_PCLI] = {0};
	cout << __FUNCTION__ << " : " << __LINE__ << endl;
	switch(_cli_req.cmd){
		case UNDEFINED:
			break;
		case DEFAULT:
			break;
		case HEARTBEAT:
			cout << "HEARTBEAT" << endl;
			
			if(ci_->timer_setting == true){
				ci_->timer_counter ++;
			}
			
			snprintf(send_buf, 22, 
				"HEADR%c010OPTI_OK000\r\n", _cli_req.id);
			netWrite(ci_->client_fd, send_buf, strlen(send_buf));
			
			break;
		case DIALING:
			pcs->setGoingNumber(_cli_req.arg, _cli_req.arglen);
			netWrite(phone_proxy_fd[0], "DIALING\n", 8);
			break;
		case OFFHOOK:
			netWrite(phone_proxy_fd[0], "OFFHOOK\n", 8);
			break;
		case ONHOOK:
			netWrite(phone_proxy_fd[0], "ONHOOK\n", 7);
			break;
		case DTMF_SEND:
			pcs->setDtmfNumber(_cli_req.arg[0]);
			netWrite(phone_proxy_fd[0], "DTMFSEND\n", 9);
			break;
		case FLASH:
			netWrite(phone_proxy_fd[0], "FLASH\n", 6);
			break;
		case MUTE:
			bool mute;
			if(_cli_req.arg[0] == '1')
				mute = true;
			else if(_cli_req.arg[0] == '0')
				mute = false;
			pcs->setMute(mute);
			netWrite(phone_proxy_fd[0], "MUTE\n", 5);
			break;
		case QUERY:
			
			break;
		case LOGIN:
			break;
		case LOG_OUT:
			break;
		case LOGOUTALL:
			break;
		case SWITCHTOSONMACHINE:
			snprintf(send_buf, 23, 
				"HEADR%c011SWTOSON001%c\r\n", _cli_req.id, _cli_req.arg[0]);
			for(int i=0; i<CLIENT_NUM; i++){
				if(ci[i].id == _cli_req.arg[0]){
					netWrite(ci[i].client_fd, send_buf, strlen(send_buf));
					break;
				}
			}
			break;
		case SWITCHOFFHOOK:
			snprintf(send_buf, 23, 
				"HEADR%c011SWOFFHK001%c\r\n", _cli_req.id, _cli_req.arg[0]);			
			for(int i=0; i<CLIENT_NUM; i++){
				if(ci[i].id == _cli_req.arg[0]){
					netWrite(ci[i].client_fd, send_buf, strlen(send_buf));
					break;
				}
			}			
			break;
		case SWITCHONHOOK:
			snprintf(send_buf, 23, 
				"HEADR%c011SWONHOK001%c\r\n", _cli_req.id, _cli_req.arg[0]);			
			for(int i=0; i<CLIENT_NUM; i++){
				if(ci[i].id == _cli_req.arg[0]){
					netWrite(ci[i].client_fd, send_buf, strlen(send_buf));
					break;
				}
			}					
			break;
		case SWITCHBACK:
			break;
		case TALKBACKDIALING:
			snprintf(send_buf, 23, 
				"HEADR%c011TB_DIAL001%c\r\n", _cli_req.id, _cli_req.arg[0]);			
			for(int i=0; i<CLIENT_NUM; i++){
				if(ci[i].id == _cli_req.arg[0]){
					netWrite(ci[i].client_fd, send_buf, strlen(send_buf));
					break;
				}
			}

			break;
		case TALKBACKOFFHOOK:
			snprintf(send_buf, 23, 
				"HEADR%c011TB_OFHK001%c\r\n", _cli_req.id, _cli_req.arg[0]);			
			for(int i=0; i<CLIENT_NUM; i++){
				if(ci[i].id == _cli_req.arg[0]){
					netWrite(ci[i].client_fd, send_buf, strlen(send_buf));
					break;
				}
			}

			break;
		case TALKBACKONHOOK:
			snprintf(send_buf, 23, 
				"HEADR%c011TB_ONHK001%c\r\n", _cli_req.id, _cli_req.arg[0]);			
			for(int i=0; i<CLIENT_NUM; i++){
				if(ci[i].id == _cli_req.arg[0]){
					netWrite(ci[i].client_fd, send_buf, strlen(send_buf));
					break;
				}
			}

			break;			
		default:
			break;
	}
	
	return 0;
}

int PhoneProxy::parsePhoneControlServiceEvent(){
	ssize_t nread;
	char buff[MAX_NUM_LEN_] = {0};	
	nread = netReadLine(phone_proxy_fd[0], buff, MAX_NUM_LEN_);
	if(nread < 0){
		return (-1);
	}
	if(strcmp(buff, "RINGON\n") == 0){
		cout << __FUNCTION__ << " " << __LINE__
			 << " " << "RINGON" << endl;

		_phone_control_service_event = RINGON;
	}
	if(strcmp(buff, "RINGOFF\n") == 0){
		_phone_control_service_event = RINGOFF;
	}
	if(strcmp(buff, "INCOMING\n") == 0){
		cout << __FUNCTION__ << " " << __LINE__
			 << " " << "incoming" << endl;
			 
		_phone_control_service_event = INCOMING_NUM;
	}
	if(strcmp(buff, "BUSYLINE\n") == 0){
		_phone_control_service_event = BUSYLINE;
	}

	return 0;
}		

int PhoneProxy::handlePhoneControlServiceEvent(){
	char send_buf[MAX_LEN_PCLI] = {0};
	char tele_no[MAX_NUM_LEN_] = {0};
	switch(_phone_control_service_event){
		case DEFAULT_INCOMING:
			return (-1);
		case RINGON:							
			for(int i=0; i<CLIENT_NUM; i++){
				if(ci[i].client_fd != -1){
					netWrite(ci[i].client_fd, "HEADR0010RINGON_000\r\n", 22);					
				}
			}			
			break;
		case RINGOFF:
			for(int i=0; i<CLIENT_NUM; i++){
				if(ci[i].client_fd != -1){
					netWrite(ci[i].client_fd, "HEADR0010RINGOFF000\r\n", 22);					
				}
			}			
			break;
		case INCOMING_NUM:
			
			int tele_no_len;
			pcs->getIncomingNumber(tele_no, &tele_no_len);
			cout << __FUNCTION__ << " " << __LINE__
			 << " " << "incoming no : " << tele_no << endl;
			
			snprintf(send_buf, 22+tele_no_len, "HEADR0%03dINCOMIN%03d%s\r\n",
							 10+tele_no_len, tele_no_len, tele_no);			
			for(int i=0; i<CLIENT_NUM; i++){
				if(ci[i].client_fd != -1){
					netWrite(ci[i].client_fd, send_buf, strlen(send_buf)+1);					
				}
			}			
			break;	
		case BUSYLINE:
			for(int i=0; i<CLIENT_NUM; i++){
				if(ci[i].client_fd != -1){
					netWrite(ci[i].client_fd, "HEADR0010LINBUSY000\r\n", 22);					
				}
			}			
			break;	
		default:
			break;
	}
	return 0;
}





int32_t PhoneProxy::startPhoneProxy(){
    if (_phoneProxyRunning) {
        return 0;
    }

    _phoneProxyRunning = true;

	// PhoneControlServiceRunning
    const char* threadName = "handaer_phone_proxy_thread";
    _ptrThreadPhoneProxy = ThreadWrapper::CreateThread(phoneProxyThreadFunc,
                                                this,
                                                kRealtimePriority,
                                                threadName);
    if (_ptrThreadPhoneProxy == NULL) {
        cout << "failed to create the phone proxy thread" << endl;
        _phoneProxyRunning = false;
        return -1;
    }

    unsigned int threadID(0);
    if (!_ptrThreadPhoneProxy->Start(threadID)) {
        cout << "failed to start the phone proxy thread" << endl;
        _phoneProxyRunning = false;
        delete _ptrThreadPhoneProxy;
        _ptrThreadPhoneProxy = NULL;
        return -1;
    }
    _phoneProxyThreadId = threadID;


    return 0;	

}
int32_t PhoneProxy::stopPhoneProxy(){
	_phoneProxyRunning = false;

    if ( _ptrThreadPhoneProxy
			&& !_ptrThreadPhoneProxy->Stop() ) {
        cout << "failed to stop the phone proxy thread" << endl;
        return -1;
    } else {
        delete _ptrThreadPhoneProxy;
        _ptrThreadPhoneProxy = NULL;
    }
	
    return 0;

}
bool PhoneProxy::phoneProxyisRunning() const{
	return (_phoneProxyRunning);

}

int32_t PhoneProxy::startHeartBeating(){
    if (_heartBeatingisRunning) {
        return 0;
    }

    _heartBeatingisRunning = true;

	// PhoneControlServiceRunning
    const char* threadName = "handaer_heart_beating_thread";
    _ptrThreadHeartBeating = ThreadWrapper::CreateThread(heartBeatingThreadFunc,
                                                this,
                                                kRealtimePriority,
                                                threadName);
    if (_ptrThreadHeartBeating == NULL) {
        cout << "failed to create the heart beating thread" << endl;
        _heartBeatingisRunning = false;
        return -1;
    }

    unsigned int threadID(0);
    if (!_ptrThreadHeartBeating->Start(threadID)) {
        cout << "failed to start the heart beating thread" << endl;
        _heartBeatingisRunning = false;
        delete _ptrThreadHeartBeating;
        _ptrThreadHeartBeating = NULL;
        return -1;
    }
    _heartBeatingThreadId = threadID;


    return 0;	

}
int32_t PhoneProxy::stopHeartBeating(){
	_heartBeatingisRunning = false;

    if ( _ptrThreadHeartBeating
			&& !_ptrThreadHeartBeating->Stop() ) {
        cout << "failed to stop the heart beating thread" << endl;
        return -1;
    } else {
        delete _ptrThreadHeartBeating;
        _ptrThreadHeartBeating = NULL;
    }
	
    return 0;
}
bool PhoneProxy::heartBeatingisRunning() const{
	return (_heartBeatingisRunning);

}




bool PhoneProxy::phoneProxyThreadFunc(void* pThis){
	return (static_cast<PhoneProxy*>(pThis)->phoneProxyThreadProcess());

}

bool PhoneProxy::phoneProxyThreadProcess(){
	//cout << __FUNCTION__ << " " << __LINE__ << endl;
	
	int nfds;
	struct epoll_event events[MAX_EVENTS];
	nfds = epoll_wait(epollfd, events, MAX_EVENTS, EPOLL_TIMEOUT_MS);
	if(nfds == -1){
		perror("epoll_wait : ");
		exit(-1);
	}
	if(nfds > 0)
		cout << " nfds : " << nfds << endl;
	for(int n=0; n<nfds; ++n){
		if(events[n].data.fd == phone_proxy_fd[0]){
			parsePhoneControlServiceEvent();
			handlePhoneControlServiceEvent();
		} else {
			parseClient((cli_info_t *) events[n].data.ptr); 
			handleClient((cli_info_t *) events[n].data.ptr);
		}
	}	
	return true;
}

bool PhoneProxy::heartBeatingThreadFunc(void* pThis){
	return (static_cast<PhoneProxy*>(pThis)->heartBeatingThreadProcess());

}





void PhoneProxy::notify( int signum ){        
	assert( signum == SIGALRM );
	int i;
	for(i = 0; i < CLIENT_NUM; i++) {
		if(timer_info_g[i].in_use == 0) {
			continue;
		}
        timer_info_g[i].elapse ++;
		if(timer_info_g[i].elapse == 
		   			timer_info_g[i].interval) {
            timer_info_g[i].elapse = 0;
            timer_info_g[i].timer_func_cb(timer_info_g[i].timer_func_cb_data,
				        timer_info_g[i].this_obj);
		}
	}
	
	return;
}

bool PhoneProxy::heartBeatingThreadProcess(){
	cout << __FUNCTION__ << " " << __LINE__ << endl;

	
	timer->setTimer(TIMER_SEC, 0);
	timer->setHandler(notify);    
	timer->reset();
	
	return false;
}

void PhoneProxy::get_current_format_time(char * tstr) {
	time_t t;
	t = time(NULL);
	strcpy(tstr, ctime(&t));
	tstr[strlen(tstr)-1] = '\0'; // replace '\n' with '\0'
	return;
}



int PhoneProxy::destroyClient(cli_info_t *pci){
	cout << __FUNCTION__ << " " << __LINE__ << endl;
	if(pci->timer_setting){
		deleteClientTimer(pci);
		pci->timer_setting = false;
	}
	//int epollfd_tmp = getEpollFd();
	if(epoll_ctl(epollfd, EPOLL_CTL_DEL, pci->client_fd, NULL)) {
		perror("epoll_ctl_del : ");
		return (-1);
	}
	netWrite(pci->client_fd, "You will be not online\n", 23);
	close(pci->client_fd);
	
	memset(pci, 0, sizeof(cli_info_t));
	pci->client_fd = -1;
	pci->id = -1;

	for(int i=0; i<CLIENT_NUM; i++){
		cout << i << " " << ci[i].client_fd << endl;
	}

	return 0;
}


// arg --> cli_info_t *
int PhoneProxy::recycleClient(void *arg, void *pThis){
	if(arg == NULL){
		return -1;
	}
	PhoneProxy *ppx = static_cast<PhoneProxy*>(pThis);
	cli_info_t * cli_info_ = (cli_info_t *)arg;
	cout << "client_fd " << cli_info_->client_fd << endl;

	char tstr[200];
	get_current_format_time(tstr);
	cout << __FUNCTION__ << " " << tstr << endl;
	cout << "cli_info_->old_timer_counter " << cli_info_->old_timer_counter
	 << endl << "cli_info_->timer_counter " << cli_info_->timer_counter
	 << endl << "cli_info_->exit_threshold " << cli_info_->exit_threshold 
	 << endl;
	if(cli_info_->old_timer_counter == cli_info_->timer_counter){
		cli_info_->exit_threshold ++;
	}else{
		cli_info_->exit_threshold  = 0;
		cli_info_->old_timer_counter = cli_info_->timer_counter;
	}
	if(cli_info_->exit_threshold > 4){
		ppx->destroyClient(cli_info_);		
	}
	return 0;
}

int PhoneProxy::setClientTimer(cli_info_t* cli_info, int interval, 
			timer_process_cbfn_t timer_proc, void *arg, void* pThis) {
	if (timer_proc == NULL || interval <= 0) {
		return(-1);
	}
	
	int i;
	for(i=0 ; i<CLIENT_NUM; i++){
		if(timer_info_g[i].in_use == 1) {
			continue;
		}

		memset(&timer_info_g[i], 0, sizeof(timer_info_g[i]));

		timer_info_g[i].timer_func_cb = timer_proc;
		if(arg != NULL) {			
	        timer_info_g[i].timer_func_cb_data = arg;
		}
		timer_info_g[i].this_obj = pThis;
	    timer_info_g[i].interval = interval;
	    timer_info_g[i].elapse = 0;
	    timer_info_g[i].in_use = 1;
	
		cli_info->ti = &timer_info_g[i];
		break;
	}
	
	if(i >= CLIENT_NUM) {
		return(-1);
	}
	return 0;
}



int PhoneProxy::deleteClientTimer(cli_info_t* cli_info) {
	cout << __FUNCTION__ << " " << __LINE__ << endl;

	if(cli_info->ti == NULL){
		return -1;
	}
	
	memset(cli_info->ti, 0, sizeof(timer_info_t));
	cli_info->ti = NULL;
	
	return(0);
}

bool PhoneProxy::resetTimerInfo(){
	memset(timer_info_g, 0, sizeof(timer_info_g));
	return true;
}


bool PhoneProxy::phoneProxyInit(int port){
	epollfd = epoll_create(MAX_EVENTS);
	if(epollfd == -1){
		perror("epoll create: ");
		exit (-1);
	}
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, phone_proxy_fd) < 0) {   
	    perror("socketpair: ");   
	    exit (-1);   
    }
	
	PhoneControlService::setPhoneProxyFd(phone_proxy_fd[1]);
	pcs = new PhoneControlService();

	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = phone_proxy_fd[0];
	if(epoll_ctl(epollfd, EPOLL_CTL_ADD, phone_proxy_fd[0], &ev) == -1){
		perror("epoll_ctl : phone_proxy_fd[0] ");
		exit (-1);
	}

	listenOnServerSocket(port);

	resetTimerInfo();
	timer = new PhoneTimer(TIMER_SEC, 0);
	startHeartBeating();
	startPhoneProxy();

#if 0
	sigset_t signal_set;
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGALRM);
	int status = pthread_sigmask(SIG_BLOCK, &signal_set, NULL);
	if(status != 0){
		perror("set signal mask : ");
	}
#endif

	return true;
}
bool PhoneProxy::phoneProxyExit(){
	stopPhoneProxy();
	stopHeartBeating();

	timer->cancel();
	if(timer != NULL){
		delete timer;
		timer = NULL;
	}
	resetTimerInfo();

	close(serv_listen_sockfd);
	close(epollfd);
	if(pcs != NULL){
		delete pcs;
		pcs = NULL;
	}

	return true;
}





}

