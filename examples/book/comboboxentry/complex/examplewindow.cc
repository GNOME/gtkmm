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
  set_title("ComboBoxEntry example");

  //Create the Tree model:
  //m_refTreeModel = Gtk::TreeStore::create(m_Columns);
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_Combo.set_model(m_refTreeModel);

  //Fill the ComboBox's Tree Model:
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = "1";
  row[m_Columns.m_col_name] = "Billy Bob";
  /*
  Gtk::TreeModel::Row childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_id] = 11;
  childrow[m_Columns.m_col_name] = "Billy Bob Junior";

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_id] = 12;
  childrow[m_Columns.m_col_name] = "Sue Bob";
  */

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = "2";
  row[m_Columns.m_col_name] = "Joey Jojo";


  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = "3";
  row[m_Columns.m_col_name] = "Rob McRoberts";

  /*
  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_id] = 31;
  childrow[m_Columns.m_col_name] = "Xavier McRoberts";
  */
  
  //Add the model columns to the Combo (which is a kind of view),
  //rendering them in the default way:
  //m_Combo.pack_start(m_Columns.m_col_id); //This is automatically rendered when we use set_text_column().
  m_Combo.pack_start(m_Columns.m_col_name); 

  m_Combo.set_text_column(m_Columns.m_col_id);

  //Add the ComboBox to the window.
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
  Gtk::Entry* entry = m_Combo.get_entry();
  //Note: to get changes only when the entry has been completed, 
  //instead of on every key press, connect to Entry::signal_changed() 
  //instead of ComboBoxEntry::signal_changed.

  if(entry)
  {
    std::cout << " ID=" << entry->get_text() << std::endl;
  }
}

