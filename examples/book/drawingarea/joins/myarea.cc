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

#include "myarea.h"
#include <cairomm/context.h>

MyArea::MyArea()
{
}


MyArea::~MyArea()
{
}


bool MyArea::on_expose_event(GdkEventExpose* event)
{
  // This is where we draw on the window
  Glib::RefPtr<Gdk::Window> window = get_window();
  if(window)
  {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    // coordinates for the center of the window
    int xc, yc;
    xc = width / 2;
    yc = height / 2;

    Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
    cr->set_line_width(10.0);

    // clip to the area indicated by the expose event so that we only redraw
    // the portion of the window that needs to be redrawn
    cr->rectangle(event->area.x, event->area.y,
            event->area.width, event->area.height);
    cr->clip();

    cr->scale(width, height);
    cr->save();
    cr->set_source_rgb(1, 1, 1);
    cr->paint();
    cr->restore();
    cr->set_line_width(0.12);
    cr->move_to(0.3, 0.3);
    cr->rel_line_to(0.2, -0.2);
    cr->rel_line_to(0.2, 0.2);
    cr->set_line_join(Cairo::LINE_JOIN_MITER); /* def ault */
    cr->stroke();
    cr->move_to(0.3, 0.6);
    cr->rel_line_to(0.2, -0.2);
    cr->rel_line_to(0.2, 0.2);
    cr->set_line_join(Cairo::LINE_JOIN_BEVEL);
    cr->stroke();
    cr->move_to(0.3, 0.9);
    cr->rel_line_to(0.2, -0.2);
    cr->rel_line_to(0.2, 0.2);
    cr->set_line_join(Cairo::LINE_JOIN_ROUND);
    cr->stroke();

  }

  return true;
}
