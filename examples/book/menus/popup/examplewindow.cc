//$Id$ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
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

#include "examplewindow.h"
#include <gtkmm/stock.h>
#include <iostream>

ExampleWindow::ExampleWindow()
: m_Label("Right-click to see the popup menu."),
  m_Image(Gtk::Stock::DIALOG_QUESTION, Gtk::ICON_SIZE_MENU)
{
  set_title("popup example");
  set_default_size(200, 200);

  add(m_Box);

  //Add an event box that can catch button_press events:
  m_Box.pack_start(m_EventBox);
  m_EventBox.signal_button_press_event().connect( SigC::slot(*this, &ExampleWindow::on_button_press_event) );

  m_EventBox.add(m_Label);


  //Fill menu:
  {
  	Gtk::Menu::MenuList& menulist = m_Menu_Popup.items();

  	menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Edit",
      SigC::slot(*this, &ExampleWindow::on_menu_file_popup_generic) ) );
	menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Process", Gtk::Menu::AccelKey("<control>p"),
      SigC::slot(*this, &ExampleWindow::on_menu_file_popup_generic) ) );
  	menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Remove",
      SigC::slot(*this, &ExampleWindow::on_menu_file_popup_generic) ) );

    //Add a ImageMenuElem:
    menulist.push_back( Gtk::Menu_Helpers::ImageMenuElem("_Something", m_Image,
      SigC::slot(*this, &ExampleWindow::on_menu_file_popup_generic) ) ) ;


  }
  m_Menu_Popup.accelerate(*this);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_menu_file_popup_generic()
{
   std::cout << "A popup menu item was selected." << std::endl;
}

bool ExampleWindow::on_button_press_event(GdkEventButton* event)
{
  if( (event->type == GDK_BUTTON_PRESS) && (event->button == 3) )
  {
    m_Menu_Popup.popup(event->button, event->time);
    return true; //It has been handled.
  }
  else
    return false;
}

