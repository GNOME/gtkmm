
#include "popupentry.h"

#include <gdk/gdkkeysyms.h>
#include <gtk/gtkentry.h> /* see XXX below */
#include <gtkmm.h>


PopupEntry::PopupEntry(const Glib::ustring& path)
:
  Glib::ObjectBase  (typeid(PopupEntry)),
  Gtk::EventBox     (),
  Gtk::CellEditable (),
  path_             (path),
  button_           (0),
  entry_            (0),
  editing_canceled_ (false)
{
  Gtk::HBox *const hbox = new Gtk::HBox(false, 0);
  add(*Gtk::manage(hbox));

  entry_ = new Gtk::Entry();
  hbox->pack_start(*Gtk::manage(entry_), Gtk::PACK_EXPAND_WIDGET);
  entry_->set_has_frame(false);
  entry_->gobj()->is_cell_renderer = true; // XXX

  button_ = new Gtk::Button();
  hbox->pack_start(*Gtk::manage(button_), Gtk::PACK_SHRINK);
  button_->add(*Gtk::manage(new Gtk::Arrow(Gtk::ARROW_DOWN, Gtk::SHADOW_OUT)));

  set_flags(Gtk::CAN_FOCUS);
  add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);

  show_all_children();
}

PopupEntry::~PopupEntry()
{}

Glib::ustring PopupEntry::get_path() const
{
  return path_;
}

void PopupEntry::set_text(const Glib::ustring& text)
{
  entry_->set_text(text);
}

Glib::ustring PopupEntry::get_text() const
{
  return entry_->get_text();
}

void PopupEntry::select_region(int start_pos, int end_pos)
{
  entry_->select_region(start_pos, end_pos);
}

bool PopupEntry::get_editing_canceled() const
{
  return editing_canceled_;
}

// static
int PopupEntry::get_button_width()
{
  Gtk::Window window (Gtk::WINDOW_POPUP);

  Gtk::Button *const button = new Gtk::Button();
  window.add(*Gtk::manage(button));

  button->add(*Gtk::manage(new Gtk::Arrow(Gtk::ARROW_DOWN, Gtk::SHADOW_OUT)));

  // Urgh.  Hackish :/
  window.move(-500, -500);
  window.show_all();

  GtkRequisition requisition = { 0, 0 };
  window.size_request(&requisition);

  return requisition.width;
}

PopupEntry::type_signal_arrow_clicked& PopupEntry::signal_arrow_clicked()
{
  return signal_arrow_clicked_;
}

bool PopupEntry::on_key_press_event(GdkEventKey* event)
{
  if(event->keyval == GDK_Escape)
  {
    editing_canceled_ = true;

    editing_done();
    remove_widget();

    return true;
  }

  entry_->grab_focus();

  // Hackish :/ Synthesize a key press event for the entry.

  GdkEvent synth_event;
  synth_event.key = *event;

  synth_event.key.window = Glib::unwrap(entry_->get_window()); // XXX
  synth_event.key.send_event = true;

  entry_->event(&synth_event);

  return Gtk::EventBox::on_key_press_event(event);
}

void PopupEntry::start_editing_vfunc(GdkEvent*)
{
  entry_->select_region(0, -1);

  // TODO: This is a key-binding signal. Investigate whether we really need to use a keybinding signal
  // when creating a derived CellRenderer.
  entry_->signal_activate().connect(sigc::mem_fun(*this, &Self::on_entry_activate));
  entry_->signal_key_press_event().connect(sigc::mem_fun(*this, &Self::on_entry_key_press_event));

  //TODO: Doesn't this mean that we have multiple connection, because this is never disconnected?
  button_->signal_clicked().connect(sigc::mem_fun(*this, &Self::on_button_clicked));
}

void PopupEntry::on_button_clicked()
{
  signal_arrow_clicked_.emit();
}

void PopupEntry::on_entry_activate()
{
  editing_done();
  //remove_widget(); // TODO: this line causes the widget to be removed twice -- dunno why
}

bool PopupEntry::on_entry_key_press_event(GdkEventKey* event)
{
  if(event->keyval == GDK_Escape)
  {
    editing_canceled_ = true;

    editing_done();
    remove_widget();

    return true;
  }

  return false;
}

