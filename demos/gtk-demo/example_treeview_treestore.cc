/* Tree View/Tree Store
 *
 * The GtkTreeStore is used to store data in tree form, to be
 * used later on by a GtkTreeView to display it. This demo builds
 * a simple GtkTreeStore and displays it. If you're new to the
 * GtkTreeView widgets and associates, look into the GtkListStore
 * example first.
 *
 */

#include <gtkmm.h>

class CellItem_Holiday
{
public:
  CellItem_Holiday();
  CellItem_Holiday(Glib::ustring label, bool alex, bool havoc, bool tim, bool owen, bool dave, bool world_holiday);
  CellItem_Holiday(Glib::ustring label, const std::vector<CellItem_Holiday>& children);
  CellItem_Holiday(const CellItem_Holiday& src);
  ~CellItem_Holiday();
  CellItem_Holiday& operator=(const CellItem_Holiday& src);

  Glib::ustring m_label;
  bool m_alex;
  bool m_havoc;
  bool m_tim;
  bool m_owen;
  bool m_dave;
  bool m_world_holiday; /* shared by the European hackers */
  std::vector<CellItem_Holiday> m_children;
};

class Example_TreeView_TreeStore : public Gtk::Window
{
public:
  Example_TreeView_TreeStore();
  virtual ~Example_TreeView_TreeStore();

protected:
  //vfunc overrides:
  virtual void on_realize();

  virtual void create_model();
  virtual void add_columns();
  virtual void add_items();
  virtual void treestore_add_item(const CellItem_Holiday& foo);

  //Member widgets:
  Gtk::Box m_VBox;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::Label m_Label;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::TreeStore> m_refTreeStore;

  typedef std::vector<CellItem_Holiday> type_vecItems;
  type_vecItems m_vecItems;

  struct ModelColumns : public Gtk::TreeModelColumnRecord
  {
    Gtk::TreeModelColumn<Glib::ustring>  holiday_name;
    Gtk::TreeModelColumn<bool>           alex;
    Gtk::TreeModelColumn<bool>           havoc;
    Gtk::TreeModelColumn<bool>           tim;
    Gtk::TreeModelColumn<bool>           owen;
    Gtk::TreeModelColumn<bool>           dave;
    Gtk::TreeModelColumn<bool>           visible;
    Gtk::TreeModelColumn<bool>           world;

    ModelColumns();
  };

  const ModelColumns m_columns;
};


Example_TreeView_TreeStore::ModelColumns::ModelColumns()
{
  add(holiday_name);
  add(alex); add(havoc); add(tim); add(owen); add(dave);
  add(visible); add(world);
}


CellItem_Holiday::CellItem_Holiday()
{
  m_alex = false;
  m_havoc = false;
  m_tim = false;
  m_owen = false;
  m_dave = false;
  m_world_holiday = false;
}

CellItem_Holiday::CellItem_Holiday(Glib::ustring label, bool alex, bool havoc, bool tim, bool owen, bool dave, bool world_holiday)
{
  m_label = label;
  m_alex = alex;
  m_havoc = havoc;
  m_tim = tim;
  m_owen = owen;
  m_dave = dave;
  m_world_holiday = world_holiday;
}

CellItem_Holiday::CellItem_Holiday(Glib::ustring label, const std::vector<CellItem_Holiday>& children)
{
  m_label = label;
  m_alex = false;
  m_havoc = false;
  m_tim = false;
  m_owen = false;
  m_dave = false;
  m_world_holiday = false;
  m_children = children;
}

CellItem_Holiday::CellItem_Holiday(const CellItem_Holiday& src)
{
  operator=(src);
}

CellItem_Holiday::~CellItem_Holiday()
{
}

CellItem_Holiday& CellItem_Holiday::operator=(const CellItem_Holiday& src)
{
  m_label = src.m_label;
  m_alex = src.m_alex;
  m_havoc = src.m_havoc;
  m_tim = src.m_tim;
  m_owen = src.m_owen;
  m_dave = src.m_dave;
  m_world_holiday = src.m_world_holiday;
  m_children = src.m_children;

  return *this;
}


//Called by DemoWindow;
Gtk::Window* do_treeview_treestore()
{
  return new Example_TreeView_TreeStore();
}


Example_TreeView_TreeStore::Example_TreeView_TreeStore()
: m_VBox(Gtk::ORIENTATION_VERTICAL, 8),
  m_Label("Jonathan's Holiday Card Planning Sheet")
{
  set_title("Card planning sheet");
  set_border_width(8);
  set_default_size(650, 400);

  add(m_VBox);
  m_VBox.pack_start(m_Label, Gtk::PACK_SHRINK);

  m_ScrolledWindow.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  m_VBox.pack_start(m_ScrolledWindow);

  /* create model */
  create_model();

  /* create tree view */
  m_TreeView.set_model(m_refTreeStore);
  Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = m_TreeView.get_selection();
  refTreeSelection->set_mode(Gtk::SELECTION_MULTIPLE);


  add_columns();
  m_ScrolledWindow.add(m_TreeView);

  show_all();
}

Example_TreeView_TreeStore::~Example_TreeView_TreeStore()
{
}

void Example_TreeView_TreeStore::add_items()
{
  std::vector<CellItem_Holiday> january;
  january.push_back( CellItem_Holiday("New Years Day", true, true, true, true, false, true) );
  january.push_back( CellItem_Holiday("Presidential Inauguration", false, true, false, true, false, false) );
  january.push_back( CellItem_Holiday("Martin Luther King Jr. day", false, true, false, true, false, false) );

  std::vector<CellItem_Holiday> february;
  february.push_back( CellItem_Holiday("Presidents' Day", false, true, false, true, false, false) );
  february.push_back( CellItem_Holiday("Groundhog Day", false, false, false, false, false, false) );
  february.push_back( CellItem_Holiday("Valentine's Day", false, false, false, false, true, true) );

  std::vector<CellItem_Holiday> march;
  march.push_back( CellItem_Holiday("National Tree Planting Day", false, false, false, false, false, false) );
  march.push_back( CellItem_Holiday("St Patrick's Day", false, false, false, false, false, true) );

  std::vector<CellItem_Holiday> april;
  april.push_back( CellItem_Holiday("April Fools' Day", false, false, false, false, false, true) );
  april.push_back( CellItem_Holiday("Army Day", false, false, false, false, false, false) );
  april.push_back( CellItem_Holiday("Earth Day", false, false, false, false, false, true) );
  april.push_back( CellItem_Holiday("Administrative Professionals' Day", false, false, false, false, false, false) );

  std::vector<CellItem_Holiday> may;
  may.push_back( CellItem_Holiday("Nurses' Day", false, false, false, false, false, false) );
  may.push_back( CellItem_Holiday("National Day of Prayer", false, false, false, false, false, false) );
  may.push_back( CellItem_Holiday("Mothers' Day", false, false, false, false, false, true) );
  may.push_back( CellItem_Holiday("Armed Forces Day", false, false, false, false, false, false) );
  may.push_back( CellItem_Holiday("Memorial Day", true, true, true, true, false, true) );

  std::vector<CellItem_Holiday> june;
  june.push_back( CellItem_Holiday("June Fathers' Day", false, false, false, false, false, true) );
  june.push_back( CellItem_Holiday("Juneteenth (Liberation of Slaves)", false, false, false, false, false, false) );
  june.push_back( CellItem_Holiday("Flag Day", false, true, false, true, false, false) );

  std::vector<CellItem_Holiday> july;
  july.push_back( CellItem_Holiday("Parents' Day", false, false, false, false, false, true) );
  july.push_back( CellItem_Holiday("Independence Day", false, true, false, true, false, false) );

  std::vector<CellItem_Holiday> august;
  august.push_back( CellItem_Holiday("Air Force Day", false, false, false, false, false, false) );
  august.push_back( CellItem_Holiday("Coast Guard Day", false, false, false, false, false, false) );
  august.push_back( CellItem_Holiday("Friendship Day", false, false, false, false, false, false) );

  std::vector<CellItem_Holiday> september;
  september.push_back( CellItem_Holiday("Grandparents' Day", false, false, false, false, false, true) );
  september.push_back( CellItem_Holiday("Citizenship Day or Constitution Day", false, false, false, false, false, false) );
  september.push_back( CellItem_Holiday("Labor Day", true, true, true, true, false, true) );

  std::vector<CellItem_Holiday> october;
  october.push_back( CellItem_Holiday("National Children's Day", false, false, false, false, false, false) );
  october.push_back( CellItem_Holiday("Bosses' Day", false, false, false, false, false, false) );
  october.push_back( CellItem_Holiday("Sweetest Day", false, false, false, false, false, false) );
  october.push_back( CellItem_Holiday("Mother-in-Law's Day", false, false, false, false, false, false) );
  october.push_back( CellItem_Holiday("Navy Day", false, false, false, false, false, false) );
  october.push_back( CellItem_Holiday("Columbus Day", false, true, false, true, false, false) );
  october.push_back( CellItem_Holiday("Halloween", false, false, false, false, false, true) );

  std::vector<CellItem_Holiday> november;
  november.push_back( CellItem_Holiday("Marine Corps Day", false, false, false, false, false, false) );
  november.push_back( CellItem_Holiday("Veterans' Day", true, true, true, true, false, true) );
  november.push_back( CellItem_Holiday("Thanksgiving", false, true, false, true, false, false) );

  std::vector<CellItem_Holiday> december;
  december.push_back( CellItem_Holiday("Pearl Harbor Remembrance Day", false, false, false, false, false, false) );
  december.push_back( CellItem_Holiday("Christmas", true, true, true, true, false, true) );
  december.push_back( CellItem_Holiday("Kwanzaa", false, false, false, false, false, false) );

  m_vecItems.push_back( CellItem_Holiday("January", january) );
  m_vecItems.push_back( CellItem_Holiday("February", february) );
  m_vecItems.push_back( CellItem_Holiday("March", march) );
  m_vecItems.push_back( CellItem_Holiday("April", april) );
  m_vecItems.push_back( CellItem_Holiday("May", may) );
  m_vecItems.push_back( CellItem_Holiday("June", june) );
  m_vecItems.push_back( CellItem_Holiday("July", july) );
  m_vecItems.push_back( CellItem_Holiday("August", august) );
  m_vecItems.push_back( CellItem_Holiday("September", september) );
  m_vecItems.push_back( CellItem_Holiday("October", october) );
  m_vecItems.push_back( CellItem_Holiday("November", november) );
  m_vecItems.push_back( CellItem_Holiday("December", december) );
}

void Example_TreeView_TreeStore::create_model()
{
  m_refTreeStore = Gtk::TreeStore::create(m_columns);

  add_items();

  std::for_each(
      m_vecItems.begin(), m_vecItems.end(),
      sigc::mem_fun(*this, &Example_TreeView_TreeStore::treestore_add_item));

#if 0 /* testing code: should work, try it out if you like */

  Gtk::TreeIterChildren children = m_refTreeStore->children();

  for(Gtk::TreeModel::iterarator node = children.begin(); node != children.end(); ++node)
  {
    g_print("outer loop\n");

    for(Gtk::TreeModel::iterarator row = node.children().begin(); row != node.children().end(); )
    {
      g_print("inner loop\n");
      row = m_refTreeStore->erase(row);
    }
  }

#endif /* testing code */
}

void Example_TreeView_TreeStore::treestore_add_item(const CellItem_Holiday& foo)
{
  Gtk::TreeRow row = *(m_refTreeStore->append());

  row[m_columns.holiday_name] = foo.m_label;
  row[m_columns.alex]         = foo.m_alex;
  row[m_columns.havoc]        = foo.m_havoc;
  row[m_columns.tim]          = foo.m_tim;
  row[m_columns.owen]         = foo.m_owen;
  row[m_columns.dave]         = foo.m_dave;
  row[m_columns.visible]      = false;
  row[m_columns.world]        = foo.m_world_holiday;

  //Add Children:
  for(std::vector<CellItem_Holiday>::const_iterator iterVec = foo.m_children.begin();
      iterVec != foo.m_children.end();
      ++iterVec)
  {
    const CellItem_Holiday& child = *iterVec;

    Gtk::TreeRow child_row = *(m_refTreeStore->append(row.children()));

    child_row[m_columns.holiday_name] = child.m_label;
    child_row[m_columns.alex]         = child.m_alex;
    child_row[m_columns.havoc]        = child.m_havoc;
    child_row[m_columns.tim]          = child.m_tim;
    child_row[m_columns.owen]         = child.m_owen;
    child_row[m_columns.dave]         = child.m_dave;
    child_row[m_columns.visible]      = true;
    child_row[m_columns.world]        = child.m_world_holiday;
  }
}

void Example_TreeView_TreeStore::add_columns()
{
  /* column for holiday names */
  {
    int cols_count = m_TreeView.append_column("Holiday",  m_columns.holiday_name);
    Gtk::TreeViewColumn* pColumn = m_TreeView.get_column(cols_count-1);
    if(pColumn)
    {
      Gtk::CellRenderer* pRenderer = pColumn->get_first_cell();
      pRenderer->property_xalign().set_value(0.0);

      pColumn->set_clickable();
    }
  }

  /* column for Alex */
  {
    int cols_count = m_TreeView.append_column_editable("Alex", m_columns.alex);
    Gtk::TreeViewColumn* pColumn = m_TreeView.get_column(cols_count-1);
    if(pColumn)
    {
      Gtk::CellRendererToggle* pRenderer = static_cast<Gtk::CellRendererToggle*>(pColumn->get_first_cell());
      pRenderer->property_xalign().set_value(0.0);

      pColumn->add_attribute(pRenderer->property_visible(), m_columns.visible);
      pColumn->add_attribute(pRenderer->property_activatable(), m_columns.world);

      pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
      pColumn->set_fixed_width(50);
      pColumn->set_clickable();
    }
  }

  /* column for Havoc */
  {
    int cols_count = m_TreeView.append_column_editable("Havoc", m_columns.havoc);
    Gtk::TreeViewColumn* pColumn = m_TreeView.get_column(cols_count-1);
    if(pColumn)
    {
      Gtk::CellRendererToggle* pRenderer = static_cast<Gtk::CellRendererToggle*>(pColumn->get_first_cell());
      pRenderer->property_xalign().set_value(0.0);

      pColumn->add_attribute(pRenderer->property_visible(), m_columns.visible);

      pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
      pColumn->set_fixed_width(50);
      pColumn->set_clickable();
    }
  }

  /* column for Tim */
  {
    int cols_count = m_TreeView.append_column_editable("Tim", m_columns.tim);
    Gtk::TreeViewColumn* pColumn = m_TreeView.get_column(cols_count-1);
    if(pColumn)
    {
      Gtk::CellRendererToggle* pRenderer = static_cast<Gtk::CellRendererToggle*>(pColumn->get_first_cell());
      pRenderer->property_xalign().set_value(0.0);

      pColumn->add_attribute(pRenderer->property_visible(), m_columns.visible);
      pColumn->add_attribute(pRenderer->property_activatable(), m_columns.world);

      pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
      pColumn->set_fixed_width(50);
      pColumn->set_clickable();
    }
  }

  /* column for Owen */
  {
    int cols_count = m_TreeView.append_column_editable("Owen", m_columns.owen);
    Gtk::TreeViewColumn* pColumn = m_TreeView.get_column(cols_count-1);
    if(pColumn)
    {
      Gtk::CellRendererToggle* pRenderer = static_cast<Gtk::CellRendererToggle*>(pColumn->get_first_cell());
      pRenderer->property_xalign().set_value(0.0);

      pColumn->add_attribute(pRenderer->property_visible(), m_columns.visible);

      pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
      pColumn->set_fixed_width(50);
      pColumn->set_clickable();
    }
  }

  /* column for Dave */
  {
    int cols_count = m_TreeView.append_column("Dave", m_columns.dave);
    Gtk::TreeViewColumn* pColumn = m_TreeView.get_column(cols_count-1);
    if(pColumn)
    {
      Gtk::CellRendererToggle* pRenderer = static_cast<Gtk::CellRendererToggle*>(pColumn->get_first_cell());
      pRenderer->property_xalign().set_value(0.0);

      pColumn->add_attribute(pRenderer->property_visible(), m_columns.visible);

      pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
      pColumn->set_fixed_width(50);
      pColumn->set_clickable();
    }
  }
}


void Example_TreeView_TreeStore::on_realize()
{
  m_TreeView.expand_all();
  //call base class:
  Window::on_realize();
}
