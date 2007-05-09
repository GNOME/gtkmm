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
: m_VBox(false, 5),
  m_Alignment(0.5, 0.5, 0, 0),
  m_Table(2, 2, true),
  m_CheckButton_Text("Show text"),
  m_CheckButton_Activity("Activity mode"),
  m_CheckButton_Orientation("Right to Left"),
  m_Button_Close("Close"),
  m_bActivityMode(false)
{
  set_resizable();
  set_title("Gtk::ProgressBar");

  m_VBox.set_border_width(10);
  add(m_VBox);

  m_VBox.pack_start(m_Alignment, Gtk::PACK_SHRINK, 5);
  m_Alignment.add(m_ProgressBar);

  //Add a timer callback to update the value of the progress bar:
  m_connection_id_timeout = Glib::signal_timeout().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_timeout), 50 );

  m_VBox.pack_start(m_Separator, Gtk::PACK_SHRINK);
  m_VBox.pack_start(m_Table);

  //Add a check button to select displaying of the trough text:
  m_Table.attach(m_CheckButton_Text, 0, 1, 0, 1, Gtk::EXPAND | Gtk::FILL,
          Gtk::EXPAND | Gtk::FILL, 5, 5);
  m_CheckButton_Text.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_checkbutton_text) );

  //Add a check button to select displaying of the trough text:
  m_Table.attach(m_CheckButton_Activity, 0, 1, 1, 2, Gtk::EXPAND | Gtk::FILL,
          Gtk::EXPAND | Gtk::FILL, 5, 5);
  m_CheckButton_Activity.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_checkbutton_activity) );

  //Add a check button to toggle activity mode:
  m_Table.attach(m_CheckButton_Orientation, 0, 1, 2, 3, Gtk::EXPAND | Gtk::FILL,
          Gtk::EXPAND | Gtk::FILL, 5, 5);
  m_CheckButton_Orientation.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_checkbutton_orientation) );

  //Add a button to exit the program.
  m_VBox.pack_start(m_Button_Close, Gtk::PACK_SHRINK);
  m_Button_Close.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_close) );
  m_Button_Close.set_flags(Gtk::CAN_DEFAULT);
  m_Button_Close.grab_default();

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_checkbutton_text()
{
  const Glib::ustring text = m_ProgressBar.get_text();

  if(!text.empty())
    m_ProgressBar.set_text("");
  else
    m_ProgressBar.set_text("some text");
}

void ExampleWindow::on_checkbutton_activity()
{
  m_bActivityMode = m_CheckButton_Activity.get_active();

  if(m_bActivityMode)
    m_ProgressBar.pulse();
  else
    m_ProgressBar.set_fraction(0.0);
}

void ExampleWindow::on_checkbutton_orientation()
{
  switch(m_ProgressBar.get_orientation())
  {
    case Gtk::PROGRESS_LEFT_TO_RIGHT:
      m_ProgressBar.set_orientation(Gtk::PROGRESS_RIGHT_TO_LEFT);
      break;
    case Gtk::PROGRESS_RIGHT_TO_LEFT:
      m_ProgressBar.set_orientation(Gtk::PROGRESS_LEFT_TO_RIGHT);
      break;
    default:
      break; // do nothing	
  }
}

void ExampleWindow::on_button_close()
{
  hide();
}

/* Update the value of the progress bar so that we get
 * some movement */
bool ExampleWindow::on_timeout()
{
  if(m_bActivityMode)
    m_ProgressBar.pulse();
  else
  {
    double new_val = m_ProgressBar.get_fraction() + 0.01;

    if(new_val > 1.0)
      new_val = 0.0;

    //Set the new value:
    m_ProgressBar.set_fraction(new_val);
  }

  //As this is a timeout function, return true so that it
  //continues to get called
  return true;
}

