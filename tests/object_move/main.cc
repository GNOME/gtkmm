#include <gtkmm.h>
#include <gtkmm/init.h>
#include <gtk/gtk.h>
#include <iostream>
#include <stdlib.h>

class Derived : public Gtk::Object
{
public:
  Derived(GObject* gobject, int i)
  : Gtk::Object(gobject),
    i_(i)
  {
  }

  Derived(const Derived& src) = delete;
  Derived& operator=(const Derived& src) = delete;

  Derived(Derived&& src) noexcept
  : Gtk::Object(std::move(src)),
    i_(std::move(src.i_))
  {}

  Derived& operator=(Derived&& src) noexcept
  {
    Gtk::Object::operator=(std::move(src));
    i_ = std::move(src.i_);

    return *this;
  }

  int i_;
};

static
void test_object_move_constructor()
{
  GObject* button = G_OBJECT(gtk_button_new());
  Derived derived(button, 5);
  std::cout << "debug: gobj(): " << derived.gobj() << std::endl;
  g_assert(derived.gobj() == button);

  Derived derived2(std::move(derived));
  g_assert_cmpint(derived2.i_, ==, 5);
  std::cout << "debug: gobj(): " << derived2.gobj() << std::endl;
  g_assert(derived2.gobj() == button);
  g_assert(derived.gobj() == nullptr);
}

static
void test_object_move_assignment_operator()
{
  GObject* button = G_OBJECT(gtk_button_new());
  Derived derived(button, 5);
  //std::cout << "debug: gobj(): " << derived.gobj() << std::endl;
  g_assert(derived.gobj() == button);

  GObject* button2 = G_OBJECT(gtk_button_new());
  Derived derived2(button2, 6);
  derived2 = std::move(derived);
  g_assert_cmpint(derived2.i_, ==, 5);
  //std::cout << "debug: gobj(): " << derived2.gobj() << std::endl;
  g_assert(derived2.gobj() == button);
  g_assert(derived.gobj() == nullptr);
}

int main(int /* argc */, char** /* argv */)
{
  gtk_init();
  Gtk::init_gtkmm_internals();

  test_object_move_constructor();
  test_object_move_assignment_operator();

  return EXIT_SUCCESS;
}
