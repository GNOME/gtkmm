#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts/ directory and
# the defs file will be placed in gdk/src.

source "$(dirname "$0")/init_generate.sh"

out_dir="$root_dir/gdk/src"

shopt -s extglob # Enable extended pattern matching
shopt -s nullglob # Skip a filename pattern that matches no file
# Process files whose names start with gdk and end with .h, but not with private.h.
# Exclude gtk/gdk/gdkinternals.h.
"$gen_enums" "$gtk_source_prefix"/gdk/gdk!(*private|internals).h "$gtk_source_prefix"/gdk/deprecated/!(*private).h \
             "$gtk_build_prefix"/gdk/gdk*.h > "$out_dir"/gdk_enums.defs
"$gen_enums" "$pixbuf_source_prefix"/gdk-pixbuf/gdk!(*private).h \
             "$pixbuf_build_prefix"/gdk-pixbuf/gdk*.h > "$out_dir"/gdk_pixbuf_enums.defs
