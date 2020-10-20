#include <gtkmm.h>
#include <gtk/gtk.h>
#include <iostream>
#include <list>


class MyDialog : public Gtk::Dialog {
public:
  MyDialog()
   {
     add_button("Ok", 0);
   }
};

class MyWindow : public Gtk::Window
{
public:
  MyWindow();

  void on_button_clicked();
  void on_dialog_response(int response_id);

protected:
  Gtk::Box m_Box;
  Gtk::Button m_Button;
  std::unique_ptr<MyDialog> m_Dialog;
};

MyWindow::MyWindow()
: m_Box(Gtk::Orientation::HORIZONTAL),
  m_Button("Show Dialog")
{
  set_size_request(200, 200);

  m_Button.signal_clicked().connect( sigc::mem_fun(*this, &MyWindow::on_button_clicked) );
  m_Button.set_expand(true);
  m_Box.append(m_Button);
  set_child(m_Box);
}

void MyWindow::on_button_clicked()
{
  m_Dialog.reset(nullptr);
  std::cout << "before list_toplevels 1" << std::endl;
  std::vector<Gtk::Window*> toplevelwindows = list_toplevels();
  std::cout << "after list_toplevels" << std::endl;
  std::cout << "toplevelwindows.size = " << toplevelwindows.size() << std::endl;

  m_Dialog.reset(new MyDialog);
  m_Dialog->set_transient_for(*this);
  m_Dialog->set_modal();
  m_Dialog->set_hide_on_close();
  m_Dialog->signal_response().connect(sigc::mem_fun(*this, &MyWindow::on_dialog_response));
  m_Dialog->show();
  std::cout << "After m_Dialog->show()" << std::endl;
}

void MyWindow::on_dialog_response(int /* response_id */)
{
  std::cout << "before list_toplevels 2" << std::endl;
  std::vector<Gtk::Window*> toplevelwindows = list_toplevels();
  std::cout << "after list_toplevels" << std::endl;
  std::cout << "toplevelwindows.size = " << toplevelwindows.size() << std::endl;
  m_Dialog->hide();
}

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create();
  return app->make_window_and_run<MyWindow>(argc, argv);
}
