## Copyright (c) 2001
## The gtkmm development team.

SUBDIRS = private

sublib_name = atkmm
sublib_libname = atkmm-1.3
sublib_libversion = $(LIBGTKMM_SO_VERSION)
sublib_namespace	= Atk
sublib_cflags = $(ATKMM_CFLAGS)
sublib_topdir = atk
sublib_win32_dlls_libs	= $(top_builddir)/glib/glibmm/libglibmm-2.3.la

sublib_files_extra_posix_cc =
sublib_files_extra_win32_cc =
sublib_files_extra_general_cc = init.cc
sublib_files_extra_general_deprecated_cc =

sublib_files_extra_posix_h =
sublib_files_extra_win32_h =
sublib_files_extra_general_h = init.h
sublib_files_extra_general_deprecated_h = 

include $(top_srcdir)/build_shared/Makefile_build_gensrc.am_fragment

lib_LTLIBRARIES = libatkmm-1.3.la

if OS_WIN32
libatkmm_1_3_la_SOURCES = $(files_all_general_cc) $(files_all_win32_cc)
else
libatkmm_1_3_la_SOURCES = $(files_all_general_cc) $(files_all_posix_cc)
endif

libatkmm_1_3_la_LDFLAGS = $(common_ldflags)
libatkmm_1_3_la_LIBADD = $(win32_dlls_extra_libs) $(ATKMM_LIBS)

