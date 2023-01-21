/* Grid View
 *
 * The Gtk::GridView widget presents a view into a large dynamic grid of items. 
 * It uses a Gio::ListStore for data storage, so the list view example
 * Lists -> Application Launcher might be helpful.
 */

#include <gtkmm.h>
#include <iostream> //For std::cout.

class Example_GridView : public Gtk::Window
{
public:
  Example_GridView();
  ~Example_GridView() override;

protected:
  class ModelColumns : public Glib::Object
  {
  public:
    std::string m_path;
    Glib::ustring m_display_name;
    bool m_is_directory;
    std::string get_image_resource_path() const
    {
      return m_is_directory ? "/gridview/gnome-fs-directory.png" : "/gridview/gnome-fs-regular.png";
    }

    static Glib::RefPtr<ModelColumns> create(const std::string& path,
      const Glib::ustring& display_name, bool is_directory)
    {
      return Glib::make_refptr_for_instance<ModelColumns>(
        new ModelColumns(path, display_name, is_directory));
    }
    
  protected:
    ModelColumns(const std::string& path, const Glib::ustring& display_name,
      bool is_directory)
    : m_path(path), m_display_name(display_name), m_is_directory(is_directory)
    { }
  }; // ModelColumns

  void fill_store();

  //Signal handlers:
  void on_button_up();
  void on_button_home();
  void on_gridview_item_activated(unsigned int position);
  void on_setup_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item);

  int on_model_sort(const Glib::RefPtr<const ModelColumns>& a, const Glib::RefPtr<const ModelColumns>& b);

  Glib::RefPtr<Gio::ListStore<ModelColumns>> m_dir_model;
  Glib::RefPtr<Gtk::MultiSelection> m_selection_model;
  Glib::RefPtr<Gtk::SignalListItemFactory> m_factory;

  std::string m_parent;

  //Member widgets:
  Gtk::Box m_VBox;
  Gtk::Box m_Toolbar;
  Gtk::Label m_PathLabel;
  Gtk::Button m_ButtonUp;
  Gtk::Button m_ButtonHome;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::GridView m_GridView;
};

//Called by DemoWindow;
Gtk::Window* do_gridview()
{
  return new Example_GridView();
}

Example_GridView::Example_GridView()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Toolbar(Gtk::Orientation::HORIZONTAL),
  m_ButtonUp(),
  m_ButtonHome()
{
  m_ButtonUp.set_icon_name("go-up");
  m_ButtonHome.set_icon_name("go-home");

  set_title("Grid View");
  set_default_size(650, 400);

  m_VBox.append(m_Toolbar);

  m_ButtonUp.set_sensitive();
  m_Toolbar.append(m_ButtonUp);

  m_ButtonHome.set_sensitive();
  m_Toolbar.append(m_ButtonHome);

  m_VBox.append(*Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::HORIZONTAL));
  m_VBox.append(m_PathLabel);

  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);

  // Create the data model:
  m_dir_model = Gio::ListStore<ModelColumns>::create();
  m_selection_model = Gtk::MultiSelection::create(m_dir_model);

  m_factory = Gtk::SignalListItemFactory::create();
  m_factory->signal_setup().connect(
    sigc::mem_fun(*this, &Example_GridView::on_setup_listitem));
  m_factory->signal_bind().connect(
    sigc::mem_fun(*this, &Example_GridView::on_bind_listitem));

  /* and fill it with the contents of '/' */
  m_parent = "/";
  fill_store();

  m_GridView.set_model(m_selection_model);
  m_GridView.set_factory(m_factory);

  //Connect signals:
  m_ButtonUp.signal_clicked().connect( sigc::mem_fun(*this, &Example_GridView::on_button_up) );
  m_ButtonHome.signal_clicked().connect( sigc::mem_fun(*this, &Example_GridView::on_button_home) );
  m_GridView.signal_activate().connect(
    sigc::mem_fun(*this, &Example_GridView::on_gridview_item_activated));

  m_ScrolledWindow.set_child(m_GridView);

  m_GridView.grab_focus();

  set_child(m_VBox);
}

void Example_GridView::on_setup_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  // Each ListItem contains a vertical Box with an Image and a Label.
  auto vBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  auto image = Gtk::make_managed<Gtk::Image>();
  image->set_icon_size(Gtk::IconSize::LARGE);
  vBox->append(*image);
  vBox->append(*Gtk::make_managed<Gtk::Label>());
  list_item->set_child(*vBox);
}

void Example_GridView::on_bind_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto vBox = dynamic_cast<Gtk::Box*>(list_item->get_child());
  if (!vBox)
    return;
  auto image = dynamic_cast<Gtk::Image*>(vBox->get_first_child());
  if (!image)
    return;
  auto label = dynamic_cast<Gtk::Label*>(image->get_next_sibling());
  if (!label)
    return;
  image->set_from_resource(col->get_image_resource_path());
  label->set_text(col->m_display_name);
}

int Example_GridView::on_model_sort(const Glib::RefPtr<const ModelColumns>& a, const Glib::RefPtr<const ModelColumns>& b)
{
  /* We need this function because we want to sort folders before files. */

  const bool a_is_dir = a->m_is_directory;
  const bool b_is_dir = b->m_is_directory;

  if(!a_is_dir && b_is_dir)
    return 1;
  else if (a_is_dir && !b_is_dir)
    return -1;
  else
  {
    const Glib::ustring name_a = a->m_display_name;
    return name_a.compare(b->m_display_name);
  }
}

Example_GridView::~Example_GridView()
{
}

void Example_GridView::on_button_up()
{
  m_parent = Glib::path_get_dirname(m_parent);
  fill_store();

  /* Maybe de-sensitize the up button */
  m_ButtonUp.set_sensitive(m_parent != "/");
}

void Example_GridView::on_button_home()
{
  m_parent = Glib::get_home_dir();
  fill_store();

  /* Sensitize the up button */
  m_ButtonUp.set_sensitive(true);
}

void Example_GridView::fill_store()
{
  /* First clear the store */
  m_dir_model->remove_all();
  m_PathLabel.set_text(Glib::filename_to_utf8(m_parent));

  /* Now go through the directory and extract all the file information */
  try
  {
    Glib::Dir dir(m_parent); // throws an exception if it fails.

    auto name = dir.read_name();
    while (!name.empty())
    {
      /* We ignore hidden files that start with a '.' */
      if (name[0] != '.')
      {
        const auto path = Glib::build_filename(m_parent, name);
        const auto display_name = Glib::filename_to_utf8(name);
        const bool is_dir = Glib::file_test(path, Glib::FileTest::IS_DIR);

        m_dir_model->append(ModelColumns::create(path, display_name, is_dir));
      }
      name = dir.read_name();
    }
    m_dir_model->sort(sigc::mem_fun(*this, &Example_GridView::on_model_sort));
  }
  catch (const Glib::FileError& ex)
  {
    std::cout << ex.what() << std::endl;
  }
}

void Example_GridView::on_gridview_item_activated(unsigned int position)
{
  auto col = m_dir_model->get_item(position);
  if (!col)
    return;
  const bool is_dir = col->m_is_directory;
  const std::string filepath = col->m_path;
  if(is_dir)
  {
    m_parent = filepath;
    fill_store();

    /* Sensitize the up button */
    m_ButtonUp.set_sensitive();
  }
}
