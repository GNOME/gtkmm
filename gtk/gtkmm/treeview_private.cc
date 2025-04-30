/* Copyright (C) 2001-2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or(at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <https://www.gnu.org/licenses/>.
 */

#ifndef GTKMM_DISABLE_DEPRECATED // The entire file is deprecated.

#include <glibmm.h>
#include <gtkmm/treeview_private.h>

namespace Gtk
{

namespace TreeView_Private
{
extern "C"
{
// A function with external linkage and C linkage does not get a mangled name.
// Even though gtkmm_SignalProxy_CellData_gtk_callback is declared in a named namespace,
// the linker does not see the namespace name, only 'gtkmm_SignalProxy_CellData_gtk_callback'.
// Therefore the function name shall have a prefix, hopefully unique.
void gtkmm_SignalProxy_CellData_gtk_callback(GtkTreeViewColumn*, GtkCellRenderer* cell,
                                        GtkTreeModel* model, GtkTreeIter* iter, void* data)
{
  if(!model)
    g_warning("gtkmm_SignalProxy_CellData_gtk_callback(): model is NULL, which is unusual.\n");

  TreeViewColumn::SlotTreeCellData* the_slot = static_cast<TreeViewColumn::SlotTreeCellData*>(data);

  try
  {
    // use Slot::operator()
    auto cppiter = Gtk::TreeModel::iterator(model, iter);
    if(!cppiter.get_model_gobject())
    {
      g_warning("gtkmm_SignalProxy_CellData_gtk_callback() The cppiter has no model\n");
      return;
    }

    (*the_slot)(Glib::wrap(cell, false), cppiter);
  }
  catch(...)
  {
    Glib::exception_handlers_invoke();
  }
}

void gtkmm_SignalProxy_CellData_gtk_callback_destroy(void* data)
{
  delete static_cast<TreeViewColumn::SlotTreeCellData*>(data);
}

gboolean gtkmm_SignalProxy_RowSeparator_gtk_callback(GtkTreeModel* model, GtkTreeIter* iter, void* data)
{
  TreeView::SlotRowSeparator* the_slot = static_cast<TreeView::SlotRowSeparator*>(data);

  try
  {
    return (*the_slot)(Glib::wrap(model, true), Gtk::TreeModel::iterator(model, iter));
  }
  catch(...)
  {
    Glib::exception_handlers_invoke();
  }

  return 0; // arbitrary value
}

void gtkmm_SignalProxy_RowSeparator_gtk_callback_destroy(void* data)
{
  delete static_cast<TreeView::SlotRowSeparator*>(data);
}
} // extern "C"

void SignalProxy_CellData_gtk_callback(GtkTreeViewColumn* column, GtkCellRenderer* cell,
                                       GtkTreeModel* model, GtkTreeIter* iter, void* data)
{
  gtkmm_SignalProxy_CellData_gtk_callback(column, cell, model, iter, data);
}

void SignalProxy_CellData_gtk_callback_destroy(void* data)
{
  delete static_cast<TreeViewColumn::SlotTreeCellData*>(data);
}

gboolean SignalProxy_RowSeparator_gtk_callback(GtkTreeModel* model, GtkTreeIter* iter, void* data)
{
  return gtkmm_SignalProxy_RowSeparator_gtk_callback(model, iter, data);
}

void SignalProxy_RowSeparator_gtk_callback_destroy(void* data)
{
  delete static_cast<TreeView::SlotRowSeparator*>(data);
}

} // namespace TreeView_Private

} // namespace Gtk

#endif // GTKMM_DISABLE_DEPRECATED
