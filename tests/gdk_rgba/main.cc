#include <gdkmm/rgba.h>
#include <glib.h>

int
main()
{
  // A default-constructed RGBA is black and fully transparent
  auto rgba = Gdk::RGBA{};
  g_assert_cmpfloat(rgba.get_red  (), ==, 0.0);
  g_assert_cmpfloat(rgba.get_green(), ==, 0.0);
  g_assert_cmpfloat(rgba.get_blue (), ==, 0.0);
  g_assert_cmpfloat(rgba.get_alpha(), ==, 0.0);

  // Test that when passing r,g,b the alpha defaults to 1
  rgba.set_rgba(0.0, 0.0, 0.0);
  g_assert_cmpfloat(rgba.get_alpha(), ==, 1.0);

  // Test our get_*_u(). Note only the min/max `u`s are reliable due to rounding
  g_assert_cmpint(rgba.get_red_u  (), ==, 0x0000);
  g_assert_cmpint(rgba.get_green_u(), ==, 0x0000);
  g_assert_cmpint(rgba.get_blue_u (), ==, 0x0000);
  g_assert_cmpint(rgba.get_alpha_u(), ==, 0xFFFF);

  // Test our set_*_u()
  rgba.set_rgba(1.0, 1.0, 1.0, 1.0);
  auto rgba2 = Gdk::RGBA{};
  rgba2.set_rgba_u(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
  g_assert_true(rgba == rgba2);

  // and set_grey*()
  rgba2.set_grey(1.0, 1.0);
  g_assert_true(rgba == rgba2);
  rgba2.set_grey_u(0xFFFF, 0xFFFF);
  g_assert_true(rgba == rgba2);

  // Test that hues 0° and 360° both result in red, fixed in GitLab Issue #42
  rgba.set_hsv(0.0, 1.0, 1.0);
  g_assert_cmpfloat(rgba.get_red  (), ==, 1.0);
  g_assert_cmpfloat(rgba.get_green(), ==, 0.0);
  g_assert_cmpfloat(rgba.get_blue (), ==, 0.0);
  g_assert_cmpfloat(rgba.get_alpha(), ==, 1.0);
  rgba2.set_hsv(360.0, 1.0, 1.0);
  g_assert_true(rgba == rgba2);

  // Test HSL the same way
  rgba2.set_hsl(0.0, 1.0, 0.5);
  g_assert_true(rgba == rgba2);
  rgba2.set_hsl(360.0, 1.0, 0.5);
  g_assert_true(rgba == rgba2);

  return 0;
}
