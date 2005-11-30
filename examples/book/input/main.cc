#include <gtkmm/main.h>
#include "gtkmmconfig.h" //For HAVE_MKFIFO
#include <fcntl.h>
#include <iostream>

#include <unistd.h> //The SUN Forte compiler puts F_OK here.

//The SUN Forte compiler needs these for mkfifo:
#include <sys/types.h>
#include <sys/stat.h>

int read_fd;
Glib::RefPtr<Glib::IOChannel> iochannel;

/*
  send to the fifo with:
  echo "Hello" > testfifo

  quit the program with:
  echo "Q" > testfifo
*/

// this will be our signal handler for read operations
// it will print out the message sent to the fifo
// and quit the program if the message was 'Q'.
bool MyCallback(Glib::IOCondition io_condition)
{
  
  if ((io_condition & Glib::IO_IN) == 0) {
    std::cerr << "Invalid fifo response" << std::endl;
  }
  else {
   Glib::ustring buf;

   iochannel->read_line (buf);
   std::cout << buf;
   if (buf == "Q\n")
	   Gtk::Main::quit ();

  }
  return true;
}


int main(int argc, char *argv[])
{
  // the usual Gtk::Main object
  Gtk::Main app(argc, argv);

  if (access("testfifo", F_OK) == -1) {
    // fifo doesn't exit - create it
    #ifdef HAVE_MKFIFO
    if (mkfifo("testfifo", 0666) != 0) {
      std::cerr << "error creating fifo" << std::endl;
      return -1;
    }
    #else
      std::cerr << "error creating fifo: This platform does not have mkfifo()" << std::endl;
    #endif //HAVE_MKFIFO
  }
 
  read_fd = open("testfifo", O_RDONLY);
  if (read_fd == -1)
  {
    std::cerr << "error opening fifo" << std::endl;
    return -1;
  }

  // connect the signal handler
  Glib::signal_io().connect(sigc::ptr_fun(MyCallback), read_fd, Glib::IO_IN);

  // Creates a iochannel from the file descriptor
  iochannel = Glib::IOChannel::create_from_fd(read_fd);

  // and last but not least - run the application main loop
  app.run();

  // now remove the temporary fifo
  if(unlink("testfifo"))
    std::cerr << "error removing fifo" << std::endl;

  return 0;
}
