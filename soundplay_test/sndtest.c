#include <sys/soundcard.h>

#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>

static int oss_open(const char *devname, int bits,int stereo, int rate, int *minsz)
{
	int fd;
	int p=0,cond=0;
	int i=0;
	int min_size=0,blocksize=512;
	int err;
	int frag;
	audio_buf_info info;
  
	//g_message("opening sound device");
	fd=open(devname,O_RDWR|O_NONBLOCK);//fd=open(devname,O_RDWR|O_NONBLOCK);
	if (fd<0) 
	{
		printf("sound card open error\n");
		return -EWOULDBLOCK;
	}
	
	/* unset nonblocking mode */
	/* We wanted non blocking open but now put it back to normal ; thanks Xine !*/
	fcntl(fd, F_SETFL, fcntl(fd, F_GETFL)&~O_NONBLOCK);

	/* reset is maybe not needed but takes time*/
	/*ioctl(fd, SNDCTL_DSP_RESET, 0); */

	/* This code is used to limit the internal buffer of the sound
	   card so that no internal delay can occur in the sound card */
	frag = ( ( 32767 << 16 ) | 7 );
	if( ioctl( fd, SNDCTL_DSP_SETFRAGMENT, &frag ) ) {
		printf("oss_open: can't set fragment size:%s.",strerror(errno));
	}
	
	p=AFMT_S16_NE;
	
	err=ioctl(fd,SNDCTL_DSP_SETFMT,&p);
	if (err<0){
		printf("oss_open: can't set sample format:%s.",strerror(errno));
	}

	
	p =  bits;  /* 16 bits */
	err=ioctl(fd, SNDCTL_DSP_SAMPLESIZE, &p);
	if (err<0){
		printf("oss_open: can't set sample size to %i:%s.",bits,strerror(errno));
	}

	p =  rate;  /* rate in khz*/
	err=ioctl(fd, SNDCTL_DSP_SPEED, &p);
	if (err<0){
		printf("oss_open: can't set sample rate to %i:%s.",rate,strerror(errno));
	}
	
	p =  stereo;  /* stereo or not */
	err=ioctl(fd, SNDCTL_DSP_STEREO, &p);
	if (err<0){
		printf("oss_open: can't set mono/stereo mode:%s.",strerror(errno));
	}
	
	if (rate==16000) blocksize=4096;	/* oss emulation is not very good at 16khz */
	else blocksize=blocksize*(rate/8000);
	ioctl(fd, SNDCTL_DSP_GETBLKSIZE, &min_size);
	printf("min_size is %d\n", min_size);
	/* try to subdivide BLKSIZE to reach blocksize if necessary */
	if (min_size>blocksize)
	{
		cond=1;
		p=min_size/blocksize;
		while(cond)
		{
			i=ioctl(fd, SNDCTL_DSP_SUBDIVIDE, &p);
			printf("SUB_DIVIDE said error=%i,errno=%s\n",i,strerror(errno));
			if ((i==0) || (p==1)) cond=0;
			else p=p/2;
		}
	}
	
	ioctl(fd, SNDCTL_DSP_GETBLKSIZE, &min_size);
	if (min_size>blocksize)
	{
		printf("dsp block size set to %i.\n",min_size);
	}else{
		/* no need to access the card with less latency than needed*/
		min_size=blocksize;
	}
	printf("/dev/dsp opened: rate=%i,bits=%i,stereo=%i blocksize=%i.\n",rate,bits,stereo,min_size);
	
	if( ioctl( fd, SNDCTL_DSP_GETISPACE, &info ) == -1 ) {
		printf("oss_open: can't get ispace:%s.\n",strerror(errno));
	}
	else{
		printf("oss_open: audio buffer size: %i.\n", info.fragsize * sizeof( short ));
	}


	/* start recording !!! Alex */
	{
		int fl,res;
		
		fl=PCM_ENABLE_INPUT|PCM_ENABLE_OUTPUT;
		res=ioctl(fd, SNDCTL_DSP_SETTRIGGER, &fl);

		if (res<0) printf("OSS_TRIGGER: %s\n",strerror(errno));
	} 
	*minsz=min_size;
	return fd;
}


static void * oss_thread(void *p){
	int bsize=0;
	char rtmpbuff[10000];
	int err;
	int pcmfd;
	int first = 0;

	pcmfd=oss_open("/dev/dsp",16,0,8000,&bsize);
	
	while(1){
		if (pcmfd>=0){

			struct timeval timeout;
			fd_set read_fds;
			audio_buf_info info;
			
			timeout.tv_sec = 0;
			timeout.tv_usec = 0;
			FD_ZERO( &read_fds );
			FD_SET(pcmfd, &read_fds );
			if( select(pcmfd + 1, &read_fds, NULL, NULL, &timeout ) == -1 ) {
			}
			if (FD_ISSET(pcmfd, &read_fds ) &&  ioctl( pcmfd, SNDCTL_DSP_GETISPACE, &info ) != -1)
			{
				if(first)
				{
					first--;
				}
				else
					bsize = 480;
				if (info.bytes>= bsize)
				{
					err=read(pcmfd,rtmpbuff, bsize);
					if (err<0){
						printf("Fail to read %i bytes from soundcard: %s",
							   bsize,strerror(errno));
					}else{
						//printf("get size is %d\n", err);
						write(pcmfd,rtmpbuff,err);
					}
				}
				else
				{
					timeout.tv_sec = 0;
					timeout.tv_usec = 5000;
					select(0, 0, NULL, NULL, &timeout );
				}
			}
			else
			  {
				timeout.tv_sec = 0;
				timeout.tv_usec = 5000;
				select(0, 0, NULL, NULL, &timeout );
			  }
		}else usleep(20000);
	}
	if (pcmfd>=0) {
		close(pcmfd);
	}

	return NULL;
}

int main(int argc, char **argv)
{
	oss_thread(NULL);
	return 0;
}
