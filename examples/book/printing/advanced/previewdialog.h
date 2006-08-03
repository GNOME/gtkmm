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

#ifndef GTKMM_PREVIEW_WINDOW_H
#define GTKMM_PREVIEW_WINDOW_H

#include <gtkmm.h>

class PrintFormOperation;

class PreviewDialog : public Gtk::Window
{
 public:
  explicit PreviewDialog(
                  PrintFormOperation* pfo,
                  const Glib::RefPtr<Gtk::PrintOperationPreview>& preview,
                  int page_count,
                  const Glib::RefPtr<Gtk::PrintContext>& context,
                  Gtk::Window& parent);
  ~PreviewDialog();

 protected:

  virtual void on_drawing_area_realized(const Glib::RefPtr<Gtk::PrintContext>& context);

  virtual void on_page_number_changed();
  virtual void on_close_clicked();
  virtual void on_hide();

  virtual bool on_drawing_area_expose_event(GdkEventExpose* event);

  //PrintOperationPreview signal handlers:
  virtual void on_popreview_ready(const Glib::RefPtr<Gtk::PrintContext>& print_ctx);
  virtual void on_popreview_got_page_size(const Glib::RefPtr<Gtk::PrintContext>& context, const Glib::RefPtr<Gtk::PageSetup>& page_setup);

  PrintFormOperation* m_pOperation;

  Glib::RefPtr<Gtk::PrintOperationPreview> m_refPreview;
  Glib::RefPtr<Pango::Layout> m_refLayout;

  Gtk::VBox m_VBox;
  Gtk::HBox m_HBox;
  Gtk::SpinButton m_PageSpin;
  Gtk::Button m_CloseButton;
  Gtk::DrawingArea m_DrawingArea;

  int m_Page;
  int m_PageCount;
  double m_DpiX, m_DpiY;
};

#endif // GTKMM_PREVIEW_WINDOW_H
