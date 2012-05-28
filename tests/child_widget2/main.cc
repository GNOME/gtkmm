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
  vbox(Gtk::ORIENTATION_VERTICAL)
{
  add(vbox);
  vbox.pack_start(b);
  show_all_children();
}

int main (int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv);

  MyWindow window;
  return app->run(window);
}
