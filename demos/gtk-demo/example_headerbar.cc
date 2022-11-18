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

#include <gtkmm.h>

class Example_HeaderBar : public Gtk::Window
{
public:
  Example_HeaderBar();
  ~Example_HeaderBar() override;

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
: m_arrow_buttons_box(Gtk::Orientation::HORIZONTAL)
{
  // Window properties
  // Window title is set by header bar
  set_default_size(600, 400);

  // Configuration
  m_header_bar.set_show_title_buttons();
  set_title("Welcome to Facebook - Log in, sign up or learn more");

  // Header Bar buttons
  configure_send_receive_button();
  configure_arrow_buttons();

  // Header Bar layout
  m_header_bar.pack_start(m_arrow_buttons_box);
  m_header_bar.pack_end(m_send_receive_button);

  // Layout
  set_titlebar(m_header_bar);
  set_child(m_text_view);
}

Example_HeaderBar::~Example_HeaderBar()
{
}

void Example_HeaderBar::configure_send_receive_button()
{
  auto icon = Gio::ThemedIcon::create("mail-send-receive-symbolic", false);

  m_send_receive_image.set(icon);
  m_send_receive_button.set_child(m_send_receive_image);
}

void Example_HeaderBar::configure_arrow_buttons()
{
  m_arrow_buttons_box.add_css_class("linked");

  m_left_arrow_button.set_image_from_icon_name("pan-start-symbolic", Gtk::IconSize::INHERIT, true);
  m_right_arrow_button.set_image_from_icon_name("pan-end-symbolic", Gtk::IconSize::INHERIT, true);

  m_arrow_buttons_box.append(m_left_arrow_button);
  m_arrow_buttons_box.append(m_right_arrow_button);
}
