dnl
dnl Some macros needed for autoconf
dnl

dnl AL_PROG_GNU_M4(ACTION_NOT_FOUND)
dnl  Check for GNU m4.  (sun won't do.)
dnl
AC_DEFUN([AL_PROG_GNU_M4],[
AC_CHECK_PROGS(M4, gm4 m4, m4)

if test "$M4" = "m4"; then
  AC_MSG_CHECKING(whether m4 is GNU m4)
  if $M4 --version </dev/null 2>/dev/null | grep '^GNU m4 ' >/dev/null ; then
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
    if test "$host_vendor" = "sun"; then
      $1
    fi
  fi
fi
])


## GTKMM_CV_PERL_VERSION(version)
##
## Helper macro of GTKMM_CHECK_PERL().  It generates a cache variable
## name that includes the version number, in order to avoid clashes.
##
AC_DEFUN([GTKMM_CV_PERL_VERSION],[gtkmm_cv_perl_version_[]m4_translit([$1],[.${}],[____])])


## GTKMM_CHECK_PERL(version)
##
## Check for Perl >= version and set PERL_PATH.  If Perl is not found
## and maintainer-mode is enabled, abort with an error message.  If not
## in maintainer-mode, set PERL_PATH=perl on failure.
##
AC_DEFUN([GTKMM_CHECK_PERL],
[
  gtkmm_perl_result=no

  AC_PATH_PROGS([PERL_PATH], [perl perl5], [not found])

  if test "x$PERL_PATH" != "xnot found"; then
  {
    AC_CACHE_CHECK(
      [whether Perl is new enough],
      GTKMM_CV_PERL_VERSION([$1]),
    [
      ]GTKMM_CV_PERL_VERSION([$1])[=no
      "$PERL_PATH" -e "require v$1; exit 0;" >/dev/null 2>&1 && ]GTKMM_CV_PERL_VERSION([$1])[=yes
    ])
    test "x${GTKMM_CV_PERL_VERSION([$1])}" = xyes && gtkmm_perl_result=yes
  }
  else
  {
    # Make sure we have something sensible in gtkmmproc, even if it doesn't work.
    PERL_PATH=perl
  }
  fi

  if test "x$gtkmm_perl_result" = xno && test "x$USE_MAINTAINER_MODE" = xyes; then
  {
    AC_MSG_ERROR([[
*** Perl >= ]$1[ is required for building $PACKAGE in maintainer-mode.
]])
  }
  fi

  AC_SUBST([PERL_PATH])
])


dnl AL_PROG_GNU_MAKE(ACTION_NOT_FOUND)
dnl   Check for GNU make (no sun make)
dnl
AC_DEFUN([AL_PROG_GNU_MAKE],[
dnl 
dnl Check for GNU make (stolen from gtk+/configure.in)
AC_MSG_CHECKING(whether make is GNU Make)
if $ac_make --version 2>/dev/null | grep '^GNU Make ' >/dev/null ; then
        AC_MSG_RESULT(yes)
else
        AC_MSG_RESULT(no)
        if test "$host_vendor" = "sun" ; then
           $1
        fi
fi
])

dnl AL_ACLOCAL_INCLUDE(macrodir)
dnl   Add a directory to macro search (from gnome)
AC_DEFUN([AL_ACLOCAL_INCLUDE],
[
  test "x$ACLOCAL_FLAGS" = "x" || ACLOCAL="$ACLOCAL $ACLOCAL_FLAGS"
  for dir in $1
  do
    ACLOCAL="$ACLOCAL -I $srcdir/$dir"
  done
])


## GTKMM_ARG_ENABLE_DEBUG_REFCOUNTING()
##
## Provide the --enable-debug-refcounting configure argument, disabled
## by default.  If enabled, #define GTKMM_DEBUG_REFCOUNTING.
##
AC_DEFUN([GTKMM_ARG_ENABLE_DEBUG_REFCOUNTING],
[
  AC_ARG_ENABLE([debug-refcounting],
      [  --enable-debug-refcounting  Print a debug message on every ref/unref.
                              [[default=disabled]]],
      [gtkmm_debug_refcounting="$enableval"],
      [gtkmm_debug_refcounting='no'])

  if test "x$gtkmm_debug_refcounting" = "xyes"; then
  {
    AC_DEFINE([GTKMM_DEBUG_REFCOUNTING],[1])
  }
  fi
])


## GTKMM_ARG_ENABLE_WARNINGS()
##
## Provide the --enable-warnings configure argument, set to 'minimum'
## by default.
##
AC_DEFUN([GTKMM_ARG_ENABLE_WARNINGS],
[
  AC_ARG_ENABLE([warnings],
      [  --enable-warnings=[[none|minimum|maximum|hardcore]]
                          Control compiler pickyness.  [[default=minimum]]],
      [gtkmm_enable_warnings="$enableval"],
      [gtkmm_enable_warnings='minimum'])

  AC_MSG_CHECKING([for compiler warning flags to use])

  gtkmm_warning_flags=''

  case "$gtkmm_enable_warnings" in
    minimum|yes) gtkmm_warning_flags='-Wall';;
    maximum)     gtkmm_warning_flags='-pedantic -W -Wall';;
    hardcore)    gtkmm_warning_flags='-pedantic -W -Wall -Werror';;
  esac

  gtkmm_use_flags=''

  if test "x$gtkmm_warning_flags" != "x"
  then
    echo 'int foo() { return 0; }' > conftest.cc

    for flag in $gtkmm_warning_flags
    do
      # Test whether the compiler accepts the flag.  GCC doesn't bail
      # out when given an unsupported flag but prints a warning, so
      # check the compiler output instead.
      gtkmm_cxx_out="`$CXX $flag -c conftest.cc 2>&1`"
      rm -f conftest.$OBJEXT
      test "x${gtkmm_cxx_out}" = "x" && \
        gtkmm_use_flags="${gtkmm_use_flags:+$gtkmm_use_flags }$flag"
    done

    rm -f conftest.cc
    gtkmm_cxx_out=''
  fi

  if test "x$gtkmm_use_flags" != "x"
  then
    for flag in $gtkmm_use_flags
    do
      case " $CXXFLAGS " in
        *" $flag "*) ;; # don't add flags twice
        *)           CXXFLAGS="${CXXFLAGS:+$CXXFLAGS }$flag";;
      esac
    done
  else
    gtkmm_use_flags='none'
  fi

  AC_MSG_RESULT([$gtkmm_use_flags])
])

