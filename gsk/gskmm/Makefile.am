## Copyright (C) 2025 The gtkmm Development Team
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

noinst_LTLIBRARIES = libgskmm-@GSKMM_API_VERSION@.la

include $(srcdir)/../src/filelist.gmake.am
include $(srcdir)/filelist.gmake.am

files_built_cc = $(gskmm_files_built_cc)
files_built_h  = $(gskmm_files_built_h)
files_built_ph = $(gskmm_files_built_ph)
files_extra_cc = $(gskmm_files_extra_cc)
files_extra_h  = $(gskmm_files_extra_h)
files_extra_ph = $(gskmm_files_extra_ph)

# Install header files in $(includedir)/gtkmm-@GTKMM_API_VERSION@/gskmm
binding_modulename = gtkmm-@GTKMM_API_VERSION@

include $(top_srcdir)/build/compile-binding.am

local_includes = -I$(top_builddir)/gdk $(if $(srcdir:.=),-I$(top_srcdir)/gdk)
local_cppflags = $(binding_includes) $(local_includes) $(binding_cppflags) -DGSKMM_BUILD=1

AM_CPPFLAGS = $(local_cppflags) $(GTHREAD_CFLAGS) $(GSKMM_CFLAGS)
AM_CXXFLAGS = $(GTKMM_WXXFLAGS)

libgskmm_@GSKMM_API_VERSION@_la_SOURCES = $(binding_sources)
libgskmm_@GSKMM_API_VERSION@_la_LDFLAGS = -no-undefined
libgskmm_@GSKMM_API_VERSION@_la_LIBADD  = $(GSKMM_LIBS)
