/*
  * =====================================================================================
  *
  * 	  Filename:  phone_multi_timer.h
  *
  *    Description:  This file provides an interface of multiple timers. 
  *			      For convenience, it simplify signal processing.
  * 			      Also, it can't be used in multithreading environment.
  *			      So, It need to be modified.
  *
  * 	   Version:  1.0
  * 	   Created:  05/03/2013 04:07:31 PM
  * 	  Revision:  none
  * 	  Compiler:  gcc
  *
  * 		Author:  YOUR NAME (chen.chunsheng badwtg1111@hotmail.com), 
  *   Organization:  handaer
  *
  * =====================================================================================
  */

#ifndef _PHONE_MULTI_TIMER_H_
#define _PHONE_MULTI_TIMER_H_

#include <sys/time.h>

namespace handaer{


#define 	MAX_TIMER_CNT			 10

#define	 	MUL_TIMER_INITIAL_SEC  	 10
#define		TIMER_INTERVAL_SEC	 	 10

#define 	MAX_FUNC_ARG_LEN 	 	 100

#define 	INVALID_TIMER_HANDLE 	 (-1)

typedef int timer_handle_t;

typedef int (*timer_process_cbfn_t)(void *, int);
typedef void (*sig_cbfn_t)(int);


typedef struct _timer_manage {
	
	struct _timer_info {
		
		int state;     // on or off  
		int interval;
		int elapse;    // 0~interval  
		
		timer_process_cbfn_t  timer_proc;
		char func_arg[MAX_FUNC_ARG_LEN];
		int arg_len;
		
	}timer_info[MAX_TIMER_CNT];

	sig_cbfn_t old_sigfunc;
	sig_cbfn_t new_sigfunc;
	struct itimerval value, ovalue;
	
} _timer_manage_t;





 
int init_multi_timer(void);
 
int destroy_multi_timer(void);


  
timer_handle_t set_a_timer(int interval, timer_process_cbfn_t timer_proc, 
							 void *arg, int arg_len);
 
int del_a_timer(timer_handle_t  handle);


}


#endif // _PHONE_MULTI_TIMER_H_  

