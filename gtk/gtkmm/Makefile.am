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

lib_LTLIBRARIES = libgtkmm-@GTKMM_API_VERSION@.la

include $(srcdir)/../src/filelist.gmake.am
include $(srcdir)/filelist.gmake.am

files_built_cc = $(gtkmm_files_built_cc)
files_built_h  = $(gtkmm_files_built_h)
files_built_ph = $(gtkmm_files_built_ph)
files_extra_cc = $(gtkmm_files_extra_cc)
files_extra_h  = $(gtkmm_files_extra_h)
files_extra_ph = $(gtkmm_files_extra_ph)

local_includes = -I$(top_builddir)/gdk $(if $(srcdir:.=),-I$(top_srcdir)/gdk) \
                 -I$(top_builddir)/gsk $(if $(srcdir:.=),-I$(top_srcdir)/gsk)
local_libadd   = $(top_builddir)/gdk/gdkmm/libgdkmm-$(GDKMM_API_VERSION).la \
                 $(top_builddir)/gsk/gskmm/libgskmm-$(GSKMM_API_VERSION).la

include $(top_srcdir)/build/compile-binding.am

local_cppflags = $(binding_includes) $(local_includes) $(binding_cppflags) -DGTKMM_BUILD=1

AM_CPPFLAGS = $(local_cppflags) $(GTHREAD_CFLAGS) $(GTKMM_CFLAGS)
AM_CXXFLAGS = $(GTKMM_WXXFLAGS)

libgtkmm_@GTKMM_API_VERSION@_la_SOURCES = $(binding_sources)
libgtkmm_@GTKMM_API_VERSION@_la_LDFLAGS = -no-undefined -version-info $(LIBGTKMM_SO_VERSION)
libgtkmm_@GTKMM_API_VERSION@_la_LIBADD  = $(local_libadd) $(GTKMM_LIBS)
