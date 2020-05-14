/* Dialog and Message Boxes
 *
 * Dialog widgets are used to pop up a transient window for user feedback.
 */

#include <gtkmm.h>
#include <gtk/gtk.h>
#include <stdio.h>

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
  void on_dialog_response(int response_id, Gtk::Dialog* dialog);

  //Member widgets:
  Gtk::Frame m_Frame;
  Gtk::Box m_VBox, m_VBox2;
  Gtk::Box m_HBox, m_HBox2;
  Gtk::Button m_Button_Message, m_Button_Interactive;
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


  m_Grid.set_row_spacing(4);
  m_Grid.set_column_spacing(4);
  m_HBox2.append(m_Grid);

  m_Grid.attach(m_Label1, 0, 0);
  m_Grid.attach(m_Entry1, 1, 0);
  m_Label1.set_mnemonic_widget(m_Entry1);

  m_Grid.attach(m_Label2, 0, 1);
  m_Grid.attach(m_Entry2, 1, 1);
  m_Label2.set_mnemonic_widget(m_Entry2);
}

Example_Dialog::~Example_Dialog()
{
}

void Example_Dialog::on_button_message()
{
  Glib::ustring strMessage = "This message box has been popped up the following\n"
                             "number of times:\n\n";
  {
    auto buf = Glib::make_unique_ptr_gfree(g_strdup_printf("%d", m_count));
    strMessage += buf.get();
  }
  Gtk::MessageDialog dialog(*this, strMessage, false, Gtk::MessageType::INFO, Gtk::ButtonsType::OK, true); //true = modal
  dialog.signal_response().connect(sigc::bind(
    sigc::mem_fun(*this, &Example_Dialog::on_dialog_response), &dialog));
  dialog.show();

  m_count++;
}

void Example_Dialog::on_button_interactive()
{
  Dialog_Interactive* pDialog = new Dialog_Interactive(*this, m_Entry1.get_text(), m_Entry2.get_text());
  pDialog->set_modal(true);
  pDialog->signal_response().connect(sigc::bind(
    sigc::mem_fun(*this, &Example_Dialog::on_dialog_response), pDialog));
  pDialog->show();

  m_Entry1.set_text(pDialog->get_entry1());
  m_Entry2.set_text(pDialog->get_entry2());
  delete pDialog;
}

void Example_Dialog::on_dialog_response(int /* response_id */, Gtk::Dialog* dialog)
{
  dialog->hide();
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

