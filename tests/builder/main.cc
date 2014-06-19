/* Copyright (C) 2014 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

// This test case is a result of https://bugzilla.gnome.org/show_bug.cgi?id=731444
// Bug 731444 - gtkmm::builder - derived widget's destructor is not called -> memory leaks

#include <iostream>
#include <cstring>
#include <gtkmm.h>

namespace
{

const char gladefile[] =
"<?xml version='1.0' encoding='UTF-8'?>"
"<!-- Generated with glade 3.16.1 -->"
"<interface>"
  "<requires lib='gtk+' version='3.10'/>"
  "<object class='GtkWindow' id='main_window'>"
    "<property name='can_focus'>False</property>"
    "<property name='title' translatable='yes'>Gtk::Builder ref count</property>"
    "<property name='default_width'>440</property>"
    "<property name='default_height'>150</property>"
    "<child>"
      "<object class='GtkBox' id='vbox'>"
        "<property name='visible'>True</property>"
        "<property name='can_focus'>False</property>"
        "<property name='orientation'>vertical</property>"
        "<child>"
          "<object class='GtkButton' id='derived_button'>"
            "<property name='label' translatable='yes'>DerivedButton</property>"
            "<property name='visible'>True</property>"
            "<property name='can_focus'>True</property>"
            "<property name='receives_default'>True</property>"
          "</object>"
          "<packing>"
            "<property name='expand'>False</property>"
            "<property name='fill'>True</property>"
            "<property name='position'>0</property>"
          "</packing>"
        "</child>"
        "<child>"
          "<object class='GtkButton' id='standard_button'>"
            "<property name='label' translatable='yes'>Gtk::Button</property>"
            "<property name='visible'>True</property>"
            "<property name='can_focus'>True</property>"
            "<property name='receives_default'>True</property>"
          "</object>"
          "<packing>"
            "<property name='expand'>False</property>"
            "<property name='fill'>True</property>"
            "<property name='position'>1</property>"
          "</packing>"
        "</child>"
      "</object>"
    "</child>"
  "</object>"
  "<object class='GtkButton' id='orphaned_button'>"
    "<property name='label' translatable='yes'>Gtk::Button</property>"
    "<property name='visible'>True</property>"
    "<property name='can_focus'>True</property>"
    "<property name='receives_default'>True</property>"
  "</object>"
"</interface>";

void* on_managed_button_deleted(void* /* data */)
{
  std::cout << "Gtk::Button in window deleted" << std::endl;
  return 0;
}

void* on_orphaned_button_deleted(void* /* data */)
{
  std::cout << "Orphaned Gtk::Button deleted" << std::endl;
  return 0;
}

class DerivedButton : public Gtk::Button
{
public:
  DerivedButton(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& /* refBuilder */)
  : Gtk::Button(cobject)
  {
    std::cout << "DerivedButton::ctor" << std::endl;
  }

  virtual ~DerivedButton()
  {
    std::cout << "DerivedButton::dtor" << std::endl;
  }
};

class MainWindow : public Gtk::Window
{
public:
  MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
  : Gtk::Window(cobject), m_pDerivedButton(0), m_pStandardButton(0)
  {
    std::cout << "MainWindow::ctor" << std::endl;

    // Called twice just to see if two calls affect the ref count.
    refBuilder->get_widget_derived("derived_button", m_pDerivedButton);
    refBuilder->get_widget_derived("derived_button", m_pDerivedButton);
    refBuilder->get_widget("standard_button", m_pStandardButton);
    refBuilder->get_widget("standard_button", m_pStandardButton);

    m_pStandardButton->add_destroy_notify_callback(0, on_managed_button_deleted);
  }

  virtual ~MainWindow()
  {
    std::cout << "MainWindow::dtor" << std::endl;
  }

  const DerivedButton* get_derived_button() const { return m_pDerivedButton; }
  const Gtk::Button* get_standard_button() const { return m_pStandardButton; }

private:
  DerivedButton* m_pDerivedButton;
  Gtk::Button* m_pStandardButton;
};

} // end of anonymous namespace

int main(int argc, char* argv[])
{
  // With the command-line parameter --p-a-d, ref counts are printed
  // after the widgets have been deleted. This means accesses to deallocated
  // memory, possibly with bad side effects.
  bool print_after_deletion = false;
  int argc1 = argc;
  if (argc > 1 && std::strcmp(argv[1], "--p-a-d") == 0)
  {
    print_after_deletion = true;
    argc1 = 1; // Don't give the command line arguments to Gtk::Application.
  }

  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc1, argv);

  Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_string(gladefile);

  MainWindow* main_win = 0;
  builder->get_widget_derived("main_window", main_win);

  Gtk::Button* orph_button = 0;
  builder->get_widget("orphaned_button", orph_button);
  orph_button->add_destroy_notify_callback(0, on_orphaned_button_deleted);

  const GObject* const window = (GObject*)main_win->gobj();
  const GObject* const orphaned_button = (GObject*)orph_button->gobj();
  const GObject* const derived_button = (GObject*)main_win->get_derived_button()->gobj();
  const GObject* const standard_button = (GObject*)main_win->get_standard_button()->gobj();

  std::cout << "Before app->run(*main_win)" << std::endl
    << "  ref_count(MainWindow)=" << window->ref_count << std::endl
    << "  ref_count(DerivedButton)=" << derived_button->ref_count << std::endl
    << "  ref_count(Gtk::Button)=" << standard_button->ref_count << std::endl
    << "  ref_count(orphaned_button)=" << orphaned_button->ref_count << std::endl;

  const int result = app->run(*main_win);
 
  std::cout << "After app->run(*main_win)" << std::endl
    << "  ref_count(MainWindow)=" << window->ref_count << std::endl
    << "  ref_count(DerivedButton)=" << derived_button->ref_count << std::endl
    << "  ref_count(Gtk::Button)=" << standard_button->ref_count << std::endl
    << "  ref_count(orphaned_button)=" << orphaned_button->ref_count << std::endl;

  delete main_win;

  std::cout << "After delete main_win" << std::endl
    << "  ref_count(MainWindow)=" << window->ref_count << std::endl
    << "  ref_count(DerivedButton)=" << derived_button->ref_count << std::endl
    << "  ref_count(Gtk::Button)=" << standard_button->ref_count << std::endl
    << "  ref_count(orphaned_button)=" << orphaned_button->ref_count << std::endl;

  builder.reset();

  if (print_after_deletion)
  {
    // If Builder is correct, this code will access deallocated memory.
    std::cout << "After builder.reset()" << std::endl
      << "  ref_count(MainWindow)=" << window->ref_count << std::endl
      << "  ref_count(DerivedButton)=" << derived_button->ref_count << std::endl
      << "  ref_count(Gtk::Button)=" << standard_button->ref_count << std::endl
      << "  ref_count(orphaned_button)=" << orphaned_button->ref_count << std::endl;
  }

  return result;
}
