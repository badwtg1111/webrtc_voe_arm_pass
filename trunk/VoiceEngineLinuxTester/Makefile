CC=arm-linux-g++

WEBRTC_TRUNK=/root/newdisk1/webrtc_no_peerconnection/trunk/
WEBRTC_SRC_ROOT_DIR=/root/newdisk1/webrtc_no_peerconnection/trunk/webrtc/
WEBRTC_LIB_ROOT_DIR=/root/newdisk1/webrtc_no_peerconnection/trunk/out/Debug/obj.target/webrtc/

WEBRTC_MACROS='-DWEBRTC_SVNREVISION="n/a"' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DCHROMIUM_BUILD' \
	'-DUSE_NSS=1' \
	'-DENABLE_ONE_CLICK_SIGNIN' \
	'-DGTK_DISABLE_SINGLE_INCLUDES=1' \
	'-DENABLE_REMOTING=1' \
	'-DENABLE_WEBRTC=1' \
	'-DENABLE_P2P_APIS=1' \
	'-DENABLE_CONFIGURATION_POLICY' \
	'-DENABLE_INPUT_SPEECH' \
	'-DENABLE_NOTIFICATIONS' \
	'-DENABLE_GPU=1' \
	'-DENABLE_EGLIMAGE=1' \
	'-DUSE_SKIA=1' \
	'-DENABLE_TASK_MANAGER=1' \
	'-DENABLE_WEB_INTENTS=1' \
	'-DENABLE_EXTENSIONS=1' \
	'-DENABLE_PLUGIN_INSTALLATION=1' \
	'-DENABLE_PROTECTOR_SERVICE=1' \
	'-DENABLE_SESSION_SERVICE=1' \
	'-DENABLE_THEMES=1' \
	'-DENABLE_BACKGROUND=1' \
	'-DENABLE_PROMO_RESOURCE_SERVICE=1' \
	'-DENABLE_AUTOMATION=1' \
	'-DWEBRTC_CHROMIUM_BUILD' \
	'-DWEBRTC_LINUX' \
	'-DWEBRTC_THREAD_RR' \
	'-DFEATURE_ENABLE_SSL' \
	'-DFEATURE_ENABLE_VOICEMAIL' \
	'-DEXPAT_RELATIVE_PATH' \
	'-DGTEST_RELATIVE_PATH' \
	'-DJSONCPP_RELATIVE_PATH' \
	'-DWEBRTC_RELATIVE_PATH' \
	'-DNO_SOUND_SYSTEM' \
	'-DLINUX' \
	'-DPOSIX' \
	'-D__STDC_FORMAT_MACROS' \
	'-DNDEBUG' \
	'-DNVALGRIND' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=0'

WEBRTC_INCLUDES= \
				-I $(WEBRTC_TRUNK) \
				-I $(WEBRTC_SRC_ROOT_DIR) \
				-I $(WEBRTC_SRC_ROOT_DIR)utility/source \
				-I $(WEBRTC_SRC_ROOT_DIR)../libyuv/include \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)utility/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)video_engine/include \
				-I $(WEBRTC_SRC_ROOT_DIR)voice_engine/include \
				-I $(WEBRTC_SRC_ROOT_DIR)voice_engine \
				-I $(WEBRTC_SRC_ROOT_DIR)system_wrappers/source \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/rtp_rtcp/source \
				-I $(WEBRTC_SRC_ROOT_DIR)voice_engine/main/source \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/utility/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)system_wrappers/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/rtp_rtcp/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)voice_engine/main/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/media_file/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/udp_transport/source \
				-I $(WEBRTC_SRC_ROOT_DIR)common_audio/resampler/include \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/udp_transport/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/audio_processing/include \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/audio_processing/utility \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/audio_device/main/source \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/bitrate_controller/include \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/audio_processing/agc/include \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/audio_processing/aec/include \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/audio_device/main/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/audio_coding/main/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/video_coding/main/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/video_render/main/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/video_render/include \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/video_capture/main/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/video_capture/include \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/video_render/main/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/video_capture/main/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/video_coding/codecs/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/audio_processing/aecm/include \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/video_processing/main/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/audio_conference_mixer/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/audio_conference_mixer/interface \
				-I $(WEBRTC_SRC_ROOT_DIR)modules/video_coding/codecs/i420/main/interface \



WEBRTC_LIBS=-lpthread -lrt -ldl -lX11\
			-lgtk-x11-2.0 \
			-lgdk-x11-2.0 \
			-latk-1.0 \
			-lgio-2.0 \
			-lpangoft2-1.0 \
			-lgdk_pixbuf-2.0 \
			-lm \
			-lpangocairo-1.0 \
			-lcairo \
			-lpango-1.0 \
			-lfreetype \
			-lfontconfig \
			-lgobject-2.0 \
			-lgmodule-2.0 \
			-lgthread-2.0 \
			-lrt \
			-lglib-2.0 \
			-lX11 \
			-lXext \
			-lexpat \
			-ldl \
			-L$(WEBRTC_LIB_ROOT_DIR)system_wrappers/source/ -lsystem_wrappers \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lwebrtc_utility \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -laec \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -laecm \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -laec_sse2 \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lagc \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lapm_util  \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -laudio_coding_module  \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -laudio_conference_mixer \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -laudio_device \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -laudio_processing \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lbitrate_controller \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lCNG  \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lG711 \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lG722 \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -liLBC  \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -liSAC \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -liSACFix \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lmedia_file  \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lNetEq  \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lns \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lPCM16B  \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lrtp_rtcp  \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -ludp_transport \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lvideo_capture_module \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lvideo_processing \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lvideo_processing_sse2 \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lvideo_render_module \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lwebrtc_i420  \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lwebrtc_video_coding \
			-L$(WEBRTC_LIB_ROOT_DIR)modules/ -lwebrtc_vp8 \
			-L$(WEBRTC_LIB_ROOT_DIR)common_audio/ -lresampler  \
			-L$(WEBRTC_LIB_ROOT_DIR)common_audio/ -lsignal_processing \
			-L$(WEBRTC_LIB_ROOT_DIR)common_audio/ -lvad \
			-L$(WEBRTC_LIB_ROOT_DIR)common_video/ -lwebrtc_libyuv \
			-L$(WEBRTC_LIB_ROOT_DIR)common_video/ -lwebrtc_jpeg \
			-L$(WEBRTC_LIB_ROOT_DIR)voice_engine/ -lvoice_engine_core \
			-L$(WEBRTC_LIB_ROOT_DIR)video_engine/ -lvideo_engine_core  \
			-L$(WEBRTC_LIB_ROOT_DIR)../libvpx/ -lvpx  \
			-L$(WEBRTC_LIB_ROOT_DIR)../libyuv/ -lyuv  \
			-L$(WEBRTC_LIB_ROOT_DIR)../libjpeg_turbo -ljpeg_turbo \
			-L$(WEBRTC_LIB_ROOT_DIR)../protobuf -lprotobuf_lite \
			
			
CFLAGS = -g -Wall -Wno-reorder -Wl,-z,noexecstack -fno-rtti -fno-threadsafe-statics -fvisibility-inlines-hidden \
			-Wsign-compare -fPIC -O0 $(WEBRTC_INCLUDES) $(WEBRTC_MACROS)

SRCS2 = TelephonyEvent.cpp VoEApi.cpp ViEApi.cpp videosize.cc GIPSVoiceEngineHelper.cpp GIPSVideoEngineHelper.cpp ChannelPool.cc CaptureDevicePool.cc 

OBJS2 = $(SRCS2:.cpp=.o) $(SRCS2:.cc=.o)

SRCS1 = Tester.cpp voe_cmd_test.cc
OBJS1 = $(SRCS1:.cpp=.o) $(SRCS1:.cc=.o)

EXECUTABLE	= GIPSVoiceEngienTester

all:
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SRCS1) $(WEBRTC_LIBS)

clean:
	rm -f *.o $(EXECUTABLE)
