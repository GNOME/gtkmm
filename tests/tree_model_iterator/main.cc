#include <gtkmm.h>
#include <iostream>
#include <cassert>
#include <cstdlib>

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
  Gtk::Main::init_gtkmm_internals();

  test_const_conversion();
  test_assignment_from_const();

  return EXIT_SUCCESS;
}
