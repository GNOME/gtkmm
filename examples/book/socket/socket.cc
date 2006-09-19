#include <iostream>
#include <fstream>
#include <gtkmm.h>
#include <gtkmm/socket.h>

using namespace std;

const char* id_filename = "plug.id";

void plug_added()
{
    cout << "A plug was added" << endl;
}

bool plug_removed()
{
    cout << "A Plug was removed" << endl;
    return true;
}

class MySocketWindow : public Gtk::Window
{
    public:
        MySocketWindow()
        {
            ifstream infile(id_filename);
            if (infile)
            {
                Gtk::Socket* socket = Gtk::manage(new Gtk::Socket());
                add(*socket);
                socket->signal_plug_added().connect(sigc::ptr_fun(plug_added));
                socket->signal_plug_removed().connect(sigc::ptr_fun(plug_removed));
                Gdk::NativeWindow plug_id;
                infile >> plug_id;
                infile.close();
                socket->add_id(plug_id);
            }
            else
            {
                Gtk::Label* label = Gtk::manage(
                        new Gtk::Label("Plug id file not found.\n Make sure plug is running."));
                add(*label);
                set_size_request(150, 50);
            }
            show_all();
        }
};

int main(int argc, char** argv)
{
    Gtk::Main app(argc, argv);
    MySocketWindow win;
    app.run(win);
    return 0;
}
