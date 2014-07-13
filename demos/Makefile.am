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

check_PROGRAMS = pixbuf-demo gtk-demo/gtkmm-demo

pixbuf_demo_SOURCES = pixbuf-demo.cc

gtk_demo_gtkmm_demo_SOURCES =				\
	gtk-demo/demo-common.cc				\
	gtk-demo/demo-common.h				\
	gtk-demo/demos.h				\
	gtk-demo/demowindow.cc				\
	gtk-demo/demowindow.h				\
	gtk-demo/example_appwindow.cc			\
	gtk-demo/example_buttonbox.cc			\
	gtk-demo/example_change_display.cc		\
	gtk-demo/example_colorsel.cc			\
	gtk-demo/example_dialog.cc			\
	gtk-demo/example_drawingarea.cc			\
	gtk-demo/example_flowbox.cc			\
	gtk-demo/example_gestures.cc			\
	gtk-demo/example_headerbar.cc			\
	gtk-demo/example_icontheme.cc			\
	gtk-demo/example_iconview.cc			\
	gtk-demo/example_images.cc			\
	gtk-demo/example_menus.cc			\
	gtk-demo/example_overlay.cc			\
	gtk-demo/example_panes.cc			\
	gtk-demo/example_pixbufs.cc			\
	gtk-demo/example_sizegroup.cc			\
	gtk-demo/example_stack.cc			\
	gtk-demo/example_textview.cc			\
	gtk-demo/example_treeview_editable_cells.cc	\
	gtk-demo/example_treeview_liststore.cc		\
	gtk-demo/example_treeview_treestore.cc		\
	gtk-demo/main.cc				\
	gtk-demo/textwidget.cc				\
	gtk-demo/textwidget.h

dist_noinst_DATA =			\
	gtk-demo/alphatest.png		\
	gtk-demo/apple-red.png		\
	gtk-demo/background.jpg		\
	gtk-demo/floppybuddy.gif	\
	gtk-demo/gnome-applets.png	\
	gtk-demo/gnome-calendar.png	\
	gtk-demo/gnome-foot.png		\
	gtk-demo/gnome-fs-directory.png	\
	gtk-demo/gnome-fs-regular.png	\
	gtk-demo/gnome-gimp.png		\
	gtk-demo/gnome-gmush.png	\
	gtk-demo/gnome-gsame.png	\
	gtk-demo/gnu-keys.png		\
	gtk-demo/gtk-logo-rgb.gif

gdkmm_includes = -I$(top_builddir)/gdk $(if $(srcdir:.=),-I$(top_srcdir)/gdk)
gdkmm_ldadd    = $(top_builddir)/gdk/gdkmm/libgdkmm-$(GDKMM_API_VERSION).la

gtkmm_includes = -I$(top_builddir)/gtk $(if $(srcdir:.=),-I$(top_srcdir)/gtk)
gtkmm_ldadd    = $(top_builddir)/gtk/gtkmm/libgtkmm-$(GTKMM_API_VERSION).la

local_includes = -I$(top_builddir) $(gdkmm_includes) $(gtkmm_includes)
local_ldadd    = $(gdkmm_ldadd) $(gtkmm_ldadd)
local_cppflags = -DDEMOCODEDIR=\""$(democodedir)"\"

AM_CPPFLAGS = $(local_includes) $(GTHREAD_CFLAGS) $(GTKMM_CFLAGS) $(local_cppflags)
AM_CXXFLAGS = $(GTKMM_WXXFLAGS) -DGLIBMM_DISABLE_DEPRECATED -DGIOMM_DISABLE_DEPRECATED -DGTKMM_DISABLE_DEPRECATED -DGDKMM_DISABLE_DEPRECATED

pixbuf_demo_LDADD         = $(GTKMM_LIBS) $(local_ldadd)
gtk_demo_gtkmm_demo_LDADD = $(GTKMM_LIBS) $(local_ldadd)
