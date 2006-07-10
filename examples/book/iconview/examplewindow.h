//$Id$ -*- c++ -*-

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

#include <glibmm/ustring.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm/window.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/box.h>
#include <gtkmm/iconview.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/liststore.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/button.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  // Signal handlers:
  //
  virtual void on_button_quit();
  virtual void on_item_activated(const Gtk::TreeModel::Path& path);
  virtual void on_selection_changed();

  void add_entry(const std::string& filename, const Glib::ustring& description);

  // Tree model columns:
  //
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()
    {
      add(m_col_filename);
      add(m_col_description);
      add(m_col_pixbuf);
    }

    Gtk::TreeModelColumn<std::string> m_col_filename;
    Gtk::TreeModelColumn<Glib::ustring>  m_col_description;
    Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > m_col_pixbuf;
  };

  ModelColumns m_Columns;

  // Child widgets:
  Gtk::VBox m_VBox;

  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::IconView m_IconView;
  Glib::RefPtr<Gtk::ListStore> m_refListModel;

  Gtk::HButtonBox m_ButtonBox;
  Gtk::Button m_Button_Quit;

};

#endif //GTKMM_EXAMPLEWINDOW_H

// vim: ts=8 sw=8

