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

ACLOCAL_AMFLAGS = -I build ${ACLOCAL_FLAGS}
DISTCHECK_CONFIGURE_FLAGS = --enable-warnings=fatal

if MAINTAINER_MODE
src_subdirs = gdk/src gtk/src
else
src_subdirs =
endif
if ENABLE_DOCUMENTATION
doc_subdirs = docs
else
doc_subdirs =
endif
SUBDIRS = tools $(src_subdirs) gdk/gdkmm gtk/gtkmm tests demos $(doc_subdirs)

gdkmm_includedir = $(includedir)/$(GDKMM_MODULE_NAME)
gdkmm_include_HEADERS = gdk/gdkmm.h
gdkmm_libincludedir = $(libdir)/$(GDKMM_MODULE_NAME)/include
nodist_gdkmm_libinclude_HEADERS = gdk/gdkmmconfig.h

gtkmm_includedir = $(includedir)/$(GTKMM_MODULE_NAME)
gtkmm_include_HEADERS = gtk/gtkmm.h
gtkmm_libincludedir = $(libdir)/$(GTKMM_MODULE_NAME)/include
nodist_gtkmm_libinclude_HEADERS = gtk/gtkmmconfig.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gdk/$(GDKMM_MODULE_NAME).pc gtk/$(GTKMM_MODULE_NAME).pc

include $(srcdir)/MSVC_Net2013/filelist.am
include $(srcdir)/win32_installer/filelist.am

text_files = COPYING.tools PORTING README.SUN README.win32
msvc_files = $(addprefix MSVC_Net2013/,$(msvc_net2013_data))
winstall_files = $(addprefix win32_installer/,$(windows_installer_files))

dist_noinst_DATA = $(text_files) $(msvc_files) $(winstall_files)
dist_noinst_SCRIPTS = autogen.sh

DISTCLEANFILES = $(filter %mmconfig.h,$(msvc_files)) win32_installer/lgpl.txt

# Optional: auto-generate the ChangeLog file from the git log on make dist
include $(top_srcdir)/build/dist-changelog.am
