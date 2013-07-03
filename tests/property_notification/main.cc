#include <gtkmm.h>
#include <iostream>

void on_property_rgba_changed()
{
  std::cout << "rgba property changed" << std::endl;
}

void on_property_rgba_changed_nicer_api()
{
  std::cout << "rgba property changed (nicer API)" << std::endl;
}

void on_property_name_changed()
{
  //Check that we don't get notification of the wrong property:
  std::cout << "name property changed" << std::endl;
}

int main (int argc, char **argv)
{
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv);

  Gtk::Window window;

  Gtk::ColorButton button;
  button.show();

  button.connect_property_changed("rgba", sigc::ptr_fun(&on_property_rgba_changed));

  button.property_rgba().signal_changed().connect(sigc::ptr_fun(&on_property_rgba_changed_nicer_api));

  button.connect_property_changed("name", sigc::ptr_fun(&on_property_name_changed));


  window.add(button);

  return app->run(window);
}
