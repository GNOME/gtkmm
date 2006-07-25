/* gtkmm example Copyright (C) 2006 gtkmm development team
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
#include "previewdialog.h"
#include "printformoperation.h"


#include <iostream>

#include <pangomm.h>

const Glib::ustring app_title = "gtkmm Printing Example";

ExampleWindow::ExampleWindow()
  :
  m_Table(3, 2),
  m_NameLabel("Name"),
  m_SurnameLabel("Surname"),
  m_CommentsLabel("Comments")
{
  m_refPageSetup = Gtk::PageSetup::create();
  m_refSettings = Gtk::PrintSettings::create();

  m_ContextId = m_Statusbar.get_context_id(app_title);

  set_title(app_title);
  set_default_size(400, 300);

  add(m_VBox);

  build_main_menu();

  m_VBox.pack_start(m_Table);

  //Arrange the widgets inside the table:
  m_Table.attach(m_NameLabel, 0, 1, 0, 1);
  m_Table.attach(m_NameEntry, 1, 2, 0, 1);

  m_Table.attach(m_SurnameLabel, 0, 1, 1, 2, Gtk::SHRINK);
  m_Table.attach(m_SurnameEntry, 1, 2, 1, 2);

  //Add the TreeView, inside a ScrolledWindow:
  m_ScrolledWindow.add(m_TextView);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_Table.attach(m_CommentsLabel, 0, 1, 2, 3, Gtk::SHRINK);
  m_Table.attach(m_ScrolledWindow, 1, 2, 2, 3);

  m_refTextBuffer = Gtk::TextBuffer::create();
  m_TextView.set_buffer(m_refTextBuffer);

  m_VBox.pack_start(m_Statusbar);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::build_main_menu()
{
  //Create actions for menus and toolbars:
  m_refActionGroup = Gtk::ActionGroup::create();

  //File menu:
  m_refActionGroup->add(
    Gtk::Action::create("FileMenu", "_File"));

  m_refActionGroup->add(
    Gtk::Action::create("New", Gtk::Stock::NEW),
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_new));

  m_refActionGroup->add(
    Gtk::Action::create("PageSetup", "Page _Setup"),
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_page_setup));

  m_refActionGroup->add(
    Gtk::Action::create("PrintPreview", "Print Preview"),
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_print_preview));

  m_refActionGroup->add(
    Gtk::Action::create("Print", Gtk::Stock::PRINT),
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_print));

  m_refActionGroup->add(
    Gtk::Action::create("Quit", Gtk::Stock::QUIT),
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_quit));

  m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(m_refActionGroup);
 
  add_accel_group(m_refUIManager->get_accel_group());

  //Layout the actions in a menubar and toolbar:
  
  Glib::ustring ui_info = 
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='FileMenu'>"
        "      <menuitem action='New'/>"
        "      <menuitem action='PageSetup'/>"
        "      <menuitem action='PrintPreview'/>"
        "      <menuitem action='Print'/>"
        "      <separator/>"
        "      <menuitem action='Quit'/>"
        "    </menu>"
        "  </menubar>"
        "  <toolbar  name='ToolBar'>"
        "    <toolitem action='New'/>"
        "    <toolitem action='Print'/>"
        "      <separator/>"
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
    std::cerr << "building menus failed: " << ex.what();
  }
  #else
  std::auto_ptr<Glib::Error> ex;
  m_refUIManager->add_ui_from_string(ui_info, ex);
  if(ex.get())
  { 
    std::cerr << "building menus failed: " << ex->what();
  }
  #endif //GLIBMM_EXCEPTIONS_ENABLED

 
  //Get the menubar and toolbar widgets, and add them to a container widget:
  Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
  if(pMenubar)
    m_VBox.pack_start(*pMenubar, Gtk::PACK_SHRINK);

  Gtk::Widget* pToolbar = m_refUIManager->get_widget("/ToolBar") ;
  if(pToolbar)
    m_VBox.pack_start(*pToolbar, Gtk::PACK_SHRINK);
}

void ExampleWindow::on_printoperation_status_changed(const Glib::RefPtr<PrintFormOperation>& operation)
{
  Glib::ustring status_msg;

  if (operation->is_finished())
  {
    status_msg = "Print job completed.";
  }
  else
  {
    //You could also use get_status().
    status_msg = operation->get_status_string();
  }

  m_Statusbar.push(status_msg, m_ContextId);
}

void ExampleWindow::on_printoperation_preview_done(const Glib::RefPtr<Gtk::PrintSettings>& settings)
{
  g_debug("ew::on_printoperation_preview_done");

  //Store the print settings that the user chose while using the print preview dialog:
  m_refSettings = settings;
}

void ExampleWindow::on_printoperation_done(Gtk::PrintOperationResult result, const Glib::RefPtr<PrintFormOperation>& operation)
{
  g_debug("ew::on_printoperation_done");

  //Printing is "done" when the print data is spooled.

  if (result == Gtk::PRINT_OPERATION_RESULT_ERROR)
  {
    Gtk::MessageDialog err_dialog(*this, "Error printing form", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
    err_dialog.run();
  }
  else if (result == Gtk::PRINT_OPERATION_RESULT_APPLY)
  {
    //Update PrintSettings with the ones used in this PrintOperation:
    m_refSettings = operation->get_print_settings();
  }

  if (! operation->is_finished())
  {
    //We will connect to the status-changed signal to track status
    //and update a status bar. In addition, you can, for example,
    //keep a list of active print operations, or provide a progress dialog.
    operation->signal_status_changed().connect(sigc::bind(sigc::mem_fun(*this, &ExampleWindow::on_printoperation_status_changed), operation));
  }
}

void ExampleWindow::print_or_preview(Gtk::PrintOperationAction print_action)
{
  //Create a new PrintOperation with our PageSetup and PrintSettings:
  //(We use our derived PrintOperation class)
  Glib::RefPtr<PrintFormOperation> print = PrintFormOperation::create();

  print->set_name(m_NameEntry.get_text() + " " + m_SurnameEntry.get_text());
  print->set_comments(m_refTextBuffer->get_text(false /* Don't include hidden. */));
  //print->set_font("Sans 12");

  print->set_track_print_status();
  print->set_default_page_setup(m_refPageSetup);
  print->set_print_settings(m_refSettings);

  //print->signal_preview_done.connect( sigc::mem_fun(*this, &ExampleWindow::on_printoperation_preview_done) );

  print->signal_done().connect(sigc::bind(sigc::mem_fun(*this, &ExampleWindow::on_printoperation_done), print));


  try
  {
    print->run(print_action /* print or preview */, *this);
  }
  catch (const Gtk::PrintError& ex)
  {
    //See documentation for exact Gtk::PrintError error codes.
    std::cerr << "An error occurred while trying to run a print operation:" << ex.what() << std::endl;
  }

  g_debug("print status: %s", print->get_status_string().c_str());
}

void ExampleWindow::on_menu_file_new()
{
  //Clear entries and textview:
  m_NameEntry.set_text("");
  m_SurnameEntry.set_text("");
  m_refTextBuffer->set_text("");
  m_TextView.set_buffer(m_refTextBuffer);
}

void ExampleWindow::on_menu_file_page_setup()
{
  //Show the page setup dialog, asking it to start with the existing settings:
  Glib::RefPtr<Gtk::PageSetup> new_page_setup = Gtk::run_page_setup_dialog(*this, m_refPageSetup, m_refSettings);

  //Save the chosen page setup dialog for use when printing, previewing, or showing the page setup dialog again:
  m_refPageSetup = new_page_setup;
}

void ExampleWindow::on_menu_file_print_preview()
{
  g_debug("starting with PREVIEW");
  print_or_preview(Gtk::PRINT_OPERATION_ACTION_PREVIEW);
}

void ExampleWindow::on_menu_file_print()
{
  g_debug("starting with PRINT_DIALOG");
  print_or_preview(Gtk::PRINT_OPERATION_ACTION_PRINT_DIALOG);
}

void ExampleWindow::on_menu_file_quit()
{
  hide();
}
