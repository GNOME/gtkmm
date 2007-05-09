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

#include <iostream>
#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_Button_Quit("Quit")
{
  set_title("Gtk::TreeView (TreeModelFilter) example");
  set_border_width(5);
  set_default_size(400, 200);

  add(m_VBox);

  //Add the TreeView, inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.add(m_TreeView);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_VBox.pack_start(m_ScrolledWindow);
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );

  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);

  m_refTreeModelFilter = Gtk::TreeModelFilter::create( m_refTreeModel,
          Gtk::TreeModel::Path() );
  //TODO: Do not specify the empty Path, when we have added a suitable
  //constructor to gtkmm.
  m_refTreeModelFilter->set_modify_func( m_ColumnsDisplay, sigc::mem_fun(*this,
              &ExampleWindow::on_filter_modify) );

  m_TreeView.set_model(m_refTreeModelFilter);

  //Fill the TreeView's model
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "Billy Bob";
  row[m_Columns.m_col_something] = true;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "Joey Jojo";
  row[m_Columns.m_col_something] = true;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "Rob McRoberts";
  //This should cause this row to be filtered out (now shown).
  row[m_Columns.m_col_something] = false;

  //Add the TreeView's view columns:
  m_TreeView.append_column("Name", m_ColumnsDisplay.m_col_name_uppercase);
  m_TreeView.append_column_editable("Something",
          m_ColumnsDisplay.m_col_something_text);

  //Make all the columns reorderable:
  //This is not necessary, but it's nice to show the feature.
  //You can use TreeView::set_column_drag_function() to more
  //finely control column drag and drop.
  for(guint i = 0; i < 2; i++)
  {
    Gtk::TreeView::Column* pColumn = m_TreeView.get_column(i);
    pColumn->set_reorderable();
  }

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_filter_modify(const Gtk::TreeModel::iterator& iter,
        Glib::ValueBase& value, int column)
{
  //iter is an iterator to the row in the filter model.
  //column is the column number in the filter model.
  //value should be set to the value of that column in this row, to be
  //displayed.

  //Look in the child model, to calculate the model to show in the filter model:
  Gtk::TreeModel::iterator iter_child =
      m_refTreeModelFilter->convert_iter_to_child_iter(iter);
  Gtk::TreeModel::Row row_child = *iter_child;

  switch(column)
  {
    case(0): //name_uppercase
    {
      Glib::ustring name = row_child[m_Columns.m_col_name];

      Glib::Value<Glib::ustring> valString;
      //TODO: Is there any way to avoid this step? Can't it copy the type as
      //well as the value?
      valString.init( Glib::Value< Glib::ustring >::value_type() );

      valString.set(name);
      value = valString; 
      break;
    }
    case(1):
    {
      bool something = row_child[m_Columns.m_col_something];

      Glib::Value<Glib::ustring> valString;
      //TODO: Is there any way to avoid this step? Can't it copy the type as
      //well as the value?
      valString.init( Glib::Value< Glib::ustring >::value_type());

      valString.set( (something ? "something" : "notsomething"));
      value = valString;
      break;
    }
    default:
    {
      break;
    }
  }
}

void ExampleWindow::on_button_quit()
{
  hide();
}

