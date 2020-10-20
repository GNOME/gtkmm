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

class TestWindow : public Gtk::Window
{
public:
  TestWindow()
  {
    button.connect_property_changed("rgba", sigc::ptr_fun(&on_property_rgba_changed));
    button.property_rgba().signal_changed().connect(sigc::ptr_fun(&on_property_rgba_changed_nicer_api));
    button.connect_property_changed("name", sigc::ptr_fun(&on_property_name_changed));

    set_child(button);
  }

protected:
  Gtk::ColorButton button;
};

int main (int argc, char **argv)
{
  auto app = Gtk::Application::create();
  return app->make_window_and_run<TestWindow>(argc, argv);
}
