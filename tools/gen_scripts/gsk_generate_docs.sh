#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts/ directory and
# the XML file will be placed in gsk/src.

source "$(dirname "$0")/init_generate.sh"

out_dir="$root_dir/gsk/src"

params="--with-properties --no-recursion"
for dir in "$gtk_source_prefix"/{gsk,gsk/deprecated} "$gtk_build_prefix"/gsk; do
  if [ -d "$dir" ]; then
    params="$params -s $dir"
  fi
done

"$gen_docs" $params > "$out_dir/gsk_docs.xml"
