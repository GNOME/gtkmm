
#include "cellrendererpopup.h"

#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>


class CellRendererList : public CellRendererPopup
{
public:
  CellRendererList();
  virtual ~CellRendererList();

  void append_list_item(const Glib::ustring& text);
  Glib::ustring get_selected_item();

protected:
  virtual void on_show_popup(const Glib::ustring& path, int x1, int y1, int x2, int y2);

private:
  typedef CellRendererList Self;

  Glib::RefPtr<Gtk::ListStore>  list_store_;
  Gtk::TreeView                 tree_view_;

  bool on_tree_view_button_release_event(GdkEventButton* event);
  void on_tree_selection_changed();
};

