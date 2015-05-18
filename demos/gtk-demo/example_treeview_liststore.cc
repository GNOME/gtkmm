/* Tree View/List Store
 *
 * The Gtk::ListStore is used to store data in list form, to be used
 * later on by a Gtk::TreeView to display it. This demo builds a
 * simple Gtk::ListStore and displays it.
 */

#include <gtkmm.h>

class CellItem_Bug
{
public:
  CellItem_Bug();
  CellItem_Bug(bool fixed, guint number, const Glib::ustring& severity, const Glib::ustring& description);
  CellItem_Bug(const CellItem_Bug& src);
  ~CellItem_Bug();
  CellItem_Bug& operator=(const CellItem_Bug& src);

  bool m_fixed;
  guint m_number;
  Glib::ustring m_severity;
  Glib::ustring m_description;
};

class Example_TreeView_ListStore : public Gtk::Window
{
public:
  Example_TreeView_ListStore();
  virtual ~Example_TreeView_ListStore();

protected:
  virtual void create_model();
  virtual void add_columns();
  virtual void add_items();
  virtual void liststore_add_item(const CellItem_Bug& foo);

  //Member widgets:
  Gtk::Box m_VBox;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::Label m_Label;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::ListStore> m_refListStore;

  typedef std::vector<CellItem_Bug> type_vecItems;
  type_vecItems m_vecItems;

  struct ModelColumns : public Gtk::TreeModelColumnRecord
  {
    Gtk::TreeModelColumn<bool>          fixed;
    Gtk::TreeModelColumn<unsigned int>  number;
    Gtk::TreeModelColumn<Glib::ustring> severity;
    Gtk::TreeModelColumn<Glib::ustring> description;

    ModelColumns() { add(fixed); add(number); add(severity); add(description); }
  };

  const ModelColumns m_columns;
};


CellItem_Bug::CellItem_Bug()
{
  m_fixed = false;
  m_number = 0;
}

CellItem_Bug::CellItem_Bug(bool fixed, guint number, const Glib::ustring& severity, const Glib::ustring& description)
{
  m_fixed = fixed;
  m_number = number;
  m_severity = severity;
  m_description = description;
}

CellItem_Bug::CellItem_Bug(const CellItem_Bug& src)
{
  operator=(src);
}

CellItem_Bug::~CellItem_Bug()
{
}

CellItem_Bug& CellItem_Bug::operator=(const CellItem_Bug& src)
{
  m_fixed = src.m_fixed;
  m_number = src.m_number;
  m_severity = src.m_severity;
  m_description = src.m_description;

  return *this;
}


//Called by DemoWindow;
Gtk::Window* do_treeview_liststore()
{
  return new Example_TreeView_ListStore();
}


Example_TreeView_ListStore::Example_TreeView_ListStore()
: m_VBox(Gtk::ORIENTATION_VERTICAL, 8),
  m_Label("This is the bug list (note: not based on real data, it would be nice to have a nice ODBC interface to bugzilla or so, though).")
{
  set_title("Gtk::ListStore demo");
  set_border_width(8);
  set_default_size(280, 250);

  add(m_VBox);
  m_VBox.pack_start(m_Label, Gtk::PACK_SHRINK);

  m_ScrolledWindow.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
  m_ScrolledWindow.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
  m_VBox.pack_start(m_ScrolledWindow);

  /* create model */
  create_model();

  /* create tree view */
  m_TreeView.set_model(m_refListStore);
  m_TreeView.set_search_column(m_columns.description.index());

  add_columns();
  m_ScrolledWindow.add(m_TreeView);

  show_all();
}

Example_TreeView_ListStore::~Example_TreeView_ListStore()
{
}

void Example_TreeView_ListStore::add_items()
{
  m_vecItems.push_back( CellItem_Bug(false, 60482, "Normal",     "scrollable notebooks and hidden tabs") );
  m_vecItems.push_back( CellItem_Bug(false, 60620, "Critical",   "gdk_window_clear_area (gdkwindow-win32.c) is not thread-safe") );
  m_vecItems.push_back( CellItem_Bug(false, 50214, "Major",      "Xft support does not clean up correctly") );
  m_vecItems.push_back( CellItem_Bug(true,  52877, "Major",      "GtkFileSelection needs a refresh method. ") );
  m_vecItems.push_back( CellItem_Bug(false, 56070, "Normal",     "Can not click button after setting insensitive") );
  m_vecItems.push_back( CellItem_Bug(true,  56355, "Normal",     "GtkLabel - Not all changes propagate correctly") );
  m_vecItems.push_back( CellItem_Bug(false, 50055, "Normal",     "Rework width/height computations for TreeView") );
  m_vecItems.push_back( CellItem_Bug(false, 58278, "Normal",     "gtk_dialog_set_response_sensitive () does nott work") );
  m_vecItems.push_back( CellItem_Bug(false, 55767, "Normal",     "Getters for all setters") );
  m_vecItems.push_back( CellItem_Bug(false, 56925, "Normal",     "Gtkcalender size") );
  m_vecItems.push_back( CellItem_Bug(false, 56221, "Normal",     "Selectable label needs right-click copy menu") );
  m_vecItems.push_back( CellItem_Bug(true,  50939, "Normal",     "Add shift clicking to GtkTextView") );
  m_vecItems.push_back( CellItem_Bug(false, 6112,  "Enhancement","netscape-like collapsable toolbars") );
  m_vecItems.push_back( CellItem_Bug(false, 1,     "Normal",     "First bug :=)") );
}

void Example_TreeView_ListStore::create_model()
{
  m_refListStore = Gtk::ListStore::create(m_columns);

  add_items();

  std::for_each(
      m_vecItems.begin(), m_vecItems.end(),
      sigc::mem_fun(*this, &Example_TreeView_ListStore::liststore_add_item));
}

void Example_TreeView_ListStore::liststore_add_item(const CellItem_Bug& foo)
{
  Gtk::TreeRow row = *(m_refListStore->append());

  row[m_columns.fixed]       = foo.m_fixed;
  row[m_columns.number]      = foo.m_number;
  row[m_columns.severity]    = foo.m_severity;
  row[m_columns.description] = foo.m_description;
}

void Example_TreeView_ListStore::add_columns()
{
   /* column for fixed toggles */
  {
    int cols_count = m_TreeView.append_column_editable("Fixed?", m_columns.fixed);
    Gtk::TreeViewColumn* pColumn = m_TreeView.get_column(cols_count-1);

    /* set this column to a fixed sizing (of 50 pixels) */
    pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
    pColumn->set_fixed_width(50);
    pColumn->set_clickable();
  }

  /* column for bug numbers */
  m_TreeView.append_column("Bug number", m_columns.number);

  /* column for severities */
  m_TreeView.append_column("Severity", m_columns.severity);

  /* column for descriptions */
  m_TreeView.append_column("Description", m_columns.description);
}
