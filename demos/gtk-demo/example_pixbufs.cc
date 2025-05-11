/* Pixbufs
 *
 * A Gdk::Pixbuf represents an image, normally in RGB or RGBA format.
 * Pixbufs are normally used to load files from disk and perform
 * image scaling.
 *
 * This demo is not all that educational, but looks cool. It was written
 * by Extreme Pixbuf Hacker Federico Mena Quintero. It also shows
 * off how to use Gtk::DrawingArea to do a simple animation.
 *
 * Look at the Image demo for additional pixbuf usage examples.
 */

//TODO: Remove GDKMM_DISABLE_DEPRECATED when set_source_pixbuf() has been replaced.
#undef GDKMM_DISABLE_DEPRECATED
#include <gtkmm.h>
#include <cmath>
#include <algorithm>

namespace
{
const char* background_name = "background.jpg";

const char* image_names[] = {
  "apple-red.png",
  "gnome-applets.png",
  "gnome-calendar.png",
  "gnome-foot.png",
  "gnome-gmush.png",
  "gnome-gimp.png",
  "gnome-gsame.png",
  "gnu-keys.png"
};

const int n_images = G_N_ELEMENTS(image_names);

const gint64 cycle_time = 3000000; // microseconds

} // anonymous namespace

class Example_Pixbufs : public Gtk::Window
{
public:
  Example_Pixbufs();
  ~Example_Pixbufs() override;

protected:
  virtual void load_pixbufs();
  void on_drawingarea_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

  // Callback:
  bool on_tick(const Glib::RefPtr<Gdk::FrameClock>& frame_clock);

  //Member widgets:
  Glib::RefPtr<Gdk::Pixbuf> m_refPixbuf;
  Glib::RefPtr<Gdk::Pixbuf> m_refPixbuf_Background;
  Glib::RefPtr<Gdk::Pixbuf> m_images[n_images];
  Gtk::DrawingArea m_DrawingArea;

  guint m_tick_id = 0;
  guint m_back_width = 0;
  guint m_back_height = 0;
  gint64 m_start_time = 0;
  Glib::RefPtr<Gtk::AlertDialog> m_pAlertDialog;
};

//Called by DemoWindow;
Gtk::Window* do_pixbufs()
{
  return new Example_Pixbufs();
}

Example_Pixbufs::Example_Pixbufs()
{
  set_title("Pixbufs");
  set_resizable(false);

  try
  {
    load_pixbufs();

    set_size_request(m_back_width, m_back_height);
    m_refPixbuf = Gdk::Pixbuf::create(Gdk::Colorspace::RGB, false, 8, m_back_width, m_back_height);
    m_DrawingArea.set_draw_func(sigc::mem_fun(*this, &Example_Pixbufs::on_drawingarea_draw));
    set_child(m_DrawingArea);

    m_tick_id = m_DrawingArea.add_tick_callback(
        sigc::mem_fun(*this, &Example_Pixbufs::on_tick));
  }
  catch (const Glib::Error& error)
  {
    if (!m_pAlertDialog)
      m_pAlertDialog = Gtk::AlertDialog::create();

    Glib::ustring strMsg = "Failed to load an image: ";
    strMsg += error.what();
    m_pAlertDialog->set_message(strMsg);
    m_pAlertDialog->show(*this);
  }
#ifdef GDKMM_DISABLE_DEPRECATED
  // If gtkmm has been built without deprecated API, the #undef before #include <gtkmm.h>
  // has no effect. GDKMM_DISABLE_DEPRECATED is defined in gtkmm.h.
  const Glib::ustring strMessage = "gtkmm has been built without deprecated API.";
  const Glib::ustring strDetail = "Can't show this demo. ";
  auto dialog = Gtk::AlertDialog::create(strMessage);
  dialog->set_detail(strDetail);
  dialog->show(*this);
#endif
}

Example_Pixbufs::~Example_Pixbufs()
{
  m_DrawingArea.remove_tick_callback(m_tick_id); // Will probably happen anyway, in the destructor.
}

/* Loads the m_images for the demo and throws an exception if the operation failed */
void Example_Pixbufs::load_pixbufs()
{
  if(m_refPixbuf_Background)
    return; /* already loaded earlier */

  auto resource_name_background = std::string("/pixbufs/") + background_name;

  m_refPixbuf_Background = Gdk::Pixbuf::create_from_resource(resource_name_background);

  m_back_width = m_refPixbuf_Background->get_width();
  m_back_height = m_refPixbuf_Background->get_height();

  for (int i = 0; i < n_images; ++i)
  {
    auto resource_name = std::string("/pixbufs/") + image_names[i];

    auto pixbuf = Gdk::Pixbuf::create_from_resource(resource_name);

    m_images[i] = pixbuf;
  }
}

/* Draw callback for the drawing area */
void Example_Pixbufs::on_drawingarea_draw(const Cairo::RefPtr<Cairo::Context>& cr, int, int)
{
#ifndef GDKMM_DISABLE_DEPRECATED
  Gdk::Cairo::set_source_pixbuf(cr, m_refPixbuf);
#endif
  cr->paint();
}

/* Handler to regenerate the frame */
bool Example_Pixbufs::on_tick(const Glib::RefPtr<Gdk::FrameClock>& frame_clock)
{
  m_refPixbuf_Background->copy_area(0, 0, m_back_width, m_back_height, m_refPixbuf, 0, 0);

  if (m_start_time == 0)
    m_start_time = frame_clock->get_frame_time();

  const gint64 current_time = frame_clock->get_frame_time();
  const double f = ((current_time - m_start_time) % cycle_time) / (double)cycle_time;

  const double xmid = m_back_width / 2.0;
  const double ymid = m_back_height / 2.0;

  const double radius = std::min(xmid, ymid) / 2.0;

  for (int i = 0; i < n_images; i++)
  {
    const double ang = 2.0 * G_PI * (double)i / n_images - f * 2.0 * G_PI;

    const int iw = m_images[i]->get_width();
    const int ih = m_images[i]->get_height();

    const double r = radius + (radius / 3.0) * std::sin(f * 2.0 * G_PI);

    const double xpos = std::floor(xmid + r * std::cos(ang) - iw / 2.0 + 0.5);
    const double ypos = std::floor(ymid + r * std::sin(ang) - ih / 2.0 + 0.5);

    double k = (i & 1) ? std::sin(f * 2.0 * G_PI) : std::cos(f * 2.0 * G_PI);
    k = 2.0 * k * k;
    k = std::max(0.25, k);

    const Gdk::Rectangle r1((int)xpos, (int)ypos, (int)(iw * k), (int)(ih * k));
    const Gdk::Rectangle r2(0, 0, m_back_width, m_back_height);

    if (r1.intersects(r2))
    {
      Gdk::Rectangle dest = r1;
      dest.intersect(r2);
      m_images[i]->composite(m_refPixbuf,
		      dest.get_x(), dest.get_y(),
		      dest.get_width(), dest.get_height(),
		      xpos, ypos,
		      k, k,
		      Gdk::InterpType::NEAREST,
		      (int)((i & 1)
		       ? std::max(127.0, std::fabs(255.0 * std::sin(f * 2.0 * G_PI)))
		       : std::max(127.0, std::fabs(255.0 * std::cos(f * 2.0 * G_PI)))));
    }
  }

  m_DrawingArea.queue_draw();

  return true;
}
