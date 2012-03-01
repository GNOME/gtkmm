#!/bin/bash

# Note that h2def.py should be in PATH for this script to work and
# JHBUILD_SOURCES should be defined to contain the path to the root of the
# jhbuild sources.  The script assumes that it resides in the tools/gen_scripts
# directory and the defs files will be placed in gdk/src.

if [ -z "$JHBUILD_SOURCES" -o ! -x "`which h2def.py`" ]; then
  echo -e "JHBUILD_SOURCES must contain the path to the jhbuild sources and \
h2def.py\nneeds to be executable and in PATH."
  exit 1;
fi

PREFIX="$JHBUILD_SOURCES/gtk+"
ROOT_DIR="$(dirname "$0")/../.."
OUT_DIR="$ROOT_DIR/gdk/src"

h2def.py "$PREFIX"/gdk/*.h > "$OUT_DIR"/gdk_methods.defs
