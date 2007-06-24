//$Id: deriveddialog.h 691 2004-06-02 13:33:10Z mxpxpod $ -*- c++ -*-

/* libglademm example Copyright (C) 2003 libglademm development team
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

#ifndef GTKMM_EXAMPLE_DERIVED_DIALOG_H
#define GTKMM_EXAMPLE_DERIVED_DIALOG_H

#include <gtkmm.h>


class DerivedDialog : public Gtk::Dialog
{
public:
  DerivedDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
  virtual ~DerivedDialog();

protected:
  //Signal handlers:
  virtual void on_button_quit();

  Glib::RefPtr<Gtk::Builder> m_refGlade;
  Gtk::Button* m_pButton;
};

#endif //GTKMM_EXAMPLE_DERIVED_WINDOW_H
