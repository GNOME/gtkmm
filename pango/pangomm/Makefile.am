## Copyright (c) 2001
## The gtkmm development team.

SUBDIRS			= private

sublib_name		= pangomm
sublib_namespace	= Pango
sublib_cflags		= $(PANGOMM_CFLAGS)
sublib_win32_dlls_libs	= $(top_builddir)/glib/glibmm/libglibmm-2.4.la

sublib_files_extra_posix_cc =
sublib_files_extra_win32_cc =
sublib_files_extra_general_cc =

sublib_files_extra_posix_h =
sublib_files_extra_win32_h =
sublib_files_extra_general_h = 

include $(top_srcdir)/build_shared/Makefile_build_gensrc.am_fragment

lib_LTLIBRARIES			= libpangomm-1.4.la
if PLATFORM_WIN32
libpangomm_1_4_la_SOURCES	= $(files_all_general_cc) $(files_all_win32_cc)
else
libpangomm_1_4_la_SOURCES	= $(files_all_general_cc) $(files_all_posix_cc)
endif
libpangomm_1_4_la_LDFLAGS	= $(common_ldflags)
libpangomm_1_4_la_LIBADD	= $(win32_dlls_extra_libs) $(PANGOMM_LIBS)

