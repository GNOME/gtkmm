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
  ~Example_Gestures() override;

protected:
  void on_drawing_area_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr, int width, int height);

  // Signal handlers:
  void on_gesture_swipe_swipe(double velocity_x, double velocity_y);
  void on_gesture_long_press_pressed(double x, double y);
  void on_gesture_long_press_end(Gdk::EventSequence* sequence);
  void on_gesture_rotate_angle_changed(double angle, double angle_delta);
  void on_gesture_zoom_scale_changed(double scale);

  // Child widget:
  Gtk::DrawingArea m_DrawingArea;

  // Gestures:
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

  set_child(m_DrawingArea);
  m_DrawingArea.set_draw_func(sigc::mem_fun(*this, &Example_Gestures::on_drawing_area_draw));

  // Create gestures.
  auto swipe = Gtk::GestureSwipe::create();
  swipe->set_propagation_phase(Gtk::PropagationPhase::BUBBLE);
  swipe->signal_swipe().connect(sigc::mem_fun(*this, &Example_Gestures::on_gesture_swipe_swipe));
  swipe->set_touch_only(false);
  m_DrawingArea.add_controller(swipe);

  auto long_press = Gtk::GestureLongPress::create();
  long_press->set_propagation_phase(Gtk::PropagationPhase::BUBBLE);
  long_press->signal_pressed().connect(sigc::mem_fun(*this, &Example_Gestures::on_gesture_long_press_pressed));
  long_press->signal_end().connect(sigc::mem_fun(*this, &Example_Gestures::on_gesture_long_press_end));
  long_press->set_touch_only(false);
  m_DrawingArea.add_controller(long_press);

  m_GestureRotate = Gtk::GestureRotate::create();
  m_GestureRotate->set_propagation_phase(Gtk::PropagationPhase::BUBBLE);
  m_GestureRotate->signal_angle_changed().connect(sigc::mem_fun(*this, &Example_Gestures::on_gesture_rotate_angle_changed));
  m_DrawingArea.add_controller(m_GestureRotate);

  m_GestureZoom = Gtk::GestureZoom::create();
  m_GestureZoom->set_propagation_phase(Gtk::PropagationPhase::BUBBLE);
  m_GestureZoom->signal_scale_changed().connect(sigc::mem_fun(*this, &Example_Gestures::on_gesture_zoom_scale_changed));
  m_DrawingArea.add_controller(m_GestureZoom);
}

Example_Gestures::~Example_Gestures()
{
}

void Example_Gestures::on_drawing_area_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr,
  int width, int height)
{
  // Coordinates for the center of the window
  const int xc = width / 2;
  const int yc = height / 2;

  if (m_GestureRotate->is_recognized() || m_GestureZoom->is_recognized())
  {
    auto matrix = Cairo::translation_matrix(xc, yc);
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

void Example_Gestures::on_gesture_long_press_end(Gdk::EventSequence* /* sequence */)
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
