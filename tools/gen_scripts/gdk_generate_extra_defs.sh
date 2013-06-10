#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts directory
# and the defs file will be placed in gdk/src.

ROOT_DIR="$(dirname "$0")/../.."
GEN_DIR="$ROOT_DIR/tools/extra_defs_gen"
OUT_DIR="$ROOT_DIR/gdk/src"

"$GEN_DIR"/generate_defs_gdk > "$OUT_DIR"/gdk_signals.defs

