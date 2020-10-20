#include <gtkmm/application.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

class AppWindow
    : public Gtk::Window
{
public:
    AppWindow();

private:
    void on_button_clicked();

    Gtk::Label* m_label;
};

AppWindow::AppWindow()
    : m_label (nullptr)
{
    auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 5);
    set_child(*vbox);

    auto button = Gtk::make_managed<Gtk::Button>("Delete Label");
    vbox->append(*button);

    //m_label = Gtk::make_managed<Gtk::Label>("test");
    m_label = new Gtk::Label("test");
    g_warning("m_label -> ref_count: %d\n", G_OBJECT(m_label->gobj())->ref_count);
    vbox->append(*m_label);
    g_warning("m_label -> ref_count: %d\n", G_OBJECT(m_label->gobj())->ref_count);

    button->signal_clicked().connect( sigc::mem_fun(*this, &AppWindow::on_button_clicked));
}

void AppWindow::on_button_clicked()
{
  if(m_label)
  {
    g_warning("AppWindow::on_button_clicked(): label refcount=%d", G_OBJECT(m_label->gobj())->ref_count);
    delete m_label;
    m_label = nullptr;
  }
}

int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create();
  return app->make_window_and_run<AppWindow>(argc, argv);
}
