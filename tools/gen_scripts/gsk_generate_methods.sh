#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts/ directory and
# the defs file will be placed in gsk/src.

source "$(dirname "$0")/init_generate.sh"

out_dir="$root_dir/gsk/src"

shopt -s extglob # Enable extended pattern matching
shopt -s nullglob # Skip a filename pattern that matches no file
# Process files whose names end with .h, but not with private.h.
"$gen_methods" "$gtk_source_prefix"/gsk/!(*private).h "$gtk_source_prefix"/gsk/deprecated/!(*private).h \
               "$gtk_build_prefix"/gsk/*.h > "$out_dir"/gsk_methods.defs

