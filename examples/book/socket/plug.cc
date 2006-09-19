#include <iostream>
#include <fstream>
#include <gtkmm.h>
#include <gtkmm/plug.h>
#include <glib/gstdio.h>

using namespace std;

const char* id_filename = "plug.id";

void on_embed()
{
    cout << "I've been embedded." << endl;
}


class MyPlug : public Gtk::Plug
{
    public:
        MyPlug() :
            m_label("I am the plug")
        {
            set_size_request(150, 100);
            add(m_label);
            signal_embedded().connect(sigc::ptr_fun(on_embed));
            show_all();
        }

    private:
        Gtk::Label m_label;
};


int main(int argc, char** argv)
{
    Gtk::Main app(argc, argv);
    MyPlug plug;

    ofstream out(id_filename);
    out << plug.get_id();
    out.close();
    cout << "The window ID is: " << plug.get_id() << endl;

    app.run(plug);

    // remove the ID file when the program exits
    g_remove(id_filename);
    return 0;
}
