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

#ifndef GTKMM_EXAMPLE_RANGEWIDGETS_LABELEDOPTIONMENU_H
#define GTKMM_EXAMPLE_RANGEWIDGETS_LABELEDOPTIONMENU_H

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/menu.h>

class LabeledOptionMenu : public Gtk::HBox
{
public:
  LabeledOptionMenu(const Glib::ustring& menu_title, Gtk::Menu& menu,
    bool homogeneous = false, int spacing = 10);

protected:
    Gtk::Label m_label;

    #ifndef GTKMM_DISABLE_DEPRECATED
    Gtk::OptionMenu m_OptionMenu;
    #endif //GTKMM_DISABLE_DEPRECATED

    Gtk::Menu* m_pMenu;
};
#endif //GTKMM_EXAMPLE_RANGEWIDGETS_LABELEDOPTIONMENU_H
