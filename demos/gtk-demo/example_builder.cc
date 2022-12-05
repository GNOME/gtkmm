/* Builder
 *
 * Demonstrates an interface loaded from a XML description.
 */

#include <gtkmm.h>
#include <gtk/gtk.h>
#include <iostream> // For std::cout

class Example_Builder : public Gtk::Window
{
public:
  Example_Builder(BaseObjectType* cobject,
                  const Glib::RefPtr<Gtk::Builder>& builder);
  ~Example_Builder() override;

protected:
  void on_file_quit();
  void on_help_about();
  void on_help_help();
  void on_not_implemented();

  Glib::RefPtr<Gtk::Builder> m_builder;
};

//Called by DemoWindow:
Gtk::Window* do_builder()
{
  // Load the XML file and instantiate its widgets:
  auto builder = Gtk::Builder::create();
  try
  {
    builder->add_from_resource("/builder/example_builder.ui");
  }
  catch (const Glib::Error& error)
  {
    std::cout << "Error loading example_builder.ui: " << error.what() << std::endl;
    return nullptr;
  }

  // Get the GtkBuilder-instantiated window:
  auto pWindow = Gtk::Builder::get_widget_derived<Example_Builder>(builder, "window1");
  if (!pWindow)
  {
    std::cout << "Could not get 'window1' from the builder." << std::endl;
    return nullptr;
  }
  return pWindow;
}

Example_Builder::Example_Builder(
  BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
: Gtk::Window(cobject),
  m_builder(builder)
{
  auto refActions = Gio::SimpleActionGroup::create();
  refActions->add_action("quit", sigc::mem_fun(*this, &Example_Builder::on_file_quit));
  refActions->add_action("about", sigc::mem_fun(*this, &Example_Builder::on_help_about));
  refActions->add_action("help", sigc::mem_fun(*this, &Example_Builder::on_help_help));
  refActions->add_action("new", sigc::mem_fun(*this, &Example_Builder::on_not_implemented));
  refActions->add_action("open", sigc::mem_fun(*this, &Example_Builder::on_not_implemented));
  refActions->add_action("save", sigc::mem_fun(*this, &Example_Builder::on_not_implemented));
  refActions->add_action("save-as", sigc::mem_fun(*this, &Example_Builder::on_not_implemented));
  refActions->add_action("copy", sigc::mem_fun(*this, &Example_Builder::on_not_implemented));
  refActions->add_action("cut", sigc::mem_fun(*this, &Example_Builder::on_not_implemented));
  refActions->add_action("paste", sigc::mem_fun(*this, &Example_Builder::on_not_implemented));
  insert_action_group("win", refActions);

  auto controller = Gtk::ShortcutController::create();
  controller->set_scope(Gtk::ShortcutScope::GLOBAL);
  add_controller(controller);
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_n, Gdk::ModifierType::CONTROL_MASK),
    Gtk::NamedAction::create("win.new")));
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_o, Gdk::ModifierType::CONTROL_MASK),
    Gtk::NamedAction::create("win.open")));
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_s, Gdk::ModifierType::CONTROL_MASK),
    Gtk::NamedAction::create("win.save")));
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_s, Gdk::ModifierType::CONTROL_MASK|Gdk::ModifierType::SHIFT_MASK),
    Gtk::NamedAction::create("win.save-as")));
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_q, Gdk::ModifierType::CONTROL_MASK),
    Gtk::NamedAction::create("win.quit")));
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_c, Gdk::ModifierType::CONTROL_MASK),
    Gtk::NamedAction::create("win.copy")));
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_x, Gdk::ModifierType::CONTROL_MASK),
    Gtk::NamedAction::create("win.cut")));
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_v, Gdk::ModifierType::CONTROL_MASK),
    Gtk::NamedAction::create("win.paste")));
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_F1),
    Gtk::NamedAction::create("win.help")));
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_F7),
    Gtk::NamedAction::create("win.about")));
}

Example_Builder::~Example_Builder()
{
}

void Example_Builder::on_file_quit()
{
  set_visible(false);
}

void Example_Builder::on_help_about()
{
  auto pDialog = m_builder->get_widget<Gtk::AboutDialog>("aboutdialog1");
  if (pDialog)
  {
    pDialog->set_transient_for(*this);
    pDialog->set_hide_on_close(true);
    pDialog->present();
  }
}

void Example_Builder::on_help_help()
{
  std::cout << "Help not available." << std::endl;
}

void Example_Builder::on_not_implemented()
{
  std::cout << "The selected menu item is not implemented." << std::endl;
}
