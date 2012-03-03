#include <gtkmm.h>
#include <iostream>

void on_property_color_changed()
{
  std::cout << "color property changed" << std::endl;
}

void on_property_color_changed_nicer_api()
{
  std::cout << "color property changed (nicer API)" << std::endl;
}

void on_property_name_changed()
{
  //Check that we don't get notification of the wrong property:
  std::cout << "name property changed" << std::endl;
}

int main (int argc, char **argv)
{
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.test");

  Gtk::Window window;

  Gtk::ColorButton button;
  button.show();

  button.connect_property_changed("color", sigc::ptr_fun(&on_property_color_changed));

  button.property_color().signal_changed().connect(sigc::ptr_fun(&on_property_color_changed_nicer_api));

  button.connect_property_changed("name", sigc::ptr_fun(&on_property_name_changed));


  window.add(button);

  return app->run(window);
}
