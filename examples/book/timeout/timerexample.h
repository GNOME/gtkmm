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

#ifndef GTKMM_EXAMPLE_TIMEREXAMPLE_H
#define GTKMM_EXAMPLE_TIMEREXAMPLE_H

#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <map>

class TimerExample : public Gtk::Window
{
public:
  TimerExample();
  virtual ~TimerExample();

protected:

  // the callback functions for add & remove button
  void add_timer_pressed();
  void del_timer_pressed();

  // the callback for the timer
  // note that is not of the type gint callback(void)
  // since we use bind() to add a data value of type gint to it
  bool timer_callback(gint timer_nr);

  // the usual stuff - nothing exciting
  Gtk::HBox   m_box;
  Gtk::Button m_add_timer, m_del_timer, m_quit;
  gint m_t_nr;

  // the start value for our timer
  static const gint COUNT_VALUE;

  // the timeout value for the timers in [ms]
  static const gint TIMEOUT_VALUE;

  // we need this to store our connections
  std::map<gint, SigC::Connection> m_timers;

  // this is for storing our timer values
  // each timer countsa back from COUNT_VALUE to 0 and
  // if removed when it reaches 0
  std::map<gint,gint> m_counters;
};


#endif // GTKMM_EXAMPLE_TIMEREXAMPLE_H

