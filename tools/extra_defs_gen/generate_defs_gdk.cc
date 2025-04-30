/* Copyright (C) 2001 The Free Software Foundation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <https://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif
// We always need to generate the .defs for all types because the code
// using deprecated API is generated unconditionally and only disabled
// at compile time.
#undef GDK_PIXBUF_DISABLE_DEPRECATED
#undef GDK_DISABLE_DEPRECATED
#undef GTK_DISABLE_DEPRECATED

#include <glibmm_generate_extra_defs/generate_extra_defs.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>

int main(int /* argc */, char** /* argv */)
{
  gtk_init();

  std::cout << get_defs( GDK_TYPE_APP_LAUNCH_CONTEXT )
            << get_defs( GDK_TYPE_CICP_PARAMS )
            << get_defs( GDK_TYPE_CLIPBOARD )
            << get_defs( GDK_TYPE_CONTENT_PROVIDER )
            << get_defs( GDK_TYPE_CURSOR )
            << get_defs( GDK_TYPE_DEVICE )
            << get_defs( GDK_TYPE_DEVICE_TOOL )
            << get_defs( GDK_TYPE_DISPLAY )
#if !defined(G_OS_WIN32)
            << get_defs( GDK_TYPE_DISPLAY_MANAGER )
#endif /* G_OS_WIN32 */
            << get_defs( GDK_TYPE_DMABUF_TEXTURE_BUILDER )
            << get_defs( GDK_TYPE_DRAG )
            << get_defs( GDK_TYPE_DRAG_SURFACE )
            << get_defs( GDK_TYPE_DRAW_CONTEXT )
            << get_defs( GDK_TYPE_DROP )
            << get_defs( GDK_TYPE_FRAME_CLOCK )
            << get_defs( GDK_TYPE_GL_TEXTURE_BUILDER )
            << get_defs( GDK_TYPE_MEMORY_TEXTURE_BUILDER )
            << get_defs( GDK_TYPE_MONITOR )
            << get_defs( GDK_TYPE_PAINTABLE )
            << get_defs( GDK_TYPE_PIXBUF )
            << get_defs( GDK_TYPE_PIXBUF_ANIMATION )
            << get_defs( GDK_TYPE_PIXBUF_LOADER )
            << get_defs( GDK_TYPE_POPUP )
            << get_defs( GDK_TYPE_SEAT )
            << get_defs( GDK_TYPE_SURFACE )
            << get_defs( GDK_TYPE_TEXTURE )
            << get_defs( GDK_TYPE_TOPLEVEL )
            << get_defs( GDK_TYPE_GL_CONTEXT )
            ;
  return 0;
}
