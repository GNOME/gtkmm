 /* Color Chooser
  *
  * Gtk::ColorDialog lets the user choose a color.
  *
  * Gtk::ColorDialog is not a widget.
  * Gtk::ColorDialog::choose_rgba() shows a dialog.
  *
  * Sometimes it's easier to use Gtk::ColorDialogButton, which is a widget.
  */

#include <gtkmm.h>
#include <iostream>

class Example_ColorSel : public Gtk::Window
{
public:
  Example_ColorSel();
  ~Example_ColorSel() override;

protected:
  //Signal handlers:
  void on_button_clicked();
  void on_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result);

  //Drawing function:
  void on_drawing_area_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

  //Member widgets:
  Gtk::Box m_VBox;
  Gtk::Frame m_Frame;
  Gtk::DrawingArea m_DrawingArea;
  Gtk::Button m_Button;
  Gdk::RGBA m_Color;
  Glib::RefPtr<Gtk::ColorDialog> m_pDialog;
};

//Called by DemoWindow;
Gtk::Window* do_colorsel()
{
  return new Example_ColorSel();
}

Example_ColorSel::Example_ColorSel()
: m_VBox(Gtk::Orientation::VERTICAL, 8),
  m_Button("_Change the color above", true)
{
  set_title("Color Chooser");
  set_resizable(false);

  m_VBox.set_margin(12);
  set_child(m_VBox);

  // Create the color swatch area
  m_Frame.set_expand(true);
  m_VBox.append(m_Frame);

  // set a fixed size
  m_DrawingArea.set_content_width(200);
  m_DrawingArea.set_content_height(200);

  // set the color
  m_Color.set_rgba(0, 0, 1, 1);
  m_DrawingArea.set_draw_func(sigc::mem_fun(*this, &Example_ColorSel::on_drawing_area_draw));

  m_Frame.set_child(m_DrawingArea);

  m_Button.set_halign(Gtk::Align::END);
  m_Button.set_valign(Gtk::Align::CENTER);

  m_VBox.append(m_Button);

  m_Button.signal_clicked().connect(sigc::mem_fun(*this, &Example_ColorSel::on_button_clicked));
}

Example_ColorSel::~Example_ColorSel()
{
}

void Example_ColorSel::on_button_clicked()
{
  if (!m_pDialog)
  {
    m_pDialog = Gtk::ColorDialog::create();
    m_pDialog->set_title("Choose a color");
  }
  m_pDialog->choose_rgba(*this, m_Color,
    sigc::mem_fun(*this, &Example_ColorSel::on_dialog_finish));
}

void Example_ColorSel::on_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result)
{
  try
  {
    m_Color = m_pDialog->choose_rgba_finish(result);
    m_DrawingArea.queue_draw();
  }
  catch (const Gtk::DialogError& err)
  {
    std::cout << "No color selected. " << err.what() << std::endl;
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Unexpected exception. " << err.what() << std::endl;
  }
}

void Example_ColorSel::on_drawing_area_draw(const Cairo::RefPtr<Cairo::Context>& cr, int, int)
{
  Gdk::Cairo::set_source_rgba(cr, m_Color);
  cr->paint();
}
