/* Images
 *
 * GtkImage is used to display an image; the image can be in a number of formats.
 * Typically, you load an image into a GdkPixbuf, then display the pixbuf.
 *
 * This demo code shows some of the more obscure cases, in the simple
 * case a call to gtk_image_new_from_file() is all you need.
 *
 * If you want to put image data in your program as a C variable,
 * use the make-inline-pixbuf program that comes with GTK+.
 * This way you won't need to depend on loading external files, your
 * application binary can be self-contained.
 */

#include <gtkmm.h>

class Example_Images : public Gtk::Window
{
public:
  Example_Images();
  virtual ~Example_Images();

protected:
  virtual void start_progressive_loading();

  //signal handler:
  virtual bool on_timeout();
  virtual void on_loader_area_prepared();
  virtual void on_loader_area_updated(int x, int y, int width, int height);

  //Member widgets:
  Gtk::Box m_VBox;
  Gtk::Label m_Label_Image, m_Label_Animation, m_Label_Progressive;
  Gtk::Frame m_Frame_Image, m_Frame_Animation, m_Frame_Progressive;
  Gtk::Image m_Image_Progressive;
  Glib::RefPtr<Gdk::PixbufLoader> m_refPixbufLoader;

  Glib::RefPtr<Gio::InputStream> m_image_stream;
};

//Called by DemoWindow;
Gtk::Window* do_images()
{
  return new Example_Images();
}

Example_Images::Example_Images()
:
  m_VBox                (Gtk::ORIENTATION_VERTICAL, 8),
  m_image_stream        ()
{
  set_title("Images");
  set_border_width(8);

  m_VBox.set_border_width(8);
  add(m_VBox);

  /* Image */

  m_Label_Image.set_markup("<u>Image loaded from a file</u>");
  m_VBox.pack_start(m_Label_Image, Gtk::PACK_SHRINK);

  m_Frame_Image.set_shadow_type(Gtk::SHADOW_IN);

  m_Frame_Image.set_halign(Gtk::ALIGN_CENTER);
  m_Frame_Image.set_valign(Gtk::ALIGN_CENTER);
  m_VBox.pack_start(m_Frame_Image, Gtk::PACK_SHRINK);

  Gtk::Image* pImage = Gtk::manage(new Gtk::Image());
  pImage->set_from_resource("/images/gtk-logo-rgb.gif");
  m_Frame_Image.add(*pImage);

  /* Animation */

  m_Label_Animation.set_markup("<u>Animation loaded from a file</u>");
  m_VBox.pack_start(m_Label_Animation, Gtk::PACK_SHRINK);

  m_Frame_Animation.set_shadow_type(Gtk::SHADOW_IN);

  m_Frame_Animation.set_halign(Gtk::ALIGN_CENTER);
  m_Frame_Animation.set_valign(Gtk::ALIGN_CENTER);
  m_VBox.pack_start(m_Frame_Animation, Gtk::PACK_SHRINK);

  pImage = Gtk::manage(new Gtk::Image());
  pImage->set_from_resource("/images/floppybuddy.gif");
  m_Frame_Animation.add(*pImage);

  /* Progressive */

  m_Label_Progressive.set_markup("<u>Progressive image loading</u>");
  m_VBox.pack_start(m_Label_Progressive, Gtk::PACK_SHRINK);

  m_Frame_Progressive.set_shadow_type(Gtk::SHADOW_IN);

  m_VBox.pack_start(m_Frame_Progressive, Gtk::PACK_SHRINK);

  /* Create an empty image for now; the progressive loader
   * will create the pixbuf and fill it in.
   */
  m_Frame_Progressive.add(m_Image_Progressive);

  start_progressive_loading();

  show_all();
}

Example_Images::~Example_Images()
{
  try
  {
    if(m_refPixbufLoader)
      m_refPixbufLoader->close();
  }
  catch(const Gdk::PixbufError&)
  {
    // ignore errors
  }
}

void Example_Images::start_progressive_loading()
{
  Glib::signal_timeout().connect(sigc::mem_fun(*this, &Example_Images::on_timeout), 150);
}

bool Example_Images::on_timeout()
{
  /* This shows off fully-paranoid error handling, so looks scary.
   * You could factor out the error handling code into a nice separate
   * function to make things nicer.
   */

  if(m_image_stream)
  {
    guint8 buf[256];
    gsize bytes_read = 0;

    try
    {
      bytes_read = m_image_stream->read(buf, sizeof(buf));
    }
    catch(const Glib::Error& error)
    {
     
      Glib::ustring strMsg = "Failure reading image 'alphatest.png': ";
      strMsg += error.what();

      Gtk::MessageDialog dialog(strMsg, false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE);
      dialog.run();

      m_image_stream.reset();

      return false; // uninstall the timeout
    }

    try
    {
      m_refPixbufLoader->write(buf, bytes_read);
    }
    catch(const Glib::Error& error)
    {
      Glib::ustring strMsg = "Failed to load image: ";
      strMsg += error.what();

      Gtk::MessageDialog dialog(strMsg, false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE);
      dialog.run();

      m_image_stream.reset();

      return false; // uninstall the timeout
    }

    if(bytes_read == 0)
    {
      m_image_stream.reset();

      /* Errors can happen on close, e.g. if the image
       * file was truncated we'll know on close that
       * it was incomplete.
       */

      try
      {
        m_refPixbufLoader->close();
      }
      catch(const Glib::Error& error)
      {
        Glib::ustring strMsg = "Failed to close image: ";
        strMsg += error.what();

        Gtk::MessageDialog dialog(strMsg, false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE);
        dialog.run();

        m_refPixbufLoader.reset();

        return false; // uninstall the timeout
      }

      m_refPixbufLoader.reset();
    }
  }
  else
  {
    try
    {
      m_image_stream = Gio::Resource::open_stream_global("/images/alphatest.png");
    }
    catch(const Glib::Error& error)
    {
      Glib::ustring strMsg = "Unable to open image 'alphatest.png': ";
      strMsg += error.what();

      Gtk::MessageDialog dialog(strMsg, false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE);
      dialog.run();

      return false; // uninstall the timeout
    }

    if(m_refPixbufLoader)
    {
      m_refPixbufLoader->close();

      m_refPixbufLoader.reset();
    }

    m_refPixbufLoader = Gdk::PixbufLoader::create();

    m_refPixbufLoader->signal_area_prepared().connect(
        sigc::mem_fun(*this, &Example_Images::on_loader_area_prepared));

    m_refPixbufLoader->signal_area_updated().connect(
        sigc::mem_fun(*this, &Example_Images::on_loader_area_updated));
  }

  return true; // leave timeout installed
}

void Example_Images::on_loader_area_prepared()
{
  const Glib::RefPtr<Gdk::Pixbuf> refPixbuf = m_refPixbufLoader->get_pixbuf();

  /* Avoid displaying random memory contents, since the pixbuf
   * isn't filled in yet.
   */
  refPixbuf->fill(0xaaaaaaff);
  m_Image_Progressive.set(refPixbuf);
}

void Example_Images::on_loader_area_updated(int/*x*/, int/*y*/, int/*width*/, int/*height*/)
{
  /* We know the pixbuf inside the Gtk::Image has changed, but the image
   * itself doesn't know this; so give it a hint by setting the pixbuf
   * again. Queuing a redraw used to be sufficient, but nowadays Gtk::Image
   * uses GtkIconHelper which caches the pixbuf state and will just redraw
   * from the cache.
   * If we wanted to be really efficient, we could use a drawing area or
   * something instead of a Gtk::Image, so we could control the exact
   * position of the pixbuf on the display, then we could queue a draw
   * for only the updated area of the image.
   */
  Glib::RefPtr<Gdk::Pixbuf> refPixbuf = m_Image_Progressive.get_pixbuf();
  m_Image_Progressive.set(refPixbuf);
}

