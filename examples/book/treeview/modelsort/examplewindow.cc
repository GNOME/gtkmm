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
  set_title("Gtk::TreeView (TreeModelSort) example");
  set_border_width(6);
  set_default_size(400, 400);

  m_VBox.set_spacing(6);
  add(m_VBox);

  //Add the TreeViews, inside ScrolledWindows, with the button underneath:
  m_ScrolledWindow1.add(m_TreeView1);
  m_ScrolledWindow2.add(m_TreeView2);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow1.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  m_ScrolledWindow2.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_VBox.pack_start(m_ScrolledWindow1);
  m_VBox.pack_start(m_ScrolledWindow2);
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );

  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);

  //Put the TreeModel inside sort models:
  //Note that you can just call set_sort_column() on the normal model if you
  //only want to display one sorted view.
  //This example shows how to use SortModel to show two views of the same model,
  //with different sort columns.
  m_refTreeModelSort1 = Gtk::TreeModelSort::create(m_refTreeModel);
  m_refTreeModelSort1->set_sort_column(m_Columns.m_col_id, Gtk::SORT_ASCENDING);
  m_TreeView1.set_model(m_refTreeModelSort1);

  m_refTreeModelSort2 = Gtk::TreeModelSort::create(m_refTreeModel);
  m_refTreeModelSort2->set_sort_column(m_Columns.m_col_name,
          Gtk::SORT_ASCENDING);
  m_TreeView2.set_model(m_refTreeModelSort2);


  //Fill the tree model
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "Zebede Aardvark";
  row[m_Columns.m_col_something] = true;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "Rob McRoberts";
  row[m_Columns.m_col_something] = true;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "Joey Jojo";
  //This should cause this row to be filtered out (now shown).
  row[m_Columns.m_col_something] = false;

  //Add the TreeViews' view columns:
  m_TreeView1.append_column("ID", m_Columns.m_col_id);
  m_TreeView1.append_column("Name", m_Columns.m_col_name);
  m_TreeView1.append_column_editable("Something", m_Columns.m_col_something);

  m_TreeView2.append_column("ID", m_Columns.m_col_id);
  m_TreeView2.append_column("Name", m_Columns.m_col_name);
  m_TreeView2.append_column_editable("Something", m_Columns.m_col_something);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  hide();
}

