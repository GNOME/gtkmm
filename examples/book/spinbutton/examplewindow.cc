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
#include <stdio.h>

ExampleWindow::ExampleWindow()
:
  m_Frame_NotAccelerated("Not accelerated"),
  m_Frame_Accelerated("Accelerated"),
  m_VBox_Main(false, 5),
  m_Label_Day("Day :"), m_Label_Month("Month: "), m_Label_Year("Year: "),
  m_Label_Value("Value: "),
  m_Label_Digits("Digits: "),
  m_adjustment_day(1.0, 1.0, 31.0, 1.0, 5.0, 0.0),
  m_adjustment_month(1.0, 1.0, 12.0, 1.0, 5.0, 0.0),
  m_adjustment_year(1998.0, 0.0, 2100.0, 1.0, 100.0, 0.0),
  m_adjustment_value(0.0, -10000.0, 10000.0, 0.5, 100.0, 0.0),
  m_adjustment_digits(2.0, 1.0, 5.0, 1.0, 1.0, 0.0),
  m_SpinButton_Day(m_adjustment_day),
  m_SpinButton_Month(m_adjustment_month),
  m_SpinButton_Year(m_adjustment_year),
  m_SpinButton_Value(m_adjustment_value, 1.0, 2),
  m_SpinButton_Digits(m_adjustment_digits),
  m_CheckButton_Snap("Snap to 0.5-ticks"),
  m_CheckButton_Numeric("Numeric only input mode"),
  m_Button_Int("Value as Int"),
  m_Button_Float("Value as Float"),
  m_Button_Close("Close")
{
  set_title("SpinButton");

  m_VBox_Main.set_border_width(10);
  add(m_VBox_Main);

  m_VBox_Main.pack_start(m_Frame_NotAccelerated);

  m_VBox.set_border_width(5);
  m_Frame_NotAccelerated.add(m_VBox);

  /* Day, month, year spinners */

  m_VBox.pack_start(m_HBox_NotAccelerated, Gtk::PACK_EXPAND_WIDGET, 5);

  m_Label_Day.set_alignment(Gtk::ALIGN_LEFT);
  m_VBox_Day.pack_start(m_Label_Day);

  m_SpinButton_Day.set_wrap();

  m_VBox_Day.pack_start(m_SpinButton_Day);

  m_HBox_NotAccelerated.pack_start(m_VBox_Day, Gtk::PACK_EXPAND_WIDGET, 5);

  m_Label_Month.set_alignment(Gtk::ALIGN_LEFT);
  m_VBox_Month.pack_start(m_Label_Month);

  m_SpinButton_Month.set_wrap();
  m_VBox_Month.pack_start(m_SpinButton_Month);

  m_HBox_NotAccelerated.pack_start(m_VBox_Month, Gtk::PACK_EXPAND_WIDGET, 5);

  m_Label_Year.set_alignment(Gtk::ALIGN_LEFT);
  m_VBox_Year.pack_start(m_Label_Year);

  m_SpinButton_Year.set_wrap();
  m_SpinButton_Year.set_size_request(55, -1);
  m_VBox_Year.pack_start(m_SpinButton_Year);

  m_HBox_NotAccelerated.pack_start(m_VBox_Year, Gtk::PACK_EXPAND_WIDGET, 5);

  //Accelerated:
  m_VBox_Main.pack_start(m_Frame_Accelerated);

  m_VBox_Accelerated.set_border_width(5);
  m_Frame_Accelerated.add(m_VBox_Accelerated);

  m_VBox_Accelerated.pack_start(m_HBox_Accelerated, Gtk::PACK_EXPAND_WIDGET, 5);

  m_HBox_Accelerated.pack_start(m_VBox_Value, Gtk::PACK_EXPAND_WIDGET, 5);

  m_Label_Value.set_alignment(Gtk::ALIGN_LEFT);
  m_VBox_Value.pack_start(m_Label_Value);

  m_SpinButton_Value.set_wrap();
  m_SpinButton_Value.set_size_request(100, -1);
  m_VBox_Value.pack_start(m_SpinButton_Value);

  m_HBox_Accelerated.pack_start(m_VBox_Digits, Gtk::PACK_EXPAND_WIDGET, 5);

  m_Label_Digits.set_alignment(Gtk::ALIGN_LEFT);
  m_VBox_Digits.pack_start(m_Label_Digits);

  m_SpinButton_Digits.set_wrap();
  m_adjustment_digits.signal_value_changed().connect( SigC::slot(*this, &ExampleWindow::on_spinbutton_digits_changed) );

  m_VBox_Digits.pack_start(m_SpinButton_Digits);


  //CheckButtons:
  m_VBox_Accelerated.pack_start(m_CheckButton_Snap);
  m_CheckButton_Snap.set_active();
  m_CheckButton_Snap.signal_clicked().connect( SigC::slot(*this, &ExampleWindow::on_checkbutton_snap) );

  m_VBox_Accelerated.pack_start(m_CheckButton_Numeric);
  m_CheckButton_Numeric.set_active();
  m_CheckButton_Numeric.signal_clicked().connect( SigC::slot(*this, &ExampleWindow::on_checkbutton_numeric) );


  //Buttons:
  m_VBox_Accelerated.pack_start (m_HBox_Buttons, Gtk::PACK_SHRINK, 5);

  m_Button_Int.signal_clicked().connect(bind(slot(*this,&ExampleWindow::on_button_getvalue), VALUE_FORMAT_INT));
  m_HBox_Buttons.pack_start(m_Button_Int, Gtk::PACK_EXPAND_WIDGET, 5);

  m_Button_Float.signal_clicked().connect(bind(slot(*this,&ExampleWindow::on_button_getvalue), VALUE_FORMAT_FLOAT));
  m_HBox_Buttons.pack_start(m_Button_Float, Gtk::PACK_EXPAND_WIDGET, 5);

  m_VBox_Accelerated.pack_start(m_Label_ShowValue);
  m_Label_ShowValue.set_text("0");

  //Close button:
  m_Button_Close.signal_clicked().connect( SigC::slot(*this, &ExampleWindow::on_button_close) );
  m_VBox_Main.pack_start(m_Button_Close, Gtk::PACK_SHRINK);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}


void ExampleWindow::on_button_close()
{
  hide();
}

void ExampleWindow::on_checkbutton_snap()
{
  m_SpinButton_Value.set_snap_to_ticks( m_CheckButton_Snap.get_active() );
}

void ExampleWindow::on_checkbutton_numeric()
{
  m_SpinButton_Value.set_numeric( m_CheckButton_Numeric.get_active() );
}

void ExampleWindow::on_spinbutton_digits_changed()
{
  m_SpinButton_Value.set_digits( m_SpinButton_Digits.get_value_as_int() );
}

void ExampleWindow::on_button_getvalue(enumValueFormats display)
{
  gchar buf[32];

  if (display == VALUE_FORMAT_INT)
    sprintf (buf, "%d", m_SpinButton_Value.get_value_as_int());
  else
    sprintf (buf, "%0.*f", m_SpinButton_Value.get_digits(), m_SpinButton_Value.get_value());

  m_Label_ShowValue.set_text(buf);
}
