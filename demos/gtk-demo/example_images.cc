/* Images
 *
 * Gtk::Image and Gtk::Picture are used to display an image; the image can be
 * in a number of formats.
 *
 * Gtk::Image is the widget used to display icons or images that should be
 * sized and styled like an icon, while Gtk::Picture is used for images
 * that should be displayed as-is.
 *
 * This demo code shows some of the more obscure cases. In the simple
 * case a call to 'new Gtk::Picture(filename)' or
 * Gtk::Image::set_from_icon_name() is all you need.
 *
 * If you want to put image data in your program as a resource,
 * use the glib-compile-resources program that comes with GLib.
 * This way you won't need to depend on loading external files, your
 * application binary can be self-contained.
 */

#include <gtkmm.h>
#include "demowindow.h"

class Example_Images : public Gtk::Window
{
public:
  Example_Images();
  ~Example_Images() override;

protected:
  void start_progressive_loading();

  //Signal handlers:
  bool on_timeout();
  void on_loader_area_prepared();
  void on_loader_area_updated(int x, int y, int width, int height);
  void on_toggle_sensitivity();

  //Member widgets:
  Gtk::Box m_BaseVBox;
  Gtk::Box m_HBox;
  Gtk::Label m_Label_Image;
  Gtk::Frame m_Frame_Image;
  Gtk::Label m_Label_Animation;
  Gtk::Frame m_Frame_Animation;
  Gtk::Label m_Label_ThemedIcon;
  Gtk::Frame m_Frame_ThemedIcon;
  Gtk::Label m_Label_Progressive;
  Gtk::Frame m_Frame_Progressive;
  Gtk::Picture m_Picture_Progressive;
  Gtk::Label m_Label_Video;
  Gtk::Frame m_Frame_Video;
  Gtk::Label m_Label_Paintable;
  Gtk::ToggleButton m_ToggleButton;

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
  m_BaseVBox(Gtk::Orientation::VERTICAL, 8),
  m_HBox(Gtk::Orientation::HORIZONTAL, 16),
  m_ToggleButton("_Insensitive", true),
  m_image_stream()
{
  set_title("Images");

  m_BaseVBox.set_margin(16);
  add(m_BaseVBox);
  m_BaseVBox.pack_start(m_HBox);

  /* Image */

  auto pVBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 8);
  m_HBox.pack_start(*pVBox, Gtk::PackOptions::SHRINK);

  m_Label_Image.set_markup("<u>Image loaded from a file</u>");
  pVBox->pack_start(m_Label_Image, Gtk::PackOptions::SHRINK);

  m_Frame_Image.set_shadow_type(Gtk::ShadowType::IN);
  m_Frame_Image.set_halign(Gtk::Align::CENTER);
  m_Frame_Image.set_valign(Gtk::Align::CENTER);
  pVBox->pack_start(m_Frame_Image, Gtk::PackOptions::SHRINK);

  auto pImage = Gtk::make_managed<Gtk::Image>();
  pImage->set_from_icon_name("gtk3-demo");
  pImage->set_icon_size(Gtk::IconSize::LARGE);
  m_Frame_Image.add(*pImage);

  /* Animation */

  m_Label_Animation.set_markup("<u>Animation loaded from a file</u>");
  pVBox->pack_start(m_Label_Animation, Gtk::PackOptions::SHRINK);

  m_Frame_Animation.set_shadow_type(Gtk::ShadowType::IN);
  m_Frame_Animation.set_halign(Gtk::Align::CENTER);
  m_Frame_Animation.set_valign(Gtk::Align::CENTER);
  pVBox->pack_start(m_Frame_Animation, Gtk::PackOptions::SHRINK);

  auto pPicture = Gtk::make_managed<Gtk::Picture>();
  pPicture->set_resource("/images/floppybuddy.gif");
  m_Frame_Animation.add(*pPicture);

  /* Symbolic themed icon */

  m_Label_ThemedIcon.set_markup("<u>Symbolic themed icon</u>");
  pVBox->pack_start(m_Label_ThemedIcon, Gtk::PackOptions::SHRINK);

  m_Frame_ThemedIcon.set_shadow_type(Gtk::ShadowType::IN);
  m_Frame_ThemedIcon.set_halign(Gtk::Align::CENTER);
  m_Frame_ThemedIcon.set_valign(Gtk::Align::CENTER);
  pVBox->pack_start(m_Frame_ThemedIcon, Gtk::PackOptions::SHRINK);

  auto icon = Gio::ThemedIcon::create("battery-caution-charging-symbolic", true);
  pImage = Gtk::make_managed<Gtk::Image>(icon);
  pImage->set_icon_size(Gtk::IconSize::LARGE);
  m_Frame_ThemedIcon.add(*pImage);

  /* Progressive */

  pVBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 8);
  m_HBox.pack_start(*pVBox, Gtk::PackOptions::SHRINK);

  m_Label_Progressive.set_markup("<u>Progressive image loading</u>");
  pVBox->pack_start(m_Label_Progressive, Gtk::PackOptions::SHRINK);

  m_Frame_Progressive.set_shadow_type(Gtk::ShadowType::IN);
  m_Frame_Progressive.set_halign(Gtk::Align::CENTER);
  m_Frame_Progressive.set_valign(Gtk::Align::CENTER);
  pVBox->pack_start(m_Frame_Progressive, Gtk::PackOptions::SHRINK);

  /* Create an empty image for now; the progressive loader
   * will create the pixbuf and fill it in.
   */
  m_Frame_Progressive.add(m_Picture_Progressive);

  start_progressive_loading();

  /* Video */

  m_Label_Video.set_markup("<u>Displaying video</u>");
  pVBox->pack_start(m_Label_Video, Gtk::PackOptions::SHRINK);

  m_Frame_Video.set_shadow_type(Gtk::ShadowType::IN);
  m_Frame_Video.set_halign(Gtk::Align::CENTER);
  m_Frame_Video.set_valign(Gtk::Align::CENTER);
  pVBox->pack_start(m_Frame_Video, Gtk::PackOptions::SHRINK);

  auto video = Gtk::make_managed<Gtk::Video>();
  video->set_resource("/images/gtk-logo.webm");
  video->get_media_stream()->set_loop();
  m_Frame_Video.add(*video);

  /* Widget paintable */

  pVBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 8);
  m_HBox.pack_start(*pVBox, Gtk::PackOptions::SHRINK);

  m_Label_Paintable.set_markup("<u>Gtk::WidgetPaintable</u>");
  pVBox->pack_start(m_Label_Paintable, Gtk::PackOptions::SHRINK);

  pPicture = Gtk::make_managed<Gtk::Picture>();
  auto demo_window = DemoWindow::get_demo_window();
  if (demo_window)
  {
    auto paintable = Gtk::WidgetPaintable::create(*demo_window);
    pPicture->set_paintable(paintable);
  }
  pPicture->set_size_request(100, 100);
  pPicture->set_valign(Gtk::Align::START);
  pVBox->pack_start(*pPicture, Gtk::PackOptions::SHRINK);

  /* Sensitivity control */
  m_BaseVBox.pack_start(m_ToggleButton, Gtk::PackOptions::SHRINK);
  m_ToggleButton.signal_toggled().connect(sigc::mem_fun(*this, &Example_Images::on_toggle_sensitivity));
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

      Gtk::MessageDialog dialog(strMsg, false, Gtk::MessageType::ERROR, Gtk::ButtonsType::CLOSE);
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

      Gtk::MessageDialog dialog(strMsg, false, Gtk::MessageType::ERROR, Gtk::ButtonsType::CLOSE);
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

        Gtk::MessageDialog dialog(strMsg, false, Gtk::MessageType::ERROR, Gtk::ButtonsType::CLOSE);
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

      Gtk::MessageDialog dialog(strMsg, false, Gtk::MessageType::ERROR, Gtk::ButtonsType::CLOSE);
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
  const auto refPixbuf = m_refPixbufLoader->get_pixbuf();

  /* Avoid displaying random memory contents, since the pixbuf
   * isn't filled in yet.
   */
  refPixbuf->fill(0xaaaaaaff);
  m_Picture_Progressive.set_pixbuf(refPixbuf);
}

void Example_Images::on_loader_area_updated(int/*x*/, int/*y*/, int/*width*/, int/*height*/)
{
  const auto refPixbuf = m_refPixbufLoader->get_pixbuf();
  m_Picture_Progressive.set_pixbuf(refPixbuf);
}

void Example_Images::on_toggle_sensitivity()
{
  m_HBox.set_sensitive(!m_ToggleButton.get_active());
}
