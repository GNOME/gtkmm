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

#ifndef GTKMM_EXAMPLE_RADIOBUTTONS_H
#define GTKMM_EXAMPLE_RADIOBUTTONS_H

#include <gtkmm/window.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/box.h>
#include <gtkmm/separator.h>

class RadioButtons : public Gtk::Window
{
public:
  RadioButtons();
  virtual ~RadioButtons();

protected:
  //Signal handlers:
  virtual void on_button_clicked();

  //Child widgets:
  Gtk::VBox m_Box_Top, m_Box1, m_Box2;
  Gtk::RadioButton m_RadioButton1, m_RadioButton2, m_RadioButton3;
  Gtk::HSeparator m_Separator;
  Gtk::Button m_Button_Close;
};

#endif //GTKMM_EXAMPLE_RADIOBUTTONS_H
