//$Id$ -*- c++ -*-

/* gtkmm example Copyright (C) 2003 gtkmm development team
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

#ifndef GTKMM_EXAMPLE_TIMEREXAMPLE_H
#define GTKMM_EXAMPLE_TIMEREXAMPLE_H

#include <gtkmm.h>
#include <iostream>
#include <map>

class TimerExample : public Gtk::Window
{
public:
  TimerExample();

protected:
  // signal handlers
  void add_timer_pressed();
  void del_timer_pressed();
  // this is the callback function the timeout will call
  bool on_timer_callback(int timer_nr);

  // member data
  Gtk::HBox m_box;
  // Buttons for adding & deleting a timer and quitting the app
  Gtk::Button m_add_timer, m_del_timer, m_quit;
  // keep track of the timers being added
  int m_timer_number;
  // these two constants are initialized in the member initializer
  const int count_value;
  const int timeout_value;
  // STL map for storing our connections
  std::map<int,SigC::Connection> m_timers;
  // STL map for storing our timer values
  // each timer counts back from COUNT_VALUE to 0 and
  // is removed when it reaches 0
  std::map<int,int> m_counters;
};

#endif // GTKMM_EXAMPLE_TIMEREXAMPLE_H
