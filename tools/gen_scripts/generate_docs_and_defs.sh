#!/bin/bash

# Generate all docs.xml and .defs files, either for gdk or gtk or (default) both.
# This script shall be executed from the tools/gen_scripts directory.

if [ $# -eq 0 ]
then
  GENERATE_GDK_FILES="yes"
  GENERATE_GTK_FILES="yes"
elif [ "$1" = "--gdk" ]
then
  GENERATE_GDK_FILES="yes"
  GENERATE_GTK_FILES="no"
elif [ "$1" = "--gtk" ]
then
  GENERATE_GDK_FILES="no"
  GENERATE_GTK_FILES="yes"
else
  echo "Usage: $0 [[--gdk | --gtk]]"
  exit 1
fi

if [ "$GENERATE_GDK_FILES" = "yes" ]
then
  echo === ./gdk_generate_docs.sh ===
  ./gdk_generate_docs.sh
  echo === ./gdk_generate_enums.sh ===
  ./gdk_generate_enums.sh
  echo === ./gdk_generate_extra_defs.sh ===
  ./gdk_generate_extra_defs.sh
  echo === ./gdk_generate_methods.sh ===
  ./gdk_generate_methods.sh
fi

if [ "$GENERATE_GTK_FILES" = "yes" ]
then
  if [ "$GENERATE_GDK_FILES" = "yes" ]
  then
    echo
  fi

  echo === ./gtk_generate_docs.sh ===
  ./gtk_generate_docs.sh
  echo === ./gtk_generate_enums.sh ===
  ./gtk_generate_enums.sh
  echo === ./gtk_generate_extra_defs.sh ===
  ./gtk_generate_extra_defs.sh
  echo === ./gtk_generate_methods.sh ===
  ./gtk_generate_methods.sh
fi
