#!/bin/bash

# Note that JHBUILD_SOURCES should be defined to contain the path to the root
# of the jhbuild sources. The script assumes that it resides in the
# tools/gen_scripts/ directory and the defs file will be placed in gtk/src.

if [ -z "$JHBUILD_SOURCES" ]; then
  echo -e "JHBUILD_SOURCES must contain the path to the jhbuild sources."
  exit 1;
fi

PREFIX="$JHBUILD_SOURCES/gtk+"
ROOT_DIR="$(dirname "$0")/../.."
OUT_DIR="$ROOT_DIR/gtk/src"

ENUM_PL="$JHBUILD_SOURCES/glibmm/tools/enum.pl"
$ENUM_PL "$PREFIX"/gtk/*.h "$PREFIX"/gtk/deprecated/*.h > "$OUT_DIR"/gtk_enums.defs
