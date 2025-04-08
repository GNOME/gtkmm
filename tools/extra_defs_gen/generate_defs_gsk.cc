/* Copyright (C) 2025 The gtkmm Development Team
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

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif
// We always need to generate the .defs for all types because the code
// using deprecated API is generated unconditionally and only disabled
// at compile time.
#undef GDK_PIXBUF_DISABLE_DEPRECATED
#undef GDK_DISABLE_DEPRECATED
#undef GSK_DISABLE_DEPRECATED
#undef GTK_DISABLE_DEPRECATED

#include <glibmm_generate_extra_defs/generate_extra_defs.h>
#include <gdk/gdk.h>
#include <gsk/gsk.h>
#include <gtk/gtk.h>

int main(int /* argc */, char** /* argv */)
{
  gtk_init();

  std::cout << get_defs( GSK_TYPE_RENDERER )
            ;
  return 0;
}
