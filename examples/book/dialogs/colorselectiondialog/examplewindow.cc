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
: m_Button("Show Dialog")
{
  set_title("Gtk::ColorSelectionDialog example");
  set_default_size(200, 200);
  
  add(m_VBox);
  
  m_VBox.pack_start(m_Button, Gtk::PACK_SHRINK);
  m_Button.signal_clicked().connect( SigC::slot(*this, &ExampleWindow::on_button_clicked) );

  //Set start color:
  m_Color.set_red(0);
  m_Color.set_blue(65535);
  m_Color.set_green(0);
  m_DrawingArea.modify_bg(Gtk::STATE_NORMAL, m_Color);
  
  m_VBox.pack_start(m_DrawingArea);
  
  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_clicked()
{
  Gtk::ColorSelectionDialog dialog;

  //Set the current color:
  Gtk::ColorSelection* pColorSel = dialog.get_colorsel();
  pColorSel->set_current_color(m_Color);
  
  int result = dialog.run();
  
  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      //Store the chosen color, and show it:
      m_Color = pColorSel->get_current_color();
      m_DrawingArea.modify_bg(Gtk::STATE_NORMAL, m_Color);
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
}
