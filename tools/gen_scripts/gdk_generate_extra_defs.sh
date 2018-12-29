#!/bin/bash

# The script assumes that it resides in the tools/gen_scripts directory
# and the defs file will be placed in gdk/src.

source "$(dirname "$0")/init_generate.sh"

out_dir="$root_dir/gdk/src"

# Without LC_ALL=C documentation (docs "xxx") may be translated in the .defs file.
LC_ALL=C "$extra_defs_gen_dir"/generate_defs_gdk > "$out_dir"/gdk_signals.defs

