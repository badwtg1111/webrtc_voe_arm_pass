/*
 * =====================================================================================
 *
 *       Filename:  phone_control_base.h
 *
 *    Description:  finish the serial control  
 *
 *        Version:  1.0
 *        Created:  05/03/2013 04:07:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (chen.chunsheng badwtg1111@hotmail.com), 
 *   Organization:  handaer
 *
 * =====================================================================================
 */
#ifndef _PHONE_CONTROL_BASE_H_
#define _PHONE_CONTROL_BASE_H_
 
#include <unistd.h>
#include <termios.h>

namespace handaer{

class PhoneControlBase{
	public:
		int serial_fd;
		enum {WBUF_SZ = 128};
		PhoneControlBase();
		~PhoneControlBase();

		int setReadTimeOutMs(int time_out_ms_);
		int setDeviceName(char *dev_name);
		int openDevice(void);
		int serialConfig(speed_t baudrate);
		int closeDevice(void);
		
		ssize_t readAll(char *buf, size_t len);
		ssize_t readLine(char *buf, size_t len);
		ssize_t writeDevice(const char *buf, size_t len);
	private:
		ssize_t readOnce(char *buf, size_t len);
		unsigned char sumArray(const  char  *arr, int len);  

		char device_name[16];
		
		char * msg;
		int msg_len;
		int time_out_ms;
};



}

#endif
