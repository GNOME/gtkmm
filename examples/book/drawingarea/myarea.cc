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

MyArea::MyArea()
{
  // get_window() would return 0 because the Gdk::Window has not yet been realized
  // So we can only allocate the colors here - the rest will happen in on_realize().
  Glib::RefPtr<Gdk::Colormap> colormap = get_default_colormap ();

  blue_ = Gdk::Color("blue");
  red_ = Gdk::Color("red");

  colormap->alloc_color(blue_);
  colormap->alloc_color(red_);
}

MyArea::~MyArea()
{
}

void MyArea::on_realize()
{
  // We need to call the base on_realize()
  Gtk::DrawingArea::on_realize();

  // Now we can allocate any additional resources we need
  Glib::RefPtr<Gdk::Window> window = get_window();
  gc_ = Gdk::GC::create(window);
  window->set_background(red_);
  window->clear();
  gc_->set_foreground(blue_);
}

bool MyArea::on_expose_event(GdkEventExpose*)
{
  // This is where we draw on the window
  Glib::RefPtr<Gdk::Window> window = get_window();
  window->clear();
  window->draw_line(gc_, 1, 1, 100, 100);
  return true;
}

