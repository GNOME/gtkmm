/* $Id$ */

/* Copyright(C) 2001-2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or(at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gtkmm/treeview_private.h>
#include <glibmm.h>


namespace Gtk
{

namespace TreeView_Private
{

SignalProxy_CellData::SignalProxy_CellData(const SlotType& slot)
:
  slot_ (slot)
{}

SignalProxy_CellData::~SignalProxy_CellData()
{}

void SignalProxy_CellData::gtk_callback(GtkTreeViewColumn*, GtkCellRenderer* cell,
                                        GtkTreeModel* model, GtkTreeIter* iter, void* data)
{
  SignalProxy_CellData *const self = static_cast<SignalProxy_CellData*>(data);

  try
  {
    // use Slot::operator()
    (self->slot_)(Glib::wrap(cell, false), TreeIter(model, iter));
  }
  catch(...)
  {
    Glib::exception_handlers_invoke();
  }
}

void SignalProxy_CellData::gtk_callback_destroy(void* data)
{
  delete static_cast<SignalProxy_CellData*>(data);
}


} // namespace TreeView_Private

} // namespace Gtk

