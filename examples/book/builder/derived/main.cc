//$Id: main.cc 824 2006-02-22 21:46:32Z murrayc $ -*- c++ -*-

/* libglademm example Copyright (C) 2003 libglademm development team
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

#include "deriveddialog.h"
#include <iostream>

int main (int argc, char **argv)
{
  Gtk::Main kit(argc, argv);

  //Load the Glade file and instiate its widgets:
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
    refBuilder->add_from_file("basic.ui");
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
#else
  std::auto_ptr<Glib::Error> error;

  if (!refBuilder->add_from_file("basic.ui", error))
  {
    std::cerr << error->what() << std::endl;
    return 1;
  }
#endif /* !GLIBMM_EXCEPTIONS_ENABLED */

  //Get the GtkBuilder-instantiated dialog::
  DerivedDialog* pDialog = 0;
  refBuilder->get_widget_derived("DialogBasic", pDialog);
  if(pDialog)
  {
    //Start:
    kit.run(*pDialog);
  }

  delete pDialog;
    

  return 0;
}
