/* Copyright (C) 2017 The gtkmm Development Team
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

#ifndef _GTKMM_WIDGETCUSTOMSNAPSHOT_H
#define _GTKMM_WIDGETCUSTOMSNAPSHOT_H

#include <glibmm/extraclassinit.h>
#include <gtkmm/snapshot.h>

using GtkWidget = struct _GtkWidget;
//using GtkSnapshot = struct _GtkSnapshot;

namespace Gtk
{

/** %Widget with snapshot_vfunc().
 *
 * Because of the way gtk+4 renders widgets, Gtk::Widget can't wrap the snapshot virtual function.
 * If you make a custom widget that uses the snapshot vfunc, you must derive your
 * custom widget from both %WidgetCustomSnapshot and the relevant widget class.
 * E.g. if you make a custom widget that you want to derive from Gtk::Widget,
 * and you want snapshot_vfunc() to be called:
 * @code
 * #include <gtkmm/widgetcustomsnapshot.h>
 *
 * class MyWidget : public Gtk::WidgetCustomSnapshot, public Gtk::Widget
 * {
 * public:
 *   MyWidget()
 *   :
 *   // The GType name will be gtkmm__CustomObject_MyMidget
 *   Glib::ObjectBase("MyWidget"), // Unique class name
 *   Gtk::WidgetCustomSnapshot(),
 *   Gtk::Widget()
 *   {
 *     // ...
 *   }
 *   // ...
 * protected:
 *   void snapshot_vfunc(Gtk::Snapshot& snapshot) override;
 *   // ...
 * };
 * @endcode
 *
 * %WidgetCustomSnapshot must be listed @e before the widget class (Gtk::Widget in
 * the example) in the list of base classes.
 *
 * Do not use %WidgetCustomSnapshot for drawing in a Gtk::DrawingArea.
 * %Gtk::DrawingArea uses a draw function instead of %snapshot_vfunc().
 * See Gtk::DrawingArea::set_draw_func().
 *
 * Don't derive from both WidgetCustomDraw and %WidgetCustomSnapshot in the
 * same class. It will compile, but probably at most one of signal_draw() and
 * snapshot_vfunc() will work.
 *
 * @newin{3,90}
 * @ingroup Widgets
 */
class WidgetCustomSnapshot : public Glib::ExtraClassInit
{
public:
  WidgetCustomSnapshot();

protected:
  /// Called when a widget is supposed to create a snapshot of itself.
  virtual void snapshot_vfunc(const Glib::RefPtr<Snapshot>& snapshot);

private:
  static void snapshot_vfunc_callback(GtkWidget* self, GtkSnapshot* snapshot);
  static void class_init_function(void* g_class, void* class_data);

}; // end WidgetCustomSnapshot

} // namespace Gtk

#endif // _GTKMM_WIDGETCUSTOMSNAPSHOT_H
