#ifndef _PADTOPHONE_H_
#define _PADTOPHONE_H_

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
/* According to POSIX.1-2001 */
#include <sys/select.h>
/* According to earlier standards */
#include <sys/time.h>
#include <pthread.h>

#define N 512
//#define COM_DEV  "/dev/ttyS0"
//#define COM_DEV  "/dev/ttySAC1"
#define COM_DEV  "/dev/ttySAC3"



#ifdef __cplusplus
extern "C" {
#endif

unsigned char sumArray(const char  *arr, int len);  
void packageAndSendToUart(int fd, const char *buff);
int openSerial(void);
void serialInit(int fd);// serial initialization

ssize_t readFromUart(int fd, void *buf, 
					 size_t nbytes, unsigned int timeout);
ssize_t readFromUartTotal(int fd, void *buff, size_t nbytes, unsigned int timeout);
void connectIntoIdle(int fd); //��ѯ������

/*ע�����*/
extern void registration(int fd);
extern void queryRegister(int fd);
extern void cancelSubmachine(int fd, char *num);

extern void cancelSubmachine1(int fd);
extern void cancelSubmachine2(int fd);
extern void cancelSubmachineAll(int fd);

/*�������*/
void offHookAndDialUp(int fd, const char *telnum, size_t nbit);
void onHook(int fd);//�һ�
void machineExit(int fd);
void PSTNHandsFreePickMachine(int fd);//PSTN����ժ��
void PSTNHandlePickMachine(int fd);
void turnToHandsFree(int fd);
void turnToHandle(int fd);
void turnToTheSonMachine(int fd, char *son_num);
void dialUp(int fd, const char *telnum, size_t nbit);
/* ******************************************************************/
/**
 * @brief  dialUpRespectively  : ��DTMF����
 *
 * @param  fd : ����������
 * @param  num : DTMF(0~9,*,#),��12������
 */
/* ******************************************************************/
void dialUpRespectively(int fd, char *num);

/*GSM ����*/
void sendGSMRinging(int fd);
void stopGSMRinging(int fd);
void GSMHF(int fd);
void GSMHS(int fd);

/*�Խ���ز���*/
extern void talkbackOnHook(int fd);
extern void talkbackOffHook(int fd);
extern void talkbackToHandsFree(int fd);
extern void talkbackToHandle(int fd);
extern void talkbackToSubmachine1(int fd);
extern void talkbackToSubmachine2(int fd);


/*ת�ӹ���*/
extern void turnToTheSonMachine(int fd, char *son_num);
extern void masterResponse(int fd);

/*��������*/


void volumeMICGain(int fd);

void volumeChangeHandle(int fd);
void volumeChangeHandsFree(int fd);

void volumeChangeHandle7(int fd);
void volumeChangeHandsFree7(int fd);

void volumeChangeHandsFree6(int fd);
	void volumeChangeHandsFree5(int fd);
	void volumeChangeHandsFree4(int fd);


/*����ͨ������*/
void talkbackToThreeparty(int fd);
void threepartyToTalkback(int fd);



#ifdef __cplusplus
}
#endif

#endif
