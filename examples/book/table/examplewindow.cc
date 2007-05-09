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

#include <iostream>
#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_Table(2, 2, true),
  m_Button_1("button 1"),
  m_Button_2("button 2"),
  m_Button_Quit("Quit")
{
  set_title("Gtk::Table");
  set_border_width(20);

  add(m_Table);

  m_Table.attach(m_Button_1, 0, 1, 0, 1);
  m_Table.attach(m_Button_2, 1, 2, 0, 1);
  m_Table.attach(m_Button_Quit, 0, 2, 1, 2);

  m_Button_1.signal_clicked().connect(
          sigc::bind<Glib::ustring>( sigc::mem_fun(*this,
                  &ExampleWindow::on_button_numbered), "button 1") );
  m_Button_2.signal_clicked().connect(
          sigc::bind<Glib::ustring>( sigc::mem_fun(*this,
                  &ExampleWindow::on_button_numbered), "button 2") );

  m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  hide();
}

void
ExampleWindow::on_button_numbered(Glib::ustring data)
{
  std::cout << "Hello again - " << data << " was pressed" << std::endl;
}

