/* Copyright (C) 1998-2010 The gtkmm Development Team
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
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _GTKMM_OBJECT_H
#define _GTKMM_OBJECT_H

#include <glibmm/object.h>
#include <gtkmm/base.h>
#include <gtkmmconfig.h>

namespace Gtk
{

class Object;

/** Mark a Gtk::Object as owned by its parent container widget, so you don't need to delete it manually.
 * For instance,
 * @code
 * Gtk::Button* button = Gtk::manage( new Gtk::Button("Hello") );
 * vbox.pack_start(*button); //vbox will delete button when vbox is deleted.
 * @endcode
 *
 * @param obj A Gtk::Object, such as a gtkmm widget.
 * @result The Gtk::Object passed as the @a obj parameter.
 */
template<class T>
T* manage(T* obj)
{
  obj->set_manage();
  return obj;
}

/** Gtk::Object is the base class for all widgets, and for a few non-widget objects such as
 * Gtk::Adjustment. Gtk::Object predates Glib::Object; non-widgets that derive from Gtk::Object
 * rather than Glib::Object do so for backward compatibility reasons.
 *
 * The most interesting difference between Gtk::Object and Glib::Object is the ability to use Gtk::manage() to delegate memory management to the container widget. Gtk::Objects can also be
 * explicitly deleted at any time, instead of using only reference-counting, and container widgets
 * can respond when their child objects are being deleted (for instance by removing the widget).
 */

class GTKMM_API Object : public Glib::Object
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef Object CppObjectType;
  typedef Glib::Object_Class CppClassType;
  typedef GObject BaseObjectType;
  typedef GObjectClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~Object();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class Object_Class;
  static CppClassType object_class_;

  // noncopyable
  Object(const Object&);
  Object& operator=(const Object&);

protected:
  explicit Object(const Glib::ConstructParams& construct_params);
  explicit Object(GObject* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GObject*       gobj()       { return reinterpret_cast<GObject*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GObject* gobj() const { return reinterpret_cast<GObject*>(gobject_); }

public:
  #ifndef DOXYGEN_SHOULD_SKIP_THIS
  /** Used by Gtk::manage(). You should not need to use this directly.
   */
  virtual void set_manage();
  #endif //DOXYGEN_SHOULD_SKIP_THIS

  #ifndef DOXYGEN_SHOULD_SKIP_THIS
  /** Private API.
   */
  bool is_managed_() const;
  #endif //DOXYGEN_SHOULD_SKIP_THIS

protected:

  #ifndef DOXYGEN_SHOULD_SKIP_THIS
  /** Private API.
   */
  void destroy_();
  #endif //DOXYGEN_SHOULD_SKIP_THIS

  #ifndef DOXYGEN_SHOULD_SKIP_THIS
  void _init_unmanage(bool is_toplevel = false);
  virtual void destroy_notify_(); //override.
  void disconnect_cpp_wrapper();
  void _release_c_instance();
  static void callback_weak_notify_(void* data, GObject* gobject); //only connected for a short time.

  // set if flags used by derived classes.
  bool referenced_; // = not managed.
  bool gobject_disposed_;
  #endif //DOXYGEN_SHOULD_SKIP_THIS
};

} // namespace Gtk

#endif /* _GTKMM_OBJECT_H */
