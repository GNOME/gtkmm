#!/bin/bash

# Note that JHBUILD_SOURCES should be defined to contain the path to the root
# of the jhbuild sources. The script assumes that it resides in the
# tools/gen_scripts/ directory and the defs file will be placed in gdk/src.

if [ -z "$JHBUILD_SOURCES" ]; then
  echo -e "JHBUILD_SOURCES must contain the path to the jhbuild sources."
  exit 1;
fi

PREFIX="$JHBUILD_SOURCES"
ROOT_DIR="$(dirname "$0")/../.."
OUT_DIR="$ROOT_DIR/gdk/src"

shopt -s extglob # Enable extended pattern matching
ENUM_PL="$JHBUILD_SOURCES/glibmm/tools/enum.pl"
# Process files whose names end with .h, but not with private.h.
# Exclude gtk+-3/gdk/gdkinternals.h.
$ENUM_PL "$PREFIX"/gtk+-3/gdk/!(*private|gdkinternals).h "$PREFIX"/gtk+-3/gdk/deprecated/!(*private).h > "$OUT_DIR"/gdk_enums.defs
$ENUM_PL "$PREFIX"/gdk-pixbuf/gdk-pixbuf/gdk!(*private).h \
         "$PREFIX"/gdk-pixbuf/build/gdk-pixbuf/*.h > "$OUT_DIR"/gdk_pixbuf_enums.defs
