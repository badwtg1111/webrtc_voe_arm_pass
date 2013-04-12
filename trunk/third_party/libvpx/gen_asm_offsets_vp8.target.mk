# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := gen_asm_offsets_vp8
### Rules for action "unpack_lib_posix":
quiet_cmd_third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_unpack_lib_posix = ACTION third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_unpack_lib_posix $@
cmd_third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_unpack_lib_posix = LD_LIBRARY_PATH=$(builddir)/lib.host:$(builddir)/lib.target:$$LD_LIBRARY_PATH; export LD_LIBRARY_PATH; cd third_party/libvpx; mkdir -p $(obj).$(TOOLSET)/gen_asm_offsets_vp8/geni; ../../third_party/libvpx/unpack_lib_posix.sh -d "$(obj).$(TOOLSET)/gen_asm_offsets_vp8/geni" -a "$(builddir)/libvpx_asm_offsets.a" -a "$(obj).$(TOOLSET)/third_party/libvpx/libvpx_asm_offsets.a" -a "$(obj).$(TOOLSET)/Source/WebKit/chromium/third_party/libvpx/libvpx_asm_offsets.a" -f asm_enc_offsets.o

$(obj).$(TOOLSET)/$(TARGET)/geni/asm_enc_offsets.o: obj := $(abs_obj)
$(obj).$(TOOLSET)/$(TARGET)/geni/asm_enc_offsets.o: builddir := $(abs_builddir)
$(obj).$(TOOLSET)/$(TARGET)/geni/asm_enc_offsets.o: TOOLSET := $(TOOLSET)
$(obj).$(TOOLSET)/$(TARGET)/geni/asm_enc_offsets.o: third_party/libvpx/unpack_lib_posix.sh FORCE_DO_CMD
	$(call do_cmd,third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_unpack_lib_posix)

all_deps += $(obj).$(TOOLSET)/$(TARGET)/geni/asm_enc_offsets.o
action_third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_unpack_lib_posix_outputs := $(obj).$(TOOLSET)/$(TARGET)/geni/asm_enc_offsets.o


### Generated for rule third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_obj_int_extract:
$(obj)/gen/third_party/libvpx/vp8_asm_enc_offsets.asm: obj := $(abs_obj)
$(obj)/gen/third_party/libvpx/vp8_asm_enc_offsets.asm: builddir := $(abs_builddir)
$(obj)/gen/third_party/libvpx/vp8_asm_enc_offsets.asm: TOOLSET := $(TOOLSET)
$(obj)/gen/third_party/libvpx/vp8_asm_enc_offsets.asm: $(obj).$(TOOLSET)/$(TARGET)/geni/asm_enc_offsets.o $(builddir)/libvpx_obj_int_extract third_party/libvpx/obj_int_extract.sh FORCE_DO_CMD
	$(call do_cmd,third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_obj_int_extract_0)

all_deps += $(obj)/gen/third_party/libvpx/vp8_asm_enc_offsets.asm
cmd_third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_obj_int_extract_0 = LD_LIBRARY_PATH=$(builddir)/lib.host:$(builddir)/lib.target:$$LD_LIBRARY_PATH; export LD_LIBRARY_PATH; cd third_party/libvpx; mkdir -p $(obj)/gen/third_party/libvpx; ../../third_party/libvpx/obj_int_extract.sh -e "$(builddir)/libvpx_obj_int_extract" -f gas -b "$(abspath $<)" -o "$(obj)/gen/third_party/libvpx/vp8_asm_enc_offsets.asm"
quiet_cmd_third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_obj_int_extract_0 = RULE third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_obj_int_extract_0 $@

rule_third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_obj_int_extract_outputs := \
	$(obj)/gen/third_party/libvpx/vp8_asm_enc_offsets.asm

### Finished generating for rule: third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_obj_int_extract

### Finished generating for all rules

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
	'-DDYNAMIC_ANNOTATIONS_ENABLED=1' \
	'-DWTF_USE_DYNAMIC_ANNOTATIONS=1' \
	'-D_DEBUG'

# Flags passed to all source files.
CFLAGS_Debug := \
	-fstack-protector \
	--param=ssp-buffer-size=4 \
	-pthread \
	-fno-exceptions \
	-fno-strict-aliasing \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-pipe \
	-fPIC \
	-Wno-format \
	-Wno-unused-result \
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
	-Wno-deprecated \
	-Wno-abi

INCS_Debug :=

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
	'-DNDEBUG' \
	'-DNVALGRIND' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=0'

# Flags passed to all source files.
CFLAGS_Release := \
	-fstack-protector \
	--param=ssp-buffer-size=4 \
	-pthread \
	-fno-exceptions \
	-fno-strict-aliasing \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-pipe \
	-fPIC \
	-Wno-format \
	-Wno-unused-result \
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
	-Wno-deprecated \
	-Wno-abi

INCS_Release :=

OBJS :=

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# Make sure our dependencies are built before any of us.
$(OBJS): | $(obj).target/third_party/libvpx/libvpx_asm_offsets.a $(builddir)/libvpx_obj_int_extract

# Make sure our actions/rules run before any of us.
$(OBJS): | $(action_third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_unpack_lib_posix_outputs) $(rule_third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_obj_int_extract_outputs)


### Rules for final target.
# Build our special outputs first.
$(obj).target/third_party/libvpx/gen_asm_offsets_vp8.stamp: | $(action_third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_unpack_lib_posix_outputs) $(rule_third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_obj_int_extract_outputs)

# Preserve order dependency of special output on deps.
$(action_third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_unpack_lib_posix_outputs) $(rule_third_party_libvpx_libvpx_gyp_gen_asm_offsets_vp8_target_obj_int_extract_outputs): | $(obj).target/third_party/libvpx/libvpx_asm_offsets.a $(builddir)/libvpx_obj_int_extract

$(obj).target/third_party/libvpx/gen_asm_offsets_vp8.stamp: TOOLSET := $(TOOLSET)
$(obj).target/third_party/libvpx/gen_asm_offsets_vp8.stamp: $(obj).target/third_party/libvpx/libvpx_asm_offsets.a $(builddir)/libvpx_obj_int_extract FORCE_DO_CMD
	$(call do_cmd,touch)

all_deps += $(obj).target/third_party/libvpx/gen_asm_offsets_vp8.stamp
# Add target alias
.PHONY: gen_asm_offsets_vp8
gen_asm_offsets_vp8: $(obj).target/third_party/libvpx/gen_asm_offsets_vp8.stamp

# Add target alias to "all" target.
.PHONY: all
all: gen_asm_offsets_vp8

