//使用ARM串口2
//波特率9600
//55 AA AA 55 BA 04 00 01 01 01         0
//55 AA AA 55 BA 05 00 01 01 01         1
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



#define COM_DEV  "/dev/ttySAC2"
#define BAUDRATE  9600

const unsigned char pstn_mic[10] = {0x55, 0xAA, 0xAA, 0x55, 0xBA, 0x04, 0x00, 0x01, 0x01, 0x01};
const unsigned char apc_mic[10] = {0x55, 0xAA, 0xAA, 0x55, 0xBA, 0x05, 0x00, 0x01, 0x01, 0x01};

typedef enum MIC_TYPE {
	PSTN_MIC=0,
	APC_MIC=1,
} mic_type_t;


int openSerial(void)
{
	int fd; /* File descriptor for the port */
	fd = open(COM_DEV, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	{
		perror("open_port: Unable to open "COM_DEV" - ");
	}
	else
		printf("open %s .....\n", COM_DEV);
		//fcntl(fd, F_SETFL, 0);/*恢复串口为阻塞状态*/

	return (fd);
}


/**
 * 用于设置串口的属性
 */
int serial_init(const int fd, int baud)
{
    printf("__________________%d______________ %s() entry\n", __LINE__, __FUNCTION__);
    int res = 0;
	struct termios old_opt, new_opt;
	memset(&old_opt, 0, sizeof(struct termios));
	memset(&new_opt, 0, sizeof(struct termios));
	 
	if (tcgetattr(fd, &old_opt) < 0)
	{  
		printf("tcgetattr failed!%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__);
		return -1;
	}
		
		// 配置
	new_opt.c_iflag = IGNPAR;
    
    switch (baud)
    {
        case 2400:
        {
            new_opt.c_cflag = B2400;
            break;
        }
        case 4800:
        {
            new_opt.c_cflag = B4800;            
            break;
        }
        case 9600:
        {
            new_opt.c_cflag = B9600;
            break;
        }
        case 57600:
        {
            new_opt.c_cflag = B57600;
            break;
        }
        case 115200:
        {
            new_opt.c_cflag = B115200;
            break;
        }
        default :
        {
            new_opt.c_cflag = B115200;
            break;
        }
    }
    
   new_opt.c_cflag |= CS8;                //数据位为8  
   new_opt.c_cflag |= (CREAD | CLOCAL);   //
   new_opt.c_cflag &= ~PARENB;            //无校验   
   new_opt.c_cflag &= ~CSTOPB;            //停止位是一位
   new_opt.c_cc[VMIN] = 1;                // 当接收到一个字节数据就读取
   new_opt.c_cc[VTIME] = 0;               // 不启用计时器  
    
    
    //tcflush(fd, TCIOFLUSH);
   if (tcsetattr(fd, TCSANOW, &new_opt) < 0)
    {
        printf("tcsetattr failed!%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__ );
        return -2;
    }
    printf("__________________%d______________ %s() exit\n", __LINE__, __FUNCTION__);
    return 0;
}


int main(int argc, char *argv[]){
	int fd;
	int ret;
	mic_type_t mt;
	
	if(argc < 2){
		printf("usage:%s 0/1\n",argv[0]);
		return -1;
	}
	mt = (mic_type_t) atoi(argv[1]);
	
	fd = openSerial();
	if (fd < 0){
		perror("Can't open "COM_DEV);
	}
	serial_init(fd, BAUDRATE);
	
	switch(mt){
	case PSTN_MIC:
		ret = write(fd, pstn_mic, 10);
		printf("Set PSTN MIC success %d\n", ret);
		break;
	case APC_MIC:
		ret = write(fd, apc_mic, 10);
		printf("Set APC MIC success %d\n", ret);
		break;
	default:
		printf("Mic type error\n");
		break;
	};
	
	close(fd);
	return 0;
}