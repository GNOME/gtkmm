#!/bin/bash

# Note that 
# JHBUILD_SOURCES should be defined to contain the path to the root of the
# jhbuild sources. The defs files will be placed in gdk/src.

if [ -z "$JHBUILD_SOURCES" ]; then
  echo -e "JHBUILD_SOURCES must contain the path to the jhbuild sources."
  exit 1;
fi

PREFIX="$JHBUILD_SOURCES/gtk+"
ROOT_DIR="$(dirname "$0")/../.."
OUT_DIR="$ROOT_DIR/gdk/src"

ENUM_PL="$JHBUILD_SOURCES/glibmm/tools/enum.pl"
$ENUM_PL "$PREFIX"/gdk/*.h > "$OUT_DIR"/gdk_enums.defs
