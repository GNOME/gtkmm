/* Drawing Area
 *
 * GtkDrawingArea is a blank area where you can draw custom displays
 * of various kinds.
 *
 * This demo has two drawing areas. The checkerboard area shows
 * how you can just draw something; all you have to do is write
 * a signal handler for draw, as shown here.
 *
 * The "scribble" area is a bit more advanced, and shows how to handle
 * events such as button presses and mouse motion. Click the mouse
 * and drag in the scribble area to draw squiggles. Resize the window
 * to clear the area.
 */

#include <gtkmm.h>

class Example_DrawingArea : public Gtk::Window
{
public:
  Example_DrawingArea();
  virtual ~Example_DrawingArea();

protected:
  //signal handlers:
  bool on_drawingarea_checkerboard_draw(const Cairo::RefPtr<Cairo::Context>& cr);
  bool on_drawingarea_scribble_draw(const Cairo::RefPtr<Cairo::Context>& cr);
  bool on_drawingarea_scribble_configure_event(GdkEventConfigure* event);
  bool on_drawingarea_scribble_motion_notify_event(GdkEventMotion* event);
  bool on_drawingarea_scribble_button_press_event(GdkEventButton* event);

  void scribble_draw_brush(int x, int y);

  //Member widgets:
  Gtk::Frame m_Frame_Checkerboard, m_Frame_Scribble;
  Gtk::Box m_VBox;
  Gtk::Label m_Label_Checkerboard, m_Label_Scribble;
  Gtk::DrawingArea m_DrawingArea_Checkerboard, m_DrawingArea_Scribble;

  Cairo::RefPtr<Cairo::Surface> m_surface;
};

//Called by DemoWindow;
Gtk::Window* do_drawingarea()
{
  return new Example_DrawingArea();
}

Example_DrawingArea::Example_DrawingArea()
:
  m_VBox(Gtk::ORIENTATION_VERTICAL, 8)
{
  set_title("Drawing Area");
  set_border_width(8);

  m_VBox.set_border_width(8);
  add(m_VBox);

  /*
   * Create the checkerboard area
   */
  m_Label_Checkerboard.set_markup("<u>Checkerboard pattern</u>");
  m_VBox.pack_start(m_Label_Checkerboard, Gtk::PACK_SHRINK);

  m_Frame_Checkerboard.set_shadow_type(Gtk::SHADOW_IN);
  m_VBox.pack_start(m_Frame_Checkerboard);

  /* set a minimum size */
  m_DrawingArea_Checkerboard.set_size_request(100, 100);
  m_Frame_Checkerboard.add(m_DrawingArea_Checkerboard);

  m_DrawingArea_Checkerboard.signal_draw().connect(
      sigc::mem_fun(*this, &Example_DrawingArea::on_drawingarea_checkerboard_draw));

  /*
   * Create the scribble area
   */
  m_Label_Scribble.set_markup("<u>Scribble area</u>");
  m_VBox.pack_start(m_Label_Scribble, Gtk::PACK_SHRINK);

  m_Frame_Scribble.set_shadow_type(Gtk::SHADOW_IN);
  m_VBox.pack_start(m_Frame_Scribble);

  /* set a minimum size */
  m_DrawingArea_Scribble.set_size_request(100, 100);
  m_Frame_Scribble.add(m_DrawingArea_Scribble);

  /* Signals used to handle backing pixmap */
  m_DrawingArea_Scribble.signal_draw().connect(
      sigc::mem_fun(*this, &Example_DrawingArea::on_drawingarea_scribble_draw));
  m_DrawingArea_Scribble.signal_configure_event().connect(
      sigc::mem_fun(*this, &Example_DrawingArea::on_drawingarea_scribble_configure_event));

  /* Event signals */
  m_DrawingArea_Scribble.signal_motion_notify_event().connect(
      sigc::mem_fun(*this, &Example_DrawingArea::on_drawingarea_scribble_motion_notify_event));
  m_DrawingArea_Scribble.signal_button_press_event().connect(
      sigc::mem_fun(*this, &Example_DrawingArea::on_drawingarea_scribble_button_press_event));

  /* Ask to receive events the drawing area doesn't normally
   * subscribe to.
   */
  m_DrawingArea_Scribble.add_events(Gdk::LEAVE_NOTIFY_MASK |
                                    Gdk::BUTTON_PRESS_MASK |
                                    Gdk::POINTER_MOTION_MASK |
                                    Gdk::POINTER_MOTION_HINT_MASK);
  show_all();
}

Example_DrawingArea::~Example_DrawingArea()
{
}

bool Example_DrawingArea::on_drawingarea_checkerboard_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  enum { CHECK_SIZE = 10, SPACING = 2 };

  /* At the start of a draw handler, a clip region has been set on
   * the Cairo context, and the contents have been cleared to the
   * widget's background color. The docs for
   * Gdk::Window::begin_paint_region() give more details on how this
   * works.
   */

  int xcount = 0;

  const int width = m_DrawingArea_Checkerboard.get_allocated_width();
  const int height = m_DrawingArea_Checkerboard.get_allocated_height();
  int i = SPACING;
  while (i < width)
  {
    int j = SPACING;
    int ycount = xcount % 2; /* start with even/odd depending on row */
    while (j < height)
    {
      if (ycount % 2)
        cr->set_source_rgb(0.45777, 0, 0.45777);
      else
        cr->set_source_rgb(1, 1, 1);

      /* If we're outside event->area, this will do nothing.
       * It might be mildly more efficient if we handled
       * the clipping ourselves, but again we're feeling lazy.
       */
      cr->rectangle(i, j, CHECK_SIZE, CHECK_SIZE);
      cr->fill();

      j += CHECK_SIZE + SPACING;
      ++ycount;
    }

    i += CHECK_SIZE + SPACING;
    ++xcount;
  }

  /* return true because we've handled this event, so no
   * further processing is required.
   */
  return true;
}

bool Example_DrawingArea::on_drawingarea_scribble_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  cr->set_source(m_surface, 0, 0); //TODO: Add =0 default parameters to cairomm.
  cr->paint();

  return false;
}

bool Example_DrawingArea::on_drawingarea_scribble_configure_event(GdkEventConfigure*)
{
  const Gtk::Allocation allocation = m_DrawingArea_Scribble.get_allocation();
  m_surface =
    m_DrawingArea_Scribble.get_window()->create_similar_surface(
      Cairo::CONTENT_COLOR, allocation.get_width(), allocation.get_height());
  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_surface);
  cr->set_source_rgb(1, 1, 1);
  cr->paint();

  /* We've handled the configure event, no need for further processing. */
  return true;
}

bool Example_DrawingArea::on_drawingarea_scribble_motion_notify_event(GdkEventMotion* event)
{
  if(!m_surface)
    return false; // paranoia check, in case we haven't gotten a configure event

  /* This call is very important; it requests the next motion event.  If you
   * don't call Gdk::Window::get_device_position() you'll only get a single motion
   * event.  The reason is that we specified Gdk::POINTER_MOTION_HINT_MASK to
   * Gtk::Widget::add_events().  If we hadn't specified that, we could just use
   * event->x, event->y as the pointer location. But we'd also get deluged in
   * events.  By requesting the next event as we handle the current one, we
   * avoid getting a huge number of events faster than we can cope.
   */
  if(event && event->window)
  {
    const Glib::RefPtr<Gdk::Window> refWindow =
        Glib::wrap(event->window, true); // true == take_copy

    if(refWindow)
    {
      int x = 0, y = 0;
      Gdk::ModifierType state = Gdk::ModifierType(0);
      const Glib::RefPtr<const Gdk::Device> device =
        Glib::wrap(event->device, true); // true == take_copy
      refWindow->get_device_position(device, x, y, state);

      if((state & Gdk::BUTTON1_MASK) != 0)
        scribble_draw_brush(x, y);
    }
  }

  // We've handled it, stop processing.
  return true;
}

bool Example_DrawingArea::on_drawingarea_scribble_button_press_event(GdkEventButton* event)
{
  if(!m_surface)
    return false; // paranoia check, in case we haven't gotten a configure event

  if(event->button == 1)
    scribble_draw_brush(int(event->x), int(event->y));

  // We've handled the event, stop processing.
  return true;
}

/* Draw a rectangle on the screen.
 */
void Example_DrawingArea::scribble_draw_brush(int x, int y)
{
  const Gdk::Rectangle update_rect (x - 3, y - 3, 6, 6);

  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_surface);
  Gdk::Cairo::add_rectangle_to_path(cr, update_rect);
  cr->fill();

  // Now invalidate the affected region of the drawing area.
  m_DrawingArea_Scribble.get_window()->invalidate_rect(update_rect, false);
}
