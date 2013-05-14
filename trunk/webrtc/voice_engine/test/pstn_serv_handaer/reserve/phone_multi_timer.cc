/*
  * =====================================================================================
  *
  * 	  Filename:  phone_multi_timer.cc
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
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include "phone_multi_timer.h"

namespace handaer {

static _timer_manage_t  timer_manage;

static void sig_func(int signo);

//struct itimerval {
//	struct timeval it_interval; /* next value */
//	struct timeval it_value;	/* current value */  --> 0  -->  it_interval -->0 ......
//};
//Timers decrement from it_value to zero, generate a signal, and reset to
//it_interval.  A timer which is set to zero (it_value  is  zero	or	the
//timer expires and it_interval is zero) stops.


/* success, return 0; failed, return -1 */
int init_multi_timer(void) {
	int ret;

	memset(&timer_manage, 0, sizeof(_timer_manage_t));
	if((timer_manage.old_sigfunc = signal(SIGALRM, sig_func)) == SIG_ERR){
		return(-1);
	}
    timer_manage.new_sigfunc = sig_func;

    timer_manage.value.it_value.tv_sec = MUL_TIMER_INITIAL_SEC; //current value
    timer_manage.value.it_value.tv_usec = 0;
    timer_manage.value.it_interval.tv_sec = TIMER_INTERVAL_SEC; //next value
    timer_manage.value.it_interval.tv_usec = 0;
    ret = setitimer(ITIMER_REAL, &timer_manage.value, &timer_manage.ovalue);

	return (ret);
}


/* success, return 0; failed, return -1 */
int destroy_multi_timer(void) {
	int ret;

	if((signal(SIGALRM, timer_manage.old_sigfunc)) == SIG_ERR){
		return(-1);
	}

    ret = setitimer(ITIMER_REAL, &timer_manage.ovalue, &timer_manage.value);
	if(ret <  0){
		return(-1);
	}
	memset(&timer_manage, 0,sizeof(_timer_manage_t));

	return (0);
}


/* success, return timer handle(>=0); failed, return -1 */
timer_handle_t set_a_timer(int interval, timer_process_cbfn_t timer_proc, 
							 void *arg, int arg_len) {
	int i;

	if (timer_proc == NULL || interval <= 0) {
		return(-1);
	}

	for(i = 0; i < MAX_TIMER_CNT; i++) {
		if(timer_manage.timer_info[i].state == 1) {
			continue;
		}

		memset(&timer_manage.timer_info[i], 0, sizeof(timer_manage.timer_info[i]));
        timer_manage.timer_info[i].timer_proc = timer_proc;
		if(arg != NULL) {
			if(arg_len > MAX_FUNC_ARG_LEN){  
				return (-1);
			}
			memcpy(timer_manage.timer_info[i].func_arg, arg, arg_len);
            timer_manage.timer_info[i].arg_len = arg_len;
		}
        timer_manage.timer_info[i].interval = interval;
        timer_manage.timer_info[i].elapse = 0;
        timer_manage.timer_info[i].state = 1;
		break;
	}

	if(i >= MAX_TIMER_CNT) {
		return(-1);
	}
	
	return(i);
}


/* success, return 0; failed, return -1 */
int del_a_timer(timer_handle_t handle) {
	if(handle < 0 || handle >= MAX_TIMER_CNT) {
		return (-1);
	}

	memset(&timer_manage.timer_info[handle], 0, sizeof(timer_manage.timer_info[handle]));

	return(0);
}


static void sig_func(int signo) {
	int i;
	for(i = 0; i < MAX_TIMER_CNT; i++) {
		if(timer_manage.timer_info[i].state == 0) {
			continue;
		}
        timer_manage.timer_info[i].elapse ++;
		if(timer_manage.timer_info[i].elapse == 
		   			timer_manage.timer_info[i].interval) {
            timer_manage.timer_info[i].elapse = 0;
            timer_manage.timer_info[i].timer_proc(timer_manage.timer_info[i].func_arg, timer_manage.timer_info[i].arg_len);
		}
	}
	
	return;
}

}



//#define _MUL_TIMER_MAIN
#ifdef  _MUL_TIMER_MAIN

using namespace handaer;

static void get_current_format_time(char * tstr) {
	time_t t;
    t = time(NULL);
	strcpy(tstr, ctime(&t));
    tstr[strlen(tstr)-1] = '\0'; // replace '\n' with '\0'

	return;
}


timer_handle_t  hdl[3], call_cnt = 0;

int timer_proc1(void * arg, int len) {
	char tstr[200];
	static int i, ret;

    get_current_format_time(tstr);
	printf("hello %s: timer_proc1 is here.\n", tstr);
	if(i >= 5) {
        get_current_format_time(tstr);
        ret = del_a_timer(hdl[0]);
		printf("timer_proc1: %s del_a_timer::ret=%d\n", tstr, ret);
	}
    i++;
    call_cnt++;

	return (0);
}

int timer_proc2(void * arg, int len) {
	char tstr[200];
	static int i, ret;

    get_current_format_time(tstr);
	printf("hello %s: timer_proc2 is here.\n", tstr);
	if(i >= 5){
        get_current_format_time(tstr);
        ret = del_a_timer(hdl[1]);
		printf("timer_proc2: %s del_a_timer::ret=%d\n", tstr, ret);
	}
    i++;
    call_cnt++;

	return (0);
}

int timer_proc3(void * arg, int len) {
	char tstr[200];
	static int i, ret;

    get_current_format_time(tstr);
	printf("hello %s: timer_proc3 is here.\n", tstr);
	if(i >= 20){
        get_current_format_time(tstr);
        ret = del_a_timer(hdl[2]);
		printf("timer_proc3: %s del_a_timer::ret=%d\n", tstr, ret);
	}
    i++;
    call_cnt++;

	return (0);
}


int main(void) {
	char arg[50];
	char tstr[200];
	int ret;

    init_multi_timer();

    get_current_format_time(tstr);
	printf("hello %s: main is here.\n", tstr);
	
    hdl[0] = set_a_timer(2, timer_proc1, NULL, 0);
	printf("hdl[0]=%d\n", hdl[0]);
	
    hdl[1] = set_a_timer(1, timer_proc2, arg, 50);
	printf("hdl[1]=%d\n", hdl[1]);
	
    hdl[2]= set_a_timer(1, timer_proc3, arg, 50);
	printf("hdl[2]=%d\n", hdl[2]);
	
	while(1) {
		if(call_cnt >= 25) {
            get_current_format_time(tstr);
            ret = destroy_multi_timer();
			printf("main: %s destroy_mul_timer, ret=%d\n", tstr, ret);
            call_cnt++;
		}
		if(call_cnt >= 50) {
			break;
		}
	}

	return 0;
}

#endif





