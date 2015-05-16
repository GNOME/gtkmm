/* Builder
 *
 * Demonstrates an interface loaded from a XML description.
 */

#include "gtkmm.h"
#include "gtk/gtk.h"
#include <iostream> // For std::cout

class Example_Builder : public Gtk::Window
{
public:
  Example_Builder(BaseObjectType* cobject,
                  const Glib::RefPtr<Gtk::Builder>& builder);
  virtual ~Example_Builder();

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
  Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
  try
  {
    builder->add_from_resource("/builder/example_builder.ui");
  }
  catch (const Glib::Error& error)
  {
    std::cout << "Error loading example_builder.ui: " << error.what() << std::endl;
    return 0;
  }

  // Get the GtkBuilder-instantiated window:
  Example_Builder* pWindow = 0;
  builder->get_widget_derived("window1", pWindow);
  if (!pWindow)
  {
    std::cout << "Could not get 'window1' from the builder." << std::endl;
    return 0;
  }
  return pWindow;
}

Example_Builder::Example_Builder(
  BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
: Gtk::Window(cobject),
  m_builder(builder)
{
  Gtk::Toolbar* pToolbar = 0;
  builder->get_widget("toolbar1", pToolbar);
  if (pToolbar)
    pToolbar->get_style_context()->add_class("primary-toolbar");

  Glib::RefPtr<Gio::SimpleActionGroup> refActions = Gio::SimpleActionGroup::create();
  refActions->add_action("quit", sigc::mem_fun(*this, &Example_Builder::on_file_quit));
  refActions->add_action("about", sigc::mem_fun(*this, &Example_Builder::on_help_about));
  refActions->add_action("help", sigc::mem_fun(*this, &Example_Builder::on_help_help));
  insert_action_group("win", refActions);

  Glib::RefPtr<Gtk::AccelGroup> refAccelGroup = Gtk::AccelGroup::create();
  add_accel_group(refAccelGroup);

  Gtk::MenuItem* pMenuItem = 0;
  builder->get_widget("new_item", pMenuItem);
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_n, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);

  builder->get_widget("open_item", pMenuItem);
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_o, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);

  builder->get_widget("save_item", pMenuItem);
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_s, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);

  builder->get_widget("quit_item", pMenuItem);
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_q, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);

  builder->get_widget("copy_item", pMenuItem);
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_c, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);

  builder->get_widget("cut_item", pMenuItem);
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_x, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);

  builder->get_widget("paste_item", pMenuItem);
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_v, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);

  builder->get_widget("help_item", pMenuItem);
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_F1, (Gdk::ModifierType)0, Gtk::ACCEL_VISIBLE);

  builder->get_widget("about_item", pMenuItem);
  if (pMenuItem)
    pMenuItem->add_accelerator("activate", refAccelGroup,
      GDK_KEY_F7, (Gdk::ModifierType)0, Gtk::ACCEL_VISIBLE);

  show_all();
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
  Gtk::AboutDialog* pDialog = 0;
  m_builder->get_widget("aboutdialog1", pDialog);
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
