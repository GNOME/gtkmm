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
  set_title("Gtk::TreeView (ListStore) example");
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
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this, &ExampleWindow::on_button_quit) );

  //Create and fill the combo models
  //You could also use set_cell_data_func() to choose or fill these later.
  m_refTreeModelCombo1 = Gtk::ListStore::create(m_ColumnsCombo);
  
  Gtk::TreeModel::Row row = *(m_refTreeModelCombo1->append());
  row[m_ColumnsCombo.m_col_choice] = "abc";
  row = *(m_refTreeModelCombo1->append());
  row[m_ColumnsCombo.m_col_choice] = "def";
  
  m_refTreeModelCombo2 = Gtk::ListStore::create(m_ColumnsCombo);
  
  row = *(m_refTreeModelCombo2->append());
  row[m_ColumnsCombo.m_col_choice] = "foo"; //The value that can be chosen from the combo, to use in the model.
  row[m_ColumnsCombo.m_col_description] = "The Foo item"; //A description, to help the user to choose the value from the combo.
  row = *(m_refTreeModelCombo2->append());
  row[m_ColumnsCombo.m_col_choice] = "bar";
  row[m_ColumnsCombo.m_col_description] = "The item known as bar";
  row = *(m_refTreeModelCombo2->append());
  row[m_ColumnsCombo.m_col_choice] = "goo";
  row[m_ColumnsCombo.m_col_description] = "goo, goo, goo, goo";
  
  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_TreeView.set_model(m_refTreeModel);

  //Fill the TreeView's model
  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "Billy Bob";
  row[m_Columns.m_col_itemchosen] = "click to choose";
  row[m_Columns.m_col_choices] = m_refTreeModelCombo1; //Choose from this list to set the value in m_col_itemchosen.
  
  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "Joey Jojo";
  row[m_Columns.m_col_choices] = m_refTreeModelCombo2;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "Rob McRoberts";
  row[m_Columns.m_col_choices] = m_refTreeModelCombo1;

  //Add the TreeView's view columns:
  m_TreeView.append_column("ID", m_Columns.m_col_id);
  m_TreeView.append_column("Name", m_Columns.m_col_name);
  
  //Create a Combo CellRenderer, instead of the default Text CellRenderer:
  Gtk::TreeView::Column* pColumn = Gtk::manage( new Gtk::TreeView::Column("Item Chosen") ); 
  Gtk::CellRendererCombo* pRenderer = Gtk::manage(new Gtk::CellRendererCombo);
  pColumn->pack_start(*pRenderer);
  m_TreeView.append_column(*pColumn);
  
  //Make this View column represent the m_col_itemchosen model column:
  pColumn->add_attribute(pRenderer->property_text(), m_Columns.m_col_itemchosen);
  
  //Allow the user to choose from this list to set the value in m_col_itemchosen:
  pColumn->add_attribute(pRenderer->property_model(), m_Columns.m_col_choices);
  
  //Alternatively, you could use just one combo model, in all rows, instead of mapping it to a model column:
  //pRenderer->property_model() = m_refTreeModelCombo1;

  pRenderer->property_text_column() = 0; //This must be a text column, in m_refTreeModelCombo1, or m_refTreeModelCombo;
  
  //Allow the user to edit the column:
  //This is done automatically when we use View::append_column(model_column),
  //but that uses a simple Text CellRenderer.
  pRenderer->property_editable() = true;

  pRenderer->signal_edited().connect( sigc::mem_fun(*this, &ExampleWindow::on_cellrenderer_choice_edited) );
      
  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  hide();
}

void ExampleWindow::on_cellrenderer_choice_edited(const Glib::ustring& path_string, const Glib::ustring& new_text)
{
  Gtk::TreePath path(path_string);

  //Get the row from the path:
  Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
  if(iter)
  {
      //Store the user's new text in the model:
      Gtk::TreeRow row = *iter;
      row[m_Columns.m_col_itemchosen] = new_text;
  }
}


