/* UI Manager
 *
 * The UIManager object allows the easy creation of menus
 * from an array of actions and a description of the menu hierarchy.
 */

#include <gtkmm.h>
#include <iostream>


class Example_UIManager : public Gtk::Window
{
public:
  Example_UIManager();
  virtual ~Example_UIManager();

protected:
  enum color
  {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE
  };

  enum shape
  {
    SHAPE_SQUARE,
    SHAPE_RECTANGLE,
    SHAPE_OVAL
  };

  //Signal handlers:
  virtual void on_button_clicked();
  virtual void on_action_activated();
  virtual void on_radio_action_color_activated(color chosen_color);
  virtual void on_radio_action_shape_activated(shape chosen_shape);
 
   
  //Member widgets:
  Gtk::VBox m_Box1;
  Gtk::VBox m_Box2;
  Gtk::HSeparator m_Separator;
  Gtk::Label m_Label;
  Gtk::Button m_Button;
  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
};


//Called by DemoWindow;
Gtk::Window* do_ui_manager()
{
  return new Example_UIManager();
}


Example_UIManager::Example_UIManager()
: m_Box2(false, 10),
  m_Label("Type\n<alt>\nto start"),
  m_Button("close")
{
  set_title("UI Manager");
  set_border_width(0);

  //Define the actions:
  m_refActionGroup = Gtk::ActionGroup::create("Actions"); //It also works with no name, which is probably better if there is only one.

  //In real life, the details would not be supplied _in addition _ the stock IDs.

  //Add normal Actions:
  m_refActionGroup->add( Gtk::Action::create("FileMenu", "_File") ); 
  m_refActionGroup->add( Gtk::Action::create("PreferencesMenu", "_Preferences") );
  m_refActionGroup->add( Gtk::Action::create("ColorMenu", "_Color") );
  m_refActionGroup->add( Gtk::Action::create("ShapeMenu", "_Shape") );
  m_refActionGroup->add( Gtk::Action::create("HelpMenu", "_Help") );
  m_refActionGroup->add( Gtk::Action::create("New", Gtk::Stock::NEW, "_New", "Create a new file"),
    sigc::mem_fun(*this, &Example_UIManager::on_action_activated) );
  m_refActionGroup->add( Gtk::Action::create("Open", Gtk::Stock::OPEN, "_Open", "Open a file"),
    sigc::mem_fun(*this, &Example_UIManager::on_action_activated) );
  m_refActionGroup->add( Gtk::Action::create("Save", Gtk::Stock::SAVE, "_Save", "Save current file"),
    sigc::mem_fun(*this, &Example_UIManager::on_action_activated) );
  m_refActionGroup->add( Gtk::Action::create("SaveAs", Gtk::Stock::SAVE, "Save _As...", "Save to a file"),
    sigc::mem_fun(*this, &Example_UIManager::on_action_activated) );
  m_refActionGroup->add( Gtk::Action::create("Quit", Gtk::Stock::QUIT, "_Quit", "Quit"),
    sigc::mem_fun(*this, &Example_UIManager::on_action_activated) );
  m_refActionGroup->add( Gtk::Action::create("About", "_About", "About"),
    Gtk::AccelKey("<control>A"),
    sigc::mem_fun(*this, &Example_UIManager::on_action_activated) );
  //TODO: This StockID does not seem to be registered in the C version either, but it is in appwindow.c:
  m_refActionGroup->add( Gtk::Action::create("Logo", Gtk::StockID("demo-gtk-logo"), "", "GTK+"),
    sigc::mem_fun(*this, &Example_UIManager::on_action_activated) );

  //Add Toggle Actions:
  m_refActionGroup->add( Gtk::ToggleAction::create("Bold", Gtk::Stock::BOLD, "_Bold", "Bold", true /* is_active */),
    sigc::mem_fun(*this, &Example_UIManager::on_action_activated) );

  //Add Radio Actions:
  Gtk::RadioAction::Group group_colors;
  m_refActionGroup->add( Gtk::RadioAction::create(group_colors, "Red", "_Red", "Blood"),
    Gtk::AccelKey("<control>R"),
    sigc::bind<-1>( sigc::mem_fun(*this, &Example_UIManager::on_radio_action_color_activated), COLOR_RED ) );
  m_refActionGroup->add( Gtk::RadioAction::create(group_colors, "Green", "_Green", "Grass"),
    Gtk::AccelKey("<control>G"),
    sigc::bind<-1>( sigc::mem_fun(*this, &Example_UIManager::on_radio_action_color_activated), COLOR_GREEN ) );
  m_refActionGroup->add( Gtk::RadioAction::create(group_colors, "Blue", "_Blue", "Sky"),
    Gtk::AccelKey("<control>B"),
    sigc::bind<-1>( sigc::mem_fun(*this, &Example_UIManager::on_radio_action_color_activated), COLOR_BLUE ) );

  Gtk::RadioAction::Group group_shapes;
  m_refActionGroup->add( Gtk::RadioAction::create(group_shapes, "Square", "_Square", "Square"),
    Gtk::AccelKey("<control>S"),
    sigc::bind<-1>( sigc::mem_fun(*this, &Example_UIManager::on_radio_action_shape_activated), SHAPE_SQUARE ) );
  m_refActionGroup->add( Gtk::RadioAction::create(group_shapes, "Rectangle", "_Rectangle", "Rectangle"),
    Gtk::AccelKey("<control>R"),
    sigc::bind<-1>( sigc::mem_fun(*this, &Example_UIManager::on_radio_action_shape_activated), SHAPE_RECTANGLE ) );
  m_refActionGroup->add( Gtk::RadioAction::create(group_shapes, "Oval", "_Oval", "Egg"),
    Gtk::AccelKey("<control>O"),
    sigc::bind<-1>( sigc::mem_fun(*this, &Example_UIManager::on_radio_action_shape_activated), SHAPE_OVAL ) );

  m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(m_refActionGroup);
  add_accel_group(m_refUIManager->get_accel_group());

  //Layout the actions in a menubar and toolbar:
  try
  {
    Glib::ustring ui_info = 
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='FileMenu'>"
        "      <menuitem action='New'/>"
        "      <menuitem action='Open'/>"
        "      <menuitem action='Save'/>"
        "      <menuitem action='SaveAs'/>"
        "      <separator/>"
        "      <menuitem action='Quit'/>"
        "    </menu>"
        "    <menu action='PreferencesMenu'>"
        "      <menu action='ColorMenu'>"
        "	<menuitem action='Red'/>"
        "	<menuitem action='Green'/>"
        "	<menuitem action='Blue'/>"
        "      </menu>"
        "      <menu action='ShapeMenu'>"
        "        <menuitem action='Square'/>"
        "        <menuitem action='Rectangle'/>"
        "        <menuitem action='Oval'/>"
        "      </menu>"
        "      <menuitem action='Bold'/>"
        "    </menu>"
        "    <menu action='HelpMenu'>"
        "      <menuitem action='About'/>"
        "    </menu>"
        "  </menubar>"
        "  <toolbar  name='ToolBar'>"
        "    <toolitem action='Open'/>"
        "    <toolitem action='Quit'/>"
        "    <separator action='Sep1'/>"
        "    <toolitem action='Logo'/>"
        "  </toolbar>"
        "</ui>";
        
    m_refUIManager->add_ui_from_string(ui_info);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "building menus failed: " <<  ex.what();
  }

  add(m_Box1);
  Gtk::Widget* pMenuBar = m_refUIManager->get_widget("/MenuBar") ;
  m_Box1.pack_start(*pMenuBar, Gtk::PACK_SHRINK);

  m_Label.set_size_request(200, 200);
  m_Label.set_alignment(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
  m_Box1.pack_start(m_Label, Gtk::PACK_EXPAND_WIDGET);
     
  m_Box1.pack_start(m_Separator, Gtk::PACK_EXPAND_WIDGET);
   
  m_Box2.set_border_width(10);
  m_Box1.pack_start(m_Box2, Gtk::PACK_EXPAND_WIDGET);

  m_Button.signal_clicked().connect( sigc::mem_fun( *this, &Example_UIManager::on_button_clicked ) );
  
  m_Box2.pack_start(m_Button, Gtk::PACK_EXPAND_WIDGET);
  m_Button.set_flags(Gtk::CAN_DEFAULT);
  m_Button.grab_default();

  show_all();
}

Example_UIManager::~Example_UIManager()
{
}

void Example_UIManager::on_button_clicked()
{
  hide();
}

void Example_UIManager::on_action_activated()
{
  std::cout << "Action activated." << std::endl;
}

void Example_UIManager::on_radio_action_color_activated(color chosen_color)
{
  std::cout << "Color Radio Action selected. Item selected=" << chosen_color << std::endl;
}

void Example_UIManager::on_radio_action_shape_activated(shape chosen_shape)
{
  std::cout << "Shape Radio Action selected. Item selected=" << chosen_shape << std::endl;
}
