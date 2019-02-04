 /* Color Chooser
 *
 * Gtk::ColorChooserDialog lets the user choose a color.
 *
 */

#include <gtkmm.h>

class Example_ColorSel : public Gtk::Window
{
public:
  Example_ColorSel();
  ~Example_ColorSel() override;

protected:
  //Signal handler:
  void on_button_clicked();

  //Drawing function:
  void on_drawing_area_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

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
: m_VBox(Gtk::Orientation::VERTICAL, 8),
  m_Button("_Change the above color", true)
{
  set_title("Color Chooser");
  set_resizable(false);

  m_VBox.set_margin(12);
  add(m_VBox);

  // Create the color swatch area
  m_Frame.set_shadow_type(Gtk::ShadowType::IN);
  m_Frame.set_expand(true);
  m_VBox.add(m_Frame);

  // set a fixed size
  m_DrawingArea.set_content_width(200);
  m_DrawingArea.set_content_height(200);

  // set the color
  m_Color.set_rgba(0, 0, 1, 1);
  m_DrawingArea.set_draw_func(sigc::mem_fun(*this, &Example_ColorSel::on_drawing_area_draw));

  m_Frame.add(m_DrawingArea);

  m_Button.set_halign(Gtk::Align::END);
  m_Button.set_valign(Gtk::Align::CENTER);

  m_VBox.add(m_Button);

  m_Button.signal_clicked().connect(sigc::mem_fun(*this, &Example_ColorSel::on_button_clicked));
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

  if(response == Gtk::ResponseType::OK)
  {
    m_Color = dialog.get_rgba();
    m_DrawingArea.queue_draw();
  }
}

void Example_ColorSel::on_drawing_area_draw(const Cairo::RefPtr<Cairo::Context>& cr, int, int)
{
  Gdk::Cairo::set_source_rgba(cr, m_Color);
  cr->paint();
}
