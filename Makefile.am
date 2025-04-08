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
src_subdirs = gdk/src gsk/src gtk/src
else
src_subdirs =
endif
if ENABLE_DOCUMENTATION
doc_subdirs = docs
else
doc_subdirs =
endif
SUBDIRS = tools $(src_subdirs) gdk/gdkmm gsk/gskmm gtk/gtkmm tests demos $(doc_subdirs)

gdkmm_includedir = $(includedir)/$(GTKMM_MODULE_NAME)
gdkmm_include_HEADERS = gdk/gdkmm.h
gdkmm_libincludedir = $(libdir)/$(GTKMM_MODULE_NAME)/include
nodist_gdkmm_libinclude_HEADERS = gdk/gdkmmconfig.h

gskmm_includedir = $(includedir)/$(GTKMM_MODULE_NAME)
gskmm_include_HEADERS = gsk/gskmm.h
gskmm_libincludedir = $(libdir)/$(GTKMM_MODULE_NAME)/include
nodist_gskmm_libinclude_HEADERS = gsk/gskmmconfig.h

gtkmm_includedir = $(includedir)/$(GTKMM_MODULE_NAME)
gtkmm_include_HEADERS = gtk/gtkmm.h
gtkmm_libincludedir = $(libdir)/$(GTKMM_MODULE_NAME)/include
nodist_gtkmm_libinclude_HEADERS = gtk/gtkmmconfig.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gtk/$(GTKMM_MODULE_NAME).pc

include $(srcdir)/MSVC_NMake/filelist.am
#include $(srcdir)/win32_installer/filelist.am

text_files = COPYING.tools README.md README.win32.md
msvc_files = $(addprefix MSVC_NMake/,$(msvc_nmake_data))
winstall_files = $(addprefix win32_installer/,$(windows_installer_files))

dist_noinst_DATA = $(text_files) $(msvc_files) $(winstall_files)
dist_noinst_SCRIPTS = autogen.sh

DISTCLEANFILES = $(filter %mmconfig.h,$(msvc_files)) win32_installer/lgpl.txt

# Distribute files needed when building gtkmm with Meson.
EXTRA_DIST = \
  meson.build \
  meson_options.txt \
  MSVC_NMake/gdkmm/meson.build \
  MSVC_NMake/gskmm/meson.build \
  MSVC_NMake/gtkmm/meson.build \
  demos/gtk-demo/meson.build \
  docs/reference/meson.build \
  gdk/meson.build \
  gdk/gdkmmconfig.h.meson \
  gdk/gdkmm/meson.build \
  gsk/meson.build \
  gsk/gskmmconfig.h.meson \
  gsk/gskmm/meson.build \
  gtk/meson.build \
  gtk/gtkmmconfig.h.meson \
  gtk/gtkmm/meson.build \
  subprojects/cairomm-1.16.wrap \
  subprojects/gdk-pixbuf.wrap \
  subprojects/glibmm-2.68.wrap \
  subprojects/gtk4.wrap \
  subprojects/libepoxy.wrap \
  subprojects/pangomm-2.48.wrap \
  tests/meson.build \
  tools/dummy-header.py \
  tools/extra_defs_gen/meson.build \
  untracked/README

# Optional: auto-generate the ChangeLog file from the git log on make dist
include $(top_srcdir)/build/dist-changelog.am
