#include <gtkmm/arrow.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/main.h>

class ArrowButton : public Gtk::Button
{
public:
   ArrowButton(Gtk::ArrowType,Gtk::ShadowType);
   virtual ~ArrowButton();
};

/* Create an Arrow widget with the specified parameters
 * and pack it into a button */
ArrowButton::ArrowButton(Gtk::ArrowType arrow_type,Gtk::ShadowType shadow_type)
  : Gtk::Button()
{
    Gtk::Arrow* arrow = SigC::manage (new Gtk::Arrow (arrow_type, shadow_type));
  add (*arrow);
}
  
ArrowButton::~ArrowButton()
{}

/* We will derive our new application window from window */
class AppWindow : public Gtk::Window
{
public:
  AppWindow();
  virtual ~AppWindow();
};

AppWindow::AppWindow()
{
  ArrowButton *button;
  Gtk::HBox    *box;

  set_title ("Arrow Buttons");

  /* Sets the border width of the window. */
  set_border_width (10);
  
  /* Create a box to hold the arrows/buttons */
  box=SigC::manage (new Gtk::HBox (false, 0));
  box->set_border_width (2);

  /* Pack and show all our widgets */
  button = SigC::manage (new ArrowButton (Gtk::ARROW_LEFT, Gtk::SHADOW_ETCHED_IN));
  box->pack_start (*button, Gtk::PACK_SHRINK, 3);

  button = SigC::manage(new ArrowButton (Gtk::ARROW_RIGHT, Gtk::SHADOW_ETCHED_IN));
  box->pack_start(*button, Gtk::PACK_SHRINK, 3);

  button = SigC::manage (new ArrowButton (Gtk::ARROW_LEFT, Gtk::SHADOW_ETCHED_OUT));
  box->pack_start (*button, Gtk::PACK_SHRINK, 3);

  button = SigC::manage (new ArrowButton (Gtk::ARROW_RIGHT, Gtk::SHADOW_ETCHED_OUT));
  box->pack_start (*button, Gtk::PACK_SHRINK, 3);
 
  add (*box);
  show_all ();
}

AppWindow::~AppWindow() {};

int main (int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);

  AppWindow arrows;
  Gtk::Main::run(arrows);
  return 0;
}
