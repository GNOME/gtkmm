/* Menus
 *
 * There are several widgets involved in displaying menus. The
 * GtkMenuBar widget is a horizontal menu bar, which normally appears
 * at the top of an application. The GtkMenu widget is the actual menu
 * that pops up. Both GtkMenuBar and GtkMenu are subclasses of
 * GtkMenuShell; a GtkMenuShell contains menu items
 * (GtkMenuItem). Each menu item contains text and/or images and can
 * be selected by the user.
 *
 * There are several kinds of menu item, including plain GtkMenuItem,
 * GtkCheckMenuItem which can be checked/unchecked, GtkRadioMenuItem
 * which is a check menu item that's in a mutually exclusive group,
 * GtkSeparatorMenuItem which is a separator bar, GtkTearoffMenuItem
 * which allows a GtkMenu to be torn off, and GtkImageMenuItem which
 * can place a GtkImage or other widget next to the menu text.
 *
 * A GtkMenuItem can have a submenu, which is simply a GtkMenu to pop
 * up when the menu item is selected. Typically, all menu items in a menu bar
 * have submenus.
 *
 * GtkUIManager provides a higher-level interface for creating menu bars
 * and menus; while you can construct menus manually, most people don't
 * do that. There's a separate demo for GtkUIManager.
 *
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

  virtual Gtk::Menu* create_menu(gint depth, bool tearoff);

  //Member widgets:
  Gtk::Frame m_Frame_Horizontal, m_Frame_Vertical;
  Gtk::VBox m_VBox1, m_VBox_Sub1, m_VBox_Sub2;
  Gtk::MenuBar m_MenuBar;
  Gtk::OptionMenu m_OptionMenu;
  Gtk::HSeparator m_Separator;
  Gtk::Button m_Button;
};

//Called by DemoWindow;
Gtk::Window* do_menus()
{
  return new Example_Menus();
}

Example_Menus::Example_Menus()
: m_VBox_Sub1(false, 10),
  m_VBox_Sub2(false, 10),
  m_Button("close")
{
  set_title("menus");
  set_border_width(0);

  add(m_VBox1);

  m_VBox1.pack_start(m_MenuBar, Gtk::PACK_SHRINK);

  {
    using namespace Gtk::Menu_Helpers;
    MenuList items = m_MenuBar.items();

    items.push_back(MenuElem("test\nline2"));
    Gtk::MenuItem* pMenuItem = &items.back();
    pMenuItem->set_submenu( *(create_menu(2, true)) );

    items.push_back(MenuElem("foo"));
    pMenuItem = &items.back();
    pMenuItem->set_submenu( *(create_menu(3, true)) );

    items.push_back(MenuElem("bar"));
    pMenuItem = &items.back();
    pMenuItem->set_submenu( *(create_menu(4, true)) );
    pMenuItem->set_right_justified();
  }


  m_VBox_Sub1.set_border_width(10);
  m_VBox1.pack_start(m_VBox_Sub1);

  {
    Gtk::Menu* pMenu = create_menu(1, false);
    pMenu->set_accel_group(get_accel_group());

    using namespace Gtk::Menu_Helpers;
    MenuList items = pMenu->items();

    items.push_back(SeparatorElem());
    items.push_back( CheckMenuElem("Accelerate Me", Gtk::AccelKey(GDK_F1, Gdk::ModifierType(0))) );
    items.push_back( CheckMenuElem("Accelerator Locked") );
    items.back().add_accelerator("activate", get_accel_group(), GDK_F2, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE | Gtk::ACCEL_LOCKED);
    items.push_back( CheckMenuElem("Accelerator Frozen") );
    items.back().add_accelerator("activate", get_accel_group(), GDK_F2, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE);
    items.back().add_accelerator("activate", get_accel_group(), GDK_F3, Gdk::ModifierType(0), Gtk::ACCEL_VISIBLE);

    m_OptionMenu.set_menu(*pMenu);
    m_OptionMenu.set_history(3);

    m_VBox_Sub1.pack_start(m_OptionMenu);
  }

  m_VBox1.pack_start(m_Separator, Gtk::PACK_SHRINK);


  m_VBox_Sub2.set_border_width(10);
  m_VBox1.pack_start(m_VBox_Sub2, Gtk::PACK_SHRINK);

  m_Button.signal_clicked().connect(SigC::slot(*this, &Example_Menus::on_button_clicked));

  m_VBox_Sub2.pack_start(m_Button);
  m_Button.property_can_default().set_value(true);
  m_Button.grab_default();

  show_all();
}

Example_Menus::~Example_Menus()
{
}

Gtk::Menu* Example_Menus::create_menu(gint depth, bool tearoff)
{
  if (depth < 1)
    return 0;

  Gtk::Menu* pMenu = Gtk::manage(new Gtk::Menu());

  {
    using namespace Gtk::Menu_Helpers;

    MenuList items = pMenu->items();

    if(tearoff)
    {
      items.push_back(TearoffMenuElem());
    }

    Gtk::RadioMenuItem::Group radiogroup;

    for(int i = 0, j = 1; i < 5; i++, j++)
    {
      char buf[32];
      sprintf(buf, "item %2d - %d", depth, j);

      items.push_back(RadioMenuElem(radiogroup, buf));

      Gtk::MenuItem* pMenuItem = &items.back();
      if(pMenuItem)
      {
        if(i == 3)
          pMenuItem->set_sensitive(false);

        Gtk::Menu* pSubMenu = create_menu(depth - 1, true);
        if(pSubMenu)
         pMenuItem->set_submenu(*pSubMenu);
      }
    }
  }

  return pMenu;
}

void Example_Menus::on_button_clicked()
{
  hide();
}


