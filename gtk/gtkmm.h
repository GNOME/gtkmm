/* gtkmm - a C++ wrapper for the Gtk toolkit
 *
 * Copyright (C) 1999-2002 The gtkmm Development Team
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

#ifndef _GTKMM_H
#define _GTKMM_H

/** @mainpage gtkmm Reference Manual
 *
 * @section description Description
 *
 * gtkmm is the official C++ interface for the popular GUI library GTK.
 * Highlights include typesafe callbacks, and a comprehensive set of widgets
 * that are easily extensible via inheritance.
 *
 * For instance, see @ref Widgets, @ref Dialogs, @ref ListView "ListView" and
 * @ref TextView "TextView".
 *
 * See also the
 * <a href="https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/">Programming
 * with gtkmm</a> book.
 *
 * @section features Features
 *
 * - GTK’s mature, capable set of @ref Widgets "widgets". See
 *   <a href="https://www.gtk.org/">the GTK website</a> for more information.
 * - Use inheritance to derive custom widgets.
 * - Type-safe signal handlers (slots), in standard C++, using
 *   <a href="https://libsigcplusplus.github.io/libsigcplusplus/">libsigc++</a>.
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
 * g++ program.cc -o program  `pkg-config --cflags --libs gtkmm-4.0`
 * @endcode
 * If your version of g++ is not C++17-compliant by default,
 * add the @c -std=c++17 option.
 *
 * If you use <a href="https://mesonbuild.com/">Meson</a>, include the following
 * in @c meson.build:
 * @code
 * gtkmm_dep = dependency('gtkmm-4.0')
 * program_name = 'program'
 * cpp_sources = [ 'program.cc' ]
 * executable(program_name,
 *   cpp_sources,
 *   dependencies: gtkmm_dep
 * )
 * @endcode
 *
 * Alternatively, if using autoconf, use the following in @c configure.ac:
 * @code
 * PKG_CHECK_MODULES([GTKMM], [gtkmm-4.0])
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

#include <gdkmm.h>
#include <gskmm.h>

#include <gtkmm/object.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/accelerator.h>
#include <gtkmm/accelkey.h>
#include <gtkmm/accessibletext.h>
#include <gtkmm/actionable.h>
#include <gtkmm/actionbar.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/alertdialog.h>
#include <gtkmm/appchooserbutton.h>
#include <gtkmm/appchooserdialog.h>
#include <gtkmm/appchooserwidget.h>
#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/aspectframe.h>
#include <gtkmm/assistant.h>
#include <gtkmm/atcontext.h>
#include <gtkmm/binlayout.h>
#include <gtkmm/boolfilter.h>
#include <gtkmm/border.h>
#include <gtkmm/box.h>
#include <gtkmm/boxlayout.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/cellarea.h>
#include <gtkmm/cellareabox.h>
#include <gtkmm/cellareacontext.h>
#include <gtkmm/cellview.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/cellrenderer.h>
#include <gtkmm/cellrendereraccel.h>
#include <gtkmm/cellrenderercombo.h>
#include <gtkmm/cellrendererpixbuf.h>
#include <gtkmm/cellrendererprogress.h>
#include <gtkmm/cellrendererspin.h>
#include <gtkmm/cellrendererspinner.h>
#include <gtkmm/cellrenderertext.h>
#include <gtkmm/cellrenderertoggle.h>
#include <gtkmm/centerbox.h>
#include <gtkmm/centerlayout.h>
#include <gtkmm/colorbutton.h>
#include <gtkmm/colorchooser.h>
#include <gtkmm/colorchooserdialog.h>
#include <gtkmm/colordialogbutton.h>
#include <gtkmm/columnview.h>
#include <gtkmm/columnviewcell.h>
#include <gtkmm/columnviewrow.h>
#include <gtkmm/columnviewsorter.h>
#include <gtkmm/combobox.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/constraintlayout.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/csssection.h>
#include <gtkmm/dialog.h>
#include <gtkmm/directorylist.h>
#include <gtkmm/dragicon.h>
#include <gtkmm/dragsource.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/dropcontrollermotion.h>
#include <gtkmm/dropdown.h>
#include <gtkmm/droptarget.h>
#include <gtkmm/droptargetasync.h>
#include <gtkmm/editablelabel.h>
#include <gtkmm/emojichooser.h>
#include <gtkmm/entry.h>
#include <gtkmm/expander.h>
#include <gtkmm/enums.h>
#include <gtkmm/error.h>
#include <gtkmm/eventcontroller.h>
#include <gtkmm/eventcontrollerfocus.h>
#include <gtkmm/eventcontrollerkey.h>
#include <gtkmm/eventcontrollerlegacy.h>
#include <gtkmm/eventcontrollermotion.h>
#include <gtkmm/eventcontrollerscroll.h>
#include <gtkmm/filechooser.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/filechoosernative.h>
#include <gtkmm/filechooserwidget.h>
#include <gtkmm/filedialog.h>
#include <gtkmm/filefilter.h>
#include <gtkmm/filelauncher.h>
#include <gtkmm/filterlistmodel.h>
#include <gtkmm/fixed.h>
#include <gtkmm/fixedlayout.h>
#include <gtkmm/fixedlayoutchild.h>
#include <gtkmm/flattenlistmodel.h>
#include <gtkmm/flowbox.h>
#include <gtkmm/flowboxchild.h>
#include <gtkmm/fontbutton.h>
#include <gtkmm/fontchooser.h>
#include <gtkmm/fontchooserdialog.h>
#include <gtkmm/fontchooserwidget.h>
#include <gtkmm/fontdialogbutton.h>
#include <gtkmm/frame.h>
#include <gtkmm/gesture.h>
#include <gtkmm/gestureclick.h>
#include <gtkmm/gesturedrag.h>
#include <gtkmm/gesturelongpress.h>
#include <gtkmm/gesturepan.h>
#include <gtkmm/gesturerotate.h>
#include <gtkmm/gesturesingle.h>
#include <gtkmm/gesturestylus.h>
#include <gtkmm/gestureswipe.h>
#include <gtkmm/gesturezoom.h>
#include <gtkmm/glarea.h>
#include <gtkmm/graphicsoffload.h>
#include <gtkmm/grid.h>
#include <gtkmm/gridlayout.h>
#include <gtkmm/gridlayoutchild.h>
#include <gtkmm/gridview.h>
#include <gtkmm/headerbar.h>
#include <gtkmm/icontheme.h>
#include <gtkmm/iconview.h>
#include <gtkmm/image.h>
#include <gtkmm/infobar.h>
#include <gtkmm/inscription.h>
#include <gtkmm/calendar.h>
#include <gtkmm/label.h>
#include <gtkmm/layoutchild.h>
#include <gtkmm/layoutmanager.h>
#include <gtkmm/levelbar.h>
#include <gtkmm/listbox.h>
#include <gtkmm/listboxrow.h>
#include <gtkmm/listheader.h>
#include <gtkmm/liststore.h>
#include <gtkmm/listview.h>
#include <gtkmm/listviewtext.h>
#include <gtkmm/linkbutton.h>
#include <gtkmm/mediacontrols.h>
#include <gtkmm/mediafile.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/multifilter.h>
#include <gtkmm/multiselection.h>
#include <gtkmm/multisorter.h>
#include <gtkmm/noselection.h>
#include <gtkmm/notebook.h>
#include <gtkmm/numericsorter.h>
#include <gtkmm/object.h>
#include <gtkmm/overlay.h>
#include <gtkmm/padcontroller.h>
#include <gtkmm/paned.h>
#include <gtkmm/pagesetup.h>
#ifndef G_OS_WIN32
# include <gtkmm/pagesetupunixdialog.h>
#endif
#include <gtkmm/papersize.h>
#include <gtkmm/passwordentry.h>
#include <gtkmm/picture.h>
#include <gtkmm/popover.h>
#include <gtkmm/popovermenu.h>
#include <gtkmm/popovermenubar.h>
#include <gtkmm/printcontext.h>
#include <gtkmm/printdialog.h>
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
#include <gtkmm/range.h>
#include <gtkmm/recentinfo.h>
#include <gtkmm/recentmanager.h>
#include <gtkmm/revealer.h>
#include <gtkmm/scale.h>
#include <gtkmm/scalebutton.h>
#include <gtkmm/scrollbar.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/searchbar.h>
#include <gtkmm/searchentry.h>
#include <gtkmm/searchentry2.h>
#include <gtkmm/separator.h>
#include <gtkmm/sectionmodel.h>
#include <gtkmm/selectionfiltermodel.h>
#include <gtkmm/selectionlistmodelimpl.h>
#include <gtkmm/settings.h>
#include <gtkmm/shortcutcontroller.h>
#include <gtkmm/shortcutlabel.h>
#include <gtkmm/shortcutsgroup.h>
#include <gtkmm/shortcutssection.h>
#include <gtkmm/shortcutsshortcut.h>
#include <gtkmm/shortcutswindow.h>
#include <gtkmm/signallistitemfactory.h>
#include <gtkmm/singleselection.h>
#include <gtkmm/sizegroup.h>
#include <gtkmm/slicelistmodel.h>
#include <gtkmm/snapshot.h>
#include <gtkmm/sortlistmodel.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/spinner.h>
#include <gtkmm/stack.h>
#include <gtkmm/stacksidebar.h>
#include <gtkmm/stackswitcher.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/stringfilter.h>
#include <gtkmm/stringlist.h>
#include <gtkmm/stringobject.h>
#include <gtkmm/stringsorter.h>
#include <gtkmm/stylecontext.h>
#include <gtkmm/switch.h>
#include <gtkmm/symbolicpaintable.h>
#include <gtkmm/text.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/textchildanchor.h>
#include <gtkmm/textiter.h>
#include <gtkmm/textmark.h>
#include <gtkmm/texttag.h>
#include <gtkmm/texttagtable.h>
#include <gtkmm/textview.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/tooltip.h>
#include <gtkmm/treeexpander.h>
#include <gtkmm/treelistmodel.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treemodelfilter.h>
#include <gtkmm/treemodelsort.h>
#include <gtkmm/treepath.h>
#include <gtkmm/treerowreference.h>
#include <gtkmm/treeselection.h>
#include <gtkmm/treestore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treeviewcolumn.h>
#include <gtkmm/urilauncher.h>
#include <gtkmm/version.h>
#include <gtkmm/video.h>
#include <gtkmm/viewport.h>
#include <gtkmm/volumebutton.h>
#include <gtkmm/widget.h>
#include <gtkmm/widgetpaintable.h>
#include <gtkmm/windowcontrols.h>
#include <gtkmm/window.h>
#include <gtkmm/windowhandle.h>

#endif /* #ifndef GTKMM_H */
