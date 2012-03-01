#!/bin/bash

# Note that enum.pl should be in PATH for this script to work and
# JHBUILD_SOURCES should be defined to contain the path to the root of the
# jhbuild sources.  The script assumes that it resides in the tools/gen_scripts
# directory and the defs files will be placed in gtk/src.

if [ -z "$JHBUILD_SOURCES" -o ! -x "`which enum.pl`" ]; then
  echo -e "JHBUILD_SOURCES must contain the path to the jhbuild sources and \
enum.pl\nneeds to be executable and in PATH."
  exit 1;
fi

PREFIX="$JHBUILD_SOURCES/gtk+"
ROOT_DIR="$(dirname "$0")/../.."
OUT_DIR="$ROOT_DIR/gtk/src"

enum.pl "$PREFIX"/gtk/*.h "$PREFIX"/gtk/deprecated/*.h > "$OUT_DIR"/gtk_enums.defs
