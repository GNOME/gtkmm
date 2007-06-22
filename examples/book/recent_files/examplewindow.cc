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
: m_refRecentManager(Gtk::RecentManager::get_default())
{
  set_title("recent files example");
  set_default_size(200, 200);

  //We can put a MenuBar at the top of the box and other stuff below it.
  add(m_Box);

  //Create actions for menus and toolbars:
  m_refActionGroup = Gtk::ActionGroup::create();

  //File menu:
  m_refActionGroup->add( Gtk::Action::create("FileMenu", "_File") );
  m_refActionGroup->add( Gtk::Action::create("FileNew", Gtk::Stock::NEW),
          sigc::mem_fun(*this, &ExampleWindow::on_menu_file_new));

  /* A recent-files sub-menu: */
  //TODO: Shouldn't this have a default constructor?: 
  //See bug #450032.
  //m_refActionGroup->add( Gtk::RecentAction::create() );
  m_refActionGroup->add( Gtk::RecentAction::create("FileRecentFiles",
              "_Recent Files"));

  /* A menu item to open the recent-files dialog: */
  m_refActionGroup->add( Gtk::Action::create("FileRecentDialog",
              "Recent Files _Dialog"), sigc::mem_fun(*this,
                  &ExampleWindow::on_menu_file_recent_files_dialog) );

  m_refActionGroup->add( Gtk::Action::create("FileQuit", Gtk::Stock::QUIT),
          sigc::mem_fun(*this, &ExampleWindow::on_menu_file_quit) );


  m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(m_refActionGroup);

  add_accel_group(m_refUIManager->get_accel_group());

  //Layout the actions in a menubar and toolbar:
  Glib::ustring ui_info =
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='FileMenu'>"
        "      <menuitem action='FileNew'/>"
        "      <menuitem action='FileRecentFiles'/>"
        "      <menuitem action='FileRecentDialog'/>"
        "      <separator/>"
        "      <menuitem action='FileQuit'/>"
        "    </menu>"
        "  </menubar>"
        "  <toolbar  name='ToolBar'>"
        "    <toolitem action='FileNew'/>"
        "    <toolitem action='FileQuit'/>"
        "  </toolbar>"
        "</ui>";

  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
    m_refUIManager->add_ui_from_string(ui_info);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "building menus failed: " <<  ex.what();
  }
  #else
  std::auto_ptr<Glib::Error> ex;
  m_refUIManager->add_ui_from_string(ui_info, ex);
  if(ex.get())
     std::cerr << "building menus failed: " <<  ex->what();
  #endif //GLIBMM_EXCEPTIONS_ENABLED

  //Get the menubar and toolbar widgets, and add them to a container widget:
  Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
  if(pMenubar)
    m_Box.pack_start(*pMenubar, Gtk::PACK_SHRINK);

  Gtk::Widget* pToolbar = m_refUIManager->get_widget("/ToolBar") ;
  if(pToolbar)
    m_Box.pack_start(*pToolbar, Gtk::PACK_SHRINK);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_menu_file_new()
{
    std::cout << " New File" << std::endl;
}

void ExampleWindow::on_menu_file_quit()
{
  hide(); //Closes the main window to stop the Gtk::Main::run().
}

void ExampleWindow::on_menu_file_recent_files_dialog()
{
  Gtk::RecentChooserDialog dialog(*this, "Recent Files", m_refRecentManager);
  dialog.add_button("Select File", Gtk::RESPONSE_OK);
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

  const int response = dialog.run();
  dialog.hide();
  if(response == Gtk::RESPONSE_OK)
  {
     std::cout << "URI selected = " << dialog.get_current_uri() << std::endl;
  }
}

