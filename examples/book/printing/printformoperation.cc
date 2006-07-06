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
#include "printformoperation.h"

using std::vector;

PrintFormOperation::PrintFormOperation()
{
  g_debug("pfo ctor");
}

PrintFormOperation::~PrintFormOperation()
{
  g_debug("pfo dtor");
}

Glib::RefPtr<PrintFormOperation> PrintFormOperation::create()
{
  return Glib::RefPtr<PrintFormOperation>(new PrintFormOperation());
}

void PrintFormOperation::on_begin_print(const Glib::RefPtr<Gtk::PrintContext>&
                                        print_ctx)
{
  //Create and set up Pango layout for PrintData based on passed PrintContext:
  m_refLayout = print_ctx->create_pango_layout();

  Pango::FontDescription font_desc(m_Font);
  m_refLayout->set_font_description(font_desc);

  double width = print_ctx->get_width();
  double height = print_ctx->get_height();

  m_refLayout->set_width(static_cast<int>(width * Pango::SCALE));

  //Set and mark up the text to print:
  Glib::ustring marked_up_form_text;
  marked_up_form_text += "<b>Name</b>: " + m_Name + "\n\n";
  marked_up_form_text += "<b>Comments</b>: " + m_Comments;

  m_refLayout->set_markup(marked_up_form_text);

  //Set the number of pages to print by determining the line numbers
  //where page breaks occur:
  int line_count = m_refLayout->get_line_count();

  Glib::RefPtr<Pango::LayoutLine> layout_line;
  double page_height = 0;

  for (int line = 0; line < line_count; ++line)
  {
    Pango::Rectangle ink_rect, logical_rect;

    layout_line = m_refLayout->get_line(line);
    layout_line->get_extents(ink_rect, logical_rect);

    double line_height = logical_rect.get_height() / 1024.0;

    if (page_height + line_height > height)
    {
      m_PageBreaks.push_back(line);
      page_height = 0;
    }

    page_height += line_height;
  }

  set_n_pages(m_PageBreaks.size() + 1);
}

void PrintFormOperation::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>&
                                      print_ctx,
                                      int page_nr)
{
  //See which lines we need to print:
  int start_page_line, end_page_line;

  if (page_nr == 0)
  {
    start_page_line = 0;
  }
  else
  {
    start_page_line = m_PageBreaks[page_nr - 1];
  }

  if (page_nr < static_cast<int>(m_PageBreaks.size()))
  {
    end_page_line = m_PageBreaks[page_nr];
  }
  else
  {
    end_page_line = m_refLayout->get_line_count();
  }

  //Get a Cairo Context, which is used as a drawing board:
  Cairo::RefPtr<Cairo::Context> cairo_ctx = print_ctx->get_cairo_context();

  //We'll use black letters:
  cairo_ctx->set_source_rgb(0, 0, 0);

  //Render Pango LayoutLines over the Cairo context:
  Pango::LayoutIter iter;
  m_refLayout->get_iter(iter);

  double start_pos = 0;
  int line_index = 0;
  
  do 
  {
    if (line_index >= start_page_line)
    {
      Glib::RefPtr<Pango::LayoutLine> layout_line = iter.get_line();
      Pango::Rectangle logical_rect = iter.get_line_logical_extents();
      int baseline = iter.get_baseline();

      if (line_index == start_page_line)
      {
	start_pos = logical_rect.get_y() / 1024.0;
      }

      cairo_ctx->move_to(logical_rect.get_x() / 1024.0,
                         baseline / 1024.0 - start_pos);

      //TODO: change this when it's wrapped
      pango_cairo_show_layout_line(cairo_ctx->cobj(), layout_line->gobj());
    }

    line_index++;
  }
  while (line_index < end_page_line && iter.next_line());
}

Gtk::Widget* PrintFormOperation::on_create_custom_widget()
{
  //Create a custom tab in the print dialog titled "Other"
  set_custom_tab_label("Other");

  Gtk::VBox* vbox = new Gtk::VBox();
  vbox->set_border_width(12);

  Gtk::HBox* hbox = Gtk::manage(new Gtk::HBox(false, 8));
  vbox->pack_start(*hbox, false, false);
  hbox->set_border_width(6);
  hbox->show();

  Gtk::Label* label = Gtk::manage(new Gtk::Label("Choose a font: "));
  hbox->pack_start(*label, false, false);
  label->show();

  m_FontButton.set_font_name(m_Font);
  hbox->pack_start(m_FontButton, false, false);
  m_FontButton.show();

  return vbox;
}

void PrintFormOperation::on_custom_widget_apply(Gtk::Widget& widget)
{
  widget.get_name(); // suppress -Werror
  //Note: the returned widget is the VBox
  //we created in on_create_custom_widget() - here we don't need to use it.
  Glib::ustring selected_font = m_FontButton.get_font_name();
  m_Font = selected_font;
}

bool PrintFormOperation::on_preview(
                       const Glib::RefPtr<Gtk::PrintOperationPreview>& preview,
                       const Glib::RefPtr<Gtk::PrintContext>& context,
                       Gtk::Window* parent)
{
  g_debug("pfo::on_preview");

  PreviewDialog pd(preview,
                   property_n_pages().get_value(),
                   context,
                   m_refLayout,
                   *parent);
  pd.run();

  g_debug("emitting preview_done");
  Glib::RefPtr<Gtk::PrintSettings> settings = get_print_settings();
  signal_preview_done.emit(settings);

  return true;
}
