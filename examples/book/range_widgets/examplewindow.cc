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
#include "labeledoptionmenu.h"
#include <iostream>

ExampleWindow::ExampleWindow()
:
  m_VBox2(false, 20),
  m_VBox_HScale(false, 10),
  m_HBox_Scales(false, 10),
  m_HBox_Digits(false, 10),
  m_HBox_PageSize(false, 10),

  // value, lower, upper, step_increment, page_increment, page_size
  // note that the page_size value only makes a difference for
  // scrollbar widgets, and the highest value you'll get is actually
  // (upper - page_size).
  m_adjustment(0.0, 0.0, 101.0, 0.1, 1.0, 1.0),
  m_adjustment_digits(1.0, 0.0, 5.0),
  m_adjustment_pagesize(1.0, 1.0, 101.0),

  m_VScale(m_adjustment),
  m_HScale(m_adjustment),
  m_Scale_Digits(m_adjustment_digits),
  m_Scale_PageSize(m_adjustment_pagesize),

  // a checkbutton to control whether the value is displayed or not
  m_CheckButton("Display value on scale widgets", 0),

  // reuse the same adjustment again
  m_Scrollbar(m_adjustment),
  // notice how this causes the scales to always be update
  // continuously when the scrollbar is moved

  m_Button_Quit("Quit")
{
  set_title("range controls");

  //VScale:
  m_VScale.set_update_policy(Gtk::UPDATE_CONTINUOUS);
  m_VScale.set_digits(1);
  m_VScale.set_value_pos(Gtk::POS_TOP);
  m_VScale.set_draw_value();

  //HScale:
  m_HScale.set_update_policy(Gtk::UPDATE_CONTINUOUS);
  m_HScale.set_digits(1);
  m_HScale.set_value_pos(Gtk::POS_TOP);
  m_HScale.set_draw_value();
  m_HScale.set_size_request(200, 30);

  add(m_VBox_Top);
  m_VBox_Top.pack_start(m_VBox2);
  m_VBox2.set_border_width(10);
  m_VBox2.pack_start(m_HBox_Scales);

  //Put VScale and HScale (above scrollbar) side-by-side.
  m_HBox_Scales.pack_start(m_VScale);
  m_HBox_Scales.pack_start(m_VBox_HScale);

  m_VBox_HScale.pack_start(m_HScale);

  //Scrollbar:
  m_Scrollbar.set_update_policy(Gtk::UPDATE_CONTINUOUS);
  m_VBox_HScale.pack_start(m_Scrollbar);

  //CheckButton:
  m_CheckButton.set_active();
  m_CheckButton.signal_toggled().connect( sigc::mem_fun(*this, &ExampleWindow::on_checkbutton_toggled) );
  m_VBox2.pack_start(m_CheckButton);

  //OptionMenus:
  {
      using namespace Gtk::Menu_Helpers;

      MenuList& list_vpos = m_Menu_Position.items();
      list_vpos.push_back(
        MenuElem("Top", sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_menu_position), Gtk::POS_TOP)) );
      list_vpos.push_back(
        MenuElem("Bottom", sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_menu_position), Gtk::POS_BOTTOM)) );
      list_vpos.push_back(
        MenuElem("Left", sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_menu_position), Gtk::POS_LEFT)) );
      list_vpos.push_back(
        MenuElem("Right", sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_menu_position), Gtk::POS_RIGHT)) );

      m_VBox2.pack_start( *Gtk::manage(new LabeledOptionMenu("Scale Value Position:", m_Menu_Position)) );


      MenuList& list_upd = m_Menu_Policy.items();
      list_upd.push_back(
        MenuElem("Continuous", sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_menu_policy), Gtk::UPDATE_CONTINUOUS)) );
      list_upd.push_back(
        MenuElem("Discontinuous", sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_menu_policy), Gtk::UPDATE_DISCONTINUOUS)) );
      list_upd.push_back(
        MenuElem("Delayed", sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_menu_policy), Gtk::UPDATE_DELAYED)) );

      m_VBox2.pack_start( *Gtk::manage(new LabeledOptionMenu("Scale Update Policy:", m_Menu_Policy)) );
  }

  //Digits:
  m_HBox_Digits.pack_start(*Gtk::manage(new Gtk::Label("Scale Digits:", 0)),  Gtk::PACK_SHRINK);
  m_Scale_Digits.set_digits(0);
  m_adjustment_digits.signal_value_changed().connect( sigc::mem_fun(*this, &ExampleWindow::on_adjustment1_value_changed) );
  m_HBox_Digits.pack_start(m_Scale_Digits);

  //Page Size:
  m_HBox_PageSize.pack_start(*Gtk::manage(new Gtk::Label("Scrollbar Page Size:", 0)), Gtk::PACK_SHRINK);
  m_Scale_PageSize.set_digits(0);
  m_adjustment_pagesize.signal_value_changed().connect( sigc::mem_fun(*this, &ExampleWindow::on_adjustment2_value_changed) );
  m_HBox_PageSize.pack_start(m_Scale_PageSize);

  m_VBox2.pack_start(m_HBox_Digits);
  m_VBox2.pack_start(m_HBox_PageSize);
  m_VBox_Top.pack_start(m_Separator, Gtk::PACK_SHRINK);
  m_VBox_Top.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);

  m_Button_Quit.set_flags(Gtk::CAN_DEFAULT);
  m_Button_Quit.grab_default();
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this, &ExampleWindow::on_button_quit) );
  m_Button_Quit.set_border_width(10);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_checkbutton_toggled()
{
    m_VScale.set_draw_value(m_CheckButton.get_active());
    m_HScale.set_draw_value(m_CheckButton.get_active());
}

void ExampleWindow::on_menu_position(Gtk::PositionType postype)
{
    m_VScale.set_value_pos(postype);
    m_HScale.set_value_pos(postype);
}

void ExampleWindow::on_menu_policy(Gtk::UpdateType type)
{
    m_VScale.set_update_policy(type);
    m_HScale.set_update_policy(type);
}

void ExampleWindow::on_adjustment1_value_changed()
{
    double val = m_adjustment_digits.get_value();
    m_VScale.set_digits((int)val);
    m_HScale.set_digits((int)val);
}

void ExampleWindow::on_adjustment2_value_changed()
{
    double val = m_adjustment_pagesize.get_value();
    m_adjustment.set_page_size((int)val);
    m_adjustment.set_page_increment((int)val);

    // note that we don't have to emit the "changed" signal;
    // gtkmm does this for us
}

void ExampleWindow::on_button_quit()
{
  hide();
}
