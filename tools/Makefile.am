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

AUTOMAKE_OPTIONS = subdir-objects

include $(srcdir)/m4/filelist.am

# TODO: These should go into $(datadir)/$(PACKAGE_TARNAME)/ instead.
gmmproc_m4_includedir = $(libdir)/$(GTKMM_MODULE_NAME)/proc/m4
dist_gmmproc_m4_include_DATA = $(addprefix m4/,$(files_codegen_m4))

noinst_PROGRAMS = extra_defs_gen/generate_defs_gdk \
                  extra_defs_gen/generate_defs_gsk \
                  extra_defs_gen/generate_defs_gtk

extra_defs_gen_generate_defs_gdk_SOURCES = extra_defs_gen/generate_defs_gdk.cc
extra_defs_gen_generate_defs_gdk_LDADD   = $(GTKMM_LIBS) -lglibmm_generate_extra_defs-2.68
extra_defs_gen_generate_defs_gdk_LDFLAGS = -no-undefined -avoid-version

extra_defs_gen_generate_defs_gsk_SOURCES = extra_defs_gen/generate_defs_gsk.cc
extra_defs_gen_generate_defs_gsk_LDADD   = $(GTKMM_LIBS) -lglibmm_generate_extra_defs-2.68
extra_defs_gen_generate_defs_gsk_LDFLAGS = -no-undefined -avoid-version

extra_defs_gen_generate_defs_gtk_SOURCES = extra_defs_gen/generate_defs_gtk.cc
extra_defs_gen_generate_defs_gtk_LDADD   = $(GTKMM_LIBS) -lglibmm_generate_extra_defs-2.68
extra_defs_gen_generate_defs_gtk_LDFLAGS = -no-undefined -avoid-version

AM_CPPFLAGS = -I$(top_builddir) $(GTHREAD_CFLAGS) $(GTKMM_CFLAGS)
AM_CXXFLAGS = $(GTKMM_WXXFLAGS)

# Instruct GNU make to delete the targets of a rule after it failed, in
# order to avoid the complication of handling that situation manually.
.DELETE_ON_ERROR:
