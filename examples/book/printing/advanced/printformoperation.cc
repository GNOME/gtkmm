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
#include <iostream>

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

void PrintFormOperation::on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& print_context)
{
  g_debug("PrintFormOperation::on_begin_print");

  //Create and set up a Pango layout for PrintData based on the passed PrintContext:
  //We then use this to calculate the number of pages needed,
  //and the lines that are on each page.
  m_refLayout = print_context->create_pango_layout();

  Pango::FontDescription font_desc("sans 12");
  m_refLayout->set_font_description(font_desc);

  const double width = print_context->get_width();
  const double height = print_context->get_height();

  m_refLayout->set_width(static_cast<int>(width * Pango::SCALE));

  //Set and mark up the text to print:
  Glib::ustring marked_up_form_text;
  marked_up_form_text += "<b>Name</b>: " + m_Name + "\n\n";
  marked_up_form_text += "<b>Comments</b>: " + m_Comments;

  m_refLayout->set_markup(marked_up_form_text);

  //Set the number of pages to print by determining the line numbers
  //where page breaks occur:
  const int line_count = m_refLayout->get_line_count();

  Glib::RefPtr<Pango::LayoutLine> layout_line;
  double page_height = 0;

  for (int line = 0; line < line_count; ++line)
  {
    Pango::Rectangle ink_rect, logical_rect;

    layout_line = m_refLayout->get_line(line);
    layout_line->get_extents(ink_rect, logical_rect);

    const double line_height = logical_rect.get_height() / 1024.0;

    if (page_height + line_height > height)
    {
      m_PageBreaks.push_back(line);
      page_height = 0;
    }

    page_height += line_height;
  }

  set_n_pages(m_PageBreaks.size() + 1);
}

void PrintFormOperation::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& print_context, int page_nr)
{
  //Decide which lines we need to print in order to print the specified page:
  int start_page_line = 0;
  int end_page_line = 0;

  if(page_nr == 0)
  {
    start_page_line = 0;
  }
  else
  {
    start_page_line = m_PageBreaks[page_nr - 1];
  }

  if(page_nr < static_cast<int>(m_PageBreaks.size()))
  {
    end_page_line = m_PageBreaks[page_nr];
  }
  else
  {
    end_page_line = m_refLayout->get_line_count();
  }

  //Get a Cairo Context, which is used as a drawing board:
  Cairo::RefPtr<Cairo::Context> cairo_ctx = print_context->get_cairo_context();

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

      cairo_ctx->move_to(logical_rect.get_x() / 1024.0, baseline / 1024.0 - start_pos);

      layout_line->show_in_cairo_context(cairo_ctx);
    }

    line_index++;
  }
  while (line_index < end_page_line && iter.next_line());
}

/*
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

  //m_FontButton.set_font_name(m_Font);
  //hbox->pack_start(m_FontButton, false, false);
  //m_FontButton.show();

  return vbox;
}
*/

/*
void PrintFormOperation::on_custom_widget_apply(Gtk::Widget*)
{
  //Note: the returned widget is the VBox we created in on_create_custom_widget().
  //We don't need to use it, because we can use the child FontButton directly:

  Glib::ustring selected_font = m_FontButton.get_font_name();
  m_Font = selected_font;
}
*/

bool PrintFormOperation::on_preview(
                       const Glib::RefPtr<Gtk::PrintOperationPreview>& preview,
                       const Glib::RefPtr<Gtk::PrintContext>& context,
                       Gtk::Window* parent)
{
  if(!parent)
  {
    std::cerr << "PrintFormOperation::on_preview(): parent was null." << std::endl;
    return false;
  }

  //Use our custom preview dialog:
  m_pDialog = new PreviewDialog(this, preview, property_n_pages(), context, *parent);
  m_pDialog->signal_delete_event().connect(
    sigc::mem_fun(*this, &PrintFormOperation::on_preview_window_delete_event));

  return true;
}

bool
PrintFormOperation::on_preview_window_delete_event(GdkEventAny*)
{
  //Pass the main window the most recent settings user applied.
  //TODO: Why do we need to do this?
  //Glib::RefPtr<Gtk::PrintSettings> settings = get_print_settings();
  //signal_preview_done.emit(settings);

  m_pDialog->hide();
  delete m_pDialog;

  return true;
}
