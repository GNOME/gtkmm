#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/main.h>

class AppWindow
    : public Gtk::Window
{
public:
    AppWindow ();

private:
    void on_button_clicked();

    Gtk::Label* m_label;
};

AppWindow::AppWindow()
    : m_label (nullptr)
{
    Gtk::Box* vbox = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 5);
    add(*vbox);

    Gtk::Button* button = Gtk::make_managed<Gtk::Button>("Delete Label");
    vbox->pack_start(*button, Gtk::PACK_SHRINK);

    //m_label = Gtk::make_managed<Gtk::Label>("test");
    m_label = new Gtk::Label ("test");
    g_warning("m_label -> ref_count: %d\n", G_OBJECT(m_label->gobj())->ref_count);
    vbox->pack_start(*m_label, Gtk::PACK_SHRINK);
    g_warning("m_label -> ref_count: %d\n", G_OBJECT(m_label->gobj())->ref_count);

    button->signal_clicked ().connect( sigc::mem_fun(*this, &AppWindow::on_button_clicked) );

    show_all_children();
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
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv);
  AppWindow window;
  return app->run(window);
}
