/* Copyright (C) 2019 The gtkmm Development Team
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
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include <gdkmm/devicewithpad.h>

namespace Gdk
{

DeviceWithPad::DeviceWithPad(GdkDevice* castitem)
:
  Device(castitem)
{}


DeviceWithPad::DeviceWithPad(DeviceWithPad&& src) noexcept
: Device(std::move(src)),
  DevicePad(std::move(src))
{}

DeviceWithPad& DeviceWithPad::operator=(DeviceWithPad&& src) noexcept
{
  Device::operator=(std::move(src));
  DevicePad::operator=(std::move(src));
  return *this;
}

DeviceWithPad::~DeviceWithPad() noexcept
{}

} // namespace Gdk


