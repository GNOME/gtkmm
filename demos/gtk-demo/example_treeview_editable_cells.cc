/* Tree View/Editable Cells
 *
 * This demo demonstrates the use of editable cells in a Gtk::TreeView. If
 * you're new to the Gtk::TreeView widgets and associates, look into
 * the Gtk::ListStore example first.
 *
 */

#include <cstdlib>
#include <iostream>
#include <gtkmm.h>

class CellItem_Product
{
public:
  CellItem_Product();
  CellItem_Product(const CellItem_Product& src);
  ~CellItem_Product();
  CellItem_Product& operator=(const CellItem_Product& src);

  int m_number;
  Glib::ustring m_product;
};

class Example_TreeView_EditableCells : public Gtk::Window
{
public:
  Example_TreeView_EditableCells();
  ~Example_TreeView_EditableCells() override;

protected:
  //signal handlers:
  virtual void on_button_add_clicked();
  virtual void on_button_remove_clicked();

  virtual void create_model();
  virtual void add_columns();
  virtual void add_items();
  virtual void liststore_add_item(const CellItem_Product& foo);

  //We only have these signal handlers here, because the append_column_editable() convenience methods do not work with
  //the IRIX MipsPro compiler.
  virtual void on_column_number_edited(const Glib::ustring& path_string, const Glib::ustring& new_text);
  virtual void on_column_product_edited(const Glib::ustring& path_string, const Glib::ustring& new_text);

  //Member widgets:
  Gtk::Box m_VBox;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::Label m_Label;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::ListStore> m_refListStore;
  Gtk::Box m_HBox;
  Gtk::Button m_Button_Add, m_Button_Remove;

  std::vector<CellItem_Product> m_vecItems;

  struct ModelColumns : public Gtk::TreeModelColumnRecord
  {
    Gtk::TreeModelColumn<int>           number;
    Gtk::TreeModelColumn<Glib::ustring> product;

    ModelColumns() { add(number); add(product); }
  };

  const ModelColumns m_columns;
};


CellItem_Product::CellItem_Product()
{
  m_number = 0;
}

CellItem_Product::CellItem_Product(const CellItem_Product& src)
{
  operator=(src);
}

CellItem_Product::~CellItem_Product()
{
}

CellItem_Product& CellItem_Product::operator=(const CellItem_Product& src)
{
  m_number = src.m_number;
  m_product = src.m_product;

  return *this;
}


//Called by DemoWindow;
Gtk::Window* do_treeview_editable_cells()
{
  return new Example_TreeView_EditableCells();
}


Example_TreeView_EditableCells::Example_TreeView_EditableCells()
: m_VBox(Gtk::Orientation::VERTICAL, 5),
  m_Label("Shopping list (you can edit the cells!)"),
  m_HBox(Gtk::Orientation::HORIZONTAL, 4),
  m_Button_Add("Add item"),
  m_Button_Remove("Remove item")
{
  set_title("Shopping List");
  set_default_size(320, 200);

  m_VBox.property_margin() = 5;
  add(m_VBox);
  m_VBox.pack_start(m_Label, Gtk::PackOptions::SHRINK);

  m_ScrolledWindow.set_shadow_type(Gtk::ShadowType::ETCHED_IN);
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_VBox.pack_start(m_ScrolledWindow, Gtk::PackOptions::EXPAND_WIDGET);

  /* create model */
  create_model();

  /* create tree view */
  m_TreeView.set_model(m_refListStore);
  auto refTreeSelection = m_TreeView.get_selection();
  refTreeSelection->set_mode(Gtk::SelectionMode::SINGLE);

  add_columns();
  m_ScrolledWindow.add(m_TreeView);

  /* some buttons */
  m_VBox.pack_start(m_HBox, Gtk::PackOptions::SHRINK);

  m_HBox.pack_start(m_Button_Add, Gtk::PackOptions::EXPAND_WIDGET);
  m_HBox.set_vexpand(false);

  m_Button_Add.signal_clicked().connect(
    sigc::mem_fun(*this, &Example_TreeView_EditableCells::on_button_add_clicked));

  m_HBox.pack_start(m_Button_Remove, Gtk::PackOptions::EXPAND_WIDGET);
  m_Button_Remove.signal_clicked().connect(
    sigc::mem_fun(*this, &Example_TreeView_EditableCells::on_button_remove_clicked));
}

Example_TreeView_EditableCells::~Example_TreeView_EditableCells()
{
}

void Example_TreeView_EditableCells::add_items()
{
  CellItem_Product foo;

  foo.m_number = 3;
  foo.m_product = "bottles of coke";
  m_vecItems.push_back(foo);

  foo.m_number = 5;
  foo.m_product = "packages of noodles";
  m_vecItems.push_back(foo);

  foo.m_number = 2;
  foo.m_product = "packages of chocolate chip cookies";
  m_vecItems.push_back(foo);

  foo.m_number = 1;
  foo.m_product = "can vanilla ice cream";
  m_vecItems.push_back(foo);

  foo.m_number = 6;
  foo.m_product = "eggs";
  m_vecItems.push_back(foo);
}

void Example_TreeView_EditableCells::create_model()
{
  m_refListStore = Gtk::ListStore::create(m_columns);

  /* add items */
  add_items();

  std::for_each(
      m_vecItems.begin(), m_vecItems.end(),
      sigc::mem_fun(*this, &Example_TreeView_EditableCells::liststore_add_item));
}

void Example_TreeView_EditableCells::liststore_add_item(const CellItem_Product& foo)
{
  auto row = *(m_refListStore->append());

  row[m_columns.number]   = foo.m_number;
  row[m_columns.product]  = foo.m_product;
}

//We only have these signal handlers here, because the append_column_editable() convenience methods do not work with
//the IRIX MipsPro compiler.
void Example_TreeView_EditableCells::on_column_number_edited(const Glib::ustring& path_string, const Glib::ustring& new_text)
{
  Gtk::TreePath path(path_string);

  //Get the row from the path:
  auto refModel = m_TreeView.get_model();
  if(refModel)
  {
    auto iter = refModel->get_iter(path);
    if(iter)
    {
      //Convert the text to a number, using the same logic used by GtkCellRendererText when it stores numbers.
      int new_value = 0;
      try
      {
        new_value = std::stoi(new_text);
      }
      catch (const std::exception& err)
      {
        std::cout << "Could not convert \"" << new_text << "\" to an integer. ("
          << err.what() << ")" << std::endl;
      }

      //Store the user's new text in the model:
      auto row = *iter;
      row[m_columns.number] = new_value;
    }
  }
}

void Example_TreeView_EditableCells::on_column_product_edited(const Glib::ustring& path_string, const Glib::ustring& new_text)
{
  Gtk::TreePath path(path_string);

  //Get the row from the path:
  auto refModel = m_TreeView.get_model();
  if(refModel)
  {
    auto iter = refModel->get_iter(path);
    if(iter)
    {
        //Store the user's new text in the model:
        auto row = *iter;
        row[m_columns.product] = new_text;
    }
  }
}

void Example_TreeView_EditableCells::add_columns()
{
  //This is the wasy way:
  // number column:
  //m_TreeView.append_column_editable("Number", m_columns.number);
  //
  // product column:
  //m_TreeView.append_column_editable("Product", m_columns.product);

  //And this is the way that works with the IRIX MipsPro compiler too:
  {
    auto pViewColumn = Gtk::make_managed<Gtk::TreeView::Column>("Number", m_columns.number);

    //connect signal handlers for auto-storing of edited cell data
    auto pCellRenderer = pViewColumn->get_first_cell();
    auto pCellRenderText = dynamic_cast<Gtk::CellRendererText*>(pCellRenderer);
    if(pCellRenderText)
    {
      //Set the appropriate property,
      pCellRenderText->property_editable() = true;

      //Connect to the appropriate signal, sending the model_column too,
      pCellRenderText->signal_edited().connect( sigc::mem_fun(*this, &Example_TreeView_EditableCells::on_column_number_edited) );
    }

    m_TreeView.append_column(*pViewColumn);
  }

  {
    auto pViewColumn = Gtk::make_managed<Gtk::TreeView::Column>("Product", m_columns.product);

    //connect signal handlers for auto-storing of edited cell data
    auto pCellRenderer = pViewColumn->get_first_cell();
    auto pCellRenderText = dynamic_cast<Gtk::CellRendererText*>(pCellRenderer);
    if(pCellRenderText)
    {
      //Set the appropriate property,
      pCellRenderText->property_editable() = true;

      //Connect to the appropriate signal, sending the model_column too,
      pCellRenderText->signal_edited().connect( sigc::mem_fun(*this, &Example_TreeView_EditableCells::on_column_product_edited) );
    }

    m_TreeView.append_column(*pViewColumn);
  }


}


void Example_TreeView_EditableCells::on_button_add_clicked()
{
  CellItem_Product foo;
  foo.m_number = 0;
  foo.m_product = "Description here";
  m_vecItems.push_back(foo);

  liststore_add_item(foo);
}

void Example_TreeView_EditableCells::on_button_remove_clicked()
{
  auto refSelection = m_TreeView.get_selection();

  if(const auto iter = refSelection->get_selected())
  {
    const Gtk::TreeModel::Path path(iter);
    const unsigned int index = path.front();

    // Remove item from ListStore:
    m_refListStore->erase(iter);

    // Remove item from vecItems.
    if(index < m_vecItems.size())
      m_vecItems.erase(m_vecItems.begin() + index);
  }
}
