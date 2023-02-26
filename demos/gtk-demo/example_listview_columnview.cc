/* Column View
 *
 * Gtk::ColumnView is a widget to present a view into a large dynamic list of
 * items using multiple columns with headers. However, the list in this demo is
 * neither large nor dynamic.
 */

#include <gtkmm.h>

class MyObject : public Glib::Object
{
public:
  enum NamePart
  {
    FIRST,
    SECOND
  };

  static Glib::RefPtr<MyObject> create(
    const Glib::ustring& first_name, const Glib::ustring& second_name)
  {
    return Glib::make_refptr_for_instance<MyObject>(new MyObject{first_name, second_name});
  }

  void set_name(const Glib::ustring& first_name, const Glib::ustring& second_name)
  {
    m_name[FIRST] = first_name;
    m_name[SECOND] = second_name;
  }

  Glib::ustring get_name(NamePart name_part) const { return m_name[name_part]; }

protected:
  MyObject(const Glib::ustring& first_name, const Glib::ustring& second_name)
  : m_name{first_name, second_name}
  {
  }

private:
  Glib::ustring m_name[2];
};

class Example_Listview_ColumnView : public Gtk::Window
{
public:
  Example_Listview_ColumnView();
  ~Example_Listview_ColumnView() override;

protected:
  // Signal handlers:
  void on_setup_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item,
                        MyObject::NamePart name_part);

  // Member widget:
  Gtk::ColumnView m_ColumnView;
};

// Called by DemoWindow
Gtk::Window* do_listview_columnview()
{
  return new Example_Listview_ColumnView();
}

Example_Listview_ColumnView::Example_Listview_ColumnView()
{
  set_title("Gtk::ColumnView");
  set_default_size(300, 200);

  auto store = Gio::ListStore<MyObject>::create();
  store->append(MyObject::create("Joe", "Brown"));
  store->append(MyObject::create("Mary", "West"));
  store->append(MyObject::create("Danny", "Jones"));

  m_ColumnView.set_model(Gtk::SingleSelection::create(store));
  m_ColumnView.add_css_class("data-table");
  set_child(m_ColumnView);

  // First column
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &Example_Listview_ColumnView::on_setup_listitem));
  factory->signal_bind().connect(
    sigc::bind(sigc::mem_fun(*this, &Example_Listview_ColumnView::on_bind_listitem),
      MyObject::FIRST));
  auto col = Gtk::ColumnViewColumn::create("First Name", factory);
  m_ColumnView.append_column(col);

  // Second column
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &Example_Listview_ColumnView::on_setup_listitem));
  factory->signal_bind().connect(
    sigc::bind(sigc::mem_fun(*this, &Example_Listview_ColumnView::on_bind_listitem),
      MyObject::SECOND));
  col = Gtk::ColumnViewColumn::create("Second Name", factory);
  m_ColumnView.append_column(col);
}

Example_Listview_ColumnView::~Example_Listview_ColumnView()
{
}

void Example_Listview_ColumnView::on_setup_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  list_item->set_child(*Gtk::make_managed<Gtk::Label>());
}

void Example_Listview_ColumnView::on_bind_listitem(
  const Glib::RefPtr<Gtk::ListItem>& list_item, MyObject::NamePart name_part)
{
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (label)
  {
    auto item = list_item->get_item();
    if (auto mo = std::dynamic_pointer_cast<MyObject>(item))
      label->set_text(mo->get_name(name_part));
  }
}
