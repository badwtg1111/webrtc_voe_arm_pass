# This file is generated by gyp; do not edit.

export builddir_name ?= ./webrtc/tools/out
.PHONY: all
all:
	$(MAKE) -C ../.. command_line_parser frame_editing_lib frame_editor tools_unittests rgba_to_i420_converter video_quality_analysis psnr_ssim_analyzer frame_analyzer
