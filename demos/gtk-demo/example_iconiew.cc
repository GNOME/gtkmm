/* Icon View
 *
 * The Gtk::IconView widget is used to display and manipulate icons.  It
 * uses a Gtk::TreeModel for data storage, so the list store example
 * might be helpful.
 *
 */

#include <gtkmm.h>

class Example_IconView : public Gtk::Window
{
public:
  Example_IconView();
  virtual ~Example_IconView();

protected:

  //Signal handlers:
  virtual void on_button_clicked();

  class ModelColumns : public Gtk::TreeModelColumnRecord
  {
  public:

    Gtk::TreeModelColumn<Glib::ustring> path;
    Gtk::TreeModelColumn<Glib::ustring> display_name;
    Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> >  pixbuf;
    Gtk::TreeModelColumn<bool>          is_directory;

    ModelColumns() { add(path); add(display_name); add(pixbuf); add(is_description); }
  };

  const ModelColumns m_columns;
  
  Glib::RefPtr<Gtk::ListStore> m_model;

  //Member widgets:
  Gtk::VBox m_VBox;
  Gtk::Frame m_Frame;
  Gtk::DrawingArea m_DrawingArea;
  Gtk::Button m_Button;
  Gdk::Color m_Color;
  Gtk::Alignment m_Alignment;
};

//Called by DemoWindow;
Gtk::Window* do_colorsel()
{
  return new Example_IconView();
}

Example_IconView::Example_IconView()
: m_VBox(false, 8),
  m_Button("_Change the above color", true),
  m_Alignment(Gtk::ALIGN_RIGHT, Gtk::ALIGN_BOTTOM, 0.0, 0.0)
{
  set_title("Icon View");
  set_border_width(8);

  m_model = Gtk::ListStore::create(m_columns);

  m_VBox.set_border_width(8);
  add(m_VBox);

  /*
   * Create the color swatch area
   */

  m_Frame.set_shadow_type(Gtk::SHADOW_IN);
  m_VBox.pack_start(m_Frame);

  // set a fixed size
  m_DrawingArea.set_size_request(200, 200);

  // Unset the background pixmap (as used by pixmap themes)
  // because it takes precedence over the background color.
  m_DrawingArea.modify_bg_pixmap(Gtk::STATE_NORMAL, "<none>");

  // set the color
  m_Color.set_rgb(0, 0, 65535);
  m_DrawingArea.modify_bg(Gtk::STATE_NORMAL, m_Color);

  m_Frame.add(m_DrawingArea);

  m_Alignment.add(m_Button);

  m_VBox.pack_start(m_Alignment,Gtk::PACK_SHRINK);

  m_Button.signal_clicked().connect(sigc::mem_fun(*this, &Example_IconView::on_button_clicked));

  show_all();
}

Example_IconView::~Example_IconView()
{
}

void Example_IconView::on_button_clicked()
{
  Gtk::ColorSelectionDialog dialog ("Changing color");
  dialog.set_transient_for(*this);

  Gtk::ColorSelection *const pColorSel = dialog.get_colorsel();

  pColorSel->set_previous_color(m_Color);
  pColorSel->set_current_color(m_Color);
  pColorSel->set_has_palette();

  const int response = dialog.run();

  if(response == Gtk::RESPONSE_OK)
  {
    m_Color = pColorSel->get_current_color();

    m_DrawingArea.modify_bg(Gtk::STATE_NORMAL, m_Color);
  }
}

