/* Color Selector
 *
 * GtkColorSelection lets the user choose a color. GtkColorSelectionDialog is
 * a prebuilt dialog containing a GtkColorSelection.
 *
 */

#include <gtkmm.h>

class Example_ColorSel : public Gtk::Window
{
public:
  Example_ColorSel();
  virtual ~Example_ColorSel();

protected:
  //Signal handlers:
  virtual void on_button_clicked();

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
  return new Example_ColorSel();
}

Example_ColorSel::Example_ColorSel()
: m_VBox(false, 8),
  m_Button("_Change the above color", true),
  m_Alignment(Gtk::ALIGN_RIGHT, Gtk::ALIGN_BOTTOM, 0.0, 0.0)
{
  set_title("Color Selection");
  set_border_width(8);

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

  m_Button.signal_clicked().connect(SigC::slot(*this, &Example_ColorSel::on_button_clicked));

  show_all();
}

Example_ColorSel::~Example_ColorSel()
{
}

void Example_ColorSel::on_button_clicked()
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

