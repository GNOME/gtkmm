/* G Calendar
 * Copyright (C) 1998 Cesar Miquel, Shawn T. Amundson, Mattias Grönlund
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gtkmm.h>
#include <iostream>


enum { DEF_PAD = 10 };
enum { DEF_PAD_SMALL = 5 };

enum { TM_YEAR_BASE = 1900 };

class CalendarExample : public Gtk::Window
{

public:
  CalendarExample();
  virtual ~CalendarExample();

  void set_flags();
  void font_selection_ok();
  void select_font();
  void toggle_flag(Gtk::CheckButton *toggle);

  void month_changed();
  void day_selected();
  void day_selected_double_click();

protected:
  Gtk::CheckButton* flag_checkboxes_[5];
  bool settings_[5];

  Gtk::FontSelectionDialog* font_dialog_;
  Gtk::Calendar* calendar_;
  Gtk::Label* label_selected_;
  Gtk::Label* label_selected_double_click_;
  Gtk::Label* label_month_;

  Glib::Date get_date() const;
};

CalendarExample::~CalendarExample()
{
  for (int i = 0; i < 5; i++)
  {
	  delete flag_checkboxes_[i];
  }

  delete calendar_;
  delete label_selected_;
  delete label_selected_double_click_;
  delete label_month_;
}

/*
 * GtkCalendar
 */

void CalendarExample::month_changed()
{
  label_month_->set_text(get_date().format_string("%x"));
}

void CalendarExample::day_selected()
{
  label_selected_->set_text(get_date().format_string("%x"));
}

void CalendarExample::day_selected_double_click()
{
  label_selected_double_click_->set_text(get_date().format_string("%x"));
}

void CalendarExample::set_flags()
{
  int options = 0;

  for (int i = 0; i < 5; i++)
  {
    if (settings_[i])
    {
      options = options + (1 << i);
    }
  }

  if (calendar_)
    calendar_->set_display_options((Gtk::CalendarDisplayOptions)options);
}

void CalendarExample::toggle_flag(Gtk::CheckButton *toggle)
{
  int j = 0;
  for (int i = 0; i < 5; i++)
    if (flag_checkboxes_[i] == (Gtk::CheckButton *)toggle)
      j = i;

  settings_[j] = !settings_[j];
  set_flags();
}

void CalendarExample::font_selection_ok()
{
  if(calendar_)
  {
    Glib::ustring font_name = font_dialog_->get_font_name();
    if (!font_name.empty())
    {
        calendar_->modify_font(Pango::FontDescription(font_name));
    }
  }
}


void CalendarExample::select_font()
{
  if (!font_dialog_)
  {
    font_dialog_  = new Gtk::FontSelectionDialog("Font Selection Dialog");
    font_dialog_->set_position(Gtk::WIN_POS_MOUSE);
    font_dialog_->get_ok_button()->signal_clicked().connect(sigc::mem_fun(*this, &CalendarExample::font_selection_ok));
    //font_dialog_->get_cancel_button()->signal_clicked.connect(sigc::bind(sigc::mem_fun(this, &CalendarExample::destroy_widget), font_dialog_));
  }

  if (!font_dialog_->is_visible())
    font_dialog_->show();
  else
  {
    delete font_dialog_;
    font_dialog_ = 0;
  }
}

CalendarExample::CalendarExample()
{
  font_dialog_ = NULL;

  for (int i = 0; i < 5; i++) {
    settings_[i] = 0;
  }

  set_border_width(5);

  set_resizable(false);

  Gtk::VBox* vbox = Gtk::manage(new Gtk::VBox(false, DEF_PAD));
  add(*vbox);

  /*
   * The top part of the CalendarExample, flags and fontsel.
   */

  Gtk::HBox* hbox = Gtk::manage(new Gtk::HBox(false, DEF_PAD));
  vbox->pack_start(*hbox, Gtk::PACK_EXPAND_WIDGET, DEF_PAD);
  Gtk::HButtonBox* hbbox = Gtk::manage(new Gtk::HButtonBox());
  hbox->pack_start(*hbbox, Gtk::PACK_SHRINK, DEF_PAD);
  hbbox->set_layout(Gtk::BUTTONBOX_SPREAD);
  hbbox->set_spacing(5);

  /* Calendar widget */
  Gtk::Frame* frame = Gtk::manage(new Gtk::Frame("Calendar"));
  hbbox->pack_start(*frame, Gtk::PACK_EXPAND_WIDGET, DEF_PAD);
  calendar_ = new Gtk::Calendar();
  set_flags();
  calendar_->mark_day(19);	
  frame->add(*calendar_);
  calendar_->signal_month_changed().connect(sigc::mem_fun(*this, &CalendarExample::month_changed));
  calendar_->signal_day_selected().connect(sigc::mem_fun(*this, &CalendarExample::day_selected));
  calendar_->signal_day_selected_double_click().connect(sigc::mem_fun(*this, &CalendarExample::day_selected_double_click));

  Gtk::VSeparator* separator = Gtk::manage(new Gtk::VSeparator());
  hbox->pack_start (*separator, Gtk::PACK_SHRINK);

  Gtk::VBox* vbox2 = Gtk::manage(new Gtk::VBox(false, DEF_PAD));
  hbox->pack_start(*vbox2, Gtk::PACK_SHRINK, DEF_PAD);
  
  /* Build the Right frame with the flags in */ 

  Gtk::Frame* frameFlags = Gtk::manage(new Gtk::Frame("Flags"));
  vbox2->pack_start(*frameFlags, Gtk::PACK_EXPAND_WIDGET, DEF_PAD);
  Gtk::VBox* vbox3 = Gtk::manage(new Gtk::VBox(true, DEF_PAD_SMALL));
  frameFlags->add(*vbox3);

  struct {
    char *label;
  } flags[] =
    {
      { "Show Heading" },
      { "Show Day Names" },
      { "No Month Change" },
      { "Show Week Numbers" },
      { "Week Start Monday" }
    };

  for (int i = 0; i < 5; i++)
  {
    Gtk::CheckButton* toggle = new Gtk::CheckButton(flags[i].label);
    toggle->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &CalendarExample::toggle_flag), toggle));
    vbox3->pack_start(*toggle);
    flag_checkboxes_[i] = toggle;
  }

  /* Build the right font-button */ 
  Gtk::Button* button = Gtk::manage(new Gtk::Button("Font..."));
  button->signal_clicked().connect(sigc::mem_fun(*this, &CalendarExample::select_font));
  vbox2->pack_start (*button, Gtk::PACK_SHRINK);

  /*
   *  Build the Signal-event part.
   */

  frame = Gtk::manage(new Gtk::Frame("Signal events"));
  vbox->pack_start(*frame, Gtk::PACK_EXPAND_WIDGET, DEF_PAD);
  vbox2 = Gtk::manage(new Gtk::VBox(true, DEF_PAD_SMALL));
  frame->add(*vbox2);
  
  hbox = Gtk::manage(new Gtk::HBox(false, 5));
  vbox2->pack_start (*hbox, Gtk::PACK_SHRINK);
  Gtk::Label* label = Gtk::manage(new Gtk::Label("Day selected:"));
  hbox->pack_start (*label, Gtk::PACK_SHRINK);
  label_selected_ = new Gtk::Label("");
  hbox->pack_start (*label_selected_, Gtk::PACK_SHRINK);

  hbox = Gtk::manage(new Gtk::HBox(false, 5));
  vbox2->pack_start (*hbox, Gtk::PACK_SHRINK);
  label = Gtk::manage(new Gtk::Label("Day selected double click:"));
  hbox->pack_start (*label, Gtk::PACK_SHRINK);
  label_selected_double_click_ = new Gtk::Label("");
  hbox->pack_start (*label_selected_double_click_, Gtk::PACK_SHRINK);

  hbox = Gtk::manage(new Gtk::HBox(false, 5));
  vbox2->pack_start (*hbox, Gtk::PACK_SHRINK);
  label = Gtk::manage(new Gtk::Label("Month change:")); 
  hbox->pack_start (*label, Gtk::PACK_SHRINK);
  label_month_ = new Gtk::Label("");
  hbox->pack_start(*label_month_, Gtk::PACK_SHRINK);
  
  Gtk::HButtonBox* bbox = Gtk::manage(new Gtk::HButtonBox());
  vbox->pack_start(*bbox, Gtk::PACK_SHRINK);
  bbox->set_layout(Gtk::BUTTONBOX_END);

  button = Gtk::manage(new Gtk::Button("Close"));
  button->signal_clicked().connect(&Gtk::Main::quit);
  bbox->add(*button);
  button->set_flags(Gtk::CAN_DEFAULT);
  button->grab_default();

  show_all();
}

Glib::Date CalendarExample::get_date() const
{
  using Glib::Date;

  unsigned int year = 0, month = 0, day = 0;
  calendar_->get_date(year, month, day);

  return Date(Date::Day(day), Date::Month(Date::JANUARY + month), Date::Year(year));
}


int main(int argc, char** argv)
{
  Gtk::Main myapp(&argc, &argv);
  CalendarExample calendar;
  Gtk::Main::run(calendar);
  return 0;
}

