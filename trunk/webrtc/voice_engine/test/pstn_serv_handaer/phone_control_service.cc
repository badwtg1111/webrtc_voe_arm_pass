/*
 * =====================================================================================
 *
 *       Filename:  phone_control_service.cc
 *
 *    Description:  in charge of phone control process 
 *
 *        Version:  1.0
 *        Created:  05/03/2013 04:07:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (chen.chunsheng badwtg1111@hotmail.com), 
 *   Organization:  handaer
 *
 * =====================================================================================
 */
#include "thread_wrapper.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "phone_control_service.h"

using namespace std;
using namespace webrtc;

namespace handaer{
int PhoneControlService::phone_proxy_fd = -1;

PhoneControlService::PhoneControlService()
	:PhoneControlBase(),	 
	 _ptrThreadPhoneControlService(NULL),
	 ThreadPhoneControlServiceId(0),	
	 phoneControlServiceRunning(false),
	 
	 event_type_serial(DEFAULT),
	 event_type_client(DEFAULT),
	 dtmf(0),
	 mute_ok(false),
	 incoming_son_number(-1),
	 going_son_number(-1){

	FD_ZERO(&fdR);
	tv.tv_sec = 0;
	tv.tv_usec = TIMEOUT_US;
	 
	memset(incoming_number, 0, MAX_NUM_LEN);
	memset(going_number, 0, MAX_NUM_LEN);



	phoneControlServiceInit();

	StartPhoneControlService();
	 

}

PhoneControlService::~PhoneControlService(){
	StopPhoneControlService();
	
	phoneControlServiceExit();
}

bool PhoneControlService::phoneControlServiceInit(){
	openDevice();
	serialConfig(B9600);
	connectIntoIdle();

	return true;
}

bool PhoneControlService::phoneControlServiceExit(){
	closeDevice();
	return true;
}


int PhoneControlService::dialUp(const  char *num, int num_len){
		
	char dial[MAX_NUM_LEN] = {0};
	memcpy(dial, "AT%TPDN=", 9);
	strncat(dial, num, num_len);
	writeDevice(dial,num_len+8);

	char buff[SERIAL_BUF_LEN] = {0};
	readAll(buff, SERIAL_BUF_LEN);

	return 0;
}
int PhoneControlService::offHook(void){
	
	writeDevice("AT%TPCA=1,1,1", 13);
	writeDevice("AT%TPSM=1", 9);

	char buff[SERIAL_BUF_LEN] = {0};
	readAll(buff, SERIAL_BUF_LEN);

	return 0;
}
int PhoneControlService::onHook(void){
	writeDevice("AT%TPCA=0,0,0", 13);
	
	char buff[SERIAL_BUF_LEN] = {0};
	readAll(buff, SERIAL_BUF_LEN);

	return 0;
}
int PhoneControlService::sendDtmf(const  char dtmf){

	char key[16] = {0};
	memcpy(key, "AT%TPKB=", 9);
	strncat(key, &dtmf, 1);
	writeDevice(key, 9);

	char buff[SERIAL_BUF_LEN] = {0};
	readAll(buff, SERIAL_BUF_LEN);


	return 0;
}
int PhoneControlService::flash(void){
	writeDevice("AT%TPLF", 7);

	char buff[SERIAL_BUF_LEN] = {0};
	readAll(buff, SERIAL_BUF_LEN);


	return 0;
}
int PhoneControlService::mute(bool yes_no){

	if(yes_no)
		writeDevice("AT%TPCA=1,1,0", 13); //chl,spk,mic  mute
	else
		writeDevice("AT%TPCA=1,1,1", 13); //unmute

	char buff[SERIAL_BUF_LEN] = {0};
	readAll(buff, SERIAL_BUF_LEN);


	return 0;
}

int PhoneControlService::connectIntoIdle(void){
	
	writeDevice("AT%TPQV=?", 9); 
	writeDevice("AT%TPLM=1", 9);

	char buff[SERIAL_BUF_LEN] = {0};
	readAll(buff, SERIAL_BUF_LEN);
	

	return 0;
}

ssize_t PhoneControlService::netReadLine(int fd,void *buffer,size_t maxlen){
	ssize_t 	n;
	if ( (n = readline(fd, buffer, maxlen)) < 0)
		perror("readline error: ");
	return(n);	
}


int PhoneControlService::parsePhoneProxyEvent(char* msg, int msg_len_wanted){
	ssize_t nread;
	char will_read[64] = {0};
	nread = netReadLine(phone_proxy_fd, will_read, 64);
	
	if(strcmp(will_read, "DIALING\n") == 0){
		event_type_client = DIALING;
	}
	if(strcmp(will_read, "OFFHOOK\n") == 0){
		event_type_client = OFFHOOK;
	}
	if(strcmp(will_read, "ONHOOK\n") == 0){
		event_type_client = ONHOOK;
	}		
	if(strcmp(will_read, "DTMFSEND\n") == 0){
		event_type_client = DTMFSEND;
	}
	if(strcmp(will_read, "FLASH\n") == 0){
		event_type_client = FLASH;
	}		
	if(strcmp(will_read, "MUTE\n") == 0){
		event_type_client = MUTE;
	}
	
	return 0;
}
int PhoneControlService::handlePhoneProxyEvent(void *msg, int msg_len){

	switch(event_type_client){
		case DIALING:
			dialUp(going_number, strlen(going_number));
			break;
		case OFFHOOK:
			offHook();
			break;
		case ONHOOK:
			onHook();
			break;
		case DTMFSEND:
			sendDtmf(dtmf);
			break;
		case FLASH:
			flash();
			break;
		case MUTE:
			mute(mute_ok);
			break;
		default:
			break;
	}
	
	return 0;
}



int PhoneControlService::parseSerialEvent(char* msg, int msg_len_wanted){

	char recv_buf[SERIAL_BUF_LEN];
	ssize_t nread;	 
	
	memset(recv_buf, 0, SERIAL_BUF_LEN);	
	nread = readLine(recv_buf, msg_len_wanted);
	if(nread < 0){
		cout << "readLine error" << endl;
		return (-1);
	}

	
	if ( strncmp((const char *)(recv_buf+1), 
								"AT%PTBU", 7) == 0 ){
		event_type_serial = BUSYLINE;
		return 0;
	}
	if ( strncmp((const char *)(recv_buf+1), 
				"AT%PTRS=1", 9) == 0 ) {
		event_type_serial = RINGON;
		return 0;
	}
	if ( strncmp((const char *)(recv_buf+1), 
				"AT%PTRS=0", 9) == 0 ) {
		event_type_serial = RINGOFF;
		return 0;
	}	
	if ( (strncmp((const char *)(recv_buf+1), 
				"AT%PTCI=", 8) == 0 ) ) {

		event_type_serial = INCOMING_NUM;
		
		if(recv_buf[9] == 'E'){
			cout << "Incoming E" << endl;
			return 0;
		}
 		
		char *p = recv_buf + 9;
		int i=0;
		while(*p != ','){
			msg[i] = *p;
			p++;
			i++;
		}
		
		msg[i] = '\0';
		memset(incoming_number, 0, MAX_NUM_LEN);
		memcpy(incoming_number, msg, strlen(msg)+1);
		cout << "The incoming number is " << msg
			 << " or " << incoming_number
			 << "  tele_no_len = " << i << endl;
		return i;		
	}
	
	return 0;
}
int PhoneControlService::handleSerialEvent(void *msg, int msg_len){
	switch(event_type_serial){
		case RINGON:
			returnRingOn(msg, msg_len);
			break;
		case RINGOFF:
			returnRingOff(msg, msg_len);
			break;
		case BUSYLINE:
			returnBusyLine(msg, msg_len);
			break;
		case INCOMING_NUM:
			cout << __FUNCTION__ << " " << __LINE__ 
				 << " INCOMING_NUM " << endl;
			returnIncomingNumber(msg, msg_len);
			break;
		default:
			break;
	}
	
	return 0;
}
int PhoneControlService::returnRingOn(void *msg, int msg_len){
	write(phone_proxy_fd, "RINGON\n", 7);
	return 0;
}
int PhoneControlService::returnRingOff(void *msg, int msg_len){
	write(phone_proxy_fd, "RINGOFF\n", 8);
	return 0;
}
int PhoneControlService::returnIncomingNumber(void *tel_num, int tel_num_len){
	write(phone_proxy_fd, "INCOMING\n", 9);
	return 0;
}
int PhoneControlService::returnBusyLine(void *msg, int msg_len){
	write(phone_proxy_fd, "BUSYLINE\n", 9);
	return 0;
}


bool PhoneControlService::setPhoneProxyFd(int fd){
	phone_proxy_fd = fd;

	return true;
}

bool PhoneControlService::getIncomingNumber(char *num, int *num_len){
	*num_len = strlen(incoming_number);
	memcpy(num, incoming_number, strlen(incoming_number)+1);
	return true;
}
bool PhoneControlService::setGoingNumber(char *num, int num_len){
	memcpy(going_number, num, num_len+1);
	return true;	
}
bool PhoneControlService::setDtmfNumber(unsigned char num){
	dtmf = num;
	return true;
}

bool PhoneControlService::setMute(bool yes_no){
	mute_ok = yes_no;
	return true;
}





int32_t PhoneControlService::StartPhoneControlService(){
    if (phoneControlServiceRunning) {
        return 0;
    }

    phoneControlServiceRunning = true;

	// PhoneControlServiceRunning
    const char* threadName = "handaer_phone_control_service_thread";
    _ptrThreadPhoneControlService = ThreadWrapper::CreateThread(PhoneControlServiceThreadFunc,
                                                this,
                                                kRealtimePriority,
                                                threadName);
    if (_ptrThreadPhoneControlService == NULL) {
        cout << "failed to create the phone control service thread" << endl;
        phoneControlServiceRunning = false;
        return -1;
    }

    unsigned int threadID(0);
    if (!_ptrThreadPhoneControlService->Start(threadID)) {
        cout << "failed to start the phone control service thread" << endl;
        phoneControlServiceRunning = false;
        delete _ptrThreadPhoneControlService;
        _ptrThreadPhoneControlService = NULL;
        return -1;
    }
    ThreadPhoneControlServiceId = threadID;


    return 0;	

}

int32_t PhoneControlService::StopPhoneControlService(){

	phoneControlServiceRunning = false;

    if ( _ptrThreadPhoneControlService 
			&& !_ptrThreadPhoneControlService->Stop() ) {
        cout << "failed to stop the phone control service thread" << endl;
        return -1;
    } else {
        delete _ptrThreadPhoneControlService;
        _ptrThreadPhoneControlService = NULL;
    }
	
    return 0;
}

bool PhoneControlService::PhoneControlServiceRunning() const{
	return (phoneControlServiceRunning);
}


bool PhoneControlService::PhoneControlServiceThreadFunc(void* pThis){
	
	return (static_cast<PhoneControlService*>(pThis)->PhoneControlServiceThreadProcess());
}

bool PhoneControlService::resetFdsetAndTimeout(){
	FD_ZERO(&fdR);
	FD_SET(serial_fd, &fdR);
	FD_SET(phone_proxy_fd, &fdR);
	
	tv.tv_sec = 0;
	tv.tv_usec = TIMEOUT_US;

	return true;
}


bool PhoneControlService::PhoneControlServiceThreadProcess(){
	resetFdsetAndTimeout();	
	
	switch( select(max(serial_fd, phone_proxy_fd)+1, &fdR, NULL, NULL, &tv) ) {
	case -1:
		perror("select error");
		return (false);
	case 0:	//timeout			
		break;
	default:
		if ( FD_ISSET(serial_fd, &fdR) ) {
			cout << "serial event happened" << endl;			
			char mmsg[MAX_NUM_LEN];
			
			parseSerialEvent(mmsg, SERIAL_BUF_LEN);
			handleSerialEvent(NULL, 0);
		}
		
		if ( FD_ISSET(phone_proxy_fd, &fdR) ) {
			cout << "client request event happened" << endl;
			
			parsePhoneProxyEvent(NULL, 0);
			handlePhoneProxyEvent(NULL, 0);			
		}
		break;
	}//end switch (select)
			
	return true;	
}



}

