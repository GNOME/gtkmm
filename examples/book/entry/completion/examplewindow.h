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
  virtual void on_button_close();

  virtual void on_completion_action_activated(int index);

  //See the comment in the implementation:
  //virtual bool on_completion_match(const Glib::ustring& key, const Gtk::TreeModel::const_iterator& iter);


  //Tree model columns, for the EntryCompletion's filter model:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()
    { add(m_col_id); add(m_col_name); }

    Gtk::TreeModelColumn<unsigned int> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
  };

  ModelColumns m_Columns;

  typedef std::map<int, Glib::ustring> type_actions_map;
  type_actions_map m_CompletionActions;
  
  //Child widgets:
  Gtk::HBox m_HBox;
  Gtk::VBox m_VBox;
  Gtk::Entry m_Entry;
  Gtk::Label m_Label;
  Gtk::Button m_Button_Close;
};

#endif //GTKMM_EXAMPLEWINDOW_H
