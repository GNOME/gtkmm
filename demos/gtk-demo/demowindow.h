/* Copyright (C) 2001 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _DEMOWINDOW_H
#define _DEMOWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/headerbar.h>
#include <gtkmm/button.h>
#include <gtkmm/notebook.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/listview.h>
#include <gtkmm/singleselection.h>
#include <gtkmm/listitem.h>
#include "textwidget.h"

class DemoWindow : public Gtk::Window
{
public:
  DemoWindow();
  ~DemoWindow() override;

  // The Images demo can show a DemoWindow.
  static DemoWindow* get_demo_window();

protected:
  void configure_header_bar();
  Glib::RefPtr<Gio::ListModel> create_demo_model(
    const Glib::RefPtr<Glib::ObjectBase>& item = {});
  void run_example(const Glib::RefPtr<Glib::ObjectBase>& item);

  void load_file(const std::string& filename);
  void add_data_tabs(const std::string& filename);
  void remove_data_tabs();

  //Signal handlers:
  void on_setup_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_selection_changed(unsigned int position, unsigned int n_items);
  void on_listview_row_activated(unsigned int position);
  void on_run_button_clicked();
  void on_example_window_hide();

  //Member widgets:
  Gtk::HeaderBar m_HeaderBar;
  Gtk::Button m_RunButton;
  Gtk::Notebook m_Notebook;
  Gtk::ScrolledWindow m_SideBar;
  Gtk::Box m_HBox;

  Gtk::ListView m_ListView;
  Glib::RefPtr<Gtk::SingleSelection> m_refSingleSelection;

  TextWidget m_TextWidget_Info;
  TextWidget m_TextWidget_Source;

  Gtk::Window* m_pWindow_Example{nullptr};

  std::string m_current_filename;

  static DemoWindow* m_pDemoWindow;
};

#endif //_DEMOWINDOW_H
