/**
 * @file PSTNserver.cpp
 * @brief  PSTN server for pad.
 * @author Chen Chunsheng, badwtg1111@hotmail.com
 * @version 3.5
 * @date 2012-02-01
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <netdb.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>
#include <iostream>

#include <sys/time.h>
#include <assert.h>




//#include "linux/socket.h"
//#include <asm/socket.h>
//#include "linux/tcp.h"


using namespace std;


#define CURRENT_VERSION_FOR_PSTN "V 1.0.1"




#include "padtophone.h"

#include "mymediastream.h"


#define BACK_LOG 1

#define PAD_IP "10.10.10.100"
#define LOCAL_PORT  44444




#define REMOTE_PORT  55556

typedef struct fds_tag{
	int conn_fd;
	int serial_fd;
	char *file;
	int payload;
	char remote_ip_addr[50];
	
}FDS;

pthread_mutex_t mutex;

enum PstnCommand {
		/*PSTN普通电话*/
		OFFHOOK,	//0
		FREEOFH,	//1
		ONHOOK,		//2
		DIALING,	//3
		EXIT,		//4
		INCOMING,	//5

		/*客户端心跳包*/
		HEARTBEAT,
		
		/*注册功能*/
		QUERY,
		LOGIN,
		LOG_OUT,
		//LOGOUT2,
		LOGOUTALL,

		/*转接功能*/
		TOSON,
		MA_RESPONSE,

		/*对讲功能*/
		TB_ONHOOK,
		TB_OFFHOOK,
		TB_HANDSFREE,
		TB_HANDLE,
		TB_SUBMACH1,
		TB_SUBMACH2,

		/*音量调节*/
		VOLUME_HANDLE,
		VOLUME_HANDSFREE,

		VOLUME_HANDSFREE7,
		VOLUME_HANDSFREE6,
		VOLUME_HANDSFREE5,
		VOLUME_HANDSFREE4,
		
		/*三方通话*/
		TBTOTHREEPARTY,
		THREEPARTYTOTB,

		/*DTMF发送0~9，*，#，*/
		DTMF_SEND
		
};  
typedef enum PstnCommand PstnCmd;

typedef struct {
	char head[5]; //消息头
	char length[4]; //消息长度
	char cmd[8]; //命令
	char arglen[4]; //参数长度
	char arg[20]; //参数
	//short crc16;
}net_data; //传输协议的格式

int local_port = LOCAL_PORT;
char *remote_ip = NULL;//REMOTE_IP;
int remote_port = REMOTE_PORT;
/* ******************************************************************/
/**
 * @brief  net_write   -->
 *
 * @param  fd  -->
 * @param  buffer  -->
 * @param  length  -->
 *
 * @return  
 */
/* ******************************************************************/
int net_write(int fd,const void *buffer,int length) 
{ 
	int bytes_left; 
	int written_bytes; 
	char *ptr; 

	ptr = (char *)buffer; 
	bytes_left = length; 
	while(bytes_left > 0) 
	{ 
		/* 开始写*/ 
		written_bytes = write(fd,ptr,bytes_left); 
		if(written_bytes <= 0) /* 出错了*/ 
		{        
			if(errno == EINTR) /* 中断错误 我们继续写*/ 
				written_bytes = 0; 
			else             /* 其他错误 没有办法,只好撤退了*/ 
				return (-1); 
		} 
		bytes_left -= written_bytes; 
		ptr += written_bytes;     /* 从剩下的地方继续写  */ 
	} 
	return (0); 
} 
/* ******************************************************************/
/**
 * \brief  net_read   --> 完整的读函数
 *
 * \param  fd        	  --> 文件描述符
 * \param  buffer     --> 读出的数据
 * \param  length    --> 想要读的长度
 *
 * \return  返回读到的字节数，
 *            错误返回 -1
 */
/* ******************************************************************/
int net_read(int fd,void *buffer,int length) 
{ 
	int bytes_left; 
	int bytes_read; 
	char *ptr;
	
    ptr =(char *) buffer;
	bytes_left = length; 
	while(bytes_left > 0) 
	{ 
		bytes_read = read(fd,ptr,bytes_left); 
		if(bytes_read < 0) 
		{ 
			if(errno == EINTR){ 
				bytes_read = 0;
				perror("net_read error!");
			}else {
				perror("net_read error <0!");
				return (-1);
			}
		} 
		else if(bytes_read == 0) {
			perror("net_read bytes = 0 !");
			break; 
		}
		bytes_left -= bytes_read; 
		ptr += bytes_read; 
	} 
	return (length - bytes_left); 
} 


int getCmdtypeFromString(char *cmd_str){
	int cmdtype;
	
	if (strncmp(cmd_str, "OFFHOOK", 7) == 0) {
		cmdtype = OFFHOOK;	
	} else if (strncmp(cmd_str, "FREEOFH", 6) == 0) {
		cmdtype = FREEOFH;
	} else if (strncmp(cmd_str, "ONHOOK", 6) == 0) {
		cmdtype = ONHOOK;	
	} else if (strncmp(cmd_str, "DIALING", 7) == 0) {
		cmdtype = DIALING;		
	} else if (strncmp(cmd_str, "EXIT", 4) == 0) {
		cmdtype = EXIT;	
	} else if (strncmp(cmd_str, "OPTION", 6) == 0) {
		cmdtype = HEARTBEAT;
	} else if (strncmp(cmd_str, "QUERY", 5) == 0) {
		cmdtype = QUERY;	
	} else if (strncmp(cmd_str, "LOGIN", 5) == 0) {
		cmdtype = LOGIN;
	} else if (strncmp(cmd_str, "LOG_OUT", 7) == 0) {
		cmdtype = LOG_OUT;
//	} else if (strncmp(cmd_str, "LOGOUT2", 7) == 0) {
//		cmdtype = LOGOUT2;
	} else if (strncmp(cmd_str, "LOGOUTA", 7) == 0) {
		cmdtype = LOGOUTALL;
	} else if (strncmp(cmd_str, "TOSON", 5) == 0) {	
		cmdtype = TOSON;				
	} else if (strncmp(cmd_str, "MA_RESP", 7) == 0) {
		cmdtype = MA_RESPONSE;	
	} else if (strncmp(cmd_str, "TB_ONHK", 7) == 0) {
		cmdtype = TB_ONHOOK;
	} else if (strncmp(cmd_str, "TB_OFHK", 7) == 0) {
		cmdtype = TB_OFFHOOK;
	} else if (strncmp(cmd_str, "TB_HDFR", 7) == 0) {
		cmdtype = TB_HANDSFREE;
	} else if (strncmp(cmd_str, "TB_HAND", 7) == 0) {
		cmdtype = TB_HANDLE;
	} else if (strncmp(cmd_str, "TB_SUB1", 7) == 0) {
		cmdtype = TB_SUBMACH1;	
	} else if (strncmp(cmd_str, "TB_SUB2", 7) == 0) {
		cmdtype = TB_SUBMACH2;	
	} else if (strncmp(cmd_str, "VOL_HND", 7) == 0) {
		cmdtype = VOLUME_HANDLE;	
	} else if (strncmp(cmd_str, "VOL_HFR", 7) == 0) {
		cmdtype = VOLUME_HANDSFREE;	
	} else if (strncmp(cmd_str, "VOL_HF7", 7) == 0) {
		cmdtype = VOLUME_HANDSFREE7;	
	} else if (strncmp(cmd_str, "VOL_HF6", 7) == 0) {
		cmdtype = VOLUME_HANDSFREE6;	
	} else if (strncmp(cmd_str, "VOL_HF5", 7) == 0) {
		cmdtype = VOLUME_HANDSFREE5;	
	} else if (strncmp(cmd_str, "VOL_HF4", 7) == 0) {
		cmdtype = VOLUME_HANDSFREE4;	
	} else if (strncmp(cmd_str, "TBTOTHP", 7) == 0) {
		cmdtype = TBTOTHREEPARTY;	
	} else if (strncmp(cmd_str, "THPTOTB", 7) == 0) {
		cmdtype = THREEPARTYTOTB;	
	} else if (strncmp(cmd_str, "DTMFSND", 7) == 0) {
		cmdtype = DTMF_SEND;	
	} else 	{
		printf("cmd not match\n");
		cmdtype = -1;
	}

	return cmdtype;
}


int parseClient(int sockfd, char *data_, int* pdata_len_)
{
	int data_len, arg_len;
	//ssize_t r_size;
	int cmdtype;
	ssize_t nReadFromClient;

	net_data *info_buf = NULL;
	info_buf = (net_data *)malloc(sizeof(net_data));
	if (info_buf == NULL) {
		printf("fail to malloc\n");
		return -1;
	}
	memset(info_buf, 0, sizeof(net_data)); // net_data 清零


	//int timeout = 10;    //超时处理，长时间读不到消息，当timeout减到0时，返回到上层

	while (1)
	{
		usleep(10000);
#if 0
		timeout--; 
					//由于采用轮询读的方法，如果没消息则会一直循环，
					//设置一个超时值，当超出后还没数据的话，就退出此次读消息
		if (!timeout) {
			printf("No start info_buf\n");
			goto fail;
		}
#endif
		if ((nReadFromClient = net_read (sockfd, info_buf->head, 4)) < 0) {
			perror("read START err");
			//goto clientoutofcontrol;
			goto fail;
		} //读出数据头
		else if (nReadFromClient == 0){
			printf("The client exit in %s\n", __FUNCTION__);
			goto clientoutofcontrol;
		}
		
		//判断是否为帧头，不是就继续循环读
		if (strncmp(info_buf->head, "HEAD", 4) != 0) {
			printf("head is %s\n", info_buf->head);
			char temp[1024];
			net_read (sockfd, temp, 1024);
			printf("after HEAD is :%s", temp);
			goto fail;

		} else {	//判断是否为帧头，是就继续读后面的信息
	//		timeout = 40;


			if (net_read (sockfd, info_buf->length, 3) < 0) {
				printf("read length err\n");
				goto fail;
			}  //读出数据长度
			
			data_len = atoi(info_buf->length);
			
			printf("data_len = %d\n", data_len);

			if (net_read(sockfd, info_buf->cmd, 7) < 0) {
				printf("read cmd err\n");
				goto fail;
			}//读出命令

			if (net_read(sockfd, info_buf->arglen, 3) < 0) {
				printf("read arglen err\n");
				goto fail;
			}//读出参数长度
			
			arg_len = atoi(info_buf->arglen);
			printf("arg_len = %d\n", arg_len);
			
			if ((data_len - 10) > 0 || arg_len > 0) {

				if (net_read(sockfd, info_buf->arg, arg_len) < 0) {
					printf("read arg err\n");
					goto fail;
				}
			} //读出参数

			break;
		}//end if
	}//end while
	
	
#if 0 
	crc16 = ((rev_buf[4+data_lenth] & 0xffff) << 8) | rev_buf[5+data_lenth];  
	crc_head = rev_buf;
	crc_lenth = data_lenth + 4 ;

         //CRC16校验
	if (crc16 == get_crc16(crc_head, crc_lenth)) {
#endif

	cout << __FUNCTION__ << " " << __LINE__ << endl;
	cmdtype = getCmdtypeFromString(info_buf->cmd);
	cout << "cmdtype: " << cmdtype << endl;
	if (cmdtype == -1) goto fail;
	
	*pdata_len_ = arg_len;
	if (arg_len > 0) {
		memcpy(data_, info_buf->arg, sizeof(info_buf->arg));
		cout << __LINE__ << " " 
			<< *pdata_len_ << " " << sizeof(info_buf->arg) << endl;
	}
	
	free(info_buf);
	return cmdtype;
	
clientoutofcontrol:
	free(info_buf);
	cout << "clientoutofcontrol" <<" "
		<< __FUNCTION__ << " " << __LINE__ << endl;
	
	return -2;
fail:
	free(info_buf);
	return -1;
}

//int argc_tele = 7;

//int argc_tele = 14;
int argc_tele = 20;


char *argv_tele[] = {

	(char *)"mediastream",
	(char *)"--local",
	(char *)"44444",
	(char *)"--remote",
	NULL, //argv_tele[4]
	(char *)"--payload",
	NULL,//"3",//"0",//"8",//argv_tele[6]
	//"audio/pcmu/8000",

#if 0
	"--ec",
	"--ec-tail",
	"120",//"300",
	"--ec-delay",
	"300",//"620",//"0",
	"--ec-framesize",
	"128",//"160",
#endif
#if 1
//	"--agc",

	(char *)"--ng",
	(char *)"--ng-threshold",
	(char *)"0.006",
	(char *)"--ng-floorgain",
	(char *)"0.0005",
	
	(char *)"--el",
	//"--el-speed",
	//"",
	(char *)"--el-thres",
	(char *)"0.01",
	(char *)"--el-force",
	(char *)"100000",
	(char *)"--el-sustain",
	(char *)"400",
	(char *)"--el-transmit-thres",
	(char *)"17"
#endif
	//"--jitter",
	//"80"
};

#if 0

el_type=mic
el_thres=0.03
el_force=100000
el_sustain=400
el_transmit_thres=1.7
ng_floorgain=0.01

[sound]
playback_dev_id=ANDROID SND: Android Sound card
ringer_dev_id=ANDROID SND: Android Sound card
capture_dev_id=ANDROID SND: Android Sound card
remote_ring=/data/data/org.linphone/files/ringback.wav
local_ring=/data/data/org.linphone/files/oldphone_mono.wav
ec_tail_len=120
ec_framesize=128
el_type=mic
el_thres=0.03
el_force=100000
el_sustain=400
el_transmit_thres=1.7
ng_floorgain=0.01
echocancellation=0

"[ --ng (enable noise gate)] \n"
"[ --ng-threshold <(float) [0-1]> (noise gate threshold) ]\n"
"[ --ng-floorgain <(float) [0-1]> (gain applied to the signal when its energy is below the threshold.) ]\n"
"[ --capture-card <name> ]\n"
"[ --playback-card <name> ]\n"
"[ --infile	<input wav file> specify a wav file to be used for input, instead of soundcard ]\n"
"[ --outfile <output wav file> specify a wav file to write audio into, instead of soundcard ]\n"
"[ --camera <camera id as listed at startup> ]\n"
"[ --el (enable echo limiter) ]\n"
"[ --el-speed <(float) [0-1]> (gain changes are smoothed with a coefficent) ]\n"
"[ --el-thres <(float) [0-1]> (Threshold above which the system becomes active) ]\n"
"[ --el-force <(float) [0-1]> (The proportional coefficient controlling the mic attenuation) ]\n"
"[ --el-sustain <(int)> (Time in milliseconds for which the attenuation is kept unchanged after) ]\n"
"[ --el-transmit-thres <(float) [0-1]> (TO BE DOCUMENTED) ]\n"
#endif





static int time_count = 0; //
static char *old_ip = NULL; //

pthread_mutex_t og_ctl_mutex;
static int outgo_running = 1;




void * outgo_control(void *arg) {
	time_t lasttime;
	int temp = time_count;
	int exit_threshold = 0; 
	time(&lasttime);
	
	pthread_detach(pthread_self());
	
	while ( 1 ) {
		
		time_t nowtime;
		 
		time(&nowtime);
		
		if (nowtime - lasttime >= 12) {
			printf("%s:%d --> %d temp=%d ex_thres= %d\n",
				__FUNCTION__,__LINE__,time_count,temp,exit_threshold);
			if(time_count == temp)
				exit_threshold ++;
			else{
				exit_threshold = 0;
			}
			lasttime = nowtime;
			temp = time_count;
		}		

		if(exit_threshold > 4){
			pthread_mutex_lock(&og_ctl_mutex);
			outgo_running = 0;
			exit_threshold = 0;
			
			printf("%s:%d --> outgo_running= %d ex_thres= %d\n",
				__FUNCTION__,__LINE__,outgo_running,exit_threshold);
			pthread_mutex_unlock(&og_ctl_mutex);
		}

		sleep(2);
	}
	
	
	printf("control thread exit\n");
	pthread_exit(NULL);
	
}




typedef void(*ProcessHandler)(int);

class Timer{        
	protected:        
		struct sigaction  _act;        
		struct sigaction  _oldact;        
		struct itimerval  _tim_ticks;        
		void wait( long timeout_ms ){                
			struct timespec spec;                
			spec.tv_sec  = timeout_ms / 1000;                
			spec.tv_nsec = (timeout_ms % 1000) * 1000000;                
			nanosleep(&spec,NULL);        
		}
		
		
	public:        
		Timer(int sec,int usec){                
			_tim_ticks.it_value.tv_sec = sec;                
			_tim_ticks.it_value.tv_usec = usec;                
			_tim_ticks.it_interval.tv_sec = sec;                
			_tim_ticks.it_interval.tv_usec = usec;        
		}
		
		void setTimer(int sec,int usec){                
			_tim_ticks.it_value.tv_sec = sec;                
			_tim_ticks.it_value.tv_usec = usec;                
			_tim_ticks.it_interval.tv_sec = sec;                
			_tim_ticks.it_interval.tv_usec = usec;        
		} 

		void setHandler(ProcessHandler handler){                
			sigemptyset( &_act.sa_mask );                
			_act.sa_flags = 0;                
			_act.sa_handler = handler;        
		}        

		bool reset(){                
			int res = sigaction( SIGALRM, &_act, &_oldact );
			if ( res ) { 
				perror( "Fail to install handle: " );
				return false;   
			} 
			
			res = setitimer( ITIMER_REAL, &_tim_ticks, 0 );	
			//alarm(2);    
			if(res){    
				perror( "Fail to set timer: " );   
				sigaction( SIGALRM, &_oldact, 0 );    
				return false;              
			} 
				//               for ( ; ; ){        
				wait(50000); 
				//		}      
		}
		bool cancel(){
			setTimer(0,0);
			
			int res = setitimer( ITIMER_REAL, &_tim_ticks, 0 );	
			//alarm(2);    
			if(res){    
				perror( "Fail to set timer: " );   
				sigaction( SIGALRM, &_oldact, 0 );    
				return false;              
			}

			return true;
		}
		
};



#ifdef __TIMER_FOR_INCOMING__

pthread_mutex_t ring_mu;
static char ring_or_CID[50] = {0};
static int client_fd = 0;
Timer timer(2,0);


static void notify( int signum ){        
	assert( signum == SIGALRM );
	pthread_mutex_lock(&ring_mu);
	net_write(client_fd, ring_or_CID, strlen(ring_or_CID));
	net_write(client_fd, "\r\n", 2);
	printf("ring_or_CID = %s len of ring_or_CID=%d\n", ring_or_CID, strlen(ring_or_CID));
	
	timer.cancel();
	pthread_mutex_unlock(&ring_mu);
	return;
}



void * timer_for_incoming(void * arg) {       
	//Timer timer(5,0);
	timer.setTimer(2, 0);
	timer.setHandler(notify);    
	timer.reset();

	//timer.cancel();
	pthread_exit(NULL);
}



#endif

















static int flag_TOSON = 0;



MediastreamDatas* args_tele = NULL;
int handleClient(int new_fd, int fd_o, int cmdtype, char* arg_g, int arg_g_len){
	char buf[N];
	ssize_t nread;
	
	switch (cmdtype) {
		case (-2):
			
		case (-1):
			
		case EXIT:
			PSTNHandlePickMachine(fd_o);
			memset(buf, 0, N);
			nread = readFromUartTotal(fd_o, buf, N, 500);
			onHook(fd_o);
			memset(buf, 0, N);
			nread = readFromUartTotal(fd_o, buf, N, 500);

			return (-1);//will to close client socket
			break;				
		case OFFHOOK:
			
			
			PSTNHandlePickMachine(fd_o);
			memset(buf, 0, N);
			printf("memset\n");
			nread = readFromUartTotal(fd_o, buf, N, 500);
			printf("server OFFHOOK\n");
			
			
			printf("before dd sleep(2)\n");

			sleep(2);
			
			printf("after dd sleep(2)\n");

			mediastream_begin(args_tele);
			
			
			break;
		case FREEOFH:
			PSTNHandsFreePickMachine(fd_o);
			memset(buf, 0, N);
			printf("memset\n");
			nread = readFromUartTotal(fd_o, buf, N, 500);
			printf("server FREEOFH\n");
			
			mediastream_begin(args_tele);
			break;
		
		case ONHOOK:
			PSTNHandsFreePickMachine(fd_o);
			memset(buf, 0, N);
			printf("memset\n");
			nread = readFromUartTotal(fd_o, buf, N, 500);
			
			
			onHook(fd_o);//挂机
			memset(buf, 0, N);
			printf("memset\n");
			nread = readFromUartTotal(fd_o, buf, N, 500);

			cout << __FUNCTION__<< " " << __LINE__ << endl;

			
			mediastream_end(args_tele);

			break;				
		case DIALING:
			mediastream_begin(args_tele);
			
			
			dialUp(fd_o, arg_g, arg_g_len);
			memset(buf, 0, N);
			printf("memset\n");
			nread = readFromUartTotal(fd_o, buf, N, 500);
			break;
			
		case HEARTBEAT:
			cout << "HEARTBEAT" << endl;

			time_count ++;
			
			net_write(new_fd, "HEAD010OPTI_OK000", 17);
			net_write(new_fd, "\r\n", 2);
			break;
			
		case QUERY:
			queryRegister(fd_o);
			//memset(buf, 0, N);					
			//nread = readFromUartTotal(fd_o, buf, N, 500);
			break;
		case LOGIN:
			registration(fd_o);
			//memset(buf, 0, N);
			//nread = readFromUartTotal(fd_o, buf, N, 500);
			break;
		case LOG_OUT:
			cancelSubmachine(fd_o,arg_g);
			memset(buf, 0, N);
			nread = readFromUartTotal(fd_o, buf, N, 500);
			break;

		case LOGOUTALL:
			cancelSubmachineAll(fd_o);
			memset(buf, 0, N);
			nread = readFromUartTotal(fd_o, buf, N, 500);
			break;

		case TOSON:
			flag_TOSON = 1;
			turnToTheSonMachine(fd_o, arg_g);
			/*
			if(arg_g_len > 0){
				
				if(atoi(arg_g) == 1){
					talkbackToSubmachine1(fd_o);
					printf("talkbackToSubmachine1\n");		
				}
			}
			*/
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);

			//as.__end();
			mediastream_end(args_tele);

			break;
		case MA_RESPONSE:
			//must happened after PTHT=1
			//masterResponse(fd_o);
#if 0
			talkbackOffHook(fd_o);
			talkbackToHandle(fd_o);

			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);
#endif
#if 0
			talkbackToThreeparty(fd_o);

			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);
#endif
			printf("%s:%d\n", __FUNCTION__,__LINE__);
#if 1
			masterResponse(fd_o);
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);
#endif
#if 0
			onHook(fd_o);//挂机
			memset(buf, 0, N);
			printf("memset\n");
			nread = readFromUartTotal(fd_o, buf, N, 500);
#endif

#if 0
			talkbackOnHook(fd_o);
					//onHook(fd_o);
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);
#endif

			
			mediastream_begin(args_tele);
			break;
			
		case TB_ONHOOK:
			talkbackOnHook(fd_o);
			//onHook(fd_o);
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);

			cout << __FUNCTION__<< " "
				 << __LINE__ << endl;

			//as.__end();
			mediastream_end(args_tele);
			break;
		case TB_OFFHOOK:
			talkbackOffHook(fd_o);
			//talkbackToHandle(fd_o);
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);

			cout << __FUNCTION__<< " "
				 << __LINE__ << endl;

			//as._begin();
			mediastream_begin(args_tele);
			break;
		case TB_HANDSFREE:
			talkbackToHandsFree(fd_o);
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);
			break;
		case TB_HANDLE:
			talkbackToHandle(fd_o);
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);
			break;
		case TB_SUBMACH1:
			talkbackToSubmachine1(fd_o);
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);

			cout << __FUNCTION__<< " "
				 << __LINE__ << endl;

			//as._begin();
			mediastream_begin(args_tele);
			break;
		case TB_SUBMACH2:
			talkbackToSubmachine2(fd_o);
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);

			cout << __FUNCTION__<< " "
				 << __LINE__ << endl;

			//as._begin();
			mediastream_begin(args_tele);
			break;
		case VOLUME_HANDLE:
			volumeChangeHandle(fd_o);
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);
			break;
		case VOLUME_HANDSFREE:
			volumeChangeHandsFree(fd_o);
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);
			break;

		case VOLUME_HANDSFREE7:
			volumeChangeHandsFree7(fd_o);
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);
			break;
		case VOLUME_HANDSFREE6:
			volumeChangeHandsFree6(fd_o);
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);
			break;
		case VOLUME_HANDSFREE5:
			volumeChangeHandsFree5(fd_o);
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);
			break;
		case VOLUME_HANDSFREE4:
			volumeChangeHandsFree4(fd_o);
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);
			break;

		/*三方通话*/
		case TBTOTHREEPARTY:
			talkbackToThreeparty(fd_o);
			
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);
			break;
		case THREEPARTYTOTB:
			threepartyToTalkback(fd_o);
			
			memset(buf, 0, N);					
			nread = readFromUartTotal(fd_o, buf, N, 500);
			break;

		/*DTMF_SEND*/
		case DTMF_SEND:
			dialUpRespectively(fd_o, arg_g);
			
			//memset(buf, 0, N);					
			//nread = readFromUartTotal(fd_o, buf, N, 500);
			break;
			
		default:
			break;
			
		}//end switch (cmdtype) 


	return 0;

}


int handleSerialEvent(int new_fd, int fd_o){
	char recv_buf[1024];
	ssize_t nread;
	char send_buf[512];
	char buf[N];

	static int son_offhook = 1;
	static char sub_no_temp = 0;
	
	memset(recv_buf, 0, 1024);	
	nread = readFromUartTotal(fd_o, recv_buf, 50, 50);
	if(nread < 0){
		printf("read tele_no\n");
		return (-1);
	}


	if ( strncmp((const char *)(recv_buf+1), 
				"AT%PTIR=", 8) == 0 ){

		

		char *sub_no = recv_buf + 9;

		sub_no_temp = *sub_no;

#if 1
		memset(send_buf, 0, 512);
		snprintf(send_buf, 19, 
				"HEAD011TB_INCM001%c", *sub_no);
		if(son_offhook == 0){
			net_write(new_fd, send_buf, strlen(send_buf));
			net_write(new_fd, "\r\n", 2);
			printf("send_buf = %s len of send_buf=%d\n", send_buf, strlen(send_buf));
		}
		
#endif
#if 0
			memset(send_buf, 0, 512);
			snprintf(send_buf, 19, 
					"HEAD011STOMACH001%c", sub_no_temp);
		
			net_write(new_fd, send_buf, strlen(send_buf));
			net_write(new_fd, "\r\n", 2);

			cout << send_buf << ", " << __LINE__ << endl;
			sub_no_temp = 0;

#endif

#if 1
		if ( strncmp((const char *)(recv_buf+14), 
								"AT%PTHT=1", 9) == 0 ){
		
			memset(send_buf, 0, 512);
			snprintf(send_buf, 19, 
					"HEAD011STOMACH001%c", sub_no_temp);
		
			net_write(new_fd, send_buf, strlen(send_buf));
			net_write(new_fd, "\r\n", 2);

			cout << send_buf << ", " << __LINE__ << endl;
			sub_no_temp = 0;
		}

#endif

		
	}
	//AT%PTHT=1
	//pret = strstr(recv_buf, "AT%PTHT=1");
	//if(pret != NULL){

#if 1
	if ( strncmp((const char *)(recv_buf+1), 
								"AT%PTHT=1", 9) == 0 ){
		
			memset(send_buf, 0, 512);
			snprintf(send_buf, 19, 
					"HEAD011STOMACH001%c", sub_no_temp);
			int nwr;
			
			nwr = net_write(new_fd, send_buf, strlen(send_buf));
			if(nwr < 0)
				cout << "STOMACH error" << endl;

			nwr = net_write(new_fd, "\r\n", 2);
			if(nwr < 0)
				cout << "\\r\\n error" << endl;

			cout << send_buf << ", " << __LINE__ << endl;
			sub_no_temp = 0;
	}

#endif				

	/* --------------------------------------------------------------------------*/
	/**
	 * @Synopsis 普通来电时子机先摘机 
	 */
	/* ----------------------------------------------------------------------------*/
	if ( strncmp((const char *)(recv_buf+1), 
								"AT%PTHW=1", 9) == 0 ){

		son_offhook = 1;
		net_write(new_fd, "HEAD010SONOFFH000", 17);
		net_write(new_fd, "\r\n", 2);						
	}

	if ( strncmp((const char *)(recv_buf+1), 
								"AT%PTHS", 7) == 0 ){

		son_offhook = 0;
		net_write(new_fd, "HEAD010SONONHO000", 17);
		net_write(new_fd, "\r\n", 2);						
	}
	if ( strncmp((const char *)(recv_buf+1), 
								"AT%PTIC=0", 9) == 0 ){
		//pad to submachine , and submachine onhook the phone or time out

		if(flag_TOSON == 1){
			flag_TOSON = 0;
			PSTNHandlePickMachine(fd_o);
			memset(buf, 0, N);
			nread = readFromUartTotal(fd_o, buf, N, 500);
			onHook(fd_o);
			memset(buf, 0, N);
			nread = readFromUartTotal(fd_o, buf, N, 500);
		}
						
	}
	
	if ( strncmp((const char *)(recv_buf+1), 
								"AT%PTTT", 7) == 0 ){
		net_write(new_fd, "HEAD010RINGOFF000", 17);
		net_write(new_fd, "\r\n", 2);							
	}
	if ( strncmp((const char *)(recv_buf+1), 
								"AT%PTTE", 7) == 0 ){
		
		net_write(new_fd, "HEAD010RINGOFF000", 17);
		net_write(new_fd, "\r\n", 2);		
								
	}
	
	if ( strncmp((const char *)(recv_buf+1), 
								"AT%PTBU", 7) == 0 ){
		
		PSTNHandlePickMachine(fd_o);
		memset(buf, 0, N);
		nread = readFromUartTotal(fd_o, buf, N, 500);
		onHook(fd_o);
		memset(buf, 0, N);
		nread = readFromUartTotal(fd_o, buf, N, 500);

		mediastream_end(args_tele);

		net_write(new_fd, "HEAD010LINBUSY000", 17);
		net_write(new_fd, "\r\n", 2);

		
								
	}

	
	
	
	/* --------------------------------------------------------------------------*/
	/**
	 * @Synopsis  来电后PAD先摘机后转子机，子机接听
	 *
	 * 
	 */
	/* ----------------------------------------------------------------------------*/
	if ( strncmp((const char *)(recv_buf+1), 
								"AT%PTIC=1", 9) == 0 ){

		cout << "Son Machine accept" << endl;
		//write(new_fd, "HEAD010SONONHO000", 18);
		//write(new_fd, "\r\n", 2);
		son_offhook = 1;

		talkbackToThreeparty(fd_o);
		
		memset(buf, 0, N);					
		nread = readFromUartTotal(fd_o, buf, N, 500);
		usleep(1000);

		onHook(fd_o);//挂机
		memset(buf, 0, N);
		printf("memset\n");
		nread = readFromUartTotal(fd_o, buf, N, 500);

		cout << __FUNCTION__<< " " << __LINE__ << endl;

		
	}

	if ( strncmp((const char *)(recv_buf+1), 
				"AT%PTRS=1", 9) == 0 ) {
#ifdef __TIMER_FOR_INCOMING__
		pthread_t tid;
		pthread_create(&tid, NULL, timer_for_incoming, NULL);

		pthread_mutex_lock(&ring_mu);
		memset(ring_or_CID, 0, 50);
		snprintf(ring_or_CID, 27, 
				"HEAD019INCOMIN009ANONYMOUS");
		pthread_mutex_unlock(&ring_mu);

#endif
						
		net_write(new_fd, "HEAD09RINGON000", 15);
		net_write(new_fd, "\r\n", 2);



		printf("Ring incoming\n");
	} 

	if ( (strncmp((const char *)(recv_buf+14), 
								"AT%PTCI=", 8) == 0) ) {
								
#ifdef __TIMER_FOR_INCOMING__
		pthread_mutex_lock(&ring_mu);
		timer.cancel();
		pthread_mutex_unlock(&ring_mu);
#endif
		printf("into if\n");
		if(recv_buf[22] == 'E'){
			printf("Incoming error\n");
			return 0;
		}
					
					
		char tele_no[30];
		char *p = recv_buf + 22;//22;
		int i=0;
		while(*p != ','){
			tele_no[i] = *p;
			p++;
			i++;
		}
						
		tele_no[i] = '\0';
		printf("The incoming number is %s\n", tele_no);
	
		memset(send_buf, 0, 512);
		snprintf(send_buf, 18+strlen(tele_no), 
				"HEAD%03dINCOMIN%03d%s", 10+strlen(tele_no),strlen(tele_no) ,tele_no);
		//send_buf[21] = '\0';
			
		net_write(new_fd, send_buf, strlen(send_buf));
		net_write(new_fd, "\r\n", 2);
		printf("send_buf = %s len of send_buf=%d\n", send_buf, strlen(send_buf));
		
	
						
						
	}


	
	if ( (strncmp((const char *)(recv_buf+1), 
				"AT%PTCI=", 8) == 0 ) ) {

#ifdef __TIMER_FOR_INCOMING__
		pthread_mutex_lock(&ring_mu);
		timer.cancel();
		pthread_mutex_unlock(&ring_mu);
#endif
		
		printf("into if\n");
		if(recv_buf[9] == 'E'){
			printf("Incoming error too\n");
			return 0;
		}
	//	memset(send_buf, 0, 512);
	//	snprintf(send_buf, 21, 
	//			"HEAD014INCOMIN0048010");
		char tele_no[30];
		char *p = recv_buf + 9;//22;
		int i=0;
		while(*p != ','){
			tele_no[i] = *p;
			p++;
			i++;
		}
		
		tele_no[i] = '\0';
		printf("The incoming number is %s\n", tele_no);

#if 0
		pthread_mutex_lock(&ring_mu);
		memset(ring_or_CID, 0, 50);
		snprintf(ring_or_CID, 18+strlen(tele_no), 
				"HEAD%03dINCOMIN%03d%s", 10+strlen(tele_no),strlen(tele_no) ,tele_no);
		pthread_mutex_unlock(&ring_mu);
#endif

#if 1					

		memset(send_buf, 0, 512);
		snprintf(send_buf, 18+strlen(tele_no), 
				"HEAD%03dINCOMIN%03d%s", 10+strlen(tele_no),strlen(tele_no) ,tele_no);
		//send_buf[21] = '\0';
	
		net_write(new_fd, send_buf, strlen(send_buf));
		net_write(new_fd, "\r\n", 2);
		printf("send_buf = %s len of send_buf=%d\n", send_buf, strlen(send_buf));

#endif
		
		
	}

	
	if ( strncmp((const char *)(recv_buf+1), 
				"AT%PTRS=0", 9) == 0 ) {
#ifdef __TIMER_FOR_INCOMING__
		net_write(new_fd, "HEAD010BELLEND000", 17);
#endif
		net_write(new_fd, "HEAD010RINGOFF000", 17);

		net_write(new_fd, "\r\n", 2);				

		
		printf("Ring incoming off\n");
	}


	//register relative -- QUERY
	if ( strncmp((const char *)(recv_buf+1), 
				"AT%PTRV=", 8) == 0 ) {
		char subma[4] = {0};
		char *p = recv_buf + 9;
		while(*p != '\n'){
			if(*p == '1')
				subma[0] = '1';
			else
				subma[0] = '0';
			if(*p == '2')
				subma[1] = '1';
			else
				subma[1] = '0';
			if(*p == '3')
				subma[2] = '1';
			else
				subma[2] = '0';
			p++	;					
		}

		memset(send_buf, 0, 512);
		snprintf(send_buf, 21, 
				"HEAD013QUERYRE003%s", subma);
		
	
		net_write(new_fd, send_buf, strlen(send_buf));
		net_write(new_fd, "\r\n", 2);
		printf("send_buf = %s len of send_buf=%d\n", send_buf, strlen(send_buf));

		
		
	}

	//register relative -- LOGIN
	if ( strncmp((const char *)(recv_buf+9), 
				"AT%PTRG=", 8) == 0 ) {
		char *p = recv_buf + 17;

		memset(send_buf, 0, 512);
		

		
		if(*p == '0')
			snprintf(send_buf, 18, 
				"HEAD010LOGFAIL000");
			
		if(*p == '1')
			snprintf(send_buf, 18, 
				"HEAD010LOGINOK000");
			
		if(*p == '2')
			snprintf(send_buf, 18, 
				"HEAD010LOGFULL000");
			

		net_write(new_fd, send_buf, strlen(send_buf));
		net_write(new_fd, "\r\n", 2);
		printf("send_buf = %s len of send_buf=%d\n", send_buf, strlen(send_buf));

	}



	return 0;

}







// 去电线程 

/* --------------------------------------------------------------------------*/
/**
 * @brief  
 *
 * @Param arg_out
 *
 * @Returns   
 */
/* ----------------------------------------------------------------------------*/
void *outgoing(void *arg_out)
{
	int new_fd;	
	FDS *fdss = (FDS *)arg_out;
	
	
	int fd_o = fdss->serial_fd;//serial port
	new_fd = fdss->conn_fd;//client
#ifdef __TIMER_FOR_INCOMING__
	client_fd = new_fd;
#endif
	
	int payload_out = 0;
	payload_out = fdss->payload;
	
	int cmdtype;
	char arg_g[20];
	int arg_g_len;
	//MediastreamDatas* args_tele = NULL;
	
	remote_ip = fdss->remote_ip_addr;//REMOTE_IP;
	 
	
	printf("f:%s l:%d remote_ip_addr=%s\n", __FUNCTION__,__LINE__,remote_ip);

	
	argv_tele[4] = (char *)malloc(50 * sizeof(char));
	memset(argv_tele[4], 0, sizeof(argv_tele[4]));
	sprintf(argv_tele[4], "%s:%d", remote_ip, remote_port);

	printf("f:%s l:%d re_ip:re_port=%s\n", __FUNCTION__,__LINE__,argv_tele[4]);

	argv_tele[6] = (char *)malloc(10 * sizeof(char));
	memset(argv_tele[6], 0, 10);
	sprintf(argv_tele[6], "%d", payload_out);

	printf("f:%s l:%d payload=%s\n", __FUNCTION__,__LINE__,argv_tele[6]);
	
	pthread_detach(pthread_self());

	

	
	//init	
	args_tele= mediastream_init(argc_tele, argv_tele);
	if (args_tele == NULL) return (void *)(-1);
	
#if 1
	if(argv_tele[4] != NULL){
		free(argv_tele[4]);
		argv_tele[4] = NULL;
	}
	if(argv_tele[6] != NULL){
		free(argv_tele[6]);
		argv_tele[6] = NULL;
	}
	printf("free two argvs\n");
#endif

	

	printf("new_fd=%d ,fd_o=%d\n", new_fd, fd_o);
	printf("waiting for messages from client %d\n", new_fd);
	fd_set fdR;
	
	struct timeval tv;
	

	

	while(outgo_running)
	{
		//usleep(10000);
		
		FD_ZERO(&fdR);
		FD_SET(new_fd, &fdR);
		FD_SET(fd_o, &fdR);
		
		tv.tv_sec = 0;
		tv.tv_usec = 30 * 1000;
		
		//printf("tv_sec = %d  tv_usec = %d\n", tv.tv_sec,tv.tv_usec);
		
		switch( select(new_fd+1, &fdR, NULL, NULL, &tv) ) {
		case -1:
			perror("select error");
			return (void *)(-1);
		case 0:
			//printf("select timeout\n");
			//sched_yield();
			break;
		default:
#if 1
			if ( FD_ISSET(fd_o, &fdR) ) {
				printf("fd_o is ok\n");

				handleSerialEvent(new_fd, fd_o);
			}
#endif
			if ( FD_ISSET(new_fd, &fdR) ) {

				cmdtype = parseClient(new_fd, arg_g, &arg_g_len);
				int ret;
				ret = handleClient(new_fd,fd_o,cmdtype,arg_g,arg_g_len);
				if(ret == -1) goto cli_exit;

			}//end if
			break;
		}//end switch (select)

		
		//printf("waiting for messages from client %d\n", new_fd);
			
	}// end while

cli_exit:
	
	printf("A client exit\n");
	char buf[N];
	ssize_t nread;
	PSTNHandlePickMachine(fd_o);
	memset(buf, 0, N);
	nread = readFromUartTotal(fd_o, buf, N, 500);
	onHook(fd_o);
	memset(buf, 0, N);
	nread = readFromUartTotal(fd_o, buf, N, 500);
	
	close(new_fd);
	mediastream_end(args_tele);
	mediastream_uninit(args_tele);

	old_ip = NULL;

	pthread_exit(NULL);
}


int listenOnServerSocket(int port){
	int listen_fd;
	int on;
	int ret;
	struct sockaddr_in srv_addr;
	
	listen_fd = socket(PF_INET, SOCK_STREAM, 0);
	if(listen_fd < 0) {
		perror("cannot create listening socket");
		exit (-1);
	}
	printf("socket success\n");
	/* Enable address reuse */
	on = 1;
	/* Allow connections to port 8080 from any available interface */
	ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	//填充关于服务器的套节字信息
	memset(&srv_addr, 0, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	srv_addr.sin_port = htons(port);
	//将服务器和套节字绑定
	ret = bind(listen_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	if(ret == -1){
		perror("cannot bind server socket");
		close(listen_fd);
		exit (-1);
	}
	printf("bind success\n");

	//监听指定端口，连接10个客户端
	ret = listen(listen_fd, BACK_LOG);
	printf("BACK_LOG=%d\n", BACK_LOG);
	if(ret == -1) {
		perror("cannot listen the client connect request");
		close(listen_fd);
		exit (-1);
	}
	printf("listen success\n");

	return listen_fd;
	
}

int pstnInit(void){
	int fd;
	ssize_t nread;
	unsigned char r_buf_l[N];
	
	fd = openSerial();
	if(fd < 0){
		exit (-1);
	}
	printf("serial open = %d\n", fd);
	serialInit(fd);// serial initialization
	
	connectIntoIdle(fd); //查询并连接
	memset(r_buf_l, 0, N);
	nread = readFromUartTotal(fd, r_buf_l, 45, 500);


	volumeMICGain(fd);
	memset(r_buf_l, 0, N);
	nread = readFromUartTotal(fd, r_buf_l, 45, 500);
	
	//volumeChangeHandle7(fd);
	volumeChangeHandle(fd);
	memset(r_buf_l, 0, N);
	nread = readFromUartTotal(fd, r_buf_l, 45, 500);
	
	//volumeChangeHandsFree7(fd);
	volumeChangeHandsFree(fd);
	memset(r_buf_l, 0, N);
	nread = readFromUartTotal(fd, r_buf_l, 45, 500);

	return fd;

}

int main(int argc,char *argv[])
{
	//for server
	int listen_fd;
	int port;

	//for client
	int com_fd;	
	socklen_t len_clt;
	struct sockaddr_in clt_addr;
	int payload = 0;
	int fd;

	//for client thread
	FDS *fds;
	pthread_t outgoing_tid;

	//for client control thread
	pthread_t outgo_ctrl_tid;
	//服务器端运行时要给出端口信息，该端口为监听端口
	if(argc<3){
		printf("Usage:%s port payload_no\n",argv[0]);
		return 1;
	}
	printf("\nPSTNSERV current version is : %s\n", CURRENT_VERSION_FOR_PSTN);
	printf("Switch to git dir\n");
	//获得输入的端口
	port = atoi(argv[1]);
	
	
	if(argc > 2)
		payload = atoi(argv[2]);
	
	pthread_mutex_init(&og_ctl_mutex, NULL);
	pthread_mutex_init(&mutex, NULL);

#ifdef __TIMER_FOR_INCOMING__
	pthread_mutex_init(&ring_mu, NULL);
#endif
	fds = (FDS *)malloc(sizeof(FDS));
	
	
	fd = pstnInit();

	listen_fd = listenOnServerSocket(port);

	pthread_create(&outgo_ctrl_tid, NULL, outgo_control, NULL);

	char *new_ip = NULL;
	
	while(1){
		usleep(500000);
		if(old_ip == NULL){
			
		
		len_clt = sizeof(clt_addr);
		printf("before accept\n");
		
		com_fd = accept(listen_fd, (struct sockaddr *)&clt_addr, &len_clt);
		printf("accept\n");
		if(com_fd < 0)
		{
			if(errno == EINTR)
			{
				perror("EINTR Error");
				continue;
			}
			else
			{
				perror("cannot accept client connect request");
				close(listen_fd);
				return 1;
			}
		}
		printf("com_fd=%d\n", com_fd);//打印建立连接的客户端产生的套节字

#if 0

////KeepAlive实现，单位秒
//下面代码要求有ACE,如果没有包含ACE,则请把用到的ACE函数改成linux相应的接口
		int keepAlive = 1;//设定KeepAlive
		int keepIdle = 5;//开始首次KeepAlive探测前的TCP空闭时间
		int keepInterval = 5;//两次KeepAlive探测间的时间间隔
		int keepCount = 3;//判定断开前的KeepAlive探测次数
		if(setsockopt(com_fd,SOL_SOCKET,SO_KEEPALIVE,(void*)&keepAlive,sizeof(keepAlive)) == -1)
		{
   			 printf("setsockopt SO_KEEPALIVE error!\n");
		}

		if(setsockopt(com_fd,SOL_TCP,TCP_KEEPIDLE,(void *)&keepIdle,sizeof(keepIdle)) == -1)
		{
  		  	
   		 	cout << "setsockopt TCP_KEEPIDLE error!" << endl;
		}

		if(setsockopt(com_fd,SOL_TCP,TCP_KEEPINTVL,(void *)&keepInterval,sizeof(keepInterval)) == -1)
		{
  		 	 cout << "setsockopt TCP_KEEPINTVL error!" << endl;
		}

		if(setsockopt(com_fd,SOL_TCP,TCP_KEEPCNT,(void *)&keepCount,sizeof(keepCount)) == -1)
		{
    		cout << "setsockopt TCP_KEEPCNT error!" << endl;
		}
		
#endif


		
		struct in_addr ia = clt_addr.sin_addr; //(int)ip
		new_ip = inet_ntoa(ia);
		if(strcmp(new_ip, PAD_IP) != 0){
			close(com_fd);
			continue;
		}

		if(old_ip == NULL){
			printf("old_ip\n");

			memset(fds->remote_ip_addr, 0, 30);
			memcpy(fds->remote_ip_addr, new_ip, strlen(new_ip)+1);
			printf("f:%s l:%d remote_ip_addr=%s\n", __FUNCTION__,__LINE__,fds->remote_ip_addr);

		
		
			
			old_ip = fds->remote_ip_addr;			
		}
		 
		
		printf("old_ip=%s new_ip=%s\n",old_ip,new_ip);



		fds->conn_fd = com_fd;
		fds->serial_fd = fd; 
			//fds->file = mfile;
		fds->payload = payload;
		if((strcmp(old_ip, new_ip)) == 0 && old_ip != NULL){
			printf("enter client handler\n");
			
			pthread_mutex_lock(&og_ctl_mutex);
			outgo_running = 1;
			pthread_mutex_unlock(&og_ctl_mutex);

			if((pthread_create(&outgoing_tid, NULL, outgoing, (void *)fds)) == -1)
			{
				perror("pthread_create outgoing error");
				close(listen_fd);
				close(com_fd);
				close(fd);
				return 1;
			}
		}

		}

	}//end while

	free(fds);
	return 0;
}
