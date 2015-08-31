#ifndef _GTKMM_STYLEPROPERTY_H
#define _GTKMM_STYLEPROPERTY_H

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

#include <gtkmm/widget.h>
#include <glibmm/ustring.h>
#include <glibmm/value.h>

namespace Gtk
{

/** Base class for widget style properties.
 *
 * This class manages the value type-agnostic bits of style properties.
 *
 * @newin{3,16}
 */
class StylePropertyBase
{
public:

  /** Returns the name of the style property.
   */
  Glib::ustring get_name() const;

protected:
  Gtk::Widget*    widget_;
  GType           value_type_;
  GParamSpec*     param_spec_;

  /** Constructs a style property of type @a value_type for @a widget.
   * The property is not registered in Gtk, call install_style_property()
   * in order to do that. The properties are usually installed on the
   * initialization of the first instance of a widget.
   */
  StylePropertyBase(Gtk::Widget& widget, GType value_type);
  ~StylePropertyBase() noexcept;

  /** Checks if the style property has already been installed.
   */
  bool lookup_style_property(const Glib::ustring& name);

  /** Installs the style property specified by the given @a param_spec.
   */
  void install_style_property(GParamSpec* param_spec);

  /** Returns the name of the style property.
   */
  const char* get_name_internal() const;

private:
  // noncopyable
  StylePropertyBase(const StylePropertyBase&);
  StylePropertyBase& operator=(const StylePropertyBase&);
};

/** Represents a widget style property.
 *
 * This class maps one to one to a style property of a widget in Gtk. A style
 * property is similar to object properties (Glib::Property), but its value is
 * stored in the style object associated with the widget. The style property,
 * similarly to the object properties, has some global data for each property.
 * The global data includes the following information about the style property:
 *  * unique name, used to identify the style property
 *  * human-readable nickname
 *  * short description
 *  * default value, minimum and maximum bounds (applicable depending on the
 *      type of the style property)
 *  * flags, defining, among other things, whether the property can be read or
 *      written
 *
 * The StyleProperty class currently supports only the name and default value.
 * The minimum and maximum bounds are set to the full range of the value. The
 * nickname and the description are set to empty. The flags are set to indicate that
 * the property is read-only (this doesn't disallow a style provider to set the
 * value of the property).
 *
 * The global information must be installed into the widget once per property.
 * This is handled automatically. A reference to the widget must be passed on
 * the construction of the style property.
 *
 * @newin{3,16}
 */
template <class T>
class StyleProperty : public StylePropertyBase
{
public:
  typedef T PropertyType;
  typedef Glib::Value<T> ValueType;

  /** Constructs a style property for @a widget with @a name. For each instance
   * of the widget, the same property must be constructed with the same name.
   */
  StyleProperty(Gtk::Widget& widget, const Glib::ustring& name);

  /** Constructs a style property for @a widget with @a name and @a default_value.
   * For each instance of the widget, the same property must be constructed with
   * the same name and default value.
   */
  StyleProperty(Gtk::Widget& widget, const Glib::ustring& name, const PropertyType& default_value);

  /** Returns the value of the style property. Equivalent to
   * Gtk::Widget::get_style_property(get_name(), PropertyType& value).
   */
  inline PropertyType get_value() const;

  /** Returns the value of the style property. Equivalent to
   * Gtk::Widget::get_style_property(get_name(), PropertyType& value).
   */
  inline operator PropertyType() const;
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**** Gtk::StyleProperty<T> ****************************************/

template <class T>
StyleProperty<T>::StyleProperty(Gtk::Widget& widget, const Glib::ustring& name)
:
  StylePropertyBase(widget, ValueType::value_type())
{
  if (!lookup_style_property(name))
  {
    ValueType value;
    value.init(value_type_);
    GParamSpec* param_spec = value.create_param_spec(name);
    param_spec->flags = (GParamFlags)(param_spec->flags & ~G_PARAM_WRITABLE); // value.create_param_spec() sets read-write flags
    install_style_property(param_spec);
  }
}

template <class T>
StyleProperty<T>::StyleProperty(Gtk::Widget& widget, const Glib::ustring& name,
                      const typename StyleProperty<T>::PropertyType& default_value)
:
  StylePropertyBase(widget, ValueType::value_type())
{
  if (!lookup_style_property(name))
  {
    ValueType value;
    value.init(value_type_);
    value.set(default_value);
    GParamSpec* param_spec = value.create_param_spec(name);
    param_spec->flags = (GParamFlags)(param_spec->flags & ~G_PARAM_WRITABLE); // value.create_param_spec() sets read-write flags
    install_style_property(param_spec);
  }
}

template <class T> inline
typename StyleProperty<T>::PropertyType StyleProperty<T>::get_value() const
{
  PropertyType value;
  widget_->get_style_property(get_name(), value);
  return value;
}

template <class T> inline
StyleProperty<T>::operator PropertyType() const
{
  return this->get_value();
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

} // namespace Gtk

#endif /* _GTKMM_STYLEPROPERTY_H */
