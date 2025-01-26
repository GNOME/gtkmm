#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts/ directory and
# the defs file will be placed in gdk/src.

# To update the gdk_methods.defs file:
# 1. ./gdk_generate_methods.sh
#    Generates gdk_methods.defs.orig and gdk_methods.defs.
#    If any hunks from the patch file fail to apply, apply them manually to the
#    gdk_methods.defs file, if required.
# 2. Optional: Remove gdk_methods.defs.orig.

# To update the gdk_methods.defs file and the patch file:
# 1. Like step 1 when updating only the gdk_methods.defs file.
# 2. Apply new patches manually to the gdk_methods.defs file.
# 3. ./gdk_generate_methods.sh --make-patch
# 4. Like step 2 when updating only the gdk_methods.defs files.

source "$(dirname "$0")/init_generate.sh"

out_dir="$root_dir/gdk/src"

shopt -s extglob # Enable extended pattern matching
shopt -s nullglob # Skip a filename pattern that matches no file
if [ $# -eq 0 ]
then
  # Process files whose names start with gdk and end with .h, but not with private.h.
  # Exclude gtk/gdk/gdkinternals.h and gtk/gdk/gdkcolordefs.h.
  "$gen_methods" "$gtk_source_prefix"/gdk/gdk!(*private|internals|colordefs).h "$gtk_source_prefix"/gdk/deprecated/!(*private).h \
                 "$gtk_build_prefix"/gdk/gdk*.h > "$out_dir"/gdk_methods.defs
  "$gen_methods" "$pixbuf_source_prefix"/gdk-pixbuf/gdk!(*private).h \
                 "$pixbuf_build_prefix"/gdk-pixbuf/gdk*.h > "$out_dir"/gdk_pixbuf_methods.defs
  "$gen_methods" "$graphene_source_prefix"/include/graphene-*.h \
                 "$graphene_build_prefix"/include/graphene-*.h > "$out_dir"/gdk_graphene_methods.defs
  # patch version 2.7.5 does not like directory names.
  cd "$out_dir"
  patch_options="--backup --version-control=simple --suffix=.orig"
  patch $patch_options gdk_methods.defs gdk_methods.defs.patch
elif [ "$1" = "--make-patch" ]
then
  out_dir_file="$out_dir"/gdk_methods.defs
  diff --unified=5 "$out_dir_file".orig "$out_dir_file" > "$out_dir_file".patch
else
  echo "Usage: $0 [--make-patch]"
  exit 1
fi
