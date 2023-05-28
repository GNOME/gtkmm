#ifndef _GTKMM_SELECTIONLISTMODELIMPL_H
#define _GTKMM_SELECTIONLISTMODELIMPL_H

/* Copyright (C) 2021 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmmconfig.h>
#include <glibmm/object.h>
#include <giomm/listmodel.h>
#include <gtkmm/selectionmodel.h>

namespace Gtk
{
/** %Gtk::SelectionListModelImpl is an object that implements the Gio::ListModel
 * and Gtk::SelectionModel interfaces.
 *
 * gtk_notebook_get_pages() and gtk_stack_get_pages() return an object of a class
 * that implements both GListModel and GtkSelectionModel. Since that C class is not
 * public, it's not wrapped in a C++ class. A C object of such a class can be wrapped
 * in a %Gtk::SelectionListModelImpl object. %Gtk::SelectionListModelImpl does not
 * directly correspond to any GTK class.
 *
 * This class is intended only for wrapping C objects returned from GTK functions.
 *
 * @see Gtk::Notebook::get_pages(), Gtk::Stack::get_pages()
 * @newin{4,2}
 */

class GTKMM_API SelectionListModelImpl : public Gio::ListModel, public SelectionModel, public Glib::Object
{
#ifndef DOXYGEN_SHOULD_SKIP_THIS
public:
  // noncopyable
  SelectionListModelImpl(const SelectionListModelImpl&) = delete;
  SelectionListModelImpl& operator=(const SelectionListModelImpl&) = delete;

protected:
  explicit SelectionListModelImpl(GObject* castitem);
  friend class Notebook;
  friend class Stack;

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
  SelectionListModelImpl(SelectionListModelImpl&& src) noexcept;
  SelectionListModelImpl& operator=(SelectionListModelImpl&& src) noexcept;

  ~SelectionListModelImpl() noexcept override;
};

} // namespace Gtk

#endif /* _GTKMM_SELECTIONLISTMODELIMPL_H */
