//$Id$ -*- c++ -*-

/* gtkmm example Copyright (C) 2004 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef GTKMM_CUSTOM_WIDGET_MYWIDGET_H
#define GTKMM_CUSTOM_WIDGET_MYWIDGET_H

#include <gtkmm/widget.h>

class MyWidget : public Gtk::Widget
{
public:
  MyWidget();
  virtual ~MyWidget();

protected:

  //Overrides:
  virtual void on_size_request(Gtk::Requisition* requisition);
  virtual void on_size_allocate(Gtk::Allocation& allocation);
  virtual void on_map();
  virtual void on_unmap();
  virtual void on_realize();
  virtual void on_unrealize();
  virtual bool on_expose_event(GdkEventExpose* event);

  Glib::RefPtr<Gdk::Window> m_refGdkWindow;
  Glib::RefPtr<Gdk::GC> m_refGC;

  int m_scale;
};

#endif //GTKMM_CUSTOM_WIDGET_MYWIDGET_H
