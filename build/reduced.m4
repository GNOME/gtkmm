## GLIBMM_ARG_ENABLE_API_ATKMM()
##
## Provide the --enable-api-atkmm configure argument, enabled
## by default.
##
AC_DEFUN([GTKMM_ARG_ENABLE_API_ATKMM],
[
  AC_ARG_ENABLE([api-atkmm],
      [AS_HELP_STRING([--enable-api-atkmm], [Build atkmm API. @<:@default=yes@:>@])],
      [gtkmm_enable_api_atkmm="$enableval"],
      [gtkmm_enable_api_atkmm='yes'])

  AS_VAR_IF([gtkmm_enable_api_atkmm], ['yes'],
            [AC_DEFINE([GTKMM_ATKMM_ENABLED], [1],
                       [Define if atkmm API should be built.])])
])

