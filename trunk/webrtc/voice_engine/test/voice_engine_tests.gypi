# Copyright (c) 2011 The WebRTC project authors. All Rights Reserved.
#
# Use of this source code is governed by a BSD-style license
# that can be found in the LICENSE file in the root of the source
# tree. An additional intellectual property rights grant can be found
# in the file PATENTS.  All contributing project authors may
# be found in the AUTHORS file in the root of the source tree.

{
  'targets': [
    # Auto test - command line test for all platforms
    {
      'target_name': 'voe_auto_test',
      'type': 'executable',
      'dependencies': [
        'voice_engine_core',
        '<(webrtc_root)/system_wrappers/source/system_wrappers.gyp:system_wrappers',
        '<(webrtc_root)/test/test.gyp:test_support',
        '<(DEPTH)/testing/gtest.gyp:gtest',
        '<(DEPTH)/testing/gmock.gyp:gmock',
        '<(DEPTH)/third_party/google-gflags/google-gflags.gyp:google-gflags',
        '<(webrtc_root)/test/libtest/libtest.gyp:libtest',
        '<(webrtc_root)/test/channel_transport.gyp:channel_transport',
       ],
      'include_dirs': [
        'auto_test',
        'auto_test/fixtures',
        '<(webrtc_root)/modules/interface',
        # TODO(phoglund): We only depend on voice_engine_defines.h here -
        # move that file to interface and then remove this dependency.
        '<(webrtc_root)/voice_engine',
        '<(webrtc_root)/modules/audio_device/main/interface',
      ],
      'sources': [
        'auto_test/automated_mode.cc',
        'auto_test/extended/agc_config_test.cc',
        'auto_test/extended/ec_metrics_test.cc',
        'auto_test/fakes/fake_external_transport.cc',
        'auto_test/fakes/fake_external_transport.h',
        'auto_test/fixtures/after_initialization_fixture.cc',
        'auto_test/fixtures/after_initialization_fixture.h',
        'auto_test/fixtures/after_streaming_fixture.cc',
        'auto_test/fixtures/after_streaming_fixture.h',
        'auto_test/fixtures/before_initialization_fixture.cc',
        'auto_test/fixtures/before_initialization_fixture.h',
        'auto_test/fuzz/rtp_fuzz_test.cc',
        'auto_test/standard/audio_processing_test.cc',
        'auto_test/standard/call_report_test.cc',
        'auto_test/standard/codec_before_streaming_test.cc',
        'auto_test/standard/codec_test.cc',
        'auto_test/standard/dtmf_test.cc',
        'auto_test/standard/encryption_test.cc',
        'auto_test/standard/external_media_test.cc',
        'auto_test/standard/file_before_streaming_test.cc',
        'auto_test/standard/file_test.cc',
        'auto_test/standard/hardware_before_initializing_test.cc',
        'auto_test/standard/hardware_before_streaming_test.cc',
        'auto_test/standard/hardware_test.cc',
        'auto_test/standard/manual_hold_test.cc',
        'auto_test/standard/mixing_test.cc',
        'auto_test/standard/neteq_stats_test.cc',
        'auto_test/standard/neteq_test.cc',
        'auto_test/standard/network_test.cc',
        'auto_test/standard/rtp_rtcp_before_streaming_test.cc',
        'auto_test/standard/rtp_rtcp_test.cc',
        'auto_test/standard/voe_base_misc_test.cc',
        'auto_test/standard/video_sync_test.cc',
        'auto_test/standard/volume_test.cc',
        'auto_test/resource_manager.cc',
        'auto_test/voe_cpu_test.cc',
        'auto_test/voe_cpu_test.h',
        'auto_test/voe_extended_test.cc',
        'auto_test/voe_extended_test.h',
        'auto_test/voe_standard_test.cc',
        'auto_test/voe_standard_test.h',
        'auto_test/voe_stress_test.cc',
        'auto_test/voe_stress_test.h',
        'auto_test/voe_test_defines.h',
        'auto_test/voe_test_interface.h',
        'auto_test/voe_unit_test.cc',
        'auto_test/voe_unit_test.h',
      ],
      'conditions': [
        ['OS=="android"', {
          # some tests are not supported on android yet, exclude these tests.
          'sources!': [
            'auto_test/standard/hardware_before_streaming_test.cc',
          ],
        }],
      ],
      # Disable warnings to enable Win64 build, issue 1323.
      'msvs_disabled_warnings': [
        4267,  # size_t to int truncation.
      ],
    },
    {
      # command line test that should work on linux/mac/win
      'target_name': 'voe_cmd_test',
      'type': 'executable',
      'include_dirs':[
		  '/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc/usr/include/',
	  	  '/phone-2.9/include',
	  ],
	  'cflags':[
		  '--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc',
	      
	  ],
	  'linkflags':[
	      '-Wl,-rpath-link -Wl,/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc/usr/lib',
		  '--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc',
	  ],
	  'ldflags':[
		  
	  ],
	  'dependencies': [
        '<(webrtc_root)/test/test.gyp:test_support',
        '<(DEPTH)/testing/gtest.gyp:gtest',
        'voice_engine_core',
        '<(webrtc_root)/system_wrappers/source/system_wrappers.gyp:system_wrappers',
        '<(webrtc_root)/test/channel_transport.gyp:channel_transport',
      ],
      'sources': [
        'cmd_test/voe_cmd_test.cc',
      ],
    },
    {
      # command line test that should work on linux/mac/win
      'target_name': 'pstn_cmd_test',
      'type': 'executable',
      'include_dirs':[
#		  '/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc/usr/include/',
#	  	  '/phone-2.9/include',
	  ],
	  'cflags':[
#		  '--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc',
	      
	  ],
	  'linkflags':[
#	      '-Wl,-rpath-link -Wl,/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc/usr/lib',
#		  '--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc',
	  ],
	  'ldflags':[
#		  '--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc',
		  
	  ],
	  'dependencies': [
        '<(webrtc_root)/test/test.gyp:test_support',
        '<(DEPTH)/testing/gtest.gyp:gtest',
        'voice_engine_core',
        '<(webrtc_root)/system_wrappers/source/system_wrappers.gyp:system_wrappers',
        '<(webrtc_root)/test/channel_transport.gyp:channel_transport',
      ],
      'sources': [
        'pstn_cmd_test/voe_cmd_test.cc',
        'pstn_cmd_test/tester.cc',
      ],
    },
    {
      # command line test that should work on linux/mac/win
      'target_name': 'pstn_serv_arm_gyp',
      'type': 'executable',
      'include_dirs':[
#		  '/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc/usr/include/',
#	  	  '/phone-2.9/include',
	  	  '/phone/include',
	  	  './pstnserv/include/',
	  ],
	  'cflags':[
#		  '--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc',
	      
	  ],
	  'linkflags':[
#	      '-Wl,-rpath-link -Wl,/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc/usr/lib',
#		  '--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc',
	  ],
	  'ldflags':[
#		  '--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc',
		  '-L/phone/lib', 
	  ],
	  'libraries':[
		  '-logg',
		  '-lspeexdsp',
	  	  '-lspeex',
		  '-lortp',
		  '-lgsm',
		  '-lmediastreamer',
	  ],
	  'dependencies': [
#        '<(webrtc_root)/test/test.gyp:test_support',
#        '<(DEPTH)/testing/gtest.gyp:gtest',
#        'voice_engine_core',
#        '<(webrtc_root)/system_wrappers/source/system_wrappers.gyp:system_wrappers',
#        '<(webrtc_root)/test/channel_transport.gyp:channel_transport',
      ],
      'sources': [
        'pstnserv/app/PSTNserver.cpp',
        'pstnserv/include/mymediastream.h',
		'pstnserv/include/padtophone.h',
		'pstnserv/lib/mediastream.c',
		'pstnserv/lib/padtophone.c',
      ],
    },
    {
      # command line test that should work on linux/mac/win
      'target_name': 'pstn_serv_handaer',
      'type': 'executable',
      'include_dirs':[
#		  '/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc/usr/include/',
#	  	  '/phone-2.9/include',
	  	  '/phone/include',
	  	  './pstnserv/include/',
	  ],
	  'cflags':[
#		  '--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc',
	      
	  ],
	  'linkflags':[
#	      '-Wl,-rpath-link -Wl,/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc/usr/lib',
#		  '--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc',
	  ],
	  'ldflags':[
#		  '--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc',
		  '-L/phone/lib', 
	  ],
	  'libraries':[
		  '-logg',
		  '-lspeexdsp',
	  	  '-lspeex',
		  '-lortp',
		  '-lgsm',
		  '-lmediastreamer',
	  ],
	  'dependencies': [
#        '<(webrtc_root)/test/test.gyp:test_support',
#        '<(DEPTH)/testing/gtest.gyp:gtest',
#        'voice_engine_core',
         '<(webrtc_root)/system_wrappers/source/system_wrappers.gyp:system_wrappers',
#        '<(webrtc_root)/test/channel_transport.gyp:channel_transport',
      ],
      'sources': [
        'pstnserv/app/PSTNserver.cpp',
        'pstnserv/include/mymediastream.h',
		'pstnserv/include/padtophone.h',
		'pstnserv/lib/mediastream.c',
		'pstnserv/lib/padtophone.c',
      ],
    },
    {
      # command line test that should work on linux/mac/win
      'target_name': 'phone_serv_handaer',
      'type': 'executable',
      'include_dirs':[
#		  '/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc/usr/include/',
#	  	  '/phone-2.9/include',
#	  	  '/root/newdisk1/mediastreamer_mipsel/phone/include',
	  	  '/phone/include',
	  	  './pstn_serv_handaer',
	  	  './pstn_serv_handaer/system_wrapper',
	  ],
	  'cflags':[
#		  '--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc',
	      
	  ],
	  'linkflags':[
#	      '-Wl,-rpath-link -Wl,/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc/usr/lib',
#		  '--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc',
	  ],
	  'ldflags':[
#		  '--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc',
#		  '-L/root/newdisk1/mediastreamer_mipsel/phone/lib', 
		  '-L/phone/lib', 
	  ],
	  'libraries':[
		  '-logg',
		  '-lspeexdsp',
	  	  '-lspeex',
		  '-lortp',
		  '-lgsm',
		  '-lmediastreamer',
	  ],
	  'dependencies': [
#        '<(webrtc_root)/test/test.gyp:test_support',
#        '<(DEPTH)/testing/gtest.gyp:gtest',
#        'voice_engine_core',
#         '<(webrtc_root)/system_wrappers/source/system_wrappers.gyp:system_wrappers',
#        '<(webrtc_root)/test/channel_transport.gyp:channel_transport',
      ],
      'sources': [
        'pstn_serv_handaer/phone_control_base.cc',
        'pstn_serv_handaer/phone_control_base.h',
		'pstn_serv_handaer/phone_control_service.cc',
		'pstn_serv_handaer/phone_control_service.h',
		'pstn_serv_handaer/phone_mediastream.c',
		'pstn_serv_handaer/phone_mediastream.h',
        'pstn_serv_handaer/phone_proxy.cc',
        'pstn_serv_handaer/phone_proxy.h',
		'pstn_serv_handaer/phone_readline.cc',
		'pstn_serv_handaer/phone_timer.cc',
		'pstn_serv_handaer/phone_timer.h',
		'pstn_serv_handaer/phone_serv_handaer.cc',
		
		'pstn_serv_handaer/system_wrapper/phone_common_types.h',
		'pstn_serv_handaer/system_wrapper/phone_condition_variable.cc',
		'pstn_serv_handaer/system_wrapper/phone_condition_variable_posix.cc',
		'pstn_serv_handaer/system_wrapper/phone_condition_variable_posix.h',
		'pstn_serv_handaer/system_wrapper/phone_condition_variable_wrapper.h',
		'pstn_serv_handaer/system_wrapper/phone_critical_section.cc',
		'pstn_serv_handaer/system_wrapper/phone_critical_section_posix.cc',
		'pstn_serv_handaer/system_wrapper/phone_critical_section_posix.h',
		'pstn_serv_handaer/system_wrapper/phone_critical_section_wrapper.h',
		'pstn_serv_handaer/system_wrapper/phone_event.cc',
		'pstn_serv_handaer/system_wrapper/phone_event_posix.cc',
		'pstn_serv_handaer/system_wrapper/phone_event_posix.h',
		'pstn_serv_handaer/system_wrapper/phone_event_wrapper.h',
		'pstn_serv_handaer/system_wrapper/phone_sleep.cc',
		'pstn_serv_handaer/system_wrapper/phone_sleep.h',
		'pstn_serv_handaer/system_wrapper/phone_thread.cc',
		'pstn_serv_handaer/system_wrapper/phone_thread_posix.cc',
		'pstn_serv_handaer/system_wrapper/phone_thread_posix.h',
		'pstn_serv_handaer/system_wrapper/phone_thread_wrapper.h',
		'pstn_serv_handaer/system_wrapper/phone_typedefs.h',
		
      ],
    },
    
  ],

  
  'conditions': [
    # TODO(kjellander): Support UseoFMFC on VS2010.
    # http://code.google.com/p/webrtc/issues/detail?id=709
    ['OS=="win" and MSVS_VERSION < "2010"', {
      'targets': [
        # WinTest - GUI test for Windows
        {
          'target_name': 'voe_ui_win_test',
          'type': 'executable',
          'dependencies': [
            'voice_engine_core',
            '<(webrtc_root)/system_wrappers/source/system_wrappers.gyp:system_wrappers',
            '<(webrtc_root)/test/test.gyp:test_support',
          ],
          'include_dirs': [
            'win_test',
          ],
          'sources': [
            'win_test/Resource.h',
            'win_test/WinTest.cc',
            'win_test/WinTest.h',
            'win_test/WinTest.rc',
            'win_test/WinTestDlg.cc',
            'win_test/WinTestDlg.h',
            'win_test/res/WinTest.ico',
            'win_test/res/WinTest.rc2',
            'win_test/stdafx.cc',
            'win_test/stdafx.h',
          ],
          'configurations': {
            'Common_Base': {
              'msvs_configuration_attributes': {
                'conditions': [
                  ['component=="shared_library"', {
                    'UseOfMFC': '2',  # Shared DLL
                  },{
                    'UseOfMFC': '1',  # Static
                  }],
                ],
              },
            },
          },
          'msvs_settings': {
            'VCLinkerTool': {
              'SubSystem': '2',   # Windows
            },
          },
        },
      ],
    }],
  ],
}

# Local Variables:
# tab-width:2
# indent-tabs-mode:nil
# End:
# vim: set expandtab tabstop=2 shiftwidth=2:
