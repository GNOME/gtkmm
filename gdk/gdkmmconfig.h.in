#ifndef _GDKMM_CONFIG_H
#define _GDKMM_CONFIG_H

#include <pangommconfig.h>

/* Define to omit deprecated API from gdkmm. */
#undef GDKMM_DISABLE_DEPRECATED

/* Major version number of gdkmm. */
#undef GDKMM_MAJOR_VERSION

/* Micro version number of gdkmm. */
#undef GDKMM_MICRO_VERSION

/* Minor version number of gdkmm. */
#undef GDKMM_MINOR_VERSION

/* Enable DLL-specific stuff only when not building a static library */
#if !defined(__CYGWIN__) && defined(_WIN32) && !defined(GDKMM_STATIC_LIB)
# define GDKMM_DLL 1
#endif

#ifdef GDKMM_DLL
# if defined (GDKMM_BUILD) || defined (GTKMM_BUILD)
#  define GDKMM_API __declspec(dllexport)
# elif !defined (__GNUC__)
#  define GDKMM_API __declspec(dllimport)
# else /* don't dllimport classes/methods on GCC/MinGW */
#  define GDKMM_API
# endif /* GDKMM_BUILD */
#else
/* Build a static library or a non-native-Windows library */
# define GDKMM_API
#endif /* GDKMM_DLL */

#endif /* !_GDKMM_CONFIG_H */
