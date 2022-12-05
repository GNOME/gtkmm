#include <gtkmm.h>
#include <iostream>

// Gtk::Dialog is deprecated since 4.10.
// A class that derives from Gtk::Window can act as a dialog.
class MyDialog : public Gtk::Window
{
public:
  MyDialog()
  : m_ButtonBox(Gtk::Orientation::HORIZONTAL),
    m_ButtonOK("OK")
  {
    set_child(m_ButtonBox);
    m_ButtonBox.append(m_ButtonOK);
    m_ButtonBox.set_halign(Gtk::Align::END);
  }
  Gtk::Button& get_button_ok()
  {
    return m_ButtonOK;
  }
protected:
  Gtk::Box m_ButtonBox;
  Gtk::Button m_ButtonOK;
};

class MyWindow : public Gtk::Window
{
public:
  MyWindow();

  void on_button_clicked();
  void on_dialog_response();

protected:
  Gtk::Button m_Button;
  std::unique_ptr<MyDialog> m_Dialog;
};

MyWindow::MyWindow()
: m_Button("Show Dialog")
{
  set_size_request(150, 100);

  m_Button.signal_clicked().connect( sigc::mem_fun(*this, &MyWindow::on_button_clicked) );
  m_Button.set_expand(true);
  set_child(m_Button);
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
  m_Dialog->get_button_ok().signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_dialog_response));
  m_Dialog->signal_hide().connect(sigc::mem_fun(*this, &MyWindow::on_dialog_response));
  m_Dialog->set_visible(true);
  std::cout << "After m_Dialog->set_visible(true)" << std::endl;
}

void MyWindow::on_dialog_response()
{
  if (m_Dialog->is_visible())
    m_Dialog->set_visible(false);
  else
  {
    std::cout << "before list_toplevels 2" << std::endl;
    std::vector<Gtk::Window*> toplevelwindows = list_toplevels();
    std::cout << "after list_toplevels" << std::endl;
    std::cout << "toplevelwindows.size = " << toplevelwindows.size() << std::endl;
  }
}

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create();
  return app->make_window_and_run<MyWindow>(argc, argv);
}
