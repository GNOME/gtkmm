/* example-start arrow arrow.c */

#include <gtkmm/arrow.h>
#include <gtkmm/table.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/main.h>

class ArrowButton : public Gtk::Button
{
public:
   ArrowButton(Gtk::ArrowType,Gtk::ShadowType);
   ~ArrowButton();
};

/* Create an Arrow widget with the specified parameters
 * and pack it into a button */
ArrowButton::ArrowButton(Gtk::ArrowType arrow_type,Gtk::ShadowType shadow_type)
  : Gtk::Button()
{
  Gtk::Arrow* arrow = Gtk::manage (new Gtk::Arrow (arrow_type, shadow_type));
  add (*arrow);
}
  
ArrowButton::~ArrowButton() {};

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
  Gtk::Table   *table;

  set_title ("Arrow Buttons");

  /* Sets the border width of the window. */
  set_border_width (10);
  
  /* Create a box to hold the arrows/buttons */
  table= Gtk::manage (new Gtk::Table (3,3,true));
  table->set_border_width (2);

  /* Pack and show all our widgets */
  button = Gtk::manage (new ArrowButton (Gtk::ARROW_UP, Gtk::SHADOW_ETCHED_IN));
  table->attach (*button, 1, 2, 0, 1);

  button = Gtk::manage (new ArrowButton (Gtk::ARROW_LEFT, Gtk::SHADOW_ETCHED_IN));
  table->attach (*button, 0, 1, 1, 2);

  button = Gtk::manage (new ArrowButton (Gtk::ARROW_RIGHT, Gtk::SHADOW_ETCHED_IN));
  table->attach (*button, 2, 3, 1, 2);

  button = Gtk::manage (new ArrowButton (Gtk::ARROW_DOWN, Gtk::SHADOW_ETCHED_IN));
  table->attach (*button, 1, 2, 2, 3);

  table->set_row_spacing(0,5);
  table->set_row_spacing(1,5);

  table->set_col_spacing(0,5);
  table->set_col_spacing(1,5);
 
  add (*table);
  show_all ();
}

AppWindow::~AppWindow() {};

int main (int argc, char *argv[])
{
  Gtk::Main myapp(&argc, &argv);
  AppWindow arrows;

  Gtk::Main::run(arrows);
  return 0;
}

/* example-end */
