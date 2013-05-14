/*
 * =====================================================================================
 *
 *       Filename:  phone_control_base.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/03/2013 04:07:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

#include <iostream>
#include "phone_control_base.h"

using namespace std;

namespace handaer{
	

PhoneControlBase::PhoneControlBase()
	:serial_fd(-1),
	 msg(NULL),
	 msg_len(0),
	 time_out_ms(500){
	cout << "sizeof device_name = " << sizeof(device_name) << endl;
	memset(device_name, 0, sizeof(device_name));	
	memcpy(device_name, "/dev/ttySAC3", 13);

}
PhoneControlBase::~PhoneControlBase(){
}

int PhoneControlBase::setReadTimeOutMs(int time_out_ms_){
	time_out_ms = time_out_ms_;
	return 0;
}
int PhoneControlBase::setDeviceName(char *dev_name){
	memset(device_name, 0, sizeof(device_name));	
	memcpy(device_name, dev_name, strlen(dev_name)+1 ); 
	
	return 0;
}
int PhoneControlBase::openDevice(void){
	if ( serial_fd == -1 ){
		serial_fd = open(device_name, O_RDWR | O_NOCTTY | O_NDELAY);
		if (serial_fd == -1){
			perror("Unable to open /dev/ttySACx ... ");
		}
		else{
			cout << "open ttySACx success....." << endl;
		}
	}
		//fcntl(fd, F_SETFL, 0);/*»Ö¸´´®¿ÚÎª×èÈû×´Ì¬*/

	return 0;
	
}
int PhoneControlBase::serialConfig(speed_t baudrate){
	struct termios options;
	tcgetattr(serial_fd, &options);
	options.c_cflag  |= ( CLOCAL | CREAD );//Ignore modem control lines ,Enable receiver
	options.c_cflag &= ~CSIZE; //Character size mask
	options.c_cflag &= ~CRTSCTS;//Enable  RTS/CTS  (hardware)  flow  control
	options.c_cflag |= CS8;// 8bit
	options.c_cflag &= ~CSTOPB;//Set two stop bits, rather than one
	options.c_iflag |= IGNPAR;//Ignore framing errors and parity errors
	options.c_iflag &= ~(ICRNL |IXON);//Enable XON/XOFF flow control on output
	//Translate  carriage  return to newline on input (unless IGNCR is set).

	options.c_oflag = 0;
	options.c_lflag = 0;

	cfsetispeed(&options, baudrate /*B9600*/);
	cfsetospeed(&options, baudrate /*B9600*/);
	tcsetattr(serial_fd,TCSANOW,&options);//the change occurs immediately
	
	cout << "serial config finished\n" << endl;
	return 0;
}
int PhoneControlBase::closeDevice(void){
	if(serial_fd == -1)
		return 0;
	else
		close(serial_fd);

	return 0;
}

ssize_t PhoneControlBase::readOnce(char *buf, size_t len){
		int nfds;
		fd_set readfds;
		struct timeval tv;
		ssize_t nread;
		//int i = 0;
	
		tv.tv_sec = 0;
		tv.tv_usec = time_out_ms * 1000;
		FD_ZERO(&readfds);
		FD_SET(serial_fd, &readfds);
		nfds = select(serial_fd+1, &readfds, NULL, NULL, &tv);
		if (nfds < 0) {
			perror("select error");
			return(-1);
		} else if (nfds == 0) {
			errno = ETIME;
			perror("read uart timeout");
			return (-ETIME);
		} else {
			cout << "The uart has some data..." << endl;
			if (FD_ISSET(serial_fd, &readfds)) {	
				nread = read(serial_fd, buf, len);
#if 0			
				printf("read:\n");
				for(i = 0;i < nread; i++)
					printf("%02x ", ((unsigned char *)buf)[i]);
				printf("\n");
	
				for(i = 0;i < nread; i++)
				{
					if(((char *)buf)[i] == '\r')
						continue;
					printf("%c", ((unsigned char *)buf)[i]);
				}
#endif
			}
		}
		return nread;

}
ssize_t PhoneControlBase::readAll(char *buf, size_t len){
	char *buf_temp;
	unsigned int i;	
	size_t nleft;
	ssize_t nread;
	nleft = len;
	buf_temp = buf;

	while ( nleft > 0 ) {
		cout << "read from uart and left " << nleft 
			 << " total wanted " << len << endl;
		if((nread = readOnce(buf_temp, nleft)) < 0 ){
			if(nleft == len)
				return -1;// error, return -1
			else
				break; // error, return amount read so far
		} else if (nread == 0) {
			break; // EOF
		}
		nleft -= nread;
		buf_temp += nread;
	}
	cout << "read from uart and left " << nleft 
			 << " total wanted " << len << endl;
	
	cout << __FUNCTION__ << " : " << endl;
	for(i = 0;i < (len - nleft); i++)
		printf("%02x ", ((unsigned char *)buf)[i]);
	cout << endl;

	for(i = 0;i < (len - nleft); i++){
		if(((unsigned char *)buf)[i] == '\r')
			continue;
		printf("%c", ((unsigned char *)buf)[i]);
	}
	
	return (len - nleft); // return >= 0

}

ssize_t PhoneControlBase::readLine(char *buf, size_t len){
	char *buf_temp;
	unsigned int i;	
	size_t nleft;
	ssize_t nread;
	nleft = len;
	buf_temp = buf;

	while ( nleft > 0 ) {
		cout << "read from uart and left " << nleft 
			 << " total wanted " << len << endl;
		if((nread = readOnce(buf_temp, 1)) < 0 ){
			if(nleft == len)
				return -1;// error, return -1
			else
				break; // error, return amount read so far
		} else if (nread == 0) {
			break; // EOF
		}
		
		nleft -= nread;
		if(*buf_temp == '\n')
			break;
		buf_temp += nread;
		
	}
	cout << "read from uart and left " << nleft 
			 << " total wanted " << len << endl;
	
	cout << __FUNCTION__ << " : " << endl;
	for(i = 0;i < (len - nleft); i++)
		printf("%02x ", ((unsigned char *)buf)[i]);
	cout << endl;

	for(i = 0;i < (len - nleft); i++){
		if(((unsigned char *)buf)[i] == '\r')
			continue;
		printf("%c", ((unsigned char *)buf)[i]);
	}
	
	return (len - nleft); // return >= 0

}


ssize_t PhoneControlBase::writeDevice(const  char *buf, size_t len/*unused*/){
	unsigned char wbuf[WBUF_SZ];

	unsigned char sum = 0;
	unsigned char checksum = 0;
	unsigned int ii = 0;
	
	ssize_t nwrite;
	size_t length = strlen(buf);
	//printf("len = %d\n",length);

	memset(wbuf, 0, WBUF_SZ);
	wbuf[0] = '\0';
	memcpy(wbuf+1,buf,length);

	sum = sumArray(buf, length);
	//printf("sum = %02x\n",sum);
	checksum = 0xff - sum;
	wbuf[length+1] = checksum;
	wbuf[length+2] = '\r';
	wbuf[length+3] = '\n';

	nwrite = write(serial_fd,wbuf,length+4);

	cout << __FUNCTION__ << ":" << endl;
	for(ii = 0;ii < length+4;ii++)
		printf("%02x ",wbuf[ii]);
   	cout << endl;

	for(ii = 0;ii < length+4;ii++){
		if(wbuf[ii] == '\r')
			continue;
		printf("%c",wbuf[ii]);
	}

	return nwrite;

}

unsigned char PhoneControlBase::sumArray(const  char  *arr, int len){
	int i;
	unsigned char sum = 0;
	for(i = 0;i < len; i++) {
		sum += arr[i];
	}
	return sum;

}



}
