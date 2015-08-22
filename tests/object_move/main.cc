#include <gtkmm.h>
#include <gtk/gtk.h>
#include <iostream>
#include <stdlib.h>

class Derived : public Glib::Object
{
public:
  //A real application would never make the constructor public.
  //It would instead have a protectd constructor and a public create() method.
  Derived(GObject* gobject, int i)
  : Glib::Object(gobject),
    i_(i)
  {
  }

  Derived(const Derived& src) = delete;
  Derived& operator=(const Derived& src) = delete;

  Derived(Derived&& src) noexcept
  : Glib::Object(std::move(src)),
    i_(std::move(src.i_))
  {}

  Derived& operator=(Derived&& src) noexcept
  {
    Glib::Object::operator=(std::move(src));
    i_ = std::move(src.i_);

    return *this;
  }

  int i_;
};

static
void test_object_move_constructor()
{
  GObject *button = G_OBJECT(gtk_button_new());
  Derived derived(button, 5);
  std::cout << "debug: gobj(): " << derived.gobj() << std::endl;
  g_assert(derived.gobj() == button);
  Derived derived2 = std::move(derived);
  g_assert_cmpint(derived2.i_, ==, 5);
  std::cout << "debug: gobj(): " << derived2.gobj() << std::endl;
  g_assert(derived2.gobj() == button);
}

int main(int argc, char** argv)
{
  gtk_init(&argc, &argv);
  Gtk::Main::init_gtkmm_internals();

  test_object_move_constructor();

  return EXIT_SUCCESS;
}
