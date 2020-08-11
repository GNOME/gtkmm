#ifndef _GDKMM_TOPLEVELSURFACEIMPL_H
#define _GDKMM_TOPLEVELSURFACEIMPL_H

/* Copyright (C) 2020 The gtkmm Development Team
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
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gdkmmconfig.h>
#include <gdkmm/toplevel.h>
#include <gdkmm/surface.h>

namespace Gdk
{

/** %Gdk::ToplevelSurfaceImpl is a Gdk::Surface that implements the Gdk::Toplevel interface.
 *
 * The GdkToplevel interface can be implemented by C classes that
 * derive from GdkSurface. No public GTK class implements GdkToplevel.
 * Some GTK functions, such as gdk_surface_new_toplevel(), return an object
 * of a class which is derived from GdkSurface and implements GdkToplevel.
 * Since that C class is not public, it's not wrapped in a C++ class.
 * A C object of such a class can be wrapped in a %Gdk::ToplevelSurfaceImpl object.
 * %Gdk::ToplevelSurfaceImpl does not directly correspond to any GTK class.
 *
 * This class is intended only for wrapping C objects returned from GTK functions.
 *
 * @see Gdk::Surface::create_toplevel()
 * @newin{3,98}
 */
class GDKMM_API ToplevelSurfaceImpl : public Toplevel, public Surface
{
#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
  explicit ToplevelSurfaceImpl(GdkSurface* castitem);
  friend class Surface_Class;

  // noncopyable
  ToplevelSurfaceImpl(const ToplevelSurfaceImpl&) = delete;
  ToplevelSurfaceImpl& operator=(const ToplevelSurfaceImpl&) = delete;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
  ToplevelSurfaceImpl(ToplevelSurfaceImpl&& src) noexcept;
  ToplevelSurfaceImpl& operator=(ToplevelSurfaceImpl&& src) noexcept;

  ~ToplevelSurfaceImpl() noexcept override;
};

} // namespace Gdk

#endif /* _GDKMM_TOPLEVELSURFACEIMPL_H */
