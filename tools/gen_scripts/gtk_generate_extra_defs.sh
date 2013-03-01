#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts directory
# and the defs files will be placed in gtk/src.

ROOT_DIR="$(dirname "$0")/../.."
GEN_DIR="$ROOT_DIR/tools/extra_defs_gen"
OUT_DIR="$ROOT_DIR/gtk/src"

"$GEN_DIR"/generate_defs_gtk > "$OUT_DIR"/gtk_signals.defs
patch "$OUT_DIR"/gtk_signals.defs "$OUT_DIR"/gtk_signals.defs.patch

