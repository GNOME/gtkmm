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
#include <iostream>

ExampleWindow::ExampleWindow()
: m_Button_Close("Close")
{
  set_title("Gtk::Toolbar example");

  add(m_VBox);

  //Put a toolbar at the top, and a button underneath:
  m_VBox.pack_start(m_Toolbar, Gtk::PACK_SHRINK);
  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_VBox.pack_end(m_ButtonBox);

  m_ButtonBox.pack_start(m_Button_Close, Gtk::PACK_SHRINK);

  m_Button_Close.signal_clicked().connect( SigC::slot(*this, &ExampleWindow::on_button_close) );

  //Add the toolbar items:
  {
    using namespace Gtk::Toolbar_Helpers;

    m_Toolbar.tools().push_back( ButtonElem("Click me", SigC::slot(*this, &ExampleWindow::on_toolbar_item), "Toolbar item") );

    m_Toolbar.tools().push_back( Space() );

    m_Toolbar.tools().push_back( StockElem(Gtk::Stock::SAVE, SigC::slot(*this, &ExampleWindow::on_toolbar_item)) );

    m_Toolbar.tools().push_back( ToggleElem("Toggle me", SigC::slot(*this, &ExampleWindow::on_toolbar_item), "toggle duh") );

    Gtk::RadioButton::Group group;
    m_Toolbar.tools().push_back( RadioElem(group, "Radio 1") );
    m_Toolbar.tools().push_back( RadioElem(group, "Radio 2") );
    m_Toolbar.tools().push_back( RadioElem(group, "Radio 3") );
  }

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_close()
{
  hide();
}

void ExampleWindow::on_toolbar_item()
{
  std::cout << "Toolbar item clicked." << std::endl;
}


