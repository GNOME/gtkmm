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


## GLIBMM_ARG_ENABLE_API_MAEMO_EXTENSIONS
##
## Provide the --enable-api-maemo-extensions configure argument, disabled
## by default. This provides gtkmm API for the additional GTK+ methods in
## the version of GTK+ that is in the Maemo platform.
##
AC_DEFUN([GTKMM_ARG_ENABLE_API_MAEMO_EXTENSIONS],
[
  AC_ARG_ENABLE([api-maemo-extensions],
      [AS_HELP_STRING([--enable-api-maemo-extensions], [Build Maemo Extensions API. @<:@default=no@:>@])],
      [gtkmm_enable_api_maemo_extensions="$enableval"],
      [gtkmm_enable_api_maemo_extensions='no'])

  AS_VAR_IF([gtkmm_enable_api_maemo_extensions], ['yes'],
            [AC_DEFINE([GTKMM_MAEMO_EXTENSIONS_ENABLED], [1],
                       [Define if maemo extensions should be built.])])
])

