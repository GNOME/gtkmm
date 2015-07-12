/*
 * Copyright (C) 2001 The Free Software Foundation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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

int main(int argc, char** argv)
{
  gtk_init(&argc, &argv);

  std::cout << get_defs( GDK_TYPE_APP_LAUNCH_CONTEXT )
            << get_defs( GDK_TYPE_DRAG_CONTEXT )
            << get_defs( GDK_TYPE_DISPLAY )
#if !defined(G_OS_WIN32)
            << get_defs( GDK_TYPE_DISPLAY_MANAGER )
#endif /* G_OS_WIN32 */
            << get_defs( GDK_TYPE_PIXBUF )
            << get_defs( GDK_TYPE_PIXBUF_ANIMATION )
            << get_defs( GDK_TYPE_PIXBUF_LOADER )
            << get_defs( GDK_TYPE_RGBA )
            << get_defs( GDK_TYPE_SCREEN )
            << get_defs( GDK_TYPE_VISUAL )
            << get_defs( GDK_TYPE_WINDOW )
            << get_defs( GDK_TYPE_GL_CONTEXT )
            ;
  return 0;
}
