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
    int lesser = MIN(width, height);

    // coordinates for the center of the window
    int xc, yc;
    xc = width / 2;
    yc = height / 2;

    Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
    cr->set_line_width(lesser * 0.02);  // outline thickness changes
                                        // with window size

    // clip to the area indicated by the expose event so that we only redraw
    // the portion of the window that needs to be redrawn
    cr->rectangle(event->area.x, event->area.y,
            event->area.width, event->area.height);
    cr->clip();

    // first draw a simple unclosed arc
    cr->save();
    cr->arc(width / 3.0, height / 4.0, lesser / 4.0, -(M_PI / 5.0), M_PI);
    cr->close_path();   // line back to start point
    cr->set_source_rgb(0.0, 0.8, 0.0);
    cr->fill_preserve();
    cr->restore();  // back to opaque black
    cr->stroke();   // outline it

    // now draw a circle
    cr->save();
    cr->arc(xc, yc, lesser / 4.0, 0.0, 2.0 * M_PI); // full circle
    cr->set_source_rgba(0.0, 0.0, 0.8, 0.6);    // partially translucent
    cr->fill_preserve();
    cr->restore();  // back to opaque black
    cr->stroke();

    // and finally an ellipse
    double ex, ey, ew, eh;
    // center of ellipse
    ex = xc;
    ey = 3.0 * height / 4.0;
    // ellipse dimensions
    ew = 3.0 * width / 4.0;
    eh = height / 3.0;

    cr->save();

    cr->translate(ex, ey);  // make (ex, ey) == (0, 0)
    cr->scale(ew / 2.0, eh / 2.0);  // for width: ew / 2.0 == 1.0
                                    // for height: eh / 2.0 == 1.0

    cr->arc(0.0, 0.0, 1.0, 0.0, 2 * M_PI);  // 'circle' centered at (0, 0)
                                            // with 'radius' of 1.0

    cr->set_source_rgba(0.8, 0.0, 0.0, 0.7);
    cr->fill_preserve();
    cr->restore();  // back to opaque black
    cr->stroke();
  }

  return true;
}
