# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := audioproc_debug_proto
### Generated for rule trunk_webrtc_modules_modules_gyp_audioproc_debug_proto_target_genproto:
$(builddir)/pyproto/webrtc/audio_processing/debug_pb2.py: obj := $(abs_obj)
$(builddir)/pyproto/webrtc/audio_processing/debug_pb2.py: builddir := $(abs_builddir)
$(builddir)/pyproto/webrtc/audio_processing/debug_pb2.py: TOOLSET := $(TOOLSET)
$(builddir)/pyproto/webrtc/audio_processing/debug_pb2.py: webrtc/modules/audio_processing/debug.proto $(builddir)/protoc FORCE_DO_CMD
	$(call do_cmd,trunk_webrtc_modules_modules_gyp_audioproc_debug_proto_target_genproto_0)
$(obj)/gen/protoc_out/webrtc/audio_processing/debug.pb.cc $(obj)/gen/protoc_out/webrtc/audio_processing/debug.pb.h: $(builddir)/pyproto/webrtc/audio_processing/debug_pb2.py
$(obj)/gen/protoc_out/webrtc/audio_processing/debug.pb.cc $(obj)/gen/protoc_out/webrtc/audio_processing/debug.pb.h: ;

all_deps += $(builddir)/pyproto/webrtc/audio_processing/debug_pb2.py $(obj)/gen/protoc_out/webrtc/audio_processing/debug.pb.cc $(obj)/gen/protoc_out/webrtc/audio_processing/debug.pb.h
cmd_trunk_webrtc_modules_modules_gyp_audioproc_debug_proto_target_genproto_0 = LD_LIBRARY_PATH=$(builddir)/lib.host:$(builddir)/lib.target:$$LD_LIBRARY_PATH; export LD_LIBRARY_PATH; cd webrtc/modules; mkdir -p $(obj)/gen/protoc_out/webrtc/audio_processing $(builddir)/pyproto/webrtc/audio_processing; "$(builddir)/protoc" "--proto_path=audio_processing" "audio_processing/debug$(suffix $<)" "--cpp_out=$(obj)/gen/protoc_out/webrtc/audio_processing" "--python_out=$(builddir)/pyproto/webrtc/audio_processing"
quiet_cmd_trunk_webrtc_modules_modules_gyp_audioproc_debug_proto_target_genproto_0 = RULE trunk_webrtc_modules_modules_gyp_audioproc_debug_proto_target_genproto_0 $@

rule_trunk_webrtc_modules_modules_gyp_audioproc_debug_proto_target_genproto_outputs := \
	$(builddir)/pyproto/webrtc/audio_processing/debug_pb2.py \
	$(obj)/gen/protoc_out/webrtc/audio_processing/debug.pb.cc \
	$(obj)/gen/protoc_out/webrtc/audio_processing/debug.pb.h

### Finished generating for rule: trunk_webrtc_modules_modules_gyp_audioproc_debug_proto_target_genproto

### Finished generating for all rules

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
	'-DPROTOBUF_USE_DLLS' \
	'-DGOOGLE_PROTOBUF_NO_RTTI' \
	'-DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER' \
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
	-I$(obj)/gen/protoc_out \
	-Ithird_party/protobuf \
	-Ithird_party/protobuf/src

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
	'-DPROTOBUF_USE_DLLS' \
	'-DGOOGLE_PROTOBUF_NO_RTTI' \
	'-DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER' \
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
	-I$(obj)/gen/protoc_out \
	-Ithird_party/protobuf \
	-Ithird_party/protobuf/src

OBJS := \
	$(obj).target/$(TARGET)/gen/protoc_out/webrtc/audio_processing/debug.pb.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# Make sure our dependencies are built before any of us.
$(OBJS): | $(builddir)/protoc

# Make sure our actions/rules run before any of us.
$(OBJS): | $(rule_trunk_webrtc_modules_modules_gyp_audioproc_debug_proto_target_genproto_outputs)

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
# Build our special outputs first.
$(obj).target/webrtc/modules/libaudioproc_debug_proto.a: | $(rule_trunk_webrtc_modules_modules_gyp_audioproc_debug_proto_target_genproto_outputs)

# Preserve order dependency of special output on deps.
$(rule_trunk_webrtc_modules_modules_gyp_audioproc_debug_proto_target_genproto_outputs): | $(builddir)/protoc

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
	

$(obj).target/webrtc/modules/libaudioproc_debug_proto.a: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/webrtc/modules/libaudioproc_debug_proto.a: LIBS := $(LIBS)
$(obj).target/webrtc/modules/libaudioproc_debug_proto.a: TOOLSET := $(TOOLSET)
$(obj).target/webrtc/modules/libaudioproc_debug_proto.a: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,alink_thin)

all_deps += $(obj).target/webrtc/modules/libaudioproc_debug_proto.a
# Add target alias
.PHONY: audioproc_debug_proto
audioproc_debug_proto: $(obj).target/webrtc/modules/libaudioproc_debug_proto.a

# Add target alias to "all" target.
.PHONY: all
all: audioproc_debug_proto

