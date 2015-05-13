/* Pixbufs
 *
 * A GdkPixbuf represents an image, normally in RGB or RGBA format.
 * Pixbufs are normally used to load files from disk and perform
 * image scaling.
 *
 * This demo is not all that educational, but looks cool. It was written
 * by Extreme Pixbuf Hacker Federico Mena Quintero. It also shows
 * off how to use GtkDrawingArea to do a simple animation.
 *
 * Look at the Image demo for additional pixbuf usage examples.
 *
 */

//#include <config.h>

#include <gtkmm.h>
#include <math.h>

#define FRAME_DELAY 50

#define BACKGROUND_NAME "background.jpg"

#ifndef M_PI
#define M_PI 3.1415927
#endif

static const char* image_names[] = {
  "apple-red.png",
  "gnome-applets.png",
  "gnome-calendar.png",
  "gnome-foot.png",
  "gnome-gmush.png",
  "gnome-gimp.png",
  "gnome-gsame.png",
  "gnu-keys.png"
};


enum { N_IMAGES = G_N_ELEMENTS(image_names) };




class Example_Pixbufs : public Gtk::Window
{
public:
  Example_Pixbufs();
  virtual ~Example_Pixbufs();

protected:
  virtual void load_pixbufs();

  //signal handlers:
  virtual bool on_drawingarea_draw(const Cairo::RefPtr<Cairo::Context>& cr);
  virtual bool on_timeout();

  //Member widgets:
  Glib::RefPtr<Gdk::Pixbuf> m_refPixbuf;
  Glib::RefPtr<Gdk::Pixbuf> m_refPixbuf_Background;
  Glib::RefPtr<Gdk::Pixbuf> m_images[N_IMAGES];
  Gtk::DrawingArea m_DrawingArea;

  sigc::connection m_TimeoutConnection;
  guint m_back_width, m_back_height;
  gint m_frame_num;
};

//Called by DemoWindow;
Gtk::Window* do_pixbufs()
{
  return new Example_Pixbufs();
}

Example_Pixbufs::Example_Pixbufs()
{
  m_back_width = 0;
  m_back_height = 0;


  set_title("Pixbufs");
  set_resizable(false);

  try
  {
    load_pixbufs();

    set_size_request(m_back_width, m_back_height);
    m_refPixbuf = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, FALSE, 8, m_back_width, m_back_height);
    m_DrawingArea.signal_draw().connect(sigc::mem_fun(*this, &Example_Pixbufs::on_drawingarea_draw));
    add(m_DrawingArea);

    m_TimeoutConnection = Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &Example_Pixbufs::on_timeout), FRAME_DELAY);
  }
  catch (const Glib::Error& error)
  {
    Glib::ustring strMsg = "Failed to load an image: ";
    strMsg += error.what();

    Gtk::MessageDialog dialog(strMsg, false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE);
    dialog.run();
  }

  show_all();
}

Example_Pixbufs::~Example_Pixbufs()
{
  m_TimeoutConnection.disconnect(); //Will probably happen anyway, in the destructor.
}

/* Loads the m_images for the demo and throws and exception if the operation failed */
void Example_Pixbufs::load_pixbufs()
{
  if(m_refPixbuf_Background)
    return; /* already loaded earlier */

  std::string resource_name_background = std::string("/pixbufs/") + BACKGROUND_NAME;

  m_refPixbuf_Background = Gdk::Pixbuf::create_from_resource(resource_name_background);

  m_back_width = m_refPixbuf_Background->get_width();
  m_back_height = m_refPixbuf_Background->get_height();

  for(unsigned i = 0; i < N_IMAGES; ++i)
  {
    std::string resource_name = std::string("/pixbufs/") + image_names[i];

    Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_resource(resource_name);

    m_images[i] = pixbuf;
  }
}

/* Draw callback for the drawing area */
bool Example_Pixbufs::on_drawingarea_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gdk::Cairo::set_source_pixbuf(cr, m_refPixbuf);
  cr->paint();

  return true;
}

#define CYCLE_LEN 60


/* Timeout handler to regenerate the frame */
bool Example_Pixbufs::on_timeout()
{
  m_refPixbuf_Background->copy_area( 0, 0, m_back_width, m_back_height, m_refPixbuf, 0, 0);

  double f = (double) (m_frame_num % CYCLE_LEN) / CYCLE_LEN;

  double xmid = m_back_width / 2.0;
  double ymid = m_back_height / 2.0;

  double radius = MIN (xmid, ymid) / 2.0;

  for (int i = 0; i < N_IMAGES; i++)
  {
    double ang = 2.0 * M_PI * (double) i / N_IMAGES - f * 2.0 * M_PI;

    int iw = m_images[i]->get_width();
    int ih = m_images[i]->get_height();

    double r = radius + (radius / 3.0) * sin (f * 2.0 * M_PI);

    double xpos = floor (xmid + r * cos(ang) - iw / 2.0 + 0.5);
    double ypos = floor (ymid + r * sin(ang) - ih / 2.0 + 0.5);

    double k = (i & 1) ? sin (f * 2.0 * M_PI) : cos (f * 2.0 * M_PI);
    k = 2.0 * k * k;
    k = MAX (0.25, k);

    GdkRectangle r1, r2, dest;
    r1.x = (int)xpos;
    r1.y = (int)ypos;
    r1.width = (int)(iw * k);
    r1.height = (int)(ih * k);

    r2.x = 0;
    r2.y = 0;
    r2.width = m_back_width;
    r2.height = m_back_height;

    if (gdk_rectangle_intersect (&r1, &r2, &dest))
    {
      m_images[i]->composite(m_refPixbuf,
		      dest.x, dest.y,
		      dest.width, dest.height,
		      xpos, ypos,
		      k, k,
		      Gdk::INTERP_NEAREST,
		      (int)((i & 1)
		       ? MAX (127, fabs (255 * sin (f * 2.0 * M_PI)))
		       : MAX (127, fabs (255 * cos (f * 2.0 * M_PI)))));
    }
  }

  m_DrawingArea.queue_draw();

  m_frame_num++;
  return true;
}
