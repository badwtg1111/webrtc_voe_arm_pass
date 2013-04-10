#include "thread_wrapper.h" //trunk\third_party\webrtc\system_wrappers\interface
#include "cpu_info.h" //trunk\third_party\webrtc\system_wrappers\interface
#include "list_wrapper.h"//trunk\third_party\webrtc\system_wrappers\interface
#include "atomic32.h"//trunk\third_party\webrtc\system_wrappers\interface
#include "file_recorder.h"//trunk\third_party\webrtc\modules\utility\interface
#include "file_player.h"//trunk\third_party\webrtc\modules\utility\interface
#include "audio_coding_module.h"//trunk\third_party\webrtc\modules\audio_coding\main\interface
#include "media_file_defines.h"//trunk\third_party\webrtc\modules\media_file\interface
#include "video_coding.h"//trunk\third_party\webrtc\modules\video_coding\main\interface
#include "rw_lock_wrapper.h"//trunk\third_party\webrtc\system_wrappers\interface
#include "file_wrapper.h"//trunk\third_party\webrtc\system_wrappers\interface
#include "file_impl.h"//trunk\third_party\webrtc\system_wrappers\source
#include "i420.h"//trunk\third_party\webrtc\modules\video_coding\codecs\i420\main\interface
#include "video_codec_interface.h"//trunk\third_party\webrtc\modules\video_coding\codecs\interface
#include "rtp_dump.h"//trunk\third_party\webrtc\modules\utility\interface
#include "audio_device.h"//trunk\third_party\webrtc\modules\audio_device\include
						//trunk\third_party\webrtc\modules\audio_device\main\interface
#include "audio_processing.h"//trunk\third_party\webrtc\modules\audio_processing\include
#include "cpu_wrapper.h"//trunk\third_party\webrtc\system_wrappers\interface
#include "video_processing.h"//trunk\third_party\webrtc\modules\video_processing\main\interface
#include "rtp_rtcp.h"//trunk\third_party\webrtc\modules\rtp_rtcp\interface
#include "rtp_rtcp_impl.h"//trunk\third_party\webrtc\modules\rtp_rtcp\source
#include "echo_cancellation.h"//trunk\third_party\webrtc\modules\audio_processing\aec\include
#include "cpu_features_wrapper.h"//trunk\third_party\webrtc\system_wrappers\interface
#include "echo_control_mobile.h"//trunk\third_party\webrtc\modules\audio_processing\aecm\include
#include "gain_control.h"//trunk\third_party\webrtc\modules\audio_processing\agc\include
#include "fft4g.h"//trunk\third_party\webrtc\modules\audio_processing\utility
#include "sort.h"//trunk\third_party\webrtc\system_wrappers\interface
#include "video_capture.h"//trunk\third_party\webrtc\modules\video_capture\include
#include "video_capture_factory.h"//trunk\third_party\webrtc\modules\video_capture\include
#include "channel.h"//trunk\third_party\webrtc\voice_engine

#include "audio_conference_mixer.h"//trunk\third_party\webrtc\modules\audio_conference_mixer\interface
#include "video_render.h"//trunk\third_party\webrtc\modules\video_render\include
#include "bitrate_controller.h"//trunk\third_party\webrtc\modules\bitrate_controller\include
#include "udp_transport_impl.h"//trunk\third_party\webrtc\test\channel_transport
					//trunk\third_party\webrtc\modules\udp_transport\source
#include "condition_variable_wrapper.h"//trunk\third_party\webrtc\system_wrappers\interface
#include "map_wrapper.h"//trunk\third_party\webrtc\system_wrappers\interface
#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>


using namespace webrtc;

extern int cmd_main();
ThreadWrapper* g_ptrThread;
unsigned int g_ThreadID(0);

static bool VoEThreadFun(ThreadObj param)
{
	static int i = 0;
	i++;
	std::stringstream ss;
	ss<<i;
	std::string s = "I am a thread, I am arising ---  " ;
	s += ss.str();
	std::cout<<s<<std::endl;
	usleep(1000 * 1000 );
	return true;
}
static void ThreadWrapper_Tester_StartThread()
{
	const char* threadName = "voiceenginehelper_tester_thread";
	g_ptrThread = ThreadWrapper::CreateThread(VoEThreadFun, NULL, kNormalPriority, threadName);
	if (g_ptrThread == NULL)
	{
		return ;
	}
	unsigned int threadID(0);
	if (!g_ptrThread->Start(threadID))
	{
		delete g_ptrThread;
		g_ptrThread = NULL;
		return ;
	}
	g_ThreadID = threadID;
	
	#if 0
	VoECodecInst codec;
	int num;
	GIPSVoE_NumOfCodec(num);
	for(int i = 0; i < num; i++)
	{
		GIPSVoE_GetCodec(i, codec);
		if(strcmp(codec.plname, "ISAC") == 0)
		{
			break;
		}
	}
	#endif
	
}
static void ThreadWrapper_Tester_StopThread()
{
	ThreadWrapper* tmpThread = g_ptrThread;
	g_ptrThread = NULL;

	tmpThread->SetNotAlive();
	if (tmpThread->Stop())
	{
		delete tmpThread;
	}
	g_ThreadID = 0;

	std::cout<<__FUNCTION__<<" End"<<std::endl;
}

int main()
{
	std::string s = "Hello, WebRTC for linux \n";
	std::cout<<s<<std::endl;
	
	WebRtc_Word32 ret = 0;
	if(ret == 0x888888) //不执行，主要是为了解决链接的问题
	{	
		WebRtc_UWord32 cores = CpuInfo::DetectNumberOfCores();
		std::cout<<"Number of CPU core: "<<cores<<std::endl;


		std::cout<<"Create ListWrapper "<<std::endl;
		ListWrapper lw;
		lw.First();
		
		std::cout<<"Create MapWrapper "<<std::endl;
		MapWrapper mw;
		
		std::cout<<"Create ProcessThread "<<std::endl;
		ProcessThread* p = ProcessThread::CreateProcessThread();
		if(p != NULL)
		{
			ProcessThread::DestroyProcessThread(p);
		}
		
		std::cout<<"Create Atomic32 "<<std::endl;
		Atomic32 atomic(0);
		++atomic;
		--atomic;
		atomic.Value();

		std::cout<<"Create FileRecorder "<<std::endl;
		FileRecorder* file_recorder = FileRecorder::CreateFileRecorder(0, kFileFormatWavFile);
		if(file_recorder != NULL)
		{
			FileRecorder::DestroyFileRecorder(file_recorder);
		}

		std::cout<<"Create FilePlayer "<<std::endl;
		FilePlayer* filePlayerPtr = FilePlayer::CreateFilePlayer(0, kFileFormatWavFile);
		if(filePlayerPtr != NULL)
		{
			FilePlayer::DestroyFilePlayer(filePlayerPtr);
		}
		int numOfCodecs = VideoCodingModule::NumberOfCodecs();
		std::cout<<"Number of Codecs : "<<numOfCodecs<<std::endl;
		
		std::cout<<"Create RWLockWrapper "<<std::endl;
		RWLockWrapper* netEqDecodeLock = RWLockWrapper::CreateRWLock();
		if(netEqDecodeLock != NULL)
		{
			delete netEqDecodeLock;
		}

		std::cout<<"Create FileWrapper "<<std::endl;
		FileWrapper* file_wrapper = FileWrapper::Create();
		if(file_wrapper != NULL)
		{
			delete file_wrapper;
		}
		
		std::cout<<"Create I420Decoder "<<std::endl;
		I420Decoder* decoder = new I420Decoder();
		if(decoder != NULL)
		{
			delete decoder;
		}
		
		std::cout<<"Create RtpDump "<<std::endl;
		RtpDump* rtp_dump = RtpDump::CreateRtpDump();
		if(rtp_dump != NULL)
		{
			RtpDump::DestroyRtpDump(rtp_dump);
		}
		
		std::cout<<"Create AudioDeviceModule "<<std::endl;
		AudioDeviceModule* deviceModule = CreateAudioDeviceModule(0, AudioDeviceModule::kPlatformDefaultAudio);
		if(deviceModule != NULL)
		{
			//delete deviceModule;
		}

		std::cout<<"Create CpuWrapper "<<std::endl;
		CpuWrapper* cup_wrapper = CpuWrapper::CreateCpu();
		if(cup_wrapper != NULL)
		{
			delete cup_wrapper;
		}

		std::cout<<"Create ModuleRtpRtcpImpl "<<std::endl;
		RtpRtcp::Configuration conf;
		ModuleRtpRtcpImpl* rtp = new ModuleRtpRtcpImpl(conf);
		if(rtp != NULL)
		{
			delete rtp;
		}
		WebRtc_rdft(0, 0, NULL, NULL, NULL);
		WebRtc_cdft(0, 0, NULL, NULL, NULL);
		
		Sort(NULL, 0, TYPE_Word8);
		
		ret = WebRtc_GetCPUInfo(kSSE2);
		ret = WebRtcAec_Init(NULL, 0, 0);
		WebRtcAec_Create(NULL);
		WebRtcAec_Free(NULL);
		WebRtcAec_Init(NULL, 0, 0);
		WebRtcAec_BufferFarend(NULL, NULL, 0);
		WebRtcAec_Process(NULL, NULL, NULL, NULL, NULL, 0, 0, 0);
		AecConfig aecconfig;
		WebRtcAec_set_config(NULL, aecconfig);
		WebRtcAec_get_config(NULL, &aecconfig);
		WebRtcAec_get_echo_status(NULL, NULL);
		WebRtcAec_GetMetrics(NULL, NULL);
		WebRtcAec_GetDelayMetrics(NULL, NULL, NULL);
		WebRtcAec_get_error_code(NULL);
		
		WebRtcAecm_get_error_code(NULL);
		WebRtcAecm_echo_path_size_bytes();
		WebRtcAecm_GetEchoPath(NULL, NULL, 0);
		WebRtcAecm_InitEchoPath(NULL, NULL, 0);
		WebRtcAecm_get_config(NULL, NULL);
		AecmConfig config;
		WebRtcAecm_set_config(NULL, config);
		WebRtcAecm_Process(NULL, 0, 0, 0, 0, 0);
		WebRtcAecm_BufferFarend(NULL, 0, 0);
		WebRtcAecm_Init(NULL, 0);
		WebRtcAecm_Create(NULL);
		WebRtcAecm_Free(NULL);			

		WebRtcAgc_Init(NULL, 0, 0, 0, 0);	
		WebRtcAgc_Free(NULL);
		WebRtcAgc_Create(NULL);
		WebRtcAgc_config_t config_t;
		WebRtcAgc_get_config(NULL, &config_t);
		WebRtcAgc_set_config(NULL, config_t);
		WebRtcAgc_Process(NULL, NULL, NULL, 0, NULL, NULL, 0, NULL, 0, NULL);
		WebRtcAgc_VirtualMic(NULL, NULL, NULL, 0, 0, NULL);
		WebRtcAgc_AddMic(NULL, NULL, NULL, 0);
		WebRtcAgc_AddFarend(NULL, NULL, 0);
		
		AudioConferenceMixer* mixer = AudioConferenceMixer::Create(0);
		if(mixer != NULL)
		{
			delete mixer;
		}
		
		VideoRender* video_render = VideoRender::CreateVideoRender(0, NULL, true);
		if(video_render != NULL)
		{
			VideoRender::DestroyVideoRender(video_render);
		}
		
		BitrateController* bc = BitrateController::CreateBitrateController();
		if(bc != NULL)
		{
			delete bc;
		}

		voe::Channel ch(0, 0);	
		AudioProcessing* audio_processing = AudioProcessing::Create(0);
		if(audio_processing != NULL)
		{
			delete audio_processing;
		}
		
		VideoProcessingModule* image_proc_module = VideoProcessingModule::Create(0);
		if(image_proc_module != NULL)
		{
			VideoProcessingModule::Destroy(image_proc_module);
		}	
		
		VideoCaptureFactory::CreateDeviceInfo(0);
		
		WebRtc_UWord8 numOfThreads;
		UdpTransport* udp = UdpTransport::Create(0, numOfThreads);
		if(udp != NULL)
		{
			UdpTransport::Destroy(udp);
		}
		
		ConditionVariableWrapper* cond = ConditionVariableWrapper::CreateConditionVariable();
		if(cond != NULL)
		{
			delete cond;
		}

	}

	cmd_main();
	
	ThreadWrapper_Tester_StartThread();
	usleep(1000 * 1000 * 5);
	ThreadWrapper_Tester_StopThread();
	
	std::cout<<"Test end "<<std::endl;	
	
	return ret;
}