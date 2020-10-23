#include <gtkmm.h>

class MyWindow : public Gtk::Window
{
public:
  MyWindow();
private:
  Gtk::Button b;
  Gtk::Box vbox;
};

MyWindow::MyWindow() :
  b("hello"),
  vbox(Gtk::Orientation::VERTICAL)
{
  set_child(vbox);
  b.set_expand(true);
  vbox.append(b);
}

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create();
  return app->make_window_and_run<MyWindow>(argc, argv);
}
