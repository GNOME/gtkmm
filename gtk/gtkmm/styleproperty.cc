/* Copyright (C) 2014 The gtkmm Development Team
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

#include <gtkmm/styleproperty.h>

#include <gtk/gtk.h>

namespace Gtk
{

/**** Gtk::StylePropertyBase ***************************************/

StylePropertyBase::StylePropertyBase(Gtk::Widget& widget, GType value_type)
:
  widget_     (&widget),
  value_type_ (value_type),
  param_spec_ (0)
{
}

StylePropertyBase::~StylePropertyBase()
{
  if (param_spec_)
    g_param_spec_unref(param_spec_);
}

bool StylePropertyBase::lookup_style_property(const Glib::ustring& name)
{
  g_assert(param_spec_ == 0);

  param_spec_ = gtk_widget_class_find_style_property(GTK_WIDGET_GET_CLASS(widget_->gobj()), name.c_str());

  if (param_spec_)
  {
    g_assert(G_PARAM_SPEC_VALUE_TYPE(param_spec_) == value_type_);
    g_param_spec_ref(param_spec_);
  }

  return param_spec_ != 0;
}

void StylePropertyBase::install_style_property(GParamSpec* param_spec)
{
  g_return_if_fail(param_spec != 0);

  gtk_widget_class_install_style_property(GTK_WIDGET_GET_CLASS(widget_->gobj()), param_spec);

  param_spec_ = param_spec;
  g_param_spec_ref(param_spec_);
}

const char* StylePropertyBase::get_name_internal() const
{
  const char* const name = g_param_spec_get_name(param_spec_);
  g_return_val_if_fail(name != 0, "");
  return name;
}

Glib::ustring StylePropertyBase::get_name() const
{
  return Glib::ustring(get_name_internal());
}

} // namespace Gtk
