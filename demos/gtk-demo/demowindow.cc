/* $Id$ */

/* Copyright (C) 2001 The gtkmm Development Team
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gtkmm/main.h>
#include <gtkmm/cellrenderertext.h>
#include <gtkmm/treeviewcolumn.h>
#include <gtkmm/box.h>
#include <glibmm/convert.h>
#include <glibmm/fileutils.h>
#include "demowindow.h"
#include "textwidget.h"
#include "demos.h"
#include <vector>
#include <cctype>
#include <cerrno>
#include <stdio.h>

#include <cstring>

using std::isspace;
using std::strlen;

#include "demo-common.h"

#ifdef NEED_FLOCKFILE_PROTO
extern "C" void flockfile (FILE *);
#endif
#ifdef NEED_FUNLOCKFILE_PROTO
extern "C" void funlockfile (FILE *);
#endif
#ifdef NEED_GETC_UNLOCKED_PROTO
extern "C" int getc_unlocked (FILE *);
#endif

namespace
{

struct DemoColumns : public Gtk::TreeModelColumnRecord
{
  Gtk::TreeModelColumn<Glib::ustring> title;
  Gtk::TreeModelColumn<Glib::ustring> filename;
  Gtk::TreeModelColumn<type_slotDo>   slot;
  Gtk::TreeModelColumn<bool>          italic;

  DemoColumns() { add(title); add(filename); add(slot); add(italic); }
};

// Singleton accessor function.
const DemoColumns& demo_columns()
{
  static DemoColumns column_record;
  return column_record;
}

} // anonymous namespace


DemoWindow::DemoWindow()
: m_RunButton("Run"),
  m_HBox(Gtk::ORIENTATION_HORIZONTAL),
  m_TextWidget_Info(false),
  m_TextWidget_Source(true)
{
  m_pWindow_Example = 0;

  configure_header_bar();

  add(m_HBox);

  //Tree:
  m_refTreeStore = Gtk::TreeStore::create(demo_columns());
  m_TreeView.set_model(m_refTreeStore);

  m_refTreeSelection = m_TreeView.get_selection();
  m_refTreeSelection->set_mode(Gtk::SELECTION_BROWSE);
  m_refTreeSelection->set_select_function( sigc::ptr_fun(&DemoWindow::select_function) );

  m_TreeView.set_size_request(200, -1);

  fill_tree();

  //SideBar
  m_SideBar.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
  m_SideBar.get_style_context()->add_class("sidebar");
  m_SideBar.add(m_TreeView);
  m_HBox.pack_start(m_SideBar, Gtk::PACK_SHRINK);

  //Notebook:
  m_Notebook.append_page(m_TextWidget_Info, "_Info", true);  //true = use mnemonic.
  m_Notebook.append_page(m_TextWidget_Source, "_Source", true);  //true = use mnemonic.
  m_Notebook.child_property_tab_expand(m_TextWidget_Info) = true;
  m_Notebook.child_property_tab_expand(m_TextWidget_Source) = true;
  m_HBox.pack_start(m_Notebook);

  set_default_size (800, 600);

  load_file (testgtk_demos[0].filename);
  show_all();
}

void DemoWindow::configure_header_bar()
{
  m_HeaderBar.set_show_close_button();
  m_HeaderBar.pack_start(m_RunButton);

  m_RunButton.get_style_context()->add_class("suggested-action");
  m_RunButton.signal_clicked().connect(sigc::mem_fun(*this, &DemoWindow::on_run_button_clicked));

  set_titlebar(m_HeaderBar);
}

void DemoWindow::fill_tree()
{
  const DemoColumns& columns = demo_columns();

  /* this code only supports 1 level of children. If we
   * want more we probably have to use a recursing function.
   */
  for(Demo* d = testgtk_demos; d && d->title; ++d)
  {
    Gtk::TreeRow row = *(m_refTreeStore->append());

    row[columns.title]    = d->title;
    row[columns.filename] = d->filename;
    row[columns.slot]     = d->slot;
    row[columns.italic]   = false;

    for(Demo* child = d->children; child && child->title; ++child)
    {
      Gtk::TreeRow child_row = *(m_refTreeStore->append(row.children()));

      child_row[columns.title]    = child->title;
      child_row[columns.filename] = child->filename;
      child_row[columns.slot]     = child->slot;
      child_row[columns.italic]   = false;
    }
  }

  Gtk::CellRendererText* pCell = Gtk::manage(new Gtk::CellRendererText());
  pCell->property_style() = Pango::STYLE_ITALIC;

  Gtk::TreeViewColumn* pColumn = new Gtk::TreeViewColumn("Widget (double click for demo)", *pCell);
  pColumn->add_attribute(pCell->property_text(), columns.title);
  pColumn->add_attribute(pCell->property_style_set(), columns.italic);

  m_TreeView.append_column(*pColumn);

  m_refTreeSelection->signal_changed().connect(sigc::mem_fun(*this, &DemoWindow::on_treeselection_changed));
  m_TreeView.signal_row_activated().connect(sigc::mem_fun(*this, &DemoWindow::on_treeview_row_activated));

  m_TreeView.expand_all();
}

DemoWindow::~DemoWindow()
{
  on_example_window_hide(); //delete the example window if there is one.
}

void DemoWindow::on_run_button_clicked()
{
  if(m_pWindow_Example == 0) //Don't open a second window.
  {
    if(const Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected())
    {
      m_TreePath = m_refTreeStore->get_path(iter);

      run_example(*iter);
    }
  }
}

void DemoWindow::on_treeview_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* /* model */)
{
  m_TreePath = path;

  if(m_pWindow_Example == 0) //Don't open a second window.
  {
    if(const Gtk::TreeModel::iterator iter = m_TreeView.get_model()->get_iter(m_TreePath))
    {
      run_example(*iter);
    }
  }
}

void DemoWindow::run_example(const Gtk::TreeModel::Row& row)
{
  const DemoColumns& columns = demo_columns();

  const type_slotDo& slot = row[columns.slot];

  if(slot && (m_pWindow_Example = slot()))
  {
    row[columns.italic] = true;

    m_pWindow_Example->signal_hide().connect(sigc::mem_fun(*this, &DemoWindow::on_example_window_hide));
    m_pWindow_Example->show();
  }
}

bool DemoWindow::select_function(const Glib::RefPtr<Gtk::TreeModel>& model,
                                 const Gtk::TreeModel::Path& path, bool)
{
  const Gtk::TreeModel::iterator iter = model->get_iter(path);
  return iter->children().empty(); // only allow leaf nodes to be selected
}

void DemoWindow::on_treeselection_changed()
{
  if(const Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected())
  {
    const Glib::ustring filename = (*iter)[demo_columns().filename];
    const Glib::ustring title = (*iter)[demo_columns().title];

    load_file(Glib::filename_from_utf8(filename));
    m_HeaderBar.set_title(title);
  }
}

bool DemoWindow::read_line (FILE *stream, GString *str)
{
  int n_read = 0;

#ifdef HAVE_FLOCKFILE
  flockfile (stream);
#endif

  g_string_truncate (str, 0);

  while (1)
    {
      int c;

#ifdef HAVE_GETC_UNLOCKED
      c = getc_unlocked (stream);
#endif //GLIBMM_PROPERTIES_ENABLED
      if (c == EOF)
	goto done;
      else
	n_read++;

      switch (c)
	{
	case '\r':
	case '\n':
	  {
#ifdef HAVE_GETC_UNLOCKED
	    int next_c = getc_unlocked (stream);
#endif //GLIBMM_PROPERTIES_ENABLED
	    if (!(next_c == EOF ||
		  (c == '\r' && next_c == '\n') ||
		  (c == '\n' && next_c == '\r')))
	      ungetc (next_c, stream);
	
	    goto done;
	  }
	default:
	  g_string_append_c (str, c);
	}
    }

 done:

#ifdef HAVE_FUNLOCKFILE
  funlockfile (stream);
#endif
  return n_read > 0;
}


void DemoWindow::load_file(const std::string& filename)
{
  if ( m_current_filename == filename )
  {
    return;
  }
  else
  {
    m_current_filename = filename;

    m_TextWidget_Info.wipe();
    m_TextWidget_Source.wipe();

    Glib::RefPtr<Gtk::TextBuffer> refBufferInfo = m_TextWidget_Info.get_buffer();
    Glib::RefPtr<Gtk::TextBuffer> refBufferSource = m_TextWidget_Source.get_buffer();

    FILE* file = fopen (filename.c_str(), "r");
    if (!file)
    {
      try
      {
        std::string installed = demo_find_file(filename);
        file = fopen (installed.c_str(), "r");
      }
      catch (const Glib::FileError& ex)
      {
        g_warning ("%s\n", ex.what().c_str());
        return;
      }
    }

    if (!file)
    {
      g_warning ("Cannot open %s: %s\n", filename.c_str(), g_strerror (errno));
      return;
    }

    GString *buffer = g_string_new (NULL);
    int state = 0;
    bool in_para = false;
    Gtk::TextBuffer::iterator start = refBufferInfo->get_iter_at_offset(0);
    while (read_line (file, buffer))
    {
      gchar *p = buffer->str;
      gchar *q = 0;
      gchar *r = 0;

      switch (state)
    	{
      	case 0:
      	  /* Reading title */
      	  while (*p == '/' || *p == '*' || isspace (*p))
      	    p++;

      	  r = p;

      	  while (*r != '/' && strlen (r))
      	    r++;
      	  if (strlen (r) > 0)
      	    p = r + 1;

      	  q = p + strlen (p);

      	  while (q > p && isspace (*(q - 1)))
      	    q--;

      	  if (q > p)
    	    {
    	      Gtk::TextBuffer::iterator end = start;

              const Glib::ustring strTemp (p, q);
    	      end = refBufferInfo->insert(end, strTemp);
    	      start = end;

    	      start.backward_chars(strTemp.length());
    	      refBufferInfo->apply_tag_by_name("title", start, end);

    	      start = end;
      	
    	      state++;
    	    }
    	    break;
  	
      	case 1:
      	  /* Reading body of info section */
      	  while (isspace (*p))
      	    p++;

      	  if (*p == '*' && *(p + 1) == '/')
    	    {
    	      start = refBufferSource->get_iter_at_offset(0);
    	      state++;
    	    }
      	  else
    	    {
    	      int len;
        	
    	      while (*p == '*' || isspace (*p))
    		      p++;

    	      len = strlen (p);
    	      while (isspace (*(p + len - 1)))
    		     len--;
        	
    	      if (len > 0)
                {
                  if (in_para)
                    {
                      start = refBufferInfo->insert(start, " ");
                    }

                  start = refBufferInfo->insert(start, Glib::ustring(p, p + len));
                  in_para = 1;
                }
              else
                {
                  start = refBufferInfo->insert(start, "\n");
                  in_para = 0;
                }
      	    }
      	  break;

      	case 2:
      	  /* Skipping blank lines */
      	  while (isspace (*p))
      	    p++;

      	  if (*p)
    	    {
    	      p = buffer->str;
    	      state++;
    	      /* Fall through */
    	    }
      	  else
      	    break;
        	
      	case 3:
      	  /* Reading program body */
      	  start = refBufferSource->insert(start, p);
      	  start = refBufferSource->insert(start, "\n");
      	  break;
      	}
     }

    m_TextWidget_Source.fontify();
  }
}


void DemoWindow::on_example_window_hide()
{
  if(m_pWindow_Example)
  {
    if(const Gtk::TreeModel::iterator iter = m_refTreeStore->get_iter(m_TreePath))
    {
      (*iter)[demo_columns().italic] = false;

      delete m_pWindow_Example;
      m_pWindow_Example = 0;
    }
  }
}

