/* Drawing Area
 *
 * GtkDrawingArea is a blank area where you can draw custom displays
 * of various kinds.
 *
 * This demo has two drawing areas. The checkerboard area shows
 * how you can just draw something; all you have to do is write
 * a signal handler for expose_event, as shown here.
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
  bool on_drawingarea_checkerboard_expose_event(GdkEventExpose* event);
  bool on_drawingarea_scribble_expose_event(GdkEventExpose* event);
  bool on_drawingarea_scribble_configure_event(GdkEventConfigure* event);
  bool on_drawingarea_scribble_motion_notify_event(GdkEventMotion* event);
  bool on_drawingarea_scribble_button_press_event(GdkEventButton* event);

  void scribble_draw_brush(int x, int y);

  //Member widgets:
  Gtk::Frame m_Frame_Checkerboard, m_Frame_Scribble;
  Gtk::VBox m_VBox;
  Gtk::Label m_Label_Checkerboard, m_Label_Scribble;
  Gtk::DrawingArea m_DrawingArea_Checkerboard, m_DrawingArea_Scribble;

  Glib::RefPtr<Gdk::Pixmap> m_refPixmap_Scribble;
};

//Called by DemoWindow;
Gtk::Window* do_drawingarea()
{
  return new Example_DrawingArea();
}

Example_DrawingArea::Example_DrawingArea()
:
  m_VBox(false, 8)
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

  m_DrawingArea_Checkerboard.signal_expose_event().connect(
      sigc::mem_fun(*this, &Example_DrawingArea::on_drawingarea_checkerboard_expose_event));

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
  m_DrawingArea_Scribble.signal_expose_event().connect(
      sigc::mem_fun(*this, &Example_DrawingArea::on_drawingarea_scribble_expose_event));
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

bool Example_DrawingArea::on_drawingarea_checkerboard_expose_event(GdkEventExpose*)
{
  enum { CHECK_SIZE = 10, SPACING = 2 };

  /* At the start of an expose handler, a clip region of event->area
   * is set on the window, and event->area has been cleared to the
   * widget's background color. The docs for
   * gdk_window_begin_paint_region() give more details on how this
   * works.
   */

  /* It would be a bit more efficient to keep these
   * GC's around instead of recreating on each expose, but
   * this is the lazy/slow way.
   */
  Glib::RefPtr<Gdk::GC> refGC1 = Gdk::GC::create(m_DrawingArea_Checkerboard.get_window());
  Gdk::Color color;
  color.set_red(30000);
  color.set_green(0);
  color.set_blue(30000);
  refGC1->set_rgb_fg_color(color);

  Glib::RefPtr<Gdk::GC> refGC2 = Gdk::GC::create(m_DrawingArea_Checkerboard.get_window());
  color.set_red(65535);
  color.set_green(65535);
  color.set_blue(65535);
  refGC2->set_rgb_fg_color(color);

  gint xcount = 0;
  gint i = SPACING;
  while (i < m_DrawingArea_Checkerboard.get_allocation().width)
  {
    gint j = SPACING;
    gint ycount = xcount % 2; /* start with even/odd depending on row */
    while (j < m_DrawingArea_Checkerboard.get_allocation().height)
    {
      Glib::RefPtr<Gdk::GC> refGC;
    	
      if (ycount % 2)
        refGC = refGC1;
      else
        refGC = refGC2;

      /* If we're outside event->area, this will do nothing.
       * It might be mildly more efficient if we handled
       * the clipping ourselves, but again we're feeling lazy.
       */
      m_DrawingArea_Checkerboard.get_window()->draw_rectangle(refGC,
    		      true,
    		      i, j,
    		      CHECK_SIZE, CHECK_SIZE);

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

bool Example_DrawingArea::on_drawingarea_scribble_expose_event(GdkEventExpose* event)
{
  /* We use the "foreground GC" for the widget since it already exists,
   * but honestly any GC would work. The only thing to worry about
   * is whether the GC has an inappropriate clip region set.
   */
  m_DrawingArea_Scribble.get_window()->draw_drawable(
      m_DrawingArea_Scribble.get_style()->get_fg_gc(m_DrawingArea_Scribble.get_state()),
      m_refPixmap_Scribble,
      // Only copy the area that was exposed:
      event->area.x, event->area.y,
      event->area.x, event->area.y,
      event->area.width, event->area.height);

  return false;
}

bool Example_DrawingArea::on_drawingarea_scribble_configure_event(GdkEventConfigure*)
{
  m_refPixmap_Scribble = Gdk::Pixmap::create(
      m_DrawingArea_Scribble.get_window(),
      m_DrawingArea_Scribble.get_allocation().width,
      m_DrawingArea_Scribble.get_allocation().height,
      -1);

  /* Initialize the pixmap to white */
  m_refPixmap_Scribble->draw_rectangle(
      m_DrawingArea_Scribble.get_style()->get_white_gc(),
      true,
      0, 0,
      m_DrawingArea_Scribble.get_allocation().width,
      m_DrawingArea_Scribble.get_allocation().height);

  /* We've handled the configure event, no need for further processing. */
  return true;
}

bool Example_DrawingArea::on_drawingarea_scribble_motion_notify_event(GdkEventMotion* event)
{
  if(!m_refPixmap_Scribble)
    return false; // paranoia check, in case we haven't gotten a configure event

  /* This call is very important; it requests the next motion event.  If you
   * don't call Gdk::Window::get_pointer() you'll only get a single motion
   * event.  The reason is that we specified Gdk::POINTER_MOTION_HINT_MASK to
   * Gtk::Widget::add_events().  If we hadn't specified that, we could just use
   * event->x, event->y as the pointer location. But we'd also get deluged in
   * events.  By requesting the next event as we handle the current one, we
   * avoid getting a huge number of events faster than we can cope.
   */
  if(event && event->window)
  {
    const Glib::RefPtr<Gdk::Window> refWindow =
        Glib::wrap((GdkWindowObject*) event->window, true); // true == take_copy

    if(refWindow)
    {
      int x = 0, y = 0;
      Gdk::ModifierType state = Gdk::ModifierType(0);

      refWindow->get_pointer(x, y, state);

      if((state & Gdk::BUTTON1_MASK) != 0)
        scribble_draw_brush(x, y);
    }
  }

  // We've handled it, stop processing.
  return true;
}

bool Example_DrawingArea::on_drawingarea_scribble_button_press_event(GdkEventButton* event)
{
  if(!m_refPixmap_Scribble)
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

  // Paint to the pixmap, where we store our state.
  //
  m_refPixmap_Scribble->draw_rectangle(
      m_DrawingArea_Scribble.get_style()->get_black_gc(),
      true,
      update_rect.get_x(), update_rect.get_y(),
      update_rect.get_width(), update_rect.get_height());

  // Now invalidate the affected region of the drawing area.
  m_DrawingArea_Scribble.get_window()->invalidate_rect(update_rect, false);
}

