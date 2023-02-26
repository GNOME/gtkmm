/* Drop Downs
 *
 * The Gtk::DropDown widget is a modern alternative to Gtk::ComboBox.
 * It uses list models instead of tree models, and the content is
 * displayed using widgets instead of cell renderers.
 *
 * The examples here demonstrate how to use different kinds of
 * list models with Gtk::DropDown, how to use search and how to
 * display the selected item differently from the presentation
 * in the popup.
 */

#include <gtkmm.h>
#include <pangomm/cairofontmap.h>

class StringHolder : public Glib::Object {
public:
  Glib::ustring m_title;
  std::optional<Glib::ustring> m_icon;
  std::optional<Glib::ustring> m_description;
protected:
  StringHolder(const Glib::ustring& title,
               const std::optional<Glib::ustring>& icon,
               const std::optional<Glib::ustring>& description);
public:
  static Glib::RefPtr<StringHolder> create(
    const Glib::ustring& title,
    const std::optional<Glib::ustring>& icon,
    const std::optional<Glib::ustring>& description);
};

StringHolder::StringHolder(const Glib::ustring& title,
                           const std::optional<Glib::ustring>& icon,
                           const std::optional<Glib::ustring>& description)
:
  m_title(title),
  m_icon(icon),
  m_description(description)
{
}

Glib::RefPtr<StringHolder> StringHolder::create(
  const Glib::ustring& title,
  const std::optional<Glib::ustring>& icon,
  const std::optional<Glib::ustring>& description)
{
  return Glib::make_refptr_for_instance<StringHolder>(
    new StringHolder(title, icon, description));
}


class Example_DropDown : public Gtk::Window
{
public:
  Example_DropDown();
  ~Example_DropDown() override;

protected:
  void strings_setup_item_single_line(const Glib::RefPtr<Gtk::ListItem>& item);
  void strings_setup_item_full(const Glib::RefPtr<Gtk::ListItem>& item);
  void selected_item_changed(const Gtk::DropDown* dropdown,
                             const Glib::RefPtr<Gtk::ListItem>& item);
  void strings_bind_item(const Glib::RefPtr<Gtk::ListItem>& item, Gtk::DropDown* dropdown);
  void strings_unbind_item(const Glib::RefPtr<Gtk::ListItem>& item);
  Glib::RefPtr<Gtk::ListItemFactory> strings_factory_new(Gtk::DropDown* dropdown, bool full);
  Glib::RefPtr<Gio::ListModel> strings_model_new(const std::vector<Glib::ustring>& titles,
                                                 const std::vector<Glib::ustring>& icons,
                                                 const std::vector<Glib::ustring>& descriptions);
  Gtk::DropDown* drop_down_new_from_strings(const std::vector<Glib::ustring>& titles,
                                            const std::vector<Glib::ustring>& icons,
                                            const std::vector<Glib::ustring>& descriptions);

  Gtk::Box m_box;
  Gtk::CheckButton m_check;
};

Gtk::Window* do_dropdown()
{
  return new Example_DropDown();
}

void Example_DropDown::strings_setup_item_single_line(const Glib::RefPtr<Gtk::ListItem>& item)
{
  auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);

  auto image = Gtk::make_managed<Gtk::Image>();
  auto title = Gtk::make_managed<Gtk::Label>();
  title->set_xalign(0.0);
  auto checkmark = Gtk::make_managed<Gtk::Image>();
  checkmark->set_from_icon_name("object-select-symbolic");

  box->append(*image);
  box->append(*title);
  box->append(*checkmark);

  item->set_data("title", title);
  item->set_data("image", image);
  item->set_data("checkmark", checkmark);

  item->set_child(*box);
}

void Example_DropDown::strings_setup_item_full(const Glib::RefPtr<Gtk::ListItem>& item)
{
  auto image = Gtk::make_managed<Gtk::Image>();
  auto title = Gtk::make_managed<Gtk::Label>();
  title->set_xalign(0.0);
  auto description = Gtk::make_managed<Gtk::Label>();
  description->set_xalign(0.0);
  description->add_css_class("dim-label");
  auto checkmark = Gtk::make_managed<Gtk::Image>();
  checkmark->set_from_icon_name("object-select-symbolic");

  auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
  auto box2 = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 2);

  box->append(*image);
  box->append(*box2);
  box2->append(*title);
  box2->append(*description);
  box->append(*checkmark);

  item->set_data("title", title);
  item->set_data("image", image);
  item->set_data("description", description);
  item->set_data("checkmark", checkmark);

  item->set_child(*box);
}

void Example_DropDown::selected_item_changed(const Gtk::DropDown* dropdown,
                                             const Glib::RefPtr<Gtk::ListItem>& item)
{
  auto checkmark = static_cast<Gtk::Image*>(item->get_data("checkmark"));
  if (dropdown->get_selected_item() == item->get_item())
    checkmark->set_opacity(1.0);
  else
    checkmark->set_opacity(0.0);
}

void Example_DropDown::strings_bind_item(const Glib::RefPtr<Gtk::ListItem>& item,
                                         Gtk::DropDown* dropdown)
{
  auto holder = std::dynamic_pointer_cast<StringHolder>(item->get_item());

  auto title = static_cast<Gtk::Label*>(item->get_data("title"));
  auto image = static_cast<Gtk::Image*>(item->get_data("image"));
  auto description = static_cast<Gtk::Label*>(item->get_data("description"));
  auto checkmark = static_cast<Gtk::Image*>(item->get_data("checkmark"));

  title->set_label(holder->m_title);
  if (image)
  {
    if (holder->m_icon)
      image->set_from_icon_name(*holder->m_icon);
    else
      image->clear();
    image->set_visible(holder->m_icon.has_value());
  }
  if (description)
  {
    description->set_label(*holder->m_description);
    description->set_visible(holder->m_description.has_value());
  }

  auto popup = title->get_ancestor(GTK_TYPE_POPOVER);
  if (popup && popup->is_ancestor(*dropdown))
  {
    checkmark->set_visible(true);
    auto connection = dropdown->property_selected_item().signal_changed().connect(
      sigc::bind(sigc::mem_fun(*this, &Example_DropDown::selected_item_changed),
                 dropdown, item));
    item->set_data("connection", new sigc::connection(connection),
                   Glib::destroy_notify_delete<sigc::connection>);
    selected_item_changed(dropdown, item);
  }
  else
  {
    checkmark->set_visible(false);
  }
}

void Example_DropDown::strings_unbind_item(const Glib::RefPtr<Gtk::ListItem>& item)
{
  if (auto connection = static_cast<sigc::connection*>(item->get_data("connection")))
  {
    connection->disconnect();
    item->set_data("connection", nullptr);
  }
}

Glib::RefPtr<Gtk::ListItemFactory> Example_DropDown::strings_factory_new(Gtk::DropDown* dropdown,
                                                                         bool full)
{
  auto factory = Gtk::SignalListItemFactory::create();
  if (full)
    factory->signal_setup().connect(
      sigc::mem_fun(*this, &Example_DropDown::strings_setup_item_full));
  else
    factory->signal_setup().connect(
      sigc::mem_fun(*this, &Example_DropDown::strings_setup_item_single_line));
  factory->signal_bind().connect(
    sigc::bind(sigc::mem_fun(*this, &Example_DropDown::strings_bind_item), dropdown));
  factory->signal_unbind().connect(
    sigc::mem_fun(*this, &Example_DropDown::strings_unbind_item));

  return factory;
}

Glib::RefPtr<Gio::ListModel> Example_DropDown::strings_model_new(
  const std::vector<Glib::ustring>& titles,
  const std::vector<Glib::ustring>& icons,
  const std::vector<Glib::ustring>& descriptions)
{
  auto store = Gio::ListStore<StringHolder>::create();
  for (guint i = 0; i < titles.size(); i++)
  {
    auto icon = icons.empty() ? std::nullopt :
      std::make_optional<Glib::ustring>(icons[i]);
    auto description = descriptions.empty() ? std::nullopt :
      std::make_optional<Glib::ustring>(descriptions[i]);
    auto holder = StringHolder::create(titles[i], icon, description);
    store->append(holder);
  }

  return store;
}

Gtk::DropDown* Example_DropDown::drop_down_new_from_strings(
  const std::vector<Glib::ustring>& titles,
  const std::vector<Glib::ustring>& icons,
  const std::vector<Glib::ustring>& descriptions)
{
  g_return_val_if_fail(!titles.empty(), nullptr);
  g_return_val_if_fail(icons.empty() || icons.size() == titles.size(), nullptr);
  g_return_val_if_fail(descriptions.empty() || icons.size() == descriptions.size(), nullptr);

  auto model = strings_model_new(titles, icons, descriptions);
  auto dropdown = Gtk::make_managed<Gtk::DropDown>(model);

  auto factory = strings_factory_new(dropdown, false);
  Glib::RefPtr<Gtk::ListItemFactory> list_factory;
  if (!icons.empty() || !descriptions.empty())
    list_factory = strings_factory_new(dropdown, true);

  dropdown->set_factory(factory);
  dropdown->set_list_factory(list_factory);

  return dropdown;
}

Example_DropDown::Example_DropDown()
:
  m_box(Gtk::Orientation::VERTICAL, 10),
  m_check("Enable search")
{
  const std::vector<Glib::ustring> times{
    "1 minute", "2 minutes", "5 minutes", "20 minutes"
  };
  const std::vector<Glib::ustring> many_times{
    "1 minute", "2 minutes", "5 minutes", "10 minutes", "15 minutes", "20 minutes",
    "25 minutes", "30 minutes", "35 minutes", "40 minutes", "45 minutes", "50 minutes",
    "55 minutes", "1 hour", "2 hours", "3 hours", "5 hours", "6 hours", "7 hours",
    "8 hours", "9 hours", "10 hours", "11 hours", "12 hours"
  };
  const std::vector<Glib::ustring> device_titles{
    "Digital Output", "Headphones", "Digital Output", "Analog Output"
  };
  const std::vector<Glib::ustring> device_icons{
    "audio-card-symbolic", "audio-headphones-symbolic", "audio-card-symbolic",
    "audio-card-symbolic"
  };
  const std::vector<Glib::ustring> device_descriptions{
    "Built-in Audio", "Built-in audio", "Thinkpad Tunderbolt 3 Dock USB Audio",
    "Thinkpad Tunderbolt 3 Dock USB Audio"
  };

  set_title("Drop Downs");
  set_resizable(false);

  m_box.set_margin(10);
  set_child(m_box);

  auto model = Pango::CairoFontMap::get_default();
  auto dropdown = Gtk::make_managed<Gtk::DropDown>(model);
  dropdown->set_selected(0);

  auto expression = Gtk::ClosureExpression<Glib::ustring>::create(
    [](const Glib::RefPtr<Glib::ObjectBase>& item)->Glib::ustring
    {
      auto family = std::dynamic_pointer_cast<Pango::FontFamily>(item);
      return family ? family->get_name() : "";
    });
  dropdown->set_expression(expression);
  m_box.append(*dropdown);

  auto adj = Gtk::Adjustment::create(-1, -1, model->get_n_items());
  auto spin = Gtk::make_managed<Gtk::SpinButton>(adj);
  spin->set_halign(Gtk::Align::START);
  Glib::Binding::bind_property(dropdown->property_selected(),
                               spin->property_value(),
                               Glib::Binding::Flags::SYNC_CREATE |
                               Glib::Binding::Flags::BIDIRECTIONAL);
  m_box.append(*spin);

  Glib::Binding::bind_property(dropdown->property_enable_search(),
                               m_check.property_active(),
                               Glib::Binding::Flags::SYNC_CREATE |
                               Glib::Binding::Flags::BIDIRECTIONAL);
  m_box.append(m_check);

  dropdown = drop_down_new_from_strings(times, {}, {});
  m_box.append(*dropdown);

  dropdown = drop_down_new_from_strings(many_times, {}, {});
  dropdown->set_enable_search();
  expression = Gtk::ClosureExpression<Glib::ustring>::create(
    [](const Glib::RefPtr<Glib::ObjectBase>& item)->Glib::ustring
    {
      return std::dynamic_pointer_cast<StringHolder>(item)->m_title;
    });
  dropdown->set_expression(expression);
  m_box.append(*dropdown);

  dropdown = drop_down_new_from_strings(device_titles, device_icons, device_descriptions);
  m_box.append(*dropdown);
}

Example_DropDown::~Example_DropDown()
{
}
