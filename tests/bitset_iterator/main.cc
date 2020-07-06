#include <gtkmm.h>
#include <gtkmm/init.h>
#include <iostream>
#include <set>

namespace
{

bool success = true;

void test_traversal1()
{
  auto bitset = Gtk::Bitset::create();
  bitset->add_range(200, 5); // Add 200, 201, 202, 203, 204
  bitset->add(42);

  // A std::set with the same elements as bitset.
  std::set<guint> stdset{ 42, 200, 201, 202, 203, 204 };

  for (auto i : *bitset)
  {
    if (!stdset.erase(i))
    {
      success = false;
      std::cerr << "test_traversal1(): Element " << i << " not in stdset\n";
    }
  }
  if (!stdset.empty())
  {
    success = false;
    std::cerr << "test_traversal1(): stdset.size() = " << stdset.size() << " (not empty)\n";
  }
}

void test_traversal2()
{
  auto bitset = Gtk::Bitset::create();
  bitset->add_range(200, 5); // Add 200, 201, 202, 203, 204
  bitset->add(42);

  // A std::set with the same elements as bitset.
  std::set<guint> stdset{ 42, 200, 201, 202, 203, 204 };

  const auto end = bitset->end();
  for (auto it = bitset->begin(); it != end; ++it)
  {
    if (!stdset.erase(*it))
    {
      success = false;
      std::cerr << "test_traversal2(): Element " << *it << " not in stdset\n";
    }
  }
  if (!stdset.empty())
  {
    success = false;
    std::cerr << "test_traversal2(): stdset.size() = " << stdset.size() << " (not empty)\n";
  }
}

void test_copy()
{
  auto bitset = Gtk::Bitset::create();
  bitset->add_range(200, 5); // Add 200, 201, 202, 203, 204
  bitset->add(42);

  auto iter1  = bitset->end();
  if (iter1)
  {
    success = false;
    std::cerr << "test_copy(): iter1 is valid\n";
  }
  --iter1; // Shall point to the last element.
  if (!iter1)
  {
    success = false;
    std::cerr << "test_copy(): iter1 is not valid\n";
  }
  auto iter2 = iter1;
  if (!iter1 || !iter2)
  {
    success = false;
    std::cerr << "test_copy(): (bool)iter1 = " << static_cast<bool>(iter1)
              << " (bool)iter2 = " << static_cast<bool>(iter2) << "\n";
  }
  auto iter3 = std::move(iter1);
  if (iter1 || !iter3)
  {
    success = false;
    std::cerr << "test_copy(): (bool)iter1 = " << static_cast<bool>(iter1)
              << " (bool)iter3 = " << static_cast<bool>(iter3) << "\n";
  }
}

} // anonymous namespace

int main(int /* argc */, char** /* argv */)
{
  gtk_init();
  Gtk::init_gtkmm_internals();

  test_traversal1();
  test_traversal2();
  test_copy();

  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
