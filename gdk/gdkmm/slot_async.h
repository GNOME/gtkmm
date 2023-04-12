#ifndef _GDKMM_SLOT_ASYNC_H
#define _GDKMM_SLOT_ASYNC_H

/* Copyright (C) 2023 The gtkmm Development Team
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
#include <gio/gio.h>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

// Gdk::gdkmm_SignalProxy_async_callback() is a copy of Gio::giomm_SignalProxy_async_callback().
// It has been copied to gtkmm because it's new in glibmm 2.78. Gtkmm 4.12 does not
// depend on glibmm 2.78. When gtkmm depends on glibmm 2.78 or newer,
// gdkmm_SignalProxy_async_callback() becomes unnecessary.
//TODO: When gtkmm depends on glibmm 2.78 or newer and ABI can be broken, remove
// gdkmm_SignalProxy_async_callback(), and use Gio::giomm_SignalProxy_async_callback()
// instead.
namespace Gdk
{
extern "C"
{
/** Callback function, used in combination with Gio::SlotAsyncReady.
 *
 * Example:
 * @code
 * _WRAP_METHOD(void read_async(const std::vector<Glib::ustring>& mime_types,
 *   int io_priority, const Gio::SlotAsyncReady& slot{callback},
 *   const Glib::RefPtr<Gio::Cancellable>& cancellable{.?}), gdk_drop_read_async,
 *   slot_name slot, slot_callback Gdk::gdkmm_SignalProxy_async_callback)
 * @endcode
 *
 * @newin{4,12}
 */
GDKMM_API
void gdkmm_SignalProxy_async_callback(GObject*, GAsyncResult* res, void* data);

} // extern "C"

} // namespace Gdk

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#endif /* _GDKMM_SLOT_ASYNC_H */
