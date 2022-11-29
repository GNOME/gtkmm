#include <gtkmm.h>
#include <iostream>

GQuark quark_test = 0;

void initialize_quark()
{
  if (!quark_test)
  {
    std::cout << "Initializing quark\n";
    quark_test = g_quark_from_static_string("quarktestmurrayc");
  }
}

void on_object_qdata_destroyed(gpointer data)
{
  std::cout << "on_object_qdata_destroyed(): C instance=" << data << "\n";
}

int main(int /* argc */, char** /* argv */)
{
  auto app = Gtk::Application::create();
  app->register_application();

  // pButton points at a widget that was first created by GTK.
  // A C++ wrapper was later added to it.
  auto pScaleButton = new Gtk::ScaleButton(0.0, 1.0, 0.1);
  Gtk::Button* pButton = pScaleButton->get_plus_button();
  Gtk::Button m_Button;
  std::cout << "pButton  GType name: " << G_OBJECT_TYPE_NAME(pButton->gobj()) << "\n";
  std::cout << "m_Button GType name: " << G_OBJECT_TYPE_NAME(m_Button.gobj()) << "\n";

  //Set a quark and a callback:
  initialize_quark();
  int a = 0; // (This doesn't work unless we have a non-null value for the 3rd parameter.)
  g_object_set_qdata_full((GObject*)pButton->gobj(), quark_test, &a, &on_object_qdata_destroyed);

  std::cout << "pButton refcount=" << G_OBJECT(pButton->gobj())->ref_count << "\n";

  delete pScaleButton;

  std::cout << "After delete\n";

  return 0;
}
