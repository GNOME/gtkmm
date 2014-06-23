/* Icon Theme
 *
 * The source code for this demo is only really useful
 * for the use of Gtk::TreeView, as it demonstrates a few
 * things not seen in other demos, such as packing multiple
 * renderers into one column and using Gtk::CellRendererPixbuf
 * successfully. The code for retrieving and displaying all
 * icons in the current icon theme probably won't be useful
 * for the vast majority of applications.
 *
 * If there are many named icons in the icon theme, the window
 * displaying all icons may open very slowly. Be patient!
 */

#include <gtkmm.h>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>

class Example_IconTheme: public Gtk::Window
{
public:
  Example_IconTheme();
  virtual ~Example_IconTheme();

protected:

  //signal handlers:
  virtual void on_selection_changed();

  virtual Glib::RefPtr<Gtk::TreeModel> create_model();

  const Glib::RefPtr<const Gtk::IconTheme> m_IconTheme;

  //Child widgets:
  Gtk::Frame m_Frame;
  Gtk::Box m_VBox;
  Gtk::Box m_HBox;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Glib::RefPtr<Gtk::TreeModel> m_refTreeModel;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::TreeSelection> m_refTreeSelection;

  Gtk::Image m_Image;
  Gtk::Label m_Label_IconName;
  Gtk::Label m_Label_Sizes;
  Gtk::Label m_Label_Context;
  Gtk::Label m_Label_Filename;

  struct ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
    Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> > icon;
    Gtk::TreeModelColumn<Glib::ustring>               iconname;
    Gtk::TreeModelColumn<Glib::ustring>               sizes;
    Gtk::TreeModelColumn<Glib::ustring>               context;
    Gtk::TreeModelColumn<Glib::ustring>               filename;

    ModelColumns()
    {
      add(icon);
      add(iconname);
      add(sizes);
      add(context);
      add(filename);
    }
  };

  const ModelColumns m_columns;
};


Gtk::Window* do_icontheme()
{
  return new Example_IconTheme();
}

Example_IconTheme::Example_IconTheme()
:
  // Get information from the icon theme associated with the default screen.
  m_IconTheme(Gtk::IconTheme::get_default()),
  m_Frame("Selected Icon"),
  m_VBox(Gtk::ORIENTATION_VERTICAL, 8),
  m_HBox(Gtk::ORIENTATION_HORIZONTAL, 8)
{
  set_title("Icons in Current Icon Theme");
  set_default_size(1000, 500);
  set_border_width(8);

  add(m_HBox);
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  m_HBox.pack_start(m_ScrolledWindow, Gtk::PACK_EXPAND_WIDGET);

  // create the TreeModel with all the named icons
  m_refTreeModel = create_model();

  // associate the TreeModel with the TreeView
  m_TreeView.set_model(m_refTreeModel);
  m_ScrolledWindow.add(m_TreeView);

  // add columns to the TreeView, mapping model m_columns to TreeView Columns:

  //The pixbuf/iconname column:
  Gtk::TreeView::Column* pColumn = Gtk::manage(new Gtk::TreeView::Column("Icon Name"));

  //We specify the renderer(s) after construction.
  // The pixbuf/iconname column uses two CellRenderers: Here we see why Gtk::TreeView is so good.
  // m_columns.icon and m_columns.iconname are columns in the model. pColumn is the column in the TreeView:
  pColumn->pack_start(m_columns.icon, /* expand= */ false);
  pColumn->pack_start(m_columns.iconname);
  m_TreeView.append_column(*pColumn);

  //Defaults to CellRendererText for a string model column.
  m_TreeView.append_column("Sizes", m_columns.sizes);
  m_TreeView.append_column("Context", m_columns.context);
  //m_TreeView.append_column("Filename", m_columns.filename);

  m_HBox.pack_end(m_Frame, Gtk::PACK_SHRINK);
  m_Frame.set_halign(Gtk::ALIGN_CENTER);
  m_Frame.set_valign(Gtk::ALIGN_START);

  m_VBox.set_border_width(4);
  m_Frame.add(m_VBox);

  m_VBox.pack_start(m_Image, Gtk::PACK_SHRINK);
  m_VBox.pack_start(m_Label_IconName, Gtk::PACK_SHRINK);
  m_VBox.pack_start(m_Label_Sizes, Gtk::PACK_SHRINK);
  m_VBox.pack_start(m_Label_Context, Gtk::PACK_SHRINK);
  m_VBox.pack_start(m_Label_Filename, Gtk::PACK_SHRINK);

  m_refTreeSelection = m_TreeView.get_selection();
  m_refTreeSelection->set_mode(Gtk::SELECTION_SINGLE);
  m_refTreeSelection->signal_changed().connect(
    sigc::mem_fun(*this, &Example_IconTheme::on_selection_changed));

  show_all();
}

Example_IconTheme::~Example_IconTheme()
{
}

Glib::RefPtr<Gtk::TreeModel> Example_IconTheme::create_model()
{
  Glib::RefPtr<Gtk::ListStore> refStore = Gtk::ListStore::create(m_columns);
  refStore->set_sort_column(m_columns.iconname, Gtk::SORT_ASCENDING);

  // Obtain the names of all named icons.
  typedef std::vector<Glib::ustring> type_stringvec;
  type_stringvec icon_names = m_IconTheme->list_icons();

  // Obtain the names of all contexts, and the icon names per context.
  type_stringvec contexts = m_IconTheme->list_contexts();

  typedef std::map<Glib::ustring, type_stringvec> type_stringmapvec;
  type_stringmapvec iconnames_per_context;
  for (type_stringvec::const_iterator iter = contexts.begin(); iter != contexts.end(); ++iter)
  {
    iconnames_per_context[*iter] = m_IconTheme->list_icons(*iter);
  }

  // Iterate through the icon names, populating the ListStore as appropriate.
  for (type_stringvec::const_iterator iconiter = icon_names.begin(); iconiter != icon_names.end(); ++iconiter)
  {
    // Add a new empty row to the ListStore.
    Gtk::TreeModel::Row row = *(refStore->append());

    // Get the icon sizes and sort them.
    std::vector<int> sizes = m_IconTheme->get_icon_sizes(*iconiter);
    std::sort(sizes.begin(), sizes.end());
    int minsize = 16;
    for (std::size_t i = 0; i < sizes.size(); ++i)
    {
      if (sizes[i] > 0)
      {
        minsize = sizes[i];
        break;
      }
    }

    Gtk::IconInfo icon_info = m_IconTheme->lookup_icon(*iconiter, minsize, Gtk::ICON_LOOKUP_USE_BUILTIN);

    // Populate icon column.
    if (icon_info)
    {
      if (icon_info.get_filename().empty())
        row[m_columns.icon] = icon_info.get_builtin_pixbuf();
      else
        row[m_columns.icon] = icon_info.load_icon();
    }

    // Populate icon name column.
    row[m_columns.iconname] = *iconiter;

    // Populate sizes column.
    std::ostringstream size_names;
    if (sizes.size() > 0)
      size_names << sizes[0];
    for (std::size_t i = 1; i < sizes.size(); ++i)
      size_names << ", " << sizes[i];

    row[m_columns.sizes] = size_names.str();

    // Populate context column.
    // A named icon can belong to zero or more contexts,
    // although most icons belong to exactly one context.
    Glib::ustring context_names;
    for (type_stringmapvec::const_iterator mapiter = iconnames_per_context.begin();
      mapiter != iconnames_per_context.end(); ++mapiter)
    {
      if (std::find(mapiter->second.begin(), mapiter->second.end(), *iconiter) != mapiter->second.end())
      {
        if (!context_names.empty())
          context_names += ", ";
        context_names += mapiter->first;
      }
    }
    row[m_columns.context] = context_names;

    // Populate filename column.
    if (icon_info)
      row[m_columns.filename] = icon_info.get_filename();
  }

  return refStore;
}

// triggered when TreeView selection changes
void Example_IconTheme::on_selection_changed()
{
  // put all the nice data stuff in the box on the right

  // Access the model row corresponding to the selected TreeView row.
  if (const Gtk::TreeModel::iterator iter = m_refTreeSelection->get_selected())
  {
    const Gtk::TreeModel::Row row = *iter;

    // get the data out of the model
    const Glib::RefPtr<Gdk::Pixbuf> icon = row[m_columns.icon];
    const Glib::ustring icon_name = row[m_columns.iconname];
    const Glib::ustring sizes = row[m_columns.sizes];
    const Glib::ustring context = row[m_columns.context];
    const Glib::ustring filename = row[m_columns.filename];

    m_Label_IconName.set_text(icon_name);
    m_Label_Sizes.set_text(sizes);
    m_Label_Context.set_text(context);
    m_Label_Filename.set_text(filename);

    if (icon) //If there's an icon:
    {
      // find the largest size the icon comes in:
      std::vector<int> sizes = m_IconTheme->get_icon_sizes(icon_name);
      const std::vector<int>::const_iterator sizeiter =
        std::max_element(sizes.begin(), sizes.end());
      const int maxsize = (sizeiter != sizes.end() && *sizeiter > 48) ? *sizeiter : 48;

      m_Image.set(m_IconTheme->load_icon(icon_name, maxsize, Gtk::ICON_LOOKUP_USE_BUILTIN));
    }
    else
    {
      m_Image.clear();
    }
  }
  else
  {
    m_Image.clear();
    m_Label_IconName.set_text("No selected icon");
    m_Label_Sizes.set_text("");
    m_Label_Context.set_text("");
    m_Label_Filename.set_text("");
  }
}

