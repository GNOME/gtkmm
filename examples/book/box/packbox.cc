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

#include "packbox.h"
#include <cstdio> //For sprintf().

PackBox::PackBox(bool homogeneous, int spacing, Gtk::PackOptions options, int padding) :
  Gtk::HBox(homogeneous, spacing),
  m_button1("box.pack_start("),
  m_button2("button,"),
  m_button3((options == Gtk::PACK_SHRINK) ? "Gtk::PACK_SHRINK" :
            ((options == Gtk::PACK_EXPAND_PADDING) ? "Gtk::PACK_EXPAND_PADDING" : "Gtk::PACK_EXPAND_WIDGET"))
{
  pack_start(m_button1, options, padding);
  pack_start(m_button2, options, padding);
  pack_start(m_button3, options, padding);

  sprintf(padstr, "%d);", padding);

  m_pbutton4 = new Gtk::Button(padstr);
  pack_start(*m_pbutton4, options, padding);
}

PackBox::~PackBox()
{
  delete m_pbutton4;
}


