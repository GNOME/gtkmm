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

#include <gtkmm/comboboxentrytext.h>

#include <gtkmm/liststore.h>
#include <gtkmm/cellrenderertext.h>
#include <gtk/gtkcombobox.h>
#include <gtk/gtkcelllayout.h>

namespace Gtk
{

ComboBoxEntryText::ComboBoxEntryText()
{
  set_model( Gtk::ListStore::create(m_text_columns) );
  set_text_column(m_text_columns.m_column);
}

ComboBoxEntryText::ComboBoxEntryText(GtkComboBoxEntry* castitem)
: Gtk::ComboBoxEntry(castitem)
{
  set_model( Gtk::ListStore::create(m_text_columns) );
  set_text_column(m_text_columns.m_column);
}

void ComboBoxEntryText::append_text(const Glib::ustring& text)
{
  gtk_combo_box_append_text(GTK_COMBO_BOX(gobj()), text.c_str());
}

void ComboBoxEntryText::insert_text(int position, const Glib::ustring& text)
{
  gtk_combo_box_insert_text(GTK_COMBO_BOX(gobj()), position, text.c_str());
}

void ComboBoxEntryText::prepend_text(const Glib::ustring& text)
{
  gtk_combo_box_prepend_text(GTK_COMBO_BOX(gobj()), text.c_str());
}

Glib::ustring ComboBoxEntryText::get_active_text() const
{
  Glib::ustring result;

  //Get the active row:
  TreeModel::iterator active_row = get_active();
  if(active_row)
  {
    Gtk::TreeModel::Row row = *active_row;
    result = row[m_text_columns.m_column];
  }

  return result;
}


} // namespace Gtk


