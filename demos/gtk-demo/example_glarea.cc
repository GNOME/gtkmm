/* Open GL Area
 *
 * GLArea is a widget that allows custom drawing using OpenGL calls.
 *
 */

#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>

#include <gtkmm.h>

#include <epoxy/gl.h>

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::stringstream;

enum {
    X_AXIS,
    Y_AXIS,
    Z_AXIS,

    N_AXIS
};

static const GLfloat vertex_data[] = {
  0.f,   0.5f,   0.f, 1.f,
  0.5f, -0.366f, 0.f, 1.f,
 -0.5f, -0.366f, 0.f, 1.f,
};

class Example_GLArea : public Gtk::Window
{
public:
    Example_GLArea();
    virtual ~Example_GLArea();

    void on_axis_value_change( int axis, Glib::RefPtr<Gtk::Adjustment> adj );
    void realize();
    void unrealize();

    bool render( const Glib::RefPtr<Gdk::GLContext> & context );

protected:
    Gtk::Box m_VBox;
    Gtk::GLArea m_GLArea;
    Gtk::Box m_Controls;
    Gtk::Button m_Button;

    Gtk::Box * create_axis_slider_box( int axis );

    GLuint m_Vao;
    GLuint m_Buffer;
    GLuint m_Program;
    GLuint m_Mvp;

    float m_RotationAngles[N_AXIS];

    void init_buffers();
    void init_shaders();

    void draw_triangle();
};

Gtk::Window* do_glarea()
{
    return new Example_GLArea();
}

Example_GLArea::Example_GLArea() :
    m_VBox(Gtk::ORIENTATION_VERTICAL, false ),
    m_GLArea(),
    m_Controls(Gtk::ORIENTATION_VERTICAL, false ),
    m_Button("Quit")
{
    m_RotationAngles[0] = 0.0f;
    m_RotationAngles[1] = 0.0f;
    m_RotationAngles[2] = 0.0f;

    set_title("GL Area");
    set_default_size( 400, 600 );
    set_border_width(12);

    m_VBox.set_spacing( 6 );
    add(m_VBox);

    m_GLArea.set_hexpand( true );
    m_GLArea.set_vexpand( true );
    m_GLArea.set_auto_render( true );
    m_VBox.add( m_GLArea );

    // Connect gl area signals
    m_GLArea.signal_realize().connect( sigc::mem_fun( this, &Example_GLArea::realize ) );
    m_GLArea.signal_unrealize().connect( sigc::mem_fun( this, &Example_GLArea::unrealize ) );
    m_GLArea.signal_render().connect( sigc::mem_fun( this, &Example_GLArea::render ) );

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

void Example_GLArea::on_axis_value_change( int axis, Glib::RefPtr<Gtk::Adjustment> adj )
{
    m_RotationAngles[axis] = adj->get_value();

    m_GLArea.queue_draw();
}

void Example_GLArea::realize()
{
    m_GLArea.make_current();
    if( m_GLArea.get_error() != NULL )
    {
        cout << "Got an error making the context current" << endl;
        return;
    }

    init_buffers();
    init_shaders();
}

void Example_GLArea::unrealize()
{
    m_GLArea.make_current();
    if( m_GLArea.get_error() != NULL )
    {
        cout << "Error after make_current in unrealize" << endl;
        return;
    }

    // Delete buffers and program
    glDeleteBuffers( 1, &m_Vao );
    glDeleteProgram( m_Program );
}

bool Example_GLArea::render( const Glib::RefPtr<Gdk::GLContext> & context )
{
    GError * error = m_GLArea.get_error();
    if( error != NULL )
    {
        cout << "An error on the gl area occurred" << endl;
        return false;
    }

    glClearColor( 0.5, 0.5, 0.5, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT );

    draw_triangle();

    glFlush();

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

    adj->signal_value_changed().connect(
         sigc::bind( sigc::mem_fun(this, &Example_GLArea::on_axis_value_change), axis, adj )
                                        );
    Gtk::Scale * slider = Gtk::manage( new Gtk::Scale( adj, Gtk::ORIENTATION_HORIZONTAL ) );
    box->add( *slider );
    slider->set_hexpand( true );
    slider->show();

    box->show();

    return box;
}

void Example_GLArea::init_buffers()
{
    glGenVertexArrays( 1, &m_Vao );
    glBindVertexArray( m_Vao );

    glGenBuffers( 1, &m_Buffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_Buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

static GLuint create_shader( int type, const char *src )
{
  GLuint shader;
  int status;

  shader = glCreateShader( type );
  glShaderSource( shader, 1, &src, NULL );
  glCompileShader( shader );

  glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
  if( status == GL_FALSE )
  {
      int log_len;
      char *buffer;

      glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &log_len );

      buffer = (char *)g_malloc( log_len + 1 );
      glGetShaderInfoLog( shader, log_len, NULL, buffer );

      g_warning( "Compile failure in %s shader:\n%s\n",
                 type == GL_VERTEX_SHADER ? "vertex" : "fragment",
                 buffer );

      g_free( buffer );

      glDeleteShader( shader );

      return 0;
  }

  return shader;
}

static string read_shader_file( const char * filename )
{
    stringstream ss( stringstream::out );

    ifstream ifs;

    ifs.open( filename, ifstream::in );
    if( ifs.fail() )
    {
    }
    else
    {
        string temp;

        while( getline( ifs, temp ) )
        {
            ss << temp << endl;
        }
    }
    return ss.str();
}

void Example_GLArea::init_shaders()
{
  GLuint vertex, fragment;
  int status;

  string vertex_shader = read_shader_file( "glarea-vertex.glsl" );
  vertex = create_shader( GL_VERTEX_SHADER, vertex_shader.c_str() );

  if( vertex == 0 )
  {
      m_Program = 0;
      return;
  }

  string fragment_shader = read_shader_file( "glarea-fragment.glsl" );
  fragment = create_shader( GL_FRAGMENT_SHADER, fragment_shader.c_str() );

  if( fragment == 0 )
  {
      glDeleteShader(vertex);
      m_Program = 0;
      return;
  }

  m_Program = glCreateProgram();
  glAttachShader( m_Program, vertex );
  glAttachShader( m_Program, fragment );

  glLinkProgram( m_Program );

  glGetProgramiv( m_Program, GL_LINK_STATUS, &status );
  if( status == GL_FALSE )
  {
      int log_len;
      char *buffer;

      glGetProgramiv( m_Program, GL_INFO_LOG_LENGTH, &log_len );

      buffer = (char *)g_malloc( log_len + 1 );
      glGetProgramInfoLog( m_Program, log_len, NULL, buffer );

      g_warning( "Linking failure:\n%s\n", buffer );

      g_free( buffer );

      glDeleteProgram( m_Program );
      m_Program = 0;

      goto out;
    }

  /* Get the location of the "mvp" uniform */
  m_Mvp = glGetUniformLocation( m_Program, "mvp" );

  glDetachShader( m_Program, vertex );
  glDetachShader( m_Program, fragment );

out:
  glDeleteShader( vertex );
  glDeleteShader( fragment );
}

static void compute_mvp( float *res,
             float phi,
             float theta,
             float psi )
{
  float x = phi * (G_PI / 180.f);
  float y = theta * (G_PI / 180.f);
  float z = psi * (G_PI / 180.f);
  float c1 = cosf (x), s1 = sinf (x);
  float c2 = cosf (y), s2 = sinf (y);
  float c3 = cosf (z), s3 = sinf (z);
  float c3c2 = c3 * c2;
  float s3c1 = s3 * c1;
  float c3s2s1 = c3 * s2 * s1;
  float s3s1 = s3 * s1;
  float c3s2c1 = c3 * s2 * c1;
  float s3c2 = s3 * c2;
  float c3c1 = c3 * c1;
  float s3s2s1 = s3 * s2 * s1;
  float c3s1 = c3 * s1;
  float s3s2c1 = s3 * s2 * c1;
  float c2s1 = c2 * s1;
  float c2c1 = c2 * c1;

  /* initialize to the identity matrix */
  res[0] = 1.f; res[4] = 0.f;  res[8] = 0.f; res[12] = 0.f;
  res[1] = 0.f; res[5] = 1.f;  res[9] = 0.f; res[13] = 0.f;
  res[2] = 0.f; res[6] = 0.f; res[10] = 1.f; res[14] = 0.f;
  res[3] = 0.f; res[7] = 0.f; res[11] = 0.f; res[15] = 1.f;

  /* apply all three rotations using the three matrices:
   *
   * ⎡  c3 s3 0 ⎤ ⎡ c2  0 -s2 ⎤ ⎡ 1   0  0 ⎤
   * ⎢ -s3 c3 0 ⎥ ⎢  0  1   0 ⎥ ⎢ 0  c1 s1 ⎥
   * ⎣   0  0 1 ⎦ ⎣ s2  0  c2 ⎦ ⎣ 0 -s1 c1 ⎦
   */
  res[0] = c3c2;  res[4] = s3c1 + c3s2s1;  res[8] = s3s1 - c3s2c1; res[12] = 0.f;
  res[1] = -s3c2; res[5] = c3c1 - s3s2s1;  res[9] = c3s1 + s3s2c1; res[13] = 0.f;
  res[2] = s2;    res[6] = -c2s1;         res[10] = c2c1;          res[14] = 0.f;
  res[3] = 0.f;   res[7] = 0.f;           res[11] = 0.f;           res[15] = 1.f;
}

void Example_GLArea::draw_triangle()
{
    float mvp[16];

    compute_mvp( mvp,
                 m_RotationAngles[X_AXIS],
                 m_RotationAngles[Y_AXIS],
                 m_RotationAngles[Z_AXIS] );

    glUseProgram( m_Program );

    glUniformMatrix4fv( m_Mvp, 1, GL_FALSE, &mvp[0] );

    glBindBuffer( GL_ARRAY_BUFFER, m_Vao );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );

    glDrawArrays( GL_TRIANGLES, 0, 3 );

    glDisableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glUseProgram( 0 );
}
