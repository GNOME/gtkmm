/* Shortcuts Window
 *
 * Gtk::ShortcutsWindow is a window that provides a help overlay
 * for shortcuts and gestures in an application.
 *
 * Gtk::ShortcutsWindow is deprecated since gtkmm 4.18. It has no replacement
 * in gtkmm. libadwaita (a C library) has a replacement for GtkShortcutsWindow.
 */

#undef GTKMM_DISABLE_DEPRECATED // ShortcutsWindow is deprecated.
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
  auto builder = Gtk::Builder::create();
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
  auto pWindow = Gtk::Builder::get_widget_derived<Example_Shortcuts>(builder, "window1");
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
  auto pButton = builder->get_widget<Gtk::Button>("button_builder");
  if (pButton)
    pButton->signal_clicked().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_Shortcuts::on_button_clicked), "shortcuts_builder", ""));

  pButton = builder->get_widget<Gtk::Button>("button_gedit");
  if (pButton)
    pButton->signal_clicked().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_Shortcuts::on_button_clicked), "shortcuts_gedit", ""));

  pButton = builder->get_widget<Gtk::Button>("button_clocks");
  if (pButton)
    pButton->signal_clicked().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_Shortcuts::on_button_clicked), "shortcuts_clocks", ""));

  pButton = builder->get_widget<Gtk::Button>("button_clocks_stopwatch");
  if (pButton)
    pButton->signal_clicked().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_Shortcuts::on_button_clicked), "shortcuts_clocks", "stopwatch"));

  pButton = builder->get_widget<Gtk::Button>("button_boxes");
  if (pButton)
    pButton->signal_clicked().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_Shortcuts::on_button_clicked), "shortcuts_boxes", ""));

  pButton = builder->get_widget<Gtk::Button>("button_boxes_wizard");
  if (pButton)
    pButton->signal_clicked().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_Shortcuts::on_button_clicked), "shortcuts_boxes", "wizard"));

  pButton = builder->get_widget<Gtk::Button>("button_boxes_display");
  if (pButton)
    pButton->signal_clicked().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_Shortcuts::on_button_clicked), "shortcuts_boxes", "display"));
}

Example_Shortcuts::~Example_Shortcuts()
{
}

void Example_Shortcuts::on_button_clicked(const Glib::ustring& id, const Glib::ustring& view)
{
#ifndef GTKMM_DISABLE_DEPRECATED
  auto builder = Gtk::Builder::create();
  try
  {
    builder->add_from_resource("/shortcuts/example_" + id.raw() + ".ui");
  }
  catch (const Glib::Error& error)
  {
    std::cout << "Error loading example_" << id << ".ui: " << error.what() << std::endl;
    return;
  }

  // Get the GtkBuilder-instantiated shortcuts window:
  auto pOverlay = builder->get_widget<Gtk::ShortcutsWindow>(id);
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

  pOverlay->set_visible(true);

#else // GTKMM_DISABLE_DEPRECATED

  // If gtkmm has been built without deprecated API, the #undef before #include <gtkmm.h>
  // has no effect. GTKMM_DISABLE_DEPRECATED is defined in gtkmm.h.
  const Glib::ustring strMessage = "gtkmm has been built without deprecated API.";
  const Glib::ustring strDetail = "Can't show " + id + " " + view + ".";
  auto dialog = Gtk::AlertDialog::create(strMessage);
  dialog->set_detail(strDetail);
  dialog->show(*this);
#endif
}
