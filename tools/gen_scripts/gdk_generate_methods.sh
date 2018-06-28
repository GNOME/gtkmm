#!/bin/bash

# Note that JHBUILD_SOURCES should be defined to contain the path to the root
# of the jhbuild sources. The script assumes that it resides in the
# tools/gen_scripts/ directory and the defs file will be placed in gdk/src.

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

if [ -z "$JHBUILD_SOURCES" ]; then
  echo -e "JHBUILD_SOURCES must contain the path to the jhbuild sources."
  exit 1;
fi

PREFIX="$JHBUILD_SOURCES"
ROOT_DIR="$(dirname "$0")/../.."
OUT_DIR="$ROOT_DIR/gdk/src"

shopt -s extglob # Enable extended pattern matching
shopt -s nullglob # Skip a filename pattern that matches no file
if [ $# -eq 0 ]
then
  H2DEF_PY="$JHBUILD_SOURCES/glibmm/tools/defs_gen/h2def.py"
  # Process files whose names end with .h, but not with private.h.
  # Exclude gtk+/gdk/gdkinternals.h.
  $H2DEF_PY "$PREFIX"/gtk+/gdk/!(*private|gdkinternals).h "$PREFIX"/gtk+/gdk/deprecated/!(*private).h \
            "$PREFIX"/gtk+/build/gdk/*.h > "$OUT_DIR"/gdk_methods.defs
  $H2DEF_PY "$PREFIX"/gdk-pixbuf/gdk-pixbuf/gdk!(*private).h \
            "$PREFIX"/gdk-pixbuf/build/gdk-pixbuf/*.h > "$OUT_DIR"/gdk_pixbuf_methods.defs
  # patch version 2.7.5 does not like directory names.
  cd "$OUT_DIR"
  PATCH_OPTIONS="--backup --version-control=simple --suffix=.orig"
  patch $PATCH_OPTIONS gdk_methods.defs gdk_methods.defs.patch
elif [ "$1" = "--make-patch" ]
then
  OUT_DIR_FILE="$OUT_DIR"/gdk_methods.defs
  diff --unified=5 "$OUT_DIR_FILE".orig "$OUT_DIR_FILE" > "$OUT_DIR_FILE".patch
else
  echo "Usage: $0 [--make-patch]"
  exit 1
fi
