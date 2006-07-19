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
: m_Button_Quit("Quit"),
  m_validate_retry(false)
{
  set_title("Gtk::TreeView Editable Cells example");
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

  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_TreeView.set_model(m_refTreeModel);

  //Fill the TreeView's model
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "Billy Bob";
  row[m_Columns.m_col_foo] = true;
  row[m_Columns.m_col_number] = 10;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "Joey Jojo";
  row[m_Columns.m_col_foo] = true;
  row[m_Columns.m_col_number] = 20;

  row = *(m_refTreeModel->append());

  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "Rob McRoberts";
  row[m_Columns.m_col_foo] = false;
  row[m_Columns.m_col_number] = 30;

  //Add the TreeView's view columns:
  //We use the *_editable convenience methods for most of these,
  //because the default functionality is enough:
  m_TreeView.append_column_editable("ID", m_Columns.m_col_id);
  m_TreeView.append_column_editable("Name", m_Columns.m_col_name);
  m_TreeView.append_column_editable("foo", m_Columns.m_col_foo);
  m_TreeView.append_column_numeric_editable("foo", m_Columns.m_col_number, "%010d");


  //For this column, we create the CellRenderer ourselves, and connect our own signal handlers, 
  //so that we can validate the data that the user enters, and control how it is displayed.
  m_treeviewcolumn_validated.set_title("validated (<10)");
  m_treeviewcolumn_validated.pack_start(m_cellrenderer_validated);
  m_TreeView.append_column(m_treeviewcolumn_validated);
  
  //Tell the view column how to render the model values:
  m_treeviewcolumn_validated.set_cell_data_func(m_cellrenderer_validated, 
    sigc::mem_fun(*this, &ExampleWindow::treeviewcolumn_validated_on_cell_data) );

  //Make the CellRenderer editable, and handle its editing signals:
#ifdef GLIBMM_PROPERTIES_ENABLED
  m_cellrenderer_validated.property_editable() = true;
#else
  m_cellrenderer_validated.set_property("editable", true);
#endif

  m_cellrenderer_validated.signal_editing_started().connect(
    sigc::mem_fun(*this, &ExampleWindow::cellrenderer_validated_on_editing_started) );

  m_cellrenderer_validated.signal_edited().connect(
    sigc::mem_fun(*this, &ExampleWindow::cellrenderer_validated_on_edited) );


  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  hide();
}

void ExampleWindow::treeviewcolumn_validated_on_cell_data(Gtk::CellRenderer* /* renderer */, const Gtk::TreeModel::iterator& iter)
{
  //Get the value from the model and show it appropriately in the view:
  if(iter)
  {
    Gtk::TreeModel::Row row = *iter;
    int model_value = row[m_Columns.m_col_number_validated];

    //This is just an example.
    //In this case, it would be easier to use append_column_editable() or append_column_numeric_editable()
    char buffer[32];
    sprintf(buffer, "%d", model_value); 

    Glib::ustring view_text = buffer;
#ifdef GLIBMM_PROPERTIES_ENABLED
    m_cellrenderer_validated.property_text() = view_text;
#else
    m_cellrenderer_validated.set_property("text", view_text);
#endif
  }
}

void ExampleWindow::cellrenderer_validated_on_editing_started(Gtk::CellEditable* cell_editable, const Glib::ustring& /* path */)
{
  //Start editing with previously-entered (but invalid) text, 
  //if we are allowing the user to correct some invalid data. 
  if(m_validate_retry)
  {
    //This is the CellEditable inside the CellRenderer. 
    Gtk::CellEditable* celleditable_validated = cell_editable;

    //It's usually an Entry, at least for a CellRendererText:
    Gtk::Entry* pEntry = dynamic_cast<Gtk::Entry*>(celleditable_validated);
    if(pEntry)
    {
      pEntry->set_text(m_invalid_text_for_retry);
      m_validate_retry = false;
      m_invalid_text_for_retry.clear();
    }
  }

}

void ExampleWindow::cellrenderer_validated_on_edited(const Glib::ustring& path_string, const Glib::ustring& new_text)
{  
  Gtk::TreePath path(path_string);

  //Convert the inputed text to an integer, as needed by our model column:
  char* pchEnd = 0;
  int new_value = strtol(new_text.c_str(), &pchEnd, 10);

  if(new_value > 10)
  {
    //Prevent entry of numbers higher than 10.
  
    //Tell the user:
    Gtk::MessageDialog dialog(*this, "The number must be less than 10. Please try again.", false, Gtk::MESSAGE_ERROR);
    dialog.run();
   
    //Start editing again, with the bad text, so that the user can correct it.
    //A real application should probably allow the user to revert to the previous text.
    
    //Set the text to be used in the start_editing signal handler:
    m_invalid_text_for_retry = new_text;
    m_validate_retry = true;

    //Start editing again:
    m_TreeView.set_cursor(path, m_treeviewcolumn_validated, m_cellrenderer_validated, true /* start_editing */);
  }
  else
  {
    //Get the row from the path:
    Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
    if(iter)
    {
      Gtk::TreeModel::Row row = *iter;

    
      //Put the new value in the model:
      row[m_Columns.m_col_number_validated] = new_value;
    }
  }
}




