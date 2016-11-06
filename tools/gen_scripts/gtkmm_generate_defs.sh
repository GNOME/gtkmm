#!/bin/sh

if [ -z "$GTKMM_DIR" ]; then
  echo -e "GTKMM_DIR must contain the path to the gtkmm repository."
  exit 1;
fi

function patch_directory {
    PATCH_OPTIONS="--backup --version-control=simple --suffix=.orig"
    for patch_file in $1/*.patch;
    do
	orig_file=$(echo $patch_file | sed s/.patch$//)
	patch $PATCH_OPTIONS $orig_file $patch_file
    done
}

MMGIRGEN_PATH=mmgirgenerator

############## Gdk ###############
# Gdk enums
$MMGIRGEN_PATH Gdk-3.0 GdkPixbuf-2.0 \
	       --namespace=Gdk \
	       --namespace-mapping=GdkPixbuf:Gdk \
	       --print-enum > $GTKMM_DIR/gdk/src/gdk_enums.defs

#Gdk signals & properties
$MMGIRGEN_PATH Gdk-3.0 GdkPixbuf-2.0 \
	       --namespace=Gdk \
	       --namespace-mapping=GdkPixbuf:Gdk \
	       --print-signal\
	       --print-property > $GTKMM_DIR/gdk/src/gdk_signals.defs

patch_directory $GTKMM_DIR/gdk/src


############## Gtk ###############
# Gtk enums
$MMGIRGEN_PATH Gtk-3.0 \
    --namespace=Gtk \
    --print-enum > $GTKMM_DIR/gtk/src/gtk_enums.defs

#Gtk signals & properties
$MMGIRGEN_PATH Gtk-3.0 \
    --namespace=Gtk \
    --print-signal\
    --print-property > $GTKMM_DIR/gtk/src/gtk_signals.defs

patch_directory $GTKMM_DIR/gtk/src
