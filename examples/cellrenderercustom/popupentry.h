//$Id$ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
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
 
#include <gtkmm/button.h>
#include <gtkmm/celleditable.h>
#include <gtkmm/editable.h>
#include <gtkmm/entry.h>
#include <gtkmm/eventbox.h>


class PopupEntry : public Gtk::EventBox, public Gtk::CellEditable
{
public:
  explicit PopupEntry(const Glib::ustring& path);
  virtual ~PopupEntry();

  Glib::ustring get_path() const;

  void set_text(const Glib::ustring& text);
  Glib::ustring get_text() const;

  void select_region(int start_pos, int end_pos);

  bool get_editing_canceled() const;

  static int get_button_width();

  typedef sigc::signal<void> type_signal_arrow_clicked;
  type_signal_arrow_clicked& signal_arrow_clicked();

protected:
  virtual bool on_key_press_event(GdkEventKey* event);
  virtual void start_editing_vfunc(GdkEvent* event);

private:
  typedef PopupEntry Self;

  void on_entry_activate();
  bool on_entry_key_press_event(GdkEventKey* event);
  void on_button_clicked();

  Glib::ustring path_;
  Gtk::Button*  button_;
  Gtk::Entry*   entry_;
  bool          editing_canceled_;

  type_signal_arrow_clicked signal_arrow_clicked_;
};

