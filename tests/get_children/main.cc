#include <gtkmm.h>
#include <cassert>

static void on_activate()
{
  Gtk::Box box;
  const auto& cbox = box;

  assert( box.get_children().empty());
  assert(cbox.get_children().empty());

  Gtk::Label labels[3];
  for (auto& label: labels)
    box.append(label);

  assert(( box.get_children() == std::vector      <Gtk::Widget*>{&labels[0], &labels[1], &labels[2]}));
  assert((cbox.get_children() == std::vector<const Gtk::Widget*>{&labels[0], &labels[1], &labels[2]}));

  for (auto const child: box.get_children())
    box.remove(*child);

  assert( box.get_children().empty());
  assert(cbox.get_children().empty());

}

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create();
  app->signal_activate().connect(&on_activate);
  return app->run(argc, argv);
}
