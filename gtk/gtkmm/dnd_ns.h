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

#ifndef _GTKMM_DND_NS_H
#define _GTKMM_DND_NS_H

#include <gdkmm/drag.h>

namespace Gio
{
class Icon;
}

namespace Gdk
{
class Paintable;
}

namespace Gtk
{
class Widget;

/** Drag-and-drop functions.
 *
 * The %Gtk::DnD namespace contains functions that logically are Gdk::Drag methods.
 * However, they can't be members of Gdk::Drag, because they depend on code in
 * the gtk part of gtk+. Such a dependency is not allowed in a Gdk class.
 *
 * @see Gdk::Drag, Gdk::Drop, Gtk::Widget
 *
 * @newin{3,94}
 */
namespace DnD
{

/** Determines the source widget for a drag.
 *
 * @param drag A Gdk::Drag instance.
 * @returns If the drag is occurring within a single application, a pointer to
 *          the source widget, otherwise nullptr.
 */
Widget* get_source_widget(const Glib::RefPtr<Gdk::Drag>& drag);

/** Cancels an ongoing drag operation on the source side.
 *
 * If you want to be able to cancel a drag operation in this way,
 * you need to keep a reference to the Gdk::Drag instance, either from an
 * explicit call to Gtk::Widget::drag_begin(), or by connecting to
 * Gtk::Widget::signal_drag_begin().
 *
 * If @a drag does not refer to an ongoing drag operation, this
 * function does nothing.
 *
 * If a drag is cancelled in this way, the @a result argument of
 * Gtk::Widget::signal_drag_failed() is set to Gtk::DragResult::ERROR.
 *
 * @param drag A Gdk::Drag instance, as e.g. returned by Gtk::Widget::drag_begin().
 */
void cancel(const Glib::RefPtr<Gdk::Drag>& drag);

/** Changes the icon for drag operation to a given widget.
 *
 * GTK+ will not destroy the widget, so if you don’t want
 * it to persist, you should connect to Gtk::Widget::signal_drag_end()
 * and destroy it yourself.
 *
 * @param drag A Gdk::Drag instance.
 * @param widget A widget to use as an icon.
 * @param hot_x The X offset within @a widget of the hotspot.
 * @param hot_y The Y offset within @a widget of the hotspot.
 */
void set_icon(const Glib::RefPtr<Gdk::Drag>& drag, Widget& widget,
  int hot_x = 0, int hot_y = 0);

/** Sets @a paintable as the icon for a given drag.
 *
 * To position the @a paintable relative to the mouse, its top
 * left will be positioned @a hot_x, @a hot_y pixels from the
 * mouse cursor.
 *
 * @param drag A Gdk::Drag instance.
 * @param paintable The Gdk::Paintable to use as icon.
 * @param hot_x The X offset of the hotspot within the icon.
 * @param hot_y The Y offset of the hotspot within the icon.
 */
void set_icon(const Glib::RefPtr<Gdk::Drag>& drag,
  const Glib::RefPtr<Gdk::Paintable>& paintable, int hot_x = 0, int hot_y = 0);

/** Sets the icon for a given drag from a named themed icon.
 *
 * See the docs for Gtk::IconTheme for more details. Note that the
 * size of the icon depends on the icon theme (the icon is
 * loaded at the symbolic size Gtk::IconSize::INHERIT), thus 
 * @a hot_x and @a hot_y have to be used with care.
 *
 * @param drag A Gdk::Drag instance.
 * @param icon_name Name of icon to use.
 * @param hot_x The X offset of the hotspot within the icon.
 * @param hot_y The Y offset of the hotspot within the icon.
 */
void set_icon(const Glib::RefPtr<Gdk::Drag>& drag, const Glib::ustring& icon_name,
  int hot_x = 0, int hot_y = 0);

/** Sets the icon for a given drag from the given @a icon.
 *
 * See the documentation for Gtk::DnD::set_icon(const Glib::RefPtr<Gdk::Drag>& drag,
 * const Glib::ustring& icon_name, int hot_x, int hot_y)
 * for more details about using icons in drag and drop.
 *
 * @param drag A Gdk::Drag instance.
 * @param icon A Gio::Icon.
 * @param hot_x The X offset of the hotspot within the icon.
 * @param hot_y The Y offset of the hotspot within the icon.
 */
void set_icon(const Glib::RefPtr<Gdk::Drag>& drag,
  const Glib::RefPtr<Gio::Icon>& icon, int hot_x = 0, int hot_y = 0);

/** Sets the icon for a particular drag to the default icon.
 *
 * @param drag A Gdk::Drag instance.
 */
void set_icon(const Glib::RefPtr<Gdk::Drag>& drag);

} // namespace DnD
} // namespace Gtk

#endif //_GTKMM_DND_NS_H
