#ifndef _GTKMM_CHILDPROPERTYPROXY_BASE_H
#define _GTKMM_CHILDPROPERTYPROXY_BASE_H

/* childpropertyproxy_base.h
 *
 * Copyright (C) 2014 The gtkmm Development Team
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

#include <glibmm/value.h>
#include <glibmm/propertyproxy_base.h>
#include <gtkmm/widget.h>

#include <sigc++/sigc++.h>


namespace Gtk
{

// We need to reimplement the connect() method so that it uses
// "child-notify" as prefix for notify signal.
class GTKMM_API SignalProxyChildProperty : public Glib::SignalProxyProperty
{
public:
  SignalProxyChildProperty(Widget* child, const char* property_name)
    : Glib::SignalProxyProperty(child, property_name) {}

  sigc::connection connect(const SlotType& sl);
};

class GTKMM_API Container;

class GTKMM_API ChildPropertyProxy_Base
{
public:
  ChildPropertyProxy_Base(Container* parent, Widget& child, const char* property_name);
  ChildPropertyProxy_Base(const ChildPropertyProxy_Base& other);

  SignalProxyChildProperty signal_changed();

  Container* get_parent() const { return parent_; }
  Widget& get_child() const { return child_; }
  const char* get_name() const { return property_name_; }

protected:
  void set_property_(const Glib::ValueBase& value);
  void get_property_(Glib::ValueBase& value) const;
  void reset_property_();

  Container* parent_;
  Widget& child_;
  const char* property_name_;
};

} // namespace Gtk

#endif /* _GTKMM_CHILDPROPERTYPROXY_BASE_H */
