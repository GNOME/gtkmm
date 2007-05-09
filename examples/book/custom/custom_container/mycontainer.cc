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

#include <iostream>
#include "mycontainer.h"

MyContainer::MyContainer()
: m_child_one(0), m_child_two(0)
{
  set_flags(Gtk::NO_WINDOW);
  set_redraw_on_allocate(false);
}

MyContainer::~MyContainer()
{
}

void MyContainer::set_child_widgets(Gtk::Widget& child_one,
        Gtk::Widget& child_two)
{
  m_child_one = &child_one;
  m_child_two = &child_two;

  m_child_one->set_parent(*this);
  m_child_two->set_parent(*this);
}

void MyContainer::on_size_request(Gtk::Requisition* requisition)
{
  //Initialize the output parameter:
  *requisition = Gtk::Requisition();

  //Discover the total amount of minimum space needed by this container widget,
  //by examining its child widgets.  The layouts in this custom container will
  //be arranged vertically, one above the other.

   Gtk::Requisition child_requisition_one = {0, 0};
   Gtk::Requisition child_requisition_two = {0, 0};
   if(m_child_one && m_child_one->is_visible())
     child_requisition_one = m_child_one->size_request();

   if(m_child_two && m_child_two->is_visible())
     child_requisition_two = m_child_two->size_request();

  //See which one has the most width:
  int max_width = MAX(child_requisition_one.width,
          child_requisition_two.width);

  //Add the heights together:
  int total_height = child_requisition_one.height +
      child_requisition_two.height;

  //Request the width for this container based on the sizes requested by its
  //child widgets:
  requisition->height = total_height;
  requisition->width = max_width;
}

void MyContainer::on_size_allocate(Gtk::Allocation& allocation)
{
  //Do something with the space that we have actually been given:
  //(We will not be given heights or widths less than we have requested, though
  //we might get more)

  //Use the offered allocation for this container:
  set_allocation(allocation);

  //Assign sign space to the child:
  Gtk::Allocation child_allocation_one, child_allocation_two;

  //Place the first child at the top-left, 
  child_allocation_one.set_x( allocation.get_x() );
  child_allocation_one.set_y( allocation.get_y() );

  //Make it take up the full width available:
  child_allocation_one.set_width( allocation.get_width() );

  //Make it take up half the height available:
  child_allocation_one.set_height( allocation.get_height() / 2);

  if(m_child_one && m_child_one->is_visible())
    m_child_one->size_allocate(child_allocation_one);

  //Place the second child below the first child:
  child_allocation_two.set_x( allocation.get_x() );
  child_allocation_two.set_y( allocation.get_y() +
          child_allocation_one.get_height());

  //Make it take up the full width available:
  child_allocation_two.set_width( allocation.get_width() );

  //Make it take up half the height available:
  child_allocation_two.set_height( allocation.get_height() -
          child_allocation_one.get_height());

  if(m_child_two && m_child_two->is_visible())
    m_child_two->size_allocate(child_allocation_two);
}

void MyContainer::forall_vfunc(gboolean /* include_internals */,
        GtkCallback callback, gpointer callback_data)
{
  if(m_child_one)
    callback(m_child_one->gobj(), callback_data);

  if(m_child_two)
    callback(m_child_two->gobj(), callback_data);
}

void MyContainer::on_add(Gtk::Widget* child)
{
  if(!m_child_one)
  {
    m_child_one = child;
    m_child_one->set_parent(*this);
  }
  else if(!m_child_two)
  {
    m_child_two = child;

    m_child_two->set_parent(*this);
  }
}

void MyContainer::on_remove(Gtk::Widget* child)
{
  if(child)
  {
    const bool visible = child->is_visible();
    bool found = false;

    if(child == m_child_one)
    {
      m_child_one = 0;
      found = true;
    }
    else if(child == m_child_two)
    {
      m_child_two = 0;
      found = true;
    }

    if(found)
    {
      child->unparent();

      if(visible)
        queue_resize();
    }
  }
}

GtkType MyContainer::child_type_vfunc() const
{
  //If there is still space for one widget, then report the type of widget that
  //may be added.
  if(!m_child_one || !m_child_two)
    return Gtk::Widget::get_type();
  else
  {
    //No more widgets may be added.
    return G_TYPE_NONE;
  }
}

