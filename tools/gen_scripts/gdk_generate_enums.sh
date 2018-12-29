#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts/ directory and
# the defs file will be placed in gdk/src.

source "$(dirname "$0")/init_generate.sh"

out_dir="$root_dir/gdk/src"

shopt -s extglob # Enable extended pattern matching
shopt -s nullglob # Skip a filename pattern that matches no file
# Process files whose names end with .h, but not with private.h.
# Exclude gtk+-3/gdk/gdkinternals.h.
"$gen_enums" "$gtk_source_prefix"/gdk/!(*private|gdkinternals).h "$gtk_source_prefix"/gdk/deprecated/!(*private).h > "$out_dir"/gdk_enums.defs
if [ "$gtk_build_prefix" != "$gtk_source_prefix" ]; then
  "$gen_enums" "$gtk_build_prefix"/gdk/*.h >> "$out_dir"/gdk_enums.defs
fi
"$gen_enums" "$pixbuf_source_prefix"/gdk-pixbuf/gdk!(*private).h \
             "$pixbuf_build_prefix"/gdk-pixbuf/*.h > "$out_dir"/gdk_pixbuf_enums.defs
