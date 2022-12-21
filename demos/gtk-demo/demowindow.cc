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
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include "demos.h"
#include "demowindow.h"

#include <glibmm/bytes.h>
#include <glibmm/convert.h>
#include <giomm/liststore.h>
#include <giomm/resource.h>
#include <gtkmm/treelistmodel.h>
#include <gtkmm/signallistitemfactory.h>
#include <gtkmm/treeexpander.h>
#include <gtkmm/treelistrow.h>
#include <gtkmm/image.h>
#include <gtkmm/video.h>

#include <cstddef>
#include <cstring>
#include <iostream>

using std::isspace;
using std::strlen;

namespace
{

class DemoColumns : public Glib::Object
{
public:
  Glib::ustring m_title;
  std::string m_filename;
  type_slotDo m_slot; // The method to call.
  const Demo* m_children{nullptr};

  static Glib::RefPtr<DemoColumns> create(const Demo& demo)
  {
    return Glib::make_refptr_for_instance<DemoColumns>(new DemoColumns(demo));
  }
  
protected:
  DemoColumns(const Demo& demo)
  : m_title(demo.title), m_filename(demo.filename), m_slot(demo.slot),
    m_children(demo.children)
  { }
};

} // anonymous namespace

//static
DemoWindow* DemoWindow::m_pDemoWindow = nullptr;

//static
DemoWindow* DemoWindow::get_demo_window()
{
  return m_pDemoWindow;
}

DemoWindow::DemoWindow()
: m_RunButton("Run"),
  m_HBox(Gtk::Orientation::HORIZONTAL),
  m_TextWidget_Info(false),
  m_TextWidget_Source(true)
{
  m_pDemoWindow = this;

  configure_header_bar();

  set_child(m_HBox);

  //Tree:
  auto root = create_demo_model();
  auto tree_model = Gtk::TreeListModel::create(root,
    sigc::mem_fun(*this, &DemoWindow::create_demo_model), false, true);
  m_refSingleSelection = Gtk::SingleSelection::create(tree_model);
  m_refSingleSelection->signal_selection_changed().connect(
    sigc::mem_fun(*this, &DemoWindow::on_selection_changed));

  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &DemoWindow::on_setup_listitem));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &DemoWindow::on_bind_listitem));

  m_ListView.set_model(m_refSingleSelection);
  m_ListView.set_factory(factory);
  m_ListView.signal_activate().connect(
    sigc::mem_fun(*this, &DemoWindow::on_listview_row_activated));

  m_ListView.set_size_request(200, -1);

  //SideBar
  m_SideBar.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
  m_SideBar.add_css_class("sidebar");
  m_SideBar.set_hexpand(false);
  m_SideBar.set_child(m_ListView);
  m_HBox.append(m_SideBar);

  //Notebook:
  m_Notebook.popup_enable();
  m_Notebook.set_scrollable();
  m_Notebook.append_page(m_TextWidget_Info, "_Info", true);  //true = use mnemonic.
  m_Notebook.append_page(m_TextWidget_Source, "_Source", true);  //true = use mnemonic.
  m_Notebook.get_page(m_TextWidget_Info)->property_tab_expand() = true;
  m_Notebook.get_page(m_TextWidget_Source)->property_tab_expand() = true;
  m_Notebook.set_expand(true);
  m_HBox.append(m_Notebook);
  m_HBox.set_vexpand(true);

  set_default_size(800, 600);

  load_file(testgtk_demos[0].filename);
  m_refSingleSelection->set_selected(0);
  m_ListView.grab_focus();
}

DemoWindow::~DemoWindow()
{
  on_example_window_hide(); //delete the example window if there is one.
  if (m_pDemoWindow == this)
    m_pDemoWindow = nullptr;
}

void DemoWindow::configure_header_bar()
{
  m_HeaderBar.set_show_title_buttons();
  m_HeaderBar.pack_start(m_RunButton);

  m_RunButton.add_css_class("suggested-action");
  m_RunButton.signal_clicked().connect(sigc::mem_fun(*this, &DemoWindow::on_run_button_clicked));

  set_titlebar(m_HeaderBar);
}

Glib::RefPtr<Gio::ListModel> DemoWindow::create_demo_model(
  const Glib::RefPtr<Glib::ObjectBase>& item)
{
  auto col = std::dynamic_pointer_cast<DemoColumns>(item);
  if (col && !col->m_children)
    // An item without children, i.e. a leaf in the tree. 
    return {};

  auto result = Gio::ListStore<DemoColumns>::create();
  const Demo* demo = col ? col->m_children : testgtk_demos;
  for (; demo->title; ++demo)
    result->append(DemoColumns::create(*demo));
  return result;
}

void DemoWindow::on_setup_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  // Each ListItem contains a TreeExpander, which contains a Label.
  // The Label shows the DemoColumns::m_title. That's done in on_bind_listitem().
  auto expander = Gtk::make_managed<Gtk::TreeExpander>();
  auto label = Gtk::make_managed<Gtk::Label>();
  expander->set_child(*label);
  list_item->set_child(*expander);
}

void DemoWindow::on_bind_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto row = std::dynamic_pointer_cast<Gtk::TreeListRow>(list_item->get_item());
  if (!row)
    return;
  // Only leaves in the tree can be selected.
  list_item->set_selectable(!row->is_expandable());
  auto col = std::dynamic_pointer_cast<DemoColumns>(row->get_item());
  if (!col)
    return;
  auto expander = dynamic_cast<Gtk::TreeExpander*>(list_item->get_child());
  if (!expander)
    return;
  expander->set_list_row(row);
  auto label = dynamic_cast<Gtk::Label*>(expander->get_child());
  if (!label)
    return;
  label->set_text(col->m_title);
}

void DemoWindow::on_selection_changed(unsigned int /*position*/, unsigned int /*n_items*/)
{
  auto item = m_refSingleSelection->get_selected_item();
  auto row = std::dynamic_pointer_cast<Gtk::TreeListRow>(item);
  if (!row)
    return;
  auto col = std::dynamic_pointer_cast<DemoColumns>(row->get_item());
  if (!col)
    return;
  set_title(col->m_title);
  if (!col->m_filename.empty())
    load_file(col->m_filename);
}

void DemoWindow::on_listview_row_activated(unsigned int position)
{
  auto item = std::dynamic_pointer_cast<Gio::ListModel>(m_ListView.get_model())->get_object(position);
  run_example(item);
}

void DemoWindow::on_run_button_clicked()
{
  auto item = m_refSingleSelection->get_selected_item();
  run_example(item);
}

void DemoWindow::run_example(const Glib::RefPtr<Glib::ObjectBase>& item)
{
  auto row = std::dynamic_pointer_cast<Gtk::TreeListRow>(item);
  if (!row)
    return;
  auto col = std::dynamic_pointer_cast<DemoColumns>(row->get_item());
  if (!col)
    return;
  const type_slotDo& slot = col->m_slot;

  if (slot && (m_pWindow_Example = slot()))
  {
    m_pWindow_Example->set_transient_for(*this);
    m_pWindow_Example->set_modal(true);
    m_pWindow_Example->set_hide_on_close(true);
    m_pWindow_Example->signal_hide().connect(sigc::mem_fun(*this, &DemoWindow::on_example_window_hide));
    m_pWindow_Example->set_visible(true);
  }
}

void DemoWindow::on_example_window_hide()
{
  delete m_pWindow_Example;
  m_pWindow_Example = nullptr;
}

void DemoWindow::load_file(const std::string& filename)
{
  if ( m_current_filename == filename )
  {
    return;
  }
  else
  {
    // Show extra data files for this demo, if any.
    remove_data_tabs();
    add_data_tabs(filename);

    m_current_filename = filename;

    m_TextWidget_Info.wipe();
    m_TextWidget_Source.wipe();

    auto refBufferInfo = m_TextWidget_Info.get_buffer();
    auto refBufferSource = m_TextWidget_Source.get_buffer();

    Glib::RefPtr<const Glib::Bytes> bytes;
    try
    {
      bytes = Gio::Resource::lookup_data_global("/sources/" + filename);
    }
    catch (const Gio::ResourceError& ex)
    {
      std::cerr << "Cannot open source for " << filename << ": " << ex.what() << std::endl;
      return;
    }

    gsize data_size = 0;
    gchar** lines = g_strsplit(static_cast<const gchar*>(bytes->get_data(data_size)), "\n", -1);
    bytes.reset();

    int state = 0;
    bool in_para = false;
    auto start = refBufferInfo->get_iter_at_offset(0);
    for (std::size_t i = 0; lines[i] != NULL; i++)
    {
      /* Make sure \r is stripped at the end for the poor Windows people */
      lines[i] = g_strchomp(lines[i]);

      gchar *p = lines[i];
      gchar *q = nullptr;
      gchar *r = nullptr;

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
    	      auto end = start;

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

          if (!*p)
            break;

          p = lines[i];
          state++;
          [[fallthrough]];

      	case 3:
      	  /* Reading program body */
      	  start = refBufferSource->insert(start, p);
      	  start = refBufferSource->insert(start, "\n");
      	  break;
      } // end switch state
    } // end for i

    g_strfreev (lines);

    m_TextWidget_Source.fontify();
  }
}

void DemoWindow::add_data_tabs(const std::string& filename)
{
  // We can get the resource_dir from the filename by removing "example_" and ".cc".
  const auto resource_dir = "/" + filename.substr(8, filename.size() - 11);
  std::vector<std::string> resources;
  try
  {
    resources = Gio::Resource::enumerate_children_global(resource_dir);
  }
  catch (const Gio::ResourceError& ex)
  {
    // Ignore this exception. It's no error, if resource_dir does not exist.
  }
  for (std::size_t i = 0; i < resources.size(); ++i)
  {
    const auto resource_name = resource_dir + "/" + resources[i];
    std::string suffix;
    auto suffix_pos = resources[i].find_last_of('.');
    if (suffix_pos != std::string::npos)
      suffix = resources[i].substr(suffix_pos);

    Gtk::Widget* widget = nullptr;
    if (suffix == ".gif" || suffix == ".jpg" || suffix == ".png")
    {
      // It's an image.
      auto image = new Gtk::Image();
      image->set_from_resource(resource_name);
      if (image->get_paintable())
        widget = image;
      else
        delete image;
    }
    else if (suffix == ".webm")
    {
      // It's a video.
      auto video = new Gtk::Video();
      video->set_resource(resource_name);
      if (video->get_file())
        widget = video;
      else
        delete video;
    }
    if (!widget)
    {
      // So we've used the best API available to figure out it's
      // not an image or a video. Let's try something else then.

      Glib::RefPtr<const Glib::Bytes> bytes;
      try
      {
        bytes = Gio::Resource::lookup_data_global(resource_name);
      }
      catch (const Gio::ResourceError& ex)
      {
        std::cerr << "Can't get data from resource '" << resource_name << "': " << ex.what() << std::endl;
        continue;
      }
      gsize data_size = 0;
      auto data = static_cast<const char*>(bytes->get_data(data_size));
      if (g_utf8_validate(data, data_size, nullptr))
      {
        // Looks like it parses as text. Dump it into a TextWidget then!
        auto textwidget = new TextWidget(false);
        auto refBuffer = textwidget->get_buffer();
        refBuffer->set_text(data, data + data_size);
        widget = textwidget;
      }
      else
      {
        std::cerr << "Don't know how to display resource '" << resource_name << "'" << std::endl;
        continue;
      }
    }
    m_Notebook.append_page(*Gtk::manage(widget), Glib::ustring(resources[i]));
    m_Notebook.get_page(*widget)->property_tab_expand() = true;
  }
}

void DemoWindow::remove_data_tabs()
{
  // Remove all tabs except Info and Source.
  for (auto i = m_Notebook.get_n_pages(); i-- > 2;)
  {
    m_Notebook.remove_page(i);
  }
}
