//$Id$ -*- c++ -*-

/* gtkmm example Copyright (C) 2004 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef GTKMM_CUSTOM_CONTAINER_MYCONTAINER_H
#define GTKMM_CUSTOM_CONTAINER_MYCONTAINER_H

#include <gtkmm/container.h>

class MyContainer : public Gtk::Container
{
public:
  MyContainer();
  virtual ~MyContainer();

  virtual void set_child_widgets(Gtk::Widget& child_one, Gtk::Widget& child_two);

protected:

  //Overrides:
  virtual void on_size_request(Gtk::Requisition* requisition);
  virtual void on_size_allocate(Gtk::Allocation& allocation);

  virtual void forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data);

  virtual void on_add(Gtk::Widget* child);
  virtual void on_remove(Gtk::Widget* child);
  virtual GtkType child_type_vfunc() const;

  Gtk::Widget* m_child_one;
  Gtk::Widget* m_child_two;
};

#endif //GTKMM_CUSTOM_CONTAINER_MYCONTAINER_H
