/* Column View, Editable Cells
 *
 * This demo demonstrates the use of editable cells in a Gtk::ColumnView.
 * Each editable cell contains a Gtk::EditableLabel.
 */

#include <cstdlib>
#include <iostream>
#include <gtkmm.h>

class Example_ListView_EditableCells : public Gtk::Window
{
public:
  Example_ListView_EditableCells();
  ~Example_ListView_EditableCells() override;

protected:
  class ModelColumns : public Glib::Object
  {
  public:
    int m_number;
    Glib::ustring m_product;

    static Glib::RefPtr<ModelColumns> create(
      int number, const Glib::ustring& product)
    {
      return Glib::make_refptr_for_instance<ModelColumns>(
        new ModelColumns(number, product));
    }
    
  protected:
    ModelColumns(int number, const Glib::ustring& product)
    : m_number(number), m_product(product)
    { }
  }; // ModelColumns

  void create_model();
  void add_columns();
  void liststore_add_item(int number, const Glib::ustring& product);

  //Signal handlers:
  void on_button_add_clicked();
  void on_button_remove_clicked();
  void on_number_edited(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_product_edited(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_setup_number(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_setup_product(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_number(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_product(const Glib::RefPtr<Gtk::ListItem>& list_item);

  //Member widgets:
  Gtk::Box m_VBox;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::Label m_Label;
  Gtk::ColumnView m_ColumnView;
  Glib::RefPtr<Gio::ListStore<ModelColumns>> m_ListStore;
  Glib::RefPtr<Gtk::SingleSelection> m_selection_model;
  Gtk::Box m_HBox;
  Gtk::Button m_Button_Add;
  Gtk::Button m_Button_Remove;
};


//Called by DemoWindow;
Gtk::Window* do_listview_editable_cells()
{
  return new Example_ListView_EditableCells();
}


Example_ListView_EditableCells::Example_ListView_EditableCells()
: m_VBox(Gtk::Orientation::VERTICAL, 5),
  m_Label("Shopping list (you can edit the cells!)"),
  m_HBox(Gtk::Orientation::HORIZONTAL, 4),
  m_Button_Add("Add item"),
  m_Button_Remove("Remove item")
{
  set_title("Shopping List");
  set_default_size(320, 300);

  m_VBox.set_margin(5);
  set_child(m_VBox);
  m_VBox.append(m_Label);

  m_ScrolledWindow.set_has_frame(true);
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
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

  /* some buttons */
  m_VBox.append(m_HBox);
  m_HBox.set_vexpand(false);

  m_HBox.append(m_Button_Add);
  m_Button_Add.set_expand();
  m_Button_Add.signal_clicked().connect(
    sigc::mem_fun(*this, &Example_ListView_EditableCells::on_button_add_clicked));

  m_HBox.append(m_Button_Remove);
  m_Button_Remove.set_expand();
  m_Button_Remove.signal_clicked().connect(
    sigc::mem_fun(*this, &Example_ListView_EditableCells::on_button_remove_clicked));
}

Example_ListView_EditableCells::~Example_ListView_EditableCells()
{
}

void Example_ListView_EditableCells::create_model()
{
  m_ListStore = Gio::ListStore<ModelColumns>::create();

  liststore_add_item(3, "bottles of coke");
  liststore_add_item(5, "packages of noodles");
  liststore_add_item(2, "packages of chocolate chip cookies");
  liststore_add_item(1, "can vanilla ice cream");
  liststore_add_item(6, "eggs");
}

void Example_ListView_EditableCells::liststore_add_item(
  int number, const Glib::ustring& product)
{
  m_ListStore->append(ModelColumns::create(number, product));
}

void Example_ListView_EditableCells::on_number_edited(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto label = dynamic_cast<Gtk::EditableLabel*>(list_item->get_child());
  if (!label)
    return;
  if (label->get_editing())
    return;
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;

  // Convert the new text to a number.
  auto new_text = label->get_text();
  int new_value = -1;
  try
  {
    new_value = std::stoi(new_text.raw());
  }
  catch (const std::exception& err)
  {
    std::cout << "Could not convert \"" << new_text << "\" to an integer. ("
      << err.what() << ")" << std::endl;
  }
  // Store the new value in the model.
  col->m_number = new_value;
  label->set_text(Glib::ustring::format(new_value));
}

void Example_ListView_EditableCells::on_product_edited(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto label = dynamic_cast<Gtk::EditableLabel*>(list_item->get_child());
  if (!label)
    return;
  if (label->get_editing())
    return;
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;

  // Store the new text in the model.
  col->m_product = label->get_text();
}

void Example_ListView_EditableCells::add_columns()
{
  /* column for numbers */
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &Example_ListView_EditableCells::on_setup_number));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &Example_ListView_EditableCells::on_bind_number));
  auto column = Gtk::ColumnViewColumn::create("Number", factory);
  m_ColumnView.append_column(column);

  /* column for products */
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &Example_ListView_EditableCells::on_setup_product));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &Example_ListView_EditableCells::on_bind_product));
  column = Gtk::ColumnViewColumn::create("Product", factory);
  m_ColumnView.append_column(column);
}

void Example_ListView_EditableCells::on_setup_number(
  const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto label = Gtk::make_managed<Gtk::EditableLabel>();
  label->set_alignment(1.0);
  label->property_editing().signal_changed().connect(sigc::bind(sigc::mem_fun(
    *this, &Example_ListView_EditableCells::on_number_edited), list_item));
  list_item->set_child(*label);
}

void Example_ListView_EditableCells::on_setup_product(
  const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto label = Gtk::make_managed<Gtk::EditableLabel>();
  label->set_alignment(0.0);
  label->property_editing().signal_changed().connect(sigc::bind(sigc::mem_fun(
    *this, &Example_ListView_EditableCells::on_product_edited), list_item));
  list_item->set_child(*label);
}

void Example_ListView_EditableCells::on_bind_number(
  const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::EditableLabel*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Glib::ustring::format(col->m_number));
}

void Example_ListView_EditableCells::on_bind_product(
  const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::EditableLabel*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(col->m_product);
}

void Example_ListView_EditableCells::on_button_add_clicked()
{
  liststore_add_item(0, "Description here");
}

void Example_ListView_EditableCells::on_button_remove_clicked()
{
  // If an item is selected, remove it from the ListStore.
  auto position = m_selection_model->get_selected();
  if (position != GTK_INVALID_LIST_POSITION)
    m_ListStore->remove(position);
}
