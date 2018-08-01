/* Copyright (C) 2018 The gtkmm Development Team
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

#include <gtkmm/dnd_ns.h>
#include <gtkmm/widget.h>
#include <gdkmm/paintable.h>
#include <giomm/icon.h>

namespace Gtk
{
namespace DnD
{

Widget* get_source_widget(const Glib::RefPtr<Gdk::Drag>& drag)
{
  return Glib::wrap(gtk_drag_get_source_widget(Glib::unwrap(drag)));
}

void cancel(const Glib::RefPtr<Gdk::Drag>& drag)
{
  gtk_drag_cancel(Glib::unwrap(drag));
}

void set_icon(const Glib::RefPtr<Gdk::Drag>& drag, Widget& widget, int hot_x, int hot_y)
{
  gtk_drag_set_icon_widget(Glib::unwrap(drag), widget.gobj(), hot_x, hot_y);
}

void set_icon(const Glib::RefPtr<Gdk::Drag>& drag,
  const Glib::RefPtr<Gdk::Paintable>& paintable, int hot_x, int hot_y)
{
  gtk_drag_set_icon_paintable(Glib::unwrap(drag), Glib::unwrap(paintable), hot_x, hot_y);
}

void set_icon(const Glib::RefPtr<Gdk::Drag>& drag, const Glib::ustring& icon_name,
  int hot_x, int hot_y)
{
  gtk_drag_set_icon_name(Glib::unwrap(drag), icon_name.c_str(), hot_x, hot_y);
}

void set_icon(const Glib::RefPtr<Gdk::Drag>& drag,
  const Glib::RefPtr<Gio::Icon>& icon, int hot_x, int hot_y)
{
  gtk_drag_set_icon_gicon(Glib::unwrap(drag), Glib::unwrap(icon), hot_x, hot_y);
}

void set_icon(const Glib::RefPtr<Gdk::Drag>& drag)
{
  gtk_drag_set_icon_default(Glib::unwrap(drag));
}

} // namespace DnD
} // namespace Gtk
