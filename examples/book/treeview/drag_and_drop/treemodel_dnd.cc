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

bool
TreeModel_Dnd::row_draggable_vfunc(const Gtk::TreeModel::Path& path) const
{
  // Make the value of the "draggable" column determine whether this row can
  // be dragged:

  //TODO: Add a const version of get_iter to TreeModel:
  TreeModel_Dnd* unconstThis = const_cast<TreeModel_Dnd*>(this);
  const_iterator iter = unconstThis->get_iter(path);
  //const_iterator iter = get_iter(path);
  if(iter)
  {
    Row row = *iter;
    bool is_draggable = row[m_Columns.m_col_draggable];
    return is_draggable;
  }

#ifdef GLIBMM_VFUNCS_ENABLED
  return Gtk::TreeStore::row_draggable_vfunc(path);
#else
  return false;
#endif
}

bool
TreeModel_Dnd::row_drop_possible_vfunc(const Gtk::TreeModel::Path& dest,
        const Gtk::SelectionData& selection_data) const
{
  //Make the value of the "receives drags" column determine whether a row can be
  //dragged into it:

  //dest is the path that the row would have after it has been dropped:
  //But in this case we are more interested in the parent row:
  Gtk::TreeModel::Path dest_parent = dest;
  bool dest_is_not_top_level = dest_parent.up();
  if(!dest_is_not_top_level || dest_parent.empty())
  {
    //The user wants to move something to the top-level.
    //Let's always allow that.
  }
  else
  {
    //Get an iterator for the row at this path:
    //We must unconst this. This should not be necessary with a future version
    //of gtkmm.
    //TODO: Add a const version of get_iter to TreeModel:
    TreeModel_Dnd* unconstThis = const_cast<TreeModel_Dnd*>(this);
    const_iterator iter_dest_parent = unconstThis->get_iter(dest_parent);
    //const_iterator iter_dest_parent = get_iter(dest);
    if(iter_dest_parent)
    {
      Row row = *iter_dest_parent;
      bool receives_drags = row[m_Columns.m_col_receivesdrags];
      return receives_drags;
    }
  }

  //You could also examine the row being dragged (via selection_data)
  //if you must look at both rows to see whether a drop should be allowed.
  //You could use
  //TODO: Add const version of get_from_selection_data(): Glib::RefPtr<const
  //Gtk::TreeModel> refThis = Glib::RefPtr<const Gtk::TreeModel>(this);
  //
  //Glib::RefPtr<Gtk::TreeModel> refThis =
  //Glib::RefPtr<Gtk::TreeModel>(const_cast<TreeModel_Dnd*>(this));
  //refThis->reference(); //, true /* take_copy */)
  //Gtk::TreeModel::Path path_dragged_row;
  //Gtk::TreeModel::Path::get_from_selection_data(selection_data, refThis,
  //path_dragged_row);

#ifdef GLIBMM_VFUNCS_ENABLED
  return Gtk::TreeStore::row_drop_possible_vfunc(dest, selection_data);
#else
  return false;
#endif
}

