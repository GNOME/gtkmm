/* Header Bar
 *
 * Gtk::HeaderBar is a container that is suitable for implementing
 * window titlebars. One of its features is that it can position
 * a title (and optional subtitle) centered with regard to the
 * full width, regardless of variable-width content at the left
 * or right.
 *
 * It is commonly used with Gtk::Window::set_titlebar()
 */

#include "gtkmm.h"

// 2014-09-19: The pan-[up,down,start,end]-symbolic icons are new.
// See https://bugzilla.gnome.org/show_bug.cgi?id=729565
// If they are not available in your selected icon theme, perhaps you can
// use the go-[up,down,previous,next]-symbolic icons.
#define USE_PAN_ICON_NAMES 0

class Example_HeaderBar : public Gtk::Window
{
public:
  Example_HeaderBar();
  virtual ~Example_HeaderBar();

protected:

  // Widgets
  Gtk::Image m_send_receive_image;
  Gtk::Button m_send_receive_button;
  Gtk::Button m_left_arrow_button;
  Gtk::Button m_right_arrow_button;
  Gtk::TextView m_text_view;

  // Containers
  Gtk::HeaderBar m_header_bar;
  Gtk::Box m_arrow_buttons_box;

private:
  void configure_send_receive_button();
  void configure_arrow_buttons();
};

//Called by DemoWindow;
Gtk::Window* do_headerbar()
{
  return new Example_HeaderBar();
}

Example_HeaderBar::Example_HeaderBar()
: m_arrow_buttons_box(Gtk::ORIENTATION_HORIZONTAL)
{
  // Window properties
  // Window title is set by header bar
  set_default_size(600, 400);

  // Configuration
  m_header_bar.set_show_close_button();
  m_header_bar.set_title("Welcome to Facebook - Log in, sign up or learn more");
  m_header_bar.set_has_subtitle(false);

  // Header Bar buttons
  configure_send_receive_button();
  configure_arrow_buttons();

  // Header Bar layout
  m_header_bar.pack_start(m_arrow_buttons_box);
  m_header_bar.pack_end(m_send_receive_button);

  // Layout
  set_titlebar(m_header_bar);
  add(m_text_view);

  show_all_children();
}

Example_HeaderBar::~Example_HeaderBar()
{
}

void Example_HeaderBar::configure_send_receive_button()
{
  /* the 'const' is required, to avoid C2668/Ambiguous call errors
     on some compilers, such as Visual Studio or when compiling without
     GTKMM_DISABLE_DEPRECATED on g++ */
  Glib::RefPtr<const Gio::Icon> icon = Gio::ThemedIcon::create("mail-send-receive-symbolic", false);

  m_send_receive_image.set(icon, Gtk::ICON_SIZE_BUTTON);
  m_send_receive_button.add(m_send_receive_image);
}

void Example_HeaderBar::configure_arrow_buttons()
{
  m_arrow_buttons_box.get_style_context()->add_class("linked");

#if USE_PAN_ICON_NAMES
  m_left_arrow_button.set_image_from_icon_name("pan-start-symbolic", Gtk::ICON_SIZE_BUTTON, true);
  m_right_arrow_button.set_image_from_icon_name("pan-end-symbolic", Gtk::ICON_SIZE_BUTTON, true);
#else
  m_left_arrow_button.set_image_from_icon_name("go-previous-symbolic", Gtk::ICON_SIZE_BUTTON, true);
  m_right_arrow_button.set_image_from_icon_name("go-next-symbolic", Gtk::ICON_SIZE_BUTTON, true);
#endif

  m_arrow_buttons_box.add(m_left_arrow_button);
  m_arrow_buttons_box.add(m_right_arrow_button);
}
