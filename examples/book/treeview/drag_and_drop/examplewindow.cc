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
: m_Button_Quit(Gtk::Stock::QUIT)
{
  set_title("Gtk::TreeView (Drag and Drop) example");
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
  m_Button_Quit.signal_clicked().connect( SigC::slot(*this, &ExampleWindow::on_button_quit) );

  //Create the Tree model:
  //Use our derived model, which overrides some Gtk::TreeDragDest and Gtk::TreeDragSource virtual functions:
  m_refTreeModel = TreeModel_Dnd::create(); //The columns are declared in the overridden TreeModel.
  m_TreeView.set_model(m_refTreeModel);

  //Enable Drag-and-Drop of TreeView rows:
  //See also the derived TreeModel's *_vfunc overrides.
  m_TreeView.enable_model_drag_source();
  m_TreeView.enable_model_drag_dest();

  //Fill the TreeView's model
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_refTreeModel->m_Columns.m_col_id] = 1;
  row[m_refTreeModel->m_Columns.m_col_name] = "Billy Bob";
  row[m_refTreeModel->m_Columns.m_col_draggable] = true;
  row[m_refTreeModel->m_Columns.m_col_receivesdrags] = true;
  

  Gtk::TreeModel::Row childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_refTreeModel->m_Columns.m_col_id] = 11;
  childrow[m_refTreeModel->m_Columns.m_col_name] = "Billy Bob Junior";
  childrow[m_refTreeModel->m_Columns.m_col_draggable] = true;
  childrow[m_refTreeModel->m_Columns.m_col_receivesdrags] = true;

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_refTreeModel->m_Columns.m_col_id] = 12;
  childrow[m_refTreeModel->m_Columns.m_col_name] = "Sue Bob";
  childrow[m_refTreeModel->m_Columns.m_col_draggable] = true;
  childrow[m_refTreeModel->m_Columns.m_col_receivesdrags] = true;

  row = *(m_refTreeModel->append());
  row[m_refTreeModel->m_Columns.m_col_id] = 2;
  row[m_refTreeModel->m_Columns.m_col_name] = "Joey Jojo";
  row[m_refTreeModel->m_Columns.m_col_draggable] = true;
  row[m_refTreeModel->m_Columns.m_col_receivesdrags] = true;

  row = *(m_refTreeModel->append());
  row[m_refTreeModel->m_Columns.m_col_id] = 3;
  row[m_refTreeModel->m_Columns.m_col_name] = "Rob McRoberts";
  row[m_refTreeModel->m_Columns.m_col_draggable] = true;
  row[m_refTreeModel->m_Columns.m_col_receivesdrags] = true;

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_refTreeModel->m_Columns.m_col_id] = 31;
  childrow[m_refTreeModel->m_Columns.m_col_name] = "Xavier McRoberts";
  childrow[m_refTreeModel->m_Columns.m_col_draggable] = true;
  childrow[m_refTreeModel->m_Columns.m_col_receivesdrags] = true;
  
  //Add the TreeView's view columns:
  m_TreeView.append_column("ID", m_refTreeModel->m_Columns.m_col_id);
  m_TreeView.append_column("Name", m_refTreeModel->m_Columns.m_col_name);
  m_TreeView.append_column_editable("Draggable", m_refTreeModel->m_Columns.m_col_draggable);
  m_TreeView.append_column_editable("Receives Drags", m_refTreeModel->m_Columns.m_col_receivesdrags);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  hide();
}



