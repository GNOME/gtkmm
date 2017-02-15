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

#include <gtkmm/widgetcustomdraw.h>
#include <glibmm/exceptionhandler.h>
#include <gtk/gtk.h>

namespace
{
using CppObjectType = Gtk::WidgetCustomDraw;
using BaseObjectType = GtkWidget;
using BaseClassType = GtkWidgetClass;

static gboolean WidgetCustomDraw_signal_draw_callback(GtkWidget* self, cairo_t* cr,void* data)
{
  using SlotType = sigc::slot<bool(const ::Cairo::RefPtr< ::Cairo::Context>&)>;

  auto obj = dynamic_cast<CppObjectType*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));
  // Do not try to call a signal on a disassociated wrapper.
  if (obj)
  {
    try
    {
      if (const auto slot = Glib::SignalProxyNormal::data_to_slot(data))
        return static_cast<int>((*static_cast<SlotType*>(slot))(
          ::Cairo::RefPtr< ::Cairo::Context>(new ::Cairo::Context(cr, false /* has_reference */))));
    }
    catch (...)
    {
       Glib::exception_handlers_invoke();
    }
  }
  return false;
}

static gboolean WidgetCustomDraw_signal_draw_notify_callback(GtkWidget* self, cairo_t* cr, void* data)
{
  using SlotType = sigc::slot<void(const ::Cairo::RefPtr< ::Cairo::Context>&)>;

  auto obj = dynamic_cast<CppObjectType*>(Glib::ObjectBase::_get_current_wrapper((GObject*)self));
  // Do not try to call a signal on a disassociated wrapper.
  if (obj)
  {
    try
    {
      if (const auto slot = Glib::SignalProxyNormal::data_to_slot(data))
        (*static_cast<SlotType*>(slot))(
          ::Cairo::RefPtr< ::Cairo::Context>(new ::Cairo::Context(cr, false /* has_reference */)));
    }
    catch(...)
    {
      Glib::exception_handlers_invoke();
    }
  }
  return false;
}

static const Glib::SignalProxyInfo WidgetCustomDraw_signal_draw_info =
{
  "draw",
  (GCallback) &WidgetCustomDraw_signal_draw_callback,
  (GCallback) &WidgetCustomDraw_signal_draw_notify_callback
};

} // anonymous namespace

namespace Gtk
{
WidgetCustomDraw::WidgetCustomDraw()
:
Glib::ExtraClassInit(class_init_function)
{
}

Glib::SignalProxy<bool(const ::Cairo::RefPtr< ::Cairo::Context>&)> WidgetCustomDraw::signal_draw()
{
  return Glib::SignalProxy<bool(const ::Cairo::RefPtr< ::Cairo::Context>&) >(this, &WidgetCustomDraw_signal_draw_info);
}

bool WidgetCustomDraw::on_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr)
{
  const auto base = static_cast<BaseClassType*>(
    g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_))); // Get the parent class of the object class (The original underlying C class).

  if (base && base->draw)
    return (*base->draw)((BaseObjectType*)gobject_, cr->cobj());

  return false;
}

// static
gboolean WidgetCustomDraw::draw_callback(GtkWidget* self, cairo_t* cr)
{
  const auto obj_base = static_cast<Glib::ObjectBase*>(
      Glib::ObjectBase::_get_current_wrapper((GObject*)self));

  // Non-gtkmmproc-generated custom classes implicitly call the default
  // Glib::ObjectBase constructor, which sets is_derived_. But gtkmmproc-
  // generated classes can use this optimisation, which avoids the unnecessary
  // parameter conversions if there is no possibility of the virtual function
  // being overridden:
  if (obj_base && obj_base->is_derived_())
  {
    const auto obj = dynamic_cast<CppObjectType* const>(obj_base);
    if (obj) // This can be nullptr during destruction.
    {
      try // Trap C++ exceptions which would normally be lost because this is a C callback.
      {
        // Call the virtual member method, which derived classes might override.
        return static_cast<int>(obj->on_draw(
          ::Cairo::RefPtr< ::Cairo::Context>(new ::Cairo::Context(cr, false /* has_reference */))));
      }
      catch (...)
      {
        Glib::exception_handlers_invoke();
      }
    }
  }

  const auto base = static_cast<BaseClassType*>(
    g_type_class_peek_parent(G_OBJECT_GET_CLASS(self))); // Get the parent class of the object class (The original underlying C class).

  // Call the original underlying C function:
  if (base && base->draw)
    return (*base->draw)(self, cr);

  return false;
}

// Addition to Gtk::Widget's class init function
// static
void WidgetCustomDraw::class_init_function(void* g_class, void* /* class_data */)
{
  g_return_if_fail(GTK_IS_WIDGET_CLASS(g_class));

  const auto klass = static_cast<BaseClassType*>(g_class);
  klass->draw = &draw_callback;
}

} // namespace Gtk
