/* Size Groups
 *
 * Gtk::SizeGroup provides a mechanism for grouping a number of
 * widgets together so they all request the same amount of space.
 * This is typically useful when you want a column of widgets to
 * have the same size, but you can't use a Gtk::Grid widget.
 *
 * Note that size groups only affect the amount of space requested,
 * not the size that the widgets finally receive. If you want the
 * widgets in a Gtk::SizeGroup to actually be the same size, you need
 * to pack them in such a way that they get the size they request
 * and not more.
 */

#include <gtkmm.h>

class Example_SizeGroup : public Gtk::Window
{
public:
  Example_SizeGroup();
  ~Example_SizeGroup() override;

protected:
  //Signal handlers:
  void on_checkbutton_toggled();
  void on_close();

  void add_row(Gtk::Grid& grid, int row, const Glib::RefPtr<Gtk::SizeGroup>& size_group,
    const Glib::ustring& label_text, const std::vector<Glib::ustring>& options);

  //Member widgets:
  Gtk::Frame m_Frame_Color, m_Frame_Line;
  Gtk::Box m_VBox;
  Glib::RefPtr<Gtk::SizeGroup> m_refSizeGroup;
  Gtk::Grid m_Grid_Color, m_Grid_Line;
  Gtk::CheckButton m_CheckButton;
  Gtk::Button m_CloseButton;
};

//Called by DemoWindow;
Gtk::Window* do_sizegroup()
{
  return new Example_SizeGroup();
}

Example_SizeGroup::Example_SizeGroup()
: m_Frame_Color("Color Options"),
  m_Frame_Line("Line Options"),
  m_VBox(Gtk::Orientation::VERTICAL, 5),
  m_CheckButton("_Enable grouping", true),
  m_CloseButton("_Close", true)
{
  set_title("Gtk::SizeGroup");
  set_resizable(false);

  set_child(m_VBox);
  m_VBox.set_margin(5);

  m_refSizeGroup = Gtk::SizeGroup::create(Gtk::SizeGroup::Mode::HORIZONTAL),

  // Create one frame holding color options
  m_VBox.append(m_Frame_Color);

  m_Grid_Color.set_margin(5);
  m_Grid_Color.set_row_spacing(5);
  m_Grid_Color.set_column_spacing(10);
  m_Frame_Color.set_child(m_Grid_Color);

  const std::vector<Glib::ustring> color_options{"Red", "Green", "Blue"};
  add_row(m_Grid_Color, 0, m_refSizeGroup, "_Foreground", color_options);
  add_row(m_Grid_Color, 1, m_refSizeGroup, "_Background", color_options);

  // and another frame holding line style options
  m_VBox.append(m_Frame_Line);

  m_Grid_Line.set_margin(5);
  m_Grid_Line.set_row_spacing(5);
  m_Grid_Line.set_column_spacing(10);
  m_Frame_Line.set_child(m_Grid_Line);

  const std::vector<Glib::ustring> dash_options{"Solid", "Dashed", "Dotted"};
  add_row(m_Grid_Line, 0, m_refSizeGroup, "_Dashing", dash_options);

  const std::vector<Glib::ustring> end_options{"Square", "Round", "Double Arrow"};
  add_row(m_Grid_Line, 1, m_refSizeGroup, "_Line ends", end_options);

  // and a check button to turn grouping on and off
  m_VBox.append(m_CheckButton);
  m_CheckButton.set_active();
  m_CheckButton.signal_toggled().connect(sigc::mem_fun(*this, &Example_SizeGroup::on_checkbutton_toggled));

  // and finally a close button
  m_VBox.append(m_CloseButton);
  m_CloseButton.set_halign(Gtk::Align::END);
  m_CloseButton.signal_clicked().connect(sigc::mem_fun(*this, &Example_SizeGroup::on_close));
}

Example_SizeGroup::~Example_SizeGroup()
{
}

void Example_SizeGroup::on_checkbutton_toggled()
{
  // Gtk::SizeGroup::Mode::NONE is not generally useful, but is useful
  // here to show the effect of Gtk::SizeGroup::Mode::HORIZONTAL by contrast.
  auto new_mode = Gtk::SizeGroup::Mode::HORIZONTAL;
  if (!m_CheckButton.get_active())
    new_mode = Gtk::SizeGroup::Mode::NONE;

  m_refSizeGroup->set_mode(new_mode);
}

void Example_SizeGroup::add_row(Gtk::Grid& grid, int row,
                                const Glib::RefPtr<Gtk::SizeGroup>& size_group,
                                const Glib::ustring& label_text,
                                const std::vector<Glib::ustring>& options)
{
  auto pLabel = Gtk::make_managed<Gtk::Label>(label_text, Gtk::Align::START, Gtk::Align::BASELINE, true);

  pLabel->set_hexpand();
  grid.attach(*pLabel, 0, row);

  auto pDropDown = Gtk::make_managed<Gtk::DropDown>(options);
  pDropDown->set_selected(0);
  pLabel->set_mnemonic_widget(*pDropDown);
  pDropDown->set_halign(Gtk::Align::END);
  pDropDown->set_valign(Gtk::Align::BASELINE);
  size_group->add_widget(*pDropDown);
  grid.attach(*pDropDown, 1, row);
}

void Example_SizeGroup::on_close()
{
  set_visible(false);
}
