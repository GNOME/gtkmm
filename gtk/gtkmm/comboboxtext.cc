// -*- c++ -*-
/* $Id$ */

/* 
 *
 * Copyright 2003 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
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

#include <gtkmm/comboboxtext.h>

#include <gtkmm/liststore.h>
#include <gtkmm/cellrenderertext.h>
#include <gtk/gtkcombobox.h>
#include <gtk/gtkcelllayout.h>

namespace Gtk
{
 
ComboBoxText::ComboBoxText()
: Gtk::ComboBox(Gtk::ListStore::create(m_text_columns)) //Create a default treemodel. We must create it in the initializer list, because it is a construct-only property.
{
  Glib::RefPtr<TreeModel> model = get_model(); //Get the model that we just created in the initializer list.

  //TODO: Do some template magic to auto-select and connect the cellrenderer.
  //Maybe generalise the TreeView template stuff.
  
  Gtk::CellRenderer* renderer = Gtk::manage( new Gtk::CellRendererText() );
  pack_start(*renderer);

 //TODO:
  gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT(gobj()), renderer->gobj(), "text", 0, 0);
}

void ComboBoxText::append_text(const Glib::ustring& text)
{
  gtk_combo_box_append_text(gobj(), text.c_str());
}

void ComboBoxText::insert_text(int position, const Glib::ustring& text)
{
  gtk_combo_box_insert_text(gobj(), position, text.c_str());
}

void ComboBoxText::prepend_text(const Glib::ustring& text)
{
  gtk_combo_box_prepend_text(gobj(), text.c_str());
}

Glib::ustring ComboBoxText::get_active_text() const
{
  Glib::ustring result;

  //Get the active row:
  unsigned int active_row = get_active();
  Glib::RefPtr<const Gtk::TreeModel> model = get_model();
  const Gtk::TreeModel::Children& children = model->children();
  if(active_row < children.size())
  {
    Gtk::TreeModel::Row row = children[active_row];
    result = row[m_text_columns.m_column];
  }

  return result;
}


} // namespace Gtk


