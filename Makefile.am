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

ACLOCAL_AMFLAGS = -I scripts ${ACLOCAL_FLAGS}
DISTCHECK_CONFIGURE_FLAGS = --enable-warnings=fatal

if GTKMM_ATKMM_ENABLED
atk_maint_subdir = atk/src
atk_built_subdir = atk/atkmm
atk_atkmm_pcfile = atk/$(ATKMM_MODULE_NAME).pc
else
atk_maint_subdir =
atk_built_subdir =
atk_atkmm_pcfile =
endif
if MAINTAINER_MODE
src_subdirs = tools $(atk_maint_subdir) gdk/src gtk/src
else
src_subdirs =
endif
SUBDIRS = $(src_subdirs) $(atk_built_subdir) gdk/gdkmm gtk/gtkmm \
	  tests MSVC_Net2005 MSVC_Net2008 win32_installer
DIST_SUBDIRS = $(SUBDIRS) demos docs scripts

if GTKMM_ATKMM_ENABLED
atkmm_includedir = $(includedir)/$(ATKMM_MODULE_NAME)
atkmm_include_HEADERS = atk/atkmm.h
endif

gdkmm_includedir = $(includedir)/$(GDKMM_MODULE_NAME)
gdkmm_include_HEADERS = gdk/gdkmm.h
gdkmm_libincludedir = $(libdir)/$(GDKMM_MODULE_NAME)/include
nodist_gdkmm_libinclude_HEADERS = gdk/gdkmmconfig.h

gtkmm_includedir = $(includedir)/$(GTKMM_MODULE_NAME)
gtkmm_include_HEADERS = gtk/gtkmm.h
gtkmm_libincludedir = $(libdir)/$(GTKMM_MODULE_NAME)/include
nodist_gtkmm_libinclude_HEADERS = gtk/gtkmmconfig.h

pkgconfigdir = $(libdir)/pkgconfig
nodist_pkgconfig_DATA = $(atk_atkmm_pcfile) gdk/$(GDKMM_MODULE_NAME).pc gtk/$(GTKMM_MODULE_NAME).pc

dist_noinst_SCRIPTS = autogen.sh
dist_noinst_DATA = CHANGES COPYING.tools PORTING README.SUN README.win32
