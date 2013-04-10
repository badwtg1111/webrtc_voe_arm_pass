# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := audio_coding_unittests
DEFS_Debug := \
	'-DWEBRTC_SVNREVISION="Unavailable(issue687)"' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DUSE_LINUX_BREAKPAD' \
	'-DCHROMIUM_BUILD' \
	'-DUSE_DEFAULT_RENDER_THEME=1' \
	'-DUSE_LIBJPEG_TURBO=1' \
	'-DUSE_NSS=1' \
	'-DENABLE_ONE_CLICK_SIGNIN' \
	'-DGTK_DISABLE_SINGLE_INCLUDES=1' \
	'-DENABLE_REMOTING=1' \
	'-DENABLE_WEBRTC=1' \
	'-DENABLE_PEPPER_THREADING' \
	'-DENABLE_CONFIGURATION_POLICY' \
	'-DENABLE_INPUT_SPEECH' \
	'-DENABLE_NOTIFICATIONS' \
	'-DENABLE_GPU=1' \
	'-DENABLE_EGLIMAGE=1' \
	'-DUSE_SKIA=1' \
	'-DENABLE_TASK_MANAGER=1' \
	'-DENABLE_EXTENSIONS=1' \
	'-DENABLE_PLUGIN_INSTALLATION=1' \
	'-DENABLE_PLUGINS=1' \
	'-DENABLE_SESSION_SERVICE=1' \
	'-DENABLE_THEMES=1' \
	'-DENABLE_BACKGROUND=1' \
	'-DENABLE_AUTOMATION=1' \
	'-DENABLE_GOOGLE_NOW=1' \
	'-DENABLE_LANGUAGE_DETECTION=1' \
	'-DENABLE_PRINTING=1' \
	'-DENABLE_CAPTIVE_PORTAL_DETECTION=1' \
	'-DENABLE_MANAGED_USERS=1' \
	'-DWEBRTC_LOGGING' \
	'-DWEBRTC_ARCH_ARM' \
	'-DWEBRTC_LINUX' \
	'-DWEBRTC_THREAD_RR' \
	'-DUNIT_TEST' \
	'-DGTEST_HAS_RTTI=0' \
	'-D__STDC_CONSTANT_MACROS' \
	'-D__STDC_FORMAT_MACROS' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=1' \
	'-DWTF_USE_DYNAMIC_ANNOTATIONS=1' \
	'-D_DEBUG'

# Flags passed to all source files.
CFLAGS_Debug := \
	-fstack-protector \
	--param=ssp-buffer-size=4 \
	-Werror \
	-pthread \
	-fno-exceptions \
	-fno-strict-aliasing \
	-Wall \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-pipe \
	-fPIC \
	-Wextra \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	--sysroot=/root/newdisk1/webrtc_no_peerconnection/trunk/arm-sysroot \
	-O0 \
	-g

# Flags passed to only C files.
CFLAGS_C_Debug :=

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-fno-rtti \
	-fno-threadsafe-statics \
	-fvisibility-inlines-hidden \
	-Wsign-compare \
	-Woverloaded-virtual \
	-Wno-abi

INCS_Debug := \
	-Iwebrtc \
	-I. \
	-I. \
	-Iwebrtc/test \
	-Iwebrtc/modules/audio_coding/main/interface \
	-Iwebrtc/modules/interface \
	-Iwebrtc/modules/audio_coding/codecs/cng/include \
	-Iwebrtc/modules/audio_coding/codecs/isac/fix/interface \
	-Iwebrtc/modules/audio_coding/neteq/interface \
	-Iwebrtc/modules/audio_coding/neteq4/interface \
	-Iwebrtc/modules/audio_coding/neteq4/test \
	-Iwebrtc/modules/audio_coding/neteq4/tools \
	-Iwebrtc/modules/audio_coding/codecs/pcm16b/include \
	-Iwebrtc/common_audio/vad/include \
	-Itesting/gmock/include \
	-Itesting/gtest/include \
	-Iwebrtc/system_wrappers/interface \
	-I/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc/usr/include

DEFS_Release := \
	'-DWEBRTC_SVNREVISION="Unavailable(issue687)"' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DUSE_LINUX_BREAKPAD' \
	'-DCHROMIUM_BUILD' \
	'-DUSE_DEFAULT_RENDER_THEME=1' \
	'-DUSE_LIBJPEG_TURBO=1' \
	'-DUSE_NSS=1' \
	'-DENABLE_ONE_CLICK_SIGNIN' \
	'-DGTK_DISABLE_SINGLE_INCLUDES=1' \
	'-DENABLE_REMOTING=1' \
	'-DENABLE_WEBRTC=1' \
	'-DENABLE_PEPPER_THREADING' \
	'-DENABLE_CONFIGURATION_POLICY' \
	'-DENABLE_INPUT_SPEECH' \
	'-DENABLE_NOTIFICATIONS' \
	'-DENABLE_GPU=1' \
	'-DENABLE_EGLIMAGE=1' \
	'-DUSE_SKIA=1' \
	'-DENABLE_TASK_MANAGER=1' \
	'-DENABLE_EXTENSIONS=1' \
	'-DENABLE_PLUGIN_INSTALLATION=1' \
	'-DENABLE_PLUGINS=1' \
	'-DENABLE_SESSION_SERVICE=1' \
	'-DENABLE_THEMES=1' \
	'-DENABLE_BACKGROUND=1' \
	'-DENABLE_AUTOMATION=1' \
	'-DENABLE_GOOGLE_NOW=1' \
	'-DENABLE_LANGUAGE_DETECTION=1' \
	'-DENABLE_PRINTING=1' \
	'-DENABLE_CAPTIVE_PORTAL_DETECTION=1' \
	'-DENABLE_MANAGED_USERS=1' \
	'-DWEBRTC_LOGGING' \
	'-DWEBRTC_ARCH_ARM' \
	'-DWEBRTC_LINUX' \
	'-DWEBRTC_THREAD_RR' \
	'-DUNIT_TEST' \
	'-DGTEST_HAS_RTTI=0' \
	'-D__STDC_CONSTANT_MACROS' \
	'-D__STDC_FORMAT_MACROS' \
	'-DNDEBUG' \
	'-DNVALGRIND' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=0' \
	'-D_FORTIFY_SOURCE=2'

# Flags passed to all source files.
CFLAGS_Release := \
	-fstack-protector \
	--param=ssp-buffer-size=4 \
	-Werror \
	-pthread \
	-fno-exceptions \
	-fno-strict-aliasing \
	-Wall \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-pipe \
	-fPIC \
	-Wextra \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	--sysroot=/root/newdisk1/webrtc_no_peerconnection/trunk/arm-sysroot \
	-O2 \
	-fno-ident \
	-fdata-sections \
	-ffunction-sections

# Flags passed to only C files.
CFLAGS_C_Release :=

# Flags passed to only C++ files.
CFLAGS_CC_Release := \
	-fno-rtti \
	-fno-threadsafe-statics \
	-fvisibility-inlines-hidden \
	-Wsign-compare \
	-Woverloaded-virtual \
	-Wno-abi

INCS_Release := \
	-Iwebrtc \
	-I. \
	-I. \
	-Iwebrtc/test \
	-Iwebrtc/modules/audio_coding/main/interface \
	-Iwebrtc/modules/interface \
	-Iwebrtc/modules/audio_coding/codecs/cng/include \
	-Iwebrtc/modules/audio_coding/codecs/isac/fix/interface \
	-Iwebrtc/modules/audio_coding/neteq/interface \
	-Iwebrtc/modules/audio_coding/neteq4/interface \
	-Iwebrtc/modules/audio_coding/neteq4/test \
	-Iwebrtc/modules/audio_coding/neteq4/tools \
	-Iwebrtc/modules/audio_coding/codecs/pcm16b/include \
	-Iwebrtc/common_audio/vad/include \
	-Itesting/gmock/include \
	-Itesting/gtest/include \
	-Iwebrtc/system_wrappers/interface \
	-I/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc/usr/include

OBJS := \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/main/source/acm_neteq_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/codecs/cng/cng_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/codecs/isac/fix/source/filters_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/codecs/isac/fix/source/filterbanks_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/codecs/isac/fix/source/lpc_masking_model_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/codecs/isac/fix/source/transform_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/audio_multi_vector_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/audio_vector_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/background_noise_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/buffer_level_filter_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/comfort_noise_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/decision_logic_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/decoder_database_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/delay_manager_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/delay_peak_detector_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/dsp_helper_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/dtmf_buffer_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/dtmf_tone_generator_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/expand_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/merge_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/neteq_external_decoder_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/neteq_impl_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/neteq_stereo_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/neteq_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/normal_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/packet_buffer_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/payload_splitter_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/post_decode_vad_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/random_vector_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/sync_buffer_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/timestamp_scaler_unittest.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/time_stretch_unittest.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# Make sure our dependencies are built before any of us.
$(OBJS): | $(obj).target/webrtc/modules/libaudio_coding_module.a $(obj).target/webrtc/modules/libCNG.a $(obj).target/webrtc/modules/libiSACFix.a $(obj).target/webrtc/modules/libNetEq.a $(obj).target/webrtc/modules/libNetEq4.a $(obj).target/webrtc/modules/libNetEq4TestTools.a $(obj).target/webrtc/modules/libneteq_unittest_tools.a $(obj).target/webrtc/modules/libPCM16B.a $(obj).target/webrtc/common_audio/libvad.a $(obj).target/testing/libgmock.a $(obj).target/testing/libgtest.a $(obj).target/webrtc/test/libtest_support_main.a $(obj).target/webrtc/system_wrappers/source/libsystem_wrappers.a $(obj).target/webrtc/common_audio/libsignal_processing.a $(obj).target/webrtc/modules/libG711.a $(obj).target/webrtc/modules/libG722.a $(obj).target/webrtc/modules/libiLBC.a $(obj).target/webrtc/modules/libiSAC.a $(obj).target/webrtc/common_audio/libresampler.a $(obj).target/webrtc/modules/libwebrtc_opus.a $(obj).target/third_party/opus/libopus.a $(obj).target/testing/gtest_prod.stamp $(obj).target/webrtc/test/libtest_support.a

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := \
	-Wl,-z,now \
	-Wl,-z,relro \
	-pthread \
	-Wl,-z,noexecstack \
	-fPIC \
	-B$(builddir)/../../third_party/gold \
	--sysroot=/root/newdisk1/webrtc_no_peerconnection/trunk/arm-sysroot

LDFLAGS_Release := \
	-Wl,-z,now \
	-Wl,-z,relro \
	-pthread \
	-Wl,-z,noexecstack \
	-fPIC \
	-B$(builddir)/../../third_party/gold \
	--sysroot=/root/newdisk1/webrtc_no_peerconnection/trunk/arm-sysroot \
	-Wl,-O1 \
	-Wl,--as-needed \
	-Wl,--gc-sections

LIBS := \
	 \
	-lrt

$(builddir)/audio_coding_unittests: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(builddir)/audio_coding_unittests: LIBS := $(LIBS)
$(builddir)/audio_coding_unittests: LD_INPUTS := $(OBJS) $(obj).target/webrtc/modules/libaudio_coding_module.a $(obj).target/webrtc/modules/libCNG.a $(obj).target/webrtc/modules/libiSACFix.a $(obj).target/webrtc/modules/libNetEq.a $(obj).target/webrtc/modules/libNetEq4.a $(obj).target/webrtc/modules/libNetEq4TestTools.a $(obj).target/webrtc/modules/libneteq_unittest_tools.a $(obj).target/webrtc/modules/libPCM16B.a $(obj).target/webrtc/common_audio/libvad.a $(obj).target/testing/libgmock.a $(obj).target/testing/libgtest.a $(obj).target/webrtc/test/libtest_support_main.a $(obj).target/webrtc/system_wrappers/source/libsystem_wrappers.a $(obj).target/webrtc/common_audio/libsignal_processing.a $(obj).target/webrtc/modules/libG711.a $(obj).target/webrtc/modules/libG722.a $(obj).target/webrtc/modules/libiLBC.a $(obj).target/webrtc/modules/libiSAC.a $(obj).target/webrtc/common_audio/libresampler.a $(obj).target/webrtc/modules/libwebrtc_opus.a $(obj).target/third_party/opus/libopus.a $(obj).target/webrtc/test/libtest_support.a
$(builddir)/audio_coding_unittests: TOOLSET := $(TOOLSET)
$(builddir)/audio_coding_unittests: $(OBJS) $(obj).target/webrtc/modules/libaudio_coding_module.a $(obj).target/webrtc/modules/libCNG.a $(obj).target/webrtc/modules/libiSACFix.a $(obj).target/webrtc/modules/libNetEq.a $(obj).target/webrtc/modules/libNetEq4.a $(obj).target/webrtc/modules/libNetEq4TestTools.a $(obj).target/webrtc/modules/libneteq_unittest_tools.a $(obj).target/webrtc/modules/libPCM16B.a $(obj).target/webrtc/common_audio/libvad.a $(obj).target/testing/libgmock.a $(obj).target/testing/libgtest.a $(obj).target/webrtc/test/libtest_support_main.a $(obj).target/webrtc/system_wrappers/source/libsystem_wrappers.a $(obj).target/webrtc/common_audio/libsignal_processing.a $(obj).target/webrtc/modules/libG711.a $(obj).target/webrtc/modules/libG722.a $(obj).target/webrtc/modules/libiLBC.a $(obj).target/webrtc/modules/libiSAC.a $(obj).target/webrtc/common_audio/libresampler.a $(obj).target/webrtc/modules/libwebrtc_opus.a $(obj).target/third_party/opus/libopus.a $(obj).target/webrtc/test/libtest_support.a FORCE_DO_CMD
	$(call do_cmd,link)

all_deps += $(builddir)/audio_coding_unittests
# Add target alias
.PHONY: audio_coding_unittests
audio_coding_unittests: $(builddir)/audio_coding_unittests

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/audio_coding_unittests

