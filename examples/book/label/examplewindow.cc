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
:
  m_HBox(false, 5),
  m_VBox(false, 5),
  m_Frame_Normal("Normal Label"),
  m_Frame_Multi("Multi-line Label"),
  m_Frame_Left("Left Justified Label"),
  m_Frame_Right("Right Justified Label"),
  m_Frame_LineWrapped("Line wrapped label"),
  m_Frame_FilledWrapped("Filled, wrapped label"),
  m_Frame_Underlined("Underlined label"),
  m_Label_Normal("_This is a Normal label", true),
  m_Label_Multi("This is a Multi-line label.\nSecond line\nThird line"),
  m_Label_Left("This is a Left-Justified\nMulti-line label.\nThird line"),
  m_Label_Right("This is a Right-Justified\nMulti-line label.\nFourth line, (j/k)"),
  m_Label_Underlined("This label is underlined!\nThis one is underlined in quite a funky fashion")
{
  set_title("Label");
  set_border_width(5);

  add(m_HBox);

  m_HBox.pack_start(m_VBox, Gtk::PACK_SHRINK);

  m_Frame_Normal.add(m_Label_Normal);
  m_VBox.pack_start(m_Frame_Normal, Gtk::PACK_SHRINK);

  m_Frame_Multi.add(m_Label_Multi);
  m_VBox.pack_start(m_Frame_Multi, Gtk::PACK_SHRINK);

  m_Label_Left.set_justify(Gtk::JUSTIFY_LEFT);
  m_Frame_Left.add(m_Label_Left);
  m_VBox.pack_start(m_Frame_Left, Gtk::PACK_SHRINK);

  m_Label_Right.set_justify(Gtk::JUSTIFY_LEFT);
  m_Frame_Right.add(m_Label_Right);
  m_VBox.pack_start(m_Frame_Right, Gtk::PACK_SHRINK);

  m_HBox.pack_start(m_VBox2, Gtk::PACK_SHRINK);

  m_Label_LineWrapped.set_text("This is an example of a line-wrapped label.  It " \
    "should not be taking up the entire             " /* big space to test spacing */\
    "width allocated to it, but automatically " \
    "wraps the words to fit.  " \
    "The time has come, for all good men, to come to " \
    "the aid of their party.  " \
    "The sixth sheik's six sheep's sick.\n" \
    "     It supports multiple paragraphs correctly, " \
    "and  correctly   adds "\
    "many          extra  spaces. ");
  m_Label_LineWrapped.set_line_wrap();
  m_Frame_LineWrapped.add(m_Label_LineWrapped);
  m_VBox2.pack_start(m_Frame_LineWrapped, Gtk::PACK_SHRINK);

  m_Label_FilledWrapped.set_text("This is an example of a line-wrapped, filled label.  " \
    "It should be taking " \
    "up the entire              width allocated to it.  " \
    "Here is a sentence to prove "\
    "my point.  Here is another sentence. "\
    "Here comes the sun, do de do de do.\n"\
    "    This is a new paragraph.\n"\
    "    This is another newer, longer, better " \
    "paragraph.  It is coming to an end, "\
    "unfortunately.");
  m_Label_FilledWrapped.set_justify(Gtk::JUSTIFY_FILL);
  m_Label_FilledWrapped.set_line_wrap();
  m_Frame_FilledWrapped.add(m_Label_FilledWrapped);
  m_VBox2.pack_start(m_Frame_FilledWrapped, Gtk::PACK_SHRINK);

  m_Label_Underlined.set_justify(Gtk::JUSTIFY_LEFT);
  m_Label_Underlined.set_pattern ("_________________________ _ _________ _ ______     __ _______ ___");
  m_Frame_Underlined.add(m_Label_Underlined);
  m_VBox2.pack_start(m_Frame_Underlined, Gtk::PACK_SHRINK);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}


