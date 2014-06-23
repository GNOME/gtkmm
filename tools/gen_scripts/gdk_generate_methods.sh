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

H2DEF_PY="$JHBUILD_SOURCES/glibmm/tools/defs_gen/h2def.py"
$H2DEF_PY "$PREFIX"/gtk+/gdk/*.h "$PREFIX"/gtk+/gdk/deprecated/*.h > "$OUT_DIR"/gdk_methods.defs
$H2DEF_PY "$PREFIX"/gdk-pixbuf/gdk-pixbuf/gdk*.h > "$OUT_DIR"/gdk_pixbuf_methods.defs
