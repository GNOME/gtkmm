## GLIBMM_ARG_ENABLE_API_ATKMM()
##
## Provide the --enable-api-atkmm configure argument, enabled
## by default.
##
AC_DEFUN([GTKMM_ARG_ENABLE_API_ATKMM],
[
  AC_ARG_ENABLE([api-atkmm],
      [  --enable-api-atkmm  Build atkmm API.
                              [[default=yes]]],
      [gtkmm_enable_api_atkmm="$enableval"],
      [gtkmm_enable_api_atkmm='yes'])

  if test "x$gtkmm_enable_api_atkmm" = "xyes"; then
  {
    AC_DEFINE([GTKMM_ATKMM_ENABLED],[1], [Defined when the --enable-api-atkmm configure argument was given])
  }
  fi
])
