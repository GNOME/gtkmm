/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#ifndef __TICTACTOE_H__
#define __TICTACTOE_H__

#include <gdkmm.h>
#include <gtkmm/box.h>
#include <gtkmm/togglebutton.h>

class TicTacToe: public Gtk::VBox
{
  private:
    Gtk::ToggleButton *buttons[3][3];
    bool frozen;
    void toggle(Gtk::ToggleButton*);

  public:
    void freeze() {frozen=true;}
    void thaw() {frozen=false;}

    void clear();

    SigC::Signal0<void> tictactoe;

    TicTacToe();
    ~TicTacToe();
};

#endif /* __TICTACTOE_H__ */
