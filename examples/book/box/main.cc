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

#include <iostream>
#include <cstdlib>
#include <gtkmm/main.h>
#include "examplewindow.h"

using std::atoi;

int main(int argc, char *argv[])
{
  Gtk::Main main_instance(argc, argv);

  if(argc != 2)
  {
    std::cerr << "usage: packbox num, where num is 1, 2, or 3." << std::endl;
    // this just does cleanup in GTK, and exits with an exit status of 1.
    gtk_exit (1);
  }

  ExampleWindow window( atoi(argv[1]) );
  Gtk::Main::run(window); //Shows the window and returns when it is closed.

  return 0;
}
