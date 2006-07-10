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

#include <gtkmm/fileselection.h>
#include "examplewindow.h"
#include <iostream>


ExampleWindow::ExampleWindow()
: m_Button_File("Choose File"),
  m_Button_Folder("Choose Folder")
{
  set_title("Gtk::FileSelection example");

  add(m_ButtonBox);

  m_ButtonBox.pack_start(m_Button_File);
  m_Button_File.signal_clicked().connect( sigc::mem_fun(*this, &ExampleWindow::on_button_file_clicked) );

  m_ButtonBox.pack_start(m_Button_Folder);
  m_Button_Folder.signal_clicked().connect( sigc::mem_fun(*this, &ExampleWindow::on_button_folder_clicked) );

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_folder_clicked()
{
#ifndef GTKMM_DISABLE_DEPRECATED
  Gtk::FileSelection dialog("Please choose a folder");
  dialog.set_transient_for(*this);
  dialog.get_file_list()->get_parent()->hide(); //Prevent the user from selecting a file.

  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      std::cout << "OK clicked." << std::endl;
      std::cout << "Folder selected: " << dialog.get_filename() << std::endl;
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
#else
  std::cout << "Gtk::FileSelection is deprecated and gtkmm has not been compiled with support for deprecated widgets" << std::endl;
#endif //GTKMM_DISABLE_DEPRECATED
}

void ExampleWindow::on_button_file_clicked()
{
#ifndef GTKMM_DISABLE_DEPRECATED
  Gtk::FileSelection dialog("Please choose a file");
  dialog.set_transient_for(*this);
  
  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      std::cout << "OK clicked." << std::endl;

      std::string filename = dialog.get_filename(); //Notice that it is a std::string, not a Glib::ustring.
      std::cout << "File selected: " <<  filename << std::endl;
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
#else
  std::cout << "Gtk::FileSelection is deprecated and gtkmm has not been compiled with support for deprecated widgets" << std::endl;
#endif //GTKMM_DISABLE_DEPRECATED
}
