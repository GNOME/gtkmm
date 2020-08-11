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

#include <gdkmm/toplevelsurfaceimpl.h>
#include <utility> // std::move()

namespace Gdk
{
ToplevelSurfaceImpl::ToplevelSurfaceImpl(GdkSurface* castitem)
: Glib::ObjectBase(nullptr), Surface(castitem)
{}

ToplevelSurfaceImpl::ToplevelSurfaceImpl(ToplevelSurfaceImpl&& src) noexcept
: Toplevel(std::move(src)),
  Surface(std::move(src))
{}

ToplevelSurfaceImpl& ToplevelSurfaceImpl::operator=(ToplevelSurfaceImpl&& src) noexcept
{
  Toplevel::operator=(std::move(src));
  Surface::operator=(std::move(src));
  return *this;
}

ToplevelSurfaceImpl::~ToplevelSurfaceImpl() noexcept
{}

} // namespace Gdk
