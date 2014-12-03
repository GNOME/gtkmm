## Copyright (c) 2009-2014  Openismus GmbH  <http://www.openismus.com/>
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

AC_INIT([gtkmm], [3.15.2],
        [http://bugzilla.gnome.org/enter_bug.cgi?product=gtkmm],
        [gtkmm], [http://www.gtkmm.org/])
AC_PREREQ([2.59])

AC_CONFIG_SRCDIR([gtk/gtkmm.h])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build])
AC_CONFIG_HEADERS([config.h gdk/gdkmmconfig.h gtk/gtkmmconfig.h])

AM_INIT_AUTOMAKE([1.9 -Wno-portability check-news no-dist-gzip dist-xz tar-ustar no-define nostdinc])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES])
AM_MAINTAINER_MODE
AC_ARG_VAR([ACLOCAL_FLAGS], [aclocal flags, e.g. -I <macro dir>])

MM_PREREQ([0.9.7])
MM_INIT_MODULE([gdkmm-3.0])
MM_INIT_MODULE([gtkmm-3.0])

# Copy the mm-common .pl scripts into docs/,
# and use them from there,
# so we can dist them to avoid a tarball-build dependency.
MM_CONFIG_DOCTOOL_DIR([docs])

# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
AC_SUBST([LIBGTKMM_SO_VERSION], [2:0:1])

AC_PROG_CXX
AC_DISABLE_STATIC
LT_INIT([win32-dll])

PKG_CHECK_MODULES([GTK], [gtk+-3.0])
gdk_target_win32=no
gdk_target_quartz=no
gdk_target_x11=no
gdk_target_wayland=no
gdk_target_broadway=no
backends=`$PKG_CONFIG --variable=targets gtk+-3.0`
m4_foreach([mytarget], [[win32], [quartz], [x11], [wayland], [broadway]], [
    AC_ARG_ENABLE(mytarget-backend,
                  AS_HELP_STRING([--enable-mytarget-backend@<:@=yes|no|check@:>@], [enable mytarget gdk target @<:@default=check@:>@]),
                  [], [enableval=check])
    if test x$enableval != xno; then
        for target in $backends; do
            if test x$target = [x]mytarget; then
                [gdk_target_]mytarget=yes
            fi
        done
        if test x$enableval = xyes && test x$[gdk_target_]mytarget = xno; then
            AC_MSG_ERROR([Requested mytarget backend not supported by installed gdk])
        fi
    fi
])
AM_CONDITIONAL([GDK_TARGET_WIN32], [test "x$gdk_target_win32" = xyes])
AM_CONDITIONAL([GDK_TARGET_QUARTZ], [test "x$gdk_target_quartz" = xyes])
AM_CONDITIONAL([GDK_TARGET_X11], [test "x$gdk_target_x11" = xyes])
AM_CONDITIONAL([GDK_TARGET_BROADWAY], [test "x$gdk_target_broadway" = xyes])
AM_CONDITIONAL([GDK_TARGET_WAYLAND], [test "x$gdk_target_wayland" = xyes])

if test "x$gdk_target_win32" = xyes ; then
   AC_MSG_CHECKING([for native Windows host])
   AS_CASE([$host_os], [mingw*], [gtkmm_host_windows=yes], [gtkmm_host_windows=no])
   AC_MSG_RESULT([$gtkmm_host_windows])
else
   gtkmm_host_windows=no
fi
AM_CONDITIONAL([HOST_WINDOWS_NATIVE], [test "x$gtkmm_host_windows" = xyes])

# TODO: What exactly does this do?  If both static and shared libraries
# are built, both builds will have this macro defined!
AS_IF([test "x$enable_static" = xyes],
      [AC_DEFINE([GTKMM_STATIC_LIB], [1], [Define when building gtkmm as a static library])])

# gdkmm really does need GTK+, because part of Gdk::DragContext is in GTK+.
# The extra cairomm-1.0 check is because gdkmm requires a newer cairomm than pangomm requires.
# The extra gdk-pixbuf-2.0 check is because gdkmm requires a newer gdk-pixbuf than gtk+-3.0 requires.
AC_SUBST([GDKMM_MODULES], ['giomm-2.4 >= 2.43.1 pangomm-1.4 >= 2.27.1 gtk+-3.0 >= 3.15.2 cairomm-1.0 >= 1.9.2 gdk-pixbuf-2.0 >= 2.26.0'])

AS_IF([test "x$gtkmm_host_windows" = xyes],
      [GTKMM_MODULES=$GDKMM_MODULES],
      [GTKMM_MODULES="$GDKMM_MODULES gtk+-unix-print-3.0"])

# Offer the ability to omit some API from the library, to reduce the code size.
# Note that there are other options in glibmm, which affect gtkmm.
GTKMM_ARG_ENABLE_API_ATKMM

AS_IF([test "x$gtkmm_enable_api_atkmm" != xno],
      [GTKMM_MODULES="atkmm-1.6 >= 2.22.2 $GTKMM_MODULES"])
AC_SUBST([GTKMM_MODULES])

PKG_CHECK_MODULES([GDKMM], [$GDKMM_MODULES])
PKG_CHECK_MODULES([GTKMM], [$GTKMM_MODULES])

MM_PKG_CONFIG_SUBST([GTHREAD_CFLAGS], [--cflags-only-other gthread-2.0])
MM_PKG_CONFIG_SUBST([GTHREAD_LIBS], [--libs gthread-2.0])
MM_PKG_CONFIG_SUBST([GMMPROC_DIR], [--variable=gmmprocdir glibmm-2.4])
MM_PKG_CONFIG_SUBST([GMMPROC_EXTRA_M4_DIR], [--variable=gmmprocm4dir pangomm-1.4 atkmm-1.6])

MM_ARG_DISABLE_DEPRECATED_API([GDKMM GTKMM])

MM_ARG_ENABLE_DOCUMENTATION
MM_ARG_WITH_TAGFILE_DOC([libstdc++.tag], [mm-common-libstdc++])
MM_ARG_WITH_TAGFILE_DOC([libsigc++-2.0.tag], [sigc++-2.0])
MM_ARG_WITH_TAGFILE_DOC([glibmm-2.4.tag], [glibmm-2.4])
MM_ARG_WITH_TAGFILE_DOC([cairomm-1.0.tag], [cairomm-1.0])
MM_ARG_WITH_TAGFILE_DOC([pangomm-1.4.tag], [pangomm-1.4])
MM_ARG_WITH_TAGFILE_DOC([atkmm-1.6.tag], [atkmm-1.6])

AC_LANG([C++])
AC_CHECK_FUNCS([flockfile funlockfile getc_unlocked mkfifo])

# Evaluate the --enable-warnings=level option.
MM_ARG_ENABLE_WARNINGS([GTKMM_WXXFLAGS],
                       [-Wall],
                       [-pedantic -Wall -Wextra -Wformat-security -Wno-long-long -DGSEAL_ENABLE],
                       [G PANGO ATK GDK GDK_PIXBUF GTK GLIBMM ATKMM PANGOMM CAIROMM SIGCXX])

AC_CONFIG_FILES([Makefile
                 tools/Makefile
                 gdk/${GDKMM_MODULE_NAME}.pc:gdk/gdkmm.pc.in
                 gdk/${GDKMM_MODULE_NAME}-uninstalled.pc:gdk/gdkmm-uninstalled.pc.in
                 gdk/src/Makefile
                 gdk/gdkmm/Makefile
                 gtk/${GTKMM_MODULE_NAME}.pc:gtk/gtkmm.pc.in
                 gtk/${GTKMM_MODULE_NAME}-uninstalled.pc:gtk/gtkmm-uninstalled.pc.in
                 gtk/src/Makefile
                 gtk/gtkmm/Makefile
                 tests/Makefile
                 demos/Makefile
                 docs/Makefile
                 docs/reference/Doxyfile
                 MSVC_Net2005/gdkmm/gdkmm.rc
                 MSVC_Net2005/gtkmm/gtkmm.rc
                 MSVC_Net2008/gdkmm/gdkmm.rc
                 MSVC_Net2008/gtkmm/gtkmm.rc
                 MSVC_Net2010/gdkmm/gdkmm.rc
                 MSVC_Net2010/gtkmm/gtkmm.rc
                 win32_installer/gtkmm-installer.nsi])

# Copy the generated configuration headers into the MSVC project directories.
AC_CONFIG_COMMANDS([MSVC_Net2005/gdkmm/gdkmmconfig.h],
                   [cp -f gdk/gdkmmconfig.h MSVC_Net2005/gdkmm/gdkmmconfig.h])
AC_CONFIG_COMMANDS([MSVC_Net2005/gtkmm/gtkmmconfig.h],
                   [cp -f gtk/gtkmmconfig.h MSVC_Net2005/gtkmm/gtkmmconfig.h])
AC_CONFIG_COMMANDS([MSVC_Net2008/gdkmm/gdkmmconfig.h],
                   [cp -f gdk/gdkmmconfig.h MSVC_Net2008/gdkmm/gdkmmconfig.h])
AC_CONFIG_COMMANDS([MSVC_Net2008/gtkmm/gtkmmconfig.h],
                   [cp -f gtk/gtkmmconfig.h MSVC_Net2008/gtkmm/gtkmmconfig.h])
AC_CONFIG_COMMANDS([MSVC_Net2010/gdkmm/gdkmmconfig.h],
                   [cp -f gdk/gdkmmconfig.h MSVC_Net2010/gdkmm/gdkmmconfig.h])
AC_CONFIG_COMMANDS([MSVC_Net2010/gtkmm/gtkmmconfig.h],
                   [cp -f gtk/gtkmmconfig.h MSVC_Net2010/gtkmm/gtkmmconfig.h])
AC_CONFIG_COMMANDS([win32_installer/lgpl.txt],
                   [cp -f COPYING win32_installer/lgpl.txt])
AC_OUTPUT
