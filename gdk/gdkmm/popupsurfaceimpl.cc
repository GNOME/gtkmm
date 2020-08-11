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

#include <gdkmm/popupsurfaceimpl.h>
#include <utility> // std::move()

namespace Gdk
{
PopupSurfaceImpl::PopupSurfaceImpl(GdkSurface* castitem)
: Glib::ObjectBase(nullptr), Surface(castitem)
{}

PopupSurfaceImpl::PopupSurfaceImpl(PopupSurfaceImpl&& src) noexcept
: Popup(std::move(src)),
  Surface(std::move(src))
{}

PopupSurfaceImpl& PopupSurfaceImpl::operator=(PopupSurfaceImpl&& src) noexcept
{
  Popup::operator=(std::move(src));
  Surface::operator=(std::move(src));
  return *this;
}

PopupSurfaceImpl::~PopupSurfaceImpl() noexcept
{}

} // namespace Gdk
