/* Dialog and Message Boxes
 *
 * Dialog widgets are used to pop up a transient window for user feedback.
 */

#include "gtkmm.h"
#include "gtk/gtk.h"
#include "stdio.h"

class Example_Dialog : public Gtk::Window
{
public:
  Example_Dialog();
  virtual ~Example_Dialog();

protected:
  //Signal handlers:
  virtual void on_button_message();
  virtual void on_button_interactive();

  //Member widgets:
  Gtk::Frame m_Frame;
  Gtk::VBox m_VBox, m_VBox2;
  Gtk::HBox m_HBox, m_HBox2;
  Gtk::Button m_Button_Message, m_Button_Interactive;
  Gtk::Table m_Table;
  Gtk::Label m_Label1, m_Label2;
  Gtk::Entry m_Entry1, m_Entry2;

  gint m_count;
};

class Dialog_Interactive : public Gtk::Dialog
{
public:
  Dialog_Interactive(Gtk::Window& parent, const Glib::ustring& entry1, const Glib::ustring& entry2);
  virtual ~Dialog_Interactive();

  Glib::ustring get_entry1() const;
  Glib::ustring get_entry2() const;

protected:
  //Member widgets:
  Gtk::HBox m_HBox;
  Gtk::Table m_Table;
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
  m_VBox(false, 8),
  m_HBox(false, 8), m_HBox2(false, 8),
  m_Button_Message("_Message Dialog", true), m_Button_Interactive("_Interactive Dialog", true),
  m_Table(2, 2, false),
  m_Label1("_Entry 1", true), m_Label2("E_ntry 2")
{
  m_count = 0;

  set_title("Dialogs");
  set_border_width(8);

  add(m_Frame);

  m_VBox.set_border_width(8);
  m_Frame.add(m_VBox);


  /* Standard message dialog */
  m_VBox.pack_start(m_HBox, Gtk::PACK_SHRINK);
  m_Button_Message.signal_clicked().connect(sigc::mem_fun(*this, &Example_Dialog::on_button_message));
  m_HBox.pack_start(m_Button_Message, Gtk::PACK_SHRINK);
  m_VBox.pack_start(*(Gtk::manage(new Gtk::HSeparator())), Gtk::PACK_SHRINK);


  /* Interactive dialog*/
  m_VBox.pack_start(m_HBox2, Gtk::PACK_SHRINK);
  m_Button_Interactive.signal_clicked().connect(sigc::mem_fun(*this, &Example_Dialog::on_button_interactive));
  m_HBox2.pack_start(m_VBox2, Gtk::PACK_SHRINK);
  m_VBox2.pack_start(m_Button_Interactive, Gtk::PACK_SHRINK);


  m_Table.set_row_spacings(4);
  m_Table.set_col_spacings(4);
  m_HBox2.pack_start(m_Table, Gtk::PACK_SHRINK);

  m_Table.attach(m_Label1, 0, 1, 0, 1);
  m_Table.attach(m_Entry1, 1, 2, 0, 1);
  m_Label1.set_mnemonic_widget(m_Entry1);

  m_Table.attach(m_Label2, 0, 1, 1, 2);
  m_Table.attach(m_Entry2, 1, 2, 1, 2);
  m_Label2.set_mnemonic_widget(m_Entry2);

  show_all();
}

Example_Dialog::~Example_Dialog()
{
}

void Example_Dialog::on_button_message()
{
  Glib::ustring strMessage = "This message box has been popped up the following\n"
                             "number of times:\n\n";
  {
    Gdk::ScopedPtr<char> buf (g_strdup_printf("%d", m_count));
    strMessage += buf.get();
  }
  Gtk::MessageDialog dialog(strMessage, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true); //true = modal
  /*int response =*/ dialog.run();

  m_count++;
}

void Example_Dialog::on_button_interactive()
{
  Dialog_Interactive* pDialog = new Dialog_Interactive(*this, m_Entry1.get_text(), m_Entry2.get_text());
  /*int response =*/ pDialog->run();
  m_Entry1.set_text(pDialog->get_entry1());
  m_Entry2.set_text(pDialog->get_entry2());
  delete pDialog;
}


Dialog_Interactive::Dialog_Interactive(Gtk::Window& parent, const Glib::ustring& entry1, const Glib::ustring& entry2)
: Gtk::Dialog("Interactive Dialog", parent, true),
  m_HBox(false, 8),
  m_Table(2, 2, false),
  m_Label1("_Entry 1", true), m_Label2("E_ntry 2", true),
  m_Image(Gtk::Stock::DIALOG_QUESTION, Gtk::ICON_SIZE_DIALOG)
{
  add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
  add_button("_Non-stock Button", Gtk::RESPONSE_CANCEL);

  m_HBox.set_border_width(8);
  get_vbox()->pack_start(m_HBox, Gtk::PACK_SHRINK);
  m_HBox.pack_start(m_Image, Gtk::PACK_SHRINK);

  m_Table.set_row_spacings(4);
  m_Table.set_col_spacings(4);
  m_HBox.pack_start(m_Table);

  m_Table.attach(m_Label1, 0, 1, 0, 1);
  m_Entry1.set_text(entry1);
  m_Table.attach(m_Entry1, 1, 2, 0, 1);
  m_Label1.set_mnemonic_widget(m_Entry1);

  m_Table.attach(m_Label2, 0, 1, 1, 2);
  m_Entry2.set_text(entry2);
  m_Table.attach(m_Entry2,  1, 2, 1, 2);
  m_Label2.set_mnemonic_widget(m_Entry2);

  show_all();
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

