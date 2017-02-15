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

#ifndef _GTKMM_WIDGETCUSTOMDRAW_H
#define _GTKMM_WIDGETCUSTOMDRAW_H

#include <glibmm/extraclassinit.h>
#include <glibmm/signalproxy.h>
#include <cairomm/context.h>

using GtkWidget = struct _GtkWidget;

namespace Gtk
{

/** %Widget with signal_draw().
 *
 * Because of the way gtk+4 renders widgets, Gtk::Widget can't wrap the draw signal.
 * If you make a custom widget that uses the draw signal, you must derive your
 * custom widget from both %WidgetCustomDraw and the relevant widget class.
 * E.g. if you make a custom widget that you want to derive from Gtk::Widget,
 * and you want to connect to signal_draw() or override the on_draw() default
 * signal handler:
 * @code
 * #include <gtkmm/widgetcustomdraw.h>
 *
 * class MyWidget : public Gtk::WidgetCustomDraw, public Gtk::Widget
 * {
 * public:
 *   MyWidget()
 *   :
 *   // The GType name will be gtkmm__CustomObject_MyMidget
 *   Glib::ObjectBase("MyWidget"), // Unique class name
 *   Gtk::WidgetCustomDraw(),
 *   Gtk::Widget()
 *   {
 *     // ...
 *   }
 *   // ...
 * protected:
 *   bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
 *   // ...
 * };
 * @endcode
 *
 * %WidgetCustomDraw must be listed @e before the widget class (Gtk::Widget in
 * the example) in the list of base classes.
 *
 * Do not use %WidgetCustomDraw for drawing in a Gtk::DrawingArea.
 * %Gtk::DrawingArea uses a draw function instead of %signal_draw().
 * See Gtk::DrawingArea::set_draw_func().
 *
 * Don't derive from both %WidgetCustomDraw and WidgetCustomSnapshot in the
 * same class. It will compile, but probably at most one of signal_draw() and
 * snapshot_vfunc() will work.
 *
 * @newin{3,90}
 * @ingroup Widgets
 */
class WidgetCustomDraw : public Glib::ExtraClassInit
{
public:
  WidgetCustomDraw();

  /**
   * @par Slot Prototype:
   * <tt>bool on_my_%draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr)</tt>
   *
   * This signal is emitted when a widget is supposed to render itself.
   * The widget's top left corner must be painted at the origin of
   * the passed in context and be sized to the values returned by
   * Gtk::Widget::get_allocated_width() and
   * Gtk::Widget::get_allocated_height().
   *
   * Signal handlers connected to this signal can modify the cairo
   * context passed as @a cr in any way they like and don't need to
   * restore it. The signal emission takes care of calling cairo_save()
   * before and cairo_restore() after invoking the handler.
   *
   * The signal handler will get a @a cr with a clip region already set to the
   * widget's dirty region, i.e. to the area that needs repainting.  Complicated
   * widgets that want to avoid redrawing themselves completely can get the full
   * extents of the clip region with Cairo::Context::get_clip_extents(), or they can
   * get a finer-grained representation of the dirty region with
   * Cairo::Context::copy_clip_rectangle_list().
   *
   * @param cr The cairo context to draw to.
   * @return <tt>true</tt> to stop other handlers from being invoked for the event.
   *         <tt>false</tt> to propagate the event further.
   */
  Glib::SignalProxy<bool(const ::Cairo::RefPtr< ::Cairo::Context>&)> signal_draw();

protected:
  /// This is a default handler for signal_draw().
  virtual bool on_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr);

private:
  static gboolean draw_callback(GtkWidget* self, cairo_t* cr);
  static void class_init_function(void* g_class, void* class_data);

}; // end WidgetCustomDraw

} // namespace Gtk

#endif // _GTKMM_WIDGETCUSTOMDRAW_H
