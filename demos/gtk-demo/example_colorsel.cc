 /* Color Chooser
 *
 * GtkColorChooserDialog lets the user choose a color.
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
  Gtk::Box m_VBox;
  Gtk::Frame m_Frame;
  Gtk::DrawingArea m_DrawingArea;
  Gtk::Button m_Button;
  Gdk::RGBA m_Color;
};

//Called by DemoWindow;
Gtk::Window* do_colorsel()
{
  return new Example_ColorSel();
}

Example_ColorSel::Example_ColorSel()
: m_VBox(Gtk::ORIENTATION_VERTICAL, 8),
  m_Button("_Change the above color", true)
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

  /* TODO: Is this still necessary? It is not in the C version now.
  // Unset the background pixmap (as used by pixmap themes)
  // because it takes precedence over the background color.
  m_DrawingArea.modify_bg_pixmap(Gtk::STATE_NORMAL, "<none>");
  */

  // set the color
  m_Color.set_rgba(0, 0, 1, 1);
  m_DrawingArea.override_background_color(m_Color);

  m_Frame.add(m_DrawingArea);

  m_Button.set_halign(Gtk::ALIGN_END);
  m_Button.set_valign(Gtk::ALIGN_CENTER);

  m_VBox.pack_start(m_Button, Gtk::PACK_SHRINK);

  m_Button.signal_clicked().connect(sigc::mem_fun(*this, &Example_ColorSel::on_button_clicked));

  show_all();
}

Example_ColorSel::~Example_ColorSel()
{
}

void Example_ColorSel::on_button_clicked()
{
  Gtk::ColorChooserDialog dialog("Changing color");
  dialog.set_transient_for(*this);
  dialog.set_rgba(m_Color);

  const int response = dialog.run();

  if(response == Gtk::RESPONSE_OK)
  {
    m_Color = dialog.get_rgba();

    m_DrawingArea.override_background_color(m_Color);
  }
}

