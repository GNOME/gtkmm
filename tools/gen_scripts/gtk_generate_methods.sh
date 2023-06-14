#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts/ directory and
# the defs file will be placed in gtk/src.

source "$(dirname "$0")/init_generate.sh"

out_dir="$root_dir/gtk/src"

shopt -s extglob # Enable extended pattern matching
shopt -s nullglob # Skip a filename pattern that matches no file
# Process files whose names start with gtk and end with .h, but not with private.h.
"$gen_methods" "$gtk_source_prefix"/gtk/gtk!(*private).h \
               "$gtk_source_prefix"/gtk/css/gtk!(*private).h \
               "$gtk_source_prefix"/gtk/print/gtk!(*private).h \
               "$gtk_source_prefix"/gtk/deprecated/gtk!(*private).h \
               "$gtk_build_prefix"/gtk/gtk*.h \
               "$gtk_build_prefix"/gtk/css/gtk*.h > "$out_dir"/gtk_methods.defs
