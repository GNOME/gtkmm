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
  m_refActionGroup = Gtk::ActionGroup::create();

  //TODO: Consider ways to reduce the amount of code here:
  //For instance,
  //  Use a list, with push_back(), and add that.
  //
  //In real life, I don't think that the details would be supplied _as well as_ the stock IDs.

  //Add normal Actions:
  m_refActionGroup->add_action( Gtk::Action::create("FileMenu", Gtk::StockID(), "_File") ); 
  m_refActionGroup->add_action( Gtk::Action::create("PreferencesMenu", Gtk::StockID(), "_Preferences") );
  m_refActionGroup->add_action( Gtk::Action::create("ColorMenu", Gtk::StockID(), "_Color") );
  m_refActionGroup->add_action( Gtk::Action::create("ShapeMenu", Gtk::StockID(), "_Shape") );
  m_refActionGroup->add_action( Gtk::Action::create("HelpMenu", Gtk::StockID(), "_Help") );
  m_refActionGroup->add_action( Gtk::Action::create("New", Gtk::Stock::NEW,  "_New", "Create a new file"),
    Gtk::ActionGroup::AccelKey("<control>N"), SigC::slot(*this, &Example_UIManager::on_action_activated) );
  m_refActionGroup->add_action( Gtk::Action::create("Open", Gtk::Stock::OPEN, "_Open", "Open a file"),
    Gtk::ActionGroup::AccelKey("<control>O"), SigC::slot(*this, &Example_UIManager::on_action_activated) );
  m_refActionGroup->add_action( Gtk::Action::create("Save", Gtk::Stock::SAVE, "_Save", "Save current file"),
    Gtk::ActionGroup::AccelKey("<control>S"), SigC::slot(*this, &Example_UIManager::on_action_activated) );
  m_refActionGroup->add_action( Gtk::Action::create("SaveAs", Gtk::Stock::SAVE, "Save _As...", "Save to a file"),
    SigC::slot(*this, &Example_UIManager::on_action_activated) );
  m_refActionGroup->add_action( Gtk::Action::create("Quit", Gtk::Stock::QUIT, "_Quit", "Quit"),
    Gtk::ActionGroup::AccelKey("<control>Q"), SigC::slot(*this, &Example_UIManager::on_action_activated) );
  m_refActionGroup->add_action( Gtk::Action::create("About", Gtk::StockID(), "_About", "About"),
    Gtk::ActionGroup::AccelKey("<control>A"), SigC::slot(*this, &Example_UIManager::on_action_activated) );
  //TODO: This StockID does not seem to be registered in the C version either, but it is in appwindow.c:
  m_refActionGroup->add_action( Gtk::Action::create("Logo", Gtk::StockID("demo-gtk-logo"), "", "GTK+"),
    SigC::slot(*this, &Example_UIManager::on_action_activated) );

  //Add Toggle Actions:
  m_refActionGroup->add_action( Gtk::ToggleAction::create("Bold", Gtk::Stock::BOLD, "_Bold", "Bold"),
    Gtk::ActionGroup::AccelKey("<control>B"), SigC::slot(*this, &Example_UIManager::on_action_activated) );

  //Add Radio Actions:
  //TODO: As mentioned above, a list would be good here, so that we can just specify the same slot once:
  m_refActionGroup->add_action( Gtk::RadioAction::create("Red", Gtk::StockID(), "_Red", "Blood"),
    Gtk::ActionGroup::AccelKey("<control>R"), SigC::bind( SigC::slot(*this, &Example_UIManager::on_radio_action_color_activated), COLOR_RED ) );
  m_refActionGroup->add_action( Gtk::RadioAction::create("Green", Gtk::StockID(), "_Green", "Grass"),
    Gtk::ActionGroup::AccelKey("<control>G"), SigC::bind( SigC::slot(*this, &Example_UIManager::on_radio_action_color_activated), COLOR_GREEN ) );
  m_refActionGroup->add_action( Gtk::RadioAction::create("Blue", Gtk::StockID(), "_Blue", "Sky"),
    Gtk::ActionGroup::AccelKey("<control>B"), SigC::bind( SigC::slot(*this, &Example_UIManager::on_radio_action_color_activated), COLOR_BLUE ) );

  m_refActionGroup->add_action( Gtk::RadioAction::create("Square", Gtk::StockID(), "_Square", "Square"),
    Gtk::ActionGroup::AccelKey("<control>S"), SigC::bind( SigC::slot(*this, &Example_UIManager::on_radio_action_shape_activated), SHAPE_SQUARE ) );
  m_refActionGroup->add_action( Gtk::RadioAction::create("Rectangle", Gtk::StockID(), "_Rectangle", "Rectangle"),
    Gtk::ActionGroup::AccelKey("<control>R"), SigC::bind( SigC::slot(*this, &Example_UIManager::on_radio_action_shape_activated), SHAPE_RECTANGLE ) );
  m_refActionGroup->add_action( Gtk::RadioAction::create("Oval", Gtk::StockID(), "_Oval", "Egg"),
    Gtk::ActionGroup::AccelKey("<control>O"), SigC::bind( SigC::slot(*this, &Example_UIManager::on_radio_action_shape_activated), SHAPE_OVAL ) );


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

  m_Button.signal_clicked().connect( SigC::slot( *this, &Example_UIManager::on_button_clicked ) );
  
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
