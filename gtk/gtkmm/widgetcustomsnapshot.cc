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

#include <gtkmm/widgetcustomsnapshot.h>
#include <glibmm/exceptionhandler.h>
#include <gtk/gtk.h>

using CppObjectType = Gtk::WidgetCustomSnapshot;
using BaseObjectType = GtkWidget;
using BaseClassType = GtkWidgetClass;

namespace Gtk
{
WidgetCustomSnapshot::WidgetCustomSnapshot()
:
Glib::ExtraClassInit(class_init_function)
{
}

void WidgetCustomSnapshot::snapshot_vfunc(const Glib::RefPtr<Snapshot>& snapshot)
{
  const auto base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(gobject_)) // Get the parent class of the object class (The original underlying C class).
  );

  if (base && base->snapshot)
    (*base->snapshot)((BaseObjectType*)gobject_, snapshot->gobj());
}

// static
void WidgetCustomSnapshot::snapshot_vfunc_callback(GtkWidget* self, GtkSnapshot* snapshot)
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
        // Call the virtual member method, which derived classes must override.
        obj->snapshot_vfunc(Glib::wrap_gtk_snapshot(snapshot, true));
        return;
      }
      catch (...)
      {
        Glib::exception_handlers_invoke();
      }
    }
  }

  BaseClassType *const base = static_cast<BaseClassType*>(
      g_type_class_peek_parent(G_OBJECT_GET_CLASS(self)) // Get the parent class of the object class (The original underlying C class).
  );

  // Call the original underlying C function:
  if (base && base->snapshot)
    (*base->snapshot)(self, snapshot);
}

// Addition to Gtk::Widget's class init function
// static
void WidgetCustomSnapshot::class_init_function(void* g_class, void* /* class_data */)
{
  g_return_if_fail(GTK_IS_WIDGET_CLASS(g_class));

  const auto klass = static_cast<BaseClassType*>(g_class);
  klass->snapshot = &snapshot_vfunc_callback;
}


} // namespace Gtk
