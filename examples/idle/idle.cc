
#include <algorithm>
#include <iostream>
#include <map>

#include <gtkmm/adjustment.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/main.h>
#include <gtkmm/window.h>


class IdleExample : public Gtk::Window
{
  // the usual stuff - nothing exciting
  Gtk::Button m_quit;
  Gtk::ProgressBar m_progressbar_c;
  Gtk::ProgressBar m_progressbar_d;

public:
  IdleExample();
  
  // a timer-function
  bool timer_callback();
  // a idle-function
  bool idle_callback();

};


IdleExample::IdleExample() :
  m_quit("Quit"),
  m_progressbar_c(),
  m_progressbar_d()
{
  // connect the callbacks
  m_quit.signal_pressed().connect(SigC::slot(*this, &Gtk::Widget::hide));

  // put buttons into container
  Gtk::VBox *vbox = manage( new Gtk::VBox(false,5));

  // adding a few widgets
  vbox->pack_start(* manage(new Gtk::Label("Formatting windows drive C:")));
  vbox->pack_start(* manage(new Gtk::Label("100 MB")));
  vbox->pack_start(m_progressbar_c);

  vbox->pack_start(* manage(new Gtk::Label("")));

  vbox->pack_start(* manage(new Gtk::Label("Formatting windows drive D:")));
  vbox->pack_start(* manage(new Gtk::Label("5000 MB")));
  vbox->pack_start(m_progressbar_d);

  Gtk::HBox *hbox = manage( new Gtk::HBox(false,10));
  hbox->pack_start(m_quit, Gtk::PACK_EXPAND_PADDING);
  vbox->pack_start(*hbox);

  // set border and display all
  set_border_width(5);
  add(*vbox);
  show_all();

  // formatting drive c in timeout callback ;-)
  Glib::signal_timeout().connect(slot(*this,&IdleExample::timer_callback), 50);

  // formatting drive d in idle callback ;-)
  Glib::signal_idle().connect(slot(*this,&IdleExample::idle_callback));
}


// increase the progressbar's value and remove callback when done
bool IdleExample::timer_callback()
{
  double fraction = m_progressbar_c.get_fraction();
  fraction += 0.005;
  m_progressbar_c.set_fraction(std::min(fraction, 1.0));

  // Disconnect timeout handler when reaching 1.0.
  return (fraction < 1.0);
}


// increase the progressbar's value and remove callback when done
// note the diffrence in speed and also the impact of system load
// try to increase system load and watch the drive d value
bool IdleExample::idle_callback()
{
  double fraction = m_progressbar_d.get_fraction();
  fraction += 0.0001;
  m_progressbar_d.set_fraction(std::min(fraction, 1.0));

  // Disconnect idle handler when reaching 1.0.
  return (fraction < 1.0);
}

int main (int argc, char *argv[])
{
  Gtk::Main app(argc, argv);

  IdleExample example;

  Gtk::Main::run(example);
  return 0;
}

