#include <gtkmm.h>
#include <gtkmm/init.h>
#include <cassert>
#include <cstdlib>

void test_try_expression()
{
  auto expr1 = Gtk::ConstantExpression<int>::create(1);
  auto expr2 = Gtk::ConstantExpression<int>::create(2);
  std::vector<Glib::RefPtr<Gtk::Expression<int>>> expressions {expr1, expr2};
  auto try_expr = Gtk::TryExpression<int>::create(expressions);
  assert(try_expr.get() != nullptr);
  auto value = try_expr->evaluate({});
  assert(value == 1);

  try_expr.reset();
  // Check that expr1 and expr2 are still alive after try_expr has been deleted.
  value = expr1->evaluate({});
  assert(value == 1);
  value = expr2->evaluate({});
  assert(value == 2);
}

int main(int /* argc */, char** /* argv */)
{
  gtk_init();
  Gtk::init_gtkmm_internals();

  //TODO: Add tests for other types of expressions.
  test_try_expression();

  return EXIT_SUCCESS;
}
