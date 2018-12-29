#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts/ directory and
# the defs file will be placed in gtk/src.

source "$(dirname "$0")/init_generate.sh"

out_dir="$root_dir/gtk/src"

shopt -s extglob # Enable extended pattern matching
shopt -s nullglob # Skip a filename pattern that matches no file
# Process files whose names end with .h, but not with private.h.
"$gen_methods" "$gtk_source_prefix"/gtk/!(*private).h "$gtk_source_prefix"/gtk/deprecated/!(*private).h > "$out_dir"/gtk_methods.defs
if [ "$gtk_build_prefix" != "$gtk_source_prefix" ]; then
  "$gen_methods" "$gtk_build_prefix"/gtk/*.h >> "$out_dir"/gtk_methods.defs
fi
