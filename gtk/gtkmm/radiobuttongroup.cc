/* Copyright (C) 2003 The gtkmm Development Team
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

#undef GTK_DISABLE_DEPRECATED
#define GDK_DISABLE_DEPRECATION_WARNINGS 1

#include <gtkmm/radiobuttongroup.h>

#include <gtkmm/radiobutton.h>
#include <gtkmm/radiomenuitem.h>
#include <gtkmm/radioaction.h>
#include <gtkmm/radiotoolbutton.h>
#include <gtk/gtk.h>

namespace Gtk
{

RadioButtonGroup::RadioButtonGroup()
: group_(nullptr)
{}

RadioButtonGroup::RadioButtonGroup(GSList* group)
 : group_(group)
{
}

RadioButtonGroup::RadioButtonGroup(const RadioButtonGroup& src)
 : group_(src.group_)
{
}

RadioButtonGroup& RadioButtonGroup::operator=(const RadioButtonGroup& src)
{
  group_ = src.group_;
  return *this;
}

void RadioButtonGroup::add(RadioButton& item)
{
  item.set_group(*this);

  //probably not necessary:
  group_ = gtk_radio_button_get_group(item.gobj());
}

void RadioButtonGroup::add(RadioMenuItem& item)
{
  item.set_group(*this);

  //probably not necessary:
  group_ = gtk_radio_menu_item_get_group(item.gobj());
}

#ifndef GTKMM_DISABLE_DEPRECATED
void RadioButtonGroup::add(const Glib::RefPtr<RadioAction>& item)
{
  item->set_group(*this);

  //probably not necessary:
  group_ = gtk_radio_action_get_group(item->gobj());
}
#endif // GTKMM_DISABLE_DEPRECATED

void RadioButtonGroup::add(RadioToolButton& item)
{
  item.set_group(*this);

  //probably not necessary:
  group_ = gtk_radio_tool_button_get_group(item.gobj());
}

} //namespace Gtk
