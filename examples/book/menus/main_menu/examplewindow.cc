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
#include <gtkmm/stock.h>
#include <iostream>

ExampleWindow::ExampleWindow()
{
  set_title("main_menu example");
  set_default_size(200, 200);

  add(m_Box); //We can put a MenuBar at the top of the box and other stuff below it.

  //Fill menus:

  //File|New sub menu:
  {
  	Gtk::Menu::MenuList& menulist = m_Menu_File_New.items();

  	menulist.push_back( Gtk::Menu_Helpers::MenuElem("_New Foo",  Gtk::Menu::AccelKey("<control>n"),
      SigC::slot(*this, &ExampleWindow::on_menu_file_new_generic) ) );
  	menulist.push_back( Gtk::Menu_Helpers::MenuElem("New _Goo",
      SigC::slot(*this, &ExampleWindow::on_menu_file_new_generic) ) );
  }

  //File menu:
  {
  	Gtk::Menu::MenuList& menulist = m_Menu_File.items();

  	menulist.push_back( Gtk::Menu_Helpers::MenuElem("_New", m_Menu_File_New) ); //Add sub menu.
  	menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Quit",  Gtk::Menu::AccelKey("<control>q"),
      SigC::slot(*this, &ExampleWindow::on_menu_file_quit) ) );
  }

  //Edit menu:
  {
    Gtk::Menu::MenuList& menulist = m_Menu_Edit.items();

    menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Copy",
      SigC::slot(*this, &ExampleWindow::on_menu_others) ) );

    menulist.push_back( Gtk::Menu_Helpers::MenuElem("_Paste",
      SigC::slot(*this, &ExampleWindow::on_menu_others) ) );

    menulist.push_back( Gtk::Menu_Helpers::CheckMenuElem("Something",
      SigC::slot(*this, &ExampleWindow::on_menu_others) ) );
  }
  
  //Help menu: (exercise stock items)
  {
    Gtk::Menu::MenuList& menulist = m_Menu_Help.items();
    
    menulist.push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::CDROM,
      SigC::slot(*this, &ExampleWindow::on_menu_others) ) );
  }

  //Add the menus to the MenuBar:
  m_MenuBar.items().push_back( Gtk::Menu_Helpers::MenuElem("_File", m_Menu_File) );
  m_MenuBar.items().push_back( Gtk::Menu_Helpers::MenuElem("_Edit", m_Menu_Edit) );
  m_MenuBar.items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::HELP, m_Menu_Help) );

  //Add the MenuBar to the window:
  m_Box.pack_start(m_MenuBar, Gtk::PACK_SHRINK);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_menu_file_quit()
{
  hide(); //Closes the main window to stop the Gtk::Main::run().
}

void ExampleWindow::on_menu_file_new_generic()
{
   std::cout << "A File|New menu item was selected." << std::endl;
}

void ExampleWindow::on_menu_others()
{
  std::cout << "A menu item was selected." << std::endl;
}


