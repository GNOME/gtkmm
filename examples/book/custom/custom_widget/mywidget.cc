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
#include "mywidget.h"

MyWidget::MyWidget()
{
  set_flags(Gtk::NO_WINDOW);
  //add_events(Gdk::EXPOSURE_MASK);
}

MyWidget::~MyWidget()
{
}

void MyWidget::on_size_request(Gtk::Requisition* requisition)
{
  //Initialize the output parameter:
  *requisition = Gtk::Requisition();

  //Discover the total amount of minimum space needed by this widget.
  
  //Let's make this simple example widget always need 50 by 50:
  requisition->height = 50;
  requisition->width = 50;
}

void MyWidget::on_size_allocate(Gtk::Allocation& allocation)
{
  //Do something with the space that we have actually been given:
  //(We will not be given heights or widths less than we have requested, though we might get more)

  //Use the offered allocation for this container:
  set_allocation(allocation);

  if(m_refGdkWindow)
    m_refGdkWindow->move_resize( allocation.get_x(), allocation.get_y(), allocation.get_width(), allocation.get_height() );
}

void MyWidget::on_map()
{
  //Call base class:
  Gtk::Widget::on_map();
}

void MyWidget::on_unmap()
{
  //Call base class:
  Gtk::Widget::on_unmap();
}

void MyWidget::on_realize()
{
  //Call base class:
  Gtk::Widget::on_realize();

  //TODO: Not sure whether this is necessary:
  set_flags(Gtk::REALIZED);
  set_window( get_parent_window() );
  GtkWidget* cWidget = (GtkWidget*)gobj();
  cWidget->style = gtk_style_attach(cWidget->style, get_window()->gobj());

 
  if(!m_refGdkWindow)
  {
    //Create the GdkWindow:

    GdkWindowAttr attributes;
    memset(&attributes, 0, sizeof(attributes));

    Gtk::Allocation allocation = get_allocation();

    //Set initial position and size of the Gdk::Window:
    attributes.x = allocation.get_x();
    attributes.y = allocation.get_y();
    attributes.width = allocation.get_width();
    attributes.height = allocation.get_height();

    attributes.window_type = GDK_WINDOW_CHILD;
    attributes.wclass = GDK_INPUT_OUTPUT;

    m_refGdkWindow = Gdk::Window::create(
      get_window() /* parent */,
      &attributes,
      GDK_WA_X | GDK_WA_Y);

    //Allocate a GC for use in on_expose_event():
    m_refGC = Gdk::GC::create(m_refGdkWindow);
  }
}

void MyWidget::on_unrealize()
{
  m_refGdkWindow.clear();
  m_refGC.clear();

  //Call base class:
  Gtk::Widget::on_unrealize();
}

bool MyWidget::on_expose_event(GdkEventExpose* /* event */)
{
  if(m_refGdkWindow)
  {
    //Draw on the Gdk::Window:

    Glib::RefPtr<Gdk::Colormap> colormap = get_default_colormap ();
    Gdk::Color color_blue("blue");
    Gdk::Color color_red("red");
    colormap->alloc_color(color_blue);
    colormap->alloc_color(color_red);

    m_refGdkWindow->set_background( color_red );
    m_refGdkWindow->clear();
    m_refGC->set_foreground( color_blue );
    m_refGdkWindow->draw_line(m_refGC, 1, 1, 100, 100);
  }

  return true;
}
