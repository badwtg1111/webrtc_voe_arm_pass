/*
 * =====================================================================================
 *
 *       Filename:  phone_timer.h
 *
 *    Description:  timer for keep heartbeating
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
#ifndef _PHONE_TIMER_H_
#define _PHONE_TIMER_H_

#include <sys/time.h>
#include <signal.h>
 
namespace handaer{

typedef void(*ProcessHandler)(int);

class PhoneTimer{
	public:
		enum{
			TIMETICK_MS = (10 * 1000),
		};
				
	 	   
		PhoneTimer(int sec,int usec);
		~PhoneTimer();
		
		void setTimer(int sec,int usec);	
		void setHandler(ProcessHandler handler);	
		bool reset();
		bool cancel();

	protected:	
		void wait( long timeout_ms );

			
	protected:		  
		struct sigaction  _act; 	   
		struct sigaction  _oldact;		  
		struct itimerval  _tim_ticks;


};

}


#endif
