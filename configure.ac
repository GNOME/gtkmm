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

AC_INIT([gtkmm], [2.17.2], [http://bugzilla.gnome.org/enter_bug.cgi?product=gtkmm],
        [gtkmm], [http://www.gtkmm.org/])
AC_PREREQ([2.59])

AC_CONFIG_SRCDIR([gtk/gtkmm.h])
AC_CONFIG_AUX_DIR([scripts])
AC_CONFIG_MACRO_DIR([scripts])
AC_CONFIG_HEADERS([config.h gtk/gtkmmconfig.h])

MM_INIT_MODULE([atkmm-1.6], m4_expand([AC_PACKAGE_VERSION]))
MM_INIT_MODULE([gdkmm-2.4], m4_expand([AC_PACKAGE_VERSION]))
MM_INIT_MODULE([gtkmm-2.4], m4_expand([AC_PACKAGE_VERSION]))

# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
AC_SUBST([LIBGTKMM_SO_VERSION], [1:30:0])

AM_INIT_AUTOMAKE([1.9 -Wno-portability dist-bzip2 no-define nostdinc tar-pax])
AM_MAINTAINER_MODE
AC_ARG_VAR([ACLOCAL_FLAGS], [aclocal flags, e.g. -I <macro dir>])

AC_PROG_CXX
AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

AC_MSG_CHECKING([for native Windows host])
AS_CASE([$host_os], [mingw*], [gtkmm_host_windows=yes], [gtkmm_host_windows=no])
AC_MSG_RESULT([$gtkmm_host_windows])
AM_CONDITIONAL([HOST_WINDOWS_NATIVE], [test "x$gtkmm_host_windows" = xyes])
# TODO: kill dummies
AM_CONDITIONAL([OS_WIN32], [false])
AM_CONDITIONAL([PLATFORM_WIN32], [false])

# TODO: What exactly does this do?  If both static and shared libraries
# are built, both builds will have this macro defined!
AS_IF([test "x$enable_static" = xyes],
      [AC_DEFINE([GTKMM_STATIC_LIB], [1], [Define when building gtkmm as a static library])])

AC_SUBST([ATKMM_MODULES], ['glibmm-2.4 >= 2.21.2 atk >= 1.9.0'])

# gdkmm really does need GTK+, because part of Gdk::DragContext is in GTK+.
AC_SUBST([GDKMM_MODULES], ['giomm-2.4 >= 2.21.2 pangomm-1.4 >= 2.14.0 gtk+-2.0 >= 2.17.4'])

AS_IF([test "x$gtkmm_host_windows" = xyes],
      [GTKMM_MODULES=$GDKMM_MODULES],
      [GTKMM_MODULES="$GDKMM_MODULES gtk+-unix-print-2.0"])
AC_SUBST([GTKMM_MODULES])

PKG_CHECK_MODULES([ATKMM], [$ATKMM_MODULES])
PKG_CHECK_MODULES([GDKMM], [$GDKMM_MODULES])
PKG_CHECK_MODULES([GTKMM], [$GTKMM_MODULES])

MM_PKG_CONFIG_SUBST([GTHREAD_CFLAGS], [--cflags-only-other gthread-2.0])
MM_PKG_CONFIG_SUBST([GTHREAD_LIBS], [--libs-only-other --libs-only-l gthread-2.0])
MM_PKG_CONFIG_SUBST([GMMPROC_DIR], [--variable=gmmprocdir glibmm-2.4])
# TODO: Temporary hack
AC_SUBST([GMMPROC], ['${GMMPROC_DIR}/gmmproc'])

# Create a list of input directories for Doxygen.
# TODO: kill
GTKMM_DOXYGEN_INPUT_SUBDIRS([atk gdk gtk])

# TODO: Refactor into shared Autoconf macro
AC_ARG_ENABLE([deprecated-api],
              [AS_HELP_STRING([--disable-deprecated-api],
                              [omit deprecated API from the library])],
              [gtkmm_deprecated_api=$enableval],
              [gtkmm_deprecated_api=yes])
AS_IF([test "x$gtkmm_deprecated_api" = xyes],
[
  AC_MSG_NOTICE([[Deprecated API will be built, for backwards-compatibility.]])
  DISABLE_DEPRECATED_API_CFLAGS=dnl
], [
  AC_MSG_WARN([[Deprecated API will not be built, breaking compatibility.
Do not use this option for distribution packages.]])
  DISABLE_DEPRECATED_API_CFLAGS='-DATKMM_DISABLE_DEPRECATED=1 -DGDKMM_DISABLE_DEPRECATED=1 -DGTKMM_DISABLE_DEPRECATED=1'dnl
])
AC_SUBST([DISABLE_DEPRECATED_API_CFLAGS])

# Offer the ability to omit some API from the library, to reduce the code size.
# Note that there are other options in glibmm, which affect gtkmm.
GTKMM_ARG_ENABLE_API_ATKMM

AS_IF([test "x$gtkmm_enable_api_atkmm" = xno],
      [GTKMM_PC_ATKMM_DEP=],
      [GTKMM_PC_ATKMM_DEP=atkmm-1.6])
AC_SUBST([GTKMM_PC_ATKMM_DEP])

AM_CONDITIONAL([GTKMM_ATKMM_ENABLED], [test "x$gtkmm_enable_api_atkmm" != xno])

GTKMM_ARG_ENABLE_API_MAEMO_EXTENSIONS

AC_LANG([C++])
AC_CHECK_FUNCS([flockfile funlockfile getc_unlocked mkfifo])

# Evaluate the --enable-warnings=level option.
DK_ARG_ENABLE_WARNINGS([GTKMM_WXXFLAGS],
                       [-Wall],
                       [-pedantic -Wall -Wextra]
                       [G PANGO ATK GDK GDK_PIXBUF GTK])

AC_CONFIG_FILES([
      atk/Makefile
      atk/atkmm-1.6.pc
      atk/src/Makefile
      atk/atkmm/Makefile
      atk/atkmm/private/Makefile
])

AC_CONFIG_FILES([
  docs/Makefile
    docs/images/Makefile
    docs/reference/Makefile
    docs/reference/Doxyfile
      docs/reference/images/Makefile
        docs/reference/images/widgets/Makefile
])

AC_CONFIG_FILES([
  Makefile

  gdk/Makefile
  gdk/gdkmm-2.4.pc
    gdk/src/Makefile
    gdk/gdkmm/Makefile
      gdk/gdkmm/private/Makefile

  gtk/Makefile
  gtk/gtkmm-2.4.pc
    gtk/src/Makefile
    gtk/gtkmm/Makefile
      gtk/gtkmm/private/Makefile

  tools/Makefile
    tools/m4/Makefile
    tools/extra_defs_gen/Makefile
])

AC_CONFIG_FILES([
  tests/Makefile
    tests/child_widget/Makefile
    tests/child_widget2/Makefile
    tests/child_widget_managed/Makefile
    tests/refcount_dialog/Makefile
    tests/dialog/Makefile
    tests/dialog_deletethis/Makefile
    tests/delete_cpp_child/Makefile
    tests/main_with_options/Makefile
    tests/menu_destruction/Makefile
    tests/property_notification/Makefile
    tests/scrolledwindow/Makefile
    tests/wrap_existing/Makefile
    tests/boxhelper/Makefile
])

AC_CONFIG_FILES([
  scripts/Makefile
])

AC_CONFIG_FILES([
  MSVC_Net2005/Makefile
    MSVC_Net2005/gendef/Makefile
    MSVC_Net2005/atkmm/Makefile
    MSVC_Net2005/atkmm/atkmm.rc
    MSVC_Net2005/gdkmm/Makefile
    MSVC_Net2005/gdkmm/gdkmm.rc
    MSVC_Net2005/gtkmm/Makefile
    MSVC_Net2005/gtkmm/gtkmm.rc
    MSVC_Net2005/demos/Makefile
      MSVC_Net2005/demos/gtk-demo/Makefile

  MSVC_Net2008/Makefile
    MSVC_Net2008/gendef/Makefile
    MSVC_Net2008/atkmm/Makefile
    MSVC_Net2008/atkmm/atkmm.rc
    MSVC_Net2008/gdkmm/Makefile
    MSVC_Net2008/gdkmm/gdkmm.rc
    MSVC_Net2008/gtkmm/Makefile
    MSVC_Net2008/gtkmm/gtkmm.rc
    MSVC_Net2008/demos/Makefile
      MSVC_Net2008/demos/gtk-demo/Makefile

  win32_installer/Makefile
    win32_installer/NSISLibrary/Makefile
    win32_installer/translations/Makefile
  win32_installer/gtkmm-installer.nsi
])

AC_OUTPUT
