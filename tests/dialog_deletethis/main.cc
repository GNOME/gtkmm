#include <gtkmm.h>
#include <iostream>

Glib::RefPtr<Gtk::Application> app;

//This is _not_ a good example of coding with gtkmm.
class Dlg : public sigc::trackable
{
  public:
    Dlg()
    {
      dlg_ = new Gtk::Dialog("Test Dialog");
      Gtk::Button *btn = manage(new Gtk::Button("ClickMe"));
      btn->signal_clicked().connect(sigc::mem_fun(*this, &Dlg::on_button_clicked));
      dlg_->get_content_area()->pack_start(*btn);
      dlg_->add_button("_OK", Gtk::RESPONSE_OK);
      dlg_->signal_response().connect(sigc::mem_fun(*this, &Dlg::on_response));
      dlg_->show_all();
    }

    ~Dlg()
    {
      delete dlg_;
    }

    void on_button_clicked()
    {
      std::cout << "button clicked" << std::endl;
    }

    void on_response(int id)
   {
      if (id == Gtk::RESPONSE_OK || id == Gtk::RESPONSE_DELETE_EVENT)
        quit();
    }

    void quit() {
      delete this; //This is _not_ a good example of coding with gtkmm.
      app->quit();
    }

  private:
    Gtk::Dialog *dlg_;
};

int main (int argc, char **argv)
{
  app = Gtk::Application::create(argc, argv);

  new Dlg(); //Not a Gtk::Dialog - it creates one in its constructor.

  app->hold();
  return app->run();
}

  
