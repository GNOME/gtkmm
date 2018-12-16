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
  auto pToolbar = builder->get_widget<Gtk::Toolbar>("toolbar1");
  if (pToolbar)
    pToolbar->get_style_context()->add_class("primary-toolbar");

  auto refActions = Gio::SimpleActionGroup::create();
  refActions->add_action("quit", sigc::mem_fun(*this, &Example_Builder::on_file_quit));
  refActions->add_action("about", sigc::mem_fun(*this, &Example_Builder::on_help_about));
  refActions->add_action("help", sigc::mem_fun(*this, &Example_Builder::on_help_help));
  insert_action_group("win", refActions);

  auto refAccelGroup = Gtk::AccelGroup::create();
  add_accel_group(refAccelGroup);

  auto pMenuItem = builder->get_widget<Gtk::MenuItem>("new_item");
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_n, Gdk::ModifierType::CONTROL_MASK, Gtk::AccelFlags::VISIBLE);

  pMenuItem = builder->get_widget<Gtk::MenuItem>("open_item");
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_o, Gdk::ModifierType::CONTROL_MASK, Gtk::AccelFlags::VISIBLE);

  pMenuItem = builder->get_widget<Gtk::MenuItem>("save_item");
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_s, Gdk::ModifierType::CONTROL_MASK, Gtk::AccelFlags::VISIBLE);

  pMenuItem = builder->get_widget<Gtk::MenuItem>("quit_item");
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_q, Gdk::ModifierType::CONTROL_MASK, Gtk::AccelFlags::VISIBLE);

  pMenuItem = builder->get_widget<Gtk::MenuItem>("copy_item");
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_c, Gdk::ModifierType::CONTROL_MASK, Gtk::AccelFlags::VISIBLE);

  pMenuItem = builder->get_widget<Gtk::MenuItem>("cut_item");
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_x, Gdk::ModifierType::CONTROL_MASK, Gtk::AccelFlags::VISIBLE);

  pMenuItem = builder->get_widget<Gtk::MenuItem>("paste_item");
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_v, Gdk::ModifierType::CONTROL_MASK, Gtk::AccelFlags::VISIBLE);

  pMenuItem = builder->get_widget<Gtk::MenuItem>("help_item");
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_F1, (Gdk::ModifierType)0, Gtk::AccelFlags::VISIBLE);

  pMenuItem = builder->get_widget<Gtk::MenuItem>("about_item");
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_F7, (Gdk::ModifierType)0, Gtk::AccelFlags::VISIBLE);
}

Example_Builder::~Example_Builder()
{
}

void Example_Builder::on_file_quit()
{
  hide();
}

void Example_Builder::on_help_about()
{
  auto pDialog = m_builder->get_widget<Gtk::AboutDialog>("aboutdialog1");
  if (pDialog)
  {
    pDialog->set_transient_for(*this);
    pDialog->run();
    pDialog->hide();
  }
}

void Example_Builder::on_help_help()
{
  std::cout << "Help not available." << std::endl;
}
