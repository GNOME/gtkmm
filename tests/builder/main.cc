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
    "<property name='hide_on_close'>True</property>"
    "<child>"
      "<object class='GtkBox' id='vbox'>"
        "<property name='can_focus'>False</property>"
        "<property name='orientation'>vertical</property>"
        "<child>"
          "<object class='gtkmm__CustomObject_DerivedButton' id='derived_button'>"
            "<property name='label' translatable='yes'>DerivedButton</property>"
            "<property name='can_focus'>True</property>"
            "<property name='receives_default'>True</property>"
            "<property name='background'>#008080</property>"
          "</object>"
        "</child>"
        "<child>"
          "<object class='GtkButton' id='standard_button'>"
            "<property name='label' translatable='yes'>Gtk::Button</property>"
            "<property name='can_focus'>True</property>"
            "<property name='receives_default'>True</property>"
          "</object>"
        "</child>"
      "</object>"
    "</child>"
  "</object>"
  "<object class='GtkButton' id='orphaned_button'>"
    "<property name='label' translatable='yes'>Gtk::Button</property>"
    "<property name='can_focus'>True</property>"
    "<property name='receives_default'>True</property>"
  "</object>"
  "<object class='GtkAdjustment' id='adjustment'>"
    "<property name='lower'>0</property>"
    "<property name='upper'>100</property>"
    "<property name='value'>50</property>"
    "<property name='step-increment'>1</property>"
    "<property name='page-increment'>10</property>"
  "</object>"
"</interface>";

void on_managed_button_deleted(sigc::notifiable* /* data */)
{
  std::cout << "Gtk::Button in window deleted" << std::endl;
}

void on_orphaned_button_deleted(sigc::notifiable* /* data */)
{
  std::cout << "Orphaned Gtk::Button deleted" << std::endl;
}

void on_adjustment_deleted(sigc::notifiable* /* data */)
{
  std::cout << "Gtk::Adjustment deleted" << std::endl;
}

class BackgroundArea : public Gtk::DrawingArea
{
public:
  BackgroundArea()
  {
    set_draw_func(sigc::mem_fun(*this, &BackgroundArea::on_draw));
    set_size_request(-1, 30);
    set_hexpand(true);
  }
  virtual ~BackgroundArea() {}

  bool set_color(const Glib::ustring& spec)
  {
    bool success = m_color.set(spec);
    if (success)
      queue_draw();
    return success;
  }

protected:
  void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int /* width */, int /* height */)
  {
    // Fill The drawing area with the selected color.
    Gdk::Cairo::set_source_rgba(cr, m_color);
    cr->paint();
  }

  Gdk::RGBA m_color{1.0, 1.0, 1.0};

}; // BackgroundArea

class DerivedButton : public Gtk::Button
{
public:
  static void ensure_type()
  {
    std::cout << "DerivedButton::ensure_type()" << std::endl;
    static_cast<void>(DerivedButton());
  }

  DerivedButton(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& /* refBuilder */,
                const Glib::ustring& icon_name = {})
  : Glib::ObjectBase(s_type_name)
  , Gtk::Button(cobject)
  , m_backgroundArea()
  {
    std::cout << "DerivedButton::ctor" << std::endl;

    apply_background();
    property_background().signal_changed().connect(
      sigc::mem_fun(*this, &DerivedButton::apply_background));

    if (icon_name.empty())
      set_child(m_backgroundArea);
    else
    {
      auto box = Gtk::make_managed<Gtk::Box>();
      set_child(*box);
      auto icon = Gtk::make_managed<Gtk::Image>();
      icon->set_from_icon_name(icon_name);
      box->append(*icon);
      box->append(m_backgroundArea);
    }
  }

  auto property_background() const -> Glib::PropertyProxy_ReadOnly<Glib::ustring> { return m_property_background.get_proxy(); }
  auto property_background()       -> Glib::PropertyProxy         <Glib::ustring> { return m_property_background.get_proxy(); }
  auto get_background() const -> Glib::ustring { return m_property_background.get_value(); }
  void set_background(const Glib::ustring& background){ m_property_background.set_value(background); }

  virtual ~DerivedButton()
  {
    std::cout << "DerivedButton::dtor" << std::endl;
  }

private:
  static constexpr auto s_type_name = "DerivedButton";
  Glib::Property<Glib::ustring> m_property_background{*this, "background"};

  BackgroundArea m_backgroundArea;

  DerivedButton()
  : Glib::ObjectBase(s_type_name)
  {
    std::cout << "DerivedButton::ctor to register type" << std::endl;
  }

  void apply_background()
  {
    const auto background = get_background();
    std::cout << "apply_background(\"" << background << "\")" << std::endl;

    if (!m_backgroundArea.set_color(background))
      std::cout << "invalid background color, but I let you keep typing!" << std::endl;
  }
}; // DerivedButton

class MainWindow : public Gtk::Window
{
public:
  MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
  : Gtk::Window(cobject)
  , m_pDerivedButton(Gtk::Builder::get_widget_derived<DerivedButton>(refBuilder, "derived_button", "face-smile"))
  , m_pStandardButton(refBuilder->get_widget<Gtk::Button>("standard_button"))
  {
    std::cout << "MainWindow::ctor" << std::endl;

    // Called twice just to see if two calls affect the ref count.
    m_pDerivedButton = Gtk::Builder::get_widget_derived<DerivedButton>(refBuilder, "derived_button");
    m_pStandardButton = refBuilder->get_widget<Gtk::Button>("standard_button");

    m_pStandardButton->add_destroy_notify_callback(nullptr, on_managed_button_deleted);
  }

  // A default signal handler in Gtk::Window shall be called if the
  // class name in the UI file is GtkWindow, although the real GType name
  // is gtkmm__GtkWindow. https://gitlab.gnome.org/GNOME/gtkmm/-/issues/61
  bool on_close_request() override
  {
    std::cout << "MainWindow::on_close_request()" << std::endl;
    return Gtk::Window::on_close_request(); // Call the base class
  }

  virtual ~MainWindow()
  {
    std::cout << "MainWindow::dtor" << std::endl;
  }

  const DerivedButton* get_derived_button() const { return m_pDerivedButton; }
  const Gtk::Button* get_standard_button() const { return m_pStandardButton; }

private:
  DerivedButton* m_pDerivedButton = nullptr;
  Gtk::Button* m_pStandardButton = nullptr;

}; // MainWindow

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

  auto app = Gtk::Application::create();
  g_assert_nonnull(app);
  app->register_application();

  DerivedButton::ensure_type();
  auto builder = Gtk::Builder::create_from_string(gladefile);
  g_assert_nonnull(builder);

  auto main_win = Gtk::Builder::get_widget_derived<MainWindow>(builder, "main_window");
  g_assert_nonnull(main_win);

  auto orph_button = builder->get_widget<Gtk::Button>("orphaned_button");
  g_assert_nonnull(orph_button);
  orph_button->add_destroy_notify_callback(nullptr, on_orphaned_button_deleted);

  auto adjustment = builder->get_object<Gtk::Adjustment>("adjustment");
  g_assert_nonnull(adjustment);
  builder->get_object("adjustment"); // Test get same again/no-template overload
  g_assert_nonnull(adjustment);
  g_assert_cmpfloat(adjustment->get_value(), ==, 50);
  adjustment->add_destroy_notify_callback(nullptr, on_adjustment_deleted);

  const GObject* const window = (GObject*)main_win->gobj();
  const GObject* const orphaned_button = (GObject*)orph_button->gobj();
  const GObject* const derived_button = (GObject*)main_win->get_derived_button()->gobj();
  const GObject* const standard_button = (GObject*)main_win->get_standard_button()->gobj();
  const GObject* const adjustment_gobj = (GObject*)adjustment->gobj();

  std::cout << "Before app->run(argc1, argv)" << std::endl
    << "  ref_count(MainWindow)=" << window->ref_count << std::endl
    << "  ref_count(DerivedButton)=" << derived_button->ref_count << std::endl
    << "  ref_count(Gtk::Button)=" << standard_button->ref_count << std::endl
    << "  ref_count(orphaned_button)=" << orphaned_button->ref_count << std::endl
    << "  ref_count(adjustment)=" << adjustment_gobj->ref_count << std::endl;

  // This is approximately what Gtk::Application::make_window_and_run() would do.
  app->signal_activate().connect([&app, main_win] ()
  {
    app->add_window(*main_win);
    main_win->set_visible(true);
  });
  main_win->signal_hide().connect([&] ()
  {
    delete main_win;

    std::cout << "After delete main_win" << std::endl
      << "  ref_count(MainWindow)=" << window->ref_count << std::endl
      << "  ref_count(DerivedButton)=" << derived_button->ref_count << std::endl
      << "  ref_count(Gtk::Button)=" << standard_button->ref_count << std::endl
      << "  ref_count(orphaned_button)=" << orphaned_button->ref_count << std::endl
      << "  ref_count(adjustment)=" << adjustment_gobj->ref_count << std::endl;

    builder.reset();

    std::cout << "After builder.reset()" << std::endl;
    if (print_after_deletion)
    {
      // If Builder is correct, this code will access deallocated memory.
      std::cout
        << "  ref_count(MainWindow)=" << window->ref_count << std::endl
        << "  ref_count(DerivedButton)=" << derived_button->ref_count << std::endl
        << "  ref_count(Gtk::Button)=" << standard_button->ref_count << std::endl
        << "  ref_count(orphaned_button)=" << orphaned_button->ref_count << std::endl
        << "  ref_count(adjustment)=" << adjustment_gobj->ref_count << std::endl;
    }
  });

  const int result = app->run(argc1, argv);

  std::cout << "After app->run(argc1, argv)" << std::endl;
  if (print_after_deletion)
  {
    // If Builder is correct, this code will access deallocated memory.
    std::cout
      << "  ref_count(MainWindow)=" << window->ref_count << std::endl
      << "  ref_count(DerivedButton)=" << derived_button->ref_count << std::endl
      << "  ref_count(Gtk::Button)=" << standard_button->ref_count << std::endl
      << "  ref_count(orphaned_button)=" << orphaned_button->ref_count << std::endl
      << "  ref_count(adjustment)=" << adjustment_gobj->ref_count << std::endl;
  }

  return result;
}
