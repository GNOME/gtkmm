#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts directory
# and the defs files will be placed in gtk/src.
# It shall be executed from the tools/gen_scripts directory.

# To update the gtk_signals.defs file:
# 1. ./gtk_generate_extra_defs.sh
#    Generates gtk/src/gtk_signals.defs.orig and gtk/src/gtk_signals.defs.
#    If any hunks from the patch file fail to apply, apply them manually to the
#    gtk_signals.defs file, if required.
# 2. Optional: Remove gtk/src/gtk_signals.defs.orig.

# To update the gtk_signals.defs file and the patch file:
# 1. Like step 1 when updating only the gtk_signals.defs file.
# 2. Apply new patches manually to the gtk_signals.defs file.
# 3. ./gtk_generate_extra_defs.sh --make-patch
# 4. Like step 2 when updating only the gtk_signals.defs file.

source "$(dirname "$0")/init_generate.sh"

out_dir="$root_dir/gtk/src"
out_defs_file="$out_dir"/gtk_signals.defs

if [ $# -eq 0 ]
then
  # Without LC_ALL=C documentation (docs "xxx") may be translated in the .defs file.
  LC_ALL=C "$extra_defs_gen_dir"/generate_defs_gtk > "$out_defs_file"
  # patch version 2.7.5 does not like directory names.
  cd "$(dirname "$out_defs_file")"
  patch_options="--backup --version-control=simple --suffix=.orig"
  patch $patch_options "$(basename "$out_defs_file")" "$(basename "$out_defs_file").patch"
elif [ "$1" = "--make-patch" ]
then
  diff --unified=5 "$out_defs_file".orig "$out_defs_file" > "$out_defs_file".patch
else
  echo "Usage: $0 [--make-patch]"
  exit 1
fi

