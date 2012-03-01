#!/bin/bash

# Note that docextract_to_xml.py should be in PATH for this script to work and
# JHBUILD_SOURCES should be defined to contain the path to the root of the
# jhbuild sources.  The script assumes that it resides in the tools/gen_scripts
# directory and the XML file will be placed in gtk/src.

if [ -z "$JHBUILD_SOURCES" -o ! -x "`which docextract_to_xml.py`" ]; then
  echo -e "JHBUILD_SOURCES must contain path to jhbuild sources and \
docextract_to_xml.py\nneeds to be executable and in PATH."
  exit 1;
fi

PREFIX="$JHBUILD_SOURCES"
ROOT_DIR="$(dirname "$0")/../.."
OUT_DIR="$ROOT_DIR/gtk/src"

for dir in "$PREFIX"/gtk+/gtk; do
  PARAMS="$PARAMS -s $dir"
done

docextract_to_xml.py $PARAMS > "$OUT_DIR/gtk_docs.xml"
