//$Id$ -*- c++ -*-

/* gtkmm example Copyright (C) 2006 gtkmm development team
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
: m_Button_Quit("Quit"),
  m_ListViewText(3)
{
  set_title("Gtk::ListViewText example");
  set_border_width(6);
  set_default_size(400, 200);

  add(m_VBox);

  //Add the TreeView, inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.add(m_ListViewText);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_VBox.pack_start(m_ScrolledWindow);
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this, &ExampleWindow::on_button_quit) );


  //Fill the ListViewText:
  m_ListViewText.set_column_title(0, "City");
  m_ListViewText.set_column_title(1, "Temperature (celsius)"); //Obviously, you would want to use a real Gtk::TreeView to store a numeric (non-text) value.
  m_ListViewText.set_column_title(2, "Forecast");

  guint row_number = m_ListViewText.append_text();
  m_ListViewText.set_text(row_number, 0, "Madrid");
  m_ListViewText.set_text(row_number, 1, "30");   // degrees for Madrid
  m_ListViewText.set_text(row_number, 2, "cloudy"); // forecast for Madrid  

  row_number = m_ListViewText.append_text();
  m_ListViewText.set_text(row_number,  0, "Lisbon"); 
  m_ListViewText.set_text(row_number, 1, "25");   // degrees for Lisbon
  m_ListViewText.set_text(row_number, 2, "rainy");  // forecast for Lisbon

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  hide();
}


