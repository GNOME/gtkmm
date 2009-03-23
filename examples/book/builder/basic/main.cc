#include <gtkmm.h>
#include <iostream>

Gtk::Dialog* pDialog = 0;

static
void on_button_clicked()
{
  if(pDialog)
    pDialog->hide(); //hide() will cause main::run() to end.
}

int main (int argc, char **argv)
{
  Gtk::Main kit(argc, argv);

  //Load the GtkBuilder file and instantiate its widgets:
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
    refBuilder->add_from_file("basic.ui");
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
#else
  std::auto_ptr<Glib::Error> error;

  if (!refBuilder->add_from_file("basic.ui", error))
  {
    std::cerr << error->what() << std::endl;
    return 1;
  }
#endif /* !GLIBMM_EXCEPTIONS_ENABLED */

  //Get the GtkBuilder-instantiated Dialog:
  
  refBuilder->get_widget("DialogBasic", pDialog);
  if(pDialog)
  {
    //Get the GtkBuilder-instantiated Button, and connect a signal handler:
    Gtk::Button* pButton = 0;
    refBuilder->get_widget("quit_button", pButton);
    if(pButton)
    {
      pButton->signal_clicked().connect( sigc::ptr_fun(on_button_clicked) );
    }

    kit.run(*pDialog);
  }

  return 0;
}
