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
: m_Button_Close("Close"),
  m_CheckButton_Editable("Editable"),
  m_CheckButton_Visible("Visible")
{
  set_size_request(200, 100);
  set_title("Gtk::Entry");

  add(m_VBox);

  m_Entry.set_max_length(50);
  m_Entry.set_text("hello");
  m_Entry.set_text(m_Entry.get_text() + " world");
  m_Entry.select_region(0, m_Entry.get_text_length());
  m_VBox.pack_start(m_Entry);

  // Note that add() can also be used instead of pack_xxx()
  m_VBox.add(m_HBox);

  m_HBox.pack_start(m_CheckButton_Editable);
  m_CheckButton_Editable.signal_toggled().connect( sigc::mem_fun(*this, &ExampleWindow::on_checkbox_editable_toggled) );
  m_CheckButton_Editable.set_active(true);

  m_HBox.pack_start(m_CheckButton_Visible);
  m_CheckButton_Visible.signal_toggled().connect( sigc::mem_fun(*this, &ExampleWindow::on_checkbox_visibility_toggled) );
  m_CheckButton_Visible.set_active(true);

  m_Button_Close.signal_clicked().connect( sigc::mem_fun(*this, &ExampleWindow::on_button_close) );
  m_VBox.pack_start(m_Button_Close);
  m_Button_Close.set_flags(Gtk::CAN_DEFAULT);
  m_Button_Close.grab_default();

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_checkbox_editable_toggled()
{
  m_Entry.set_editable(m_CheckButton_Editable.get_active());
}

void ExampleWindow::on_checkbox_visibility_toggled()
{
  m_Entry.set_visibility(m_CheckButton_Visible.get_active());
}

void ExampleWindow::on_button_close()
{
  hide();
}

