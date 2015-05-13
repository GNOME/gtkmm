/* GdkPixbuf library - Scaling and compositing demo
 *
 * Copyright (C) 2002 The gtkmm Development Team
 *
 * Authors: Federico Mena-Quintero <federico@gimp.org>
 * gtkmm port: Daniel Elstner <daniel.kitta@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include <sigc++/sigc++.h>
#include <glibmm/main.h>
#include <gdkmm/pixbuf.h>
#include <gdkmm/rectangle.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gdkmm/general.h>

namespace
{

/*
 * These values control the smoothness and speed of the animation.
 * For instance, FRAME_DELAY=25 and CYCLE_LEN=90 looks much better
 * to me (and also wastes more CPU cycles, of course).
 */
enum
{
  FRAME_DELAY = 48,
  CYCLE_LEN   = 64
};

const char * const background_name =
  "background.jpg";

const char * const image_names[] =
{
  "apple-red.png",
  "gnome-applets.png",
  "gnome-calendar.png",
  "gnome-foot.png",
  "gnome-gmush.png",
  "gnome-gimp.png",
  "gnome-gsame.png",
  "gnu-keys.png"
};

class DemoRenderArea : public Gtk::DrawingArea
{
public:
  DemoRenderArea();
  virtual ~DemoRenderArea();

protected:
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

private:
  Glib::RefPtr<const Gdk::Pixbuf>                 background_;
  std::vector< Glib::RefPtr<const Gdk::Pixbuf> >  images_;
  Glib::RefPtr<Gdk::Pixbuf>                       current_frame_;
  unsigned int                                    frame_num_;

  void generate_next_frame();
};

Glib::RefPtr<Gdk::Pixbuf> create_pixbuf(const std::string& name)
{
  std::string resource_name = std::string("/pixbufs/") + name;
  return Gdk::Pixbuf::create_from_resource(resource_name);
}

/*
 * Load all image files, create an empty buffer for storing the current frame,
 * and install a timeout handler that will be called periodically.  The show
 * will start as soon as Gtk::Application::run() is invoked.
 */
DemoRenderArea::DemoRenderArea()
:
  frame_num_ (0)
{
  std::string resource_name = std::string("/pixbufs/") + background_name;
  background_ = Gdk::Pixbuf::create_from_resource(resource_name);
  std::transform(
      &image_names[0], &image_names[G_N_ELEMENTS(image_names)],
      std::back_inserter(images_),
      &create_pixbuf);

  const int back_width  = background_->get_width();
  const int back_height = background_->get_height();

  current_frame_ = Gdk::Pixbuf::create(
      Gdk::COLORSPACE_RGB, false, 8, back_width, back_height);

  set_size_request(back_width, back_height);
  add_events(Gdk::EXPOSURE_MASK);

  Glib::signal_timeout().connect(
      sigc::bind_return(sigc::mem_fun(*this, &DemoRenderArea::generate_next_frame), true),
      FRAME_DELAY);
}

DemoRenderArea::~DemoRenderArea()
{}

/*
 * Draw handler of the widget.  Just fill the exposed
 * area with the corresponding pixmap data from current_frame_.
 */
bool DemoRenderArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gdk::Cairo::set_source_pixbuf(cr, current_frame_);
  cr->paint();

  return true; // stop signal emission
}

/*
 * Generate the next frame of the animation and store it into current_frame_.
 * The draw handler accesses that buffer to do the actual drawing.
 */
void DemoRenderArea::generate_next_frame()
{
  const int back_width  = background_->get_width();
  const int back_height = background_->get_height();

  background_->copy_area(0, 0, back_width, back_height, current_frame_, 0, 0);

  const double xmid = back_width  / 2.0;
  const double ymid = back_height / 2.0;

  const double f = 2.0 * G_PI * double(frame_num_) / CYCLE_LEN;

  double r = std::min(xmid, ymid) / 2.0;
  r += (r / 3.0) * std::sin(f);

  for(unsigned i = 0; i < images_.size(); ++i)
  {
    const double ang = 2.0 * G_PI * double(i) / images_.size() - f;

    const double iw = images_[i]->get_width();
    const double ih = images_[i]->get_height();

    const int xpos = int(std::floor(xmid + r * std::cos(ang) - iw / 2.0 + 0.5));
    const int ypos = int(std::floor(ymid + r * std::sin(ang) - ih / 2.0 + 0.5));

    const double depth = ((i % 2) != 0) ? std::sin(f) : std::cos(f);
    const double scale = std::max(0.25, 2.0 * depth * depth);

    Gdk::Rectangle rect (xpos, ypos, int(iw * scale), int(ih * scale));
    rect.intersect(Gdk::Rectangle(0, 0, back_width, back_height));

    if(!rect.has_zero_area())
    {
      const int overall_alpha = std::max(127, int(std::abs(255.0 * depth)));

      images_[i]->composite(
          current_frame_,
          rect.get_x(), rect.get_y(), rect.get_width(), rect.get_height(),
          xpos, ypos, scale, scale,
          Gdk::INTERP_NEAREST,
          overall_alpha);
    }
  }
  frame_num_ = (frame_num_ + 1) % CYCLE_LEN;

  // Tell GTK+ the widget should be redrawn soon.  This will trigger the
  // draw signal if the widget is actually mapped on the screen.
  queue_draw();
}

} // anonymous namespace

int main(int argc, char** argv)
{
  try
  {
    Glib::RefPtr<Gtk::Application> app =
      Gtk::Application::create(argc, argv);

    Gtk::Window window;
    window.add(*Gtk::manage(new DemoRenderArea()));

    window.set_resizable(false);
    window.show_all();

    return app->run(window);
  }
  catch(const Glib::Error& error)
  {
    std::cerr << error.what() << std::endl;
    return EXIT_FAILURE;
  }
}
