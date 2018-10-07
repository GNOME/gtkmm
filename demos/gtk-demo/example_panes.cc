/* Paned Widgets
 *
 * The Gtk::Paned Widget divides its content area into two panes
 * with a divider in between that the user can adjust. A separate
 * child is placed into each pane. Gtk::Paned widgets can be split
 * horizontally or vertially.
 *
 * There are a number of options that can be set for each pane.
 * This test contains both a horizontal and a vertical Gtk::Paned
 * widget, and allows you to adjust the options for each side of
 * each widget.
 */

#include <gtkmm.h>

namespace
{

class Example_Panes : public Gtk::Window
{
public:
  Example_Panes();
  ~Example_Panes() override;
};

class PaneOptions : public Gtk::Frame
{
public:
  PaneOptions(Gtk::Paned& paned, const Glib::ustring& frame_label,
              const Glib::ustring& label1, const Glib::ustring& label2);
  ~PaneOptions() override;

private:
  // member widgets:
  Gtk::Paned*      m_pPaned;
  Gtk::CheckButton m_CheckButton_resize1;
  Gtk::CheckButton m_CheckButton_shrink1;
  Gtk::CheckButton m_CheckButton_resize2;
  Gtk::CheckButton m_CheckButton_shrink2;

  // signal handlers:
  void on_checkbutton1();
  void on_checkbutton2();
};


Example_Panes::Example_Panes()
{
  set_title("Panes");

  Gtk::Box *const pVBox = new Gtk::Box(Gtk::Orientation::VERTICAL);
  add(*Gtk::manage(pVBox));

  Gtk::Paned *const pVPaned = new Gtk::Paned(Gtk::Orientation::VERTICAL);
  pVBox->pack_start(*Gtk::manage(pVPaned), Gtk::PackOptions::EXPAND_WIDGET);
  pVPaned->property_margin() = 5;

  Gtk::Paned *const pHPaned = new Gtk::Paned(Gtk::Orientation::HORIZONTAL);
  pVPaned->add1(*Gtk::manage(pHPaned));

  Gtk::Frame *const pFrame1 = new Gtk::Frame();
  pHPaned->add1(*Gtk::manage(pFrame1));
  pFrame1->set_shadow_type(Gtk::ShadowType::IN);
  pFrame1->set_size_request(60, 60);
  pFrame1->add(*Gtk::make_managed<Gtk::Button>("_Hi there", true));

  Gtk::Frame *const pFrame2 = new Gtk::Frame();
  pHPaned->add2(*Gtk::manage(pFrame2));
  pFrame2->set_shadow_type(Gtk::ShadowType::IN);
  pFrame2->set_size_request(80, 60);

  Gtk::Frame *const pFrame3 = new Gtk::Frame();
  pVPaned->add2(*Gtk::manage(pFrame3));
  pFrame3->set_shadow_type(Gtk::ShadowType::IN);
  pFrame3->set_size_request(60, 80);

  // Now create check buttons to control sizing
  pVBox->pack_start(*Gtk::make_managed<PaneOptions>(*pHPaned, "Horizontal", "Left", "Right"), Gtk::PackOptions::SHRINK);
  pVBox->pack_start(*Gtk::make_managed<PaneOptions>(*pVPaned, "Vertical", "Top", "Bottom"),   Gtk::PackOptions::SHRINK);
}

Example_Panes::~Example_Panes()
{}


PaneOptions::PaneOptions(Gtk::Paned& paned, const Glib::ustring& frame_label,
                         const Glib::ustring& label1, const Glib::ustring& label2)
:
  Gtk::Frame            (frame_label),
  m_pPaned              (&paned),
  m_CheckButton_resize1 ("_Resize", true),
  m_CheckButton_shrink1 ("_Shrink", true),
  m_CheckButton_resize2 ("_Resize", true),
  m_CheckButton_shrink2 ("_Shrink", true)
{
  Gtk::Grid *const pGrid = new Gtk::Grid();
  pGrid->property_margin() = 4;
  add(*Gtk::manage(pGrid));

  pGrid->attach(*Gtk::make_managed<Gtk::Label>(label1), 0, 0, 1, 1);
  pGrid->attach(*Gtk::make_managed<Gtk::Label>(label2), 1, 0, 1, 1);

  pGrid->attach(m_CheckButton_resize1, 0, 1, 1, 1);
  pGrid->attach(m_CheckButton_shrink1, 0, 2, 1, 1);
  pGrid->attach(m_CheckButton_resize2, 1, 1, 1, 1);
  pGrid->attach(m_CheckButton_shrink2, 1, 2, 1, 1);

  m_CheckButton_resize1.set_active(false);
  m_CheckButton_shrink1.set_active(true);
  m_CheckButton_resize2.set_active(true);
  m_CheckButton_shrink2.set_active(true);

  m_CheckButton_resize1.signal_toggled().connect(sigc::mem_fun(*this, &PaneOptions::on_checkbutton1));
  m_CheckButton_shrink1.signal_toggled().connect(sigc::mem_fun(*this, &PaneOptions::on_checkbutton1));
  m_CheckButton_resize2.signal_toggled().connect(sigc::mem_fun(*this, &PaneOptions::on_checkbutton2));
  m_CheckButton_shrink2.signal_toggled().connect(sigc::mem_fun(*this, &PaneOptions::on_checkbutton2));

  // Sync Gtk::Paned options with the CheckButtons' state.  Actually, the
  // preset state of the buttons should match the Gtk::Paned default settings,
  // but it is definitely cleaner this way.
  on_checkbutton1();
  on_checkbutton2();
}

PaneOptions::~PaneOptions()
{}

void PaneOptions::on_checkbutton1()
{
  Gtk::Widget *const pChild = m_pPaned->get_child1();

  m_pPaned->remove(*pChild);
  m_pPaned->pack1(*pChild, m_CheckButton_resize1.get_active(), m_CheckButton_shrink1.get_active());
}

void PaneOptions::on_checkbutton2()
{
  Gtk::Widget *const pChild = m_pPaned->get_child2();

  m_pPaned->remove(*pChild);
  m_pPaned->pack2(*pChild, m_CheckButton_resize2.get_active(), m_CheckButton_shrink2.get_active());
}

} // anonymous namespace


// called by DemoWindow
Gtk::Window* do_panes()
{
  return new Example_Panes();
}

