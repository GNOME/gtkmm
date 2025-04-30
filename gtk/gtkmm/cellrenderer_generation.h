#ifndef _GTKMM_CELLRENDERER_GENERATION_H
#define _GTKMM_CELLRENDERER_GENERATION_H
/* cellrenderer_generation.h
 *
 * Copyright (C) 2003 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or(at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <https://www.gnu.org/licenses/>.
 */

#ifndef GTKMM_DISABLE_DEPRECATED // The entire file is deprecated.

#include <gtkmm/cellrenderertext.h>
#include <gtkmm/cellrendererpixbuf.h>
#include <gtkmm/cellrenderertoggle.h>
#include <gtkmm/cellrendereraccel.h>

namespace Gtk
{

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace CellRenderer_Generation
{

template<class T_ModelColumnType> //e.g. bool or Glib::ustring.
CellRenderer* generate_cellrenderer(bool editable = false)
{
  auto cell_renderer = new CellRendererText(); //the default - template specializations will use other renderers.
  //CellRendererText can render both strings and numerical values.

  cell_renderer->property_editable() = editable;

  return cell_renderer;
}

#if !defined(__GNUC__) || __GNUC__ > 2
// gcc 2.95.x fails in TreeView::append_column_editable if the
// following specializations are declared in the header.
template<>
GTKMM_API CellRenderer* generate_cellrenderer<bool>(bool editable);

template<>
GTKMM_API CellRenderer* generate_cellrenderer< Glib::RefPtr<Gdk::Pixbuf> >(bool editable);

template<>
GTKMM_API CellRenderer* generate_cellrenderer<AccelKey>(bool editable);

#endif

} //CellRenderer_Generation
#endif //DOXYGEN_SHOULD_SKIP_THIS

} // namespace Gtk

#endif // GTKMM_DISABLE_DEPRECATED

#endif /* _GTKMM_CELLRENDERER_GENERATION_H */
