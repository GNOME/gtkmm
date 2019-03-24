#ifndef _GTKMM_VERSION_H
#define _GTKMM_VERSION_H

/* Copyright (C) 2019 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmmconfig.h>

// GTKMM_M*_VERSION are defined in gtkmmconfig.h.
// They are described here because Doxygen does not document gtkmmconfig.h.

#ifdef DOXYGEN_SHOULD_SKIP_THIS
// Only Doxygen sees this.
#define GTKMM_MAJOR_VERSION
#define GTKMM_MINOR_VERSION
#define GTKMM_MICRO_VERSION
#endif

/** @defgroup Version Version
 * Gtkmm version
 * @{
 */

/** @def GTKMM_MAJOR_VERSION
 * The major version number of the GTKMM library.
 *
 * From the headers used at application compile time.
 * E.g. in GTKMM version 4.2.1 this is 4.
 */

/** @def GTKMM_MINOR_VERSION
 * The minor version number of the GTKMM library.
 *
 * From the headers used at application compile time.
 * E.g. in GTKMM version 4.2.1 this is 2.
 */

/** @def GTKMM_MICRO_VERSION
 * The micro version number of the GTKMM library.
 *
 * From the headers used at application compile time.
 * E.g. in GTKMM version 4.2.1 this is 1.
 */

/** Checks the version of the GTKMM header files at compile time.
 *
 * Returns <tt>true</tt> if the version of the GTKMM header files
 * is the same as or newer than the passed-in version.
 *
 * @newin{3,96}
 *
 * @param major Major version (e.g. 4 for version 4.2.1)
 * @param minor Minor version (e.g. 2 for version 4.2.1)
 * @param micro Micro version (e.g. 1 for version 4.2.1)
 * @returns <tt>true</tt> if GTKMM headers are new enough.
 */
#define GTKMM_CHECK_VERSION(major, minor, micro) \
  (GTKMM_MAJOR_VERSION > (major) || \
  (GTKMM_MAJOR_VERSION == (major) && GTKMM_MINOR_VERSION > (minor)) || \
  (GTKMM_MAJOR_VERSION == (major) && GTKMM_MINOR_VERSION == (minor) && \
   GTKMM_MICRO_VERSION >= (micro)))

/** @} */ // end of group Version

#endif // _GTKMM_VERSION_H
