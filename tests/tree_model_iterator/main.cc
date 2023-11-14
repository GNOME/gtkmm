// Gtk::TreeModel and Gtk::TreeIter are deprecated, but let's keep the test.
// The recommended replacement is Gio::ListModel which requires no test here.
#undef GTKMM_DISABLE_DEPRECATED

#include <gtkmm.h>
#include <gtkmm/init.h>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <type_traits>

#ifdef GTKMM_DISABLE_DEPRECATED
int
main(int, char**)
{
  // If gtkmm is configured with build-deprecated-api=false, GTKMM_DISABLE_DEPRECATED
  // is defined in gtkmm.h (actually in gtkmmconfig.h). The undef at the start of
  // this file has no effect.
  return 77; // Tell Meson's test harness to skip this test.
}

#else

struct Columns: public Gtk::TreeModelColumnRecord {
  Gtk::TreeModelColumn<int> m_int;
  Columns() { add(m_int); }
};

static const Columns columns;

[[nodiscard]] static auto
create_model()
{
  auto model = Gtk::ListStore::create(columns);
  // NOT `auto&` – see https://gitlab.gnome.org/GNOME/gtkmm/-/merge_requests/88#note_1908596
  auto row = *model->append();
  row[columns.m_int] = 42;
  return model;
}

static void
test_operator_bool()
{
  Gtk::TreeModel::iterator non_const_iter;
  Gtk::TreeModel::const_iterator const_iter;
  // empty
  assert(!non_const_iter);
  assert(!    const_iter);
  // non-empty
  const auto model = create_model();
  non_const_iter = model->children().begin();
      const_iter = model->children().begin();
  assert(non_const_iter);
  assert(    const_iter);
}

static void
test_const_comparison()
{
  Gtk::TreeModel::iterator non_const_iter;
  Gtk::TreeModel::const_iterator const_iter;
  // empty
  assert(non_const_iter == const_iter);
  assert(const_iter == non_const_iter);
  // non-empty
  const auto model = create_model();
  non_const_iter = model->children().begin();
      const_iter = model->children().begin();
  assert(non_const_iter == const_iter);
  assert(const_iter == non_const_iter);
}

static void
test_change()
{
  const auto model = create_model();
  const Gtk::TreeModel::iterator   non_const_iter = model->children().begin();
  const Gtk::TreeModel::const_iterator const_iter = model->children().begin();
  assert(non_const_iter->get_value(columns.m_int) == 42);
  assert(    const_iter->get_value(columns.m_int) == 42);
  // change value: both iterators see the new one
  non_const_iter->set_value(columns.m_int, 99);
  assert(non_const_iter->get_value(columns.m_int) == 99);
  assert(    const_iter->get_value(columns.m_int) == 99);
}

static void
test_assignment_to_const()
{
  const auto model = create_model();
  const Gtk::TreeModel::iterator non_const_iter = model->children().begin();
  // construction
  const Gtk::TreeModel::const_iterator const_iter_1 = non_const_iter;
  assert(const_iter_1 == non_const_iter);
  // assignment
  Gtk::TreeModel::const_iterator const_iter_2;
  assert(!const_iter_2);
  // assert(const_iter_2 != non_const_iter); // cannot, as treeiter.cc asserts model_ == other.model
  assert(&(const_iter_2 = non_const_iter) == &const_iter_2); // must return *this!
  assert(const_iter_2);
  assert(const_iter_2 == non_const_iter);
}

// Check that the opposite is not possible.
static void
test_assignment_from_const()
{
  static_assert(!std::is_assignable_v   <Gtk::TreeModel::iterator, Gtk::TreeModel::const_iterator>);
  static_assert(!std::is_constructible_v<Gtk::TreeModel::iterator, Gtk::TreeModel::const_iterator>);
}

// https://gitlab.gnome.org/GNOME/gtkmm/-/issues/145#note_1858930
static void
test_convertibility_to_path()
{
  // Tterators must have models (canʼt be empty/invalid) or GtkTreePath errors
  const auto model = create_model();
  const Gtk::TreeModel::iterator   non_const_iter = model->children().begin();
  const Gtk::TreeModel::const_iterator const_iter = model->children().begin();
  // TreePaths constructed from non-const & const iterators
  assert(Gtk::TreePath{non_const_iter}.to_string() == "0");
  assert(Gtk::TreePath{    const_iter}.to_string() == "0");
  // Set a path manually & test OK
  Gtk::TreePath path("42");
  assert(path.to_string() == "42");
  // Ensure changed via assignment – from non-const iterator
  path = non_const_iter;
  assert(path.to_string() == "0");
  // Set a path manually & test OK
  path = Gtk::TreePath{"99"};
  assert(path.to_string() == "99");
  // Ensure changed via assignment – from const iterator
  path =     const_iter;
  assert(path.to_string() == "0");
}

int main(int /* argc */, char** /* argv */)
{
  gtk_init();
  Gtk::init_gtkmm_internals();

  test_operator_bool();
  test_const_comparison();
  test_change();
  test_assignment_to_const();
  test_assignment_from_const();

  test_convertibility_to_path();

  return EXIT_SUCCESS;
}
#endif // GTKMM_DISABLE_DEPRECATED
