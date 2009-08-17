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

lib_LTLIBRARIES = libatkmm-1.6.la

include $(srcdir)/../src/filelist.am
include $(srcdir)/filelist.am

files_built_cc = $(atkmm_files_built_cc)
files_built_h  = $(atkmm_files_built_h)
files_built_ph = $(atkmm_files_built_ph)
files_extra_cc = $(atkmm_files_extra_cc)
files_extra_h  = $(atkmm_files_extra_h)
files_extra_ph = $(atkmm_files_extra_ph)

include $(top_srcdir)/build/compile-binding.am

local_cppflags = $(binding_includes) $(binding_cppflags) -DATKMM_BUILD=1

AM_CPPFLAGS = $(local_cppflags) $(GTHREAD_CFLAGS) $(ATKMM_CFLAGS)
AM_CXXFLAGS = $(GTKMM_WXXFLAGS)

libatkmm_1_6_la_SOURCES = $(binding_sources)
libatkmm_1_6_la_LDFLAGS = -no-undefined -version-info $(LIBGTKMM_SO_VERSION)
libatkmm_1_6_la_LIBADD  = $(ATKMM_LIBS)
