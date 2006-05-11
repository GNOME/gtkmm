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
#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_Button_One("Child One"),
  m_Button_Two("Child 2"),
  m_Button_Quit("Quit")
{
  set_title("Custom Container example");
  set_border_width(6);
  set_default_size(400, 200);

  add(m_VBox);
  
  //Add the child widgets to the custom container:
  m_MyContainer.set_child_widgets(m_Button_One, m_Button_Two);
  m_Button_One.show();
  m_Button_Two.show(); 

#ifdef GLIBMM_PROPERTIES_ENABLED
  m_Button_Two.property_xalign() = 1.0f; 
#else
  m_Button_Two.set_property("xalign", 1.0f); 
#endif //GLIBMM_PROPERTIES_ENABLED

  m_VBox.pack_start(m_MyContainer, Gtk::PACK_EXPAND_WIDGET);
  m_MyContainer.show();

  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
  m_ButtonBox.set_border_width(6);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this, &ExampleWindow::on_button_quit) );

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  hide();
}


