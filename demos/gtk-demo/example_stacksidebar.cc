/* Stack Sidebar
 *
 * Gtk::StackSidebar provides an automatic sidebar widget to control
 * navigation of a Gtk::Stack object. This widget automatically updates its
 * contents based on what is presently available in the Gtk::Stack object,
 * and using the "title" child property to set the display labels.
 */

#include <gtkmm.h>
#include <vector>

class Example_StackSidebar : public Gtk::Window
{
public:
  Example_StackSidebar();
  ~Example_StackSidebar() override;

protected:
  // Container:
  Gtk::Box m_Box;

  // Widgets:
  Gtk::HeaderBar m_HeaderBar;
  Gtk::StackSidebar m_StackSidebar;
  Gtk::Separator m_Separator;
  Gtk::Stack m_Stack;

private:
  void fill_page_names();
  std::vector<Glib::ustring> m_page_names;
};

Gtk::Window* do_stacksidebar()
{
  return new Example_StackSidebar();
}

Example_StackSidebar::Example_StackSidebar()
:
  m_Box(Gtk::Orientation::HORIZONTAL),
  m_HeaderBar(),
  m_StackSidebar(),
  m_Separator(Gtk::Orientation::VERTICAL),
  m_Stack()
{
  m_HeaderBar.set_show_title_buttons(true);
  set_titlebar(m_HeaderBar);
  set_title("Stack Sidebar demo");
  set_default_size(500, 350);

  add(m_Box);

  m_Box.pack_start(m_StackSidebar, Gtk::PackOptions::SHRINK);
  m_Box.pack_start(m_Separator, Gtk::PackOptions::SHRINK);
  m_Box.pack_start(m_Stack, Gtk::PackOptions::EXPAND_WIDGET);

  m_Stack.set_transition_type(Gtk::StackTransitionType::SLIDE_UP_DOWN);
  m_StackSidebar.set_stack(m_Stack);

  // Stack pages
  fill_page_names();
  for (std::size_t i = 0; i != m_page_names.size(); ++i)
  {
    Gtk::Widget* widget = nullptr;
    if (i == 0)
    {
      auto image = Gtk::manage(new Gtk::Image());
      image->set_from_icon_name("help-about");
      image->set_pixel_size(256);
      widget = image;
    }
    else
    {
      widget = Gtk::manage(new Gtk::Label(m_page_names[i]));
    }
    m_Stack.add(*widget, m_page_names[i], m_page_names[i]);
  }
}

Example_StackSidebar::~Example_StackSidebar()
{
}

void Example_StackSidebar::fill_page_names()
{
  m_page_names.push_back("Welcome to gtkmm");
  m_page_names.push_back("Gtk::StackSidebar Widget");
  m_page_names.push_back("Automatic navigation");
  m_page_names.push_back("Consistent appearance");
  m_page_names.push_back("Scrolling");
  m_page_names.push_back("Page 6");
  m_page_names.push_back("Page 7");
  m_page_names.push_back("Page 8");
  m_page_names.push_back("Page 9");
}
