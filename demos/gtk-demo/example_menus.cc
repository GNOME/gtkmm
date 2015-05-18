/* Menus
 *
 * There are several widgets involved in displaying menus. The
 * Gtk::MenuBar widget is a menu bar, which normally appears horizontally
 * at the top of an application, but can also be layed out vertically.
 * The Gtk::Menu widget is the actual menu that pops up. Both Gtk::MenuBar
 * and Gtk::Menu are subclasses of Gtk::MenuShell; a Gtk::MenuShell contains
 * menu items (Gtk::MenuItem). Each menu item contains text and/or images
 * and can be selected by the user.
 *
 * There are several kinds of menu item, including plain Gtk::MenuItem,
 * Gtk::CheckMenuItem which can be checked/unchecked, Gtk::RadioMenuItem
 * which is a check menu item that's in a mutually exclusive group,
 * Gtk::SeparatorMenuItem which is a separator bar, and Gtk::ImageMenuItem which
 * can place a Gtk::Image or other widget next to the menu text.
 *
 * A Gtk::MenuItem can have a submenu, which is simply a Gtk::Menu to pop
 * up when the menu item is selected. Typically, all menu items in a menu bar
 * have submenus.
 *
 * Gtk::Builder provides a higher-level interface for creating menu bars
 * and menus; while you can construct menus manually, most people don't
 * do that. There's a separate demo for Gtk::Builder.
 */

#include "gtkmm.h"
#include <stdio.h>

class Example_Menus : public Gtk::Window
{
public:
  Example_Menus();
  virtual ~Example_Menus();

protected:
  //signal handlers:
  virtual void on_button_clicked();

  virtual Gtk::Menu* create_menu(gint depth);

  //Member widgets:
  Gtk::Frame m_Frame_Horizontal, m_Frame_Vertical;
  Gtk::Box m_VBox1, m_VBox_Sub1, m_VBox_Sub2;
  Gtk::MenuBar m_MenuBar;
  Gtk::Separator m_Separator;
  Gtk::Button m_Button;
};

//Called by DemoWindow;
Gtk::Window* do_menus()
{
  return new Example_Menus();
}

Example_Menus::Example_Menus()
: m_VBox1(Gtk::ORIENTATION_VERTICAL),
  m_VBox_Sub1(Gtk::ORIENTATION_VERTICAL, 10),
  m_VBox_Sub2(Gtk::ORIENTATION_VERTICAL, 10),
  m_Separator(Gtk::ORIENTATION_HORIZONTAL),
  m_Button("close")
{
  set_title("menus");
  set_border_width(0);

  add(m_VBox1);

  m_VBox1.pack_start(m_MenuBar, Gtk::PACK_SHRINK);

  {
    //Note:: It's generally easier to use the Gtk::Builder API.
    Gtk::MenuItem* pMenuItem = Gtk::manage(new Gtk::MenuItem("test\nline2"));
    pMenuItem->set_submenu( *(create_menu(2)) );
    m_MenuBar.append(*pMenuItem);
    pMenuItem->show();

    pMenuItem = Gtk::manage(new Gtk::MenuItem("foo"));
    pMenuItem->set_submenu( *(create_menu(3)) );
    m_MenuBar.append(*pMenuItem);
    pMenuItem->show();

    pMenuItem = Gtk::manage(new Gtk::MenuItem("bar"));
    pMenuItem->set_submenu( *(create_menu(4)) );
    m_MenuBar.append(*pMenuItem);
    pMenuItem->show();
  }


  m_VBox_Sub1.set_border_width(10);
  m_VBox1.pack_start(m_VBox_Sub1);

  {
    Gtk::Menu* pMenu = create_menu(1);
    pMenu->set_accel_group(get_accel_group());

    Gtk::MenuItem* pMenuItem = Gtk::manage(new Gtk::SeparatorMenuItem());
    pMenu->append(*pMenuItem);
    pMenuItem->show();

    pMenuItem = Gtk::manage(new Gtk::CheckMenuItem("Accelerate Me"));
    pMenuItem->add_accelerator("activate", get_accel_group(), GDK_KEY_F1, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE );
    pMenu->append(*pMenuItem);
    pMenuItem->show();

    pMenuItem = Gtk::manage(new Gtk::CheckMenuItem("Accelerator Locked"));
    pMenu->append(*pMenuItem);
    pMenuItem->add_accelerator("activate", get_accel_group(), GDK_KEY_F2, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE | Gtk::ACCEL_LOCKED);
    pMenuItem->show();

    pMenuItem = Gtk::manage(new Gtk::CheckMenuItem("Accelerator Frozen"));
    pMenu->append(*pMenuItem);
    pMenuItem->add_accelerator("activate", get_accel_group(), GDK_KEY_F2, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE);
    pMenuItem->show();
  }

  m_VBox1.pack_start(m_Separator, Gtk::PACK_SHRINK);


  m_VBox_Sub2.set_border_width(10);
  m_VBox1.pack_start(m_VBox_Sub2, Gtk::PACK_SHRINK);

  m_Button.signal_clicked().connect(sigc::mem_fun(*this, &Example_Menus::on_button_clicked));

  m_VBox_Sub2.pack_start(m_Button);
  m_Button.property_can_default() = true;
  m_Button.grab_default();

  show_all();
}

Example_Menus::~Example_Menus()
{
}

Gtk::Menu* Example_Menus::create_menu(gint depth)
{
  if (depth < 1)
    return 0;

  Gtk::Menu* pMenu = Gtk::manage(new Gtk::Menu());

  {
    Gtk::RadioMenuItem::Group radiogroup;

    for(int i = 0, j = 1; i < 5; i++, j++)
    {
      char buf[32];
      sprintf(buf, "item %2d - %d", depth, j);

      Gtk::MenuItem* pMenuItem = Gtk::manage(new Gtk::RadioMenuItem(radiogroup, buf));
      pMenu->append(*pMenuItem);
      pMenuItem->show();

      if(i == 3)
        pMenuItem->set_sensitive(false);

      Gtk::Menu* pSubMenu = create_menu(depth - 1);
      if(pSubMenu)
        pMenuItem->set_submenu(*pSubMenu);
    }
  }

  return pMenu;
}

void Example_Menus::on_button_clicked()
{
  hide();
}
