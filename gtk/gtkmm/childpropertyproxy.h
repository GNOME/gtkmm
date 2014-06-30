// -*- c++ -*-
#ifndef _GTKMM_CHILDPROPERTYPROXY_H
#define _GTKMM_CHILDPROPERTYPROXY_H

/* childpropertyproxy.h
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


namespace Gtk
{

/** A ChildPropertyProxy can be used to get and set the value of a GtkContainer's child property.
 * Child properties are not specific to either the container or the contained widget, but rather
 * to their relation.
 * With the ChildPropertyProxy, you may use either get_value() and set_value(), or operator=()
 * and operator PropertyType(), like in this example:
 * @code
 * bool first_tab_tab_expand = notebook.property_tab_expand(first_tab_widget);
 * notebook.property_tab_expand(first_tab_widget) = true;
 * @endcode
 *
 * You may also receive notification when a property's value changes on a child, by connecting
 * to signal_changed().
 */
template <class T>
class ChildPropertyProxy : public ChildPropertyProxy_Base
{
public:
  typedef T PropertyType;

  ChildPropertyProxy(Gtk::Container* parent, Gtk::Widget& child, const char* property_name)
    : ChildPropertyProxy_Base(parent, child, property_name) {}

  /** Set the value of this property in child.
   * @param data The new value for the property.
   */
  void set_value(const PropertyType& data);

  /** Get the value of this property in child.
   * @result The current value of the property.
   */
  PropertyType get_value() const;

  /** Set the value of this property in child back to its default value.
   */
  void reset_value()
    { reset_property_(); }

  ChildPropertyProxy<T>& operator=(const PropertyType& data)
    { set_value(data); return *this; }

  operator PropertyType() const
    { return get_value(); }

  SignalProxyChildProperty signal_changed();
};


/** See ChildPropertyProxy().
 * This property can be written, but not read, so there is no get_value() method.
 */
template <class T>
class ChildPropertyProxy_WriteOnly : public ChildPropertyProxy_Base
{
public:
  typedef T PropertyType;

  ChildPropertyProxy_WriteOnly(Gtk::Container* parent, Gtk::Widget& child, const char* property_name)
    : ChildPropertyProxy_Base(parent, child, property_name) {}

  /** Set the value of this property in child.
   * @param data The new value for the property.
   */
  void set_value(const PropertyType& data);

  /** Set the value of this property in child back to its default value.
   */
  void reset_value()
    { reset_property_(); }

  ChildPropertyProxy_WriteOnly<T>& operator=(const PropertyType& data)
    { set_value(data); return *this; }
};

/** See ChildPropertyProxy().
 * This property can be read, but not written, so there is no set_value() method.
 */
template <class T>
class ChildPropertyProxy_ReadOnly : public ChildPropertyProxy_Base
{
public:
  typedef T PropertyType;

  //obj is const, because this should be returned by const accessors.
  ChildPropertyProxy_ReadOnly(const Gtk::Container* parent, const Gtk::Widget& child, const char* property_name)
    : ChildPropertyProxy_Base(const_cast<Gtk::Container*>(parent), const_cast<Gtk::Widget&>(child), property_name) {}

  /** Get the value of this property in child.
   * @result The current value of the property.
   */
  PropertyType get_value() const;

  operator PropertyType() const
    { return get_value(); }
};


/**** Template Implementation **********************************************/

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template <class T>
void ChildPropertyProxy<T>::set_value(const T& data)
{
  Glib::Value<T> value;
  value.init(Glib::Value<T>::value_type());

  value.set(data);
  set_property_(value);
}

template <class T>
T ChildPropertyProxy<T>::get_value() const
{
  Glib::Value<T> value;
  value.init(Glib::Value<T>::value_type());

  get_property_(value);
  return value.get();
}

template <class T>
SignalProxyChildProperty ChildPropertyProxy<T>::signal_changed()
{
  return SignalProxyChildProperty(&child_, property_name_);
}

template <class T>
void ChildPropertyProxy_WriteOnly<T>::set_value(const T& data)
{
  Glib::Value<T> value;
  value.init(Glib::Value<T>::value_type());

  value.set(data);
  set_property_(value);
}

template <class T>
T ChildPropertyProxy_ReadOnly<T>::get_value() const
{
  Glib::Value<T> value;
  value.init(Glib::Value<T>::value_type());

  get_property_(value);
  return value.get();
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

} // namespace Gtk


#endif /* _GTKMM_CHILDPROPERTYPROXY_H */
