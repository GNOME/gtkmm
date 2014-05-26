/* Size Groups
 *
 * GtkSizeGroup provides a mechanism for grouping a number of
 * widgets together so they all request the same amount of space.
 * This is typically useful when you want a column of widgets to
 * have the same size, but you can't use a GtkGrid widget.
 *
 * Note that size groups only affect the amount of space requested,
 * not the size that the widgets finally receive. If you want the
 * widgets in a GtkSizeGroup to actually be the same size, you need
 * to pack them in such a way that they get the size they request
 * and not more. For example, if you are packing your widgets
 * into a table, you would not include the Gtk::FILL flag.
 */

#include <gtkmm.h>
#include <list>

class Example_SizeGroup : public Gtk::Dialog
{
public:
  Example_SizeGroup();
  virtual ~Example_SizeGroup();

protected:
  //Signal handlers:
  virtual void on_checkbutton_toggled();

  typedef std::list<Glib::ustring> type_listStrings;
  virtual void add_row(Gtk::Grid& grid, int row, const Glib::RefPtr<Gtk::SizeGroup>& size_group, const Glib::ustring& label_text, const std::list<Glib::ustring>& options);
  virtual Gtk::ComboBoxText* create_combobox(const std::list<Glib::ustring>& strings);

  virtual void on_response(int response_id);

  //Member widgets:
  Gtk::Frame m_Frame_Color, m_Frame_Line;
  Gtk::Box m_VBox;
  Gtk::Box m_HBox;
  Glib::RefPtr<Gtk::SizeGroup> m_refSizeGroup;
  Gtk::Grid m_Grid_Color, m_Grid_Line;
  Gtk::CheckButton m_CheckButton;
};

//Called by DemoWindow;
Gtk::Window* do_sizegroup()
{
  return new Example_SizeGroup();
}

Example_SizeGroup::Example_SizeGroup()
: Gtk::Dialog("Gtk::SizeGroup"),
  m_Frame_Color("Color Options"),
  m_Frame_Line("Line Options"),
  m_VBox(Gtk::ORIENTATION_VERTICAL, 5),
  m_HBox(Gtk::ORIENTATION_HORIZONTAL, 5),
  m_CheckButton("_Enable grouping", true)
{
  set_resizable(false);
  add_button("_Close", Gtk::RESPONSE_CLOSE);

  get_content_area()->pack_start(m_VBox);
  m_VBox.set_border_width(5);

  m_refSizeGroup = Gtk::SizeGroup::create(Gtk::SIZE_GROUP_HORIZONTAL),

  /* Create one frame holding color options
   */
  m_VBox.pack_start(m_Frame_Color);

  m_Grid_Color.set_border_width(5);
  m_Grid_Color.set_row_spacing(5);
  m_Grid_Color.set_column_spacing(10);
  m_Frame_Color.add(m_Grid_Color);

  type_listStrings color_options;
  color_options.push_back("Red");
  color_options.push_back("Green");
  color_options.push_back("Blue");

  add_row(m_Grid_Color, 0, m_refSizeGroup, "_Foreground", color_options);
  add_row(m_Grid_Color, 1, m_refSizeGroup, "_Background", color_options);

  /* And another frame holding line style options
   */
  m_VBox.pack_start(m_Frame_Line, Gtk::PACK_SHRINK);

  m_Grid_Line.set_border_width(5);
  m_Grid_Line.set_row_spacing(5);
  m_Grid_Line.set_column_spacing(10);
  m_Frame_Line.add(m_Grid_Line);


  type_listStrings dash_options;
  dash_options.push_back("Solid");
  dash_options.push_back("Dashed");
  dash_options.push_back("Dotted");

  add_row(m_Grid_Line, 0, m_refSizeGroup, "_Dashing", dash_options);

  type_listStrings end_options;
  end_options.push_back("Square");
  end_options.push_back("Round");
  end_options.push_back("Arrow");

  add_row(m_Grid_Line, 1, m_refSizeGroup, "_Line ends", end_options);

  /* And a check button to turn grouping on and off */
  m_VBox.pack_start(m_CheckButton, Gtk::PACK_SHRINK);
  m_CheckButton.set_active();
  m_CheckButton.signal_toggled().connect(sigc::mem_fun(*this, &Example_SizeGroup::on_checkbutton_toggled));

  show_all();
}

Example_SizeGroup::~Example_SizeGroup()
{
}

void Example_SizeGroup::on_checkbutton_toggled()
{
  Gtk::SizeGroupMode new_mode = Gtk::SIZE_GROUP_HORIZONTAL;

  if(m_CheckButton.get_active())
    new_mode = Gtk::SIZE_GROUP_HORIZONTAL;
  else
    new_mode = Gtk::SIZE_GROUP_NONE;

  m_refSizeGroup->set_mode(new_mode);
}

void Example_SizeGroup::add_row(Gtk::Grid& grid, int row,
                                const Glib::RefPtr<Gtk::SizeGroup>& size_group,
                                const Glib::ustring& label_text,
                                const std::list<Glib::ustring>& options)
{
  Gtk::Label* pLabel = Gtk::manage(new Gtk::Label(label_text, Gtk::ALIGN_START, Gtk::ALIGN_END, true));

  grid.attach(*pLabel, 0, row, 1, 1);
  pLabel->set_hexpand();

  Gtk::ComboBoxText* pComboBoxText = create_combobox(options);
  pLabel->set_mnemonic_widget(*pComboBoxText);
  size_group->add_widget(*pComboBoxText);

  grid.attach(*pComboBoxText, 1, row, 1, 1);
}

/* Convenience function to create an option menu holding a number of strings
 */
Gtk::ComboBoxText* Example_SizeGroup::create_combobox(const std::list<Glib::ustring>& strings)
{
  Gtk::ComboBoxText* pCombo = Gtk::manage( new Gtk::ComboBoxText() );

  for(type_listStrings::const_iterator iter = strings.begin(); iter != strings.end(); iter++)
  {
    pCombo->append(*iter);
  }

  return pCombo;
}

void Example_SizeGroup::on_response(int)
{
  hide();
}

