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
  if $M4 --version </dev/null 2>/dev/null | grep '^GNU [Mm]4 ' >/dev/null ; then
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
    if test "$host_vendor" = "sun"; then
      $1
    fi
  fi
fi
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
