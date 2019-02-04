/* Button Boxes
 *
 * The Button Box widgets are used to arrange buttons with padding.
 */

#include <gtkmm.h>
#include <gtk/gtk.h>

class Example_ButtonBox : public Gtk::Window
{
public:
  Example_ButtonBox();
  ~Example_ButtonBox() override;

protected:
  Gtk::Frame* create_button_box(bool horizontal, const Glib::ustring& title,
                                int spacing, Gtk::ButtonBoxStyle layout);

  //Member widgets:
  Gtk::Frame m_Frame_Horizontal, m_Frame_Vertical;
  Gtk::Box m_VBox_Main, m_VBox;
  Gtk::Box m_HBox;
};

//Called by DemoWindow;
Gtk::Window* do_buttonbox()
{
  return new Example_ButtonBox();
}

Example_ButtonBox::Example_ButtonBox()
: m_Frame_Horizontal("Horizontal Button Boxes"),
  m_Frame_Vertical("Vertical Button Boxes"),
  m_VBox_Main(Gtk::Orientation::VERTICAL),
  m_VBox(Gtk::Orientation::VERTICAL),
  m_HBox(Gtk::Orientation::HORIZONTAL)
{
  set_title("Button Boxes");

  m_VBox_Main.set_margin(10);
  add(m_VBox_Main);

  m_Frame_Horizontal.set_margin_top(10);
  m_Frame_Horizontal.set_margin_bottom(10);
  m_Frame_Horizontal.set_expand(true);
  m_VBox_Main.add(m_Frame_Horizontal);

  m_VBox.set_margin(10);
  m_Frame_Horizontal.add(m_VBox);

  m_VBox.add( *(create_button_box(true, "Spread", 40, Gtk::ButtonBoxStyle::SPREAD)) );
  m_VBox.add( *(create_button_box(true, "Edge", 40, Gtk::ButtonBoxStyle::EDGE)) );
  m_VBox.add( *(create_button_box(true, "Start", 40, Gtk::ButtonBoxStyle::START)) );
  m_VBox.add( *(create_button_box(true, "End", 40, Gtk::ButtonBoxStyle::END)) );

  m_Frame_Vertical.set_expand(true);
  m_VBox_Main.add(m_Frame_Vertical);

  m_HBox.set_margin(10);
  m_Frame_Vertical.add(m_HBox);

  m_HBox.add( *(create_button_box(false, "Spread", 30, Gtk::ButtonBoxStyle::SPREAD)) );
  m_HBox.add( *(create_button_box(false, "Edge", 30, Gtk::ButtonBoxStyle::EDGE)) );
  m_HBox.add( *(create_button_box(false, "Start", 30, Gtk::ButtonBoxStyle::START)) );
  m_HBox.add( *(create_button_box(false, "End", 30, Gtk::ButtonBoxStyle::END)) );
}

Example_ButtonBox::~Example_ButtonBox()
{
}

Gtk::Frame* Example_ButtonBox::create_button_box(bool horizontal, const Glib::ustring& title, gint  spacing, Gtk::ButtonBoxStyle layout)
{
  auto pFrame = Gtk::make_managed<Gtk::Frame>(title);

  Gtk::ButtonBox* pButtonBox = nullptr;
  if (horizontal)
    pButtonBox = Gtk::make_managed<Gtk::ButtonBox>(Gtk::Orientation::HORIZONTAL);
  else
  {
    pButtonBox = Gtk::make_managed<Gtk::ButtonBox>(Gtk::Orientation::VERTICAL);
    pFrame->set_margin_start(5);
    pFrame->set_margin_end(5);
  }

  pButtonBox->property_margin() = 5;
  pFrame->add(*pButtonBox);

  pButtonBox->set_layout(layout);
  pButtonBox->set_spacing(spacing);

  auto pButton = Gtk::make_managed<Gtk::Button>("_OK", true);
  pButtonBox->add(*pButton);

  pButton = Gtk::make_managed<Gtk::Button>("_Cancel", true);
  pButtonBox->add(*pButton);

  pButton = Gtk::make_managed<Gtk::Button>();
  pButton->set_icon_name("help-browser");
  pButtonBox->add(*pButton);

  pFrame->set_hexpand();
  pFrame->set_vexpand();
  return pFrame;
}

