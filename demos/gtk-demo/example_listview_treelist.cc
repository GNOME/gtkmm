/* Column View, Tree List
 *
 * The Gtk::TreeListModel is used for storing data in tree form, to be
 * used later on by a Gtk::ListView or a Gtk::ColumnView to display it.
 * This demo builds a simple Gtk::TreeListModel and displays it.
 * If you're new to the Gtk::ListView widget and associates,
 * look into the Gio::ListStore example first.
 *
 * The view contains check buttons that you can check and uncheck.
 * The changes you make in the view are not copied to the model in
 * this demo. To see how changes in the GUI can be copied to the model,
 * see the List Store and the Editable Cells demos.
 */
 
#include <gtkmm.h>

namespace
{
class CellItem_Holiday
{
public:
  CellItem_Holiday() = default;
  CellItem_Holiday(Glib::ustring holiday_name, bool alex, bool havoc, bool tim, bool owen, bool dave, bool world_holiday);
  CellItem_Holiday(Glib::ustring holiday_name, const std::vector<CellItem_Holiday>& children);
  CellItem_Holiday(const CellItem_Holiday& src) = default;
  CellItem_Holiday(CellItem_Holiday&& src) = default;
  CellItem_Holiday& operator=(const CellItem_Holiday& src) = default;
  CellItem_Holiday& operator=(CellItem_Holiday&& src) = default;
  ~CellItem_Holiday() = default;

  Glib::ustring m_holiday_name;
  bool m_alex{false};
  bool m_havoc{false};
  bool m_tim{false};
  bool m_owen{false};
  bool m_dave{false};
  bool m_world_holiday{false}; /* shared by the European hackers */
  std::vector<CellItem_Holiday> m_children;
}; // CellItem_Holiday

// Columns with check buttons.
namespace CheckColumns
{
enum {
  ALEX,
  HAVOC,
  TIM,
  OWEN,
  DAVE,
  N_COLS
};
} // namespace CheckColumns

const Glib::ustring check_column_name[CheckColumns::N_COLS] = {
 "Alex",
 "Havoc",
 "Tim",
 "Owen",
 "Dave"
};

const bool is_european_hacker[CheckColumns::N_COLS] = {
// Alex, Havoc, Tim,  Owen,  Dave
   true, false, true, false, false
};

} // anonymous namespace

class Example_ListView_TreeList : public Gtk::Window
{
public:
  Example_ListView_TreeList();
  ~Example_ListView_TreeList() override;

protected:
  class ModelColumns : public Glib::Object
  {
  public:
    Glib::ustring m_holiday_name;
    bool m_alex;
    bool m_havoc;
    bool m_tim;
    bool m_owen;
    bool m_dave;
    bool m_world_holiday; /* shared by the European hackers */
    std::vector<CellItem_Holiday> m_children;

    static Glib::RefPtr<ModelColumns> create(const CellItem_Holiday& item)
    {
      return Glib::make_refptr_for_instance<ModelColumns>(new ModelColumns(item));
    }
    
  protected:
    ModelColumns(const CellItem_Holiday& item)
    : m_holiday_name(item.m_holiday_name), m_alex(item.m_alex), m_havoc(item.m_havoc),
      m_tim(item.m_tim), m_owen(item.m_owen), m_dave(item.m_dave),
      m_world_holiday(item.m_world_holiday), m_children(item.m_children)
    { }
  }; // ModelColumns

  Glib::RefPtr<Gio::ListModel> create_model(
    const Glib::RefPtr<Glib::ObjectBase>& item = {});
  void add_columns();
  void add_items();

  //Member widgets:
  Gtk::Box m_VBox;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::Label m_Label;
  Gtk::ColumnView m_ColumnView;
  Gtk::Box m_ButtonBox;
  Gtk::ToggleButton m_ShowButtons[CheckColumns::N_COLS];

  Glib::RefPtr<Gtk::TreeListModel> m_TreeListModel;
  Glib::RefPtr<Gtk::MultiSelection> m_TreeSelection;
  Glib::RefPtr<Gtk::ColumnViewColumn> m_ViewColumns[CheckColumns::N_COLS];

  // Signal handlers:
  void on_show_button_toggled(int button);
  void on_setup_holiday(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_setup_checkbutton(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_holiday(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_checkbutton(const Glib::RefPtr<Gtk::ListItem>& list_item, int check_column);

  std::vector<CellItem_Holiday> m_vecItems;
};


CellItem_Holiday::CellItem_Holiday(Glib::ustring holiday_name,
  bool alex, bool havoc, bool tim, bool owen, bool dave, bool world_holiday)
: m_holiday_name(holiday_name), m_alex(alex), m_havoc(havoc), m_tim(tim),
  m_owen(owen), m_dave(dave), m_world_holiday(world_holiday)
{ }

CellItem_Holiday::CellItem_Holiday(Glib::ustring holiday_name,
  const std::vector<CellItem_Holiday>& children)
: m_holiday_name(holiday_name), m_children(children)
{ }


//Called by DemoWindow:
Gtk::Window* do_listview_treelist()
{
  return new Example_ListView_TreeList();
}


Example_ListView_TreeList::Example_ListView_TreeList()
: m_VBox(Gtk::Orientation::VERTICAL, 8),
  m_Label("Jonathan's Holiday Card Planning Sheet"),
  m_ButtonBox(Gtk::Orientation::HORIZONTAL, 5)
{
  set_title("Card planning sheet");
  set_default_size(650, 400);

  m_VBox.set_margin(8);
  set_child(m_VBox);
  m_VBox.append(m_Label);

  m_ScrolledWindow.set_has_frame(true);
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();
  m_VBox.append(m_ScrolledWindow);

  /* create root model */
  add_items();
  auto root = create_model();

  /* create column view */
  m_TreeListModel = Gtk::TreeListModel::create(root,
    sigc::mem_fun(*this, &Example_ListView_TreeList::create_model), false, true);
  m_TreeSelection = Gtk::MultiSelection::create(m_TreeListModel);
  m_ColumnView.set_model(m_TreeSelection);
  m_ColumnView.add_css_class("data-table");

  add_columns();
  m_ScrolledWindow.set_child(m_ColumnView);

  // Buttons for showing or hiding columns.
  m_VBox.append(m_ButtonBox);
  m_ButtonBox.set_halign(Gtk::Align::END);
  m_ButtonBox.append(*Gtk::make_managed<Gtk::Label>("Show columns"));
  for (int button = 0; button < CheckColumns::N_COLS; ++button)
  {
    m_ShowButtons[button].set_label(check_column_name[button]);
    m_ShowButtons[button].set_active(true);
    m_ShowButtons[button].signal_toggled().connect(sigc::bind(sigc::mem_fun(
      *this, &Example_ListView_TreeList::on_show_button_toggled), button));
    m_ButtonBox.append(m_ShowButtons[button]);
  }
}

Example_ListView_TreeList::~Example_ListView_TreeList()
{
}

void Example_ListView_TreeList::add_items()
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

Glib::RefPtr<Gio::ListModel> Example_ListView_TreeList::create_model(
  const Glib::RefPtr<Glib::ObjectBase>& item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(item);
  if (col && col->m_children.empty())
    // An item without children, i.e. a leaf in the tree. 
    return {};

  auto result = Gio::ListStore<ModelColumns>::create();
  const std::vector<CellItem_Holiday>& children = col ? col->m_children : m_vecItems;
  for (const auto& child : children)
    result->append(ModelColumns::create(child));
  return result;
}

void Example_ListView_TreeList::add_columns()
{
  /* column for holiday names */
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &Example_ListView_TreeList::on_setup_holiday));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &Example_ListView_TreeList::on_bind_holiday));
  auto column = Gtk::ColumnViewColumn::create("Holiday", factory);
  m_ColumnView.append_column(column);

  /* columns for Alex and other friends */
  for (int check_column = 0; check_column < CheckColumns::N_COLS; ++check_column)
  {
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(
      sigc::mem_fun(*this, &Example_ListView_TreeList::on_setup_checkbutton));
    factory->signal_bind().connect(sigc::bind(
      sigc::mem_fun(*this, &Example_ListView_TreeList::on_bind_checkbutton), check_column));
    m_ViewColumns[check_column] = Gtk::ColumnViewColumn::create(check_column_name[check_column], factory);
    m_ViewColumns[check_column]->set_fixed_width(60);
    m_ColumnView.append_column(m_ViewColumns[check_column]);
  }
}

void Example_ListView_TreeList::on_show_button_toggled(int button)
{
  m_ViewColumns[button]->set_visible(m_ShowButtons[button].get_active());
}

void Example_ListView_TreeList::on_setup_holiday(
  const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  // Each ListItem contains a TreeExpander, which contains a Label.
  // The Label shows the ModelColumns::m_holiday_name. That's done in on_bind_holiday(). 
  auto expander = Gtk::make_managed<Gtk::TreeExpander>();
  auto label = Gtk::make_managed<Gtk::Label>();
  label->set_halign(Gtk::Align::START);
  expander->set_child(*label);
  list_item->set_child(*expander);
}

void Example_ListView_TreeList::on_setup_checkbutton(
  const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto checkbutton = Gtk::make_managed<Gtk::CheckButton>();
  checkbutton->set_halign(Gtk::Align::CENTER);
  checkbutton->set_valign(Gtk::Align::CENTER);
  list_item->set_child(*checkbutton);
}

void Example_ListView_TreeList::on_bind_holiday(
  const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto row = std::dynamic_pointer_cast<Gtk::TreeListRow>(list_item->get_item());
  if (!row)
    return;
  auto col = std::dynamic_pointer_cast<ModelColumns>(row->get_item());
  if (!col)
    return;
  auto expander = dynamic_cast<Gtk::TreeExpander*>(list_item->get_child());
  if (!expander)
    return;
  expander->set_list_row(row);
  auto label = dynamic_cast<Gtk::Label*>(expander->get_child());
  if (!label)
    return;
  label->set_text(col->m_holiday_name);
}

void Example_ListView_TreeList::on_bind_checkbutton(
  const Glib::RefPtr<Gtk::ListItem>& list_item, int check_column)
{
  auto row = std::dynamic_pointer_cast<Gtk::TreeListRow>(list_item->get_item());
  if (!row)
    return;
  auto checkbutton = dynamic_cast<Gtk::CheckButton*>(list_item->get_child());
  if (!checkbutton)
    return;
  checkbutton->set_visible(!row->is_expandable());
  if (row->is_expandable())
    return;
  auto col = std::dynamic_pointer_cast<ModelColumns>(row->get_item());
  if (!col)
    return;
  const bool is_activatable = col->m_world_holiday || !is_european_hacker[check_column];
  list_item->set_activatable(is_activatable);
  if (is_activatable)
  {
    bool active = false;
    switch (check_column)
    {
    case CheckColumns::ALEX: active = col->m_alex; break;
    case CheckColumns::HAVOC: active = col->m_havoc; break;
    case CheckColumns::TIM: active = col->m_tim; break;
    case CheckColumns::OWEN: active = col->m_owen; break;
    case CheckColumns::DAVE: active = col->m_dave; break;
    }
    checkbutton->set_active(active);
  }
  else
    checkbutton->set_inconsistent(true);
}
