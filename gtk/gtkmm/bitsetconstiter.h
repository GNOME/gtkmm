#ifndef _GTKMM_BITSETCONSTITER_H
#define _GTKMM_BITSETCONSTITER_H

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
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmmconfig.h>
#include <iterator>
#include <memory>
#include <gtk/gtk.h>

namespace Gtk
{

/** Alias: Gtk::Bitset::const_iterator.
 *
 * A %BitsetConstIter is a reference to a specific element in a specific bitset.
 *
 * This is a const_iterator. There is no way to modify the bitset via an iterator.
 * For modifying the bitset, use methods in Gtk::Bitset.
 *
 * @see Bitset
 *
 * @newin{3,98}
 */
class BitsetConstIter
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type        = guint;
  using difference_type   = int;
  using reference         = value_type;
  using pointer           = void;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GTKMM_API BitsetConstIter() {}
  GTKMM_API BitsetConstIter(const GtkBitset* bitset, bool is_end);
#endif // DOXYGEN_SHOULD_SKIP_THIS

  GTKMM_API BitsetConstIter(const BitsetConstIter& other);
  GTKMM_API BitsetConstIter& operator=(const BitsetConstIter& other);
  GTKMM_API BitsetConstIter(BitsetConstIter&& other) noexcept;
  GTKMM_API BitsetConstIter& operator=(BitsetConstIter&& other) noexcept;

  GTKMM_API BitsetConstIter& operator++();
  GTKMM_API BitsetConstIter  operator++(int);
  GTKMM_API BitsetConstIter& operator--();
  GTKMM_API BitsetConstIter  operator--(int);
  GTKMM_API reference operator*() const;

  /** Discovers whether the iterator is valid, and not equal to end().
   * For instance,
   * @code
   * if (bitset_iter)
   *   do_something();
   * @endcode
   */
  GTKMM_API explicit operator bool() const noexcept;

  GTKMM_API bool equal(const BitsetConstIter& other) const noexcept;

private:
  std::unique_ptr<GtkBitsetIter> gobject_;
  // BitsetConstIter does not own a reference to the GtkBitset.
  const GtkBitset* bitset_ = nullptr;
  bool is_end_ = true;
};

/** @relates Gtk::BitsetConstIter */
inline bool operator==(const BitsetConstIter& lhs, const BitsetConstIter& rhs)
{ return lhs.equal(rhs); }

/** @relates Gtk::BitsetConstIter */
inline bool operator!=(const BitsetConstIter& lhs, const BitsetConstIter& rhs)
{ return !lhs.equal(rhs); }

} // namespace Gtk

#endif /* _GTKMM_BITSETCONSTITER_H */
