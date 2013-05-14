/*
 * =====================================================================================
 *
 *       Filename:  phone_proxy.h
 *
 *    Description:  phone proxy for PAD or Handset
 *
 *        Version:  1.0
 *        Created:  05/03/2013 04:07:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (chen.chunsheng badwtg1111@hotmail.com), 
 *   Organization:  handaer
 *
 * =====================================================================================
 */
#ifndef _PHONE_PROXY_H_
#define _PHONE_PROXY_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/epoll.h>

#include "phone_control_service.h"
#include "phone_timer.h"
#include "phone_mediastream.h"
#include "thread_wrapper.h"

using namespace webrtc;

namespace handaer{

extern ssize_t readline(int fd, void *vptr, size_t maxlen);



class PhoneProxy{
	public:
		enum {
			PASSWD_LEN = 16,
			CLIENT_NUM = 4,
			BACK_LOG = 10,
			SERVER_PORT = 63290,
			MAX_NUM_LEN_ = 64,
			MAX_LEN_PCLI = 512,
			MAX_EVENTS = 5,
			EPOLL_TIMEOUT_MS = 30,
			TIMER_SEC = 10,
		};
		
		enum PstnCommand {
			UNDEFINED = -1,
			DEFAULT,
			/*client heartbeat*/
			HEARTBEAT,
			
			/*Pstn control event*/
			DIALING,	
			OFFHOOK,			
			ONHOOK,		
			DTMF_SEND,
			FLASH,
			MUTE,

			
			//about registration
			QUERY,
			LOGIN,
			LOG_OUT,			
			LOGOUTALL,

			//switch function
			SWITCHTOSONMACHINE,
			SWITCHOFFHOOK,
			SWITCHONHOOK,
			SWITCHBACK,

			//talkback function
			TALKBACKDIALING,
			TALKBACKOFFHOOK,
			TALKBACKONHOOK,
			
		};  
		typedef enum PstnCommand PstnCmdEnum;

		typedef enum{
			//Pstn incoming event
			DEFAULT_INCOMING,
			RINGON,
			RINGOFF,
			INCOMING_NUM,
			BUSYLINE,

			
		}PstnCmdIncomingEnum;

		typedef int (*timer_process_cbfn_t)(void *);

		typedef struct _timer_info {
			
			int in_use;	 // on or off  
			int interval;
			int elapse;    // 0~interval  
			
			timer_process_cbfn_t  timer_func_cb;
			void * timer_func_cb_data;			

		}timer_info_t;
		
		typedef struct {
			int fd;
			char head[6]; //head
			char id; // client_id
			int length; //length
			PstnCmdEnum cmd; //cmd
			int arglen; //arg_len
			char arg[MAX_NUM_LEN_+1]; //arg
			//short crc16;
		}cli_request_t; //client cmd message

		typedef struct {
			char id;
			char password[PASSWD_LEN];
			
			int client_fd; // PAD(0), Handset(1~3)
			char client_ip[PASSWD_LEN];

			timer_info_t * ti;			
			int timer_counter;
			int exit_threshold;
			
		}cli_info_t;
		
		PhoneProxy();
		~PhoneProxy();

		int listenOnServerSocket(int port);
		int accepting_loop(bool yes_no);
		int my_accept(struct sockaddr *addr, socklen_t *addrlen);

		PstnCmdEnum getCmdtypeFromString(char *cmd_str);
		int netWrite(int fd,const void *buffer,int length);
		int netRead(int fd,void *buffer,int length);

		ssize_t netReadLine(int fd,void *buffer,size_t maxlen);

		int parseClient(cli_info_t *ci_);
		int handleClient(cli_info_t *ci_);

		int parsePhoneControlServiceEvent(); 		
		int handlePhoneControlServiceEvent();


	
		
	public:
	    virtual int32_t startPhoneProxy();
	    virtual int32_t stopPhoneProxy();
	    virtual bool phoneProxyisRunning() const;

		virtual int32_t startHeartBeating();
	    virtual int32_t stopHeartBeating();
	    virtual bool heartBeatingisRunning() const;
		

		int setClientTimer(cli_info_t* cli_info, int interval, 
							  timer_process_cbfn_t timer_proc, void *arg);
		static int deleteClientTimer(cli_info_t* cli_info);

		bool phoneProxyInit(int port);
		bool phoneProxyExit();
		
	private:
		static bool phoneProxyThreadFunc(void*);		
		bool phoneProxyThreadProcess();

		static bool heartBeatingThreadFunc(void*);		
		bool heartBeatingThreadProcess();


		int max(int a, int b) { return (a > b ? a : b); }
		
		static void notify( int signum );
		static int recycleClient(void *arg);
		static bool resetTimerInfo();
	private:
		
		ThreadWrapper* _ptrThreadPhoneProxy;
		uint32_t _phoneProxyThreadId;	
		bool _phoneProxyRunning;
		
		ThreadWrapper* _ptrThreadHeartBeating;
		uint32_t _heartBeatingThreadId;	
		bool _heartBeatingisRunning;

		static timer_info_t timer_info_g[CLIENT_NUM];
	private:
		PhoneControlService *pcs;
		PhoneTimer *timer;
		MediastreamDatas* _ms_datas;

		int server_port;
		int payload_type;
		int serv_listen_sockfd;
		
		int phone_proxy_fd[2]; // 0 -- self, 1 -- PhoneControlService
		
		cli_info_t ci[CLIENT_NUM];	

		cli_request_t _cli_req;

		PstnCmdIncomingEnum _phone_control_service_event;
		
		
		int epollfd;
};

}

#endif
