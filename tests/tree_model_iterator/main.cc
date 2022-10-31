// Gtk::TreeModel and Gtk::TreeIter are deprecated, but let's keep the test.
// The recommended replacement is Gio::ListModel which requires no test here.
#undef GTKMM_DISABLE_DEPRECATED

#include <gtkmm.h>
#include <gtkmm/init.h>
#include <iostream>
#include <cassert>
#include <cstdlib>

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

static void
test_const_conversion() {
  Gtk::TreeModel::iterator non_const_iter;
  Gtk::TreeModel::const_iterator const_iter;
  assert(non_const_iter == const_iter);
  assert(const_iter == non_const_iter);
}

static void
test_assignment_from_const() {
  Gtk::TreeModel::iterator non_const_iter;
  auto const_iter = non_const_iter;
  assert(const_iter == non_const_iter);
}

// TODO: Find some way to check that the opposite is not possible.
// For instance, check that the code won't compile if we try to assign
// a const iterator to a non-const iterator.
/*
static void
test_assignment_to_const() {
  Gtk::TreeModel::const_iterator const_iter;
  // This should not compile:
  auto non_const_iter = const_iter;
  assert(const_iter == non_const_iter);
}
*/

int main(int /* argc */, char** /* argv */)
{
  gtk_init();
  Gtk::init_gtkmm_internals();

  test_const_conversion();
  test_assignment_from_const();

  return EXIT_SUCCESS;
}
#endif // GTKMM_DISABLE_DEPRECATED
