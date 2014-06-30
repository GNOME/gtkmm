// -*- c++ -*-

/* childpropertyproxy_base.cc
 *
 * Copyright 2014 The gtkmm Development Team
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
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gtkmm/childpropertyproxy_base.h>
#include <gtkmm/container.h>

#include <gtk/gtk.h>

namespace Gtk
{

sigc::connection SignalProxyChildProperty::connect(const SlotType& sl)
{
  // Create a proxy to hold our connection info
  // This will be deleted by destroy_notify_handler.
  Glib::PropertyProxyConnectionNode* pConnectionNode = new Glib::PropertyProxyConnectionNode(sl, obj_->gobj());

  // connect it to gtk+
  // pConnectionNode will be passed as the data argument to the callback.
  // The callback will then call the virtual Object::property_change_notify() method,
  // which will contain a switch/case statement which will examine the property name.
  const Glib::ustring notify_signal_name = "child-notify::" + Glib::ustring(property_name_);
  pConnectionNode->connection_id_ = g_signal_connect_data(obj_->gobj(),
         notify_signal_name.c_str(), (GCallback)(&Glib::PropertyProxyConnectionNode::callback), pConnectionNode,
         &Glib::PropertyProxyConnectionNode::destroy_notify_handler,
         G_CONNECT_AFTER);

  return sigc::connection(pConnectionNode->slot_);
}

ChildPropertyProxy_Base::ChildPropertyProxy_Base(Gtk::Container* parent, Gtk::Widget& child, const char* property_name)
  : parent_(parent),
    child_(child),
    property_name_(property_name) {}

ChildPropertyProxy_Base::ChildPropertyProxy_Base(const ChildPropertyProxy_Base& other)
  : parent_(other.parent_),
    child_(other.child_),
    property_name_(other.property_name_) {}

SignalProxyChildProperty ChildPropertyProxy_Base::signal_changed()
{
  return SignalProxyChildProperty(&child_, property_name_);
}

void ChildPropertyProxy_Base::set_property_(const Glib::ValueBase& value)
{
  gtk_container_child_set_property(parent_->gobj(), child_.gobj(), property_name_, value.gobj());
}

void ChildPropertyProxy_Base::get_property_(Glib::ValueBase& value) const
{
  gtk_container_child_get_property(parent_->gobj(), child_.gobj(), property_name_, value.gobj());
}

void ChildPropertyProxy_Base::reset_property_()
{
  // Get information about the parameter:
  const GParamSpec *const pParamSpec =
      gtk_container_class_find_child_property(G_OBJECT_GET_CLASS(parent_->gobj()), property_name_);

  g_return_if_fail(pParamSpec != 0);

  Glib::ValueBase value;
  value.init(G_PARAM_SPEC_VALUE_TYPE(pParamSpec));

  // An explicit reset is not needed, because ValueBase:init()
  // has already initialized it to the default value for this type.
  // value.reset();

  set_property_(value);
}

} // namespace Gtk
