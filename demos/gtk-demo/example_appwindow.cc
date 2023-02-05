/* Application main window
 *
 * Demonstrates a typical application window, with menubar and toolbar.
 *
 * Despite its name, this demo uses a Gtk::Window and not a Gtk::ApplicationWindow.
 *
 * There are several examples in the gtkmm tutorial, showing slightly different
 * ways of constructing similar application windows.
 *
 * https://gnome.pages.gitlab.gnome.org/gtkmm-documentation
 */

#include <gtkmm.h>

class Example_AppWindow : public Gtk::Window
{
public:
  Example_AppWindow();
  ~Example_AppWindow() override;

protected:
  //Signal handlers:
  void on_menu_item();
  void on_text_changed();
  void on_text_mark_set(const Gtk::TextBuffer::iterator& new_location,
    const Glib::RefPtr<Gtk::TextBuffer::Mark>& mark);
  void on_file_quit();

  //Member widgets:
  Gtk::Box m_VBox;
  Gtk::PopoverMenuBar m_Menubar;
  Gtk::Box m_Toolbar;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::Label m_Statusbar;
  Gtk::TextView m_TextView;
};

//Called by DemoWindow;
Gtk::Window* do_appwindow()
{
  return new Example_AppWindow();
}


Example_AppWindow::Example_AppWindow()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Toolbar(Gtk::Orientation::HORIZONTAL)
{
  set_title("Application Window");
  set_default_size(350, 150);

  set_child(m_VBox);

  // Create the menu:
  auto win_menu = Gio::Menu::create();

  // File menu:
  auto menu_file = Gio::Menu::create();
  win_menu->append_submenu("_File", menu_file);
  auto file_section1 = Gio::Menu::create();
  file_section1->append("_New", "example.new");
  file_section1->append("_Open", "example.open");
  file_section1->append("_Save", "example.save");
  file_section1->append("Save _As...", "example.saveas");
  menu_file->append_section(file_section1);
  auto file_section2 = Gio::Menu::create();
  file_section2->append("_Quit", "example.quit");
  menu_file->append_section(file_section2);

  // Preferences menu:
  auto menu_pref = Gio::Menu::create();
  win_menu->append_submenu("_Preferences", menu_pref);

  // Color submenu:
  auto submenu_color = Gio::Menu::create();
  submenu_color->append("_Red", "example.red");
  submenu_color->append("_Green", "example.green");
  submenu_color->append("_Blue", "example.blue");
  menu_pref->append_submenu("_Color", submenu_color);

  // Shape submenu:
  auto submenu_shape = Gio::Menu::create();
  submenu_shape->append("_Square", "example.square");
  submenu_shape->append("_Rectangle", "example.rectangle");
  submenu_shape->append("_Circle", "example.circle");
  menu_pref->append_submenu("_Shape", submenu_shape);

  // Help menu:
  auto menu_help = Gio::Menu::create();
  menu_help->append("_About", "example.about");
  win_menu->append_submenu("_Help", menu_help);

  // Add the menu to the menubar.
  m_Menubar.set_menu_model(win_menu);

  // Add the menubar to the VBox:
  m_VBox.append(m_Menubar);

  // Define the actions:
  auto action_group = Gio::SimpleActionGroup::create();
  action_group->add_action("new", sigc::mem_fun(*this, &Example_AppWindow::on_menu_item));
  action_group->add_action("open", sigc::mem_fun(*this, &Example_AppWindow::on_menu_item));
  action_group->add_action("save", sigc::mem_fun(*this, &Example_AppWindow::on_menu_item));
  action_group->add_action("saveas", sigc::mem_fun(*this, &Example_AppWindow::on_menu_item));
  action_group->add_action("quit", sigc::mem_fun(*this, &Example_AppWindow::on_file_quit));
  action_group->add_action("red", sigc::mem_fun(*this, &Example_AppWindow::on_menu_item));
  action_group->add_action("green", sigc::mem_fun(*this, &Example_AppWindow::on_menu_item));
  action_group->add_action("blue", sigc::mem_fun(*this, &Example_AppWindow::on_menu_item));
  action_group->add_action("square", sigc::mem_fun(*this, &Example_AppWindow::on_menu_item));
  action_group->add_action("rectangle", sigc::mem_fun(*this, &Example_AppWindow::on_menu_item));
  action_group->add_action("circle", sigc::mem_fun(*this, &Example_AppWindow::on_menu_item));
  action_group->add_action("about", sigc::mem_fun(*this, &Example_AppWindow::on_menu_item));
  insert_action_group("example", action_group);

  // Set accelerator keys:
  auto controller = Gtk::ShortcutController::create();
  controller->set_scope(Gtk::ShortcutScope::LOCAL);
  add_controller(controller);
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_n, Gdk::ModifierType::CONTROL_MASK),
    Gtk::NamedAction::create("example.new")));
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_o, Gdk::ModifierType::CONTROL_MASK),
    Gtk::NamedAction::create("example.open")));
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_s, Gdk::ModifierType::CONTROL_MASK),
    Gtk::NamedAction::create("example.save")));
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_q, Gdk::ModifierType::CONTROL_MASK),
    Gtk::NamedAction::create("example.quit")));
  controller->add_shortcut(Gtk::Shortcut::create(
    Gtk::KeyvalTrigger::create(GDK_KEY_F7),
    Gtk::NamedAction::create("example.about")));

  // Toolbar:
  m_Toolbar.set_hexpand();
  m_VBox.append(m_Toolbar);
  auto toolbar_button = Gtk::make_managed<Gtk::Button>();
  toolbar_button->set_icon_name("document-new");
  toolbar_button->set_tooltip_text("Create a new file");
  toolbar_button->set_action_name("example.new");
  m_Toolbar.append(*toolbar_button);

  toolbar_button = Gtk::make_managed<Gtk::Button>();
  toolbar_button->set_icon_name("document-open");
  toolbar_button->set_tooltip_text("Open a file");
  toolbar_button->set_action_name("example.open");
  m_Toolbar.append(*toolbar_button);

  toolbar_button = Gtk::make_managed<Gtk::Button>();
  toolbar_button->set_icon_name("document-save");
  toolbar_button->set_tooltip_text("Save a file");
  toolbar_button->set_action_name("example.save");
  m_Toolbar.append(*toolbar_button);

  m_Toolbar.append(*Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::VERTICAL));

  toolbar_button = Gtk::make_managed<Gtk::Button>();
  toolbar_button->set_icon_name("application-exit");
  toolbar_button->set_tooltip_text("Quit");
  toolbar_button->set_action_name("example.quit");
  m_Toolbar.append(*toolbar_button);

  // Scrolled window for the text view.
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_has_frame(true);
  m_VBox.append(m_ScrolledWindow);
  m_ScrolledWindow.set_child(m_TextView);

  // Statusbar (Actually a Label. The Gtk::Statusbar widget is deprecated.)
  m_Statusbar.set_hexpand();
  m_VBox.append(m_Statusbar);

  // Show text widget info in the statusbar.
  auto refTextBuffer = m_TextView.get_buffer();
  refTextBuffer->signal_changed().connect(sigc::mem_fun(*this, &Example_AppWindow::on_text_changed));
  refTextBuffer->signal_mark_set().connect(sigc::mem_fun(*this, &Example_AppWindow::on_text_mark_set));
  on_text_changed();
}

Example_AppWindow::~Example_AppWindow()
{
}

void Example_AppWindow::on_menu_item()
{
  auto dialog = Gtk::AlertDialog::create("You selected or toggled a menu item");
  dialog->show(*this);
}

void Example_AppWindow::on_text_changed()
{
  auto refBuffer = m_TextView.get_buffer();
  gint count = refBuffer->get_char_count();

  auto iter = refBuffer->get_iter_at_mark(refBuffer->get_insert());

  gint row = iter.get_line();
  gint col = iter.get_line_offset();

  m_Statusbar.set_text(Glib::ustring::sprintf(
    "Cursor at row %d column %d; %d chars in document", row, col, count));
}

void Example_AppWindow::on_text_mark_set(const Gtk::TextBuffer::iterator&,
  const Glib::RefPtr<Gtk::TextBuffer::Mark>&)
{
  on_text_changed();
}

void Example_AppWindow::on_file_quit()
{
  set_visible(false);
}
