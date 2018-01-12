/* Change Display
 *
 * Demonstrates migrating a window between different displays.
 * A display is a mouse and keyboard with some number of
 * associated monitors. The neat thing about having multiple
 * displays is that they can be on completely separate
 * computers, as long as there is a network connection to the
 * computer where the application is running.
 *
 * Only some of the windowing systems where GTK+ runs have the
 * concept of multiple displays. (The X Window System is the
 * main example.) Other windowing systems can only handle one
 * keyboard and mouse, and combine all monitors into
 * a single display.
 *
 * This is a moderately complex example, and demonstrates:
 *
 *  - Tracking the currently open displays
 *
 *  - Changing the display for a window
 *
 *  - Letting the user choose a window by clicking on it
 *
 *  - Using Gtk::ListStore and Gtk::TreeView
 *
 *  - Using Gtk::Dialog
 */

//TODO: Remove this undef when we know what to use instead of signal_button_release_event().
#undef GTKMM_DISABLE_DEPRECATED

#include <gtkmm.h>

class Popup : public Gtk::Window
{
public:
  Popup(const Glib::RefPtr<Gdk::Display>& display, const Glib::ustring& prompt);
  ~Popup() override;

protected:
  Gtk::Frame m_Frame;
  Gtk::Label m_Label;
};

class Example_ChangeDisplay : public Gtk::Dialog
{
public:
  Example_ChangeDisplay();
  ~Example_ChangeDisplay() override;

protected:
  virtual void setup_frame(Gtk::Frame& frame, Gtk::TreeView& treeview, Gtk::Box& buttonbox);

  virtual void initialize_displays();
  virtual void query_change_display();
  virtual Gtk::Widget* find_toplevel_at_pointer(const Glib::RefPtr<Gdk::Display>& display);
  virtual Gtk::Window* query_for_toplevel(const Glib::RefPtr<Gdk::Display>& display, const Glib::ustring& prompt);

  //signal handlers:
  virtual void on_button_display_open();
  virtual void on_button_display_close();

  virtual void on_treeview_display_selection_changed();

  virtual void on_display_closed(bool is_error, Glib::RefPtr<Gdk::Display> display);

  virtual bool on_popup_button_release_event(const Glib::RefPtr<Gdk::EventButton>& event);

  void on_response(int response_id) override;


  class ModelColumns_Display : public Gtk::TreeModelColumnRecord
  {
  public:
    Gtk::TreeModelColumn<Glib::ustring> m_name;
    Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Display> > m_display; //hidden

    ModelColumns_Display() { add(m_name); add(m_display); }
  };
  ModelColumns_Display m_columns_display;

  Gtk::Box m_VBox;
  Gtk::Frame m_Frame_Display;
  Gtk::TreeView m_TreeView_Display;
  Glib::RefPtr<Gtk::ListStore> m_refListStore_Display;
  Gtk::Box m_ButtonBox_Display;

  Gtk::Button m_Button_Display_Open, m_Button_Display_Close;

  Glib::RefPtr<Gtk::SizeGroup> m_refSizeGroup_Display;


  Glib::RefPtr<Gdk::Display> m_refCurrentDisplay;

  Popup* m_pPopup;

  bool m_popup_clicked;
};




Example_ChangeDisplay::Example_ChangeDisplay()
: Gtk::Dialog("Change Display"),
  m_VBox(Gtk::Orientation::VERTICAL, 5),
  m_Frame_Display("Display"),
  m_ButtonBox_Display(Gtk::Orientation::VERTICAL, 5),
  m_Button_Display_Open("_Open...", true), m_Button_Display_Close("_Close...", true),
  m_pPopup(nullptr),
  m_popup_clicked(false)
{
  add_button("_Close", Gtk::ResponseType::CLOSE);
  add_button("Change", Gtk::ResponseType::OK);

  set_default_size(300, 400);

  m_VBox.property_margin() = 8;
  get_content_area()->pack_start(m_VBox, Gtk::PackOptions::EXPAND_WIDGET);


  //Display:
  {
    setup_frame(m_Frame_Display, m_TreeView_Display, m_ButtonBox_Display);
    m_ButtonBox_Display.pack_start(m_Button_Display_Open, Gtk::PackOptions::SHRINK);
    m_Button_Display_Open.signal_clicked().connect( sigc::mem_fun(*this, &Example_ChangeDisplay::on_button_display_open) );
    m_ButtonBox_Display.pack_start(m_Button_Display_Close, Gtk::PackOptions::SHRINK);
    m_Button_Display_Close.signal_clicked().connect( sigc::mem_fun(*this, &Example_ChangeDisplay::on_button_display_close) );

    //Setup TreeView:
    m_refListStore_Display = Gtk::ListStore::create(m_columns_display);
    m_TreeView_Display.set_model(m_refListStore_Display);
    m_TreeView_Display.append_column("Name", m_columns_display.m_name);

    //Connect signal:
    auto refSelection = m_TreeView_Display.get_selection();
    refSelection->signal_changed().connect( sigc::mem_fun(*this, &Example_ChangeDisplay::on_treeview_display_selection_changed) );

    m_VBox.pack_start(m_Frame_Display, Gtk::PackOptions::EXPAND_WIDGET);

    m_refSizeGroup_Display = Gtk::SizeGroup::create(Gtk::SizeGroup::Mode::HORIZONTAL);
    m_refSizeGroup_Display->add_widget(m_ButtonBox_Display);
  }

  initialize_displays();
}

Example_ChangeDisplay::~Example_ChangeDisplay()
{
  if(m_pPopup)
  {
    delete m_pPopup;
    m_pPopup = nullptr;
  }
}

void Example_ChangeDisplay::setup_frame(Gtk::Frame& frame, Gtk::TreeView& treeview, Gtk::Box& buttonbox)
{
  auto pHBox = Gtk::manage( new Gtk::Box(Gtk::Orientation::HORIZONTAL, 8) );
  pHBox->property_margin() = 8;
  frame.add(*pHBox);

  auto pScrolledWindow = Gtk::manage( new Gtk::ScrolledWindow() );
  pScrolledWindow->set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
  pScrolledWindow->set_shadow_type(Gtk::ShadowType::IN);
  pHBox->pack_start(*pScrolledWindow, Gtk::PackOptions::EXPAND_WIDGET);

  treeview.set_headers_visible(false);
  pScrolledWindow->add(treeview);

  auto refSelection = treeview.get_selection();
  refSelection->set_mode(Gtk::SelectionMode::BROWSE);

  pHBox->pack_start(buttonbox, Gtk::PackOptions::SHRINK);
}

void Example_ChangeDisplay::initialize_displays()
{

#ifndef G_OS_WIN32
  auto refDisplayManager = Gdk::DisplayManager::get();

  for(auto refDisplay : refDisplayManager->list_displays())
  {
    auto row = *(m_refListStore_Display->append());
    row[m_columns_display.m_name] = refDisplay->get_name();;
    row[m_columns_display.m_display] = refDisplay;

    refDisplay->signal_closed().connect(
      sigc::bind<-1>( sigc::mem_fun(*this, &Example_ChangeDisplay::on_display_closed), refDisplay) );
  }

#endif
}

void Example_ChangeDisplay::on_display_closed(bool /* is_error */, Glib::RefPtr<Gdk::Display> display)
{
  auto children = m_refListStore_Display->children();
  for (auto iter = children.begin(); iter != children.end(); ++iter)
  {
    const Glib::RefPtr<Gdk::Display> refDisplay = (*iter)[m_columns_display.m_display];
    if (refDisplay == display)
    {
      m_refListStore_Display->erase(iter);
    }
  }
}

void Example_ChangeDisplay::on_button_display_open()
{
  Gtk::Dialog dialog("Open Display", true);
  dialog.add_button("_Cancel", Gtk::ResponseType::CANCEL);
  dialog.add_button("_OK", Gtk::ResponseType::OK);

  dialog.set_default_response(Gtk::ResponseType::OK);

  Gtk::Entry entry;
  entry.set_activates_default();

  Gtk::Label label("Please enter the name of\nthe new display\n");

  dialog.get_content_area()->add(label);
  dialog.get_content_area()->add(entry);

  entry.grab_focus();

  Glib::RefPtr<Gdk::Display> refResult;
  while (!refResult)
  {
    gint response_id = dialog.run();
    if (response_id != Gtk::ResponseType::OK)
      break;

    auto new_screen_name = entry.get_text();

    if( !new_screen_name.empty() )
    {
      refResult = Gdk::Display::open(new_screen_name);
      if (!refResult)
      {
        label.set_text("Can't open display.\nplease try another one\n");
      }
    }
  }
}

void Example_ChangeDisplay::on_button_display_close()
{
  if(m_refCurrentDisplay)
    m_refCurrentDisplay->close();
}

void Example_ChangeDisplay::on_treeview_display_selection_changed()
{
  auto refSelection = m_TreeView_Display.get_selection();
  auto iter = refSelection->get_selected();
  if(iter)
    m_refCurrentDisplay = (*iter)[m_columns_display.m_display];
  else
    m_refCurrentDisplay.reset();
}


/* Prompts the user for a toplevel window to move, and then moves
 * that window to the currently selected display
 */
void Example_ChangeDisplay::query_change_display()
{
  auto refDisplay = get_display();
  auto pTopLevel = query_for_toplevel(refDisplay,
   "Please select the toplevel\n"
   "to move to the new display");

  if (pTopLevel)
    pTopLevel->set_display(m_refCurrentDisplay);
  else
    refDisplay->beep();
}


void Example_ChangeDisplay::on_response(int response_id)
{
  if (response_id == Gtk::ResponseType::OK)
    query_change_display();
  else
    hide();
}



/* Asks the user to click on a window, then waits for them click
 * the mouse. When the mouse is released, returns the toplevel
 * window under the pointer, or NULL, if there is none.
 */
Gtk::Window* Example_ChangeDisplay::query_for_toplevel(const Glib::RefPtr<Gdk::Display>& display, const Glib::ustring& prompt)
{
  if(m_pPopup)
  {
    delete m_pPopup;
    m_pPopup = nullptr;
  }

  m_pPopup = new Popup(display, prompt);

  m_pPopup->show();

  auto cursor = Gdk::Cursor::create("crosshair");

  Gtk::Window* toplevel = nullptr;

  //TODO: Find a suitable replacement for this:
  //const GdkGrabStatus grabbed =  m_pPopup->get_window()->grab(false, Gdk::BUTTON_RELEASE_MASK, cursor, GDK_CURRENT_TIME);
  //Check it when the GTK+ example has been updated and file a bug about the unhelpful deprecation comment.
  const auto grabbed = Gdk::GrabStatus::SUCCESS;
  if(grabbed == Gdk::GrabStatus::SUCCESS )
  {
    m_popup_clicked = false;
    m_pPopup->signal_button_release_event().connect(
      sigc::mem_fun(*this, &Example_ChangeDisplay::on_popup_button_release_event), false);

    // Process events until clicked is set by button_release_event_cb.
    // We pass in may_block=true since we want to wait if there
    // are no events currently.
    while (!m_popup_clicked)
      Gtk::Main::iteration(true);

    toplevel = dynamic_cast<Gtk::Window*>(find_toplevel_at_pointer(display));
    if (toplevel == m_pPopup)
       toplevel = nullptr;
  }

  return toplevel;
}

// Finds the toplevel window under the mouse pointer, if any.
Gtk::Widget* Example_ChangeDisplay::find_toplevel_at_pointer(const Glib::RefPtr<Gdk::Display>& /* display */)
{
  //TODO: This needs to use Device::get_window_at_position(), when we can figure that out.
  //See https://bugzilla.gnome.org/show_bug.cgi?id=638907
  /*
  auto refPointerWindow = display->get_window_at_pointer();

  if (refPointerWindow)
  {
    // The user data field of a GdkWindow is used to store a pointer
    // to the widget that created it.
    GtkWidget* cWidget = nullptr;
    gpointer* user_data = nullptr;
    refPointerWindow->get_user_data(user_data);
    cWidget = (GtkWidget*)user_data;

    auto pWidget = Glib::wrap(cWidget);
    if(pWidget)
      return pWidget->get_toplevel();
  }
  */

  return nullptr;
}


bool Example_ChangeDisplay::on_popup_button_release_event(const Glib::RefPtr<Gdk::EventButton>& /* event */)
{
  m_popup_clicked = true;
  return true;
}

Popup::Popup(const Glib::RefPtr<Gdk::Display>& display, const Glib::ustring& prompt)
: Gtk::Window(Gtk::WindowType::POPUP),
  m_Label(prompt)
{
  set_display(display);
  set_modal(true);
  set_position(Gtk::WindowPosition::CENTER);

  m_Frame.set_shadow_type(Gtk::ShadowType::OUT);
  add(m_Frame);

  m_Label.property_margin() = 10;
  m_Frame.add(m_Label);
}

Popup::~Popup()
{
}


// called by DemoWindow
Gtk::Window* do_change_display()
{
  return new Example_ChangeDisplay();
}
