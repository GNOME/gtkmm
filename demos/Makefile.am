## Copyright (c) 2009  Openismus GmbH  <http://www.openismus.com/>
##
## This file is part of gtkmm.
##
## gtkmm is free software: you can redistribute it and/or modify it
## under the terms of the GNU Lesser General Public License as published
## by the Free Software Foundation, either version 2.1 of the License,
## or (at your option) any later version.
##
## gtkmm is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
## See the GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this library.  If not, see <http://www.gnu.org/licenses/>.

AUTOMAKE_OPTIONS = subdir-objects

check_PROGRAMS = gtk-demo/gtkmm-demo

## Don't distribute demo_resources.c. It's big, and it's built with
## glib-compile-resources, which is part of glib.
nodist_gtk_demo_gtkmm_demo_SOURCES = gtk-demo/demo_resources.c
dist_gtk_demo_gtkmm_demo_SOURCES = \
  gtk-demo/demos.h \
  gtk-demo/demowindow.cc \
  gtk-demo/demowindow.h \
  gtk-demo/main.cc \
  gtk-demo/textwidget.cc \
  gtk-demo/textwidget.h \
  $(GTK_DEMOS)

dist_noinst_DATA = \
  gtk-demo/demo.gresource.xml \
  $(GTK_DEMO_RESOURCES)

GTK_DEMOS = \
  gtk-demo/example_appwindow.cc \
  gtk-demo/example_builder.cc \
  gtk-demo/example_colorsel.cc \
  gtk-demo/example_dialog.cc \
  gtk-demo/example_drawingarea.cc \
  gtk-demo/example_dropdown.cc \
  gtk-demo/example_flowbox.cc \
  gtk-demo/example_gestures.cc \
  gtk-demo/example_glarea.cc \
  gtk-demo/example_gridview.cc \
  gtk-demo/example_headerbar.cc \
  gtk-demo/example_iconbrowser.cc \
  gtk-demo/example_images.cc \
  gtk-demo/example_listview_applauncher.cc \
  gtk-demo/example_listview_columnview.cc \
  gtk-demo/example_listview_editable_cells.cc \
  gtk-demo/example_listview_liststore.cc \
  gtk-demo/example_listview_treelist.cc \
  gtk-demo/example_overlay.cc \
  gtk-demo/example_panes.cc \
  gtk-demo/example_pixbufs.cc \
  gtk-demo/example_shortcuts.cc \
  gtk-demo/example_sizegroup.cc \
  gtk-demo/example_stack.cc \
  gtk-demo/example_stacksidebar.cc \
  gtk-demo/example_textview.cc

GTK_DEMO_RESOURCES = \
  gtk-demo/example_builder.ui \
  gtk-demo/example_shortcuts.ui \
  gtk-demo/example_shortcuts_boxes.ui \
  gtk-demo/example_shortcuts_builder.ui \
  gtk-demo/example_shortcuts_clocks.ui \
  gtk-demo/example_shortcuts_gedit.ui \
  gtk-demo/alphatest.png \
  gtk-demo/apple-red.png \
  gtk-demo/background.jpg \
  gtk-demo/floppybuddy.gif \
  gtk-demo/glarea-gl.fs.glsl \
  gtk-demo/glarea-gl.vs.glsl \
  gtk-demo/glarea-gles.fs.glsl \
  gtk-demo/glarea-gles.vs.glsl \
  gtk-demo/gnome-applets.png \
  gtk-demo/gnome-calendar.png \
  gtk-demo/gnome-foot.png \
  gtk-demo/gnome-fs-directory.png \
  gtk-demo/gnome-fs-regular.png \
  gtk-demo/gnome-gimp.png \
  gtk-demo/gnome-gmush.png \
  gtk-demo/gnome-gsame.png \
  gtk-demo/gnu-keys.png \
  gtk-demo/gtk-logo-rgb.png \
  gtk-demo/gtk-logo.webm

DISTCLEANFILES = gtk-demo/demo_resources.c

gtk-demo/demo_resources.c: gtk-demo/demo.gresource.xml $(GTK_DEMO_RESOURCES) $(GTK_DEMOS)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(dir $<) --generate-source $<

gdkmm_includes = -I$(top_builddir)/gdk $(if $(srcdir:.=),-I$(top_srcdir)/gdk)
gdkmm_ldadd    =

gskmm_includes = -I$(top_builddir)/gsk $(if $(srcdir:.=),-I$(top_srcdir)/gsk)
gskmm_ldadd    =

gtkmm_includes = -I$(top_builddir)/gtk $(if $(srcdir:.=),-I$(top_srcdir)/gtk)
gtkmm_ldadd    = $(top_builddir)/gtk/gtkmm/libgtkmm-$(GTKMM_API_VERSION).la

local_includes = -I$(top_builddir) $(gdkmm_includes) $(gskmm_includes) $(gtkmm_includes)
local_ldadd    = $(gdkmm_ldadd) $(gskmm_ldadd) $(gtkmm_ldadd)
local_cppflags = -DDEMOCODEDIR=\""$(democodedir)"\"

AM_CPPFLAGS = $(local_includes) $(GTHREAD_CFLAGS) $(GTKMM_CFLAGS) $(local_cppflags)
AM_CXXFLAGS = $(GTKMM_WXXFLAGS) -DGLIBMM_DISABLE_DEPRECATED -DGIOMM_DISABLE_DEPRECATED -DGDKMM_DISABLE_DEPRECATED -DGSKMM_DISABLE_DEPRECATED -DGTKMM_DISABLE_DEPRECATED

gtk_demo_gtkmm_demo_CPPFLAGS = $(AM_CPPFLAGS) $(GTKMM_DEMOS_EXTRA_CFLAGS)
gtk_demo_gtkmm_demo_LDADD = $(GTKMM_LIBS) $(GTKMM_DEMOS_EXTRA_LIBS) $(local_ldadd)
