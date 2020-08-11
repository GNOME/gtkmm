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

#include <gdkmm/dragsurfaceimpl.h>
#include <utility> // std::move()

namespace Gdk
{
DragSurfaceImpl::DragSurfaceImpl(GdkSurface* castitem)
: Glib::ObjectBase(nullptr), Surface(castitem)
{}

DragSurfaceImpl::DragSurfaceImpl(DragSurfaceImpl&& src) noexcept
: DragSurface(std::move(src)),
  Surface(std::move(src))
{}

DragSurfaceImpl& DragSurfaceImpl::operator=(DragSurfaceImpl&& src) noexcept
{
  DragSurface::operator=(std::move(src));
  Surface::operator=(std::move(src));
  return *this;
}

DragSurfaceImpl::~DragSurfaceImpl() noexcept
{}

} // namespace Gdk
