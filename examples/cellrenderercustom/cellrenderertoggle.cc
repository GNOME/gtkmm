/*
 * Example Gtk::CellRendererCustom implementation.  The custom
 * MyCellRendererToggle is functionally equivalent to Gtk::CellRendererToggle.
 */

#include <gtkmm.h>
#include <sstream>


namespace
{

class MyCellRendererToggle : public Gtk::CellRenderer
{
public:
  MyCellRendererToggle();
  virtual ~MyCellRendererToggle();

  Glib::PropertyProxy<bool> property_activatable();
  Glib::PropertyProxy<bool> property_active();
  Glib::PropertyProxy<bool> property_radio();

  typedef sigc::signal<void, const Glib::ustring&> SignalToggled;
  SignalToggled& signal_toggled();

protected:
  virtual void get_size_vfunc(Gtk::Widget& widget,
                              const Gdk::Rectangle* cell_area,
                              int* x_offset, int* y_offset,
                              int* width,    int* height) const;

  virtual void render_vfunc(const Glib::RefPtr<Gdk::Drawable>& window,
                            Gtk::Widget& widget,
                            const Gdk::Rectangle& background_area,
                            const Gdk::Rectangle& cell_area,
                            const Gdk::Rectangle& expose_area,
                            Gtk::CellRendererState flags);

  virtual bool activate_vfunc(GdkEvent* event,
                              Gtk::Widget& widget,
                              const Glib::ustring& path,
                              const Gdk::Rectangle& background_area,
                              const Gdk::Rectangle& cell_area,
                              Gtk::CellRendererState flags);

private:
  Glib::Property<bool> property_activatable_;
  Glib::Property<bool> property_active_;
  Glib::Property<bool> property_radio_;

  SignalToggled signal_toggled_;
};


class AppWindow : public Gtk::Window
{
public:
  AppWindow();
  virtual ~AppWindow();

private:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:
    Gtk::TreeModelColumn<Glib::ustring> text;
    Gtk::TreeModelColumn<bool>          active;

    ModelColumns() { add(text); add(active); }
  };

  ModelColumns                  list_columns_;
  Glib::RefPtr<Gtk::ListStore>  list_store_;
  Gtk::TreeView                 tree_view_;

  void on_cell_toggled(const Glib::ustring& path_string);
};


MyCellRendererToggle::MyCellRendererToggle()
:
  Glib::ObjectBase      (typeid(MyCellRendererToggle)),
  Gtk::CellRenderer     (),
  property_activatable_ (*this, "activatable", true),
  property_active_      (*this, "active",      false),
  property_radio_       (*this, "radio",       false)
{
  property_mode() = Gtk::CELL_RENDERER_MODE_ACTIVATABLE;
  property_xpad() = 2;
  property_ypad() = 2;
}

MyCellRendererToggle::~MyCellRendererToggle()
{}

Glib::PropertyProxy<bool> MyCellRendererToggle::property_activatable()
{
  return property_activatable_.get_proxy();
}

Glib::PropertyProxy<bool> MyCellRendererToggle::property_active()
{
  return property_active_.get_proxy();
}

Glib::PropertyProxy<bool> MyCellRendererToggle::property_radio()
{
  return property_radio_.get_proxy();
}

MyCellRendererToggle::SignalToggled& MyCellRendererToggle::signal_toggled()
{
  return signal_toggled_;
}

void MyCellRendererToggle::get_size_vfunc(Gtk::Widget&,
                                          const Gdk::Rectangle* cell_area,
                                          int* x_offset, int* y_offset,
                                          int* width,    int* height) const
{
  enum { TOGGLE_WIDTH = 12 };

  const int calc_width  = property_xpad() * 2 + TOGGLE_WIDTH;
  const int calc_height = property_ypad() * 2 + TOGGLE_WIDTH;

  if(width)
    *width = calc_width;

  if(height)
    *height = calc_height;

  if(cell_area)
  {
    if(x_offset)
    {
      *x_offset = int(property_xalign() * (cell_area->get_width() - calc_width));
      *x_offset = std::max(0, *x_offset);
    }

    if(y_offset)
    {
      *y_offset = int(property_yalign() * (cell_area->get_height() - calc_height));
      *y_offset = std::max(0, *y_offset);
    }
  }
}

void MyCellRendererToggle::render_vfunc(const Glib::RefPtr<Gdk::Drawable>& window,
                                        Gtk::Widget& widget,
                                        const Gdk::Rectangle&,
                                        const Gdk::Rectangle& cell_area,
                                        const Gdk::Rectangle&,
                                        Gtk::CellRendererState flags)
{
  const unsigned int cell_xpad = property_xpad();
  const unsigned int cell_ypad = property_ypad();

  int x_offset = 0, y_offset = 0, width = 0, height = 0;
  get_size(widget, cell_area, x_offset, y_offset, width, height);

  width  -= cell_xpad * 2;
  height -= cell_ypad * 2;

  if(width <= 0 || height <= 0)
    return;

  Gtk::StateType state = Gtk::STATE_INSENSITIVE;

  if(property_activatable_)
    state = Gtk::STATE_NORMAL;

  if((flags & Gtk::CELL_RENDERER_SELECTED) != 0)
    state = (widget.has_focus()) ? Gtk::STATE_SELECTED : Gtk::STATE_ACTIVE;

  const Gtk::ShadowType shadow = (property_active_) ? Gtk::SHADOW_IN : Gtk::SHADOW_OUT;

  //Cast the drawable to a Window. TODO: Maybe paint_option() should take a Drawable? murrayc.
  Glib::RefPtr<Gdk::Window> window_casted = Glib::RefPtr<Gdk::Window>::cast_dynamic<>(window);
  if(window_casted)
  {
    if(property_radio_)
    {
      widget.get_style()->paint_option(
          window_casted, state, shadow,
          cell_area, widget, "cellradio",
          cell_area.get_x() + x_offset + cell_xpad,
          cell_area.get_y() + y_offset + cell_ypad,
          width - 1, height - 1);
    }
    else
    {
      widget.get_style()->paint_check(
          window_casted, state, shadow,
          cell_area, widget, "cellcheck",
          cell_area.get_x() + x_offset + cell_xpad,
          cell_area.get_y() + y_offset + cell_ypad,
          width - 1, height - 1);
    }
  }
}

bool MyCellRendererToggle::activate_vfunc(GdkEvent*,
                                          Gtk::Widget&,
                                          const Glib::ustring& path,
                                          const Gdk::Rectangle&,
                                          const Gdk::Rectangle&,
                                          Gtk::CellRendererState)
{
  if(property_activatable_)
  {
    signal_toggled_(path);
    return true;
  }

  return false;
}


AppWindow::AppWindow()
:
  list_columns_ (),
  list_store_   (Gtk::ListStore::create(list_columns_)),
  tree_view_    (list_store_)
{
  add(tree_view_);

  tree_view_.append_column("Text", list_columns_.text);

  {
    MyCellRendererToggle *const renderer = new MyCellRendererToggle();
    Gtk::TreeViewColumn  *const column   = new Gtk::TreeViewColumn("Active", *Gtk::manage(renderer));
    tree_view_.append_column(*Gtk::manage(column));

    column->add_attribute(renderer->property_active(), list_columns_.active);
    renderer->signal_toggled().connect(sigc::mem_fun(*this, &AppWindow::on_cell_toggled));
  }

  std::ostringstream output (std::ios::ate);

  for(int i = 1; i <= 10; ++i)
  {
    output.str("row #");
    output << i;

    Gtk::TreeModel::Row row = *list_store_->append();

    row[list_columns_.text]   = output.str();
    row[list_columns_.active] = ((i % 2) != 0);
  }

  show_all_children();
}

AppWindow::~AppWindow()
{}

void AppWindow::on_cell_toggled(const Glib::ustring& path_string)
{
  // Get the model row that has been toggled.
  Gtk::TreeModel::Row row = *list_store_->get_iter(Gtk::TreeModel::Path(path_string));

  // Invert the 'active' value in the toggled row.
  row[list_columns_.active] = !row[list_columns_.active];
}

} // anonymous namespace


int main(int argc, char** argv)
{
  Gtk::Main main_instance (&argc, &argv);

  AppWindow window;
  Gtk::Main::run(window);

  return 0;
}

