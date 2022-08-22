/* Dialog and Message Boxes
 *
 * Dialog widgets are used to pop up a transient window for user feedback.
 */

#include <gtkmm.h>

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
  void on_message_response(int response_id, Gtk::MessageDialog* dialog);
  void on_interactive_response(int response_id, Dialog_Interactive* dialog);
  void on_non_modal_response(int response_id, Gtk::MessageDialog* dialog);

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

  gint m_count;
};

class Dialog_Interactive : public Gtk::Dialog
{
public:
  Dialog_Interactive(Gtk::Window& parent, const Glib::ustring& entry1, const Glib::ustring& entry2);
  ~Dialog_Interactive() override;

  Glib::ustring get_entry1() const;
  Glib::ustring get_entry2() const;

protected:
  //Member widgets:
  Gtk::Box m_HBox;
  Gtk::Grid m_Grid;
  Gtk::Label m_Label1, m_Label2;
  Gtk::Entry m_Entry1, m_Entry2;
  Gtk::Image m_Image;
};


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
  m_count = 0;

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
  Glib::ustring strMessage = "This message box has been popped up the following\n"
                             "number of times:\n\n";
  strMessage += Glib::ustring::format(m_count);

  auto dialog = new Gtk::MessageDialog(*this, strMessage, false, Gtk::MessageType::INFO, Gtk::ButtonsType::OK, true); //true = modal
  dialog->signal_response().connect(sigc::bind(
    sigc::mem_fun(*this, &Example_Dialog::on_message_response), dialog));
  dialog->show();
}

void Example_Dialog::on_button_interactive()
{
  Dialog_Interactive* pDialog = new Dialog_Interactive(*this, m_Entry1.get_text(), m_Entry2.get_text());
  pDialog->set_modal(true);
  pDialog->signal_response().connect(sigc::bind(
    sigc::mem_fun(*this, &Example_Dialog::on_interactive_response), pDialog));
  pDialog->show();
}

void Example_Dialog::on_button_non_modal()
{
  const Glib::ustring strMessage = "Non-modal message box.";
  auto dialog = Gtk::make_managed<Gtk::MessageDialog>(*this, strMessage,
    /* use_markup= */ false, Gtk::MessageType::INFO, Gtk::ButtonsType::OK, /* modal= */ false);
  dialog->set_destroy_with_parent(true);
  dialog->signal_response().connect(sigc::bind(
    sigc::mem_fun(*this, &Example_Dialog::on_non_modal_response), dialog));
  dialog->show();
}

void Example_Dialog::on_message_response(int /* response_id */, Gtk::MessageDialog* dialog)
{
  m_count++;
  delete dialog;
}

void Example_Dialog::on_interactive_response(int response_id, Dialog_Interactive* dialog)
{
  if (response_id == Gtk::ResponseType::OK)
  {
    m_Entry1.set_text(dialog->get_entry1());
    m_Entry2.set_text(dialog->get_entry2());
  }
  delete dialog;
}

void Example_Dialog::on_non_modal_response(int /* response_id */, Gtk::MessageDialog* dialog)
{
  // Delete the non-modal dialog.
  // If the Example_Dialog is deleted without first responding to the non-modal
  // dialog, the non-modal dialog is deleted with Example_Dialog, because it's
  // a managed widget which is destroyed with its parent.
  delete dialog;
}

Dialog_Interactive::Dialog_Interactive(Gtk::Window& parent, const Glib::ustring& entry1, const Glib::ustring& entry2)
: Gtk::Dialog("Interactive Dialog", parent, true),
  m_HBox(Gtk::Orientation::HORIZONTAL, 8),
  m_Label1("_Entry 1", true), m_Label2("E_ntry 2", true),
  m_Image()
{
  m_Image.set_from_icon_name("dialog-question");
  m_Image.set_icon_size(Gtk::IconSize::LARGE);
  add_button("_OK", Gtk::ResponseType::OK);
  add_button("_Cancel", Gtk::ResponseType::CANCEL);

  get_content_area()->append(m_HBox);
  m_HBox.append(m_Image);

  m_Grid.set_row_spacing(4);
  m_Grid.set_column_spacing(4);
  m_Grid.set_expand(true);
  m_HBox.append(m_Grid);

  m_Grid.attach(m_Label1, 0, 0);
  m_Entry1.set_text(entry1);
  m_Grid.attach(m_Entry1, 1, 0);
  m_Label1.set_mnemonic_widget(m_Entry1);

  m_Grid.attach(m_Label2, 0, 1);
  m_Entry2.set_text(entry2);
  m_Grid.attach(m_Entry2, 1, 1);
  m_Label2.set_mnemonic_widget(m_Entry2);
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
