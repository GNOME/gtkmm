#include <gtkmm/main.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

int read_fd;

/*
  send to the fifo with:
  echo "Hello" > testfifo

  quit the program with:
  echo "Q" > testfifo
*/

// this will be our signal handler for read operations
// it will print out the message sent to the fifo
// and quit the program if the message was, or began
// with, '*'
bool MyCallback(Glib::IOCondition io_condition)
{
  if ((io_condition & Glib::IO_IN) == 0) {
    std::cerr << "Invalid fifo response" << std::endl;
  }
  else {
    char buffer[PIPE_BUF];
    int result;
    while ((result = read(read_fd, buffer, PIPE_BUF)) > 0) {
      if (*buffer == 'Q') Gtk::Main::quit();
      else write(0, buffer, result);
    }
  }
  return true;
}


int main(int argc, char *argv[])
{
  // the usual Gtk::Main object
  Gtk::Main app(argc, argv);

  if (access("testfifo", F_OK) == -1) {
    // fifo doesn't exit - create it
    if (mkfifo("testfifo", 0666) != 0) {
      std::cerr << "error creating fifo" << std::endl;
      return -1;
    }
  }
 
  read_fd = open("testfifo", O_RDONLY | O_NONBLOCK);
  if (read_fd == -1)
  {
    std::cerr << "error opening fifo" << std::endl;
    return -1;
  }

  // connect the signal handler
  Glib::signal_io().connect(sigc::ptr_fun(MyCallback), read_fd, Glib::IO_IN);

  // and last but not least - run the application main loop
  app.run();

  // now remove the temporary fifo
  if(unlink("testfifo"))
    std::cerr << "error removing fifo" << std::endl;

  return 0;
}
