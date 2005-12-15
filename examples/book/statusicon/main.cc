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

#include <gtkmm.h>

int main(int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);

  Glib::RefPtr<Gtk::StatusIcon> status_icon = Gtk::StatusIcon::create(Gtk::Stock::HELP); //Use your own icon in real life.
  status_icon->set_tooltip("gtkmm StatusIcon example tooltip.");

  //Show a window:
  //The program will stop, and the status icon will disappear, when the window is closed.
  Gtk::Window window;
  window.set_title("gtkmm StatusIcon example.");
  window.set_default_size(300, 300);
  Gtk::Main::run(window); //Shows the window and returns when it is closed.

  return 0;
}
