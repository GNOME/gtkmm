
#include <iostream>
#include <sigc++/class_slot.h>
#include <glibmm/convert.h>
#include <glibmm/exceptionhandler.h>
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>


namespace
{

class MyButton : public Gtk::Button
{
public:
  explicit MyButton(const Glib::ustring& label);

protected:
  virtual void on_clicked(); // signal handler
};

class MyException1 {};
class MyException2 {};
class MyException3 {};


MyButton::MyButton(const Glib::ustring& label)
:
  Gtk::Button(label)
{}

void MyButton::on_clicked()
{
  std::cout << "The Button was clicked.\n";
  throw MyException1();
}

void global_on_clicked()
{
  std::cout << "The Button was clicked.\n";
  throw MyException2();
}

void global_on_clicked_throw_glib_error()
{
  std::cout << "The Button was clicked.\n";
  Glib::locale_from_utf8("Und tschüss!"); // invalid UTF-8
}

void global_on_clicked_throw_std_exception()
{
  std::cout << "The Button was clicked.\n";
  Glib::ustring str;
  str.at(3); // out of range
}

void handler1()
{
  std::cout << "exception handler 1\n";

  try 
  {
    throw; // rethrow exception
  }
  catch(MyException1&)
  {
    std::cout << "caught MyException1\n";
  }
  // if not handled it gets passed to next handler
}

void handler2()
{
  std::cout << "exception handler 2\n";

  try
  {
    throw; // rethrow exception
  } 
  catch(MyException2&)
  {
    std::cout << "caught MyException2\n";
  }
  // if not handled it gets passed to next handler
}

} // anonymous namespace


int main(int argc, char** argv)
{
  // New exception handlers are inserted at the front of the per-thread
  // handler list.  Thus, in this example handler2() is executed before
  // handler1().
  SigC::Connection conn_handler1 = Glib::add_exception_handler(&handler1);
  SigC::Connection conn_handler2 = Glib::add_exception_handler(&handler2);

  Gtk::Main main_instance (&argc, &argv);

  Gtk::Window window;
  window.set_title("Exception Handlers");
  window.set_border_width(10);

  Gtk::Box *const box = new Gtk::VBox(true, 5);
  window.add(*Gtk::manage(box));

  Gtk::Button *const button1 = new MyButton("From virtual method");
  box->add(*Gtk::manage(button1));
  Gtk::Button *const button2 = new Gtk::Button("From signal handler");
  box->add(*Gtk::manage(button2));
  Gtk::Button *const button3 = new Gtk::Button("Unhandled Glib::Error");
  box->add(*Gtk::manage(button3));
  Gtk::Button *const button4 = new Gtk::Button("Unhandled std::exception (crash!)");
  box->add(*Gtk::manage(button4));
  Gtk::Button *const button5 = new Gtk::Button("Disconnect handler 1");
  box->add(*Gtk::manage(button5));
  Gtk::Button *const button6 = new Gtk::Button("Disconnect handler 2");
  box->add(*Gtk::manage(button6));

  button2->signal_clicked().connect(&global_on_clicked);
  button3->signal_clicked().connect(&global_on_clicked_throw_glib_error);
  button4->signal_clicked().connect(&global_on_clicked_throw_std_exception);
  button5->signal_clicked().connect(SigC::slot_class(conn_handler1, &SigC::Connection::disconnect));
  button6->signal_clicked().connect(SigC::slot_class(conn_handler2, &SigC::Connection::disconnect));

  window.show_all_children();
  Gtk::Main::run(window);

  return 0;
}

