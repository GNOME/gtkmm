/* Gestures
 *
 * Perform gestures on touchscreens and other input devices. This
 * demo reacts to long presses and swipes from all devices, plus
 * multi-touch rotate and zoom gestures from touchscreens.
 */

#include <gtkmm.h>

class Example_Gestures : public Gtk::Window
{
public:
  Example_Gestures();
  virtual ~Example_Gestures();

protected:

  // Signal handlers:
  bool on_drawing_area_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr);
  void on_gesture_swipe_swipe(double velocity_x, double velocity_y);
  void on_gesture_long_press_pressed(double x, double y);
  void on_gesture_long_press_end(GdkEventSequence* sequence);
  void on_gesture_rotate_angle_changed(double angle, double angle_delta);
  void on_gesture_zoom_scale_changed(double scale);

  // Child widget:
  Gtk::DrawingArea m_DrawingArea;

  // Gestures:
  Glib::RefPtr<Gtk::GestureSwipe> m_GestureSwipe;
  Glib::RefPtr<Gtk::GestureLongPress> m_GestureLongPress;
  Glib::RefPtr<Gtk::GestureRotate> m_GestureRotate;
  Glib::RefPtr<Gtk::GestureZoom> m_GestureZoom;

  double m_swipe_x;
  double m_swipe_y;
  bool m_long_pressed;
};


Gtk::Window* do_gestures()
{
  return new Example_Gestures();
}

Example_Gestures::Example_Gestures()
:
  m_DrawingArea(),
  m_swipe_x(0.0), m_swipe_y(0.0), m_long_pressed(false)
{
  set_title("Gestures demo");
  set_default_size(400, 400);

  add(m_DrawingArea);
  m_DrawingArea.add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK |
                           Gdk::POINTER_MOTION_MASK | Gdk::TOUCH_MASK);
  m_DrawingArea.signal_draw().connect(sigc::mem_fun(*this, &Example_Gestures::on_drawing_area_draw));

  // Create gestures.
  m_GestureSwipe = Gtk::GestureSwipe::create(m_DrawingArea);
  m_GestureSwipe->set_propagation_phase(Gtk::PHASE_BUBBLE);
  m_GestureSwipe->signal_swipe().connect(sigc::mem_fun(*this, &Example_Gestures::on_gesture_swipe_swipe));
  m_GestureSwipe->set_touch_only(false);

  m_GestureLongPress = Gtk::GestureLongPress::create(m_DrawingArea);
  m_GestureLongPress->set_propagation_phase(Gtk::PHASE_BUBBLE);
  m_GestureLongPress->signal_pressed().connect(sigc::mem_fun(*this, &Example_Gestures::on_gesture_long_press_pressed));
  m_GestureLongPress->signal_end().connect(sigc::mem_fun(*this, &Example_Gestures::on_gesture_long_press_end));
  m_GestureLongPress->set_touch_only(false);

  m_GestureRotate = Gtk::GestureRotate::create(m_DrawingArea);
  m_GestureRotate->set_propagation_phase(Gtk::PHASE_BUBBLE);
  m_GestureRotate->signal_angle_changed().connect(sigc::mem_fun(*this, &Example_Gestures::on_gesture_rotate_angle_changed));

  m_GestureZoom = Gtk::GestureZoom::create(m_DrawingArea);
  m_GestureZoom->set_propagation_phase(Gtk::PHASE_BUBBLE);
  m_GestureZoom->signal_scale_changed().connect(sigc::mem_fun(*this, &Example_Gestures::on_gesture_zoom_scale_changed));

  show_all();
}

Example_Gestures::~Example_Gestures()
{
}

bool Example_Gestures::on_drawing_area_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr)
{
  Gtk::Allocation allocation = m_DrawingArea.get_allocation();

  // Coordinates for the center of the window
  const int xc = allocation.get_width() / 2;
  const int yc = allocation.get_height() / 2;

  if (m_GestureRotate->is_recognized() || m_GestureZoom->is_recognized())
  {
    Cairo::Matrix matrix = Cairo::translation_matrix(xc, yc);
    cr->save();

    const double angle = m_GestureRotate->get_angle_delta();
    matrix.rotate(angle);

    const double scale = m_GestureZoom->get_scale_delta();
    matrix.scale(scale, scale);

    cr->set_matrix(matrix);
    cr->rectangle(-100, -100, 200, 200);

    ::Cairo::RefPtr<Cairo::LinearGradient> pattern = Cairo::LinearGradient::create(-100, 0, 200, 0);
    pattern->add_color_stop_rgb(0, 0, 0, 1);
    pattern->add_color_stop_rgb(1, 1, 0, 0);
    cr->set_source(pattern);
    cr->fill();
    cr->restore();
  }

  if (m_swipe_x != 0.0 || m_swipe_y != 0.0)
  {
    cr->save();
    cr->set_line_width(6);
    cr->move_to(xc, yc);
    cr->rel_line_to(m_swipe_x, m_swipe_y);
    cr->set_source_rgba(1.0, 0.0, 0.0, 0.5);
    cr->stroke();
    cr->restore();
  }

  if (m_long_pressed)
  {
    cr->save();
    cr->arc(xc, yc, 50, 0, 2 * G_PI);
    cr->set_source_rgba(0.0, 1.0, 0.0, 0.5);
    cr->stroke();
    cr->restore();
  }

  return true;
}

void Example_Gestures::on_gesture_swipe_swipe(double velocity_x, double velocity_y)
{
  m_swipe_x = 0.2 * velocity_x;
  m_swipe_y = 0.2 * velocity_y;
  m_DrawingArea.queue_draw();
}

void Example_Gestures::on_gesture_long_press_pressed(double /* x */, double /* y */)
{
  m_long_pressed = true;
  m_DrawingArea.queue_draw();
}

void Example_Gestures::on_gesture_long_press_end(GdkEventSequence* /* sequence */)
{
  m_long_pressed = false;
  m_DrawingArea.queue_draw();
}

void Example_Gestures::on_gesture_rotate_angle_changed(double /* angle */, double /* angle_delta */)
{
  m_DrawingArea.queue_draw();
}

void Example_Gestures::on_gesture_zoom_scale_changed(double /* scale */)
{
  m_DrawingArea.queue_draw();
}
