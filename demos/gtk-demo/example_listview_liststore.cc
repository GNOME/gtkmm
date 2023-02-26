/* Column View, List Store
 *
 * The Gio::ListStore is used to store data in list form, to be used
 * later on by a Gtk::ColumnView to display it. This demo builds a
 * simple Gio::ListStore and displays it.
 */

#include <gtkmm.h>
#include <iostream>
#include <typeinfo>

namespace
{
// A Gio::ListStore item that stores information about a bug.
class ModelColumns : public Glib::Object
{
public:
  // When m_property_fixed is a property, it's possible to bind it to
  // CheckButton::property_active() in the GUI.
  Glib::PropertyProxy<bool> property_fixed() { return m_property_fixed.get_proxy(); }
  unsigned int m_number;
  Glib::ustring m_severity;
  Glib::ustring m_description;
  // The Binding must be stored, because it shall be unbound, and a new
  // binding created, if the Gtk::ListItem instance is rebound to another
  // ModelColumns instance.
  Glib::RefPtr<Glib::Binding> m_binding_to_checkbutton;

  static Glib::RefPtr<ModelColumns> create(bool fixed, unsigned int number,
    const Glib::ustring& severity, const Glib::ustring& description)
  {
    return Glib::make_refptr_for_instance<ModelColumns>(
      new ModelColumns(fixed, number, severity, description));
  }
  
protected:
  ModelColumns(bool fixed, unsigned int number,
    const Glib::ustring& severity, const Glib::ustring& description)
    // A class that uses Glib::Property must register a new GType. 
  : Glib::ObjectBase(typeid(ModelColumns)),
    m_number(number), m_severity(severity), m_description(description),
    m_property_fixed(*this, "fixed", fixed)
  {
    property_fixed().signal_changed().connect(
      sigc::mem_fun(*this, &ModelColumns::on_fixed_changed));
  }

  Glib::Property<bool> m_property_fixed;

  void on_fixed_changed()
  {
    std::cout << "Bug " << m_number <<  (property_fixed() ? ""  : " not") << " fixed\n";
  }
}; // ModelColumns

} // anonymous namespace

class Example_ListView_ListStore : public Gtk::Window
{
public:
  Example_ListView_ListStore();
  ~Example_ListView_ListStore() override;

protected:
  void create_model();
  void add_columns();
  void liststore_add_item(bool fixed, unsigned int number,
    const Glib::ustring& severity, const Glib::ustring& description);

  // Signal handlers:
  void on_setup_checkbutton(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item, Gtk::Align halign);
  void on_bind_fixed(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_unbind_fixed(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_number(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_severity(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_description(const Glib::RefPtr<Gtk::ListItem>& list_item);

  //Member widgets:
  Gtk::Box m_VBox;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::Label m_Label;
  Gtk::ColumnView m_ColumnView;
  Glib::RefPtr<Gio::ListStore<ModelColumns>> m_ListStore;
  Glib::RefPtr<Gtk::SingleSelection> m_selection_model;
};


//Called by DemoWindow;
Gtk::Window* do_listview_liststore()
{
  return new Example_ListView_ListStore();
}


Example_ListView_ListStore::Example_ListView_ListStore()
: m_VBox(Gtk::Orientation::VERTICAL, 8),
  m_Label("This is the bug list (note: not based on real data).")
{
  set_title("Gio::ListStore demo");
  set_default_size(280, 250);

  m_VBox.set_margin(8);
  set_child(m_VBox);
  m_VBox.append(m_Label);

  m_ScrolledWindow.set_has_frame(true);
  m_ScrolledWindow.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();
  m_VBox.append(m_ScrolledWindow);

  /* create model */
  create_model();

  /* create column view */
  m_selection_model = Gtk::SingleSelection::create(m_ListStore);
  m_selection_model->set_autoselect(false);
  m_selection_model->set_can_unselect(true);
  m_ColumnView.set_model(m_selection_model);
  m_ColumnView.set_reorderable(false);
  m_ColumnView.add_css_class("data-table");
  add_columns();

  m_ScrolledWindow.set_child(m_ColumnView);
}

Example_ListView_ListStore::~Example_ListView_ListStore()
{
}

void Example_ListView_ListStore::create_model()
{
  m_ListStore = Gio::ListStore<ModelColumns>::create();

  liststore_add_item(false, 60482, "Normal",     "scrollable notebooks and hidden tabs");
  liststore_add_item(false, 60620, "Critical",   "gdk_window_clear_area (gdkwindow-win32.c) is not thread-safe");
  liststore_add_item(false, 50214, "Major",      "Xft support does not clean up correctly");
  liststore_add_item(true,  52877, "Major",      "GtkFileSelection needs a refresh method. ");
  liststore_add_item(false, 56070, "Normal",     "Can not click button after setting insensitive");
  liststore_add_item(true,  56355, "Normal",     "GtkLabel - Not all changes propagate correctly");
  liststore_add_item(false, 50055, "Normal",     "Rework width/height computations for TreeView");
  liststore_add_item(false, 58278, "Normal",     "gtk_dialog_set_response_sensitive () does nott work");
  liststore_add_item(false, 55767, "Normal",     "Getters for all setters");
  liststore_add_item(false, 56925, "Normal",     "Gtkcalender size");
  liststore_add_item(false, 56221, "Normal",     "Selectable label needs right-click copy menu");
  liststore_add_item(true,  50939, "Normal",     "Add shift clicking to GtkTextView");
  liststore_add_item(false, 6112,  "Enhancement","netscape-like collapsable toolbars");
  liststore_add_item(false, 1,     "Normal",     "First bug :=)");
}

void Example_ListView_ListStore::liststore_add_item(bool fixed, unsigned int number,
  const Glib::ustring& severity, const Glib::ustring& description)
{
  m_ListStore->append(ModelColumns::create(fixed, number, severity, description));
}

void Example_ListView_ListStore::add_columns()
{
  /* column for fixed toggles */
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &Example_ListView_ListStore::on_setup_checkbutton));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &Example_ListView_ListStore::on_bind_fixed));
  factory->signal_unbind().connect(
    sigc::mem_fun(*this, &Example_ListView_ListStore::on_unbind_fixed));
  auto column = Gtk::ColumnViewColumn::create("Fixed?", factory);
  column->set_fixed_width(60);
  m_ColumnView.append_column(column);

  /* column for bug numbers */
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this,
    &Example_ListView_ListStore::on_setup_label), Gtk::Align::END));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &Example_ListView_ListStore::on_bind_number));
  column = Gtk::ColumnViewColumn::create("Bug number", factory);
  m_ColumnView.append_column(column);

  /* column for severities */
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this,
    &Example_ListView_ListStore::on_setup_label), Gtk::Align::START));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &Example_ListView_ListStore::on_bind_severity));
  column = Gtk::ColumnViewColumn::create("Severity", factory);
  m_ColumnView.append_column(column);

  /* column for descriptions */
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this,
    &Example_ListView_ListStore::on_setup_label), Gtk::Align::START));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &Example_ListView_ListStore::on_bind_description));
  column = Gtk::ColumnViewColumn::create("Description", factory);
  m_ColumnView.append_column(column);
}

void Example_ListView_ListStore::on_setup_checkbutton(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto checkbutton = Gtk::make_managed<Gtk::CheckButton>();
  checkbutton->set_halign(Gtk::Align::CENTER);
  checkbutton->set_valign(Gtk::Align::CENTER);
  list_item->set_child(*checkbutton);
}

void Example_ListView_ListStore::on_setup_label(
  const Glib::RefPtr<Gtk::ListItem>& list_item, Gtk::Align halign)
{
  list_item->set_child(*Gtk::make_managed<Gtk::Label>("", halign));
}

void Example_ListView_ListStore::on_bind_fixed(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto checkbutton = dynamic_cast<Gtk::CheckButton*>(list_item->get_child());
  if (!checkbutton)
    return;
  checkbutton->set_active(col->property_fixed());

  // Bind the status of the CheckButton to property_fixed() in the
  // bound ModelColumns instance. When the CheckButton is toggled,
  // the corresponding property_fixed() is also toggled.  
  if (col->m_binding_to_checkbutton)
    col->m_binding_to_checkbutton->unbind();
  col->m_binding_to_checkbutton = Glib::Binding::bind_property(
    checkbutton->property_active(), col->property_fixed(),
    Glib::Binding::Flags::BIDIRECTIONAL);
}

void Example_ListView_ListStore::on_unbind_fixed(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  if (col->m_binding_to_checkbutton)
    col->m_binding_to_checkbutton->unbind();
  col->m_binding_to_checkbutton.reset();
}

void Example_ListView_ListStore::on_bind_number(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Glib::ustring::format(col->m_number));
}

void Example_ListView_ListStore::on_bind_severity(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(col->m_severity);
}

void Example_ListView_ListStore::on_bind_description(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(col->m_description);
}
