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
#include <gtkmm.h>
#include <iostream>

ExampleWindow::ExampleWindow()
{
  set_title("main_menu example");
  set_default_size(200, 200);

  add(m_Box); //We can put a MenuBar at the top of the box and other stuff below it.

  //Define the actions:
  m_refActionGroup = Gtk::ActionGroup::create();
  
  m_refActionGroup->add( Gtk::Action::create("MenuFile", "_File") );
  m_refActionGroup->add( Gtk::Action::create("New", Gtk::Stock::NEW),
    sigc::mem_fun(*this, &ExampleWindow::on_action_file_new) );
  m_refActionGroup->add( Gtk::Action::create("Open", Gtk::Stock::OPEN),
    sigc::mem_fun(*this, &ExampleWindow::on_action_others) );

  register_stock_items(); //Makes the "example_stock_rain" stock item available.
  m_refActionGroup->add( Gtk::ToggleAction::create("Rain", Gtk::StockID("example_stock_rain") ),
    sigc::mem_fun(*this, &ExampleWindow::on_action_others) );

  m_refActionGroup->add( Gtk::Action::create("Quit", Gtk::Stock::QUIT),
    sigc::mem_fun(*this, &ExampleWindow::on_action_file_quit) );

  m_refActionGroup->add( Gtk::Action::create("MenuEdit", "_Edit") );
  m_refActionGroup->add( Gtk::Action::create("Cut", Gtk::Stock::CUT),
    sigc::mem_fun(*this, &ExampleWindow::on_action_others) );
  m_refActionGroup->add( Gtk::Action::create("Copy", Gtk::Stock::COPY),
    sigc::mem_fun(*this, &ExampleWindow::on_action_others) );
  m_refActionGroup->add( Gtk::Action::create("Paste", Gtk::Stock::PASTE),
    sigc::mem_fun(*this, &ExampleWindow::on_action_others) );

  //Define how the actions are presented in the menus and toolbars:
  Glib::RefPtr<Gtk::UIManager> m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(m_refActionGroup);
  add_accel_group(m_refUIManager->get_accel_group());

  //Layout the actions in a menubar and toolbar:
  Glib::ustring ui_info =
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='MenuFile'>"
        "      <menuitem action='New'/>"
        "      <menuitem action='Open'/>"
        "      <separator/>"
        "      <menuitem action='Rain'/>"
        "      <separator/>"
        "      <menuitem action='Quit'/>"
        "    </menu>"
        "    <menu action='MenuEdit'>"
        "      <menuitem action='Cut'/>"
        "      <menuitem action='Copy'/>"
        "      <menuitem action='Paste'/>"
        "    </menu>"
        "  </menubar>"
        "  <toolbar  name='ToolBar'>"
        "    <toolitem action='Open'/>"
        "    <toolitem action='Rain'/>"
        "    <toolitem action='Quit'/>"
        "  </toolbar>"
        "</ui>";

  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {      
    m_refUIManager->add_ui_from_string(ui_info);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "building menus and toolbars failed: " <<  ex.what();
  }
  #else
  std::auto_ptr<Glib::Error> ex;
  m_refUIManager->add_ui_from_string(ui_info, ex);
  if(ex.get())
  { 
    std::cerr << "building menus and toolbars failed: " <<  ex->what();
  }
  #endif //GLIBMM_EXCEPTIONS_ENABLED

  Gtk::Widget* pMenuBar = m_refUIManager->get_widget("/MenuBar") ;

  //Add the MenuBar to the window:
  m_Box.pack_start(*pMenuBar, Gtk::PACK_SHRINK);


  Gtk::Widget* pToolbar = m_refUIManager->get_widget("/ToolBar") ;

  //Add the MenuBar to the window:
  m_Box.pack_start(*pToolbar, Gtk::PACK_SHRINK);
  
  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_action_file_quit()
{
  hide(); //Closes the main window to stop the Gtk::Main::run().
}

void ExampleWindow::on_action_file_new()
{
   std::cout << "A File|New menu item was selected." << std::endl;
}

void ExampleWindow::on_action_others()
{
  std::cout << "A menu item was selected." << std::endl;
}


void ExampleWindow::add_stock_item(const Glib::RefPtr<Gtk::IconFactory>& factory,
                      const std::string& filepath,
                      const Glib::ustring& id, const Glib::ustring& label)
{
  Gtk::IconSource source;

  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
    //This throws an exception if the file is not found:
    source.set_pixbuf( Gdk::Pixbuf::create_from_file(filepath) );
  }
  catch(const Glib::Exception& ex)
  {
    std::cout << ex.what() << std::endl;
  }
  #else
  std::auto_ptr<Glib::Error> ex;
  source.set_pixbuf( Gdk::Pixbuf::create_from_file(filepath, ex) );
  if(ex.get())
  { 
    std::cerr <<  ex->what();
  }
  #endif //GLIBMM_EXCEPTIONS_ENABLED

  source.set_size(Gtk::ICON_SIZE_SMALL_TOOLBAR);
  source.set_size_wildcarded(); //Icon may be scaled.

  Gtk::IconSet icon_set;
  icon_set.add_source(source); //More than one source per set is allowed.

  const Gtk::StockID stock_id(id);
  factory->add(stock_id, icon_set);
  Gtk::Stock::add(Gtk::StockItem(stock_id, label));
}

void ExampleWindow::register_stock_items()
{
  Glib::RefPtr<Gtk::IconFactory> factory = Gtk::IconFactory::create();
  add_stock_item(factory, "rain.png", "example_stock_rain", "Stay dry");
  factory->add_default(); //Add factory to list of factories.
}
