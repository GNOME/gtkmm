#ifndef _DEMOS_H
#define _DEMOS_H

#include "demowindow.h"

typedef sigc::slot<Gtk::Window*> type_slotDo;

struct Demo
{
  const char* title;
  const char* filename;
  type_slotDo slot; //The method to call.
  Demo* children;
};


Gtk::Window* do_appwindow();
Gtk::Window* do_builder();
Gtk::Window* do_buttonbox();
Gtk::Window* do_change_display();
Gtk::Window* do_colorsel();
Gtk::Window* do_dialog();
Gtk::Window* do_drawingarea();
Gtk::Window* do_flowbox();
Gtk::Window* do_gestures();
Gtk::Window* do_glarea();
Gtk::Window* do_headerbar();
Gtk::Window* do_iconbrowser();
Gtk::Window* do_iconview();
Gtk::Window* do_images();
Gtk::Window* do_menus();
Gtk::Window* do_overlay();
Gtk::Window* do_panes();
Gtk::Window* do_pixbufs();
Gtk::Window* do_shortcuts();
Gtk::Window* do_sizegroup();
Gtk::Window* do_stack();
Gtk::Window* do_stacksidebar();
Gtk::Window* do_textview();

Gtk::Window* do_treeview_editable_cells();
Gtk::Window* do_treeview_liststore();
Gtk::Window* do_treeview_treestore();

Demo child0[] =
{
  { "Editable Cells", "example_treeview_editable_cells.cc", sigc::ptr_fun(&do_treeview_editable_cells), nullptr },
  { "List Store", "example_treeview_liststore.cc", sigc::ptr_fun(&do_treeview_liststore), nullptr },
  { "Tree Store", "example_treeview_treestore.cc", sigc::ptr_fun(&do_treeview_treestore), nullptr },
  { nullptr, nullptr, type_slotDo(), nullptr }
};

Demo testgtk_demos[] =
{
  { "Application main window", "example_appwindow.cc", sigc::ptr_fun(&do_appwindow), nullptr },
  { "Builder", "example_builder.cc", sigc::ptr_fun(&do_builder), nullptr },
  { "Button Boxes", "example_buttonbox.cc",  sigc::ptr_fun(&do_buttonbox), nullptr },
  { "Change Display", "example_change_display.cc", sigc::ptr_fun(&do_change_display), nullptr },
  { "Color Selector", "example_colorsel.cc", sigc::ptr_fun(&do_colorsel), nullptr },
  { "Dialog and Message Boxes", "example_dialog.cc", sigc::ptr_fun(&do_dialog), nullptr },
  { "Drawing Area", "example_drawingarea.cc", sigc::ptr_fun(&do_drawingarea), nullptr },
  { "Flow Box", "example_flowbox.cc",  sigc::ptr_fun(&do_flowbox), nullptr },
  { "Gestures", "example_gestures.cc",  sigc::ptr_fun(&do_gestures), nullptr },
  { "Header Bar", "example_headerbar.cc",  sigc::ptr_fun(&do_headerbar), nullptr },
  { "Icon Browser", "example_iconbrowser.cc", sigc::ptr_fun(&do_iconbrowser), nullptr },
  { "Icon View", "example_iconview.cc", sigc::ptr_fun(&do_iconview), nullptr },
  { "Images", "example_images.cc", sigc::ptr_fun(&do_images), nullptr },
  { "Menus", "example_menus.cc", sigc::ptr_fun(&do_menus), nullptr },
  { "OpenGL Area", "example_glarea.cc", sigc::ptr_fun(&do_glarea), nullptr },
  { "Overlay", "example_overlay.cc", sigc::ptr_fun(&do_overlay), nullptr },
  { "Paned Widgets", "example_panes.cc", sigc::ptr_fun(&do_panes), nullptr },
  { "Pixbufs", "example_pixbufs.cc", sigc::ptr_fun(&do_pixbufs), nullptr },
  { "Shortcuts Window", "example_shortcuts.cc", sigc::ptr_fun(&do_shortcuts), nullptr },
  { "Size Groups", "example_sizegroup.cc", sigc::ptr_fun(&do_sizegroup), nullptr },
  { "Stack", "example_stack.cc", sigc::ptr_fun(&do_stack), nullptr },
  { "Stack Sidebar", "example_stacksidebar.cc", sigc::ptr_fun(&do_stacksidebar), nullptr },
  { "Text Widget", "example_textview.cc", sigc::ptr_fun(&do_textview), nullptr },
  { "Tree View", "", type_slotDo(), child0 },
  { nullptr, nullptr, type_slotDo(), nullptr }
};

#endif //_DEMOS_H
