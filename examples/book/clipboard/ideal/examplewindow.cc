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

#include "examplewindow.h"
#include <algorithm>
#include <gtkmm/stock.h>


namespace
{

//These should usually be MIME types.
const char example_target_custom[] = "gtkmmclipboardexample";
const char example_target_text[]   = "UTF8_STRING";

} // anonymous namespace


ExampleWindow::ExampleWindow()
: m_Label("Select cells in the table, click Copy, then open a second instance "
          "of this example to try pasting the copied data.\nOr try pasting the "
          "text representation into gedit."),
  m_Table(2, 2, true),
  m_ButtonA1("A1"), m_ButtonA2("A2"), m_ButtonB1("B1"), m_ButtonB2("B2"),
  m_Button_Copy(Gtk::Stock::COPY), m_Button_Paste(Gtk::Stock::PASTE)
{                                                                                                
  set_title("Gtk::Clipboard example");
  set_border_width(12);                         

  add(m_VBox);

  m_VBox.pack_start(m_Label, Gtk::PACK_SHRINK);

  //Fill Table:
  m_VBox.pack_start(m_Table);
  m_Table.attach(m_ButtonA1, 0, 1, 0, 1);
  m_Table.attach(m_ButtonA2, 1, 2, 0, 1);
  m_Table.attach(m_ButtonB1, 0, 1, 1, 2);
  m_Table.attach(m_ButtonB2, 1, 2, 1, 2);

  //Add ButtonBox to bottom:
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);
  m_VBox.set_spacing(6);
  
  //Fill ButtonBox:
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_ButtonBox.pack_start(m_Button_Copy, Gtk::PACK_SHRINK);
  m_Button_Copy.signal_clicked().connect( sigc::mem_fun(*this, &ExampleWindow::on_button_copy) );
  m_ButtonBox.pack_start(m_Button_Paste, Gtk::PACK_SHRINK);
  m_Button_Paste.signal_clicked().connect( sigc::mem_fun(*this, &ExampleWindow::on_button_paste) );
    
  show_all_children();

  update_paste_status();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_copy()
{
  //Build a string representation of the stuff to be copied:
  //Ideally you would use XML, with an XML parser here:
  Glib::ustring strData;
  strData += m_ButtonA1.get_active() ? "1" : "0";
  strData += m_ButtonA2.get_active() ? "1" : "0";
  strData += m_ButtonB1.get_active() ? "1" : "0";
  strData += m_ButtonB2.get_active() ? "1" : "0";

  //Store the copied data until it is pasted:
  m_ClipboardStore = strData;
   
  Glib::RefPtr<Gtk::Clipboard> refClipboard = Gtk::Clipboard::get();

  //Targets:
  std::list<Gtk::TargetEntry> listTargets;

  listTargets.push_back( Gtk::TargetEntry(example_target_custom) );
  listTargets.push_back( Gtk::TargetEntry(example_target_text) );
  
  refClipboard->set( listTargets, sigc::mem_fun(*this, &ExampleWindow::on_clipboard_get), sigc::mem_fun(*this, &ExampleWindow::on_clipboard_clear) );

  update_paste_status();
}

void ExampleWindow::on_button_paste()
{        
  //Tell the clipboard to call our method when it is ready:
  Glib::RefPtr<Gtk::Clipboard> refClipboard = Gtk::Clipboard::get();

  refClipboard->request_contents(example_target_custom,  sigc::mem_fun(*this, &ExampleWindow::on_clipboard_received) );

  update_paste_status();
}

void ExampleWindow::on_clipboard_get(Gtk::SelectionData& selection_data, guint)
{
  //info is meant to indicate the target, but it seems to be always 0,
  //so we use the selection_data's target instead.

  const std::string target = selection_data.get_target(); 

  if(target == example_target_custom)
  {
    // This set() override uses an 8-bit text format for the data.
    selection_data.set(example_target_custom, m_ClipboardStore);
  }
  else if(target == example_target_text)
  {
    //Build some arbitrary text representation of the data,
    //so that people see something when they paste into a text editor:
    Glib::ustring text_representation;

    text_representation += m_ButtonA1.get_active() ? "A1, " : "";
    text_representation += m_ButtonA2.get_active() ? "A2, " : "";
    text_representation += m_ButtonB1.get_active() ? "B1, " : "";
    text_representation += m_ButtonB2.get_active() ? "B2, " : "";
                                          
    selection_data.set_text(text_representation);
  }
  else
  {
    g_warning("ExampleWindow::on_clipboard_get(): Unexpected clipboard target format.");
  } 
}

void ExampleWindow::on_clipboard_clear()
{
  //This isn't really necessary. I guess it might save memory.
  
  m_ClipboardStore.clear();
}

void ExampleWindow::on_clipboard_received(const Gtk::SelectionData& selection_data)
{
  const std::string target = selection_data.get_target();

  if(target == example_target_custom) //It should always be this, because that' what we asked for when calling request_contents().
  {
    Glib::ustring clipboard_data = selection_data.get_data_as_string();

    //See comment in on_button_copy() about this silly clipboard format.
    if(clipboard_data.size() >= 4)
    {
      m_ButtonA1.set_active( clipboard_data[0] == '1' );
      m_ButtonA2.set_active( clipboard_data[1] == '1' );
      m_ButtonB1.set_active( clipboard_data[2] == '1' );
      m_ButtonB2.set_active( clipboard_data[3] == '1' );
    }
  }
}

void ExampleWindow::update_paste_status()
{
  //Disable the paste button if there is nothing to paste.
  
  Glib::RefPtr<Gtk::Clipboard> refClipboard = Gtk::Clipboard::get();

  //Discover what targets are available:
  refClipboard->request_targets( sigc::mem_fun(*this, &ExampleWindow::on_clipboard_received_targets) );
}

void ExampleWindow::on_clipboard_received_targets(const Glib::StringArrayHandle& targets_array)
{
  // Get the list of available clipboard targets:
  std::list<std::string> targets = targets_array;

  const bool bPasteIsPossible =
      std::find(targets.begin(), targets.end(), example_target_custom) != targets.end();

  // Enable/Disable the Paste button appropriately:
  m_Button_Paste.set_sensitive(bPasteIsPossible);
}

