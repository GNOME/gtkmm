//$Id$ -*- c++ -*-

/* gtkmm example Copyright (C) 2003 gtkmm development team
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

#include <gtkmm/main.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <memory>

std::auto_ptr<std::ifstream> input;


// this will be our signal handler for read operations
// there is not much to say. just read a string,
// print it and quit the application if the string was quit
bool MyCallback(Glib::IOCondition /* condition */)
{
  Glib::ustring dummy;

  do
  {
    (*input) >> dummy;
    std::cout << dummy << std::endl;
  
    if(dummy == "quit")
      Gtk::Main::quit();

  } while(input->fail());
  
  return true;
}


int main(int argc, char *argv[])
{
  // the usual Gtk::Main object
  Gtk::Main app(argc, argv);

  // create a fifo for testing purposes
  if (mkfifo("testfifo", 0666) != 0) {
    std::cerr << "error creating fifo" << std::endl;
    return -1;
  }

  //TODO: I have update this example to build with gtkmm 2, but I'm not sure which of the several commented-out 
  //ifstream and file descriptor things are needed, or should work.
  //We need to look at the gtkmm 1.2 version, if it worked.
  //Alternatively, just find a gtkmm app that monitors files for changes.
  //murrayc
  
  // open the fifo
  input = std::auto_ptr<std::ifstream>( new std::ifstream("testfifo") );
  
  int fd = open("testfifo", 0);
  if (fd == -1)
  {
    std::cerr << "error opening fifo" << std::endl;
    return -1;
  }

  // assign the fifo's filedescriptor to our ifstream object
  //This sucks; it will only ever work with libstdc++-v3, as
  //  both istream::__filebuf_type and the basic_filebuf contructor
  //  that takes an fd are libstdc++-v3 specific.
  //input = std::auto_ptr<std::ifstream>( new std::istream(new std::ifstream::__filebuf_type(fd, "testfifo")) );

  // connect the signal handler
  Glib::signal_io().connect(sigc::ptr_fun(MyCallback), fd, Glib::IO_IN);

  // and last but not least - run the application main loop
  app.run();

  // now remove the temporary fifo
  if(unlink("testfifo"))
    std::cerr << "error removing fifo" << std::endl;

  return 0;
}
