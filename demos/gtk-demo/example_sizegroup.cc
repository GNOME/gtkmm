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
 * and not more. For example, if you are packing your widgets
 * into a table, you would not include the Gtk::FILL flag.
 */

#include <gtkmm.h>
#include <list>

class Example_SizeGroup : public Gtk::Window
{
public:
  Example_SizeGroup();
  ~Example_SizeGroup() override;

protected:
  //Signal handlers:
  void on_checkbutton_toggled();
  void on_close();

  using type_listStrings = std::list<Glib::ustring>;
  void add_row(Gtk::Grid& grid, int row, const Glib::RefPtr<Gtk::SizeGroup>& size_group,
    const Glib::ustring& label_text, const std::list<Glib::ustring>& options);
  Gtk::ComboBoxText* create_combobox(const std::list<Glib::ustring>& strings);

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
  m_VBox(Gtk::ORIENTATION_VERTICAL, 5),
  m_CheckButton("_Enable grouping", true),
  m_CloseButton("_Close", true)
{
  set_title("Gtk::SizeGroup");
  set_resizable(false);

  add(m_VBox);
  m_VBox.set_border_width(5);

  m_refSizeGroup = Gtk::SizeGroup::create(Gtk::SIZE_GROUP_HORIZONTAL),

  // Create one frame holding color options
  m_VBox.pack_start(m_Frame_Color);

  m_Grid_Color.set_border_width(5);
  m_Grid_Color.set_row_spacing(5);
  m_Grid_Color.set_column_spacing(10);
  m_Frame_Color.add(m_Grid_Color);

  const type_listStrings color_options{"Red", "Green", "Blue"};
  add_row(m_Grid_Color, 0, m_refSizeGroup, "_Foreground", color_options);
  add_row(m_Grid_Color, 1, m_refSizeGroup, "_Background", color_options);

  // and another frame holding line style options
  m_VBox.pack_start(m_Frame_Line, Gtk::PACK_SHRINK);

  m_Grid_Line.set_border_width(5);
  m_Grid_Line.set_row_spacing(5);
  m_Grid_Line.set_column_spacing(10);
  m_Frame_Line.add(m_Grid_Line);

  const type_listStrings dash_options{"Solid", "Dashed", "Dotted"};
  add_row(m_Grid_Line, 0, m_refSizeGroup, "_Dashing", dash_options);

  const type_listStrings end_options{"Square", "Round", "Double Arrow"};
  add_row(m_Grid_Line, 1, m_refSizeGroup, "_Line ends", end_options);

  // and a check button to turn grouping on and off
  m_VBox.pack_start(m_CheckButton, Gtk::PACK_SHRINK);
  m_CheckButton.set_active();
  m_CheckButton.signal_toggled().connect(sigc::mem_fun(*this, &Example_SizeGroup::on_checkbutton_toggled));

  // and finally a close button
  m_VBox.pack_start(m_CloseButton, Gtk::PACK_SHRINK);
  m_CloseButton.set_halign(Gtk::ALIGN_END);
  m_CloseButton.signal_clicked().connect(sigc::mem_fun(*this, &Example_SizeGroup::on_close));

  show_all();
}

Example_SizeGroup::~Example_SizeGroup()
{
}

void Example_SizeGroup::on_checkbutton_toggled()
{
  // Gtk::SIZE_GROUP_NONE is not generally useful, but is useful
  // here to show the effect of Gtk::SIZE_GROUP_HORIZONTAL by contrast.
  Gtk::SizeGroupMode new_mode = Gtk::SIZE_GROUP_HORIZONTAL;
  if (!m_CheckButton.get_active())
    new_mode = Gtk::SIZE_GROUP_NONE;

  m_refSizeGroup->set_mode(new_mode);
}

void Example_SizeGroup::add_row(Gtk::Grid& grid, int row,
                                const Glib::RefPtr<Gtk::SizeGroup>& size_group,
                                const Glib::ustring& label_text,
                                const std::list<Glib::ustring>& options)
{
  auto pLabel = Gtk::make_managed<Gtk::Label>(label_text, Gtk::ALIGN_START, Gtk::ALIGN_BASELINE, true);

  pLabel->set_hexpand();
  grid.attach(*pLabel, 0, row, 1, 1);

  auto pComboBoxText = create_combobox(options);
  pLabel->set_mnemonic_widget(*pComboBoxText);
  pComboBoxText->set_halign(Gtk::ALIGN_END);
  pComboBoxText->set_valign(Gtk::ALIGN_BASELINE);
  size_group->add_widget(*pComboBoxText);
  grid.attach(*pComboBoxText, 1, row, 1, 1);
}

// Convenience function to create an option menu holding a number of strings
Gtk::ComboBoxText* Example_SizeGroup::create_combobox(const std::list<Glib::ustring>& strings)
{
  auto pCombo = Gtk::make_managed<Gtk::ComboBoxText>();

  for(const auto& str : strings)
  {
    pCombo->append(str);
  }
  pCombo->set_active(0);

  return pCombo;
}

void Example_SizeGroup::on_close()
{
  hide();
}
