/* example-start tictactoe tictactoe.c */

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
#include <gtkmm.h>
#include <gtkmm/table.h>
#include <gtkmm/togglebutton.h>
#include "tictactoe.h"

TicTacToe::TicTacToe ()
{
  Gtk::Table *table;
  Gtk::ToggleButton *button;
  int i,j;
  
  table = manage( new Gtk::Table (3, 3, true) );
  add ( *table);

  for (i=0;i<3; i++)
    for (j=0;j<3; j++)
      {
	buttons[i][j] = button = manage( new Gtk::ToggleButton ());
	table-> attach (*button, i, i+1, j, j+1);
	button-> signal_toggled().connect ( SigC::bind(
                                     SigC::slot(*this, &TicTacToe::toggle), 
                                     button));
	button-> set_size_request (20, 20);
      }

  table-> show_all();
}

TicTacToe::~TicTacToe() {}

void
TicTacToe::clear ()
{
  freeze();

  for (int i=0;i<3;i++)
    for (int j=0;j<3;j++)
      buttons[i][j]-> set_active (false);

  thaw();
}

void
TicTacToe::toggle (Gtk::ToggleButton *button)
{
  int i,k;
  if (frozen) return;

  static int rwins[8][3] = { { 0, 0, 0 }, { 1, 1, 1 }, { 2, 2, 2 },
			     { 0, 1, 2 }, { 0, 1, 2 }, { 0, 1, 2 },
			     { 0, 1, 2 }, { 0, 1, 2 } };
  static int cwins[8][3] = { { 0, 1, 2 }, { 0, 1, 2 }, { 0, 1, 2 },
			     { 0, 0, 0 }, { 1, 1, 1 }, { 2, 2, 2 },
			     { 0, 1, 2 }, { 2, 1, 0 } };

  bool success, found;

  for (k=0; k<8; k++)
    {
      success = true;
      found = false;

      for (i=0;i<3;i++)
	{
	  success &= buttons[rwins[k][i]][cwins[k][i]]-> get_active();
	  found |= buttons[rwins[k][i]][cwins[k][i]] == button;
	}
      
      if (success && found)
	{
	  tictactoe();
	  break;
	}
    }
}

/* example-end */
