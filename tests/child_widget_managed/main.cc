#include <gtkmm.h>

class MyButton : public Gtk::Button
{
public:
    MyButton();
    virtual ~MyButton();
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
    virtual ~ExampleWindow();

protected:
    virtual void on_button_clicked();

    MyButton* m_button;
};

ExampleWindow::ExampleWindow()
{
    set_default_size(150, 150);

    m_button = manage(new MyButton);
    add(*m_button);

    sigc::connection con = m_button->signal_clicked().connect( sigc::mem_fun(*this, &ExampleWindow::on_button_clicked) ); 
    con.disconnect();
	
    show_all_children();
}

ExampleWindow::~ExampleWindow()
{
  g_warning("ExampleWindow::~ExampleWindow()");
}

void ExampleWindow::on_button_clicked()
{
  g_warning("Button clicked.");
}

int main(int argc, char* argv[])
{
    Gtk::Main kit(argc, argv);
    ExampleWindow window;
    kit.run(window);
    return 0;
}
