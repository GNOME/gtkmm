/* Button Boxes
 *
 * The Button Box widgets are used to arrange buttons with padding.
 */

#include "gtkmm.h"
#include "gtk/gtk.h"

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
  m_VBox_Main(Gtk::ORIENTATION_VERTICAL),
  m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_HBox(Gtk::ORIENTATION_HORIZONTAL)
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

  Gtk::ButtonBox* pButtonBox = nullptr;
  if (horizontal)
    pButtonBox = Gtk::manage(new Gtk::ButtonBox(Gtk::ORIENTATION_HORIZONTAL));
  else
    pButtonBox = Gtk::manage(new Gtk::ButtonBox(Gtk::ORIENTATION_VERTICAL));

  pButtonBox->set_border_width(5);
  pFrame->add(*pButtonBox);

  pButtonBox->set_layout(layout);
  pButtonBox->set_spacing(spacing);

  Gtk::Button* pButton = Gtk::manage(new Gtk::Button("_OK"));
  pButtonBox->add(*pButton);

  pButton = Gtk::manage(new Gtk::Button("_Cancel"));
  pButtonBox->add(*pButton);

  pButton = Gtk::manage(new Gtk::Button());
  Gtk::Image* pImage = Gtk::manage(new Gtk::Image());
  pImage->set_from_icon_name("help-browser", Gtk::ICON_SIZE_BUTTON);
  pButton->add(*pImage);
  pButtonBox->add(*pButton);

  return pFrame;
}

