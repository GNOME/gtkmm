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

lib_LTLIBRARIES = libgtkmm-2.4.la

include $(srcdir)/../src/filelist.am
include $(srcdir)/filelist.am

files_built_cc = $(gtkmm_files_built_cc)
files_built_h  = $(gtkmm_files_built_h)
files_built_ph = $(gtkmm_files_built_ph)
files_extra_cc = $(gtkmm_files_extra_cc)
files_extra_h  = $(gtkmm_files_extra_h)
files_extra_ph = $(gtkmm_files_extra_ph)

if GTKMM_ATKMM_ENABLED
atkmm_includes = -I$(top_builddir)/atk $(if $(srcdir:.=),-I$(top_srcdir)/atk)
atkmm_libadd   = $(top_builddir)/atk/atkmm/libatkmm-$(ATKMM_API_VERSION).la
else
atkmm_includes =
atkmm_libadd   =
endif
local_includes = -I$(top_builddir)/gdk $(if $(srcdir:.=),-I$(top_srcdir)/gdk) $(atkmm_includes)
local_libadd   = $(atkmm_libadd) $(top_builddir)/gdk/gdkmm/libgdkmm-$(GDKMM_API_VERSION).la

include $(top_srcdir)/scripts/compile-binding.am

local_cppflags = $(binding_includes) $(local_includes) $(binding_cppflags)

AM_CPPFLAGS = $(local_cppflags) $(GTHREAD_CFLAGS) $(GTKMM_CFLAGS)
AM_CXXFLAGS = $(GLIBMM_WXXFLAGS)

libgtkmm_2_4_la_SOURCES = $(binding_sources)
libgtkmm_2_4_la_LDFLAGS = -no-undefined -version-info $(LIBGTKMM_SO_VERSION)
libgtkmm_2_4_la_LIBADD  = $(local_libadd) $(GTKMM_LIBS)
