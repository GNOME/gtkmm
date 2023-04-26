#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts/ directory and
# the XML file will be placed in gdk/src.

source "$(dirname "$0")/init_generate.sh"

out_dir="$root_dir/gdk/src"

params="--with-properties --no-recursion"
for dir in "$gtk_source_prefix"/{gdk,gdk/deprecated} "$gtk_build_prefix"/gdk \
           "$pixbuf_source_prefix"/gdk-pixbuf "$pixbuf_build_prefix"/gdk-pixbuf \
           "$graphene_source_prefix"/src "$graphene_build_prefix"/src; do
  if [ -d "$dir" ]; then
    params="$params -s $dir"
  fi
done

"$gen_docs" $params > "$out_dir/gdk_docs.xml"
