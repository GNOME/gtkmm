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
  void on_animation_timeout();
  bool on_progressive_timeout();
  void on_loader_area_prepared();
  void on_loader_area_updated(int x, int y, int width, int height);
  void on_toggle_sensitivity();

  void init_message_dialog();

  //Member widgets:
  Gtk::Box m_BaseVBox;
  Gtk::Box m_HBox;
  Gtk::Label m_Label_Image;
  Gtk::Frame m_Frame_Image;
  Gtk::Label m_Label_Animation;
  Gtk::Frame m_Frame_Animation;
  Gtk::Picture m_Picture_Animation;
  Gtk::Label m_Label_ThemedIcon;
  Gtk::Frame m_Frame_ThemedIcon;
  Gtk::Label m_Label_Progressive;
  Gtk::Frame m_Frame_Progressive;
  Gtk::Picture m_Picture_Progressive;
  Gtk::Label m_Label_Video;
  Gtk::Frame m_Frame_Video;
  Gtk::Label m_Label_Paintable;
  Gtk::ToggleButton m_ToggleButton;

  Glib::RefPtr<Gdk::PixbufAnimationIter> m_refPixbufAnimationIter;
  Glib::RefPtr<Gdk::PixbufLoader> m_refPixbufLoader;
  Glib::RefPtr<Gio::InputStream> m_image_stream;
  std::unique_ptr<Gtk::MessageDialog> m_pMessageDialog;
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
  set_child(m_BaseVBox);
  m_BaseVBox.append(m_HBox);

  /* Image */

  auto pVBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 8);
  m_HBox.append(*pVBox);

  m_Label_Image.set_markup("<u>Image loaded from a file</u>");
  pVBox->append(m_Label_Image);

  m_Frame_Image.set_halign(Gtk::Align::CENTER);
  m_Frame_Image.set_valign(Gtk::Align::CENTER);
  pVBox->append(m_Frame_Image);

  auto pImage = Gtk::make_managed<Gtk::Image>();
  pImage->set_from_icon_name("gtk3-demo");
  pImage->set_icon_size(Gtk::IconSize::LARGE);
  m_Frame_Image.set_child(*pImage);

  /* Animation */

  m_Label_Animation.set_markup("<u>Animation loaded from a resource</u>");
  pVBox->append(m_Label_Animation);

  m_Frame_Animation.set_halign(Gtk::Align::CENTER);
  m_Frame_Animation.set_valign(Gtk::Align::CENTER);
  pVBox->append(m_Frame_Animation);

  auto animation = Gdk::PixbufAnimation::create_from_resource("/images/floppybuddy.gif");
  m_refPixbufAnimationIter = animation->get_iter();
  m_Frame_Animation.set_child(m_Picture_Animation);

  // Fill in the first pixbuf and start a timer.
  on_animation_timeout();

  /* Symbolic themed icon */

  m_Label_ThemedIcon.set_markup("<u>Symbolic themed icon</u>");
  pVBox->append(m_Label_ThemedIcon);

  m_Frame_ThemedIcon.set_halign(Gtk::Align::CENTER);
  m_Frame_ThemedIcon.set_valign(Gtk::Align::CENTER);
  pVBox->append(m_Frame_ThemedIcon);

  auto icon = Gio::ThemedIcon::create("battery-caution-charging-symbolic", true);
  pImage = Gtk::make_managed<Gtk::Image>(icon);
  pImage->set_icon_size(Gtk::IconSize::LARGE);
  m_Frame_ThemedIcon.set_child(*pImage);

  /* Progressive */

  pVBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 8);
  m_HBox.append(*pVBox);

  m_Label_Progressive.set_markup("<u>Progressive image loading</u>");
  pVBox->append(m_Label_Progressive);

  m_Frame_Progressive.set_halign(Gtk::Align::CENTER);
  m_Frame_Progressive.set_valign(Gtk::Align::CENTER);
  pVBox->append(m_Frame_Progressive);

  /* Create an empty image for now; the progressive loader
   * will create the pixbuf and fill it in.
   */
  m_Frame_Progressive.set_child(m_Picture_Progressive);

  start_progressive_loading();

  /* Video */

  m_Label_Video.set_markup("<u>Displaying video</u>");
  pVBox->append(m_Label_Video);

  m_Frame_Video.set_halign(Gtk::Align::CENTER);
  m_Frame_Video.set_valign(Gtk::Align::CENTER);
  pVBox->append(m_Frame_Video);

  auto video = Gtk::make_managed<Gtk::Video>();
  video->set_resource("/images/gtk-logo.webm");
  video->get_media_stream()->set_loop();
  m_Frame_Video.set_child(*video);

  /* Widget paintable */

  pVBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 8);
  m_HBox.append(*pVBox);

  m_Label_Paintable.set_markup("<u>Gtk::WidgetPaintable</u>");
  pVBox->append(m_Label_Paintable);

  auto pPicture = Gtk::make_managed<Gtk::Picture>();
  auto demo_window = DemoWindow::get_demo_window();
  if (demo_window)
  {
    auto paintable = Gtk::WidgetPaintable::create(*demo_window);
    pPicture->set_paintable(paintable);
  }
  pPicture->set_size_request(100, 100);
  pPicture->set_valign(Gtk::Align::START);
  pVBox->append(*pPicture);

  /* Sensitivity control */
  m_BaseVBox.append(m_ToggleButton);
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

void Example_Images::on_animation_timeout()
{
  auto delay = m_refPixbufAnimationIter->get_delay_time();
  Glib::signal_timeout().connect_once(
    sigc::mem_fun(*this, &Example_Images::on_animation_timeout), delay);

  m_refPixbufAnimationIter->advance();
  auto pixbuf = m_refPixbufAnimationIter->get_pixbuf();
  auto texture = Gdk::Texture::create_for_pixbuf(pixbuf);
  m_Picture_Animation.set_paintable(texture);
}

void Example_Images::init_message_dialog()
{
  if (!m_pMessageDialog)
  {
    m_pMessageDialog.reset(new Gtk::MessageDialog(
      "", false, Gtk::MessageType::ERROR, Gtk::ButtonsType::CLOSE, true));
    m_pMessageDialog->set_transient_for(*this);
    m_pMessageDialog->set_hide_on_close(true);
    m_pMessageDialog->signal_response().connect(
      sigc::hide(sigc::mem_fun(*m_pMessageDialog, &Gtk::Widget::hide)));
  }
}

void Example_Images::start_progressive_loading()
{
  Glib::signal_timeout().connect(sigc::mem_fun(*this, &Example_Images::on_progressive_timeout), 150);
}

bool Example_Images::on_progressive_timeout()
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
      init_message_dialog();

      Glib::ustring strMsg = "Failure reading image 'alphatest.png': ";
      strMsg += error.what();

      m_pMessageDialog->set_message(strMsg);
      m_pMessageDialog->show();

      m_image_stream.reset();

      return false; // uninstall the timeout
    }

    try
    {
      m_refPixbufLoader->write(buf, bytes_read);
    }
    catch(const Glib::Error& error)
    {
      init_message_dialog();

      Glib::ustring strMsg = "Failed to load image: ";
      strMsg += error.what();

      m_pMessageDialog->set_message(strMsg);
      m_pMessageDialog->show();

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
        init_message_dialog();

        Glib::ustring strMsg = "Failed to close image: ";
        strMsg += error.what();

        m_pMessageDialog->set_message(strMsg);
        m_pMessageDialog->show();

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
      init_message_dialog();

      Glib::ustring strMsg = "Unable to open image 'alphatest.png': ";
      strMsg += error.what();

      m_pMessageDialog->set_message(strMsg);
      m_pMessageDialog->show();

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
