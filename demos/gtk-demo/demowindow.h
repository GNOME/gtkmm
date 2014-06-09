/* $Id$ */

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
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _DEMOWINDOW_H
#define _DEMOWINDOW_H

#include "gtkmm/window.h"
#include "gtkmm/headerbar.h"
#include "gtkmm/button.h"
#include "gtkmm/notebook.h"
#include "gtkmm/scrolledwindow.h"
#include "gtkmm/box.h"

#include "gtkmm/treestore.h"
#include "gtkmm/treeview.h"
#include "textwidget.h"
#include <stdio.h>

class DemoWindow : public Gtk::Window
{
public:
  DemoWindow();
  virtual ~DemoWindow();

protected:
  void run_example(const Gtk::TreeModel::Row& row);
  void configure_header_bar();

  void fill_tree();

  void load_file(const std::string& filename);
  bool read_line (FILE *stream, GString *str);

  //Signal handlers:
  static bool select_function(const Glib::RefPtr<Gtk::TreeModel>& model, const Gtk::TreeModel::Path& path, bool currently_selected);
  virtual void on_treeselection_changed();
  virtual void on_treeview_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
  virtual void on_example_window_hide();
  virtual void on_run_button_clicked();

  //Member widgets:
  Gtk::HeaderBar m_HeaderBar;
  Gtk::Button m_RunButton;
  Gtk::Notebook m_Notebook;
  Gtk::ScrolledWindow m_SideBar;
  Gtk::Box m_HBox;

  Glib::RefPtr<Gtk::TreeStore> m_refTreeStore;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::TreeSelection> m_refTreeSelection;
  Gtk::TreeModel::Path m_TreePath;

  TextWidget m_TextWidget_Info, m_TextWidget_Source;

  Gtk::Window* m_pWindow_Example;

  std::string m_current_filename;
};

#endif //_DEMOWINDOW_H

