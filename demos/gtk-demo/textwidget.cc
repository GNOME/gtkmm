/* textwidget.cc
 *
 * Copyright (C) 2001-2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <cstring>
#include "textwidget.h"
#include "pangomm/fontdescription.h"
  
using std::strstr;
using std::strncmp;
using std::strlen;


TextWidget::TextWidget(bool is_source)
{
  set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  set_shadow_type (Gtk::SHADOW_IN);

  m_refTextBuffer = Gtk::TextBuffer::create();
  m_TextView.set_buffer(m_refTextBuffer);
  m_TextView.set_editable(false);
  m_TextView.set_cursor_visible(false);
  add(m_TextView);

  if (is_source)
  {
    m_TextView.set_wrap_mode (Gtk::WRAP_NONE);

    Glib::RefPtr<Gtk::TextBuffer::Tag> refTag = m_refTextBuffer->create_tag("source");
    refTag->property_font() = "Courier 12";

    refTag = m_refTextBuffer->create_tag("comment");
    refTag->property_foreground() = "red";

    refTag = m_refTextBuffer->create_tag("type");
    refTag->property_foreground() = "ForestGreen";

    refTag = m_refTextBuffer->create_tag("string");

    refTag->property_foreground() = "RosyBrown";
    refTag->property_weight() = Pango::WEIGHT_BOLD;


    refTag = m_refTextBuffer->create_tag("control");
    refTag->property_foreground() = "purple";

    refTag = m_refTextBuffer->create_tag("preprocessor");
    refTag->property_style() = Pango::STYLE_OBLIQUE;
    refTag->property_foreground() = "burlywood4";

    refTag = m_refTextBuffer->create_tag("function");
    refTag->property_weight() = Pango::WEIGHT_BOLD;
    refTag->property_foreground() = "DarkGoldenrod4";
  }
  else
  {
    // Make it a bit nicer for text.
    m_TextView.set_wrap_mode (Gtk::WRAP_WORD);
    m_TextView.set_pixels_above_lines(2);
    m_TextView.set_pixels_below_lines(2);

    Glib::RefPtr<Gtk::TextBuffer::Tag> refTag = m_refTextBuffer->create_tag("title");
    refTag->property_font() = "Sans 18";
  }
}


TextWidget::~TextWidget()
{
}

Glib::RefPtr<Gtk::TextBuffer> TextWidget::get_buffer()
{
   return m_refTextBuffer;
}

void TextWidget::wipe()
{
  Gtk::TextBuffer::iterator start, end;
  m_refTextBuffer->get_bounds(start, end);
  m_refTextBuffer->erase(start, end);
}


/* Stupid syntax highlighting.
 *
 * No regex was used in the making of this highlighting.
 * It should only work for simple cases.  This is good, as
 * that's all we should have in the demos.
 */
/* This code should not be used elsewhere, except perhaps as an example of how
 * to iterate through a text buffer.
 */
enum enumStates
{
  STATE_NORMAL,
  STATE_IN_COMMENT
};

static const char* tokens[] =
{
  "/*",
  "\"",
  NULL
};

static const char* types[] =
{
  "static",
  "const ",
  "void",
  "gint",
  "int ",
  "char ",
  "gchar ",
  "gfloat",
  "float",
  "gint8",
  "gint16",
  "gint32",
  "guint",
  "guint8",
  "guint16",
  "guint32",
  "guchar",
  "glong",
  "gboolean" ,
  "gshort",
  "gushort",
  "gulong",
  "gdouble",
  "gldouble",
  "gpointer",
  "NULL",
  "GList",
  "GSList",
  "FALSE",
  "TRUE",
  "FILE ",
  "GtkObject ",
  "GtkColorSelection ",
  "GtkWidget ",
  "GtkButton ",
  "GdkColor ",
  "GdkRectangle ",
  "GdkEventExpose ",
  "GdkGC ",
  "GdkPixbufLoader ",
  "GdkPixbuf ",
  "GError",
  "size_t",
  0
};

static const char* control[] =
{
  " if ",
  " while ",
  " else",
  " do ",
  " for ",
  "?",
  ":",
  "return ",
  "goto ",
  0
};

typedef const char* constpch;

void
parse_chars (constpch text,
       constpch* end_ptr,
       enumStates* state,
       constpch* tag,
       bool   start)
{
  int i = 0;
  const char* next_token = 0;

  /* Handle comments first */
  if(*state == STATE_IN_COMMENT)
  {
    *end_ptr = strstr (text, "*/");
    if (*end_ptr)
    {
      *end_ptr += 2;
      *state = STATE_NORMAL;
      *tag = "comment";
    }
    
    return;
  }

  *tag = 0;
  *end_ptr = 0;

  /* check for comment */
  if (!strncmp (text, "/*", 2))
  {
    *end_ptr = strstr (text, "*/");

    if (*end_ptr)
      *end_ptr += 2;
    else
      *state = STATE_IN_COMMENT;
    *tag = "comment";

    return;
  }

  /* check for preprocessor defines */
  if (*text == '#' && start)
  {
    *end_ptr = 0;
    *tag = "preprocessor";
    return;
  }

  /* functions */
  if (start && * text != '\t' && *text != ' ' && *text != '{' && *text != '}')
  {
    if (strstr (text, "("))
    {
      *end_ptr = strstr (text, "(");
      *tag = "function";
      return;
    }
  }
  
  /* check for types */
  for (i = 0; types[i] != 0; i++)
    if (!strncmp (text, types[i], strlen (types[i])))
    {
      *end_ptr = text + strlen (types[i]);
      *tag = "type";
      return;
    }

  /* check for control */
  for (i = 0; control[i] != 0; i++)
    if (!strncmp (text, control[i], strlen (control[i])))
    {
      *end_ptr = text + strlen (control[i]);
      *tag = "control";
      return;
    }

  /* check for string */
  if (text[0] == '"')
  {
    int maybe_escape = false;

    *end_ptr = text + 1;
    *tag = "string";
      
    while (**end_ptr != '\000')
    {
      if (**end_ptr == '\"' && !maybe_escape)
      {
        *end_ptr += 1;
        return;
      }
      
      if (**end_ptr == '\\')
        maybe_escape = true;
      else
        maybe_escape = false;
      *end_ptr += 1;
    }
    return;
  }

  /* not at the start of a tag.  Find the next one. */
  for (i = 0; tokens[i] != 0; i++)
  {
    next_token = strstr (text, tokens[i]);
    if (next_token)
    {
      if (*end_ptr)
        *end_ptr = (*end_ptr<next_token)?*end_ptr:next_token;
      else
        *end_ptr = next_token;
    }
  }

  for (i = 0; types[i] != 0; i++)
  {
    next_token = strstr (text, types[i]);
    if (next_token)
    {
      if (*end_ptr)
        *end_ptr = (*end_ptr<next_token)?*end_ptr:next_token;
      else
        *end_ptr = next_token;
    }
  }

  for (i = 0; control[i] != 0; i++)
  {
    next_token = strstr (text, control[i]);
    if (next_token)
    {
      if (*end_ptr)
        *end_ptr = (*end_ptr<next_token)?*end_ptr:next_token;
      else
        *end_ptr = next_token;
    }
  }

}


/* While not as cool as c-mode, this will do as a quick attempt at highlighting */
void TextWidget::fontify()
{
  enumStates state = STATE_NORMAL;

  Gtk::TextBuffer::iterator iterStart;
  Gtk::TextBuffer::iterator iterEnd;
  m_refTextBuffer->get_bounds(iterStart, iterEnd);
  m_refTextBuffer->apply_tag_by_name("source", iterStart, iterEnd);

  iterStart = m_refTextBuffer->get_iter_at_offset(0);

  Gtk::TextBuffer::iterator iterNext = iterStart;
  while(iterNext.forward_line())
  {
    bool start = true;
    const Glib::ustring& str = iterStart.get_text(iterNext);
    const gchar* start_ptr = str.c_str();

    const gchar* end_ptr = 0;
    const gchar* tag = 0;

    do
    {
      parse_chars (start_ptr, &end_ptr, &state, &tag, start);

      start = false;
      Gtk::TextBuffer::iterator iterTmp;
      if(end_ptr)
      {
        iterTmp = iterStart;
        iterTmp.forward_chars(end_ptr - start_ptr);
      }
      else
      {
        iterTmp = iterNext;
      }

      if(tag)
        m_refTextBuffer->apply_tag_by_name(tag, iterStart, iterTmp);

      iterStart = iterTmp;
      start_ptr = end_ptr;
    }
    while(end_ptr);

    iterStart = iterNext;
  }
}
