#!/bin/bash

# This file is part of gtkmm.
# Initializes some variables for the scripts that generate docs and defs files.
# Not intented to be called directly from the command line.

# Global environment variables:
# GMMPROC_GEN_SOURCE_DIR  Top directory where source files are searched for.
#                         Default value: $(dirname "$0")/../../..
#                         i.e. 3 levels above this file.
# GMMPROC_GEN_BUILD_DIR   Top directory where built files are searched for.
#                         Default value: $GMMPROC_GEN_SOURCE_DIR
#
# If you use jhbuild, you can set these environment variables equal to jhbuild's
# configuration variables checkoutroot and buildroot, respectively.
# Usually you can leave GMMPROC_GEN_SOURCE_DIR undefined.
# If you have set buildroot=None, GMMPROC_GEN_BUILD_DIR can also be undefined.

# Root directory of gtkmm source files.
root_dir="$(dirname "$0")/../.."

# Where to search for source files.
if [ -z "$GMMPROC_GEN_SOURCE_DIR" ]; then
  GMMPROC_GEN_SOURCE_DIR="$root_dir/.."
fi

# Where to search for built files.
if [ -z "$GMMPROC_GEN_BUILD_DIR" ]; then
  GMMPROC_GEN_BUILD_DIR="$GMMPROC_GEN_SOURCE_DIR"
fi

# Scripts in glibmm. These are source files.
gen_docs="$GMMPROC_GEN_SOURCE_DIR/glibmm/tools/defs_gen/docextract_to_xml.py"
gen_methods="$GMMPROC_GEN_SOURCE_DIR/glibmm/tools/defs_gen/h2def.py"
gen_enums="$GMMPROC_GEN_SOURCE_DIR/glibmm/tools/enum.pl"

# Where to find executables that generate extra defs (signals and properties).
# gtkmm is built with autotools.
# autotools support, but don't require, non-source-dir builds.
extra_defs_gen_dir="$GMMPROC_GEN_BUILD_DIR/gtkmm/tools/extra_defs_gen"

gtk_source_prefix="$GMMPROC_GEN_SOURCE_DIR/gtk"
gtk_build_prefix="$GMMPROC_GEN_BUILD_DIR/gtk"
pixbuf_source_prefix="$GMMPROC_GEN_SOURCE_DIR/gdk-pixbuf"
pixbuf_build_prefix="$GMMPROC_GEN_BUILD_DIR/gdk-pixbuf"
graphene_source_prefix="$GMMPROC_GEN_SOURCE_DIR/graphene"
graphene_build_prefix="$GMMPROC_GEN_BUILD_DIR/graphene"
if [ "$GMMPROC_GEN_SOURCE_DIR" == "$GMMPROC_GEN_BUILD_DIR" ]; then
  # gtk and gdk-pixbuf are built with meson, which requires non-source-dir builds.
  # This is what jhbuild does, if neccesary, to force non-source-dir builds.
  gtk_build_prefix="$gtk_build_prefix/build"
  pixbuf_build_prefix="$pixbuf_build_prefix/build"
  graphene_build_prefix="$graphene_build_prefix/build"
fi
