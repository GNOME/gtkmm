/* List View, Application launcher
 *
 * This demo uses the Gtk::ListView widget as a fancy application launcher.
 *
 * It is also a very small introduction to listviews.
 */

#include <gtkmm.h>
#include <giomm/appinfo.h>
#include <giomm/liststore.h>

class Example_ListView_AppLauncher : public Gtk::Window
{
public:
  Example_ListView_AppLauncher();
  ~Example_ListView_AppLauncher() override;

protected:
  Glib::RefPtr<Gio::ListModel> create_application_list();
  void setup_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void bind_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void activate(guint position);

  Gtk::ListView* m_list;
  Glib::RefPtr<Gtk::AlertDialog> m_error_dialog;
};

Gtk::Window* do_listview_applauncher()
{
  return new Example_ListView_AppLauncher();
}


/* This is the function that creates the Gio::ListModel that we need.
 * GTK list widgets need a Gio::ListModel to display, as models support change
 * notifications.
 * Unfortunately various older APIs do not provide list models, so we create
 * our own.
 */
Glib::RefPtr<Gio::ListModel> Example_ListView_AppLauncher::create_application_list()
{
  /* We use a Gio::ListStore here, which is a simple array-like list implementation
   * for manual management.
   * List models need to know what type of data they provide, so we need to
   * provide the type here. As we want to do a list of applications, Gio::AppInfo
   * is the object we provide.
   */
  auto store = Gio::ListStore<Gio::AppInfo>::create();

  for (auto app : Gio::AppInfo::get_all())
    store->append(app);

  return store;
}

/* This is the function we use for setting up new listitems to display.
 * We add just an Gtk::Image and a Gtk::Label here to display the application's
 * icon and name, as this is just a simple demo.
 */
void Example_ListView_AppLauncher::setup_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 12);
  auto image = Gtk::make_managed<Gtk::Image>();
  image->set_icon_size(Gtk::IconSize::LARGE);
  box->append(*image);
  auto label = Gtk::make_managed<Gtk::Label>();
  box->append(*label);
  list_item->set_child(*box);
}

/* Here we need to prepare the listitem for displaying its item. We get the
 * listitem already set up from the previous function, so we can reuse the
 * Gtk::Image widget we set up above.
 * We get the item - which we know is a Gio::AppInfo because it comes out of
 * the model we set up above, grab its icon and display it.
 */
void Example_ListView_AppLauncher::bind_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  if (auto image = dynamic_cast<Gtk::Image*>(list_item->get_child()->get_first_child()))
    if (auto label = dynamic_cast<Gtk::Label*>(image->get_next_sibling()))
      if (auto app_info = std::dynamic_pointer_cast<Gio::AppInfo>(list_item->get_item()))
      {
        image->set(app_info->get_icon());
        label->set_label(app_info->get_display_name());
      }
}

/* In more complex code, we would also need functions to unbind and teardown
 * the listitem, but this is simple code, so the default implementations are
 * enough. If we had connected signals, this step would have been necessary.
 *
 * The Gtk::SignalListItemFactory documentation contains more information about
 * this step.
 */

/* This function is called whenever an item in the list is activated. This is
 * the simple way to allow reacting to the Enter key or double-clicking on a
 * listitem.
 * Of course, it is possible to use far more complex interactions by turning
 * off activation and adding buttons or other widgets in the setup function
 * above, but this is a simple demo, so we'll use the simple way.
 */
void Example_ListView_AppLauncher::activate(guint position)
{
  auto item = std::dynamic_pointer_cast<Gio::ListModel>(m_list->get_model())->get_object(position);
  if (auto app_info = std::dynamic_pointer_cast<Gio::AppInfo>(item))
  {
    /* Prepare the context for launching the application and launch it. This
     * code is explained in detail in the documentation for Gdk::AppLaunchContext
     * and Gio::AppInfo.
     */
    auto context = m_list->get_display()->get_app_launch_context();
    try
    {
      app_info->launch(std::vector<Glib::RefPtr<Gio::File>>(), context);
    }
    catch (const Glib::Error& error)
    {
      /* And because error handling is important, even a simple demo has it:
       * We display an error dialog that something went wrong.
       */
      if (!m_error_dialog)
        m_error_dialog = Gtk::AlertDialog::create();

      m_error_dialog->set_message("Could not launch " + app_info->get_display_name());
      m_error_dialog->set_detail(error.what());
      m_error_dialog->show(*this);
    }
  }
}

Example_ListView_AppLauncher::Example_ListView_AppLauncher()
{
  set_default_size(640, 320);
  set_title("Application Launcher");

  /* The Gtk::ListItemFactory is what is used to create Gtk::ListItems
   * to display the data from the model. So it is absolutely necessary
   * to create one.
   * We will use a Gtk::SignalListItemFactory because it is the simplest
   * one to use. Different ones are available for different use cases.
   * The most powerful one is Gtk::BuilderListItemFactory which uses
   * Gtk::Builder .ui files, so it requires little code.
   */
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &Example_ListView_AppLauncher::setup_listitem));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &Example_ListView_AppLauncher::bind_listitem));

  /* And of course we need to set the data model. Here we call the function
   * we wrote above that gives us the list of applications. Then we set
   * it on the list widget.
   * The list will now take items from the model and use the factory
   * to create as many listitems as it needs to show itself to the user.
   */
  auto model = create_application_list();

  /* Create the list widget here.
   */
  m_list = Gtk::make_managed<Gtk::ListView>(Gtk::SingleSelection::create(model), factory);

  /* We connect the activate signal here. It's the function we defined
   * above for launching the selected application.
   */
  m_list->signal_activate().connect(
    sigc::mem_fun(*this, &Example_ListView_AppLauncher::activate));

  /* List widgets should always be contained in a Gtk::ScrolledWindow,
   * because otherwise they might get too large or they might not
   * be scrollable.
   */
  auto sw = Gtk::make_managed<Gtk::ScrolledWindow>();
  set_child(*sw);
  sw->set_child(*m_list);
}

Example_ListView_AppLauncher::~Example_ListView_AppLauncher()
{
}
