#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts/ directory and
# the XML file will be placed in gtk/src.

source "$(dirname "$0")/init_generate.sh"

out_dir="$root_dir/gtk/src"

params="--with-properties --no-recursion"
for dir in "$gtk_source_prefix"/{gtk,gtk/css,gtk/print,gtk/deprecated} "$gtk_build_prefix"/{gtk,gtk/css}; do
  if [ -d "$dir" ]; then
    params="$params -s $dir"
  fi
done

# Exclude gtkdnd-quartz.c. Function descriptions in gtkdnd-quartz.c can
# replace better descriptions in gtkdnd.c, if gtkdnd-quartz.c is processed.
params="$params -x $gtk_source_prefix/gtk/gtkdnd-quartz.c"

"$gen_docs" $params > "$out_dir/gtk_docs.xml"
