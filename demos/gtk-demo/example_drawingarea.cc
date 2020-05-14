/* Drawing Area
 *
 * Gtk::DrawingArea is a blank area where you can draw custom displays
 * of various kinds.
 *
 * This demo has two drawing areas. The checkerboard area shows
 * how you can just draw something; all you have to do is write
 * a draw function, as shown here.
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
  ~Example_DrawingArea() override;

protected:
  //draw functions:
  void on_drawingarea_checkerboard_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
  void on_drawingarea_scribble_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

  //signal handlers:
  void on_drawingarea_scribble_resize(int width, int height);
  void on_drawingarea_scribble_drag_begin(double start_x, double start_y);
  void on_drawingarea_scribble_drag_update(double offset_x, double offset_y);
  void on_drawingarea_scribble_drag_end(double offset_x, double offset_y);

  void scribble_create_surface();
  void scribble_draw_brush(double x, double y);

  //Member widgets:
  Gtk::Frame m_Frame_Checkerboard, m_Frame_Scribble;
  Gtk::Box m_VBox;
  Gtk::Label m_Label_Checkerboard, m_Label_Scribble;
  Gtk::DrawingArea m_DrawingArea_Checkerboard, m_DrawingArea_Scribble;

  Cairo::RefPtr<Cairo::ImageSurface> m_surface;
  Glib::RefPtr<Gtk::GestureDrag> m_drag;
  double m_start_x = 0.0;
  double m_start_y = 0.0;
};

//Called by DemoWindow;
Gtk::Window* do_drawingarea()
{
  return new Example_DrawingArea();
}

Example_DrawingArea::Example_DrawingArea()
:
  m_VBox(Gtk::Orientation::VERTICAL, 8)
{
  set_title("Drawing Area");

  m_VBox.set_margin(16);
  set_child(m_VBox);

  /*
   * Create the checkerboard area
   */
  m_Label_Checkerboard.set_markup("<u>Checkerboard pattern</u>");
  m_VBox.append(m_Label_Checkerboard);

  m_Frame_Checkerboard.set_expand(true);
  m_VBox.append(m_Frame_Checkerboard);

  /* set a minimum size */
  m_DrawingArea_Checkerboard.set_content_width(100);
  m_DrawingArea_Checkerboard.set_content_height(100);
  m_Frame_Checkerboard.set_child(m_DrawingArea_Checkerboard);

  m_DrawingArea_Checkerboard.set_draw_func(
      sigc::mem_fun(*this, &Example_DrawingArea::on_drawingarea_checkerboard_draw));

  /*
   * Create the scribble area
   */
  m_Label_Scribble.set_markup("<u>Scribble area</u>");
  m_VBox.append(m_Label_Scribble);

  m_Frame_Scribble.set_expand(true);
  m_VBox.append(m_Frame_Scribble);

  m_drag = Gtk::GestureDrag::create();
  m_drag->set_button(GDK_BUTTON_PRIMARY);
  m_DrawingArea_Scribble.add_controller(m_drag);

  /* set a minimum size */
  m_DrawingArea_Scribble.set_content_width(100);
  m_DrawingArea_Scribble.set_content_height(100);
  m_Frame_Scribble.set_child(m_DrawingArea_Scribble);

  m_DrawingArea_Scribble.set_draw_func(
      sigc::mem_fun(*this, &Example_DrawingArea::on_drawingarea_scribble_draw));

  /* Connect signal handlers */
  m_DrawingArea_Scribble.signal_resize().connect(
      sigc::mem_fun(*this, &Example_DrawingArea::on_drawingarea_scribble_resize));

  m_drag->signal_drag_begin().connect(
      sigc::mem_fun(*this, &Example_DrawingArea::on_drawingarea_scribble_drag_begin));
  m_drag->signal_drag_update().connect(
      sigc::mem_fun(*this, &Example_DrawingArea::on_drawingarea_scribble_drag_update));
  m_drag->signal_drag_end().connect(
      sigc::mem_fun(*this, &Example_DrawingArea::on_drawingarea_scribble_drag_end));
}

Example_DrawingArea::~Example_DrawingArea()
{
}

void Example_DrawingArea::on_drawingarea_checkerboard_draw(const Cairo::RefPtr<Cairo::Context>& cr,
  int width, int height)
{
  enum { CHECK_SIZE = 10, SPACING = 2 };

  /* At the start of a draw handler, a clip region has been set on
   * the Cairo context, and the contents have been cleared to the
   * widget's background color. The docs for
   * Gdk::Window::begin_paint_region() give more details on how this
   * works.
   */

  int xcount = 0;

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
}

void Example_DrawingArea::on_drawingarea_scribble_draw(const Cairo::RefPtr<Cairo::Context>& cr,
  int, int)
{
  cr->set_source(m_surface, 0, 0);
  cr->paint();
}

// Create a new surface of the appropriate size to store our scribbles.
void Example_DrawingArea::scribble_create_surface()
{
  m_surface = Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32,
    m_DrawingArea_Scribble.get_width(), m_DrawingArea_Scribble.get_height());

  // Initialize the surface to white.
  auto cr = Cairo::Context::create(m_surface);
  cr->set_source_rgb(1, 1, 1);
  cr->paint();
}

void Example_DrawingArea::on_drawingarea_scribble_resize(
  int /* width */, int /* height */)
{
  scribble_create_surface();
}

void Example_DrawingArea::on_drawingarea_scribble_drag_begin(double start_x, double start_y)
{
  m_start_x = start_x;
  m_start_y = start_y;
  scribble_draw_brush(m_start_x, m_start_y);
}

void Example_DrawingArea::on_drawingarea_scribble_drag_update(double offset_x, double offset_y)
{
  scribble_draw_brush(m_start_x + offset_x, m_start_y + offset_y);
}

void Example_DrawingArea::on_drawingarea_scribble_drag_end(double offset_x, double offset_y)
{
  scribble_draw_brush(m_start_x + offset_x, m_start_y + offset_y);
}

// Draw a rectangle on the screen.
void Example_DrawingArea::scribble_draw_brush(double x, double y)
{
  if (!m_surface ||
       m_surface->get_width() != m_DrawingArea_Scribble.get_width() ||
       m_surface->get_height() != m_DrawingArea_Scribble.get_height())
    scribble_create_surface();

  const Gdk::Rectangle update_rect((int)x - 3, (int)y - 3, 6, 6);

  // Paint to the surface, where we store our state.
  auto cr = Cairo::Context::create(m_surface);
  Gdk::Cairo::add_rectangle_to_path(cr, update_rect);
  cr->fill();

  m_DrawingArea_Scribble.queue_draw();
}
