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

#include "treemodel_dnd.h"
#include <iostream>

TreeModel_Dnd::TreeModel_Dnd()
{
  //We can't just call Gtk::TreeModel(m_Columns) in the initializer list
  //because m_Columns does not exist when the base class constructor runs.
  //And we can't have a static m_Columns instance, because that would be
  //instantiated before the gtkmm type system.
  //So, we use this method, which should only be used just after creation:
  set_column_types(m_Columns);
}

Glib::RefPtr<TreeModel_Dnd> TreeModel_Dnd::create()
{
  return Glib::RefPtr<TreeModel_Dnd>( new TreeModel_Dnd() );
}

bool TreeModel_Dnd::row_draggable_vfunc(const Gtk::TreeModel::Path& path)
{
  //Make the value of the "draggable" column determine whether this row can be dragged:
  
  const_iterator iter = get_iter(path);
  if(iter)
  {
    Row row = *iter;
    bool is_draggable = row[m_Columns.m_col_draggable];
    return is_draggable;
  }

  return Gtk::TreeStore::row_draggable_vfunc(path);
}

bool TreeModel_Dnd::row_drop_possible_vfunc(const Gtk::TreeModel::Path& dest, const Gtk::SelectionData& selection_data)
{
  //Make the value of the "receives drags" column determine whether a row can be dragged into it:

  //dest is the path of the row after which the dragged path would be dropped.
  //But in this case we are more interested in the parent row:
  const_iterator iter = get_iter(dest);
  if(iter)
  {
    const_iterator iter_parent = iter->parent();
    if(iter_parent)
    {
      Row row = *iter_parent;
      bool receives_drags = row[m_Columns.m_col_receivesdrags];
      return receives_drags;
    }
  }

  //You could also examine the row being dragged (via selection_data)
  //if you must look at both rows to see whether a drop should be allowed.
  //TODO: Demonstrate this when the API has been corrected to use Gtk::SelectionData instead of GtkSelectionData,
  //and use Gtk::TreeModel::Path::get_from_selection_data(selection_data, model, path)

  return Gtk::TreeStore::row_drop_possible_vfunc(dest, selection_data);
}
  




