
pixmap_files = \
	alphatest.png		\
	apple-red.png		\
	gnome-applets.png	\
	gnome-calendar.png	\
	gnome-foot.png		\
	gnome-gimp.png		\
	gnome-gmush.png		\
	gnome-gsame.png		\
	gnu-keys.png		\
	floppybuddy.gif		\
	gtk-logo-rgb.gif

EXTRA_DIST = $(pixmap_files)

#Build the executable, but don't install it.
noinst_PROGRAMS = demo

#Where to find the header files needed by the source files:
INCLUDES = -I$(top_builddir)/gtk   -I$(top_srcdir)/gtk   \
           -I$(top_builddir)/gdk   -I$(top_srcdir)/gdk   \
           -I$(top_builddir)/pango -I$(top_srcdir)/pango \
           -I$(top_builddir)/atk   -I$(top_srcdir)/atk \
           $(GTKMM_CFLAGS)

#The libraries that the executable needs to link against:
LIBS = $(top_builddir)/pango/pangomm/libpangomm-1.3.la \
       $(top_builddir)/atk/atkmm/libatkmm-1.3.la \
       $(top_builddir)/gdk/gdkmm/libgdkmm-2.3.la \
       $(top_builddir)/gtk/gtkmm/libgtkmm-2.3.la \
       $(GTKMM_LIBS)

#List of source files needed to build the executable:
demo_SOURCES = demowindow.h demowindow.cc main.cc demos.h textwidget.h textwidget.cc \
               example_appwindow.cc example_buttonbox.cc example_change_display.cc example_colorsel.cc \
               example_dialog.cc example_drawingarea.cc \
               example_images.cc example_menus.cc example_panes.cc example_pixbufs.cc example_sizegroup.cc \
               example_stockbrowser.cc example_uimanager.cc example_textview.cc \
               example_treeview_editable_cells.cc example_treeview_liststore.cc example_treeview_treestore.cc
