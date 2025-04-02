/* Copyright (C) 2017 The gtkmm Development Team
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

#ifndef _GDKMM_CAIROUTILS_H
#define _GDKMM_CAIROUTILS_H

#include <gdkmmconfig.h>

#include <cairomm/context.h>
#include <cairomm/region.h>
#include <cairomm/surface.h>
#include <glibmm/containerhandle_shared.h>
#include <type_traits>

namespace Gdk
{
namespace Cairo
{

// Cairomm has no wrap() functions, similar to Glib::wrap().
// They are used in _CONVERSION() macros and in TypeTraits<Cairo::RefPtr<T>>.

/** Creates a Cairo::RefPtr with a C++ wrapper for the C instance.
 *
 * @param cobject The C instance.
 * @param has_reference If true, then the wrapper object takes ownership of
 *        the C instance without increasing its reference count. The reference
 *        count is decreased in the destructor in all cases.
 * @returns A C++ instance that wraps this C instance. If @a cobject is a nullptr,
 *          returns an empty Cairo::RefPtr.
 *
 * @newin{3,92}
 */
GDKMM_API
::Cairo::RefPtr< ::Cairo::Context> wrap(cairo_t* cobject, bool has_reference = true);

/** Creates a Cairo::RefPtr with a C++ wrapper for the C instance.
 *
 * @param cobject The C instance.
 * @param has_reference If true, then the wrapper object takes ownership of
 *        the C instance without increasing its reference count. The reference
 *        count is decreased in the destructor in all cases.
 * @returns A C++ instance that wraps this C instance. If @a cobject is a nullptr,
 *          returns an empty Cairo::RefPtr.
 *
 * @newin{3,92}
 */
GDKMM_API
::Cairo::RefPtr< ::Cairo::Region> wrap(cairo_region_t* cobject, bool has_reference = true);

/** Creates a Cairo::RefPtr with a C++ wrapper for the C instance.
 *
 * @tparam T Cairo::Surface or a subclass of Cairo::Surface.
 * @param cobject The C instance.
 * @param has_reference If true, then the wrapper object takes ownership of
 *        the C instance without increasing its reference count. The reference
 *        count is decreased in the destructor in all cases.
 * @returns A C++ instance that wraps this C instance. If @a cobject is a nullptr,
 *          returns an empty Cairo::RefPtr.
 *
 * @newin{3,92}
 */
template <typename T = ::Cairo::Surface, typename = std::enable_if<std::is_base_of< ::Cairo::Surface, T>::value>>
::Cairo::RefPtr<T> wrap(cairo_surface_t* cobject, bool has_reference = true)
{
  return ::Cairo::make_refptr_for_instance<T>(cobject ? new T(cobject, has_reference) : nullptr);
}

} //namespace Cairo
} //namespace Gdk

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Glib
{
namespace Container_Helpers
{
// Used by Glib::ArrayHandler<>, Glib::ListHandler<>, Glib::SListHandler<>.
// It's not possible to make a specialization like
//   template <T>
//   struct TypeTraits<Cairo::RefPtr<T>>
// because both Glib::RefPtr and Cairo:RefPtr are typedef'ed std::shared_ptr.
// The compiler would see template <T> struct TypeTraits<Cairo::RefPtr<T>> as
// an illegal redefinition of template <T> struct TypeTraits<Glib::RefPtr<T>>.

/** Specialization for pointers to cairo surfaces.
 * The C++ type is always a Cairo::RefPtr<>.
 *
 * @newin{3,92}
 */
template <>
struct TypeTraits<::Cairo::RefPtr<::Cairo::Surface>>
{
  using CppType = ::Cairo::RefPtr<::Cairo::Surface>;
  using CType = ::Cairo::Surface::cobject*;
  using CTypeNonConst = ::Cairo::Surface::cobject*;

  static CType to_c_type(const CppType& ptr) { return ptr ? ptr->cobj() : nullptr; }
  static CType to_c_type(CType ptr) { return ptr; }
  static CppType to_cpp_type(CType ptr) { return Gdk::Cairo::wrap(ptr, false); }
  static void release_c_type(CType ptr) { cairo_surface_destroy(ptr); }
};

/** Specialization for pointers to const cairo surfaces.
 * The C++ type is always a Cairo::RefPtr<>.
 *
 * @newin{3,92}
 */
template <>
struct TypeTraits<::Cairo::RefPtr<const ::Cairo::Surface>>
{
  using CppType = Cairo::RefPtr<const ::Cairo::Surface>;
  using CType = const ::Cairo::Surface::cobject*;
  using CTypeNonConst = ::Cairo::Surface::cobject*;

  static CType to_c_type(const CppType& ptr) { return ptr ? ptr->cobj() : nullptr; }
  static CType to_c_type(CType ptr) { return ptr; }
  static CppType to_cpp_type(CType ptr) { return Gdk::Cairo::wrap(const_cast<CTypeNonConst>(ptr), false); }
  static void release_c_type(CType ptr) { cairo_surface_destroy(const_cast<CTypeNonConst>(ptr)); }
};

} // namespace Container_Helpers
} // namespace Glib
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#endif //_GDKMM_CAIROUTILS_H
