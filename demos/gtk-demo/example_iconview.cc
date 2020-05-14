/* Icon View
 *
 * The Gtk::IconView widget is used to display and manipulate icons.  It
 * uses a Gtk::TreeModel for data storage, so the list store example
 * might be helpful.
 *
 */

#include <gtkmm.h>
#include <iostream> //For std::cout.

class Example_IconView : public Gtk::Window
{
public:
  Example_IconView();
  ~Example_IconView() override;

protected:

  void fill_store();

  //Signal handlers:
  virtual void on_button_up();
  virtual void on_button_home();
  virtual void on_iconview_item_activated(const Gtk::TreeModel::Path& path);

  virtual int on_model_sort(const Gtk::TreeModel::const_iterator& a, const Gtk::TreeModel::const_iterator& b);

  class ModelColumns : public Gtk::TreeModelColumnRecord
  {
  public:

    Gtk::TreeModelColumn<std::string> path;
    Gtk::TreeModelColumn<Glib::ustring> display_name;
    Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> >  pixbuf;
    Gtk::TreeModelColumn<bool>          is_directory;

    ModelColumns() { add(path); add(display_name); add(pixbuf); add(is_directory); }
  };

  const ModelColumns m_columns;

  Glib::RefPtr<Gtk::ListStore> m_model;
  Glib::RefPtr<Gdk::Pixbuf> m_refPixbufFile, m_refPixbufFolder;

  std::string m_parent;

  //Member widgets:
  Gtk::Box m_VBox;
  Gtk::Box m_Toolbar;
  Gtk::Button m_ButtonUp, m_ButtonHome;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::IconView m_IconView;
};

//Called by DemoWindow;
Gtk::Window* do_iconview()
{
  return new Example_IconView();
}

Example_IconView::Example_IconView()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_ButtonUp(),
  m_ButtonHome()
{
  m_ButtonUp.set_icon_name("go-up");
  m_ButtonHome.set_icon_name("go-home");

  set_title("Icon View");
  set_default_size(650, 400);

  try
  {
    m_refPixbufFile = Gdk::Pixbuf::create_from_resource("/iconview/gnome-fs-regular.png");
    m_refPixbufFolder = Gdk::Pixbuf::create_from_resource("/iconview/gnome-fs-directory.png");
  }
  catch(const Glib::Error& error)
  {
    std::cout << error.what() << std::endl;
  }

  m_VBox.append(m_Toolbar);

  m_ButtonUp.set_sensitive();
  m_Toolbar.append(m_ButtonUp);

  m_ButtonHome.set_sensitive();
  m_Toolbar.append(m_ButtonHome);

  m_ScrolledWindow.set_has_frame(true);
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);

  //Create the data model:
  m_model = Gtk::ListStore::create(m_columns);
  m_model->set_default_sort_func( sigc::mem_fun(*this, &Example_IconView::on_model_sort) );
  m_model->set_sort_column(Gtk::TreeSortable::DEFAULT_SORT_COLUMN_ID, Gtk::SortType::ASCENDING);

  /* and fill it with the contents of '/' */
  m_parent = "/";
  fill_store();

  m_IconView.set_model(m_model);
  m_IconView.set_selection_mode(Gtk::SelectionMode::MULTIPLE);

  //Connect signals:
  m_ButtonUp.signal_clicked().connect( sigc::mem_fun(*this, &Example_IconView::on_button_up) );
  m_ButtonHome.signal_clicked().connect( sigc::mem_fun(*this, &Example_IconView::on_button_home) );

  /* We now set which model columns that correspont to the text
   * and pixbuf of each item
   */
  m_IconView.set_text_column(m_columns.display_name);
  m_IconView.set_pixbuf_column(m_columns.pixbuf);

  m_IconView.signal_item_activated().connect( sigc::mem_fun(*this, &Example_IconView::on_iconview_item_activated) );

  m_ScrolledWindow.set_child(m_IconView);

  m_IconView.grab_focus();

  set_child(m_VBox);
}

int Example_IconView::on_model_sort(const Gtk::TreeModel::const_iterator& a, const Gtk::TreeModel::const_iterator& b)
{
  /* We need this function because we want to sort
   * folders before files.
   */

  const auto row_a = *a;
  const auto row_b = *b;

  const bool a_is_dir = row_a[m_columns.is_directory];
  const bool b_is_dir = row_b[m_columns.is_directory];

  if(!a_is_dir && b_is_dir)
    return 1;
  else if (a_is_dir && !b_is_dir)
    return -1;
  else
  {
    Glib::ustring name_a = row_a[m_columns.display_name];
    return name_a.compare(row_b.get_value(m_columns.display_name));
  }
}


Example_IconView::~Example_IconView()
{
}

void Example_IconView::on_button_up()
{
  m_parent = Glib::path_get_dirname(m_parent);
  fill_store();

  /* Maybe de-sensitize the up button */
  m_ButtonUp.set_sensitive( m_parent == "/" );
}

void Example_IconView::on_button_home()
{
  m_parent = Glib::get_home_dir();
  fill_store();

  /* De-sensitize the up button */
  m_ButtonUp.set_sensitive(true);
}


void Example_IconView::fill_store()
{
  /* First clear the store */
  m_model->clear();

  /* Now go through the directory and extract all the file
   * information */
  try
  {
    Glib::Dir dir(m_parent); //throws an exception if it fails.

    auto name = dir.read_name();
    while(!name.empty())
    {
      /* We ignore hidden files that start with a '.' */
      if (name[0] != '.')
      {
        auto path = Glib::build_filename(m_parent, name);
        bool is_dir = Glib::file_test(path, Glib::FileTest::IS_DIR);

        auto display_name = Glib::filename_to_utf8(name);

        auto iter = m_model->append();
        auto row = *iter;
        row[m_columns.path] = path;
        row[m_columns.display_name] = display_name;
        row[m_columns.is_directory] = is_dir;
        row[m_columns.pixbuf] = (is_dir ? m_refPixbufFolder : m_refPixbufFile);
      }

      name = dir.read_name();
    }
  }
  catch(const Glib::FileError& ex)
  {
    std::cout << ex.what() << std::endl;
  }
}


void Example_IconView::on_iconview_item_activated(const Gtk::TreeModel::Path& path)
{
  auto iter = m_model->get_iter(path);
  if(iter)
  {
    auto row = *iter;
    const bool is_dir = row[m_columns.is_directory];
    const std::string filepath = row[m_columns.path];
    if(is_dir)
    {
      m_parent = filepath;
      fill_store();

       /* Sensitize the up button */
      m_ButtonUp.set_sensitive();
    }
  }
}

