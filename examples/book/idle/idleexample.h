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

#ifndef GTKMM_EXAMPLE_IDLEEXAMPLE_H
#define GTKMM_EXAMPLE_IDLEEXAMPLE_H

#include <gtkmm.h>
#include <iostream>

class IdleExample : public Gtk::Window
{
public:
  IdleExample();

protected:
  // Signal Handlers:
  bool on_timer();
  bool on_idle();

  // Member data:
  Gtk::VBox m_Box;
  Gtk::Button m_ButtonQuit;
  Gtk::ProgressBar m_ProgressBar_c;
  Gtk::ProgressBar m_ProgressBar_d;
};

#endif // GTKMM_EXAMPLE_IDLEEXAMPLE_H
