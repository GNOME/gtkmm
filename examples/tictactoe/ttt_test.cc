#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include "tictactoe.h"

void
win (TicTacToe *ttt)
{
  g_print ("Yay!\n");
  ttt-> clear();
}


int 
main (int argc, char *argv[])
{
  Gtk::Main m(argc, argv);

  TicTacToe* ttt = manage( new TicTacToe );
  ttt-> tictactoe.connect ( bind (slot (&win), ttt) );

  Gtk::Window window;
  window.set_title ("Tic-Tac-Toe");
  window.set_border_width (10);
  window.add (*ttt);
  window.show_all ();
  
  Gtk::Main::run(window);
  
  return 0;
}
