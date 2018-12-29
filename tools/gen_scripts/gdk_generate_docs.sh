#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts/ directory and
# the XML file will be placed in gdk/src.

source "$(dirname "$0")/init_generate.sh"

out_dir="$root_dir/gdk/src"

params="--with-properties --no-recursion"
if [ "$gtk_build_prefix" != "$gtk_source_prefix" ]; then
  gtk_build_dir="$gtk_build_prefix"/gdk
fi
for dir in "$gtk_source_prefix"/{gdk,gdk/deprecated} "$gtk_build_dir" \
           "$pixbuf_source_prefix"/gdk-pixbuf "$pixbuf_build_prefix"/gdk-pixbuf; do
  if [ -d "$dir" ]; then
    params="$params -s $dir"
  fi
done

"$gen_docs" $params > "$out_dir/gdk_docs.xml"
