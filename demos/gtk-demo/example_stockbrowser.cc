/* Stock Item and Icon Browser
 *
 * The source code for this demo is only really useful
 * for the use of Gtk::TreeView, as it demonstrates a few
 * things not seen in other demos, such as packing multiple
 * renderers into one column and using Gtk::CellRendererPixbuf
 * successfully. The code for retrieving and displaying all
 * stock items probably won't be useful for the vast majority
 * of applications
 */

#include <gtkmm.h>

class Example_StockBrowser: public Gtk::Window
{
public:
  Example_StockBrowser();
  virtual ~Example_StockBrowser();

protected:

  //signal handlers:
  virtual void on_selection_changed();

  virtual Glib::RefPtr<Gtk::TreeModel> create_model();
  static Glib::ustring id_to_symbol(const Gtk::StockID& stockid); // convert StockID to Gtk::Stock symbol

  //Child widgets:
  Gtk::Frame m_Frame;
  Gtk::VBox m_VBox;
  Gtk::HBox m_HBox;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Glib::RefPtr<Gtk::TreeModel> m_refTreeModel;
  Gtk::TreeView m_TreeView;
  Gtk::Alignment m_Alignment;
  Glib::RefPtr<Gtk::TreeSelection> m_refTreeSelection;

  Gtk::Label m_Label_Type;
  Gtk::Label m_Label_Symbol;
  Gtk::Label m_Label_ID;
  Gtk::Label m_Label_Accel;
  Gtk::Image m_Image;

  struct ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
    Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> >  icon;
    Gtk::TreeModelColumn<Glib::ustring>                symbol;
    Gtk::TreeModelColumn<Glib::ustring>                label;
    Gtk::TreeModelColumn<Glib::ustring>                accel;
    Gtk::TreeModelColumn<Gtk::StockID>                 id;

    ModelColumns() { add(icon); add(symbol); add(label); add(accel); add(id); }
  };

  const ModelColumns m_columns;
};


Gtk::Window* do_stock_browser()
{
  return new Example_StockBrowser();
}

Example_StockBrowser::Example_StockBrowser()
:
  m_Frame("Selected Item"),
  m_VBox(false, 8),
  m_HBox(false, 8),
  m_Alignment(Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP, 0.0, 0.0)
{
  set_title("Stock Icons and Items");
  set_default_size(-1, 500);
  set_border_width(8);

  add(m_HBox);
  m_ScrolledWindow.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
  m_HBox.pack_start(m_ScrolledWindow, Gtk::PACK_SHRINK);

  // create the TreeModel with all the stock item data in it
  m_refTreeModel = create_model();

  // create the TreeView, associate the TreeModel with it
  m_TreeView .set_model(m_refTreeModel);
  m_ScrolledWindow.add(m_TreeView);

  // add columns to the TreeView, mapping model Columns to TreeView m_columns::

  { //The pixbuf/text column:
    Gtk::TreeView::Column* pColumn = Gtk::manage( new Gtk::TreeView::Column("Symbol") );  //We specify the renderer(s) after construction.

    // The icon/symbol column uses two CellRenderers: Here we see why Gtk::TreeView is so good
    // m_columns.icon and m_columns.symbol are columns in the model. pColumn is the column in the TreeView:

    pColumn->pack_start(m_columns.icon, false);
    pColumn->pack_start(m_columns.symbol);

    m_TreeView.append_column(*pColumn);
  }

  // the label column
  m_TreeView.append_column("Label", m_columns.label); //Defaults to CellRendererText for a string model column.

  // the accelerator column
  m_TreeView.append_column("Accelerator", m_columns.accel); //Defaults to CellRendererText for a string model column.

  // the ID column
  m_TreeView.append_column("ID", m_columns.id); //Defaults to CellRendererText for a string model column.

  m_HBox.pack_end(m_Alignment);
  m_Alignment.add(m_Frame);

  m_VBox.set_border_width(4);
  m_Frame.add(m_VBox);

  m_VBox.pack_start(m_Label_Type, Gtk::PACK_SHRINK);
  m_VBox.pack_start(m_Image, Gtk::PACK_SHRINK);
  m_VBox.pack_start(m_Label_Accel, Gtk::PACK_SHRINK);
  m_VBox.pack_start(m_Label_Symbol, Gtk::PACK_SHRINK);
  m_VBox.pack_start(m_Label_ID, Gtk::PACK_SHRINK);

  m_refTreeSelection = m_TreeView.get_selection();
  m_refTreeSelection->set_mode(Gtk::SELECTION_SINGLE);
  m_refTreeSelection->signal_changed().connect(
      SigC::slot(*this, &Example_StockBrowser::on_selection_changed));

  show_all();
}

Example_StockBrowser::~Example_StockBrowser()
{
}

Glib::RefPtr<Gtk::TreeModel> Example_StockBrowser::create_model()
{
  Glib::RefPtr<Gtk::ListStore> refStore = Gtk::ListStore::create(m_columns);
  refStore->set_sort_column_id(m_columns.id, Gtk::SORT_ASCENDING);

  // obtain the ids of all stock items
  typedef std::vector<Gtk::StockID> type_vecIDs;
  const type_vecIDs vecIDs = Gtk::Stock::get_ids();

  // iterate through them, populating the ListStore as appropriate
  for(type_vecIDs::const_iterator iterIDs = vecIDs.begin(); iterIDs != vecIDs.end(); ++iterIDs)
  {
    const Gtk::StockID& stockid = *iterIDs;

    // Add a new empty row to the ListStore:
    Gtk::TreeModel::Row row = *(refStore->append());

    // Populate ID and symbol columns:
    row[m_columns.id]     = stockid;
    row[m_columns.symbol] = id_to_symbol(stockid);

    // get a Gtk::StockItem object for use:
    Gtk::StockItem item;
    if(Gtk::Stock::lookup(stockid, item))
    {
      // Populate Accel column, if the stock item has an accelerator key.
      if(const unsigned int keyval = item.get_keyval())
        row[m_columns.accel] = Gtk::AccelGroup::name(keyval, item.get_modifier());

      row[m_columns.label] = item.get_label();
    }

    // Populate icon column:
    row[m_columns.icon] = render_icon(stockid, Gtk::ICON_SIZE_MENU);
  }

  return refStore;
}

/* gtk-foo-bar -> Gtk::Stock::FOO_BAR
 */
Glib::ustring Example_StockBrowser::id_to_symbol(const Gtk::StockID& stockid)
{
  static const char prefix[] = "gtk-";
  const size_t prefix_length = sizeof(prefix) - 1;

  const Glib::ustring id = stockid.get_string();
  Glib::ustring::const_iterator id_pos = id.begin();

  Glib::ustring scope;

  if((id.length() >= prefix_length) && (id.compare(0, prefix_length, prefix) == 0))
  {
    scope = "Gtk::Stock::";
    std::advance(id_pos, prefix_length);
  }

  Glib::ustring symbol;
  std::replace_copy(id_pos, id.end(), std::back_inserter(symbol), gunichar('-'), gunichar('_'));

  return scope + symbol.uppercase();
}

// triggered when TreeView selection changes
void Example_StockBrowser::on_selection_changed()
{
  // put all the nice data stuff in the box on the right

  // Access the model "row" corresponding to the selected TreeView "row".
  if(const Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected())
  {
    const Gtk::TreeModel::Row row = *iter;

    // get the data out of the model
    const Gtk::StockID stockid = row[m_columns.id];
    const Glib::ustring symbol = row[m_columns.symbol];
    const Glib::ustring accel  = row[m_columns.accel];
    const Glib::ustring label  = row[m_columns.label];
    const Glib::RefPtr<Gdk::Pixbuf> icon = row[m_columns.icon];

    // Show what data was available:
    const char* type_text = "???????";

    if(!label.empty() && icon)  type_text = "Icon and Item";
    else if(icon)               type_text = "Icon Only";
    else if(!label.empty())     type_text = "Item Only";

    m_Label_Type.set_text(type_text);
    m_Label_Symbol.set_text(symbol);
    m_Label_ID.set_text(stockid.get_string());
    m_Label_Accel.set_text_with_mnemonic(label + ' ' + accel);

    if(icon) //If there's a stock icon:
    {
      // find the largest size the icon comes in:
      const Gtk::IconSet iconset = Gtk::IconSet::lookup_default(stockid);

      typedef std::vector<Gtk::IconSize> type_vecSizes;
      const type_vecSizes sizes = iconset.get_sizes();

      Gtk::IconSize best_size = Gtk::ICON_SIZE_INVALID;
      int biggest_pixelcount = 0;

      for(type_vecSizes::const_iterator psize = sizes.begin(); psize != sizes.end(); ++psize)
      {
        int width  = 0;
        int height = 0;
        Gtk::IconSize::lookup(*psize, width, height);

        if(width * height > biggest_pixelcount)
        {
          biggest_pixelcount = width * height;
          best_size = *psize;
        }
      }

      m_Image.set(stockid, best_size);
    }
    else
    {
      m_Image.clear();
    }
  }
  else
  {
    m_Label_Type.set_text("No selected item");
    m_Label_Symbol.set_text("");
    m_Label_ID.set_text("");
    m_Label_Accel.set_text("");
    m_Image.clear();
  }
}

