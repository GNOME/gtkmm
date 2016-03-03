/* gtkmm - a C++ wrapper for the Gtk toolkit
 *
 * Copyright 1999-2002 The gtkmm Development Team
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
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _GTKMM_H
#define _GTKMM_H

/** @mainpage gtkmm Reference Manual
 *
 * @section description Description
 *
 * gtkmm is the official C++ interface for the popular GUI library GTK+.
 * Highlights include typesafe callbacks, and a comprehensive set of widgets
 * that are easily extensible via inheritance.
 *
 * For instance, see @ref Widgets, @ref Dialogs, @ref TreeView "TreeView" and
 * @ref TextView "TextView".
 *
 * See also the
 * <a href="http://library.gnome.org/devel/gtkmm-tutorial/stable/">Programming
 * with gtkmm</a> book.
 *
 *
 * @section features Features
 *
 * - GTK+’s mature, capable set of @ref Widgets widgets. See
 *   <a href="http://www.gtk.org/">the GTK+ website</a> for more information.
 * - Use inheritance to derive custom widgets.
 * - Type-safe signal handlers (slots), in standard C++, using
 *   <a href="http://libsigc.sourceforge.net/">libsigc++</a>.
 * - Polymorphism.
 * - Use of the Standard C++ Library, including strings, containers and
 *   iterators.
 * - Full internationalisation with UTF8.
 * - Complete C++ memory management.
 *   - Member instances or dynamic new and delete.
 *   - Optional automatic deletion of child widgets.
 *   - No manual reference-counting.
 * - Full use of C++ namespaces.
 * - No macros.
 *
 * @section basics Basic Usage
 *
 * Include the gtkmm header:
 * @code
 * #include <gtkmm.h>
 * @endcode
 * (You may include individual headers, such as @c gtkmm/button.h instead.)
 *
 * If your source file is @c program.cc, you can compile it with:
 * @code
 * g++ program.cc -o program  `pkg-config --cflags --libs gtkmm-3.0`
 * @endcode
 *
 * Alternatively, if using autoconf, use the following in @c configure.ac:
 * @code
 * PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0])
 * @endcode
 * Then use the generated @c GTKMM_CFLAGS and @c GTKMM_LIBS variables in the
 * project @c Makefile.am files. For example:
 * @code
 * program_CPPFLAGS = $(GTKMM_CFLAGS)
 * program_LDADD = $(GTKMM_LIBS)
 * @endcode
 */

/* Gtkmm version.  */
extern const int gtkmm_major_version;
extern const int gtkmm_minor_version;
extern const int gtkmm_micro_version;

#include <glibmm.h>
#include <giomm.h>

#include <gdkmm/dragcontext.h> //TODO: Remove this. It works around a strange compilation problem with Cairo::Surface in the tests.

#include <gdkmm.h>

//Include these first so they can do some undef/re-def magic for StockID.
#include <gtkmm/toggleaction.h>
#include <gtkmm/radioaction.h>

#include <gtkmm/object.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/accelkey.h>
#include <gtkmm/accelmap.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/actionable.h>
#include <gtkmm/actionbar.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/alignment.h>
#include <gtkmm/appchooserbutton.h>
#include <gtkmm/appchooserdialog.h>
#include <gtkmm/appchooserwidget.h>
#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/arrow.h>
#include <gtkmm/aspectframe.h>
#include <gtkmm/assistant.h>
#include <gtkmm/base.h>
#include <gtkmm/bin.h>
#include <gtkmm/border.h>
#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/cellarea.h>
#include <gtkmm/cellareabox.h>
#include <gtkmm/cellareacontext.h>
#include <gtkmm/cellview.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/checkmenuitem.h>
#include <gtkmm/cellrenderer.h>
#include <gtkmm/cellrendereraccel.h>
#include <gtkmm/cellrenderercombo.h>
#include <gtkmm/cellrendererpixbuf.h>
#include <gtkmm/cellrendererprogress.h>
#include <gtkmm/cellrendererspin.h>
#include <gtkmm/cellrendererspinner.h>
#include <gtkmm/cellrenderertext.h>
#include <gtkmm/cellrenderertoggle.h>
#include <gtkmm/colorbutton.h>
#include <gtkmm/colorchooser.h>
#include <gtkmm/colorchooserdialog.h>
#include <gtkmm/colorselection.h>
#include <gtkmm/combobox.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/container.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/csssection.h>
#include <gtkmm/dialog.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/editable.h>
#include <gtkmm/entry.h>
#include <gtkmm/expander.h>
#include <gtkmm/enums.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/eventcontroller.h>
#include <gtkmm/filechooser.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/filechooserwidget.h>
#include <gtkmm/filefilter.h>
#include <gtkmm/fixed.h>
#include <gtkmm/flowbox.h>
#include <gtkmm/flowboxchild.h>
#include <gtkmm/fontbutton.h>
#include <gtkmm/fontchooser.h>
#include <gtkmm/fontchooserdialog.h>
#include <gtkmm/fontchooserwidget.h>
#include <gtkmm/fontselection.h>
#include <gtkmm/frame.h>
#include <gtkmm/gesture.h>
#include <gtkmm/gesturedrag.h>
#include <gtkmm/gesturelongpress.h>
#include <gtkmm/gesturemultipress.h>
#include <gtkmm/gesturepan.h>
#include <gtkmm/gesturerotate.h>
#include <gtkmm/gesturesingle.h>
#include <gtkmm/gestureswipe.h>
#include <gtkmm/gesturezoom.h>
#include <gtkmm/glarea.h>
#include <gtkmm/grid.h>
#include <gtkmm/handlebox.h>
#include <gtkmm/headerbar.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/hvbuttonbox.h>
#include <gtkmm/hvpaned.h>
#include <gtkmm/hvscale.h>
#include <gtkmm/hvscrollbar.h>
#include <gtkmm/hvseparator.h>
#include <gtkmm/iconset.h>
#include <gtkmm/iconfactory.h>
#include <gtkmm/iconsource.h>
#include <gtkmm/icontheme.h>
#include <gtkmm/iconview.h>
#include <gtkmm/image.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/infobar.h>
#include <gtkmm/calendar.h>
#include <gtkmm/invisible.h>
#include <gtkmm/label.h>
#include <gtkmm/layout.h>
#include <gtkmm/levelbar.h>
#include <gtkmm/listbox.h>
#include <gtkmm/listboxrow.h>
#include <gtkmm/liststore.h>
#include <gtkmm/listviewtext.h>
#include <gtkmm/linkbutton.h>
#include <gtkmm/main.h>
#include <gtkmm/menu.h>
#include <gtkmm/menubar.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/menushell.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/misc.h>
#include <gtkmm/modelbutton.h>
#include <gtkmm/notebook.h>
#include <gtkmm/numerableicon.h>
#include <gtkmm/object.h>
#include <gtkmm/offscreenwindow.h>
#include <gtkmm/overlay.h>
#include <gtkmm/paned.h>
#include <gtkmm/pagesetup.h>
#ifndef G_OS_WIN32
# include <gtkmm/pagesetupunixdialog.h>
#endif
#include <gtkmm/papersize.h>
#include <gtkmm/placessidebar.h>
#include <gtkmm/popover.h>
#include <gtkmm/popovermenu.h>
#include <gtkmm/printcontext.h>
#ifndef G_OS_WIN32
# include <gtkmm/printer.h>
# include <gtkmm/printjob.h>
#endif
#include <gtkmm/printoperation.h>
#include <gtkmm/printoperationpreview.h>
#include <gtkmm/printsettings.h>
#ifndef G_OS_WIN32
# include <gtkmm/printunixdialog.h>
#endif
#include <gtkmm/progressbar.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/radiomenuitem.h>
#include <gtkmm/radiotoolbutton.h>
#include <gtkmm/range.h>
#include <gtkmm/recentaction.h>
#include <gtkmm/recentchooser.h>
#include <gtkmm/recentchooserdialog.h>
#include <gtkmm/recentchoosermenu.h>
#include <gtkmm/recentchooserwidget.h>
#include <gtkmm/recentfilter.h>
#include <gtkmm/recentinfo.h>
#include <gtkmm/recentmanager.h>
#include <gtkmm/revealer.h>
#include <gtkmm/scale.h>
#include <gtkmm/scalebutton.h>
#include <gtkmm/scrollbar.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/searchbar.h>
#include <gtkmm/searchentry.h>
#include <gtkmm/separator.h>
#include <gtkmm/separatormenuitem.h>
#include <gtkmm/separatortoolitem.h>
#include <gtkmm/settings.h>
#include <gtkmm/shortcutsgroup.h>
#include <gtkmm/shortcutssection.h>
#include <gtkmm/shortcutsshortcut.h>
#include <gtkmm/shortcutswindow.h>
#include <gtkmm/sizegroup.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/spinner.h>
#include <gtkmm/stack.h>
#include <gtkmm/stacksidebar.h>
#include <gtkmm/stackswitcher.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/statusicon.h>
#include <gtkmm/stock.h>
#include <gtkmm/stockitem.h>
#include <gtkmm/stylecontext.h>
#include <gtkmm/styleproperty.h>
#include <gtkmm/switch.h>
#include <gtkmm/table.h>
#include <gtkmm/tearoffmenuitem.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/textchildanchor.h>
#include <gtkmm/textiter.h>
#include <gtkmm/textmark.h>
#include <gtkmm/texttag.h>
#include <gtkmm/texttagtable.h>
#include <gtkmm/textview.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/toolitem.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/toolpalette.h>
#include <gtkmm/toggletoolbutton.h>
#include <gtkmm/menutoolbutton.h>
#include <gtkmm/tooltip.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treemodelfilter.h>
#include <gtkmm/treemodelsort.h>
#include <gtkmm/treepath.h>
#include <gtkmm/treerowreference.h>
#include <gtkmm/treeselection.h>
#include <gtkmm/treestore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treeviewcolumn.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/viewport.h>
#include <gtkmm/volumebutton.h>
#include <gtkmm/widget.h>
#include <gtkmm/widgetpath.h>
#include <gtkmm/window.h>
#include <gtkmm/stockid.h>

#endif /* #ifndef GTKMM_H */
