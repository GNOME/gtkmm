/* $Id$ */

/* Copyright (C) 2001 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _DEMOWINDOW_H
#define _DEMOWINDOW_H

#include "gtkmm/window.h"
#include "gtkmm/notebook.h"
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
  void fill_tree();

  void load_file(const std::string& filename);
  bool read_line (FILE *stream, GString *str);

  //Signal handlers:
  static bool select_function(const Glib::RefPtr<Gtk::TreeModel>& model, const Gtk::TreeModel::Path& path, bool currently_selected);
  virtual void on_treeselection_changed();
  virtual void on_treeview_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
  virtual void on_example_window_hide();

  //Member widgets:
  Gtk::Notebook m_Notebook;
  Gtk::HBox m_HBox;

  Glib::RefPtr<Gtk::TreeStore> m_refTreeStore;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::TreeSelection> m_refTreeSelection;
  Gtk::TreeModel::Path m_TreePath;

  TextWidget m_TextWidget_Info, m_TextWidget_Source;

  Gtk::Window* m_pWindow_Example;

  std::string m_current_filename;
};

#endif //_DEMOWINDOW_H

