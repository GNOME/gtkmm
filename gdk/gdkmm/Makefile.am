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

noinst_LTLIBRARIES = libgdkmm-@GDKMM_API_VERSION@.la

include $(srcdir)/../src/filelist.gmake.am
include $(srcdir)/filelist.gmake.am

files_built_cc = $(gdkmm_files_built_cc)
files_built_h  = $(gdkmm_files_built_h)
files_built_ph = $(gdkmm_files_built_ph)
files_extra_cc = $(gdkmm_files_extra_cc)
files_extra_h  = $(gdkmm_files_extra_h)
files_extra_ph = $(gdkmm_files_extra_ph)

# Install header files in $(includedir)/gtkmm-@GTKMM_API_VERSION@/gdkmm
binding_modulename = gtkmm-@GTKMM_API_VERSION@

include $(top_srcdir)/build/compile-binding.am

local_cppflags = $(binding_includes) $(binding_cppflags) -DGDKMM_BUILD=1

AM_CPPFLAGS = $(local_cppflags) $(GTHREAD_CFLAGS) $(GDKMM_CFLAGS)
AM_CXXFLAGS = $(GTKMM_WXXFLAGS)

libgdkmm_@GDKMM_API_VERSION@_la_SOURCES = $(binding_sources)
libgdkmm_@GDKMM_API_VERSION@_la_LDFLAGS = -no-undefined
libgdkmm_@GDKMM_API_VERSION@_la_LIBADD  = $(GDKMM_LIBS)
