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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/table.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/printoperation.h>

//class PreviewWindow;
class PrintFormOperation;

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:

  virtual void build_main_menu();

  virtual void print_or_preview(Gtk::PrintOperationAction print_action);
  //virtual void on_preview_dialog_hide();

  //PrintOperation signal handlers.
  //We handle these so can get necessary information to update the UI or print settings.
  //Our derived PrintOperation class also overrides some default signal handlers.
  virtual void on_printoperation_status_changed(const Glib::RefPtr<PrintFormOperation>& operation);

  virtual void on_printoperation_preview_done(const Glib::RefPtr<Gtk::PrintSettings>& settings);

  virtual void on_printoperation_done(Gtk::PrintOperationResult result, const Glib::RefPtr<PrintFormOperation>& operation);

/*   virtual bool on_printoperation_preview(Gtk::PrintOperationPreview* preview, */
/*                           const Glib::RefPtr<Gtk::PrintContext>& context, */
/*                           Gtk::Window* parent, */
/*                           Glib::RefPtr<PrintFormOperation>& operation); */
  
  //Action signal handlers:
  virtual void on_menu_file_new();
  virtual void on_menu_file_page_setup();
  virtual void on_menu_file_print_preview();
  virtual void on_menu_file_print();
  virtual void on_menu_file_quit();

  //std::auto_ptr<PreviewWindow> m_PreviewDialog;

  //Printing-related objects:
  Glib::RefPtr<Gtk::PageSetup> m_refPageSetup;
  Glib::RefPtr<Gtk::PrintSettings> m_refSettings;


  //Child widgets:
  Gtk::VBox m_VBox;
  Gtk::Table m_Table;

  Gtk::Label m_NameLabel;
  Gtk::Entry m_NameEntry;

  Gtk::Label m_SurnameLabel;
  Gtk::Entry m_SurnameEntry;

  Gtk::Label m_CommentsLabel;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TextView m_TextView;
  
  Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

  unsigned m_ContextId;
  Gtk::Statusbar m_Statusbar;

  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
};

#endif //GTKMM_EXAMPLEWINDOW_H
