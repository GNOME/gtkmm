/* Open GL Area
 *
 * Blah
 *
 */

#include <iostream>

#include <vector>

#include <gtkmm.h>

using std::vector;
using std::cout;
using std::endl;

enum {
    X_AXIS,
    Y_AXIS,
    Z_AXIS,

    N_AXIS
};

class Example_GLArea : public Gtk::Window
{
public:
    Example_GLArea();
    virtual ~Example_GLArea();

    //    void on_axis_value_change( Gtk::Adjustment & adj );
    void on_axis_value_change();
    void realize();
    void unrealize();
    void create_context( GdkGLContext * context );
    bool render( GdkGLContext * context );
    void resize( int width, int height );

protected:
    Gtk::Box m_VBox;
    Gtk::GLArea m_GLArea;
    Gtk::Box m_Controls;
    Gtk::Button m_Button;

    Gtk::Box * create_axis_slider_box( int axis );
};

Gtk::Window* do_glarea()
{
    return new Example_GLArea();
}

Example_GLArea::Example_GLArea() :
    m_VBox(Gtk::ORIENTATION_VERTICAL, 8),
    m_GLArea(),
    m_Controls(Gtk::ORIENTATION_VERTICAL, false ),
    m_Button("Quit")
{
    set_title("GL Area");
    set_default_size( 400, 600 );
    set_border_width(8);
    //Connect destroy signal

    m_VBox.set_border_width(12);
    add(m_VBox);

    m_GLArea.set_hexpand( true );
    m_GLArea.set_vexpand( true );
    m_GLArea.set_auto_render( true );
    m_VBox.add( m_GLArea );

    // Connect gl area signals
    m_GLArea.signal_realize().connect( sigc::mem_fun( this, &Example_GLArea::realize ) );
    m_GLArea.signal_unrealize().connect( sigc::mem_fun( this, &Example_GLArea::unrealize ) );
    m_GLArea.signal_render().connect( sigc::mem_fun( this, &Example_GLArea::render ) );
    m_GLArea.signal_resize().connect( sigc::mem_fun( this, &Example_GLArea::resize ) );

    m_VBox.add( m_Controls );
    m_Controls.set_hexpand( true );

    for( int i = 0 ; i < N_AXIS ; ++i )
    {
        Gtk::Box * sliderBox = create_axis_slider_box(i);
        m_Controls.add( *sliderBox );
    }

    m_Button.set_hexpand(true);
    m_VBox.add(m_Button);
    // Connect clicked to destroy of window
    m_Button.signal_clicked().connect( sigc::mem_fun(this, &Gtk::Window::close ) );

    show_all();
}

Example_GLArea::~Example_GLArea()
{
}

//void Example_GLArea::on_axis_value_change( Gtk::Adjustment & adj )
void Example_GLArea::on_axis_value_change()
{
    cout << "Received axis change signal" << endl;
}

void Example_GLArea::realize()
{
    cout << "Realize called" << endl;
    m_GLArea.make_current();
    if( m_GLArea.get_error() != NULL )
    {
        return;
    }
    // init buffers
    // init shaders
}

void Example_GLArea::unrealize()
{
    cout << "Unrealize called" << endl;
    m_GLArea.make_current();
    if( m_GLArea.get_error() != NULL )
    {
        return;
    }
    // Delete buffers and program
}

void Example_GLArea::create_context( GdkGLContext * context )
{
    cout << "Received create_context signal" << endl;
}

void Example_GLArea::resize( int width, int height )
{
    cout << "Resized to " << width << " " << height << endl;
}

bool Example_GLArea::render( GdkGLContext * context )
{
    return true;
}

Gtk::Box * Example_GLArea::create_axis_slider_box( int axis )
{
    Gtk::Box * box = Gtk::manage(new Gtk::Box( Gtk::ORIENTATION_HORIZONTAL, false ) );

    const char * text;

    switch( axis )
    {
    case X_AXIS:
        {
            text = "X axis";
            break;
        }
    case Y_AXIS:
        {
            text = "Y axis";
            break;
        }
    case Z_AXIS:
        {
            text = "Z axis";
            break;
        }
    default:
        {
            g_assert_not_reached();
        }
        
    }

    Gtk::Label * label = Gtk::manage( new Gtk::Label( text ) );
    box->add( *label );
    label->show();

    Glib::RefPtr<Gtk::Adjustment> adj = Gtk::Adjustment::create( 0.0, 0.0, 360.0, 1.0, 12.0, 0.0 );

    adj->signal_value_changed().connect( sigc::mem_fun(this, &Example_GLArea::on_axis_value_change) );

    Gtk::Scale * slider = Gtk::manage( new Gtk::Scale( adj, Gtk::ORIENTATION_HORIZONTAL ) );
    box->add( *slider );
    slider->set_hexpand( true );
    slider->show();

    box->show();

    return box;
}
