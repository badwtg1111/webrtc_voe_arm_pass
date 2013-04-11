#include <sys/soundcard.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
	/* id����ȡ��Ƶ�ļ���������fd��д����ļ���������i��jΪ��ʱ����*/
	int id,fd,i,j;
	/* �洢��Ƶ���ݵĻ����������Ե���*/
	char testbuf[4096];
	/* �������豸��ʧ�����˳�*/
	if ((id = open("/dev/dsp", O_RDWR )) < 0)
	{
		fprintf (stderr, " Can't open sound device!\n");
		exit ( -1 ) ;
	}
	/* ������ļ���ʧ�����˳�*/
	if ((fd = open("test.wav", O_RDWR | O_CREAT)) < 0)
	{
		fprintf ( stderr, " Can't open output file!\n");
		exit (-1 );
	}
	/* �����ʵ��Ĳ�����ʹ�������豸��������*/
	/* ��ϸ�����ο�Linux����������̵��ĵ�*/
#if 0
	i=0;
	ioctl (id,SNDCTL_DSP_RESET,(char *)&i) ;
	ioctl (id,SNDCTL_DSP_SYNC,(char *)&i);
	i=1;
	ioctl (id,SNDCTL_DSP_NONBLOCK,(char *)&i);
	i=8000;
	ioctl (id,SNDCTL_DSP_SPEED,(char *)&i);
	i=1;
	ioctl (id,SNDCTL_DSP_CHANNELS,(char *)&i);
	i=16;
	ioctl (id,SNDCTL_DSP_SETFMT,(char *)&i);

	i=3;
	ioctl (id,SNDCTL_DSP_SETTRIGGER,(char *)&i);
	i=3;
	ioctl (id,SNDCTL_DSP_SETFRAGMENT,(char *)&i);
	i=1;
	ioctl (id,SNDCTL_DSP_PROFILE,(char *)&i);

#endif


	i = 8000;
	//i = 48000;
	ioctl (id, SNDCTL_DSP_SPEED, &i);
	i = 1;
	//i = 2;
	ioctl (id, SNDCTL_DSP_CHANNELS, &i);
	//i = 16;
	i = AFMT_MU_LAW;
	ioctl (id,SNDCTL_DSP_SETFMT, &i);
	/* ��ȡһ����������Ƶ���ݣ�����֮д������ļ���ȥ*/
	for (j=0; j<100000000;)
	{
		i = read(id, testbuf, 4096);
		printf("read size is %d\n", i);
		if (i > 0)
		{
			write(fd, testbuf, i);
			j++;
		}
	}
	/* �ر����롢����ļ�*/
	close(fd);
	close(id);
	exit(0);
}
