#ifndef _DEMOS_H
#define _DEMOS_H

#include "demowindow.h"

//typedef	Gtk::Window* (*GDoDemoFunc) (void);

typedef SigC::Slot0<Gtk::Window*> type_slotDo;

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
Gtk::Window* do_images();
//Gtk::Window* do_item_factory();
Gtk::Window* do_menus();
Gtk::Window* do_pixbufs();
Gtk::Window* do_panes();
Gtk::Window* do_sizegroup();
Gtk::Window* do_stock_browser();
Gtk::Window* do_textview();

Gtk::Window* do_treeview_editable_cells();
Gtk::Window* do_treeview_liststore();
Gtk::Window* do_treeview_treestore();

Demo child0[] = {
  { "Editable Cells", "example_treeview_editable_cells.cc", SigC::slot(&do_treeview_editable_cells), 0 },
  { "List Store", "example_treeview_liststore.cc", do_treeview_liststore, 0 },
  { "Tree Store", "example_treeview_treestore.cc", do_treeview_treestore, 0 },
  { 0, 0, type_slotDo(), 0 }
};


Demo testgtk_demos[] =
{
  { "Application main window", "example_appwindow.cc", SigC::slot(&do_appwindow), 0 },
  { "Button Boxes", "example_buttonbox.cc",  SigC::slot(&do_buttonbox), 0 },
  { "Change Display", "example_change_display.cc", SigC::slot(&do_change_display), 0 },
  { "Color Selector", "example_colorsel.cc", SigC::slot(&do_colorsel), 0 },
  { "Dialog and Message Boxes", "example_dialog.cc", SigC::slot(&do_dialog), 0 },
  { "Drawing Area", "example_drawingarea.cc", SigC::slot(&do_drawingarea), 0 },
  { "Images", "example_images.cc", SigC::slot(&do_images), 0 },
/*
  { "Item Factory", "example_item_factory.cc", SigC::slot(&do_item_factory), 0 },
*/
  { "Menus", "example_menus.cc", SigC::slot(&do_menus), 0 },
  { "Paned Widgets", "example_panes.cc", SigC::slot(&do_panes), 0 },
  { "Pixbufs", "example_pixbufs.cc", SigC::slot(&do_pixbufs), 0 },
  { "Size Groups", "example_sizegroup.cc", SigC::slot(&do_sizegroup), 0 },
  { "Stock Item and Icon Browser", "example_stockbrowser.cc", SigC::slot(&do_stock_browser), 0 },
  { "Text Widget", "example_textview.cc", SigC::slot(&do_textview), 0 },
  { "Tree View", "", type_slotDo(), child0 },
  { 0, 0, type_slotDo(), 0 }
};

#endif //_DEMOS_H

