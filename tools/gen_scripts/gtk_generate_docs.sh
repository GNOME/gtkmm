#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts/ directory and
# the XML file will be placed in gtk/src.

source "$(dirname "$0")/init_generate.sh"

out_dir="$root_dir/gtk/src"

params="--with-properties --no-recursion"
if [ "$gtk_build_prefix" != "$gtk_source_prefix" ]; then
  gtk_build_dir="$gtk_build_prefix"/gtk
fi
for dir in "$gtk_source_prefix"/{gtk,gtk/deprecated} "$gtk_build_dir"; do
  if [ -d "$dir" ]; then
    params="$params -s $dir"
  fi
done

# Exclude gtkclipboard-quartz.c and gtkdnd-quartz.c. Function descriptions in
# those files can replace better descriptions in gtkclipboard.c and gtkdnd.c,
# if they are processed.
params="$params -x $gtk_source_prefix/gtk/gtkclipboard-quartz.c"
params="$params -x $gtk_source_prefix/gtk/gtkdnd-quartz.c"

"$gen_docs" $params > "$out_dir/gtk_docs.xml"
