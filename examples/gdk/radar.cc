//$Id$ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * This example was originally provided by Alain Roughe <alain.rouge@enac.fr>
*/


#include <gtkmm/drawingarea.h>
#include <gdkmm/colormap.h>
#include <gdkmm/window.h>


#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/statusbar.h>

#include <gtkmm/window.h>
#include <gtkmm/main.h>

#include <cmath>
#include <sstream>

#include <vector>

#include <pangomm/fontdescription.h>

const double DEG2RAD = 3.1415928 / 180.0;
#ifndef M_PI
#define M_PI 3.14159265359
#endif /* M_PI */

// PPI Plan Position Indicator: radar screen
class PPI : public Gtk::DrawingArea
{
public:
  PPI();
  virtual ~PPI();
  bool timer_callback();


protected:
  //Overridden default signal handlers:
  virtual void on_realize();
  virtual bool on_expose_event(GdkEventExpose* event);

  Glib::RefPtr<Gdk::GC> gc_;
  Gdk::Color blue_, red_, green_, black_, white_, grey_, yellow_;

private:
  int loop;
  double alpha;
};


PPI::PPI()
{
  // get_window() would return 0 because the Gdk::Window has not yet been realized
  // So we can only allocate the colors here - the rest will happen in on_realize().
  Glib::RefPtr<Gdk::Colormap> colormap = get_default_colormap();

  blue_ = Gdk::Color("blue");
  red_ = Gdk::Color("red");
  green_ = Gdk::Color("green");

  black_ = Gdk::Color("black");
  white_ = Gdk::Color("white");
  grey_ = Gdk::Color("grey");

  yellow_ = Gdk::Color("yellow");

  colormap->alloc_color(blue_);
  colormap->alloc_color(red_);
  colormap->alloc_color(green_);
  
  colormap->alloc_color(black_);
  colormap->alloc_color(white_);
  colormap->alloc_color(grey_);

  colormap->alloc_color(yellow_);

  // timeout
  Glib::signal_timeout().connect(SigC::slot(*this, &PPI::timer_callback), 50);

  // loop, alpha
  loop = 0;
  alpha = 0.0;

  add_events(Gdk::EXPOSURE_MASK);
}


PPI::~PPI()
{
}


void PPI::on_realize()
{
  // We need to call the base on_realize()
  Gtk::DrawingArea::on_realize();

  // Now we can allocate any additional resources we need
  Glib::RefPtr<Gdk::Window> window = get_window();

  gc_ = Gdk::GC::create(window);

  window->set_background(black_);
  window->clear();

  gc_->set_foreground(green_);
}


bool PPI::on_expose_event(GdkEventExpose*)
{
  // we need a ref to the gdkmm window
  Glib::RefPtr<Gdk::Window> window = get_window();

  // window geometry: x, y, width, height, depth
  int winx, winy, winw, winh, wind;
  window->get_geometry(winx, winy, winw, winh, wind);

  window->clear();

  // 4 white points
  gc_->set_foreground(white_);
  window->draw_point(gc_, 5, 5);
  window->draw_point(gc_, 5, winh-5);
  window->draw_point(gc_, winw-5, winh-5);
  window->draw_point(gc_, winw-5, 5);

  // a thick solid grey line
  gc_->set_foreground(grey_);
  gc_->set_line_attributes(/*line_width*/7, /*LineStyle*/Gdk::LINE_SOLID,/*CapStyle*/Gdk::CAP_NOT_LAST,/*JoinStyle*/Gdk::JOIN_MITER);
  // LineStyle: LINE_SOLID, LINE_ON_OFF_DASH, LINE_DOUBLE_DASH
  // CapStyle: CAP_NOT_LAST, CAP_BUTT, CAP_ROUND, CAP_PROJECTING
  // JoinStyle: JOIN_MITER, JOIN_ROUND, JOIN_BEVEL
  window->draw_line(gc_, 10, 10, winw-10, winh-10);
  
  // a thin dashed grey line
  gc_->set_foreground(grey_);
  gc_->set_line_attributes(/*line_width*/2,
                           /*LineStyle*/Gdk::LINE_ON_OFF_DASH,/*CapStyle*/Gdk::CAP_NOT_LAST,/*JoinStyle*/Gdk::JOIN_MITER); 
  // custom dash  FIXME 
  // gint8 dl[2];
  // dl[0] = 0x00;
  // dl[1] = 0xFF;
  // gint8 *dlp=dl;
  // gc_->set_dashes(/*dash_offset*/0,/*dash_list*/dlp,/*n*/2);

  window->draw_line(gc_, winw-10, 10, 10, winh-10);

  // a red filled rectangle: south target
  gc_->set_foreground(red_);

  if ( (alpha > (85.0*DEG2RAD)) && (alpha < (95.0*DEG2RAD)) ) 
  {
   window->draw_rectangle(gc_, 1, winw/2-10, winh-30, 20, 10);
   Glib::RefPtr<Pango::Layout> alayout = create_pango_layout("TARGET!");
   window->draw_layout(gc_, winw/2-10, winh - 45, alayout);
   }
  
 
  // a green circle
  // draw_arc( gc_, int filled, int x, int y, int width, int height, int angle1, int angle2)
  // x :x coordinate of the left edge of the bounding rectangle 
  // Y :y coordinate of the top edge of the bounding rectangle 
  // width, height: width, height of the bounding rectangle 
  // angle1: start angle of the arc relative to the 3 o'clock position counter-clockwise in 1/64 ths of a degree
  // angle2: end angle of the arc relative to angle1 in 1/64 ths of a degree
  int bounding;
  if (winw>winh) bounding = winh-10; else bounding = winw -10;
  gc_->set_foreground(green_);
  gc_->set_line_attributes(/*line_width*/2, 
                           /*LineStyle*/Gdk::LINE_ON_OFF_DASH,/*CapStyle*/Gdk::CAP_NOT_LAST,/*JoinStyle*/Gdk::JOIN_MITER);  
  window->draw_arc(gc_, 0, winw/2-(bounding/2), winh/2-(bounding/2), bounding, bounding, 0, 360*64);


  // green rotating line  
  double radius;
  int x1, y1, x2, y2;
  radius = winw/2.0;
  if (winw>winh) radius = winh/2.0; else radius = winw/2.0;
  x1 = winw/2;
  y1 = winh/2;
  x2 = x1 + (int) (radius * cos(alpha));
  y2 = y1 + (int) (radius * sin(alpha));
  gc_->set_foreground(green_);
  gc_->set_line_attributes(/*line_width*/2,/*LineStyle*/Gdk::LINE_SOLID,/*CapStyle*/Gdk::CAP_NOT_LAST,/*JoinStyle*/Gdk::JOIN_MITER);  
  window->draw_line(gc_, x1, y1, x2, y2);


  // "RADAR DEMO!" text
   gc_->set_foreground(white_);  
   Glib::ustring us1("RADAR");
   Glib::ustring us2(" DEMO!");
   Glib::ustring us3 = us1 + us2;
   Glib::RefPtr<Pango::Layout> pl1 = create_pango_layout(us3);
   
     // TODO: FontDescription   
     Pango::FontDescription fd;
     fd.set_size(1000);
     pl1->set_font_description(/* const FontDescription& desc */ fd);
     // TODO END

     window->draw_layout(gc_, 0, 0, pl1);

  // "Loop = " text
   gc_->set_foreground(white_);  
   Glib::ustring us4("Loop=");
 
   // 21.5.3 TCPL 3eme ed. 
   std::ostringstream ost;
   ost << loop;
   Glib::ustring us5;
   us5 = ost.str();

   Glib::ustring us6 = us4 + us5;

   Glib::RefPtr<Pango::Layout> pl2 = create_pango_layout(us6);
   window->draw_layout(gc_, winw-75, 0, pl2);

   // a yellow cross
   gc_->set_foreground(yellow_);
   gc_->set_line_attributes(/*line_width*/4,/*LineStyle*/Gdk::LINE_SOLID,/*CapStyle*/Gdk::CAP_NOT_LAST,/*JoinStyle*/Gdk::JOIN_MITER);  
   window->draw_line(gc_, winw/2-10, winh/2, winw/2+10, winh/2);
   window->draw_line(gc_, winw/2, winh/2-10, winw/2, winh/2+10);

   // draw_points 
   gc_->set_foreground(blue_);
      
   std::vector<Gdk::Point> vec1;
   vec1.push_back(Gdk::Point(10,20));
   vec1.push_back(Gdk::Point(10,22));
   vec1.push_back(Gdk::Point(10,24));
   vec1.push_back(Gdk::Point(10,26));
   vec1.push_back(Gdk::Point(10,28));
      
   window->draw_points(gc_, vec1);
   
  // draw_lines : a blue Z 
   gc_->set_foreground(blue_);
   gc_->set_line_attributes(/*line_width*/4,/*LineStyle*/Gdk::LINE_SOLID,/*CapStyle*/Gdk::CAP_NOT_LAST,/*JoinStyle*/Gdk::JOIN_MITER);  
          
   std::vector<Gdk::Point> vec2;
   vec2.push_back(Gdk::Point(10,50));
   vec2.push_back(Gdk::Point(30,50));
   vec2.push_back(Gdk::Point(10,70));
   vec2.push_back(Gdk::Point(50,70));
  
   window->draw_lines(gc_, vec2);

   // draw_segments : a yellow Z
   gc_->set_foreground(yellow_);
   gc_->set_line_attributes(/*line_width*/4,/*LineStyle*/Gdk::LINE_SOLID,/*CapStyle*/Gdk::CAP_NOT_LAST,/*JoinStyle*/Gdk::JOIN_MITER);  
   GdkSegment segs[] = {  {10, 80, 30, 80}, {30, 80, 10, 100}, {10, 100, 50, 100} };
   window->draw_segments(gc_,/*GdkSegment *segs*/segs,/*int nsegs*/G_N_ELEMENTS(segs));

  // draw_polygon : a blue Z 
   gc_->set_foreground(blue_);
   gc_->set_line_attributes(/*line_width*/4,/*LineStyle*/Gdk::LINE_SOLID,/*CapStyle*/Gdk::CAP_NOT_LAST,/*JoinStyle*/Gdk::JOIN_MITER);  

   std::vector<Gdk::Point> vec3;
   vec3.push_back(Gdk::Point(10,110));
   vec3.push_back(Gdk::Point(30,110));
   vec3.push_back(Gdk::Point(10,130));
   vec3.push_back(Gdk::Point(50,130));

   window->draw_polygon(gc_,/*filled*/false, vec3);

   return true;
}


bool PPI::timer_callback()
{
 loop = loop + 1;
 alpha = alpha + 0.020; // 20 milli radians
 alpha = fmod(alpha, 2.0 * M_PI);

 queue_draw();

 // never disconnect timer handler
 return 1;
}


class Radar : public Gtk::Window
{
public:
  Radar();
  virtual ~Radar();
  
protected:
  // Child widgets
  Gtk::VBox m_box0;
  Gtk::HBox m_box1;
  Gtk::VBox m_box2;
  Gtk::HBox m_box3; //empty box

  Gtk::Button m_button1, m_button2;
  Gtk::Statusbar m_sb;

  PPI m_area;
};


Radar::Radar()
  : m_box0(/*homogeneous*/false, /*spacing*/5), m_box1(false, 5), m_box2(false, 5), m_box3(false, 5), 
    m_button1("Dialog"), m_button2("Quit"), 
    m_sb(), 
    m_area()
{

  // box2
  m_button2.signal_clicked().connect(SigC::slot(*this, &Gtk::Widget::hide));
  m_box2.pack_start(m_box3, /*Gtk::PackOptions*/Gtk::PACK_EXPAND_WIDGET, /*padding*/5);
  m_box2.pack_start(m_button1, Gtk::PACK_SHRINK, 5);
  m_box2.pack_start(m_button2, Gtk::PACK_SHRINK, 5);
  
  // box1
  m_area.set_size_request(400, 400);
  m_box1.pack_start(m_area, Gtk::PACK_EXPAND_WIDGET, 5);
  m_box1.pack_start(m_box2, Gtk::PACK_SHRINK, 5);
    
  // box0
  m_box0.pack_start(m_box1, Gtk::PACK_EXPAND_WIDGET, 5);
  m_box0.pack_start(m_sb, Gtk::PACK_SHRINK, 5);
  
  set_border_width(10);
  add(m_box0);
  show_all();

}


Radar::~Radar()
{
}


int main(int argc, char** argv)
{
   Gtk::Main main_instance (argc, argv);

   Radar radar;
   Gtk::Main::run(radar);

   return 0;
}

