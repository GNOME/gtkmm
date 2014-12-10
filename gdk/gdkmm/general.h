/* Copyright 2002      The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _GDKMM_GENERAL_H
#define _GDKMM_GENERAL_H

#include <gdkmm/pixbuf.h>
#include <gdkmm/color.h>
#include <gdkmm/rectangle.h>
#include <gdkmm/rgba.h>
#include <cairomm/context.h>
#include <cairomm/region.h>

namespace Gdk
{

int screen_width();
int screen_height();

int screen_width_mm();
int screen_height_mm();

void flush();

namespace Cairo
{

#ifndef GDKMM_DISABLE_DEPRECATED

/** Sets the specified Gdk::Color as the source color of the Cairo context.
 * @param context The cairo context.
 * @param color The color to use as the source color.
 *
 * @newin{2,10}
 * @deprecated Use set_source_rgba() instead.
 */
void set_source_color(const ::Cairo::RefPtr< ::Cairo::Context >& context, const Gdk::Color& color);

#endif //GDKMM_DISABLE_DEPRECATED

/** Sets the specified Gdk::RGBA as the source color of the Cairo context.
 * @param context The cairo context.
 * @param color The color to use as the source color.
 *
 * @newin{3,0}
 */
void set_source_rgba(const ::Cairo::RefPtr< ::Cairo::Context >& context, const Gdk::RGBA& color);


/** Sets the given pixbuf as the source pattern for the Cairo context. The pattern has an extend mode of CAIRO_EXTEND_NONE and is aligned so that the origin of pixbuf is pixbuf_x, pixbuf_y.
 * @param context The cairo context.
 * @param pixbuf A Gdk::Pixbuf
 * @param pixbuf_x X coordinate of location to place upper left corner of pixbuf.
 * @param pixbuf_y Y coordinate of location to place upper left corner of pixbuf.
 *
 * @newin{2,10}
 */
void set_source_pixbuf(const ::Cairo::RefPtr< ::Cairo::Context >& context, const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double pixbuf_x = 0, double pixbuf_y = 0);

//TODO: Wrap gdk_cairo_set_source_window()?

/** Adds the given rectangle to the current path of the context.
 *
 * @param context A cairo context.
 * @param rectangle A rectangle to add to the path of the context.
 *
 * @newin{2,10}
 */
void add_rectangle_to_path(const ::Cairo::RefPtr< ::Cairo::Context >& context, const Gdk::Rectangle& rectangle);

/** Adds the given region to the current path of the context.
 *
 * @param context A cairo context.
 * @param region A region to add to the path of the context.
 *
 * @newin{2,10}
 */
void add_region_to_path(const ::Cairo::RefPtr< ::Cairo::Context >& context, const ::Cairo::RefPtr< ::Cairo::Region>& region);

} //namespace Cairo

} //namespace Gdk

#endif //_GDKMM_GENERAL_H
