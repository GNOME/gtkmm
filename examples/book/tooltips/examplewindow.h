/* -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

/* gtkmm example Copyright (C) 2007 gtkmm development team
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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:

  ExampleWindow();
  virtual ~ExampleWindow();

protected:

  //Methods:
  void prepare_textview();
  void connect_signals();

  //Signal handlers:
  virtual void on_markup_checkbutton_click();
  virtual bool on_textview_query_tooltip(int x, int y, bool keyboard_tooltip, const Glib::RefPtr<Gtk::Tooltip>& tooltip);
  virtual bool on_button_query_tooltip(int x, int y, bool keyboard_tooltip, const Glib::RefPtr<Gtk::Tooltip>& tooltip);

  //Child widgets:
  Gtk::VBox m_vbox;

  Gtk::CheckButton m_checkbutton;
  Gtk::Label m_label;

  Gtk::ScrolledWindow m_scrolled_window;
  Gtk::TextView m_text_view;
  Glib::RefPtr<Gtk::TextBuffer> m_ref_text_buffer;
  Glib::RefPtr<Gtk::TextTag> m_ref_bold_tag;

  Gtk::Button m_button;
  Gtk::Window m_button_tooltip_window;

};

#endif // GTKMM_EXAMPLEWINDOW_H

