#ifndef _GTKMM_ACCELERATOR_H
#define _GTKMM_ACCELERATOR_H
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

#include <glibmm/ustring.h>
#include <gdkmm/enums.h>

// The corresponding gtk functions are declared in gtkaccelgroup.h.

namespace Gtk
{

/** Utilities for keyboard accelerators.
 *
 * We have various utility functions to parse and generate
 * textual representations of keyboard accelerators.
 *
 * If you want to set up keyboard accelerators for widgets,
 * Gtk::ShortcutTrigger is probably more convenient than the
 * functions in this namespace.
 *
 * Key values are the codes which are sent whenever a key is pressed or released.
 * The complete list of key values can be found in the
 * <a href="https://gitlab.gnome.org/GNOME/gtk/tree/main/gdk/gdkkeysyms.h">gdk/gdkkeysyms.h</a>
 * header file. They are prefixed with <tt>GDK_KEY_</tt>.
 */
namespace Accelerator
{
  /** Determines whether a given keyval and modifier mask constitute
   * a valid keyboard accelerator.
   *
   * For example, the 'a' keyval plus Gdk::ModifierType::CONTROL_MASK is valid -
   * this is a "Ctrl+a" accelerator. But you can't, for instance, use the
   * GDK_KEY_Control_L keyval as an accelerator.
   *
   * @return <tt>true</tt> if the accelerator is valid.
   */
  GTKMM_API
  bool valid(guint keyval, Gdk::ModifierType modifiers);

  /** Parses a string representing an accelerator.
   *
   * The format looks like “\<Control\>a” or “\<Shift\>\<Alt\>F1”.
   *
   * The parser is fairly liberal and allows lower or upper case, and also
   * abbreviations such as “\<Ctl\>” and “\<Ctrl\>”. Key names are parsed using
   * gdk_keyval_from_name(). For character keys the name is not the symbol,
   * but the lowercase name, e.g. one would use “\<Ctrl\>minus” instead of
   * “\<Ctrl\>-”.
   *
   * If the parse fails, @a accelerator_key and @a accelerator_mods will
   * be set to 0 (zero).
   *
   * @param accelerator See the Gtk::AccelKey constructor for the format.
   * @param[out] accelerator_key Accelerator keyval.
   * @param[out] accelerator_mods Accelerator modifier mask.
   * @return <tt>true</tt> if parsing succeeded.
   */
  GTKMM_API
  bool parse(const Glib::ustring& accelerator, guint& accelerator_key,
    Gdk::ModifierType& accelerator_mods);

  /** Converts an accelerator keyval and modifier mask
   * into a string parseable by parse().
   *
   * For example, if you pass in 'q' and Gdk::ModifierType::CONTROL_MASK,
   * it returns "\<Control\>q".
   *
   * If you need to display accelerators in the user interface, see get_label().
   *
   * @param accelerator_key Accelerator keyval.
   * @param accelerator_mods Accelerator modifier mask.
   * @return The accelerator name.
   */
  GTKMM_API
  Glib::ustring name(guint accelerator_key, Gdk::ModifierType accelerator_mods);
  
  /** Converts an accelerator keyval and modifier mask into a string
   * which can be used to represent the accelerator to the user.
   * 
   * @param accelerator_key Accelerator keyval.
   * @param accelerator_mods Accelerator modifier mask.
   * @return A string representing the accelerator.
   */
  GTKMM_API
  Glib::ustring get_label(guint accelerator_key, Gdk::ModifierType accelerator_mods);

  /** Gets the modifier mask.
   *
   * The modifier mask determines which modifiers are considered significant
   * for keyboard accelerators. This includes all keyboard modifiers except
   * for %GDK_LOCK_MASK.
   *
   * @return The modifier mask for accelerators
   */
  GTKMM_API
  Gdk::ModifierType get_default_mod_mask();

} // namespace Accelerator

} // namespace Gtk
#endif /* _GTKMM_ACCELERATOR_H */
