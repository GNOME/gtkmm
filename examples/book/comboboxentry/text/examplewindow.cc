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
{
  set_title("ComboBoxEntryText example");

  //Fill the combo:
  m_Combo.append_text("something");
  m_Combo.append_text("something else");
  m_Combo.append_text("something or other");

  add(m_Combo);

  //Connect signal handler:
  m_Combo.signal_changed().connect( sigc::mem_fun(*this, &ExampleWindow::on_combo_changed) );

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_combo_changed()
{
  Glib::ustring text = m_Combo.get_active_text();
  if(!(text.empty()))
    std::cout << "Combo changed: " << text << std::endl;
}

