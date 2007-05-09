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
{
  set_title("Gtk::ColorButton example");
  set_default_size(200, 200);

  add(m_VBox);

  m_VBox.pack_start(m_Button, Gtk::PACK_SHRINK);
  m_Button.signal_color_set().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_color_set) );

  //Set start color:
  m_Color.set_red(0);
  m_Color.set_blue(65535);
  m_Color.set_green(0);
  m_Button.set_color(m_Color);

  m_DrawingArea.modify_bg(Gtk::STATE_NORMAL, m_Color);

  m_VBox.pack_start(m_DrawingArea);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_color_set()
{
  //Store the chosen color, and show it:
  m_Color = m_Button.get_color();
  m_DrawingArea.modify_bg(Gtk::STATE_NORMAL, m_Color);
}
