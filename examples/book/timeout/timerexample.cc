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

#include "timerexample.h"
#include <gtkmm/main.h>
#include <iostream>

const gint TimerExample::COUNT_VALUE = 5;
const gint TimerExample::TIMEOUT_VALUE = 1500;


TimerExample::TimerExample() :
  m_box(true, 10),
  m_add_timer("add a new timer"),
  m_del_timer("remove timer"),
  m_quit("Quit"),
  m_t_nr(0)
{
  // connect the signal handlers:
  m_quit.signal_pressed().connect(SigC::slot(*this, &Gtk::Widget::hide));
  m_add_timer.signal_pressed().connect(SigC::slot(*this, &TimerExample::add_timer_pressed));
  m_del_timer.signal_pressed().connect(SigC::slot(*this, &TimerExample::del_timer_pressed));

  // put buttons into container:
  m_box.pack_start(m_add_timer);
  m_box.pack_start(m_del_timer);
  m_box.pack_start(m_quit);

  // set border and display all
  set_border_width(10);
  add(m_box);
  show_all();
}

TimerExample::~TimerExample()
{
}


void TimerExample::add_timer_pressed()
{
  // creation of a new object prevents long lines and
  // shows us a little how slots work
  // we have 0 parameters and gint as return value after calling SigC::bind
  SigC::Slot0<bool> my_slot = SigC::bind(SigC::slot(*this, &TimerExample::timer_callback), m_t_nr);

  // now connect the slot to Glib::signal_timeout()
  SigC::Connection conn = Glib::signal_timeout().connect(my_slot, TIMEOUT_VALUE);

  // memorize connection
  m_timers[m_t_nr] = conn;

  // initialize timer count
  m_counters[m_t_nr] = COUNT_VALUE + 1;

  // print some information on the console
  std::cout << "added timeout " << m_t_nr++ << std::endl;
}


void TimerExample::del_timer_pressed()
{
  // are there any timers ?
  if(m_timers.empty())
  {
    // nope
    std::cout << "Sorry, there are no timers left" << std::endl;
  }
  else
  {
    // get the nr of the first timer
    gint timer_nr = m_timers.begin()->first;

    // give a little information to the user
    std::cout << "Removing timer " << timer_nr << std::endl;

    // delete the entry in the counter values
    m_counters.erase(timer_nr);

    // TODO: Is this still necessary?
    // destroy the connection !!!!!
    // this is important since the connection is NOT destroyed when
    // the according Connection-Object is deleted
    // The purpose of the connection object is to give you the
    // possibility to destroy a connection without having to destroy
    // either the sender or the receiver
    // Try it and comment out the following line ....
    m_timers[timer_nr].disconnect();
    // destroy the connection
    m_timers.erase(timer_nr);
  }
}


bool TimerExample::timer_callback(gint timer_nr)
{
  // print the timer number
  std::cout << "This is timer " << timer_nr;

  // decrement & check counter value
  if(--m_counters[timer_nr] == 0)
  {
    std::cout << " boom" << std::endl;

    // delete the counter entry
    m_counters.erase(timer_nr);

    // delete the connection entry
    m_timers.erase(timer_nr);

    // note that we do not need to call disconnect on the connection
    // since we Gtk::Main does this for us when we return 0
    return false;
  }

  // print the timer value
  std::cout << " - " << m_counters[timer_nr] << "/" << COUNT_VALUE << std::endl;
  return true;
}

