/* Flow Box
 *
 * Gtk::FlowBox allows flexible and responsive grids which reflow
 * as needed and support sorting and filtering.
 *
 * The children of a FlowBox are regular widgets
 */

#include "gtkmm.h"

class Example_FlowBox : public Gtk::Window
{
public:
  Example_FlowBox();
  virtual ~Example_FlowBox();

protected:
  //Signal handlers:
  bool on_drawing_area_draw(const Cairo::RefPtr<Cairo::Context>& cr, int swatch_i);

  // Containers
  Gtk::ScrolledWindow m_scrolled_window;
  Gtk::FlowBox m_flow_box;

private:
  void fill_color_names();
  Gtk::Button* create_color_swatch(int swatch_i);

  std::vector<Glib::ustring> m_color_names;
};

//Called by DemoWindow;
Gtk::Window* do_flowbox()
{
  return new Example_FlowBox();
}

Example_FlowBox::Example_FlowBox()
{
  // Window properties
  set_title("FlowBox Example");
  set_default_size(600, 400);
  set_border_width(6);

  // Scrolled window
  m_scrolled_window.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);

  // Flow box
  m_flow_box.set_max_children_per_line(30);
  m_flow_box.set_selection_mode(Gtk::SELECTION_NONE);
  m_flow_box.set_homogeneous();

  // Color swatches
  fill_color_names();
  for(std::size_t i = 0; i != m_color_names.size(); ++i)
  {
    Gtk::Button* color_swatch = create_color_swatch(i);
    m_flow_box.add(*color_swatch);
  }

  // Layout
  m_scrolled_window.add(m_flow_box);
  add(m_scrolled_window);

  show_all_children();
}

Example_FlowBox::~Example_FlowBox()
{
}

Gtk::Button* Example_FlowBox::create_color_swatch(int swatch_i)
{
  Gtk::DrawingArea* drawing_area = Gtk::manage(new Gtk::DrawingArea());
  Gtk::Button* color_swatch = Gtk::manage(new Gtk::Button());

  drawing_area->set_size_request(24, 24);

  color_swatch->add(*drawing_area);
  drawing_area->signal_draw().connect(sigc::bind(sigc::mem_fun(*this, &Example_FlowBox::on_drawing_area_draw), swatch_i));

  return color_swatch;
}

bool Example_FlowBox::on_drawing_area_draw(const Cairo::RefPtr<Cairo::Context>& cr, int swatch_i)
{
  Gdk::RGBA rgba(m_color_names[swatch_i]);
  Gdk::Cairo::set_source_rgba(cr, rgba);
  cr->paint();

  return true;
}

void Example_FlowBox::fill_color_names()
{
  m_color_names.push_back("AliceBlue");
  m_color_names.push_back("AntiqueWhite");
  m_color_names.push_back("AntiqueWhite1");
  m_color_names.push_back("AntiqueWhite2");
  m_color_names.push_back("AntiqueWhite3");
  m_color_names.push_back("AntiqueWhite4");
  m_color_names.push_back("aqua");
  m_color_names.push_back("aquamarine");
  m_color_names.push_back("aquamarine1");
  m_color_names.push_back("aquamarine2");
  m_color_names.push_back("aquamarine3");
  m_color_names.push_back("aquamarine4");
  m_color_names.push_back("azure");
  m_color_names.push_back("azure1");
  m_color_names.push_back("azure2");
  m_color_names.push_back("azure3");
  m_color_names.push_back("azure4");
  m_color_names.push_back("beige");
  m_color_names.push_back("bisque");
  m_color_names.push_back("bisque1");
  m_color_names.push_back("bisque2");
  m_color_names.push_back("bisque3");
  m_color_names.push_back("bisque4");
  m_color_names.push_back("black");
  m_color_names.push_back("BlanchedAlmond");
  m_color_names.push_back("blue");
  m_color_names.push_back("blue1");
  m_color_names.push_back("blue2");
  m_color_names.push_back("blue3");
  m_color_names.push_back("blue4");
  m_color_names.push_back("BlueViolet");
  m_color_names.push_back("brown");
  m_color_names.push_back("brown1");
  m_color_names.push_back("brown2");
  m_color_names.push_back("brown3");
  m_color_names.push_back("brown4");
  m_color_names.push_back("burlywood");
  m_color_names.push_back("burlywood1");
  m_color_names.push_back("burlywood2");
  m_color_names.push_back("burlywood3");
  m_color_names.push_back("burlywood4");
  m_color_names.push_back("CadetBlue");
  m_color_names.push_back("CadetBlue1");
  m_color_names.push_back("CadetBlue2");
  m_color_names.push_back("CadetBlue3");
  m_color_names.push_back("CadetBlue4");
  m_color_names.push_back("chartreuse");
  m_color_names.push_back("chartreuse1");
  m_color_names.push_back("chartreuse2");
  m_color_names.push_back("chartreuse3");
  m_color_names.push_back("chartreuse4");
  m_color_names.push_back("chocolate");
  m_color_names.push_back("chocolate1");
  m_color_names.push_back("chocolate2");
  m_color_names.push_back("chocolate3");
  m_color_names.push_back("chocolate4");
  m_color_names.push_back("coral");
  m_color_names.push_back("coral1");
  m_color_names.push_back("coral2");
  m_color_names.push_back("coral3");
  m_color_names.push_back("coral4");
  m_color_names.push_back("CornflowerBlue");
  m_color_names.push_back("cornsilk");
  m_color_names.push_back("cornsilk1");
  m_color_names.push_back("cornsilk2");
  m_color_names.push_back("cornsilk3");
  m_color_names.push_back("cornsilk4");
  m_color_names.push_back("crimson");
  m_color_names.push_back("cyan");
  m_color_names.push_back("cyan1");
  m_color_names.push_back("cyan2");
  m_color_names.push_back("cyan3");
  m_color_names.push_back("cyan4");
  m_color_names.push_back("DarkBlue");
  m_color_names.push_back("DarkCyan");
  m_color_names.push_back("DarkGoldenrod");
  m_color_names.push_back("DarkGoldenrod1");
  m_color_names.push_back("DarkGoldenrod2");
  m_color_names.push_back("DarkGoldenrod3");
  m_color_names.push_back("DarkGoldenrod4");
  m_color_names.push_back("DarkGray");
  m_color_names.push_back("DarkGreen");
  m_color_names.push_back("DarkGrey");
  m_color_names.push_back("DarkKhaki");
  m_color_names.push_back("DarkMagenta");
  m_color_names.push_back("DarkOliveGreen");
  m_color_names.push_back("DarkOliveGreen1");
  m_color_names.push_back("DarkOliveGreen2");
  m_color_names.push_back("DarkOliveGreen3");
  m_color_names.push_back("DarkOliveGreen4");
  m_color_names.push_back("DarkOrange");
  m_color_names.push_back("DarkOrange1");
  m_color_names.push_back("DarkOrange2");
  m_color_names.push_back("DarkOrange3");
  m_color_names.push_back("DarkOrange4");
  m_color_names.push_back("DarkOrchid");
  m_color_names.push_back("DarkOrchid1");
  m_color_names.push_back("DarkOrchid2");
  m_color_names.push_back("DarkOrchid3");
  m_color_names.push_back("DarkOrchid4");
  m_color_names.push_back("DarkRed");
  m_color_names.push_back("DarkSalmon");
  m_color_names.push_back("DarkSeaGreen");
  m_color_names.push_back("DarkSeaGreen1");
}
