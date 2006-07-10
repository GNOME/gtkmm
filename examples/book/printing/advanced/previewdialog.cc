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

#include "previewdialog.h"

#include <gtkmm/stock.h>
#include <math.h>

PreviewDialog::PreviewDialog(
               const Glib::RefPtr<Gtk::PrintOperationPreview>& preview,
               int page_count,
               const Glib::RefPtr<Gtk::PrintContext>& print_ctx,
               const Glib::RefPtr<Pango::Layout>& layout,
               Gtk::Window& parent)
  :
  m_refPreview(preview),
  m_refLayout(layout),
  m_PageSpin(1, 0),
  m_CloseButton(Gtk::Stock::CLOSE),
  m_Page(1),
  m_PageCount(page_count)
{
  g_debug("parent title: %s", parent.get_title().c_str());
  set_transient_for(parent);
  set_title("Preview");
  set_border_width(2);

  Gtk::VBox* vbox = get_vbox();

  vbox->pack_start(m_HBox);
  m_HBox.pack_start(m_PageSpin);
  m_HBox.pack_start(m_CloseButton);

  m_DrawingArea.set_size_request(200, 300);
  vbox->pack_start(m_DrawingArea);
  m_DrawingArea.set_double_buffered(false);

  m_DrawingArea.signal_realize().connect(
    sigc::bind(sigc::mem_fun(*this, &PreviewDialog::on_drawing_area_realized),
	       print_ctx));

  m_CloseButton.signal_clicked().connect(
    sigc::mem_fun(*this, &PreviewDialog::on_close_clicked));

  show_all_children();
}

PreviewDialog::~PreviewDialog()
{
  g_debug("pw dtor");
}

void PreviewDialog::on_drawing_area_realized(
                       const Glib::RefPtr<Gtk::PrintContext>& print_ctx)
{
  Glib::RefPtr<Gdk::Window> gdk_window = m_DrawingArea.get_window();
  Cairo::RefPtr<Cairo::Context> cairo_ctx = gdk_window->create_cairo_context();

  print_ctx->set_cairo_context(cairo_ctx, 72, 72);

  m_PageSpin.signal_value_changed().connect(
    sigc::mem_fun(*this, &PreviewDialog::on_page_number_changed));
}

void PreviewDialog::on_page_number_changed()
{
  m_Page = m_PageSpin.get_value_as_int();
  m_DrawingArea.queue_draw();
}

bool PreviewDialog::on_expose_event(GdkEventExpose* /* event */)
{
  Glib::RefPtr<Gdk::Window> window = m_DrawingArea.get_window();
  if(window)
    window->clear();

  if(m_refPreview)
    m_refPreview->render_page(m_Page - 1);

  return true;
}

void PreviewDialog::on_ready(const Glib::RefPtr<Gtk::PrintContext>& print_ctx)
{
  if (print_ctx) ; //Werror

  m_PageSpin.set_range(1.0, m_PageCount);

  m_DrawingArea.signal_expose_event().connect(
    sigc::mem_fun(*this, &PreviewDialog::on_expose_event));

  m_DrawingArea.queue_draw();
}

void PreviewDialog::on_got_page_size(
                       const Glib::RefPtr<Gtk::PrintContext>& print_ctx,
                       const Glib::RefPtr<Gtk::PageSetup>& page_setup)
{
  Gtk::PaperSize paper_size = page_setup->get_paper_size();

  double width = paper_size.get_width(Gtk::UNIT_INCH);
  double height = paper_size.get_height(Gtk::UNIT_INCH);

  Cairo::RefPtr<Cairo::Context> cairo_ctx =
    m_DrawingArea.get_window()->create_cairo_context();

  double dpi_x = m_DrawingArea.get_allocation().get_width() / width;
  double dpi_y = m_DrawingArea.get_allocation().get_height() / height;

  if (fabs(dpi_x - m_DpiX) > 0.001 ||
      fabs(dpi_y - m_DpiY) > 0.001)
  {
    print_ctx->set_cairo_context(cairo_ctx, dpi_x, dpi_y);
    m_DpiX = dpi_x;
    m_DpiY = dpi_y;
  }

  pango_cairo_update_layout(cairo_ctx->cobj(), m_refLayout->gobj());
}

void PreviewDialog::on_close_clicked()
{
  m_refPreview->end_preview();
  hide();
}
