## Copyright (c) 2001
## The gtkmm development team.

SUBDIRS			= private

sublib_name		= gdkmm
sublib_libname		= gdkmm-1.4
sublib_libversion = $(LIBGTKMM_SO_VERSION)
sublib_namespace	= Gdk
sublib_cflags		= $(GDKMM_CFLAGS)
sublib_topdir = gdkmm
sublib_win32_dlls_libs	= $(top_builddir)/pango/pangomm/libpangomm-1.4.la \
	        	  $(top_builddir)/glib/glibmm/libglibmm-2.4.la

sublib_files_extra_posix_cc =
sublib_files_extra_win32_cc =
sublib_files_extra_general_cc = general.cc

sublib_files_extra_posix_h =
sublib_files_extra_win32_h =
sublib_files_extra_general_h = list.h general.h

include $(top_srcdir)/build_shared/Makefile_build_gensrc.am_fragment

lib_LTLIBRARIES		= libgdkmm-2.4.la
if OS_WIN32
libgdkmm_2_4_la_SOURCES	= $(files_all_general_cc) $(files_all_win32_cc)
else
libgdkmm_2_4_la_SOURCES	= $(files_all_general_cc) $(files_all_posix_cc)
endif 
libgdkmm_2_4_la_LDFLAGS	= $(common_ldflags)
libgdkmm_2_4_la_LIBADD	= $(win32_dlls_extra_libs) $(GDKMM_LIBS)

