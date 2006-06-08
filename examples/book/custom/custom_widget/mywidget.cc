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

#include "mywidget.h"
#include <iostream>
//#include <gtk/gtkwidget.h> //For GTK_IS_WIDGET()


MyWidget::MyWidget()
: Glib::ObjectBase("mywidget"), //The GType name will actually be gtkmm__CustomObject_mywidget
  Gtk::Widget(),
  m_scale(1000)
{
  set_flags(Gtk::NO_WINDOW);

  //This shows the GType name, which must be used in the RC file.
  std::cout << "GType name: " <<G_OBJECT_TYPE_NAME(gobj()) << std::endl;

  //This show that the GType still derives from GtkWidget:
  //std::cout << "Gtype is a GtkWidget?:" << GTK_IS_WIDGET(gobj()) << std::endl;

  //Install a style so that an aspect of this widget may be themed via an RC file: 
  gtk_widget_class_install_style_property(GTK_WIDGET_CLASS(G_OBJECT_GET_CLASS(gobj())), 
     g_param_spec_int("example_scale",
		      "Scale of Example Drawing",
                      "The scale to use when drawing the picture. This is just a silly example.",
                      G_MININT,
		      G_MAXINT,
		      0,
 		      G_PARAM_READABLE) );

  gtk_rc_parse("custom_gtkrc");
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

  ensure_style();

  //Get the themed style from the RC file:
  get_style_property("example_scale", m_scale);
  std::cout << "m_scale (example_scale from the theme/rc-file) is: " << m_scale << std::endl; 

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

    attributes.event_mask = get_events () | Gdk::EXPOSURE_MASK; 
    attributes.window_type = GDK_WINDOW_CHILD;
    attributes.wclass = GDK_INPUT_OUTPUT;

    
    m_refGdkWindow = Gdk::Window::create(get_window() /* parent */, &attributes, GDK_WA_X | GDK_WA_Y);
    unset_flags(Gtk::NO_WINDOW);
    set_window(m_refGdkWindow);

    //set colors
    modify_bg(Gtk::STATE_NORMAL , Gdk::Color("red"));
    modify_fg(Gtk::STATE_NORMAL , Gdk::Color("blue"));

    //make the widget receive expose events
    m_refGdkWindow->set_user_data(gobj());
    
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
    m_refGdkWindow->clear();
    double scale_x = (double)get_allocation().get_width() / m_scale;
    double scale_y = (double)get_allocation().get_height() / m_scale;

    m_refGdkWindow->draw_line(m_refGC, (int)(155*scale_x), (int)(165*scale_y), (int)(155*scale_x), (int)(838*scale_y));
    m_refGdkWindow->draw_line(m_refGC, (int)(155*scale_x), (int)(838*scale_y), (int)(265*scale_x), (int)(900*scale_y));
    m_refGdkWindow->draw_line(m_refGC, (int)(265*scale_x), (int)(900*scale_y), (int)(849*scale_x), (int)(564*scale_y));
    m_refGdkWindow->draw_line(m_refGC, (int)(849*scale_x), (int)(564*scale_y), (int)(849*scale_x), (int)(438*scale_y));
    m_refGdkWindow->draw_line(m_refGC, (int)(849*scale_x), (int)(438*scale_y), (int)(265*scale_x), (int)(100*scale_y));
    m_refGdkWindow->draw_line(m_refGC, (int)(265*scale_x), (int)(100*scale_y), (int)(155*scale_x), (int)(165*scale_y));
    m_refGdkWindow->draw_line(m_refGC, (int)(265*scale_x), (int)(100*scale_y), (int)(265*scale_x), (int)(652*scale_y));
    m_refGdkWindow->draw_line(m_refGC, (int)(265*scale_x), (int)(652*scale_y), (int)(526*scale_x), (int)(502*scale_y));
    m_refGdkWindow->draw_line(m_refGC, (int)(369*scale_x), (int)(411*scale_y), (int)(633*scale_x), (int)(564*scale_y));
    m_refGdkWindow->draw_line(m_refGC, (int)(369*scale_x), (int)(286*scale_y), (int)(369*scale_x), (int)(592*scale_y));
    m_refGdkWindow->draw_line(m_refGC, (int)(369*scale_x), (int)(286*scale_y), (int)(849*scale_x), (int)(564*scale_y));
    m_refGdkWindow->draw_line(m_refGC, (int)(633*scale_x), (int)(564*scale_y), (int)(155*scale_x), (int)(838*scale_y));
  }
  return true;
}
