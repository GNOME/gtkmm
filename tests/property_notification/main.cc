#include <gtkmm.h>
#include <iostream>

void on_property_text_changed()
{
  std::cout << "text property changed" << std::endl;
}

void on_property_text_changed_nicer_api()
{
  std::cout << "text property changed (nicer API)" << std::endl;
}

void on_property_editable_changed()
{
  //Check that we don't get notification of the wrong property:
  std::cout << "editable property changed (should not happen)" << std::endl;
}

class TestWindow : public Gtk::Window
{
public:
  TestWindow()
  {
    set_default_size(200, 100);

    m_label.connect_property_changed("text", sigc::ptr_fun(&on_property_text_changed));
    m_label.property_text().signal_changed().connect(sigc::ptr_fun(&on_property_text_changed_nicer_api));
    m_label.connect_property_changed("editable", sigc::ptr_fun(&on_property_editable_changed));
    m_label.set_halign(Gtk::Align::CENTER);
    m_label.set_valign(Gtk::Align::CENTER);

    set_child(m_label);
  }

protected:
  Gtk::EditableLabel m_label {"Editable text"};
};

int main (int argc, char **argv)
{
  auto app = Gtk::Application::create();
  return app->make_window_and_run<TestWindow>(argc, argv);
}
