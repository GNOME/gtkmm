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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  //Signal handlers:
  virtual void on_button_quit();

  //Tree model columns for the TreeView:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()
    { add(m_col_id); add(m_col_name); add(m_col_choices); }

    Gtk::TreeModelColumn<unsigned int> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    Gtk::TreeModelColumn< Glib::RefPtr<Gtk::TreeModel> > m_col_choices;
  };

  ModelColumns m_Columns;
  
  //Tree model columns for the Combo CellRenderer in the TreeView column:
  class ModelColumnsCombo : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumnsCombo()
    { add(m_col_choice); }

    Gtk::TreeModelColumn<Glib::ustring> m_col_choice;
  };
  
  ModelColumnsCombo m_ColumnsCombo;

  //Child widgets:
  Gtk::VBox m_VBox;

  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

  Glib::RefPtr<Gtk::ListStore> m_refTreeModelCombo1, m_refTreeModelCombo2;
    
  Gtk::HButtonBox m_ButtonBox;
  Gtk::Button m_Button_Quit;
};

#endif //GTKMM_EXAMPLEWINDOW_H
