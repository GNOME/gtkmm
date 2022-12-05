#include <gtkmm.h>
#include <iostream>

Glib::RefPtr<Gtk::Application> app;

//This is _not_ a good example of coding with gtkmm.
class Dlg : public sigc::trackable
{
  public:
    Dlg()
    {
      // Gtk::Dialog is deprecated since 4.10.
      // A class that derives from Gtk::Window can act as a dialog.
      dlg_ = new Gtk::Window();
      dlg_->set_title("Test Dialog");
      dlg_->set_hide_on_close();
      auto vBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
      dlg_->set_child(*vBox);
      auto btn = Gtk::make_managed<Gtk::Button>("ClickMe");
      btn->signal_clicked().connect(sigc::mem_fun(*this, &Dlg::on_button_clicked));
      btn->set_expand(true);
      vBox->append(*btn);
      vBox->append(*Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::HORIZONTAL));
      auto hBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
      hBox->set_halign(Gtk::Align::END);
      vBox->append(*hBox);
      btn = Gtk::make_managed<Gtk::Button>("OK");
      hBox->append(*btn);
      btn->signal_clicked().connect(sigc::mem_fun(*this, &Dlg::on_response));
      dlg_->signal_hide().connect(sigc::mem_fun(*this, &Dlg::on_response));
      dlg_->set_visible(true);
    }

    ~Dlg()
    {
      delete dlg_;
    }

    void on_button_clicked()
    {
      std::cout << "button clicked" << std::endl;
    }

    void on_response()
    {
      delete this; //This is _not_ a good example of coding with gtkmm.
      app->quit();
    }

  private:
    Gtk::Window* dlg_;
};

int main (int argc, char** argv)
{
  app = Gtk::Application::create();
  app->register_application();

  new Dlg(); //Not a Gtk::Window - it creates one in its constructor.

  app->hold();
  return app->run(argc, argv);
}
