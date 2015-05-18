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
  virtual ~Dialog_Interactive();

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
  m_VBox(Gtk::ORIENTATION_VERTICAL, 8),
  m_HBox(Gtk::ORIENTATION_HORIZONTAL, 8), m_HBox2(Gtk::ORIENTATION_HORIZONTAL, 8),
  m_Button_Message("_Message Dialog", true), m_Button_Interactive("_Interactive Dialog", true),
  m_Label1("_Entry 1", true),
  m_Label2("E_ntry 2", true)
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
  m_VBox.pack_start(*(Gtk::manage(new Gtk::Separator(Gtk::ORIENTATION_HORIZONTAL))), Gtk::PACK_SHRINK);


  /* Interactive dialog*/
  m_VBox.pack_start(m_HBox2, Gtk::PACK_SHRINK);
  m_Button_Interactive.signal_clicked().connect(sigc::mem_fun(*this, &Example_Dialog::on_button_interactive));
  m_HBox2.pack_start(m_VBox2, Gtk::PACK_SHRINK);
  m_VBox2.pack_start(m_Button_Interactive, Gtk::PACK_SHRINK);


  m_Grid.set_row_spacing(4);
  m_Grid.set_column_spacing(4);
  m_HBox2.pack_start(m_Grid, Gtk::PACK_SHRINK);

  m_Grid.attach(m_Label1, 0, 0, 1, 1);
  m_Grid.attach(m_Entry1, 1, 0, 1, 1);
  m_Label1.set_mnemonic_widget(m_Entry1);

  m_Grid.attach(m_Label2, 0, 1, 1, 1);
  m_Grid.attach(m_Entry2, 1, 1, 1, 1);
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
    Glib::ScopedPtr<char> buf (g_strdup_printf("%d", m_count));
    strMessage += buf.get();
  }
  Gtk::MessageDialog dialog(*this, strMessage, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true); //true = modal
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
  m_HBox(Gtk::ORIENTATION_HORIZONTAL, 8),
  m_Label1("_Entry 1", true), m_Label2("E_ntry 2", true),
  m_Image()
{
  m_Image.set_from_icon_name("dialog-question", Gtk::ICON_SIZE_DIALOG);
  add_button("_OK", Gtk::RESPONSE_OK);
  add_button("_Cancel", Gtk::RESPONSE_CANCEL);

  m_HBox.set_border_width(8);
  get_content_area()->pack_start(m_HBox, Gtk::PACK_SHRINK);
  m_HBox.pack_start(m_Image, Gtk::PACK_SHRINK);

  m_Grid.set_row_spacing(4);
  m_Grid.set_column_spacing(4);
  m_HBox.pack_start(m_Grid);

  m_Grid.attach(m_Label1, 0, 0, 1, 1);
  m_Entry1.set_text(entry1);
  m_Grid.attach(m_Entry1, 1, 0, 1, 1);
  m_Label1.set_mnemonic_widget(m_Entry1);

  m_Grid.attach(m_Label2, 0, 1, 1, 1);
  m_Entry2.set_text(entry2);
  m_Grid.attach(m_Entry2, 1, 1, 1, 1);
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

