#include <gtkmm.h>
#include <iostream>

void on_destroyed_optionmenuderived(GtkWidget* widget, gpointer)
{
  std::cout << "on_destroyed_optionmenuderived" << std::endl;
}

void on_destroyed_menuderived(GtkWidget* widget, gpointer)
{
  std::cout << "on_destroyed_menuderived" << std::endl;
}

class OptionMenuDerived : public Gtk::OptionMenu
{
public:
  OptionMenuDerived()
  {
  g_signal_connect (gobj(), "destroy",
				G_CALLBACK (on_destroyed_optionmenuderived), NULL);
  }
  
  ~OptionMenuDerived()
  {
    remove_menu();
    std::cout << "~OptionMenuDerived()" << std::endl;
  }
};

class MenuDerived : public Gtk::Menu
{
public:
  MenuDerived()
  {
  g_signal_connect (gobj(), "destroy",
				G_CALLBACK (on_destroyed_menuderived), NULL);
  }
  
  ~MenuDerived()
  {
    std::cout << "~MenuDerived() 1" << std::endl;
 
    std::cout << "~MenuDerived() 2" << std::endl;

  }
};

class test_window : public Gtk::Window
{
public:
  test_window();
  ~test_window()
  {
    std::cout << "~test_window()1" << std::endl;

   }
  
protected:

  //Gtk::MenuItem m_MenuItem;
  MenuDerived m_Menu;
  OptionMenuDerived m_OptionMenu;
};

test_window::test_window()
//: m_MenuItem("One")
{
  //  m_Menu.append(m_MenuItem);
  m_OptionMenu.set_menu(m_Menu);
  add(m_OptionMenu);
  //show_all();
}

int main(int argc, char *argv[])
{
  Gtk::Main main_runner(argc, argv);
  test_window foo;
  Gtk::Main::run(foo);

  return(0);
}
