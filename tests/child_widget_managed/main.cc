#include <gtkmm.h>

class MyButton : public Gtk::Button
{
public:
    MyButton();
    ~MyButton() override;
};

MyButton::MyButton()
: Gtk::Button("Ok", true)
{ }

MyButton::~MyButton()
{
    g_warning("MyButtom::~MyButton()");
}

class ExampleWindow : public Gtk::Window
{
public:
    ExampleWindow();
    ~ExampleWindow() override;

protected:

    MyButton* m_button;
};

ExampleWindow::ExampleWindow()
{
    set_default_size(150, 150);

    m_button = Gtk::make_managed<MyButton>();
    set_child(*m_button);
}

ExampleWindow::~ExampleWindow()
{
  g_warning("ExampleWindow::~ExampleWindow()");
}


int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create();
  return app->make_window_and_run<ExampleWindow>(argc, argv);
}
