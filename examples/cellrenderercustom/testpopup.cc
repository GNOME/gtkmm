
#include "cellrendererlist.h"
#include <gtkmm.h>
#include <sstream>


namespace
{

class AppWindow : public Gtk::Window
{
public:
  AppWindow();
  virtual ~AppWindow();

private:
  struct ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
    Gtk::TreeModelColumn<Glib::ustring> text1;
    Gtk::TreeModelColumn<Glib::ustring> text2;

    ModelColumns() { add(text1); add(text2); }
  };

  ModelColumns                  list_columns_;
  Glib::RefPtr<Gtk::ListStore>  list_store_;
  Gtk::TreeView                 tree_view_;

  void on_cell_edited(const Glib::ustring& path, const Glib::ustring& new_text);
};


AppWindow::AppWindow()
:
  list_columns_ (),
  list_store_   (Gtk::ListStore::create(list_columns_)),
  tree_view_    (list_store_)
{
  add(tree_view_);

  tree_view_.append_column("Text 1", list_columns_.text1);

  {
    CellRendererList    *const renderer = new CellRendererList();
    Gtk::TreeViewColumn *const column   = new Gtk::TreeViewColumn("Text 2", *Gtk::manage(renderer));
    tree_view_.append_column(*Gtk::manage(column));

    column->add_attribute(renderer->property_text(), list_columns_.text2);

    renderer->append_list_item("foo");
    renderer->append_list_item("bar");
    renderer->append_list_item("bazz");
    renderer->append_list_item("fuzz");
    renderer->append_list_item("sliff");
    renderer->append_list_item("sloff");

    renderer->property_editable() = true;
    renderer->signal_edited().connect(sigc::mem_fun(*this, &AppWindow::on_cell_edited));
  }

  std::ostringstream output (std::ios::ate);

  for(int i = 1; i <= 10; ++i)
  {
    output.str("row #");
    output << i;

    Gtk::TreeModel::Row row = *list_store_->append();

    row[list_columns_.text1] = output.str();
    row[list_columns_.text2] = "foobar!";
  }

  show_all_children();
}

AppWindow::~AppWindow()
{}

void AppWindow::on_cell_edited(const Glib::ustring& path, const Glib::ustring& new_text)
{
  // Get the model row that has been edited.
  Gtk::TreeModel::Row row = *list_store_->get_iter(Gtk::TreeModel::Path(path));

  row[list_columns_.text2] = new_text;
}

} // anonymous namespace


int main(int argc, char** argv)
{
  Gtk::Main main_instance (&argc, &argv);

  AppWindow window;
  Gtk::Main::run(window);

  return 0;
}

