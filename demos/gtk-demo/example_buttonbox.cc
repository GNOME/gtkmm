/* Button Boxes
 *
 * The Button Box widgets are used to arrange buttons with padding.
 */

#include "gtkmm.h"
#include "gtk/gtkstock.h"

class Example_ButtonBox : public Gtk::Window
{
public:
  Example_ButtonBox();
  virtual ~Example_ButtonBox();

protected:
  Gtk::Frame* create_button_box(bool horizontal, const Glib::ustring& title,
                                int spacing, Gtk::ButtonBoxStyle layout);

  //Member widgets:
  Gtk::Frame m_Frame_Horizontal, m_Frame_Vertical;
  Gtk::VBox m_VBox_Main, m_VBox;
  Gtk::HBox m_HBox;
};

//Called by DemoWindow;
Gtk::Window* do_buttonbox()
{
  return new Example_ButtonBox();
}

Example_ButtonBox::Example_ButtonBox()
: m_Frame_Horizontal("Horizontal Button Boxes"),
  m_Frame_Vertical("Vertical Button Boxes")
{
  set_title("Button Boxes");
  set_border_width(10);

  add(m_VBox_Main);

  m_VBox_Main.pack_start(m_Frame_Horizontal, Gtk::PACK_EXPAND_WIDGET, 10);

  m_VBox.set_border_width(10);
  m_Frame_Horizontal.add(m_VBox);

  m_VBox.pack_start( *(create_button_box(true, "Spread", 40, Gtk::BUTTONBOX_SPREAD)) );
  m_VBox.pack_start( *(create_button_box(true, "Edge", 40, Gtk::BUTTONBOX_EDGE)) );
  m_VBox.pack_start( *(create_button_box(true, "Start", 40, Gtk::BUTTONBOX_START)) );
  m_VBox.pack_start( *(create_button_box(true, "End", 40, Gtk::BUTTONBOX_END)) );

  m_VBox_Main.pack_start(m_Frame_Vertical, Gtk::PACK_EXPAND_WIDGET, 10);

  m_VBox.set_border_width(10);
  m_Frame_Vertical.add(m_HBox);

  m_HBox.pack_start( *(create_button_box(false, "Spread", 30, Gtk::BUTTONBOX_SPREAD)) );
  m_HBox.pack_start( *(create_button_box(false, "Edge", 30, Gtk::BUTTONBOX_EDGE)) );
  m_HBox.pack_start( *(create_button_box(false, "Start", 30, Gtk::BUTTONBOX_START)) );
  m_HBox.pack_start( *(create_button_box(false, "End", 30, Gtk::BUTTONBOX_END)) );

  show_all();
}

Example_ButtonBox::~Example_ButtonBox()
{
}

Gtk::Frame* Example_ButtonBox::create_button_box(bool horizontal, const Glib::ustring& title, gint  spacing, Gtk::ButtonBoxStyle layout)
{
  Gtk::Frame* pFrame = Gtk::manage(new Gtk::Frame(title));

  Gtk::ButtonBox* pButtonBox = 0;
  if (horizontal)
    pButtonBox = Gtk::manage(new Gtk::HButtonBox());
  else
    pButtonBox = Gtk::manage(new Gtk::VButtonBox());

  pButtonBox->set_border_width(5);
  pFrame->add(*pButtonBox);

  pButtonBox->set_layout(layout);
  pButtonBox->set_spacing(spacing);

  Gtk::Button* pButton = Gtk::manage(new Gtk::Button(Gtk::Stock::OK));
  pButtonBox->add(*pButton);

  pButton = Gtk::manage(new Gtk::Button(Gtk::Stock::CANCEL));
  pButtonBox->add(*pButton);

  pButton = Gtk::manage(new Gtk::Button(Gtk::Stock::HELP));
  pButtonBox->add(*pButton);

  return pFrame;
}

