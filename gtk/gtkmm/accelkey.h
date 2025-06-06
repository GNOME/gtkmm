#ifndef _GTKMM_ACCELKEY_H
#define _GTKMM_ACCELKEY_H

/* Copyright (C) 1998-2002 The gtkmm Development Team
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
 * License along with this library; if not, see <https://www.gnu.org/licenses/>.
 */

#include <gtkmmconfig.h>

#include <gdk/gdkkeysyms.h>
#include <gdkmm/enums.h>

namespace Gtk
{

/** Defines accelerator key combinations.
 * For instance, pressing Control-Q to activate the File|Quit menu item.
 *
 * By defining accelerator paths you can allow the user of your application
 * to change accelerators himself. An example of an accelerator might be
 * "<MainWindow>/File/Open". Modified accelerators may be saved.
 *
 * Key values are the codes which are sent whenever a key is pressed or released.
 * The complete list of key values can be found in the
 * <a href="https://gitlab.gnome.org/GNOME/gtk/tree/main/gdk/gdkkeysyms.h">gdk/gdkkeysyms.h</a>
 * header file. They are prefixed with <tt>GDK_KEY_</tt>.
 *
 * @ingroup Menus
 */
class GTKMM_API AccelKey
{
public:
  AccelKey();

 /** AccelKey constructor.
  * @param accel_key For instance, 'q'
  * @param accel_mods For instance, Gdk::ModifierType::CONTROL_MASK
  * @param accel_path For instance, "<MainWindow>/File/Open"
  */
  AccelKey(guint accel_key, Gdk::ModifierType accel_mods,
           const Glib::ustring& accel_path = {});

  /** AccelKey constructor.
   * @param accelerator For instance, &quot;&lt;control&gt;q&quot; - Use
   *     &lt;control&gt;, &lt;shift&gt;, &lt;alt&gt; and &lt;release&gt;.
   *     Use F1, F2, etc, for function keys.
   * @param accel_path For instance, "<MainWindow>/File/Open"
   */
  AccelKey(const Glib::ustring& accelerator,
           const Glib::ustring& accel_path = {});

  AccelKey(const AccelKey& src);

  AccelKey& operator=(const AccelKey& src);

  bool is_null() const;

  /**
   * Gets the accelerator key.
   */
  guint get_key() const;
  /**
   * Gets the accelerator modifier.
   */
  Gdk::ModifierType get_mod() const;
  /**
   * Gets the accelerator path.
   */
  Glib::ustring get_path() const;
  /**
   * Gets the accelerator representation for labels.
   */
  Glib::ustring get_abbrev() const;

protected:
  guint key_;
  Gdk::ModifierType mod_;
  Glib::ustring path_;
};

} /* namespace Gtk */

#endif //_GTKMM_ACCELKEY_H
