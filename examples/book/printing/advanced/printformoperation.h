/* gtkmm example Copyright (C) 2006 gtkmm development team
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

#ifndef GTKMM_PRINT_FORM_OPERATION_H
#define GTKMM_PRINT_FORM_OPERATION_H

#include <pangomm.h>
#include <gtkmm.h>
#include <vector>

class PreviewDialog;

//We derive our own class from PrintOperation,
//so we can put the actual print implementation here.
class PrintFormOperation : public Gtk::PrintOperation
{
 public:
  static Glib::RefPtr<PrintFormOperation> create();
  virtual ~PrintFormOperation();

  Glib::RefPtr<Pango::Layout> get_pango_layout() { return m_refLayout; }

  void set_name(const Glib::ustring& name) { m_Name = name; }
  void set_comments(const Glib::ustring& comments) { m_Comments = comments; }

  //TODO: Use an accessor method for this, with a typedef:
  //sigc::signal< void, const Glib::RefPtr<Gtk::PrintSettings>& > signal_preview_done;

 protected:
  PrintFormOperation();

  //PrintOperation default signal handler overrides:
  virtual void on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& context);
  virtual void on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& context, int page_nr);

  //virtual Gtk::Widget* on_create_custom_widget();
  //virtual void on_custom_widget_apply(Gtk::Widget* widget);


  virtual bool on_preview(const Glib::RefPtr<Gtk::PrintOperationPreview>& preview,
                  const Glib::RefPtr<Gtk::PrintContext>& context,
                  Gtk::Window* parent);

  virtual bool on_preview_window_delete_event(GdkEventAny*);

  PreviewDialog* m_pDialog;

  Glib::ustring m_Name;
  Glib::ustring m_Comments;
  Glib::RefPtr<Pango::Layout> m_refLayout;
  std::vector<int> m_PageBreaks; // line numbers where a page break occurs
  Gtk::FontButton m_FontButton; // displayed in a custom print dialog tab
};

#endif // GTKMM_PRINT_FORM_OPERATION_H
