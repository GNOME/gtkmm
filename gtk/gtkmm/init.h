#ifndef _GTKMM_INIT_H
#define _GTKMM_INIT_H

/* Copyright (C) 2020 The gtkmm Development Team
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

namespace Gtk
{

/** Initialize the table of wrap_new functions.
 *
 * This would usually only be used by the init() methods of libraries that
 * depend on gtkmm. Gtkmm applications initialize gtkmm by a call to
 * Gtk::Application::create().
 *
 * @newin{3,98}
 */
GTKMM_API
void init_gtkmm_internals();

} // namespace Gtk

#endif /* _GTKMM_INIT_H */
