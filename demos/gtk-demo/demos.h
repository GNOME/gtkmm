#ifndef _DEMOS_H
#define _DEMOS_H

#include <sigc++/slot.h>

namespace Gtk
{
class Window;
}

using type_slotDo = sigc::slot<Gtk::Window*()>;

struct Demo
{
  const char* title;
  const char* filename;
  type_slotDo slot; //The method to call.
  Demo* children;
};

Gtk::Window* do_appwindow();
Gtk::Window* do_builder();
Gtk::Window* do_colorsel();
Gtk::Window* do_dialog();
Gtk::Window* do_drawingarea();
Gtk::Window* do_dropdown();
Gtk::Window* do_flowbox();
Gtk::Window* do_gestures();
Gtk::Window* do_glarea();
Gtk::Window* do_gridview();
Gtk::Window* do_headerbar();
Gtk::Window* do_iconbrowser();
Gtk::Window* do_images();
Gtk::Window* do_listview_applauncher();
Gtk::Window* do_listview_columnview();
Gtk::Window* do_listview_editable_cells();
Gtk::Window* do_listview_liststore();
Gtk::Window* do_listview_treelist();
Gtk::Window* do_overlay();
Gtk::Window* do_panes();
Gtk::Window* do_pixbufs();
Gtk::Window* do_shortcuts();
Gtk::Window* do_sizegroup();
Gtk::Window* do_stack();
Gtk::Window* do_stacksidebar();
Gtk::Window* do_textview();

Demo child0[] =
{
  { "Application Launcher", "example_listview_applauncher.cc", sigc::ptr_fun(&do_listview_applauncher), nullptr },
  { "Column View", "example_listview_columnview.cc", sigc::ptr_fun(&do_listview_columnview), nullptr },
  { "Editable Cells", "example_listview_editable_cells.cc", sigc::ptr_fun(&do_listview_editable_cells), nullptr },
  { "List Store", "example_listview_liststore.cc", sigc::ptr_fun(&do_listview_liststore), nullptr },
  { "Tree List", "example_listview_treelist.cc", sigc::ptr_fun(&do_listview_treelist), nullptr },
  { nullptr, nullptr, type_slotDo(), nullptr }
};

Demo testgtk_demos[] =
{
  { "Application main window", "example_appwindow.cc", sigc::ptr_fun(&do_appwindow), nullptr },
  { "Builder", "example_builder.cc", sigc::ptr_fun(&do_builder), nullptr },
  { "Color Chooser", "example_colorsel.cc", sigc::ptr_fun(&do_colorsel), nullptr },
  { "Dialog and Message Boxes", "example_dialog.cc", sigc::ptr_fun(&do_dialog), nullptr },
  { "Drawing Area", "example_drawingarea.cc", sigc::ptr_fun(&do_drawingarea), nullptr },
  { "Drop Downs", "example_dropdown.cc", sigc::ptr_fun(&do_dropdown), nullptr },
  { "Flow Box", "example_flowbox.cc",  sigc::ptr_fun(&do_flowbox), nullptr },
  { "Gestures", "example_gestures.cc",  sigc::ptr_fun(&do_gestures), nullptr },
  { "Grid View", "example_gridview.cc", sigc::ptr_fun(&do_gridview), nullptr },
  { "Header Bar", "example_headerbar.cc",  sigc::ptr_fun(&do_headerbar), nullptr },
  { "Icon Browser", "example_iconbrowser.cc", sigc::ptr_fun(&do_iconbrowser), nullptr },
  { "Images", "example_images.cc", sigc::ptr_fun(&do_images), nullptr },
  { "Lists", "", type_slotDo(), child0 },
  { "OpenGL Area", "example_glarea.cc", sigc::ptr_fun(&do_glarea), nullptr },
  { "Overlay", "example_overlay.cc", sigc::ptr_fun(&do_overlay), nullptr },
  { "Paned Widgets", "example_panes.cc", sigc::ptr_fun(&do_panes), nullptr },
  { "Pixbufs", "example_pixbufs.cc", sigc::ptr_fun(&do_pixbufs), nullptr },
  { "Shortcuts Window", "example_shortcuts.cc", sigc::ptr_fun(&do_shortcuts), nullptr },
  { "Size Groups", "example_sizegroup.cc", sigc::ptr_fun(&do_sizegroup), nullptr },
  { "Stack", "example_stack.cc", sigc::ptr_fun(&do_stack), nullptr },
  { "Stack Sidebar", "example_stacksidebar.cc", sigc::ptr_fun(&do_stacksidebar), nullptr },
  { "Text Widget", "example_textview.cc", sigc::ptr_fun(&do_textview), nullptr },
  { nullptr, nullptr, type_slotDo(), nullptr }
};

#endif //_DEMOS_H
