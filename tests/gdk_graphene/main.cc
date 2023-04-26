// Test Gdk::Graphene

#include <gdkmm/graphene_rect.h>
#include <glib.h>

int main()
{
  Gdk::Graphene::Point p1;
  g_assert_false(p1);
  Gdk::Graphene::Point p2(3, 4);
  p1 = p2;
  g_assert_cmpfloat(p1.get_x(), ==, 3.0f);
  g_assert_cmpfloat(p1.get_y(), ==, 4.0f);
  p2.set_x(3.1f);
  g_assert_false(p1.near(p2, 0.05f));
  g_assert_true(p1.near(p2, 0.15f));

  Gdk::Graphene::Size s1;
  g_assert_false(s1);
  Gdk::Graphene::Size s2(5, 6);
  s1 = s2;
  g_assert_cmpfloat(s1.get_width(), ==, 5.0f);
  g_assert_cmpfloat(s1.get_height(), ==, 6.0f);

  Gdk::Graphene::Rect r1(10, 20, -2, -3);
  Gdk::Graphene::Rect r2 = r1;
  r2.normalize();
  g_assert_cmpfloat(r2.get_x(), ==, 8.0f);
  g_assert_cmpfloat(r2.get_y(), ==, 17.0f);
  g_assert_cmpfloat(r2.get_width(), ==, 2.0f);
  g_assert_cmpfloat(r2.get_height(), ==, 3.0f);
  g_assert_cmpfloat(r2.get_area(), ==, 6.0f);
  g_assert_false(r2.contains_point(p2));
  g_assert_true(r2.contains_point(Gdk::Graphene::Point(8.5f, 18.0f)));
  g_assert_false(r2.contains_rect(Gdk::Graphene::Rect(1, 2, 3, 4)));
  g_assert_true(Gdk::Graphene::Rect(7, 16, 4, 5).contains_rect(r2));

  auto p3 = r2.get_origin();
  auto s3 = r2.get_size();
  g_assert_cmpfloat(p3.get_x(), ==, 8.0f);
  g_assert_cmpfloat(p3.get_y(), ==, 17.0f);
  g_assert_cmpfloat(s3.get_width(), ==, 2.0f);
  g_assert_cmpfloat(s3.get_height(), ==, 3.0f);
  r2.set_origin(p1);
  r2.set_size(s1);
  g_assert_cmpfloat(r2.get_top_left().get_x(), ==, 3.0f);
  g_assert_cmpfloat(r2.get_top_right().get_y(), ==, 4.0f);
  g_assert_cmpfloat(r2.get_bottom_left().get_y(), ==, 10.0f);
  g_assert_cmpfloat(r2.get_bottom_right().get_x(), ==, 8.0f);
  
  return 0;
}
