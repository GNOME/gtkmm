/* Copyright (C) 1998-2002 The gtkmm Development Team
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
 * License along with this library; if not, see <https://www.gnu.org/licenses/>.
 */

#include <glibmm/utility.h>
#include <gtkmm/accelerator.h>
#include <gtk/gtk.h>

// The corresponding gtk functions are defined in gtkaccelgroup.c.

namespace Gtk
{

namespace Accelerator
{

bool valid(guint keyval, Gdk::ModifierType modifiers)
{
  return gtk_accelerator_valid(keyval, (GdkModifierType) modifiers);
}

bool parse(const Glib::ustring& accelerator,
           guint&               accelerator_key,
           Gdk::ModifierType&   accelerator_mods)
{
  auto mods = GdkModifierType(0);
  const auto result = gtk_accelerator_parse(accelerator.c_str(), &accelerator_key, &mods);

  accelerator_mods = static_cast<Gdk::ModifierType>(mods);
  return result;
}

Glib::ustring name(guint accelerator_key, Gdk::ModifierType accelerator_mods)
{
  return Glib::convert_return_gchar_ptr_to_ustring(gtk_accelerator_name(
    accelerator_key, static_cast<GdkModifierType>(accelerator_mods)));
}

Glib::ustring get_label(guint accelerator_key, Gdk::ModifierType accelerator_mods)
{
  return Glib::convert_return_gchar_ptr_to_ustring(gtk_accelerator_get_label(
    accelerator_key, static_cast<GdkModifierType>(accelerator_mods)));
}

Gdk::ModifierType get_default_mod_mask()
{
  return static_cast<Gdk::ModifierType>(gtk_accelerator_get_default_mod_mask());
}

} // namespace Accelerator

} // namespace Gtk
