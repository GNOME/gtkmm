//TODO: Update this example:
#undef GTKMM_DISABLE_DEPRECATED

#include <gtkmm/main.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/optionmenu.h>
#include <gtkmm/menu.h>
#include <gtkmm/stock.h>

#include <stdio.h>
//#include <glib.h>
//#include <gdk/gdk.h>
//#include <gtk/gtk.h>

class MainWindowClass 
    : public Gtk::Window
{
public:
    MainWindowClass ();
    virtual ~MainWindowClass ();

private:
  
    void quit_pressed_cb ();
    void toolbar_cb (const char*);
    void toolbar_item_cb (Gtk::Toolbar* toolbar, Gtk::ToolbarStyle style);
};

void 
MainWindowClass::toolbar_cb (const char* c)
{
    printf("toolbar_cb : %s\n", c);
}

void 
MainWindowClass::toolbar_item_cb (Gtk::Toolbar* toolbar,
                                  Gtk::ToolbarStyle style)
{
    toolbar->set_toolbar_style(style);
}

MainWindowClass::MainWindowClass()
{
    using namespace Gtk::Toolbar_Helpers;
    using namespace Gtk::Menu_Helpers;

    set_size_request (350,100);
  
    Gtk::VBox* vbox = manage (new Gtk::VBox (false, 0));
    add(*vbox);

    Gtk::Toolbar* toolbar = manage (new Gtk::Toolbar ());
    vbox->pack_start (*toolbar, Gtk::PACK_SHRINK);

    Gtk::OptionMenu* optionmenu = manage (new Gtk::OptionMenu ());
    vbox->pack_start (*optionmenu, Gtk::PACK_SHRINK);

    Gtk::Button* button = manage (new Gtk::Button ("Quit"));
    button->signal_clicked ()
        .connect(sigc::mem_fun (*this, &MainWindowClass::quit_pressed_cb));
    vbox->pack_start (*button);


    toolbar->tools ()
        .push_back (StockElem (Gtk::Stock::NEW,
                               sigc::bind (sigc::mem_fun (*this,
                                           &MainWindowClass::toolbar_cb),
                                     "New Item"),
                               "New Item"));
    toolbar->tools ()
        .push_back (StockElem (Gtk::Stock::OPEN,
                               sigc::bind (sigc::mem_fun (*this,
                                           &MainWindowClass::toolbar_cb),
                                     "Open Item"),
                               "Open Item"));
    toolbar->tools ()
        .push_back (StockElem (Gtk::Stock::SAVE,
                               sigc::bind (sigc::mem_fun (*this,
                                           &MainWindowClass::toolbar_cb),
                                     "Save Item"),
                               "Save Item"));
    toolbar->tools ().push_back (Space ());
    toolbar->tools ()
        .push_back (StockElem (Gtk::Stock::UNDO,
                               sigc::bind (sigc::mem_fun (*this,
                                           &MainWindowClass::toolbar_cb),
                                     "Undo action"),
                               "Undo action"));
    toolbar->tools ()
        .push_back (StockElem (Gtk::Stock::REDO,
                               sigc::bind (sigc::mem_fun (*this, 
                                           &MainWindowClass::toolbar_cb),
                                     "Redo action"),
                               "Redo action"));


    Gtk::Menu* menu = manage (new Gtk::Menu ());
    optionmenu->set_menu (*menu);

    menu->items ()
        .push_back (MenuElem ("Icons",
                              sigc::bind (sigc::mem_fun (*this, 
                                          &MainWindowClass::toolbar_item_cb),
                                    toolbar,
                                    Gtk::TOOLBAR_ICONS)));
    menu->items ()
        .push_back (MenuElem ("Text",
                              sigc::bind (sigc::mem_fun (*this, 
                                          &MainWindowClass::toolbar_item_cb),
                                    toolbar,
                                    Gtk::TOOLBAR_TEXT)));
    menu->items ()
        .push_back (MenuElem ("Both",
                              sigc::bind (sigc::mem_fun (*this, 
                                          &MainWindowClass::toolbar_item_cb),
                                    toolbar,
                                    Gtk::TOOLBAR_BOTH)));
    menu->items ()
        .push_back (MenuElem ("Both (horiz)",
                              sigc::bind (sigc::mem_fun (*this, 
                                          &MainWindowClass::toolbar_item_cb),
                                    toolbar,
                                    Gtk::TOOLBAR_BOTH_HORIZ)));
    
    menu->items ()[0].activate ();
    optionmenu->set_history (0);

    vbox->show_all ();
}

MainWindowClass::~MainWindowClass ()
{}

void MainWindowClass::quit_pressed_cb ()
{
    hide ();
}

int main (gint argc, gchar **argv)
{
    Gtk::Main kit(argc, argv);
    MainWindowClass main_window;
  
    Gtk::Main::run(main_window);

    return (0);
}
