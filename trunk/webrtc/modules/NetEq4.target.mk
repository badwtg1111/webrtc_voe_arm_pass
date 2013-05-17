# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := NetEq4
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
	'-DWEBRTC_ARCH_ARM' \
	'-DWEBRTC_LINUX' \
	'-DWEBRTC_THREAD_RR' \
	'-DWEBRTC_CLOCK_TYPE_REALTIME' \
	'-DWEBRTC_CODEC_OPUS' \
	'-D__STDC_CONSTANT_MACROS' \
	'-D__STDC_FORMAT_MACROS' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=1' \
	'-DWTF_USE_DYNAMIC_ANNOTATIONS=1' \
	'-D_DEBUG'

# Flags passed to all source files.
CFLAGS_Debug := \
	-Werror \
	-pthread \
	-fno-exceptions \
	-fno-strict-aliasing \
	-Wall \
	-Wno-unused-parameter \
	-pipe \
	-fPIC \
	-Wextra \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc \
	-O0 \
	-g

# Flags passed to only C files.
CFLAGS_C_Debug :=

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-fno-rtti \
	-Wsign-compare \
	-Woverloaded-virtual \
	-Wno-abi

INCS_Debug := \
	-Iwebrtc \
	-I. \
	-I. \
	-Iwebrtc/modules/audio_coding/neteq4/interface \
	-Iwebrtc/modules/audio_coding/codecs/g711/include \
	-Iwebrtc/modules/audio_coding/codecs/g722/include \
	-Iwebrtc/modules/audio_coding/codecs/pcm16b/include \
	-Iwebrtc/modules/audio_coding/codecs/ilbc/interface \
	-Iwebrtc/modules/audio_coding/codecs/isac/main/interface \
	-Iwebrtc/modules/audio_coding/codecs/isac/fix/interface \
	-Iwebrtc/modules/audio_coding/codecs/cng/include \
	-Iwebrtc/common_audio/signal_processing/include \
	-Iwebrtc/common_audio/vad/include \
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
	'-DWEBRTC_ARCH_ARM' \
	'-DWEBRTC_LINUX' \
	'-DWEBRTC_THREAD_RR' \
	'-DWEBRTC_CLOCK_TYPE_REALTIME' \
	'-DWEBRTC_CODEC_OPUS' \
	'-D__STDC_CONSTANT_MACROS' \
	'-D__STDC_FORMAT_MACROS' \
	'-DNDEBUG' \
	'-DNVALGRIND' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=0' \
	'-D_FORTIFY_SOURCE=2'

# Flags passed to all source files.
CFLAGS_Release := \
	-Werror \
	-pthread \
	-fno-exceptions \
	-fno-strict-aliasing \
	-Wall \
	-Wno-unused-parameter \
	-pipe \
	-fPIC \
	-Wextra \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc \
	-O2 \
	-fno-ident \
	-fdata-sections \
	-ffunction-sections

# Flags passed to only C files.
CFLAGS_C_Release :=

# Flags passed to only C++ files.
CFLAGS_CC_Release := \
	-fno-rtti \
	-Wsign-compare \
	-Woverloaded-virtual \
	-Wno-abi

INCS_Release := \
	-Iwebrtc \
	-I. \
	-I. \
	-Iwebrtc/modules/audio_coding/neteq4/interface \
	-Iwebrtc/modules/audio_coding/codecs/g711/include \
	-Iwebrtc/modules/audio_coding/codecs/g722/include \
	-Iwebrtc/modules/audio_coding/codecs/pcm16b/include \
	-Iwebrtc/modules/audio_coding/codecs/ilbc/interface \
	-Iwebrtc/modules/audio_coding/codecs/isac/main/interface \
	-Iwebrtc/modules/audio_coding/codecs/isac/fix/interface \
	-Iwebrtc/modules/audio_coding/codecs/cng/include \
	-Iwebrtc/common_audio/signal_processing/include \
	-Iwebrtc/common_audio/vad/include \
	-Iwebrtc/system_wrappers/interface \
	-I/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc/usr/include

OBJS := \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/accelerate.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/audio_decoder_impl.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/audio_decoder.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/audio_multi_vector.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/audio_vector.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/background_noise.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/buffer_level_filter.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/comfort_noise.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/decision_logic.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/decision_logic_fax.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/decision_logic_normal.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/decoder_database.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/delay_manager.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/delay_peak_detector.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/dsp_helper.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/dtmf_buffer.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/dtmf_tone_generator.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/expand.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/merge.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/neteq_impl.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/neteq.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/statistics_calculator.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/normal.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/packet_buffer.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/payload_splitter.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/post_decode_vad.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/preemptive_expand.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/random_vector.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/rtcp.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/sync_buffer.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/timestamp_scaler.o \
	$(obj).target/$(TARGET)/webrtc/modules/audio_coding/neteq4/time_stretch.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

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
	--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc

LDFLAGS_Release := \
	-Wl,-z,now \
	-Wl,-z,relro \
	-pthread \
	-Wl,-z,noexecstack \
	-fPIC \
	-B$(builddir)/../../third_party/gold \
	--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc \
	-Wl,-O1 \
	-Wl,--as-needed \
	-Wl,--gc-sections

LIBS := \
	

$(obj).target/webrtc/modules/libNetEq4.a: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/webrtc/modules/libNetEq4.a: LIBS := $(LIBS)
$(obj).target/webrtc/modules/libNetEq4.a: TOOLSET := $(TOOLSET)
$(obj).target/webrtc/modules/libNetEq4.a: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,alink_thin)

all_deps += $(obj).target/webrtc/modules/libNetEq4.a
# Add target alias
.PHONY: NetEq4
NetEq4: $(obj).target/webrtc/modules/libNetEq4.a

# Add target alias to "all" target.
.PHONY: all
all: NetEq4

