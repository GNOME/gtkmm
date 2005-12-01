/* $Id$ */

/* Copyright 2002      The gtkmm Development Team
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

#ifndef _GDKMM_GENERAL_H
#define _GDKMM_GENERAL_H

#include <gdkmm/pixbuf.h>
#include <cairomm/context.h>

namespace Gdk
{

int screen_width();
int screen_height();

int screen_width_mm();
int screen_height_mm();

void flush();

namespace Cairo
{

/** Sets the specified Gdk::Color as the source color of the Cairo context.
 * @param @context The cairo context.
 * @param color The color to use as the source color. 
 *
 * @newin2p10
 */
void set_source_color(::Cairo::Context& context, const Gdk::Color& color);

/** Sets the given pixbuf as the source pattern for the Cairo context. The pattern has an extend mode of CAIRO_EXTEND_NONE and is aligned so that the origin of pixbuf is pixbuf_x, pixbuf_y.
 * @param @context The cairo context.
 * @param pixbuf A Gdk::Pixbuf
 * @param pixbuf_x X coordinate of location to place upper left corner of pixbuf.
 * @param pixbuf_y Y coordinate of location to place upper left corner of pixbuf.
 *
 * @newin2p10
 */
void set_source_pixbuf(::Cairo::Context& context, const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double pixbuf_x, double pixbuf_y);

//TODO: Rename to add_rectangle_to_path?
void rectangle(::Cairo::Context& context, const Gdk::Rectangle& rectangle);
void region(::Cairo::Context& context, const Gdk::Region& region);

} //namespace Cairo

} //namespace Gdk

#endif //_GDKMM_GENERAL_H

