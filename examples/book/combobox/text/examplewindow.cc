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
  set_title("combo example");

  //Fill the combo:
  m_Combo.append_text("something");
  m_Combo.append_text("something else");
  m_Combo.append_text("something or other");

  /*
  //Create a mixed entry an add it to the combo's list using the advanced interface ComboDropDown:
  Gtk::ComboDropDownItem* item = Gtk::manage(new Gtk::ComboDropDownItem);

  Gtk::HBox* hbox = Gtk::manage(new Gtk::HBox(false, 3));
  hbox->pack_start(*Gtk::manage(new Gtk::Image(Gtk::Stock::CLEAR, Gtk::ICON_SIZE_MENU)), Gtk::PACK_SHRINK);
  hbox->pack_start(*Gtk::manage(new Gtk::Label("some image - cool!")), Gtk::PACK_SHRINK);

  item->add(*hbox);
  item->show_all();
  m_Combo.get_list()->children().push_back(*item);
  
  m_Combo.set_item_string(*item, "you selected the image!");
  */
  
  //Restrict it to these choices only:
  //m_Combo.set_value_in_list();

  add(m_Combo);

  //Connect signal handler:
  m_Combo.signal_changed().connect( SigC::slot(*this, &ExampleWindow::on_combo_changed) );

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

