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
#include <iostream>

ExampleWindow::ExampleWindow()
: m_Button_Close("Close")
{
  set_title("Gtk::Toolbar example");
  set_size_request(300, 300); //The toolbar will not demand any size, because it has an overflow menu.

  add(m_VBox);

  //Put a toolbar at the top, and a button underneath:
  m_VBox.pack_start(m_Toolbar, Gtk::PACK_SHRINK);
  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_VBox.pack_end(m_ButtonBox);

  m_ButtonBox.pack_start(m_Button_Close, Gtk::PACK_SHRINK);

  m_Button_Close.signal_clicked().connect( SigC::slot(*this, &ExampleWindow::on_button_close) );

  //Add the toolbar items:
  {
    //You would normally use the UIManager, and Actions, to create the menus and toolbars together,
    //because toolbar items should just be a way to do what is also in a menu.
    //TODO: Use UIManager instead here. See the demo for an example.:

    //Gtk::Tooltips* tooltips = 0; //We need the Gtk::Tooltips from the Toolbar, I think. I filed a GTK+ bug about this. murrayc.
    
    Gtk::ToolButton* item = Gtk::manage(new Gtk::ToolButton("Click me"));
    //item.set_tooltips(*tooltips, "Toolbar item");
    m_Toolbar.append(*item);
    item->signal_clicked().connect( SigC::slot(*this, &ExampleWindow::on_toolbar_item) );

    m_Toolbar.append( *(Gtk::manage(new Gtk::SeparatorToolItem)) );
    
    item = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::SAVE));
    m_Toolbar.append(*item);
    item->signal_clicked().connect( SigC::slot(*this, &ExampleWindow::on_toolbar_item) );

    item = Gtk::manage(new Gtk::ToggleToolButton("Toggle me"));
    //item.set_tooltips(*tooltips, "toggle duh");
    m_Toolbar.append(*item);
    item->signal_clicked().connect( SigC::slot(*this, &ExampleWindow::on_toolbar_item) );

    //TODO: These don't actually seem to work:
    Gtk::RadioButtonGroup group;
    m_Toolbar.append( *Gtk::manage(new Gtk::RadioToolButton(group, "Radio 1")) );
    m_Toolbar.append( *Gtk::manage(new Gtk::RadioToolButton(group, "Radio 2")) );
    m_Toolbar.append( *Gtk::manage(new Gtk::RadioToolButton(group, "Radio 3")) );
  }

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_close()
{
  hide();
}

void ExampleWindow::on_toolbar_item()
{
  std::cout << "Toolbar item clicked." << std::endl;
}


