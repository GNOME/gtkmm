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

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_AspectFrame("2x1", /* label */
    Gtk::ALIGN_CENTER, /* center x */
    Gtk::ALIGN_CENTER, /* center y */
    2.0, /* xsize/ysize = 2 */
    false /* ignore child's aspect */)
{
  set_title("Aspect Frame");
  set_border_width(10);

  // Add a child widget to the aspect frame */
  // Ask for a 200x200 window, but the AspectFrame will give us a 200x100
  // window since we are forcing a 2x1 aspect ratio */
  m_DrawingArea.set_size_request(200, 200);
  m_AspectFrame.add(m_DrawingArea);

  // Add the aspect frame to our toplevel window:
  add(m_AspectFrame);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

