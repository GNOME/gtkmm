/* Shortcuts Window
 *
 * Gtk::ShortcutsWindow is a window that provides a help overlay
 * for shortcuts and gestures in an application.
 */

#include <gtkmm.h>
#include <iostream> // For std::cout

class Example_Shortcuts : public Gtk::Window
{
public:
  Example_Shortcuts(BaseObjectType* cobject,
                    const Glib::RefPtr<Gtk::Builder>& builder);
  ~Example_Shortcuts() override;

protected:

  // Signal handler:
  void on_button_clicked(const Glib::ustring& id, const Glib::ustring& view);

  Glib::RefPtr<Gtk::Builder> m_builder;
};

// Called by DemoWindow:
Gtk::Window* do_shortcuts()
{
  // Load the XML file and instantiate its widgets:
  Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
  try
  {
    builder->add_from_resource("/shortcuts/example_shortcuts.ui");
  }
  catch (const Glib::Error& error)
  {
    std::cout << "Error loading example_shortcuts.ui: " << error.what() << std::endl;
    return nullptr;
  }

  // Get the GtkBuilder-instantiated window:
  Example_Shortcuts* pWindow = nullptr;
  builder->get_widget_derived("window1", pWindow);
  if (!pWindow)
  {
    std::cout << "Could not get 'window1' from the builder." << std::endl;
    return nullptr;
  }
  return pWindow;
}

Example_Shortcuts::Example_Shortcuts(
  BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
: Gtk::Window(cobject),
  m_builder(builder)
{
  Gtk::Button* pButton = nullptr;
  builder->get_widget("button_builder", pButton);
  if (pButton)
    pButton->signal_clicked().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_Shortcuts::on_button_clicked), "shortcuts_builder", ""));

  pButton = nullptr;
  builder->get_widget("button_gedit", pButton);
  if (pButton)
    pButton->signal_clicked().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_Shortcuts::on_button_clicked), "shortcuts_gedit", ""));

  pButton = nullptr;
  builder->get_widget("button_clocks", pButton);
  if (pButton)
    pButton->signal_clicked().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_Shortcuts::on_button_clicked), "shortcuts_clocks", ""));

  pButton = nullptr;
  builder->get_widget("button_clocks_stopwatch", pButton);
  if (pButton)
    pButton->signal_clicked().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_Shortcuts::on_button_clicked), "shortcuts_clocks", "stopwatch"));

  pButton = nullptr;
  builder->get_widget("button_boxes", pButton);
  if (pButton)
    pButton->signal_clicked().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_Shortcuts::on_button_clicked), "shortcuts_boxes", ""));

  pButton = nullptr;
  builder->get_widget("button_boxes_wizard", pButton);
  if (pButton)
    pButton->signal_clicked().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_Shortcuts::on_button_clicked), "shortcuts_boxes", "wizard"));

  pButton = nullptr;
  builder->get_widget("button_boxes_display", pButton);
  if (pButton)
    pButton->signal_clicked().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_Shortcuts::on_button_clicked), "shortcuts_boxes", "display"));

  show_all();
}

Example_Shortcuts::~Example_Shortcuts()
{
}

void Example_Shortcuts::on_button_clicked(const Glib::ustring& id, const Glib::ustring& view)
{
  Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
  try
  {
    builder->add_from_resource("/shortcuts/example_" + id + ".ui");
  }
  catch (const Glib::Error& error)
  {
    std::cout << "Error loading example_" << id << ".ui: " << error.what() << std::endl;
    return;
  }

  // Get the GtkBuilder-instantiated shortcuts window:
  Gtk::ShortcutsWindow* pOverlay = nullptr;
  builder->get_widget(id, pOverlay);
  if (!pOverlay)
  {
    std::cout << "Could not get '"<< id << "' from the builder." << std::endl;
    return;
  }

  pOverlay->set_transient_for(*this);

  if (view.empty())
    pOverlay->unset_view_name();
  else
    pOverlay->property_view_name() = view;

  pOverlay->show();
}
