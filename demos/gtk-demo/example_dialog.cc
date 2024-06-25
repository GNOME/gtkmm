/* Dialog and Message Boxes
 *
 * Dialog widgets are used to pop up a transient window for user feedback.
 *
 * Gtk::AlertDialog can show a simple dialog with a few lines of text and
 * one or more buttons.
 *
 * Gtk::AboutDialog, ColorDialog, FileDialog, FontDialog are more
 * specialized dialog classes (not shown in this demo).
 */

#include <gtkmm.h>
#include <iostream>
#include <vector>

class Dialog_Interactive;

class Example_Dialog : public Gtk::Window
{
public:
  Example_Dialog();
  ~Example_Dialog() override;

protected:
  //Signal handlers:
  void on_button_message();
  void on_button_interactive();
  void on_button_non_modal();
  void on_message_finish(const Glib::RefPtr<Gio::AsyncResult>& result,
    const Glib::RefPtr<Gtk::AlertDialog>& dialog);
  void on_interactive_response(const Glib::ustring& response, Dialog_Interactive* dialog);
  bool on_interactive_close_request(Dialog_Interactive* dialog);

  //Member widgets:
  Gtk::Frame m_Frame;
  Gtk::Box m_VBox, m_VBox2;
  Gtk::Box m_HBox, m_HBox2;
  Gtk::Button m_Button_Message;
  Gtk::Button m_Button_Interactive;
  Gtk::Button m_Button_NonModal;
  Gtk::Grid m_Grid;
  Gtk::Label m_Label1, m_Label2;
  Gtk::Entry m_Entry1, m_Entry2;

  int m_count{0};
}; // Example_Dialog

class Dialog_Interactive : public Gtk::Window
{
public:
  Dialog_Interactive(Gtk::Window& parent, const Glib::ustring& entry1, const Glib::ustring& entry2);
  ~Dialog_Interactive() override;

  void buttons_clicked_connect(const sigc::slot<void(const Glib::ustring&)>& slot);
  Glib::ustring get_entry1() const;
  Glib::ustring get_entry2() const;

protected:
  //Member widgets:
  Gtk::Grid m_Grid;
  Gtk::Image m_Image;
  Gtk::Label m_Label1;
  Gtk::Label m_Label2;
  Gtk::Entry m_Entry1;
  Gtk::Entry m_Entry2;
  Gtk::Box m_ButtonBox;
  Gtk::Button m_Button_OK;
  Gtk::Button m_Button_Cancel;
}; // Dialog_Interactive

//Called by DemoWindow;
Gtk::Window* do_dialog()
{
  return new Example_Dialog();
}

Example_Dialog::Example_Dialog()
: m_Frame("Dialogs"),
  m_VBox(Gtk::Orientation::VERTICAL, 8),
  m_HBox(Gtk::Orientation::HORIZONTAL, 8),
  m_HBox2(Gtk::Orientation::HORIZONTAL, 8),
  m_Button_Message("_Message Dialog", true),
  m_Button_Interactive("_Interactive Dialog", true),
  m_Button_NonModal("_Non-modal Dialog", true),
  m_Label1("_Entry 1", true),
  m_Label2("E_ntry 2", true)
{
  set_title("Dialogs");

  m_Frame.set_margin(8);
  set_child(m_Frame);

  m_VBox.set_margin(8);
  m_Frame.set_child(m_VBox);

  /* Standard message dialog */
  m_VBox.append(m_HBox);
  m_Button_Message.signal_clicked().connect(sigc::mem_fun(*this, &Example_Dialog::on_button_message));
  m_HBox.append(m_Button_Message);
  m_VBox.append(*Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::HORIZONTAL));

  /* Interactive dialog*/
  m_VBox.append(m_HBox2);
  m_Button_Interactive.signal_clicked().connect(sigc::mem_fun(*this, &Example_Dialog::on_button_interactive));
  m_HBox2.append(m_VBox2);
  m_VBox2.append(m_Button_Interactive);
  m_VBox.append(*Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::HORIZONTAL));

  m_Grid.set_row_spacing(4);
  m_Grid.set_column_spacing(4);
  m_HBox2.append(m_Grid);

  m_Grid.attach(m_Label1, 0, 0);
  m_Grid.attach(m_Entry1, 1, 0);
  m_Label1.set_mnemonic_widget(m_Entry1);

  m_Grid.attach(m_Label2, 0, 1);
  m_Grid.attach(m_Entry2, 1, 1);
  m_Label2.set_mnemonic_widget(m_Entry2);

  // Non-modal message dialog,
  // i.e. a dialog that does not freeze the rest of the application.
  m_VBox.append(m_Button_NonModal);
  m_Button_NonModal.signal_clicked().connect(sigc::mem_fun(
    *this, &Example_Dialog::on_button_non_modal));
}

Example_Dialog::~Example_Dialog()
{
}

void Example_Dialog::on_button_message()
{
  Glib::ustring strMessage =
    "This message box has been closed with OK\n"
    "the following number of times:\n\n";
  strMessage += Glib::ustring::format(m_count);
  auto dialog = Gtk::AlertDialog::create(strMessage);
  dialog->set_modal(true);
  dialog->set_buttons(std::vector<Glib::ustring>{"OK", "Cancel"});
  dialog->set_default_button(0);
  dialog->set_cancel_button(1);
  dialog->choose(*this,
    sigc::bind(sigc::mem_fun(*this, &Example_Dialog::on_message_finish), dialog));
}

void Example_Dialog::on_button_interactive()
{
  Dialog_Interactive* pDialog = new Dialog_Interactive(*this, m_Entry1.get_text(), m_Entry2.get_text());
  pDialog->set_modal(true);
  // Either on_interactive_response() or on_interactive_close_request(),
  // but not both, will be called.
  pDialog->buttons_clicked_connect(sigc::bind(
    sigc::mem_fun(*this, &Example_Dialog::on_interactive_response), pDialog));
  pDialog->signal_close_request().connect(sigc::bind(
    sigc::mem_fun(*this, &Example_Dialog::on_interactive_close_request), pDialog), false);
  pDialog->set_visible(true);
}

void Example_Dialog::on_button_non_modal()
{
  const Glib::ustring strMessage = "Non-modal message box.";
  auto dialog = Gtk::AlertDialog::create(strMessage);
  dialog->set_modal(false);
  dialog->show(*this);
}

void Example_Dialog::on_message_finish(const Glib::RefPtr<Gio::AsyncResult>& result,
  const Glib::RefPtr<Gtk::AlertDialog>& dialog)
{
  try
  {
    if (dialog->choose_finish(result) == 0)
      m_count++;
  }
  catch (const Gtk::DialogError& err)
  {
    std::cout << "Gtk::DialogError. " << err.what() << std::endl;
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Unexpected exception. " << err.what() << std::endl;
  }
}

void Example_Dialog::on_interactive_response(const Glib::ustring& response, Dialog_Interactive* dialog)
{
  std::cout << "Interactive response: " << response << "\n";
  if (response == "OK")
  {
    m_Entry1.set_text(dialog->get_entry1());
    m_Entry2.set_text(dialog->get_entry2());
  }
  delete dialog;
}

bool Example_Dialog::on_interactive_close_request(Dialog_Interactive* dialog)
{
  std::cout << "Interactive close request\n";
  // When Gtk::Window::set_hide_on_close() is not called, the window
  // is destroyed on close. Destroying (in GTK parlance) does not necessarily
  // lead to deletion.
  delete dialog;
  return true; // Don't call other signal handlers.
}

//***** Interactive dialog ******

Dialog_Interactive::Dialog_Interactive(Gtk::Window& parent,
  const Glib::ustring& entry1, const Glib::ustring& entry2)
: m_Label1("_Entry 1", true),
  m_Label2("E_ntry 2", true),
  m_ButtonBox(Gtk::Orientation::HORIZONTAL, 5),
  m_Button_OK("_OK", true),
  m_Button_Cancel("_Cancel", true)
{
  set_transient_for(parent);
  set_destroy_with_parent(true);

  set_title("Interactive Dialog");
  set_child(m_Grid);

  m_Grid.set_row_spacing(4);
  m_Grid.set_column_spacing(4);
  m_Grid.set_expand(true);

  m_Image.set_from_icon_name("dialog-question");
  m_Image.set_icon_size(Gtk::IconSize::LARGE);
  m_Grid.attach(m_Image, 0, 0, 1, 2);

  m_Grid.attach(m_Label1, 1, 0);
  m_Entry1.set_text(entry1);
  m_Grid.attach(m_Entry1, 2, 0);
  m_Label1.set_mnemonic_widget(m_Entry1);

  m_Grid.attach(m_Label2, 1, 1);
  m_Entry2.set_text(entry2);
  m_Grid.attach(m_Entry2, 2, 1);
  m_Label2.set_mnemonic_widget(m_Entry2);

  m_Grid.attach(m_ButtonBox, 0, 2, 3, 1);
  m_ButtonBox.set_halign(Gtk::Align::END);
  m_ButtonBox.append(m_Button_OK);
  m_ButtonBox.append(m_Button_Cancel);
}

void Dialog_Interactive::buttons_clicked_connect(
  const sigc::slot<void(const Glib::ustring&)>& slot)
{
  m_Button_OK.signal_clicked().connect(sigc::bind(slot, "OK"));
  m_Button_Cancel.signal_clicked().connect(sigc::bind(slot, "Cancel"));
}

Glib::ustring Dialog_Interactive::get_entry1() const
{
  return m_Entry1.get_text();
}

Glib::ustring Dialog_Interactive::get_entry2() const
{
  return m_Entry2.get_text();
}

Dialog_Interactive::~Dialog_Interactive()
{
}
