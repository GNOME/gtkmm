#ifndef _GDKMM_DRAGSURFACEIMPL_H
#define _GDKMM_DRAGSURFACEIMPL_H

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
#include <gdkmm/dragsurface.h>
#include <gdkmm/surface.h>

namespace Gdk
{

/** %Gdk::DragSurfaceImpl is a Gdk::Surface that implements the Gdk::DragSurface interface.
 *
 * The GdkDragSurface interface can be implemented by C classes that
 * derive from GdkSurface. No public GTK class implements GdkDragSurface.
 * Some GTK functions, such as gdk_drag_get_drag_surface(), return an object
 * of a class which is derived from GdkSurface and implements GdkDragSurface.
 * Since that C class is not public, it's not wrapped in a C++ class.
 * A C object of such a class can be wrapped in a %Gdk::DragSurfaceImpl object.
 * %Gdk::DragSurfaceImpl does not directly correspond to any GTK class.
 *
 * This class is intended only for wrapping C objects returned from GTK functions.
 *
 * @see Gdk::Drag::get_drag_surface()
 * @newin{3,98}
 */
class GDKMM_API DragSurfaceImpl : public DragSurface, public Surface
{
#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
  explicit DragSurfaceImpl(GdkSurface* castitem);
  friend class Surface_Class;

  // noncopyable
  DragSurfaceImpl(const DragSurfaceImpl&) = delete;
  DragSurfaceImpl& operator=(const DragSurfaceImpl&) = delete;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
  DragSurfaceImpl(DragSurfaceImpl&& src) noexcept;
  DragSurfaceImpl& operator=(DragSurfaceImpl&& src) noexcept;

  ~DragSurfaceImpl() noexcept override;
};

} // namespace Gdk

#endif /* _GDKMM_DRAGSURFACEIMPL_H */
