#ifndef _GDKMM_DEVICEWITHPAD_H
#define _GDKMM_DEVICEWITHPAD_H

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

#include <gdkmm/device.h>
#include <gdkmm/devicepad.h>

namespace Gdk
{

/** A %Gdk::DeviceWithPad is a Gdk::Device that implements the Gdk::DevicePad interface.
 *
 * Use Gdk::Device::has_device_pad() to check if a %Gdk::Device is in fact a %Gdk::DeviceWithPad.
 * Use Gdk::Device::device_with_pad_cast() to get a Glib::RefPtr<Gdk::DeviceWithPad>.
 */

class GDKMM_API DeviceWithPad : public Device, public DevicePad
{
private:
  // noncopyable
  DeviceWithPad(const DeviceWithPad&) = delete;
  DeviceWithPad& operator=(const DeviceWithPad&) = delete;

  friend class Device_Class;

protected:
  explicit DeviceWithPad(GdkDevice* castitem);

public:

  DeviceWithPad(DeviceWithPad&& src) noexcept;
  DeviceWithPad& operator=(DeviceWithPad&& src) noexcept;

  ~DeviceWithPad() noexcept override;
};

} // namespace Gdk

#endif /* _GDKMM_DEVICEWITHPAD_H */
