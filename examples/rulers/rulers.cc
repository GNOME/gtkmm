#include <gtkmm/main.h>
#include <gtkmm/table.h>
#include <gtkmm/window.h>
#include <gtkmm/ruler.h>
#include <gtkmm/drawingarea.h>

// Gtk-- version of the "rulers" example from the gtk+ tutorial

class Rulers : public Gtk::Window
{
public:
  Rulers();

protected:

  //signal handlers:
  virtual bool on_area_motion_notify_event(GdkEventMotion* event); //override

  Gtk::Table m_table;
  Gtk::DrawingArea m_area;
  Gtk::HRuler m_hrule;
  Gtk::VRuler m_vrule;

  static const int XSIZE = 600, YSIZE = 400;
};

Rulers::Rulers() :
  m_table(3, 2, false)
{
  set_border_width(10);
  add(m_table);
  
  m_area.set_size_request(XSIZE, YSIZE);
  
  m_table.attach(m_area, 1,2,1,2,
		 Gtk::EXPAND | Gtk::FILL , Gtk::FILL, 0, 0);
  
  m_area.set_events(Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK );

  //Connect a signal handler for the DrawingArea's "motion_notify_event" signal, to detect cursor movement:
  m_area.signal_motion_notify_event().connect( sigc::mem_fun(*this, &Rulers::on_area_motion_notify_event) );

  // The horizontal ruler goes on top:
  m_hrule.set_metric(Gtk::PIXELS);
  m_hrule.set_range(0, XSIZE, 10, XSIZE );  //C example uses 7, 13, 0, 20 - don't know why.

  m_table.attach(m_hrule, 1,2,0,1,
		 Gtk::EXPAND | Gtk::SHRINK | Gtk::FILL, Gtk::FILL,
		 0, 0);

  // Vertical ruler:
  m_vrule.set_metric(Gtk::PIXELS);
  m_vrule.set_range(0, YSIZE, 10, YSIZE );

  m_table.attach(m_vrule, 0, 1, 1, 2,
		 Gtk::FILL, Gtk::EXPAND | Gtk::SHRINK | Gtk::FILL, 0, 0 );

  show_all_children();
}

bool Rulers::on_area_motion_notify_event(GdkEventMotion* event)
{
  //The cursor was moved in the m_area widget.
  //Show the position in the rulers:

  if(event)
  {
#ifdef GLIBMM_PROPERTIES_ENABLED
    m_hrule.property_position().set_value(event->x);
    m_vrule.property_position().set_value(event->y);
#else
  Glib::Value<double> property_value;
  property_value.init(Glib::Value<double>::value_type());

  property_value.set(event->x);
  m_hrule.set_property_value("position", property_value);

  property_value.set(event->y);
  m_vrule.set_property_value("position", property_value);
#endif
  }

  return false;  //false = signal not fully handled, pass it on..
}

int main (int argc, char *argv[])
{
  Gtk::Main myapp(argc, argv);

  Rulers rulers;

  Gtk::Main::run(rulers);
  return 0;
}

