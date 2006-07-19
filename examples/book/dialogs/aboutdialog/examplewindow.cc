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
#include <gtkmm/aboutdialog.h>
#include <iostream>
#include <gtk/gtkaboutdialog.h>


ExampleWindow::ExampleWindow()
: m_Button("Show AboutDialog")
{
  set_title("Gtk::AboutDialog example");

  add(m_ButtonBox);
  
  m_ButtonBox.pack_start(m_Button);
  m_Button.signal_clicked().connect( sigc::mem_fun(*this, &ExampleWindow::on_button_clicked) );

  m_Dialog.set_transient_for(*this);
  
  m_Dialog.set_name("Example application");
  m_Dialog.set_version("1.0.0");
  m_Dialog.set_copyright("Murray Cumming");
  m_Dialog.set_comments("This is just an example application.");
  m_Dialog.set_license("LGPL");
  
  m_Dialog.set_website("http://www.gtkmm.org");
  m_Dialog.set_website_label("gtkmm website");
  
  std::list<Glib::ustring> list_authors;
  list_authors.push_back("Murray Cumming");
  list_authors.push_back("Somebody Else");
  list_authors.push_back("AN Other");
  m_Dialog.set_authors(list_authors);
  
  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_clicked()
{
  m_Dialog.show();
  
  //Bring it to the front, in case it was already shown:
  m_Dialog.present();
}

