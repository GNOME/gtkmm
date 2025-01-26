// gtkmm#132 FileChooser, FileDialog: Gio::ListModel with Gio::File
// Test Gtk::FileChooser::get_files(), Gtk::FileChooser::get_files2() and
// Gtk::FileDialog::open_multiple_text_files_finish() after the issue has been fixed.
// Test Gio::ListModel::get_typed_object(), if glibmm >= 2.76.0.

// Gtk::FileChooser is deprecated
#undef GTKMM_DISABLE_DEPRECATED

#include <gtkmm.h>
#include <iostream>

#ifdef GLIBMM_CHECK_VERSION
#define GET_TYPED_OBJECT_EXISTS GLIBMM_CHECK_VERSION(2,76,0)
#else
#define GET_TYPED_OBJECT_EXISTS 0
#endif

class ExampleWindow : public Gtk::Window
{
public:
  // If gtkmm is configured with build-deprecated-api=false,
  // GTKMM_DISABLE_DEPRECATED is defined in gtkmm.h (actually in gtkmmconfig.h).
  // The undef at the start of this file has no effect.
  ExampleWindow()
  : m_vBox(Gtk::Orientation::VERTICAL),
    m_Button_FileDialog("FileDialog")
#ifndef GTKMM_DISABLE_DEPRECATED
  , m_FileChooserDialog(*this, "Choose files"),
    m_Button_FileChooserDialog("FileChooserDialog")
#endif
  {
    set_title("Gtk::FileDialog example");
    set_child(m_vBox);
    m_vBox.append(m_Button_FileDialog);
    m_Button_FileDialog.signal_clicked().connect(
      sigc::mem_fun(*this, &ExampleWindow::on_button_file_dialog_clicked));
#ifndef GTKMM_DISABLE_DEPRECATED
    m_vBox.append(m_Button_FileChooserDialog);
    m_Button_FileChooserDialog.signal_clicked().connect(
      sigc::mem_fun(*this, &ExampleWindow::on_button_file_chooser_dialog_clicked));

    m_FileChooserDialog.signal_response().connect(
      sigc::mem_fun(*this, &ExampleWindow::on_file_chooser_dialog_response));
    m_FileChooserDialog.set_select_multiple(true);
    m_FileChooserDialog.add_button("_Cancel", Gtk::ResponseType::CANCEL);
    m_FileChooserDialog.add_button("_Open", Gtk::ResponseType::OK);
#endif
  }
  virtual ~ExampleWindow() {}

protected:
  void on_button_file_dialog_clicked()
  {
    m_FileDialog = Gtk::FileDialog::create();
    m_FileDialog->set_modal(true);
    m_FileDialog->open_multiple_text_files(sigc::mem_fun(*this,
      &ExampleWindow::on_open_multiple_text_files));

    auto children = m_vBox.observe_children();
    if (children->get_n_items() > 0)
    {
      auto child0 = children->get_object(0);
      std::cout << "get_object() " << child0.get() << std::endl;
      std::cout << "dynamic_pointer_cast " << std::dynamic_pointer_cast<Gtk::Widget>(child0).get() << std::endl;      
#if GET_TYPED_OBJECT_EXISTS
      std::cout << "get_typed_object() " << (children->get_typed_object<Gtk::Widget>(0)).get() << std::endl;
#endif
    }
  }

  void on_open_multiple_text_files(Glib::RefPtr<Gio::AsyncResult>& result)
  {
    try
    {
      // open_multiple_text_files_finish() returns a vector of Gio::Files
      // and the selected encoding.
      auto [file_vector, encoding] = m_FileDialog->open_multiple_text_files_finish(result);
      auto file = file_vector[0];
      if (file)
        // This should print the first selected file's path and name.
        std::cout << file->get_path() << std::endl;
      else
        std::cout << "No file\n";
      std::cout << "Encoding: '" << encoding << "'\n";
    }
    catch (const Glib::Error& err)
    {
      std::cout << "Exception. " << err.what() << std::endl;
    }
  }

#ifndef GTKMM_DISABLE_DEPRECATED
  void on_button_file_chooser_dialog_clicked()
  {
    m_FileChooserDialog.set_visible(true);
  }

  void on_file_chooser_dialog_response(int response_id)
  {
    if (response_id == Gtk::ResponseType::OK)
    {
      auto list_model = m_FileChooserDialog.get_files();

      auto file = std::dynamic_pointer_cast<Gio::File>(list_model->get_object(0));
      if (file)
        std::cout << "Gio::File, get_object() " << file->get_path() << std::endl;
      else
        std::cout << "Expected failure: No file from get_files(), get_object()\n";

#if GET_TYPED_OBJECT_EXISTS
      file = list_model->get_typed_object<Gio::File>(1);
      if (file)
        std::cout << "Gio::File " << file->get_path() << std::endl;
      else
        std::cout << "No file from get_files()\n";

      auto icon = list_model->get_typed_object<Gio::Icon>(2);
      if (icon)
        std::cout << "Gio::Icon " << icon->to_string() << std::endl;
      else
        std::cout << "Expected failure: No icon from get_files()\n";

      auto file_icon = list_model->get_typed_object<Gio::FileIcon>(3);
      if (file_icon)
        std::cout << "Gio::FileIcon " << file_icon->get_file()->get_path() << std::endl;
      else
        std::cout << "Expected failure: No fileicon from get_files()\n";
#endif // GET_TYPED_OBJECT_EXISTS
      auto file_vector = m_FileChooserDialog.get_files2();
      auto file2 = file_vector[0];
      if (file2)
        // This should print the first selected file's path and name.
        std::cout << file2->get_path() << std::endl;
      else
        std::cout << "No file from get_files2()\n";
    }
    else
      std::cout << "Not OK\n";

    m_FileChooserDialog.set_visible(false);    
  }
#endif // GTKMM_DISABLE_DEPRECATED

private:
  Gtk::Box m_vBox;
  Glib::RefPtr<Gtk::FileDialog> m_FileDialog;
  Gtk::Button m_Button_FileDialog;
#ifndef GTKMM_DISABLE_DEPRECATED
  Gtk::FileChooserDialog m_FileChooserDialog;
  Gtk::Button m_Button_FileChooserDialog;
#endif
};

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("org.gtkmm.example");
  return app->make_window_and_run<ExampleWindow>(argc, argv);
}
