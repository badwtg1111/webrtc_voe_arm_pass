# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := protobuf_lite
DEFS_Debug := \
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
	'-DLIBPROTOBUF_EXPORTS' \
	'-DPROTOBUF_USE_DLLS' \
	'-DGOOGLE_PROTOBUF_NO_RTTI' \
	'-DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=1' \
	'-DWTF_USE_DYNAMIC_ANNOTATIONS=1' \
	'-D_DEBUG'

# Flags passed to all source files.
CFLAGS_Debug := \
	-pthread \
	-fno-exceptions \
	-fno-strict-aliasing \
	-Wno-unused-parameter \
	-pipe \
	-fPIC \
	-Wno-format \
	-Wno-unused-result \
	--sysroot=/usr/local/arm/4.4.1/arm-none-linux-gnueabi/libc \
	-O0 \
	-g

# Flags passed to only C files.
CFLAGS_C_Debug :=

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-fno-rtti \
	-Wno-deprecated \
	-Wno-abi

INCS_Debug := \
	-Ithird_party/protobuf \
	-Ithird_party/protobuf/src

DEFS_Release := \
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
	'-DLIBPROTOBUF_EXPORTS' \
	'-DPROTOBUF_USE_DLLS' \
	'-DGOOGLE_PROTOBUF_NO_RTTI' \
	'-DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER' \
	'-DNDEBUG' \
	'-DNVALGRIND' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=0'

# Flags passed to all source files.
CFLAGS_Release := \
	-pthread \
	-fno-exceptions \
	-fno-strict-aliasing \
	-Wno-unused-parameter \
	-pipe \
	-fPIC \
	-Wno-format \
	-Wno-unused-result \
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
	-Wno-deprecated \
	-Wno-abi

INCS_Release := \
	-Ithird_party/protobuf \
	-Ithird_party/protobuf/src

OBJS := \
	$(obj).target/$(TARGET)/third_party/protobuf/src/google/protobuf/stubs/atomicops_internals_x86_gcc.o \
	$(obj).target/$(TARGET)/third_party/protobuf/src/google/protobuf/stubs/atomicops_internals_x86_msvc.o \
	$(obj).target/$(TARGET)/third_party/protobuf/src/google/protobuf/unknown_field_set.o \
	$(obj).target/$(TARGET)/third_party/protobuf/src/google/protobuf/stubs/common.o \
	$(obj).target/$(TARGET)/third_party/protobuf/src/google/protobuf/stubs/once.o \
	$(obj).target/$(TARGET)/third_party/protobuf/src/google/protobuf/extension_set.o \
	$(obj).target/$(TARGET)/third_party/protobuf/src/google/protobuf/generated_message_util.o \
	$(obj).target/$(TARGET)/third_party/protobuf/src/google/protobuf/message_lite.o \
	$(obj).target/$(TARGET)/third_party/protobuf/src/google/protobuf/repeated_field.o \
	$(obj).target/$(TARGET)/third_party/protobuf/src/google/protobuf/wire_format_lite.o \
	$(obj).target/$(TARGET)/third_party/protobuf/src/google/protobuf/io/coded_stream.o \
	$(obj).target/$(TARGET)/third_party/protobuf/src/google/protobuf/io/zero_copy_stream.o \
	$(obj).target/$(TARGET)/third_party/protobuf/src/google/protobuf/io/zero_copy_stream_impl_lite.o

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
	

$(obj).target/third_party/protobuf/libprotobuf_lite.a: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/third_party/protobuf/libprotobuf_lite.a: LIBS := $(LIBS)
$(obj).target/third_party/protobuf/libprotobuf_lite.a: TOOLSET := $(TOOLSET)
$(obj).target/third_party/protobuf/libprotobuf_lite.a: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,alink_thin)

all_deps += $(obj).target/third_party/protobuf/libprotobuf_lite.a
# Add target alias
.PHONY: protobuf_lite
protobuf_lite: $(obj).target/third_party/protobuf/libprotobuf_lite.a

# Add target alias to "all" target.
.PHONY: all
all: protobuf_lite

