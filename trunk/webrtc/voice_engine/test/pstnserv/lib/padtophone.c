#include "padtophone.h"


unsigned char sumArray(const char  *arr, int len)  
{
	int i;
	unsigned char sum = 0;
	for(i = 0;i < len; i++) {
		sum += arr[i];
	}
	return sum;
}




void packageAndSendToUart(int fd, const char *buff)//buff -- AT code
{
	unsigned char wbuf[N];

	unsigned char sum = 0;
	unsigned char checksum = 0;
	unsigned int ii = 0;

	size_t length = strlen(buff);
	//printf("len = %d\n",length);

	memset(wbuf, 0, N);
	wbuf[0] = '\0';
	memcpy(wbuf+1,buff,length);

	sum = sumArray(buff, length);
	//printf("sum = %02x\n",sum);
	checksum = 0xff - sum;
	wbuf[length+1] = checksum;
	wbuf[length+2] = '\r';
	wbuf[length+3] = '\n';

	write(fd,wbuf,length+4);

	printf("write:\n");
	for(ii = 0;ii < length+4;ii++)
		printf("%02x ",wbuf[ii]);
   	printf("\n");

	for(ii = 0;ii < length+4;ii++)
	{
		if(wbuf[ii] == '\r')
			continue;
		printf("%c",wbuf[ii]);
	}

}

int openSerial(void)
{
	int fd; /* File descriptor for the port */
	fd = open(COM_DEV, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	{
		perror("open_port: Unable to open /dev/ttyS0 - ");
	}
	else
		printf("open ttyS0 .....\n");
		//fcntl(fd, F_SETFL, 0);/*恢复串口为阻塞状态*/

	return (fd);
}


void serialInit(int fd)// serial initialization
{
	struct termios options;
	tcgetattr(fd, &options);
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

	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);
	tcsetattr(fd,TCSANOW,&options);//the change occurs immediately
	printf("serial init finished\n");
}

ssize_t readFromUart(int fd, void *buf, size_t nbytes, unsigned int timeout)
{
	int nfds;
	fd_set readfds;
	struct timeval tv;
	ssize_t nread;
	//int i = 0;

	tv.tv_sec = 0;
	tv.tv_usec = timeout * 1000;
	FD_ZERO(&readfds);
	FD_SET(fd, &readfds);
	nfds = select(fd+1, &readfds, NULL, NULL, &tv);
	if (nfds < 0) {
		perror("select error");
		return(-1);
	} else if (nfds == 0) {
		errno = ETIME;
		printf("No data in uart to be read and timeout\n");
		return (-ETIME);
	} else {
		printf("The uart has some data...\n");
		if (FD_ISSET(fd, &readfds))
		{//	ssize_t read(int fd, void *buf, size_t count);	
			nread = read(fd, buf, nbytes);
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

ssize_t readFromUartTotal(int fd, void *buff, size_t nbytes, unsigned int timeout)
{
	void *buf_temp;
	unsigned int i;	
	size_t nleft;
	ssize_t nread;
	nleft = nbytes;
	buf_temp = buff;

	while(nleft > 0)
	{
		printf("begin read from uart\n");
		if((nread = readFromUart(fd, buf_temp, nleft, timeout)) < 0 ){
			if(nleft == nbytes)
				return -1;// error, return -1
			else
				break; // error, return amount read so far
		} else if (nread == 0) {
			break; // EOF
		}
		nleft -= nread;
		buf_temp += nread;
	}
	
	printf("read:\n");
	for(i = 0;i < (nbytes - nleft); i++)
		printf("%02x ", ((unsigned char *)buff)[i]);
	printf("\n");

	for(i = 0;i < (nbytes - nleft); i++)
	{
		if(((unsigned char *)buff)[i] == '\r')
			continue;
		printf("%c", ((unsigned char *)buff)[i]);
	}
	
	return (nbytes - nleft); // return >= 0
}

void connectIntoIdle(int fd) //查询并连接
{
	
	packageAndSendToUart(fd, "AT%TPQV=?"); //查询PSTN版本
	packageAndSendToUart(fd, "AT%TPLM=1"); //设置主控连接方式, 0---默认使用主控方
								//1----默认使用PSTN
}

	

/*注册相关*/
void registration(int fd)
{
	packageAndSendToUart(fd, "AT%TPRG");
	//packageAndSendToUart(fd, "AT%TPRV=?");
}
	
void queryRegister(int fd) // register relevance
{
	packageAndSendToUart(fd, "AT%TPRV=?");
}

void cancelSubmachine(int fd, char *num)
{
	char key[30] = "AT%TPRV=";
	strncat(key, num, 1);

	packageAndSendToUart(fd, key);
}


void cancelSubmachine1(int fd){
	packageAndSendToUart(fd, "AT%TPRV=1");
}
	
void cancelSubmachine2(int fd){
	packageAndSendToUart(fd, "AT%TPRV=2");
}

void cancelSubmachineAll(int fd){
	packageAndSendToUart(fd, "AT%TPRV=4");
}



/*拨号相关*/
void offHookAndDialUp(int fd, const char *telnum, size_t nbit)
{
	char dial[30] = "AT%TPDN=";
	strncat(dial, telnum, nbit);

	packageAndSendToUart(fd, dial);
	//packageAndSendToUart("AT%TPDN=8004");
	packageAndSendToUart(fd, "AT%TPCA=1,1,1");
	packageAndSendToUart(fd, "AT%TPSM=1");
	//packageAndSendToUart("AT%TPBC=1"); 
}
	
void onHook(int fd)//挂机
{
	packageAndSendToUart(fd, "AT%TPCA=0,0,0");
}

void machineExit(int fd)
{
	packageAndSendToUart(fd ,"AT%TPBE");
}


void PSTNHandsFreePickMachine(int fd)//PSTN免提摘机
{
	packageAndSendToUart(fd, "AT%TPCA=0,1,1");
	
	packageAndSendToUart(fd, "AT%TPSM=1");
}

void PSTNHandlePickMachine(int fd)
{
	packageAndSendToUart(fd, "AT%TPCA=1,1,1");
	packageAndSendToUart(fd, "AT%TPSM=1");//0 -- 主控模块通话业务
										//1 -- PSTN通话业务
										//2 -- Codec通路
}

void turnToHandsFree(int fd)
{
	packageAndSendToUart(fd, "AT%TPCA=0,1,1");
}

void turnToHandle(int fd)
{
	packageAndSendToUart(fd, "AT%TPCA=1,1,1");
}



void dialUp(int fd, const char *telnum, size_t nbit)
{
	char dial[30] = "AT%TPDN=";
	strncat(dial, telnum, nbit);

	packageAndSendToUart(fd, dial);
}

void dialUpRespectively(int fd, char *num)
{//AT%TPKB=6
	char key[30] = "AT%TPKB=";
	strncat(key, num, 1);

	packageAndSendToUart(fd, key);
}



/*GSM 操作*/
void sendGSMRinging(int fd)
{
	packageAndSendToUart(fd, "AT%TPLR=1");
}

void stopGSMRinging(int fd)
{
	packageAndSendToUart(fd, "AT%TPLR=0");
}

void GSMHF(int fd)
{
}

void GSMHS(int fd)
{
}

/*对讲相关操作*/
//for incoming
void talkbackOnHook(int fd){//对讲挂机
	packageAndSendToUart(fd, "AT%TPIC=0");
}

void talkbackOffHook(int fd){//对讲摘机
	packageAndSendToUart(fd, "AT%TPIC=1");
}

void talkbackToHandsFree(int fd){//对讲转免提
	packageAndSendToUart(fd, "AT%TPCA=0,1,1");
}
void talkbackToHandle(int fd){//对讲转手柄
	packageAndSendToUart(fd, "AT%TPCA=1,1,1");
}


//for going
void talkbackToSubmachine1(int fd){
	packageAndSendToUart(fd, "AT%TPIN=?");
	packageAndSendToUart(fd, "AT%TPIR=1");
	//packageAndSendToUart(fd, "AT%TPCA=0,1,1");	
}

void talkbackToSubmachine2(int fd){
	packageAndSendToUart(fd, "AT%TPIN=?");
	packageAndSendToUart(fd, "AT%TPIR=2");
	packageAndSendToUart(fd, "AT%TPCA=1,1,1");
}

/*转接功能*/
void turnToTheSonMachine(int fd, char *son_num){
//packageAndSendToUart("AT%TPBC=1"); 
	char turn[30] = "AT%TPBC=";
	strncat(turn, son_num, 1);

	packageAndSendToUart(fd, turn);
}

//子机转座机时主控应答，手柄摘机
void masterResponse(int fd){
	packageAndSendToUart(fd, "AT%TPBA=1");	
}

/*音量调节*/

void volumeMICGain(int fd){
	packageAndSendToUart(fd,"AT%TPMIG=4");
}

void volumeChangeHandle(int fd){
	packageAndSendToUart(fd, "AT%TPVO=1,8");
}

void volumeChangeHandsFree(int fd){
	packageAndSendToUart(fd, "AT%TPVO=0,8");
}

void volumeChangeHandle7(int fd){
	packageAndSendToUart(fd, "AT%TPVO=1,7");
}

void volumeChangeHandsFree7(int fd){
	packageAndSendToUart(fd, "AT%TPVO=0,7");
}


void volumeChangeHandsFree6(int fd){
	packageAndSendToUart(fd, "AT%TPVO=0,6");
}
void volumeChangeHandsFree5(int fd){
	packageAndSendToUart(fd, "AT%TPVO=0,5");
}
void volumeChangeHandsFree4(int fd){
	packageAndSendToUart(fd, "AT%TPVO=0,4");
}

/*三方通话功能*/

void talkbackToThreeparty(int fd){
	packageAndSendToUart(fd, "AT%TPIC=2");
	packageAndSendToUart(fd, "AT%TPCA=1,1,1");
}
void threepartyToTalkback(int fd){
	packageAndSendToUart(fd, "AT%TPIC=4");
	packageAndSendToUart(fd, "AT%TPCA=1,1,1");
}


