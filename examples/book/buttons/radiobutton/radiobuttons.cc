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

#include "radiobuttons.h"


RadioButtons::RadioButtons() :
  m_Box1(false, 10),
  m_Box2(false, 10),
  m_RadioButton1("button1"),
  m_RadioButton2("button2"),
  m_RadioButton3("button3"),
  m_Button_Close("close")
{
  set_title("radio buttons");
  set_border_width(0);

  //Put radio buttons 2 and 3 in the same group as 1:
  Gtk::RadioButton::Group group = m_RadioButton1.get_group();
  m_RadioButton2.set_group(group);
  m_RadioButton3.set_group(group);

  add(m_Box_Top);

  //Put Box1 in m_Box_Top:
  m_Box1.set_border_width(10);
  m_Box_Top.pack_start(m_Box1);

  //Put the radio buttons in Box1:
  m_Box1.pack_start(m_RadioButton1);
  m_Box1.pack_start(m_RadioButton2);
  m_Box1.pack_start(m_RadioButton3);
  m_RadioButton2.set_active();

  //Add a separator:
  m_Box_Top.pack_start(m_Separator, Gtk::PACK_SHRINK);

  //Put Box2 in m_Box_Top:
  m_Box2.set_border_width(10);
  m_Box_Top.pack_start(m_Box2, Gtk::PACK_SHRINK);

  //Put Close button in Box2:
  m_Box2.pack_start(m_Button_Close);
  m_Button_Close.set_flags(Gtk::CAN_DEFAULT);
  m_Button_Close.grab_default();

  m_Button_Close.signal_clicked().connect( sigc::mem_fun(*this, &RadioButtons::on_button_clicked) );

  show_all_children();
}

RadioButtons::~RadioButtons()
{
}

void RadioButtons::on_button_clicked()
{
  hide(); //to close the application.
}
