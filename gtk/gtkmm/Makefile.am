## Copyright (c) 2001
## The gtkmm development team.

SUBDIRS			= private

sublib_name		= gtkmm
sublib_namespace	= Gtk
sublib_cflags		= $(GTKMM_CFLAGS)
sublib_win32_dlls_libs	= $(top_builddir)/gdk/gdkmm/libgdkmm-2.0.la \
	               	  $(top_builddir)/atk/atkmm/libatkmm-1.0.la \
			  $(top_builddir)/pango/pangomm/libpangomm-1.0.la \
			  $(top_builddir)/glib/glibmm/libglibmm-2.0.la

sublib_files_extra_posix_cc =
sublib_files_extra_win32_cc =
sublib_files_extra_general_cc = accelkey.cc accelmap.cc menu_elems.cc selectiondata_private.cc stock.cc stockid.cc targetentry.cc treemodelcolumn.cc treeview_private.cc

sublib_files_extra_posix_h =
sublib_files_extra_win32_h =
sublib_files_extra_general_h = accelkey.h accelmap.h base.h menu_elems.h selectiondata_private.h stock.h stockid.h targetentry.h treemodelcolumn.h treeview_private.h

include $(top_srcdir)/build_shared/Makefile_build_gensrc.am_fragment

lib_LTLIBRARIES		= libgtkmm-2.0.la
if OS_WIN32
libgtkmm_2_0_la_SOURCES	= $(files_all_general_cc) $(files_all_win32_cc)
else
libgtkmm_2_0_la_SOURCES	= $(files_all_general_cc) $(files_all_posix_cc)
endif
libgtkmm_2_0_la_LDFLAGS	= $(common_ldflags)
libgtkmm_2_0_la_LIBADD	= $(win32_dlls_extra_libs) $(GTKMM_LIBS)

