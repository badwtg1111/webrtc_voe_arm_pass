#include <sys/soundcard.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	/* id：读取音频文件描述符；i，j为临时变量*/
	int id,i,j;
	/* 存储音频数据的缓冲区，可以调整*/
	char testbuf[4096];
	struct timeval timeout;
	fd_set read_fds;
	audio_buf_info info;

	FILE *infile;

	infile = fopen(argv[1], "r");
	/* 打开声卡设备，失败则退出*/

	if ((id = open("/dev/dsp", O_RDWR )) < 0)
	{
		fprintf (stderr, " Can't open sound device!\n");
		exit ( -1 ) ;
	}

	/* 设置适当的参数，使得声音设备工作正常*/
	/* 详细情况请参考Linux关于声卡编程的文档*/
	/*i=0;
	  ioctl (id,SNDCTL_DSP_RESET,(char *)&i) ;
	  ioctl (id,SNDCTL_DSP_SYNC,(char *)&i);
	  i=1;
	  ioctl (id,SNDCTL_DSP_NONBLOCK,(char *)&i);
	  */

	i = 8000;
	//i = 48000;
	ioctl (id, SNDCTL_DSP_SPEED, &i);
	i = 1;
	//i = 2;
	ioctl (id, SNDCTL_DSP_CHANNELS, &i);
	//i = 16;
	i = AFMT_MU_LAW;
	ioctl (id,SNDCTL_DSP_SETFMT, &i);

	/*
	   i=3;
	   ioctl (id,SNDCTL_DSP_SETTRIGGER,(char *)&i);
	   i=3;
	   ioctl (id,SNDCTL_DSP_SETFRAGMENT,(char *)&i);
	   i=1;
	   ioctl (id,SNDCTL_DSP_PROFILE,(char *)&i);
	   */
	timeout.tv_sec = 0;
	timeout.tv_usec = 500;
	FD_ZERO(&read_fds);
	FD_SET(id, &read_fds);

	while(1)
	{
		if (FD_ISSET(id, &read_fds ) &&  ioctl( id, SNDCTL_DSP_GETISPACE, &info ) != -1)
		{
			printf("info.bytes is %d\n", info.bytes);
			if (info.bytes >= 0)
			{
				//i = read(id, testbuf, 480);
				i = fread(testbuf,1,480,infile);
				printf("read size is %d\n", i);
				if (i > 0)
				{
					write(id, testbuf, i);
				}
			}
			/*else
			  {
			  timeout.tv_sec = 0;
			  timeout.tv_usec = 5000;
			  select(0, 0, NULL, NULL, &timeout );
			  }*/
		}
		/*else
		  {
		  timeout.tv_sec = 0;
		  timeout.tv_usec = 5000;
		  select(0, 0, NULL, NULL, &timeout );
		  }*/

	}
	/* 关闭输入、输出文件*/

	close(id);
	exit(0);
}
