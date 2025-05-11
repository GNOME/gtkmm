/* Copyright (C) 2002      The gtkmm Development Team
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
 * License along with this library; if not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _GDKMM_GENERAL_H
#define _GDKMM_GENERAL_H

#include <gdkmm/pixbuf.h>
#include <gdkmm/rectangle.h>
#include <gdkmm/rgba.h>
#include <gdkmm/glcontext.h>
#include <gdkmm/surface.h>
#include <cairomm/context.h>
#include <cairomm/region.h>
#include <cairomm/surface.h>

namespace Gdk
{

namespace Cairo
{

/** Sets the specified Gdk::RGBA as the source color of the Cairo context.
 * @param context The cairo context.
 * @param color The color to use as the source color.
 *
 * @newin{3,0}
 */
GDKMM_API
void set_source_rgba(const ::Cairo::RefPtr< ::Cairo::Context >& context, const Gdk::RGBA& color);

#ifndef GDKMM_DISABLE_DEPRECATED
/** Sets the given pixbuf as the source pattern for the %Cairo context.
 * The pattern has an extend mode of Cairo::Pattern::Extend::NONE and is aligned
 * so that the origin of @a pixbuf is @a pixbuf_x, @a pixbuf_y.
 *
 * @deprecated 4.20: Use Cairo::Context::set_source(const Cairo::RefPtr<Cairo::Surface>& surface, double x, double y) and Gdk::Texture::download().
 *
 * @param context The cairo context.
 * @param pixbuf A Gdk::Pixbuf
 * @param pixbuf_x X coordinate of location to place upper left corner of pixbuf.
 * @param pixbuf_y Y coordinate of location to place upper left corner of pixbuf.
 */
GDKMM_API
void set_source_pixbuf(const ::Cairo::RefPtr< ::Cairo::Context >& context,
  const Glib::RefPtr<const Gdk::Pixbuf>& pixbuf, double pixbuf_x = 0, double pixbuf_y = 0);
#endif // GDKMM_DISABLE_DEPRECATED

/** Adds the given rectangle to the current path of the context.
 *
 * @param context A cairo context.
 * @param rectangle A rectangle to add to the path of the context.
 */
GDKMM_API
void add_rectangle_to_path(const ::Cairo::RefPtr< ::Cairo::Context >& context, const Gdk::Rectangle& rectangle);

/** Adds the given region to the current path of the context.
 *
 * @param context A cairo context.
 * @param region A region to add to the path of the context.
 */
GDKMM_API
void add_region_to_path(const ::Cairo::RefPtr< ::Cairo::Context >& context, const ::Cairo::RefPtr< ::Cairo::Region>& region);

/** Creates a region that covers the area where the given
 * @a surface is more than 50% opaque.
 *
 * This function takes into account device offsets that might be
 * set with Cairo::Surface::set_device_offset().
 *
 * @param surface A cairo surface.
 * @returns A cairo region.
 *
 * @newin{3,24}
 */
GDKMM_API
::Cairo::RefPtr< ::Cairo::Region> create_region_from_surface(const ::Cairo::RefPtr< ::Cairo::Surface>& surface);

#ifndef GDKMM_DISABLE_DEPRECATED
/** This is the main way to draw GL content in gtkmm.
 * It takes a render buffer ID (@a source_type == GL_RENDERBUFFER) or a texture id
 * (@a source_type == GL_TEXTURE) and draws it onto @a context with an OVER operation,
 * respecting the current clip. The top left corner of the rectangle specified by
 * @a x, @a y, @a width and @a height will be drawn at the current (0,0) position
 * of the cairo context.
 *
 * This will work for *all* cairo contexts, as long as @a surface is realized, but the
 * fallback implementation that reads back the pixels from the buffer may be
 * used in the general case. In the case of direct drawing to a surface with
 * no special effects applied to @a context it will however use a more efficient
 * approach.
 *
 * For GL_RENDERBUFFER the code will always fall back to software for buffers
 * with alpha components, so make sure you use GL_TEXTURE if using alpha.
 *
 * Calling this may change the current GL context.
 *
 * @deprecated The function is overly complex and produces broken output
 *   in various combinations of arguments. If you want to draw with GL textures
 *   in Gtkmm, use Gdk::GLTexture::create(); if you want to use that texture in
 *   %Cairo, use Gdk::Texture::download() to download the data into a %Cairo
 *   image surface.
 *
 * @param context A cairo context.
 * @param surface The surface we're rendering for (not necessarily into).
 * @param source The GL ID of the source buffer.
 * @param source_type The type of the @a source.
 * @param buffer_scale The scale-factor that the @a source buffer is allocated for.
 * @param x The source x position in @a source to start copying from in GL coordinates.
 * @param y The source y position in @a source to start copying from in GL coordinates.
 * @param width The width of the region to draw.
 * @param height The height of the region to draw.
 *
 * @newin{3,24}
 */
GDKMM_API
void draw_from_gl(const ::Cairo::RefPtr< ::Cairo::Context >& context,
  const Glib::RefPtr<Gdk::Surface>& surface, int source, int source_type,
  int buffer_scale, int x, int y, int width, int height);
#endif // GDKMM_DISABLE_DEPRECATED

} //namespace Cairo

} //namespace Gdk

#endif //_GDKMM_GENERAL_H
