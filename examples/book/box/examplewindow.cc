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

#include <iostream>
#include "examplewindow.h"

ExampleWindow::ExampleWindow(int which)
: m_buttonQuit("Quit")
{
  set_title("Gtk::Box example");

  PackBox *pPackBox1, *pPackBox2, *pPackBox3, *pPackBox4, *pPackBox5;

  switch(which)
  {
    case 1:
    {
      m_Label1.set_text("Gtk::HBox(false, 0);");

      // Align the label to the left side.  We'll discuss this function and
      // others in the section on Widget Attributes.
      m_Label1.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);

      // Pack the label into the vertical box (vbox box1).  Remember that
      // widgets added to a vbox will be packed one on top of the other in
      // order.
      m_box1.pack_start(m_Label1, Gtk::PACK_SHRINK);

      // Create a PackBox - homogeneous = false, spacing = 0,
      // options = Gtk::PACK_SHRINK, padding = 0
      pPackBox1 = Gtk::manage(new PackBox(false, 0, Gtk::PACK_SHRINK));
      m_box1.pack_start(*pPackBox1, Gtk::PACK_SHRINK);

      // Create a PackBox - homogeneous = false, spacing = 0,
      // options = Gtk::PACK_EXPAND_PADDING, padding = 0
      pPackBox2 = Gtk::manage(new PackBox(false, 0, Gtk::PACK_EXPAND_PADDING));
      m_box1.pack_start(*pPackBox2, Gtk::PACK_SHRINK);

      // Create a PackBox - homogeneous = false, spacing = 0,
      // options = Gtk::PACK_EXPAND_WIDGET, padding = 0
      pPackBox3 = Gtk::manage(new PackBox(false, 0, Gtk::PACK_EXPAND_WIDGET));
      m_box1.pack_start(*pPackBox3, Gtk::PACK_SHRINK);

      // pack the separator into the vbox.  Remember each of these
      // widgets are being packed into a vbox, so they'll be stacked
      // vertically.
      m_box1.pack_start(m_seperator1, Gtk::PACK_SHRINK, 5);

      // create another new label, and show it.
      m_Label2.set_text("Gtk::HBox(true, 0);");
      m_Label2.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
      m_box1.pack_start(m_Label2, Gtk::PACK_SHRINK);

      // Args are: homogeneous, spacing, options, padding
      pPackBox4 = Gtk::manage(new PackBox(true, 0, Gtk::PACK_EXPAND_PADDING));
      m_box1.pack_start(*pPackBox4, Gtk::PACK_SHRINK);

      // Args are: homogeneous, spacing, options, padding
      pPackBox5 = Gtk::manage(new PackBox(true, 0, Gtk::PACK_EXPAND_WIDGET));
      m_box1.pack_start(*pPackBox5, Gtk::PACK_SHRINK);

      m_box1.pack_start(m_seperator2, Gtk::PACK_SHRINK, 5);

      break;
    }

    case 2:
    {

      m_Label1.set_text("Gtk::HBox(false, 10);");
      m_Label1.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
      m_box1.pack_start(m_Label1, Gtk::PACK_SHRINK);

      pPackBox1 = Gtk::manage(new PackBox(false, 10, Gtk::PACK_EXPAND_PADDING));
      m_box1.pack_start(*pPackBox1, Gtk::PACK_SHRINK);

      pPackBox2 = Gtk::manage(new PackBox(false, 10, Gtk::PACK_EXPAND_WIDGET));
      m_box1.pack_start(*pPackBox2, Gtk::PACK_SHRINK);

      m_box1.pack_start(m_seperator1, Gtk::PACK_SHRINK, 5);


      m_Label2.set_text("Gtk::HBox(false, 0);");
      m_Label2.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
      m_box1.pack_start(m_Label2, Gtk::PACK_SHRINK);

      pPackBox3 = Gtk::manage(new PackBox(false, 0, Gtk::PACK_SHRINK, 10));
      m_box1.pack_start(*pPackBox3, Gtk::PACK_SHRINK);

      pPackBox4 = Gtk::manage(new PackBox(false, 0, Gtk::PACK_EXPAND_WIDGET, 10));
      m_box1.pack_start(*pPackBox4, Gtk::PACK_SHRINK);

      m_box1.pack_start(m_seperator2, Gtk::PACK_SHRINK, 5);

      break;
    }

    case 3:
    {
      // This demonstrates the ability to use Gtk::Box::pack_end() to
      // right justify widgets.  First, we create a new box as before.
      pPackBox1 = Gtk::manage(new PackBox(false, 0, Gtk::PACK_SHRINK));

      // create the label that will be put at the end.
      m_Label1.set_text("end");

      // pack it using pack_end(), so it is put on the right side
      // of the PackBox.
      pPackBox1->pack_end(m_Label1, Gtk::PACK_SHRINK);

      m_box1.pack_start(*pPackBox1, Gtk::PACK_SHRINK);

      // this explicitly sets the separator to 400 pixels wide by 5 pixels
      // high.  This is so the hbox we created will also be 400 pixels wide,
      // and the "end" label will be separated from the other labels in the
      // hbox.  Otherwise, all the widgets in the hbox would be packed as
      // close together as possible.
      m_seperator1.set_size_request(400, 5);

      // pack the separator into ourselves
      m_box1.pack_start(m_seperator1, Gtk::PACK_SHRINK, 5);

      break;
    }

    default:
    {
      std::cerr << "Unexpected command-line option." << std::endl;
      break;
    }
  }

  // Connect the signal to hide the window:
  m_buttonQuit.signal_clicked().connect( sigc::mem_fun(*this, &ExampleWindow::on_button_quit_clicked) );

  // pack the button into the quitbox.
  // The last 2 arguments to Box::pack_start are: options, padding.
  m_boxQuit.pack_start(m_buttonQuit, Gtk::PACK_EXPAND_PADDING);
  m_box1.pack_start(m_boxQuit, Gtk::PACK_SHRINK);

  // pack the vbox (box1) which now contains all our widgets, into the
  // main window.
  add(m_box1);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit_clicked()
{
  hide();
}


