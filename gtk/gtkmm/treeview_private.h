#ifndef _GTKMM_TREEVIEW_PRIVATE_H
#define _GTKMM_TREEVIEW_PRIVATE_H
/* treeview.h
 *
 * Copyright (C) 2001-2002 The gtkmm Development Team
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

#include <gtkmm/treeviewcolumn.h>
#include <gtkmm/treeview.h>

namespace Gtk
{

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace TreeView_Private
{
extern "C"
{
GTKMM_API
void gtkmm_SignalProxy_CellData_gtk_callback(GtkTreeViewColumn*, GtkCellRenderer* cell,
                           GtkTreeModel* model, GtkTreeIter* iter, void* data);
GTKMM_API
void gtkmm_SignalProxy_CellData_gtk_callback_destroy(void* data);

GTKMM_API
gboolean gtkmm_SignalProxy_RowSeparator_gtk_callback(GtkTreeModel* model, GtkTreeIter* iter, void* data);

GTKMM_API
void gtkmm_SignalProxy_RowSeparator_gtk_callback_destroy(void* data);
} // extern "C"

GTKMM_API
void SignalProxy_CellData_gtk_callback(GtkTreeViewColumn* column, GtkCellRenderer* cell,
                           GtkTreeModel* model, GtkTreeIter* iter, void* data);
GTKMM_API
void SignalProxy_CellData_gtk_callback_destroy(void* data);

GTKMM_API
gboolean SignalProxy_RowSeparator_gtk_callback(GtkTreeModel* model, GtkTreeIter* iter, void* data);

GTKMM_API
void SignalProxy_RowSeparator_gtk_callback_destroy(void* data);

} /* namespace TreeView_Private */
#endif //DOXYGEN_SHOULD_SKIP_THIS

} /* namespace Gtk */

#endif // GTKMM_DISABLE_DEPRECATED

#endif /* _GTKMM_TREEVIEW_PRIVATE_H */
