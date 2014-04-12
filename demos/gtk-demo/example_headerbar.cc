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

class Example_HeaderBar : public Gtk::Window
{
public:
  Example_HeaderBar();
  virtual ~Example_HeaderBar();

protected:

  // Widgets
  Gtk::Image m_send_receive_image;
  Gtk::Button m_send_receive_button;
  Gtk::Arrow m_left_arrow;
  Gtk::Arrow m_right_arrow;
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
: m_left_arrow(Gtk::ARROW_LEFT, Gtk::SHADOW_NONE),
  m_right_arrow(Gtk::ARROW_RIGHT, Gtk::SHADOW_NONE),
  m_arrow_buttons_box(Gtk::ORIENTATION_HORIZONTAL)
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
  Glib::RefPtr<Gio::ThemedIcon> icon = Gio::ThemedIcon::create("mail-send-receive-symbolic", false);

  m_send_receive_image.set(icon, Gtk::ICON_SIZE_BUTTON);
  m_send_receive_button.add(m_send_receive_image);
}

void Example_HeaderBar::configure_arrow_buttons()
{
  m_arrow_buttons_box.get_style_context()->add_class("linked");

  m_left_arrow_button.add(m_left_arrow);
  m_right_arrow_button.add(m_right_arrow);

  m_arrow_buttons_box.add(m_left_arrow_button);
  m_arrow_buttons_box.add(m_right_arrow_button);
}
