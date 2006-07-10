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

#ifndef GTKMM_EXAMPLE_RANGEWIDGETS_H
#define GTKMM_EXAMPLE_RANGEWIDGETS_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/scale.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/separator.h>
#include <gtkmm/scrollbar.h>
#include <gtkmm/menu.h>
#include <gtkmm/button.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  //Signal handlers:
  virtual void on_checkbutton_toggled();
  virtual void on_menu_position(Gtk::PositionType type);
  virtual void on_menu_policy(Gtk::UpdateType type);
  virtual void on_adjustment1_value_changed();
  virtual void on_adjustment2_value_changed();
  virtual void on_button_quit();

  //Child widgets:
  Gtk::VBox m_VBox_Top, m_VBox2, m_VBox_HScale;
  Gtk::HBox m_HBox_Scales, m_HBox_Digits, m_HBox_PageSize;

  Gtk::Adjustment m_adjustment, m_adjustment_digits, m_adjustment_pagesize;

  Gtk::VScale m_VScale;
  Gtk::HScale m_HScale, m_Scale_Digits, m_Scale_PageSize;

  Gtk::HSeparator m_Separator;

  Gtk::CheckButton m_CheckButton;

  Gtk::HScrollbar m_Scrollbar;

  Gtk::Menu m_Menu_Position, m_Menu_Policy;

  Gtk::Button m_Button_Quit;
};

#endif //GTKMM_EXAMPLE_RANGEWIDGETS_H
