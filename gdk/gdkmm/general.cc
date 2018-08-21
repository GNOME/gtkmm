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

#include <gdkmm/general.h>
#include <gdkmm/color.h>
#include <gdk/gdk.h>


namespace Gdk
{

#ifndef GDKMM_DISABLE_DEPRECATED
G_GNUC_BEGIN_IGNORE_DEPRECATIONS
int screen_width()
{
  return gdk_screen_width();
}

int screen_height()
{
  return gdk_screen_height();
}

int screen_width_mm()
{
  return gdk_screen_width_mm();
}

int screen_height_mm()
{
  return gdk_screen_height_mm();
}

void flush()
{
  gdk_flush();
}
G_GNUC_END_IGNORE_DEPRECATIONS
#endif //GDKMM_DISABLE_DEPRECATED

namespace Cairo
{

#ifndef GDKMM_DISABLE_DEPRECATED
G_GNUC_BEGIN_IGNORE_DEPRECATIONS
void set_source_color(const ::Cairo::RefPtr< ::Cairo::Context >& context, const Gdk::Color& color)
{
  gdk_cairo_set_source_color(context->cobj(), const_cast<GdkColor*>(color.gobj()));
}
G_GNUC_END_IGNORE_DEPRECATIONS
#endif //GDKMM_DISABLE_DEPRECATED

void set_source_rgba(const ::Cairo::RefPtr< ::Cairo::Context >& context, const Gdk::RGBA& color)
{
  gdk_cairo_set_source_rgba(context->cobj(), const_cast<GdkRGBA*>(color.gobj()));
}

void set_source_pixbuf(const ::Cairo::RefPtr< ::Cairo::Context >& context, const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double pixbuf_x, double pixbuf_y)
{
  gdk_cairo_set_source_pixbuf(context->cobj(), pixbuf->gobj(), pixbuf_x, pixbuf_y);
}

void add_rectangle_to_path(const ::Cairo::RefPtr< ::Cairo::Context >& context, const Gdk::Rectangle& rectangle)
{
  gdk_cairo_rectangle(context->cobj(), const_cast<GdkRectangle*>(rectangle.gobj()));
}

void add_region_to_path(const ::Cairo::RefPtr< ::Cairo::Context >& context, const ::Cairo::RefPtr< ::Cairo::Region>& region)
{
  gdk_cairo_region(context->cobj(), (region ? region->cobj() : nullptr));
}

bool get_clip_rectangle(const ::Cairo::RefPtr< ::Cairo::Context >& context, Gdk::Rectangle& rectangle)
{
  return gdk_cairo_get_clip_rectangle(context->cobj(), rectangle.gobj());
}

bool get_clip_rectangle(const ::Cairo::RefPtr< ::Cairo::Context >& context)
{
  return gdk_cairo_get_clip_rectangle(context->cobj(), nullptr);
}

::Cairo::RefPtr< ::Cairo::Region> create_region_from_surface(const ::Cairo::RefPtr< ::Cairo::Surface>& surface)
{
  return ::Cairo::RefPtr< ::Cairo::Region>(new ::Cairo::Region(gdk_cairo_region_create_from_surface(surface->cobj()), true));
}

::Cairo::RefPtr< ::Cairo::ImageSurface> create_surface_from_pixbuf(const Glib::RefPtr<const Gdk::Pixbuf>& pixbuf,
  int scale, const Glib::RefPtr<Gdk::Window>& for_window)
{
  return ::Cairo::RefPtr< ::Cairo::ImageSurface>(new ::Cairo::ImageSurface(gdk_cairo_surface_create_from_pixbuf(
    pixbuf->gobj(), scale, for_window ? for_window->gobj() : nullptr), true));
}

void draw_from_gl(const ::Cairo::RefPtr< ::Cairo::Context >& context,
  const Glib::RefPtr<Gdk::Window>& window, int source, int source_type,
  int buffer_scale, int x, int y, int width, int height)
{
  gdk_cairo_draw_from_gl(context->cobj(), window->gobj(), source, source_type,
    buffer_scale, x, y, width, height);
}

} //namespace Cairo

} //namespace Gdk
