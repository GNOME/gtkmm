#ifndef _DEMOS_H
#define _DEMOS_H

#include "demowindow.h"

//typedef	Gtk::Window* (*GDoDemoFunc) (void);

typedef sigc::slot<Gtk::Window*> type_slotDo;

struct Demo
{
  const char* title;
  const char* filename;
  //GDoDemoFunc func;
  type_slotDo slot; //The method to call.
  Demo* children;
};


Gtk::Window* do_appwindow();
Gtk::Window* do_buttonbox();
Gtk::Window* do_change_display();
Gtk::Window* do_colorsel();
Gtk::Window* do_dialog();
Gtk::Window* do_drawingarea();
Gtk::Window* do_flowbox();
Gtk::Window* do_headerbar();
Gtk::Window* do_icontheme();
Gtk::Window* do_iconview();
Gtk::Window* do_images();
Gtk::Window* do_menus();
Gtk::Window* do_pixbufs();
Gtk::Window* do_panes();
Gtk::Window* do_sizegroup();
//Gtk::Window* do_stock_browser();
Gtk::Window* do_textview();

Gtk::Window* do_treeview_editable_cells();
Gtk::Window* do_treeview_liststore();
Gtk::Window* do_treeview_treestore();

//Gtk::Window* do_ui_manager();

Demo child0[] = {
  { "Editable Cells", "example_treeview_editable_cells.cc", sigc::ptr_fun(&do_treeview_editable_cells), 0 },
  { "List Store", "example_treeview_liststore.cc", sigc::ptr_fun(&do_treeview_liststore), 0 },
  { "Tree Store", "example_treeview_treestore.cc", sigc::ptr_fun(&do_treeview_treestore), 0 },
  { 0, 0, type_slotDo(), 0 }
};


Demo testgtk_demos[] =
{
  { "Application main window", "example_appwindow.cc", sigc::ptr_fun(&do_appwindow), 0 },
  { "Button Boxes", "example_buttonbox.cc",  sigc::ptr_fun(&do_buttonbox), 0 },
  { "Change Display", "example_change_display.cc", sigc::ptr_fun(&do_change_display), 0 },
  { "Color Selector", "example_colorsel.cc", sigc::ptr_fun(&do_colorsel), 0 },
  { "Dialog and Message Boxes", "example_dialog.cc", sigc::ptr_fun(&do_dialog), 0 },
  { "Drawing Area", "example_drawingarea.cc", sigc::ptr_fun(&do_drawingarea), 0 },
  { "Flow Box", "example_flowbox.cc",  sigc::ptr_fun(&do_flowbox), 0 },
  { "Header Bar", "example_headerbar.cc",  sigc::ptr_fun(&do_headerbar), 0 },
  { "Icon Theme", "example_icontheme.cc", sigc::ptr_fun(&do_icontheme), 0 },  
  { "Icon View", "example_iconview.cc", sigc::ptr_fun(&do_iconview), 0 },  
  { "Images", "example_images.cc", sigc::ptr_fun(&do_images), 0 },
  { "Menus", "example_menus.cc", sigc::ptr_fun(&do_menus), 0 },
  { "Paned Widgets", "example_panes.cc", sigc::ptr_fun(&do_panes), 0 },
  { "Pixbufs", "example_pixbufs.cc", sigc::ptr_fun(&do_pixbufs), 0 },
  { "Size Groups", "example_sizegroup.cc", sigc::ptr_fun(&do_sizegroup), 0 },
//  { "Stock Item and Icon Browser", "example_stockbrowser.cc", sigc::ptr_fun(&do_stock_browser), 0 },
  { "Text Widget", "example_textview.cc", sigc::ptr_fun(&do_textview), 0 },
  { "Tree View", "", type_slotDo(), child0 },
//  { "UI Manager", "example_uimanager.cc", sigc::ptr_fun(&do_ui_manager), 0},
  { 0, 0, type_slotDo(), 0 }
};

#endif //_DEMOS_H

