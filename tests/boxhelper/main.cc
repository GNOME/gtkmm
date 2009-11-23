#include <gtkmm.h>
#include <iostream>

int main (int argc, char** argv)
{
  Gtk::Main main(argc, argv);
  Gtk::HBox* box = new Gtk::HBox();
  Gtk::Label* label1 = new Gtk::Label("1");
  Gtk::Label* label2 = new Gtk::Label("2");
  Gtk::Label* label3 = new Gtk::Label("3");
  Gtk::Window* window = new Gtk::Window();
  
  window->set_title("Box Test");
  window->add(*box);
  
  Gtk::Box_Helpers::BoxList list = box->children();
  list.push_back (Gtk::Box_Helpers::Element(*label1));
  list.push_back (*label3);
  Gtk::Box_Helpers::BoxList::iterator inserted = list.insert (++list.begin(), *label2);
  
  if ((label2 = dynamic_cast<Gtk::Label*>(inserted->get_widget())))
    std::cout << "inserted label: " << label2->get_label() << std::endl;

  window->show_all();  
  main.run(*window);

  
  return 0;
}