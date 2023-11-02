/* Icon Browser
 *
 * Demonstrates many named icons.
 *
 * This demo shows Gtk::HeaderBar, Gtk::ListBox, Gtk::GridView and
 * Gtk::SearchBar in action, but its primary aim is to show an assortment
 * of named icons.
 *
 * Click on an icon to see it in different sizes.
 *
 * Press the search button and enter a search string, to show icons
 * whose names match the search string.
 *
 * You can drag icons to other programs. Either drag an icon's name from
 * the icon view, or drag an image from the dialog box that opens when you
 * click on an icon.
 */

#include <gtkmm.h>
#include <string>
#include <sstream>
#include <iostream>

namespace
{
// Labels in the ListBox with icon context names.
// The icon context ids in this program are not the same as in the Icon Naming Specification
// at http://standards.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html.
class IconContextLabel : public Gtk::Label
{
public:
  IconContextLabel(const Glib::ustring& id, const Glib::ustring& name)
  : Gtk::Label(name), m_id(id)
  { }

  Glib::ustring get_id() const { return m_id; }

private:
  Glib::ustring m_id;

}; // end IconContextLabel

// A Gio::ListStore item that stores name, description and context id of an icon.
class ModelColumns : public Glib::Object
{
public:
  Glib::ustring m_name;
  Glib::ustring m_description;
  Glib::ustring m_context_id;
  bool m_symbolic;

  static Glib::RefPtr<ModelColumns> create(const Glib::ustring& name,
    const Glib::ustring& description, const Glib::ustring& context_id, bool symbolic)
  {
    return Glib::make_refptr_for_instance<ModelColumns>(
      new ModelColumns(name, description, context_id, symbolic));
  }
  
protected:
  ModelColumns(const Glib::ustring& name, const Glib::ustring& description,
    const Glib::ustring& context_id, bool symbolic)
  : m_name(name), m_description(description), m_context_id(context_id),
    m_symbolic(symbolic)
  { }
}; // ModelColumns

// Dialog box, showing icon details.
class DetailDialog : public Gtk::Window
{
public:
  explicit DetailDialog(Gtk::Window& parent);
  ~DetailDialog() override;

  void set_image(const Glib::ustring& icon_name, const Glib::ustring& description);

protected:
  // Signal handler:
  void on_image_drag_begin(const Glib::RefPtr<Gdk::Drag>& drag, int size_index);
  Glib::RefPtr<Gdk::ContentProvider> on_image_prepare_texture(
    double x, double y, int size_index);

  Glib::RefPtr<const Gtk::IconPaintable> get_icon_paintable(int size_index);

  static const int n_icon_sizes = 5;
  static const int m_icon_size[n_icon_sizes];

  Glib::ustring m_icon_name;

  // Child widgets:
  Gtk::Grid m_grid;
  Gtk::Image m_image[n_icon_sizes];
  Gtk::Label m_label[n_icon_sizes];
  Gtk::Label m_description;

  Glib::RefPtr<Gtk::DragSource> m_image_drag_source[n_icon_sizes];

}; // end DetailDialog

} // anonymous namespace

// Main window.
class Example_IconBrowser : public Gtk::Window
{
public:
  Example_IconBrowser();
  ~Example_IconBrowser() override;

protected:
  // Signal handlers:
  void on_symbolic_radio_toggled();
  void on_context_list_selected_rows_changed();
  void on_icon_view_item_activated(unsigned int position);
  void on_setup_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_bind_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item);
  void on_search_bar_search_mode_enabled_changed();
  void on_search_entry_search_changed();

  void populate();
  void add_context(const Glib::ustring& id,
    const Glib::ustring& name, const Glib::ustring& description);
  void add_icon(const Glib::ustring& name,
    const Glib::ustring& description, const Glib::ustring& context_id);
  void filter_changed();
  bool is_icon_visible(const Glib::RefPtr<Glib::ObjectBase>& item) const;

  // Child widgets, header bar:
  Gtk::HeaderBar m_header;
  Gtk::Box m_header_radio_button_box;
  Gtk::ToggleButton m_normal_radio;
  Gtk::ToggleButton m_symbolic_radio;
  Gtk::ToggleButton m_search_button;

  Glib::RefPtr<Gtk::SizeGroup> m_button_size_group;

  // Child widgets, main part of window:
  Gtk::Box m_hbox;
  Gtk::ListBox m_context_list;
  Gtk::Box m_vcontent_box;
  Gtk::SearchBar m_search_bar;
  Gtk::SearchEntry2 m_search_entry;
  Gtk::ScrolledWindow m_scrolled_window;
  Gtk::GridView m_icon_view;

  // Dialog box, showing icon details:
  DetailDialog m_details;

  Glib::RefPtr<Glib::Binding> m_binding_search_button_search_entry;
  Glib::ustring m_current_context_id;
  bool m_current_symbolic{false};
  Glib::RefPtr<Gio::ListStore<ModelColumns>> m_store;
  Glib::RefPtr<Gtk::BoolFilter> m_filter;
  Glib::RefPtr<Gtk::FilterListModel> m_filter_model;
  Glib::RefPtr<Gtk::NoSelection> m_selection_model;
  Glib::RefPtr<Gtk::SignalListItemFactory> m_factory;

}; // end Example_IconBrowser


Gtk::Window* do_iconbrowser()
{
  return new Example_IconBrowser();
}

// Definition of main window methods.
Example_IconBrowser::Example_IconBrowser()
:
  m_header_radio_button_box(Gtk::Orientation::HORIZONTAL, 0),
  m_normal_radio("Normal"),
  m_symbolic_radio("Symbolic"),
  m_hbox(Gtk::Orientation::HORIZONTAL, 0),
  m_vcontent_box(Gtk::Orientation::VERTICAL, 0),
  m_details(*this)
{
  //set_title("Icon Browser"); // Not shown when header bar is shown
  set_default_size(600, 800);

  m_store = Gio::ListStore<ModelColumns>::create();
  // The BoolFilter's Expression is in filter_changed().
  m_filter = Gtk::BoolFilter::create({});
  m_filter_model = Gtk::FilterListModel::create(m_store, m_filter);
  m_selection_model = Gtk::NoSelection::create(m_filter_model);
  m_factory = Gtk::SignalListItemFactory::create();

  // The header bar.
  set_titlebar(m_header);
  set_title("Icon Browser");
  m_header.set_show_title_buttons(true);
  m_header.pack_end(m_search_button);
  m_search_button.set_image_from_icon_name("edit-find-symbolic");
  m_header.pack_end(m_header_radio_button_box);
  m_normal_radio.set_expand();
  m_normal_radio.set_active();
  m_header_radio_button_box.append(m_normal_radio);
  m_symbolic_radio.set_expand();
  m_header_radio_button_box.append(m_symbolic_radio);
  m_symbolic_radio.set_group(m_normal_radio);

  m_button_size_group = Gtk::SizeGroup::create(Gtk::SizeGroup::Mode::VERTICAL);
  m_button_size_group->add_widget(m_normal_radio);
  m_button_size_group->add_widget(m_symbolic_radio);
  m_button_size_group->add_widget(m_search_button);

  // Main part of the window.
  set_child(m_hbox);
  m_hbox.append(m_context_list);
  m_context_list.set_selection_mode(Gtk::SelectionMode::SINGLE);
  m_hbox.append(*Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::VERTICAL));
  m_vcontent_box.set_expand();
  m_hbox.append(m_vcontent_box);
  m_vcontent_box.append(m_search_bar);
  m_search_bar.set_child(m_search_entry);
  // The search bar is shown when the search toggle button is pressed.
  m_binding_search_button_search_entry = Glib::Binding::bind_property(
    m_search_button.property_active(),
    m_search_bar.property_search_mode_enabled(),
    Glib::Binding::Flags::BIDIRECTIONAL);
  m_scrolled_window.set_expand();
  m_vcontent_box.append(m_scrolled_window);
  m_scrolled_window.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
  m_scrolled_window.set_child(m_icon_view);
  m_icon_view.set_model(m_selection_model);
  m_icon_view.set_factory(m_factory);
  m_icon_view.set_single_click_activate(true);

  // Hook the search bar to key presses.
  m_search_bar.set_key_capture_widget(*this);

  // Connect signal handlers.
  m_symbolic_radio.signal_toggled().connect(
    sigc::mem_fun(*this, &Example_IconBrowser::on_symbolic_radio_toggled));
  m_context_list.signal_selected_rows_changed().connect(
    sigc::mem_fun(*this, &Example_IconBrowser::on_context_list_selected_rows_changed));
  m_icon_view.signal_activate().connect(
    sigc::mem_fun(*this, &Example_IconBrowser::on_icon_view_item_activated));
  m_factory->signal_setup().connect(
    sigc::mem_fun(*this, &Example_IconBrowser::on_setup_listitem));
  m_factory->signal_bind().connect(
    sigc::mem_fun(*this, &Example_IconBrowser::on_bind_listitem));
  m_search_bar.property_search_mode_enabled().signal_changed().connect(
    sigc::mem_fun(*this, &Example_IconBrowser::on_search_bar_search_mode_enabled_changed));
  m_search_entry.signal_search_changed().connect(
    sigc::mem_fun(*this, &Example_IconBrowser::on_search_entry_search_changed));

  on_symbolic_radio_toggled();
  populate();
  filter_changed();
}

Example_IconBrowser::~Example_IconBrowser()
{
}

void Example_IconBrowser::on_symbolic_radio_toggled()
{
  m_current_symbolic = m_symbolic_radio.get_active();
  filter_changed();
  m_icon_view.queue_draw();
}

void Example_IconBrowser::on_context_list_selected_rows_changed()
{
  auto row = m_context_list.get_selected_row();
  if (!row)
    return;

  m_search_button.set_active(false);
  auto rowchild = row->get_child();
  IconContextLabel* label = dynamic_cast<IconContextLabel*>(rowchild);
  if (label)
  {
    m_current_context_id = label->get_id();
    filter_changed();
  }
  else
    std::cout << "on_context_list_selected_rows_changed(): Unexpected child type." << std::endl;
}

void Example_IconBrowser::on_icon_view_item_activated(unsigned int position)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(m_filter_model->get_object(position));
  if (!col)
    return;
  const Glib::ustring name = col->m_name;
  if (name.empty() || !Gtk::IconTheme::get_for_display(get_display())->has_icon(name))
    return;
  m_details.set_title(name);
  m_details.set_image(name, col->m_description);
  m_details.present();
}

void Example_IconBrowser::on_setup_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  // Each ListItem contains a vertical Box with an Image and a Label.
  auto vBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  auto image = Gtk::make_managed<Gtk::Image>();
  image->set_icon_size(Gtk::IconSize::LARGE);
  vBox->append(*image);
  vBox->append(*Gtk::make_managed<Gtk::Label>());
  list_item->set_child(*vBox);
}

void Example_IconBrowser::on_bind_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto vBox = dynamic_cast<Gtk::Box*>(list_item->get_child());
  if (!vBox)
    return;
  auto image = dynamic_cast<Gtk::Image*>(vBox->get_first_child());
  if (!image)
    return;
  auto label = dynamic_cast<Gtk::Label*>(image->get_next_sibling());
  if (!label)
    return;
  image->set_from_icon_name(col->m_name);
  label->set_text(col->m_name);
  vBox->set_tooltip_text(col->m_description);

  // The grid item is a drag source. It can drag the icon's name.
  auto dnd_source = Gtk::DragSource::create();
  Glib::Value<Glib::ustring> value;
  value.init(value.value_type());
  value.set(col->m_name);
  dnd_source->set_content(Gdk::ContentProvider::create(value));
  dnd_source->set_actions(Gdk::DragAction::COPY);
  vBox->add_controller(dnd_source);
}

void Example_IconBrowser::on_search_bar_search_mode_enabled_changed()
{
  if (m_search_bar.get_search_mode())
    m_context_list.unselect_all();
}

void Example_IconBrowser::on_search_entry_search_changed()
{
  if (!m_search_entry.get_text().empty())
    filter_changed();
}

void Example_IconBrowser::populate()
{
  // This icon list has been copied from gtk+/demos/icon-browser/iconbrowserwin.c
  // and only slightly modified. (The first parameter in the calls to add_context()
  // and add_icon() has been removed.) When gtk+'s populate() changes, it is
  // easy to copy the modified populate().
  add_context("volume", "Volume", "Icons related to audio input and output volume");
  add_icon("audio-volume-high", "The icon used to indicate high audio volume", "volume");
  add_icon("audio-volume-low", "The icon used to indicate low audio volume", "volume");
  add_icon("audio-volume-medium", "The icon used to indicate medium audio volume", "volume");
  add_icon("audio-volume-muted", "The icon used to indicate the muted state for audio playback", "volume");
  add_icon("microphone-sensitivity-high", "The icon used to indicate high microphone sensitivity", "volume");
  add_icon("microphone-sensitivity-low", "The icon used to indicate low microphone sensitivity", "volume");
  add_icon("microphone-sensitivity-medium", "The icon used to indicate medium microphone sensitivity", "volume");
  add_icon("microphone-sensitivity-muted", "The icon used to indicate that a microphone is muted", "volume");

  add_context("multimedia", "Multimedia", "Icons related to playback of media");
  add_icon("media-playlist-repeat", "The icon for the repeat mode of a media player", "multimedia");
  add_icon("media-playlist-repeat-song", "The icon for repeating a song in a media player", "multimedia");
  add_icon("media-playlist-shuffle", "The icon for the shuffle mode of a media player", "multimedia");
  add_icon("media-playlist-consecutive", "The icon for consecutive mode of a media player", "multimedia");
  add_icon("media-skip-backward", "The icon for the skip backward action of a media player", "multimedia");
  add_icon("media-seek-backward", "The icon for the seek backward action of a media player", "multimedia");
  add_icon("media-playback-start", "The icon for the start playback action of a media player", "multimedia");
  add_icon("media-seek-forward", "The icon for the seek forward action of a media player", "multimedia");
  add_icon("media-skip-forward", "The icon for the skip forward action of a media player", "multimedia");
  add_icon("media-playback-stop", "The icon for the stop action of a media player", "multimedia");
  add_icon("media-playback-pause", "The icon for the pause action of a media player", "multimedia");
  add_icon("media-eject", "The icon for the eject action of a media player or file manager", "multimedia");
  add_icon("media-record", "The icon for the record action of a media application", "multimedia");
  add_icon("media-view-subtitles", "The icon used to show subtitles in a media player", "multimedia");

  add_context("network", "Network", "Icons related to network status");
  add_icon("network-transmit-receive", "The icon used data is being both transmitted and received simultaneously, while the computing device is connected to a network", "network");
  add_icon("network-transmit", "The icon used when data is being transmitted, while the computing device is connected to a network", "network");
  add_icon("network-receive", "The icon used when data is being received, while the computing device is connected to a network", "network");
  add_icon("network-idle", "The icon used when no data is being transmitted or received, while the computing device is connected to a network", "network");
  add_icon("network-error", "The icon used when an error occurs trying to intialize the network connection of the computing device", "network");
  add_icon("network-offline", "The icon used when the computing device is disconnected from the network", "network");

  add_context("weather", "Weather", "Icons about weather conditions");
  add_icon("weather-clear", "The icon used while the weather for a region is “clear skies”", "weather");
  add_icon("weather-clear-night", "The icon used while the weather for a region is “clear skies” during the night", "weather");
  add_icon("weather-few-clouds", "The icon used while the weather for a region is “partly cloudy”", "weather");
  add_icon("weather-few-clouds-night", "The icon used while the weather for a region is “partly cloudy” during the night", "weather");
  add_icon("weather-fog", "The icon used while the weather for a region is “foggy”", "weather");
  add_icon("weather-overcast", "The icon used while the weather for a region is “overcast”", "weather");
  add_icon("weather-severe-alert", "The icon used while a sever weather alert is in effect for a region", "weather");
  add_icon("weather-showers", "The icon used while rain showers are occurring in a region", "weather");
  add_icon("weather-showers-scattered", "The icon used while scattered rain showers are occurring in a region", "weather");
  add_icon("weather-snow", "The icon used while snow showers are occurring in a region", "weather");
  add_icon("weather-storm", "The icon used while storms are occurring in a region", "weather");

  add_context("navigation", "Navigation", "Icons for navigation in the user interface of a program");
  add_icon("go-first", "The icon for the go to the first item in a list", "navigation");
  add_icon("go-previous", "The icon for the go to the previous item in a list", "navigation");
  add_icon("go-next", "The icon for the go to the next item in a list", "navigation");
  add_icon("go-last", "The icon for the go to the last item in a list", "navigation");
  add_icon("go-bottom", "The icon for the go to bottom of a list", "navigation");
  add_icon("go-down", "The icon for the go down in a list", "navigation");
  add_icon("go-up", "The icon for the go up in a list", "navigation");
  add_icon("go-top", "The icon for the go to the top of a list", "navigation");
  add_icon("go-home", "The icon for the go to home location", "navigation");
  add_icon("go-jump", "The icon for the jump to action", "navigation");

  add_context("editing", "Editing", "Icons related to editing a document");
  add_icon("format-indent-less", "The icon for the decrease indent formatting action", "editing");
  add_icon("format-indent-more", "The icon for the increase indent formatting action", "editing");
  add_icon("format-justify-center", "The icon for the center justification formatting action", "editing");
  add_icon("format-justify-fill", "The icon for the fill justification formatting action", "editing");
  add_icon("format-justify-left", "The icon for the left justification formatting action", "editing");
  add_icon("format-justify-right", "The icon for the right justification action", "editing");
  add_icon("format-text-direction-ltr", "The icon for the left-to-right text formatting action", "editing");
  add_icon("format-text-direction-rtl", "The icon for the right-to-left formatting action", "editing");
  add_icon("format-text-bold", "The icon for the bold text formatting action", "editing");
  add_icon("format-text-italic", "The icon for the italic text formatting action", "editing");
  add_icon("format-text-underline", "The icon for the underlined text formatting action", "editing");
  add_icon("format-text-strikethrough", "The icon for the strikethrough text formatting action", "editing");
  add_icon("edit-clear", "The icon for the clear action", "editing");
  add_icon("edit-clear-all", "", "editing");
  add_icon("edit-copy", "The icon for the copy action", "editing");
  add_icon("edit-cut", "The icon for the cut action", "editing");
  add_icon("edit-delete", "The icon for the delete action", "editing");
  add_icon("edit-find-replace", "The icon for the find and replace action", "editing");
  add_icon("edit-paste", "The icon for the paste action", "editing");
  add_icon("edit-redo", "The icon for the redo action", "editing");
  add_icon("edit-select-all", "The icon for the select all action", "editing");
  add_icon("edit-select", "", "editing");
  add_icon("edit-undo", "The icon for the undo action", "editing");
  add_icon("document-properties", "The icon for the action to view the properties of a document in an application", "editing");
  add_icon("document-new", "The icon used for the action to create a new document", "editing");
  add_icon("document-open", "The icon used for the action to open a document", "editing");
  add_icon("document-open-recent", "The icon used for the action to open a document that was recently opened", "editing");
  add_icon("document-save", "The icon for the save action. Should be an arrow pointing down and toward a hard disk", "editing");
  add_icon("document-save-as", "The icon for the save as action", "editing");
  add_icon("document-send", "The icon for the send action. Should be an arrow pointing up and away from a hard disk", "editing");
  add_icon("document-page-setup", "The icon for the page setup action of a document editor", "editing");
  add_icon("changes-allow", "", "other");
  add_icon("changes-prevent", "", "other");
  add_icon("object-flip-horizontal", "The icon for the action to flip an object horizontally", "editing");
  add_icon("object-flip-vertical", "The icon for the action to flip an object vertically", "editing");
  add_icon("object-rotate-left", "The icon for the rotate left action performed on an object", "editing");
  add_icon("object-rotate-right", "The icon for the rotate rigt action performed on an object", "editing");
  add_icon("insert-image", "The icon for the insert image action of an application", "editing");
  add_icon("insert-link", "The icon for the insert link action of an application", "editing");
  add_icon("insert-object", "The icon for the insert object action of an application", "editing");
  add_icon("insert-text", "The icon for the insert text action of an application", "editing");
  add_icon("accessories-text-editor", "The icon used for the desktop's text editing accessory program", "editing");

  add_context("view", "View Controls", "Icons for view controls in a user interface");
  add_icon("view-list", "The icon used for “List“ view mode", "view");
  add_icon("view-grid", "The icon used for “Grid“ view mode (as opposed to “List“)", "view");
  add_icon("view-fullscreen", "The icon used for the “Fullscreen” item in the application's “View” menu", "view");
  add_icon("view-restore", "The icon used by an application for leaving the fullscreen view, and returning to a normal windowed view", "view");
  add_icon("zoom-fit-best", "The icon used for the “Best Fit” item in the application's “View” menu", "view");
  add_icon("zoom-in", "The icon used for the “Zoom in” item in the application's “View” menu", "view");
  add_icon("zoom-out", "The icon used for the “Zoom Out” item in the application's “View” menu ", "view");
  add_icon("zoom-original", "The icon used for the “Original Size” item in the application's “View” menu", "view");
  add_icon("view-continuous", "The icon used for a continuous view mode", "view");
  add_icon("view-paged", "The icon used for a paged view mode (as opposed to continuous)", "view");
  add_icon("view-dual", "The icon used for a side-by-side view of paginated content", "view");
  add_icon("view-wrapped", "The icon used to indicate a wrap-around to the beginning", "view");

  add_context("calendar", "Calendar, Tasks and Alarms", "Icons related to calendars, tasks and alarms");
  add_icon("task-due", "The icon used when a task is due soon", "calendar");
  add_icon("task-past-due", "The icon used when a task that was due, has been left incomplete", "calendar");
  add_icon("appointment-soon", "The icon used when an appointment will occur soon", "calendar");
  add_icon("appointment-missed", "The icon used when an appointment was missed", "calendar");
  add_icon("alarm", "The icon used for alarms when a task or appointment is due", "calendar");

  add_context("communication", "Communication", "Icons related email, phone calls, IM and other forms of communication");
  add_icon("mail-unread", "The icon used for an electronic mail that is unread", "communication");
  add_icon("mail-read", "The icon used for an electronic mail that is read", "communication");
  add_icon("mail-replied", "The icon used for an electronic mail that has been replied to", "communication");
  add_icon("mail-attachment", "The icon used for an electronic mail that contains attachments", "communication");
  add_icon("mail-mark-important", "The icon for the mark as important action of an electronic mail application", "communication");
  add_icon("mail-send", "The icon for the send action of an electronic mail application", "communication");
  add_icon("mail-send-receive", "The icon for the send and receive action of an electronic mail application", "communication");
  add_icon("call-start", "The icon used for initiating or accepting a call", "communication");
  add_icon("call-stop", "The icon used for stopping a current call", "communication");
  add_icon("call-missed", "The icon used to show a missed call", "communication");
  add_icon("user-available", "The icon used when a user on a chat network is available to initiate a conversation with", "communication");
  add_icon("user-offline", "The icon used when a user on a chat network is not available", "communication");
  add_icon("user-idle", "The icon used when a user on a chat network has not been an active participant in any chats on the network, for an extended period of time", "communication");
  add_icon("user-invisible", "The icon used when a user is on a chat network, but is invisible to others", "communication");
  add_icon("user-busy", "The icon used when a user is on a chat network, and has marked himself as busy", "communication");
  add_icon("user-away", "The icon used when a user on a chat network is away from their keyboard and the chat program", "communication");
  add_icon("user-status-pending", "The icon used when the current user status on a chat network is not known", "communication");

  add_context("devices", "Devices and Media", "Icons for devices and media");
  add_icon("audio-input-microphone", "The icon used for the microphone audio input device", "devices");
  add_icon("camera-web", "The fallback icon for web cameras", "devices");
  add_icon("camera-photo", "The icon used for a digital still camera devices", "devices");
  add_icon("input-keyboard", "The icon used for the keyboard input device", "devices");
  add_icon("printer", "The icon used for a printer device", "devices");
  add_icon("video-display", "The icon used for the monitor that video gets displayed to", "devices");
  add_icon("computer", "The icon used for the computing device as a whole", "devices");
  add_icon("media-optical", "The icon used for physical optical media such as CD and DVD", "devices");
  add_icon("phone", "The icon used for phone devices which support connectivity to the PC, such as VoIP, cellular, or possibly landline phones", "devices");
  add_icon("input-dialpad", "The icon used for dialpad input devices", "devices");
  add_icon("input-touchpad", "The icon used for touchpad input devices", "devices");
  add_icon("scanner", "The icon used for a scanner device", "devices");
  add_icon("audio-card", "The icon used for the audio rendering device", "devices");
  add_icon("input-gaming", "The icon used for the gaming input device", "devices");
  add_icon("input-mouse", "The icon used for the mousing input device", "devices");
  add_icon("multimedia-player", "The icon used for generic multimedia playing devices", "devices");
  add_icon("audio-headphones", "The icon used for headphones", "devices");
  add_icon("audio-headset", "The icon used for headsets", "devices");
  add_icon("display-projector", "The icon used for projectors", "devices");
  add_icon("media-removable", "The icon used for generic removable media", "devices");
  add_icon("printer-network", "The icon used for printers which are connected via the network", "devices");
  add_icon("audio-speakers", "The icon used for speakers", "devices");
  add_icon("camera-video", "The fallback icon for video cameras", "devices");
  add_icon("drive-optical", "The icon used for optical media drives such as CD and DVD", "devices");
  add_icon("drive-removable-media", "The icon used for removable media drives", "devices");
  add_icon("input-tablet", "The icon used for graphics tablet input devices", "devices");
  add_icon("network-wireless", "The icon used for wireless network connections", "devices");
  add_icon("network-wired", "The icon used for wired network connections", "devices");
  add_icon("media-floppy", "The icon used for physical floppy disk media", "devices");
  add_icon("media-flash", "The fallback icon used for flash media, such as memory stick and SD", "devices");

  add_context("contenttypes", "Content Types", "Icons for different types of data, such as audio or image files");
  add_icon("application-certificate", "", "contenttypes");
  add_icon("application-rss+xml", "", "contenttypes");
  add_icon("application-x-appliance", "", "contenttypes");
  add_icon("audio-x-generic", "The icon used for generic audio file types", "contenttypes");
  add_icon("folder", "The standard folder icon used to represent directories on local filesystems, mail folders, and other hierarchical groups", "contenttypes");
  add_icon("text-x-generic", "The icon used for generic text file types", "contenttypes");
  add_icon("video-x-generic", "The icon used for generic video file types", "contenttypes");
  add_icon("x-office-calendar", "The icon used for generic calendar file types", "contenttypes");

  add_context("emotes", "Emotes", "Icons for emotions that are expressed through text chat applications such as :-) or :-P in IRC or instant messengers");
  add_icon("face-angel", "The icon used for the 0:-) emote", "emotes");
  add_icon("face-angry", "The icon used for the X-( emote", "emotes");
  add_icon("face-cool", "The icon used for the B-) emote", "emotes");
  add_icon("face-crying", "The icon used for the :'( emote", "emotes");
  add_icon("face-devilish", "The icon used for the >:-) emote", "emotes");
  add_icon("face-embarrassed", "The icon used for the :-[ emote", "emotes");
  add_icon("face-kiss", "The icon used for the :-* emote", "emotes");
  add_icon("face-laugh", "The icon used for the :-)) emote", "emotes");
  add_icon("face-monkey", "The icon used for the :-(|) emote", "emotes");
  add_icon("face-plain", "The icon used for the :-| emote", "emotes");
  add_icon("face-raspberry", "The icon used for the :-P emote", "emotes");
  add_icon("face-sad", "The icon used for the :-( emote", "emotes");
  add_icon("face-shutmouth", "The 'shut mouth' emote", "emotes");
  add_icon("face-sick", "The icon used for the :-& emote", "emotes");
  add_icon("face-smile", "The icon used for the :-) emote", "emotes");
  add_icon("face-smile-big", "The icon used for the :-D emote", "emotes");
  add_icon("face-smirk", "The icon used for the :-! emote", "emotes");
  add_icon("face-surprise", "The icon used for the :-0 emote", "emotes");
  add_icon("face-tired", "The icon used for the |-) emote", "emotes");
  add_icon("face-uncertain", "The icon used for the :-/ emote", "emotes");
  add_icon("face-wink", "The icon used for the ;-) emote", "emotes");
  add_icon("face-worried", "The icon used for the :-S emote", "emotes");
  add_icon("face-yawn", "", "emotes");

  add_context("general", "General", "Generally useful icons that don't fit in a particular category");
  add_icon("edit-find", "The icon for generic search actions", "general");
  add_icon("content-loading", "The icon used to indicate that content is loading", "general");
  add_icon("open-menu", "The icon used for a menu button in the header bar", "general");
  add_icon("view-more", "The icon used for a  “View More“ action", "general");
  add_icon("tab-new", "The icon used for a “New Tab“ action", "general");
  add_icon("bookmark-new", "The icon used for creating a new bookmark", "general");
  add_icon("mark-location", "The icon used to mark a location on a map", "general");
  add_icon("find-location", "The icon used for a  “Search location“ action", "general");
  add_icon("send-to", "The icon used for a  “Send to“ action", "general");
  add_icon("object-select", "The icon used for generic selection actions", "general");
  add_icon("window-close", "The icon used for actions that close a view, such as window or tab close button", "general");
  add_icon("view-refresh", "The icon used for the “Refresh” item in the application's “View” menu", "general");
  add_icon("process-stop", "The icon used for the “Stop” action in applications with actions that may take a while to process, such as web page loading in a browser", "general");
  add_icon("action-unavailable", "The icon used to indicate that an action is currently unavailable, such as “Pause“ when no media is playing", "general");
  add_icon("document-print", "The icon for the print action of an application", "general");
  add_icon("printer-printing", "The icon used while a print job is successfully being spooled to a printing device", "general");
  add_icon("printer-warning", "The icon used when a recoverable problem occurs while attempting to printing", "general");
  add_icon("printer-error", "The icon used when an error occurs while attempting to print", "general");
  add_icon("dialog-information", "The icon used when a dialog is opened to give information to the user that may be pertinent to the requested action", "general");
  add_icon("dialog-question", "The icon used when a dialog is opened to ask a simple question of the user", "general");
  add_icon("dialog-warning", "The icon used when a dialog is opened to warn the user of impending issues with the requested action", "general");
  add_icon("dialog-password", "The icon used when a dialog requesting the authentication credentials for a user is opened", "general");
  add_icon("dialog-error", "The icon used when a dialog is opened to explain an error condition to the user", "general");
  add_icon("list-add", "The icon for the add to list action", "general");
  add_icon("list-remove", "The icon for the remove from list action", "general");
  add_icon("non-starred", "The icon used to indicate that an object is not 'starred'", "general");
  add_icon("semi-starred", "The icon used to indicate that an object has is 'half-starred'", "general");
  add_icon("starred", "The icon used to indicate that an object is 'starred'", "general");
  add_icon("star-new", "The used for the “New Star“ action", "general");
  add_icon("security-low", "The icon used to indicate that the security level of a connection is presumed to be insecure, either by using weak encryption, or by using a certificate that the could not be automatically verified, and which the user has not chosent to trust", "general");
  add_icon("security-medium", "The icon used to indicate that the security level of a connection is presumed to be secure, using strong encryption, and a certificate that could not be automatically verified, but which the user has chosen to trust", "general");
  add_icon("security-high", "The icon used to indicate that the security level of a connection is known to be secure, using strong encryption and a valid certificate", "general");
  add_icon("user-trash", "The icon for the user's “Trash” place in the file system", "other");
  add_icon("user-trash-full", "The icon for the user's “Trash” in the file system, when there are items in the “Trash” waiting for disposal or recovery", "general");
  add_icon("emblem-system", "The icon used as an emblem for directories that contain system libraries, settings, and data", "general");
  add_icon("avatar-default", "The generic avatar icon, which is used to represent a user that doesn't have a personalized avatar", "general");
  add_icon("emblem-synchronizing", "The icon used as an emblem to indicate that a a synchronizing operation is in process", "general");
  add_icon("emblem-shared", "The icon used as an emblem for files and directories that are shared to other users", "general");
  add_icon("folder-download", "The icon representing the location in the file system where downloaded files are stored", "general");
  add_icon("help-browser", "The icon used for the desktop's help browsing application", "general");

  add_context("other", "Other", "Icons which have may be too specialized and not of general interest");
  add_icon("view-sort-ascending", "The icon used for the “Sort Ascending” item in the application's “View” menu, or in a button for changing the sort method for a list", "other");
  add_icon("view-sort-descending", "The icon used for the “Sort Descending” item in the application's “View” menu, or in a button for changing the sort method for a list", "other");
  add_icon("document-revert", "The icon for the action of reverting to a previous version of a document", "other");
  add_icon("address-book-new", "The icon used for the action to create a new address book", "other");
  add_icon("application-exit", "The icon used for exiting an application. Typically this is seen in the application's menus as File->Quit", "other");
  add_icon("appointment-new", "The icon used for the action to create a new appointment in a calendaring application", "other");
  add_icon("contact-new", "The icon used for the action to create a new contact in an address book application", "other");
  add_icon("document-print-preview", "The icon for the print preview action of an application", "other");
  add_icon("folder-new", "The icon for creating a new folder", "other");
  add_icon("help-about", "The icon for the About item in the Help menu", "other");
  add_icon("help-contents", "The icon for Contents item in the Help menu", "other");
  add_icon("help-faq", "The icon for the FAQ item in the Help menu", "other");
  add_icon("list-remove-all", "", "other");
  add_icon("mail-forward", "The icon for the forward action of an electronic mail application", "other");
  add_icon("mail-mark-junk", "The icon for the mark as junk action of an electronic mail application", "other");
  add_icon("mail-mark-notjunk", "The icon for the mark as not junk action of an electronic mail application", "other");
  add_icon("mail-mark-read", "The icon for the mark as read action of an electronic mail application", "other");
  add_icon("mail-mark-unread", "The icon for the mark as unread action of an electronic mail application", "other");
  add_icon("mail-message-new", "The icon for the compose new mail action of an electronic mail application", "other");
  add_icon("mail-reply-all", "The icon for the reply to all action of an electronic mail application", "other");
  add_icon("mail-reply-sender", "The icon for the reply to sender action of an electronic mail application", "other");
  add_icon("pan-down", "", "other");
  add_icon("pan-end", "", "other");
  add_icon("pan-start", "", "other");
  add_icon("pan-up", "", "other");
  add_icon("system-lock-screen", "The icon used for the “Lock Screen” item in the desktop's panel application", "other");
  add_icon("system-log-out", "The icon used for the “Log Out” item in the desktop's panel application", "other");
  add_icon("system-run", "The icon used for the “Run Application...” item in the desktop's panel application", "other");
  add_icon("system-search", "The icon used for the “Search” item in the desktop's panel application", "other");
  add_icon("system-reboot", "The icon used for the “Reboot” item in the desktop's panel application", "other");
  add_icon("system-shutdown", "The icon used for the “Shutdown” item in the desktop's panel application", "other");
  add_icon("tools-check-spelling", "The icon used for the “Check Spelling” item in the application's “Tools” menu", "other");
  add_icon("window-maximize", "", "other");
  add_icon("window-minimize", "", "other");
  add_icon("window-restore", "", "other");
  add_icon("window-new", "The icon used for the “New Window” item in the application's “Windows” menu", "other");
  add_icon("accessories-calculator", "The icon used for the desktop's calculator accessory program", "other");
  add_icon("accessories-character-map", "The icon used for the desktop's international and extended text character accessory program", "other");
  add_icon("accessories-dictionary", "The icon used for the desktop's dictionary accessory program", "other");
  add_icon("multimedia-volume-control", "The icon used for the desktop's hardware volume control application", "other");
  add_icon("preferences-desktop-accessibility", "The icon used for the desktop's accessibility preferences", "other");
  add_icon("preferences-desktop-display", "", "other");
  add_icon("preferences-desktop-font", "The icon used for the desktop's font preferences", "other");
  add_icon("preferences-desktop-keyboard", "The icon used for the desktop's keyboard preferences", "other");
  add_icon("preferences-desktop-keyboard-shortcuts", "", "other");
  add_icon("preferences-desktop-locale", "The icon used for the desktop's locale preferences", "other");
  add_icon("preferences-desktop-remote-desktop", "", "other");
  add_icon("preferences-desktop-multimedia", "The icon used for the desktop's multimedia preferences", "other");
  add_icon("preferences-desktop-screensaver", "The icon used for the desktop's screen saving preferences", "other");
  add_icon("preferences-desktop-theme", "The icon used for the desktop's theme preferences", "other");
  add_icon("preferences-desktop-wallpaper", "The icon used for the desktop's wallpaper preferences", "other");
  add_icon("preferences-system-privacy", "", "other");
  add_icon("preferences-system-windows", "", "other");
  add_icon("system-file-manager", "The icon used for the desktop's file management application", "other");
  add_icon("system-software-install", "The icon used for the desktop's software installer application", "other");
  add_icon("system-software-update", "The icon used for the desktop's software updating application", "other");
  add_icon("system-users", "", "other");
  add_icon("user-info", "", "other");
  add_icon("utilities-system-monitor", "The icon used for the desktop's system resource monitor application", "other");
  add_icon("utilities-terminal", "The icon used for the desktop's terminal emulation application. ", "other");
  add_icon("application-x-addon", "", "other");
  add_icon("application-x-executable", "The icon used for executable file types", "other");
  add_icon("font-x-generic", "The icon used for generic font file types", "other");
  add_icon("image-x-generic", "The icon used for generic image file types", "other");
  add_icon("package-x-generic", "The icon used for generic package file types", "other");
  add_icon("text-html", "The icon used for HTML text file types", "other");
  add_icon("text-x-generic-template", "The icon used for generic text templates", "other");
  add_icon("text-x-preview", "", "other");
  add_icon("text-x-script", "The icon used for script file types, such as shell scripts", "other");
  add_icon("x-office-address-book", "The icon used for generic address book file types", "other");
  add_icon("x-office-document", "The icon used for generic document and letter file types", "other");
  add_icon("x-office-document-template", "", "other");
  add_icon("x-office-presentation", "The icon used for generic presentation file types", "other");
  add_icon("x-office-presentation-template", "", "other");
  add_icon("x-office-spreadsheet", "The icon used for generic spreadsheet file types", "other");
  add_icon("x-office-spreadsheet-template", "", "other");
  add_icon("x-package-repository", "", "other");
  add_icon("applications-accessories", "The icon for the “Accessories” sub-menu of the Programs menu", "other");
  add_icon("applications-development", "The icon for the “Programming” sub-menu of the Programs menu", "other");
  add_icon("applications-engineering", "The icon for the “Engineering” sub-menu of the Programs menu", "other");
  add_icon("applications-games", "The icon for the “Games” sub-menu of the Programs menu", "other");
  add_icon("applications-graphics", "The icon for the “Graphics” sub-menu of the Programs menu", "other");
  add_icon("applications-internet", "The icon for the “Internet” sub-menu of the Programs menu", "other");
  add_icon("applications-multimedia", "The icon for the “Multimedia” sub-menu of the Programs menu", "other");
  add_icon("applications-office", "The icon for the “Office” sub-menu of the Programs menu", "other");
  add_icon("applications-other", "The icon for the “Other” sub-menu of the Programs menu", "other");
  add_icon("applications-science", "The icon for the “Science” sub-menu of the Programs menu", "other");
  add_icon("applications-system", "The icon for the “System Tools” sub-menu of the Programs menu", "other");
  add_icon("applications-utilities", "The icon for the “Utilities” sub-menu of the Programs menu", "other");
  add_icon("preferences-desktop", "The icon for the “Desktop Preferences” category", "other");
  add_icon("preferences-desktop-peripherals", "The icon for the “Peripherals” sub-category of the “Desktop Preferences” category", "other");
  add_icon("preferences-desktop-personal", "The icon for the “Personal” sub-category of the “Desktop Preferences” category", "other");
  add_icon("preferences-other", "The icon for the “Other” preferences category", "other");
  add_icon("preferences-system", "The icon for the “System Preferences” category", "other");
  add_icon("preferences-system-network", "The icon for the “Network” sub-category of the “System Preferences” category", "other");
  add_icon("system-help", "The icon for the “Help” system category", "other");
  add_icon("battery", "The icon used for the system battery device", "other");
  add_icon("computer-apple-ipad", "", "other");
  add_icon("colorimeter-colorhug", "", "other");
  add_icon("drive-harddisk", "The icon used for hard disk drives", "other");
  add_icon("drive-harddisk-ieee1394", "", "other");
  add_icon("drive-harddisk-system", "", "other");
  add_icon("drive-multidisk", "", "other");
  add_icon("media-optical-bd", "", "other");
  add_icon("media-optical-cd-audio", "", "other");
  add_icon("media-optical-dvd", "", "other");
  add_icon("media-tape", "The icon used for generic physical tape media", "other");
  add_icon("media-zip", "", "other");
  add_icon("modem", "The icon used for modem devices", "other");
  add_icon("multimedia-player-apple-ipod-touch", "", "other");
  add_icon("network-vpn", "", "other");
  add_icon("pda", "This is the fallback icon for Personal Digial Assistant devices. Primary use of this icon is for PDA devices connected to the PC. Connection medium is not an important aspect of the icon. The metaphor for this fallback icon should be a generic PDA device icon", "other");
  add_icon("phone-apple-iphone", "", "other");
  add_icon("uninterruptible-power-supply", "", "other");
  add_icon("emblem-default", "The icon used as an emblem to specify the default selection of a printer for example", "other");
  add_icon("emblem-documents", "The icon used as an emblem for the directory where a user's documents are stored", "other");
  add_icon("emblem-downloads", "The icon used as an emblem for the directory where a user's downloads from the internet are stored", "other");
  add_icon("emblem-favorite", "The icon used as an emblem for files and directories that the user marks as favorites", "other");
  add_icon("emblem-generic", "", "other");
  add_icon("emblem-important", "The icon used as an emblem for files and directories that are marked as important by the user", "other");
  add_icon("emblem-mail", "The icon used as an emblem to specify the directory where the user's electronic mail is stored", "other");
  add_icon("emblem-new", "", "other");
  add_icon("emblem-ok", "", "other");
  add_icon("emblem-package", "", "other");
  add_icon("emblem-photos", "The icon used as an emblem to specify the directory where the user stores photographs", "other");
  add_icon("emblem-readonly", "The icon used as an emblem for files and directories which can not be written to by the user", "other");
  add_icon("emblem-symbolic-link", "The icon used as an emblem for files and direcotires that are links to other files or directories on the filesystem", "other");
  add_icon("emblem-synchronized", "The icon used as an emblem for files or directories that are configured to be synchronized to another device", "other");
  add_icon("emblem-unreadable", "The icon used as an emblem for files and directories that are inaccessible. ", "other");
  add_icon("emblem-urgent", "", "other");
  add_icon("emblem-videos", "", "other");
  add_icon("emblem-web", "", "other");
  add_icon("folder-documents", "", "other");
  add_icon("folder-download", "", "other");
  add_icon("folder-music", "", "other");
  add_icon("folder-pictures", "", "other");
  add_icon("folder-documents", "", "other");
  add_icon("folder-publicshare", "", "other");
  add_icon("folder-remote", "The icon used for normal directories on a remote filesystem", "other");
  add_icon("folder-saved-search", "", "other");
  add_icon("folder-templates", "", "other");
  add_icon("folder-videos", "", "other");
  add_icon("network-server", "The icon used for individual host machines under the “Network Servers” place in the file manager", "other");
  add_icon("network-workgroup", "The icon for the “Network Servers” place in the desktop's file manager, and workgroups within the network", "other");
  add_icon("start-here", "The icon used by the desktop's main menu for accessing places, applications, and other features", "other");
  add_icon("user-bookmarks", "The icon for the user's special “Bookmarks” place", "other");
  add_icon("user-desktop", "The icon for the special “Desktop” directory of the user", "other");
  add_icon("user-home", "The icon for the special “Home” directory of the user", "other");
  add_icon("airplane-mode", "", "other");
  add_icon("battery-caution-charging", "", "other");
  add_icon("battery-caution", "The icon used when the battery is below 40%", "other");
  add_icon("battery-empty-charging", "", "other");
  add_icon("battery-empty", "", "other");
  add_icon("battery-full-charged", "", "other");
  add_icon("battery-full-charging", "", "other");
  add_icon("battery-full", "", "other");
  add_icon("battery-good-charging", "", "other");
  add_icon("battery-good", "", "other");
  add_icon("battery-low-charging", "", "other");
  add_icon("battery-low", "The icon used when the battery is below 20%", "other");
  add_icon("battery-missing", "", "other");
  add_icon("bluetooth-active", "", "other");
  add_icon("bluetooth-disabled", "", "other");
  add_icon("channel-insecure", "", "other");
  add_icon("channel-secure", "", "other");
  add_icon("computer-fail", "", "other");
  add_icon("display-brightness", "", "other");
  add_icon("keyboard-brightness", "", "other");
  add_icon("folder-drag-accept", "The icon used for a folder while an object is being dragged onto it, that is of a type that the directory can contain", "other");
  add_icon("folder-open", "The icon used for folders, while their contents are being displayed within the same window. This icon would normally be shown in a tree or list view, next to the main view of a folder's contents", "other");
  add_icon("folder-visiting", "The icon used for folders, while their contents are being displayed in another window. This icon would typically be used when using multiple windows to navigate the hierarchy, such as in Nautilus's spatial mode", "other");
  add_icon("image-loading", "The icon used when another image is being loaded, such as thumnails for larger images in the file manager", "other");
  add_icon("image-missing", "The icon used when another image could not be loaded", "other");
  add_icon("mail-signed", "The icon used for an electronic mail that contains a signature", "other");
  add_icon("mail-signed-verified", "The icon used for an electronic mail that contains a signature which has also been verified by the security system", "other");
  add_icon("network-cellular-3g", "", "other");
  add_icon("network-cellular-4g", "", "other");
  add_icon("network-cellular-edge", "", "other");
  add_icon("network-cellular-gprs", "", "other");
  add_icon("network-cellular-umts", "", "other");
  add_icon("network-cellular-acquiring", "", "other");
  add_icon("network-cellular-connected", "", "other");
  add_icon("network-cellular-no-route", "", "other");
  add_icon("network-cellular-offline", "", "other");
  add_icon("network-cellular-signal-excellent", "", "other");
  add_icon("network-cellular-signal-good", "", "other");
  add_icon("network-cellular-signal-ok", "", "other");
  add_icon("network-cellular-signal-weak", "", "other");
  add_icon("network-cellular-signal-none", "", "other");
  add_icon("network-vpn-acquiring", "", "other");
  add_icon("network-vpn", "", "other");
  add_icon("network-wired-acquiring", "", "other");
  add_icon("network-wired-disconnected", "", "other");
  add_icon("network-wired-no-route", "", "other");
  add_icon("network-wired-offline", "", "other");
  add_icon("network-wireless-acquiring", "", "other");
  add_icon("network-wireless-connected", "", "other");
  add_icon("network-wireless-encrypted", "", "other");
  add_icon("network-wireless-hotspot", "", "other");
  add_icon("network-wireless-no-route", "", "other");
  add_icon("network-wireless-offline", "", "other");
  add_icon("network-wireless-signal-excellent", "", "other");
  add_icon("network-wireless-signal-good", "", "other");
  add_icon("network-wireless-signal-ok", "", "other");
  add_icon("network-wireless-signal-weak", "", "other");
  add_icon("network-wireless-signal-none", "", "other");
  add_icon("rotation-allowed", "", "other");
  add_icon("rotation-locked", "", "other");
  add_icon("software-update-available", "The icon used when an update is available for software installed on the computing device, through the system software update program", "other");
  add_icon("software-update-urgent", "The icon used when an urgent update is available through the system software update program", "other");
  add_icon("sync-error", "The icon used when an error occurs while attempting to synchronize data from the computing device, to another device", "other");
  add_icon("sync-synchronizing", "The icon used while data is successfully synchronizing to another device", "other");
  add_icon("touchpad-disabled", "", "other");
  add_icon("trophy-bronze", "", "other");
  add_icon("trophy-silver", "", "other");
  add_icon("trophy-gold", "", "other");
}

void Example_IconBrowser::add_context(const Glib::ustring& id,
  const Glib::ustring& name, const Glib::ustring& description)
{
  IconContextLabel* row = Gtk::make_managed<IconContextLabel>(id, name);
  row->set_margin(5);
  m_context_list.append(*row);

  // Set the tooltip on the list box row.
  auto listboxrow = row->get_parent();
  listboxrow->set_tooltip_text(description);

  if (m_current_context_id.empty())
    m_current_context_id = row->get_id();
}

void Example_IconBrowser::add_icon(const Glib::ustring& name,
  const Glib::ustring& description, const Glib::ustring& context_id)
{
  // Add up to two new items to m_store (which is a Gio::ListStore).
  auto regular_name = name;
  if (Gtk::IconTheme::get_for_display(get_display())->has_icon(regular_name))
    m_store->append(ModelColumns::create(
      regular_name, description, context_id, false));

  auto symbolic_name = name + "-symbolic";
  if (Gtk::IconTheme::get_for_display(get_display())->has_icon(symbolic_name))
    m_store->append(ModelColumns::create(
      symbolic_name, description, context_id, true));
}

void Example_IconBrowser::filter_changed()
{
  // When a new expression is set in the BoolFilter, it emits signal_changed(),
  // and the FilterListModel re-evaluates the filter.
  auto expression = Gtk::ClosureExpression<bool>::create(
    sigc::mem_fun(*this, &Example_IconBrowser::is_icon_visible));
  m_filter->set_expression(expression);
}

bool Example_IconBrowser::is_icon_visible(const Glib::RefPtr<Glib::ObjectBase>& item) const
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(item);
  if (!col)
    return false;
  const Glib::ustring name = col->m_name;
  if (name.empty())
    return false;
  if (col->m_symbolic != m_current_symbolic)
    return false;

  const bool search = m_search_button.get_active();
  bool visible = false;
  if (search)
  {
    const auto search_text = m_search_entry.get_text();
    visible = name.find(search_text) != std::string::npos;
  }
  else
  {
    visible = col->m_context_id == m_current_context_id;
  }
  return visible;
}


// Initialization of static data.
const int DetailDialog::n_icon_sizes;
const int DetailDialog::m_icon_size[n_icon_sizes] = { 16, 24, 32, 48, 64 };


// Definition of detail dialog methods.
DetailDialog::DetailDialog(Gtk::Window& parent)
{
  set_transient_for(parent);
  set_modal();
  set_resizable(false);
  set_hide_on_close();
  set_child(m_grid);
  m_grid.set_expand();
  m_grid.set_margin(10);
  m_grid.set_row_spacing(10);
  m_grid.set_column_spacing(10);
  for (int i = 0; i < n_icon_sizes; ++i)
  {
    m_grid.attach(m_image[i], i, 0);
    m_image[i].set_margin(4);
    m_image[i].set_halign(Gtk::Align::CENTER);
    m_image[i].set_valign(Gtk::Align::END);

    // Enable dragging an image, and copying it to another program.
    m_image_drag_source[i] = Gtk::DragSource::create();
    m_image_drag_source[i]->signal_prepare().connect(
      sigc::bind(sigc::mem_fun(*this, &DetailDialog::on_image_prepare_texture), i), false);
    m_image_drag_source[i]->signal_drag_begin().connect(
      sigc::bind(sigc::mem_fun(*this, &DetailDialog::on_image_drag_begin), i));
    m_image[i].add_controller(m_image_drag_source[i]);

    m_grid.attach(m_label[i], i, 1);
    m_label[i].set_margin(4);
    m_label[i].set_halign(Gtk::Align::CENTER);
    m_label[i].set_valign(Gtk::Align::CENTER);
    std::ostringstream ostr;
    ostr << m_icon_size[i] << 'x' << m_icon_size[i];
    m_label[i].set_text(ostr.str());
  }
  m_grid.attach(m_description, 0, 2, n_icon_sizes, 1);
  m_description.set_wrap(true);
  m_description.set_max_width_chars(60);
  m_description.set_halign(Gtk::Align::START);
  m_description.set_valign(Gtk::Align::START);
}

DetailDialog::~DetailDialog()
{
}

void DetailDialog::set_image(
  const Glib::ustring& icon_name, const Glib::ustring& description)
{
  m_icon_name = icon_name;

  for (int i = 0; i < n_icon_sizes; ++i)
  {
    m_image[i].set_from_icon_name(icon_name);
    m_image[i].set_pixel_size(m_icon_size[i]);
  }
  m_description.set_text(description);
  m_description.set_visible(!description.empty());
}

void DetailDialog::on_image_drag_begin(const Glib::RefPtr<Gdk::Drag>& /* drag */, int size_index)
{
  auto icon_paintable = get_icon_paintable(size_index);
  if (icon_paintable)
  {
    const auto hot_x = icon_paintable->get_intrinsic_width();
    const auto hot_y = icon_paintable->get_intrinsic_height();
    m_image_drag_source[size_index]->set_icon(icon_paintable, hot_x, hot_y);
  }
}

Glib::RefPtr<Gdk::ContentProvider> DetailDialog::on_image_prepare_texture(
  double, double, int size_index)
{
  auto icon_paintable = get_icon_paintable(size_index);
  if (!icon_paintable)
  {
    std::cout << "Error in DetailDialog::on_image_prepare_texture(): No Gtk::IconPaintable" << std::endl;
    return {};
  }

  const auto file = icon_paintable->get_file();
  if (!file)
  {
    std::cout << "Error in DetailDialog::on_image_prepare_texture(): No Gio::file" << std::endl;
    return {};
  }

  Glib::RefPtr<Gdk::Texture> texture;
  try
  {
    texture = Gdk::Texture::create_from_file(file);
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Error in DetailDialog::on_image_prepare_texture(): " << err.what() << std::endl;
    return {};
  }

  Glib::Value<Glib::RefPtr<const Gdk::Texture>> texture_value;
  texture_value.init(texture_value.value_type());
  texture_value.set(texture);
  return Gdk::ContentProvider::create(texture_value);
}

Glib::RefPtr<const Gtk::IconPaintable> DetailDialog::get_icon_paintable(int size_index)
{
  return Gtk::IconTheme::get_for_display(get_display())->lookup_icon(
    m_icon_name, m_icon_size[size_index]);
}
