
## GTKMM_CXX_HAS_NAMESPACE_STD()
##
## Test whether libstdc++ declares namespace std.  For safety,
## also check whether several randomly selected STL symbols
## are available in namespace std.
##
## On success, #define GTKMM_HAVE_NAMESPACE_STD to 1.
##
AC_DEFUN([GTKMM_CXX_HAS_NAMESPACE_STD],
[
  AC_CACHE_CHECK(
    [whether C++ library symbols are declared in namespace std],
    [gtkmm_cv_cxx_has_namespace_std],
  [
    AC_TRY_COMPILE(
    [
      #include <algorithm>
      #include <iterator>
      #include <iostream>
      #include <string>
    ],[
      using std::min;
      using std::find;
      using std::copy;
      using std::bidirectional_iterator_tag;
      using std::string;
      using std::istream;
      using std::cout;
    ],
      [gtkmm_cv_cxx_has_namespace_std="yes"],
      [gtkmm_cv_cxx_has_namespace_std="no"]
    )
  ])

  if test "x${gtkmm_cv_cxx_has_namespace_std}" = "xyes"; then
  {
    AC_DEFINE([GTKMM_HAVE_NAMESPACE_STD],[1])
  }
  fi
])


## GTKMM_CXX_HAS_STD_ITERATOR_TRAITS()
##
## Check for standard-conform std::iterator_traits<>, and
## #define GTKMM_HAVE_STD_ITERATOR_TRAITS on success.
##
AC_DEFUN([GTKMM_CXX_HAS_STD_ITERATOR_TRAITS],
[
  AC_REQUIRE([GTKMM_CXX_HAS_NAMESPACE_STD])

  AC_CACHE_CHECK(
    [whether the C++ library supports std::iterator_traits],
    [gtkmm_cv_cxx_has_std_iterator_traits],
  [
    AC_TRY_COMPILE(
    [
      #include <iterator>
      #ifdef GTKMM_HAVE_NAMESPACE_STD
      using namespace std;
      #endif
    ],[
      typedef iterator_traits<char*>::value_type ValueType;
    ],
      [gtkmm_cv_cxx_has_std_iterator_traits="yes"],
      [gtkmm_cv_cxx_has_std_iterator_traits="no"]
    )
  ])

  if test "x${gtkmm_cv_cxx_has_std_iterator_traits}" = "xyes"; then
  {
    AC_DEFINE([GTKMM_HAVE_STD_ITERATOR_TRAITS],[1])
  }
  fi
])


## GTKMM_CXX_HAS_SUN_REVERSE_ITERATOR()
##
## Check for Sun libCstd style std::reverse_iterator,
## and #define GTKMM_HAVE_SUN_REVERSE_ITERATOR if found.
##
AC_DEFUN([GTKMM_CXX_HAS_SUN_REVERSE_ITERATOR],
[
  AC_REQUIRE([GTKMM_CXX_HAS_NAMESPACE_STD])

  AC_CACHE_CHECK(
    [for non-standard Sun libCstd reverse_iterator],
    [gtkmm_cv_cxx_has_sun_reverse_iterator],
  [
    AC_TRY_COMPILE(
    [
      #include <iterator>
      #ifdef GTKMM_HAVE_NAMESPACE_STD
      using namespace std;
      #endif
    ],[
      typedef reverse_iterator<char*,random_access_iterator_tag,char,char&,char*,int> ReverseIter;
    ],
      [gtkmm_cv_cxx_has_sun_reverse_iterator="yes"],
      [gtkmm_cv_cxx_has_sun_reverse_iterator="no"]
    )
  ])

  if test "x${gtkmm_cv_cxx_has_sun_reverse_iterator}" = "xyes"; then
  {
    AC_DEFINE([GTKMM_HAVE_SUN_REVERSE_ITERATOR],[1])
  }
  fi
])


## GTKMM_CXX_HAS_TEMPLATE_SEQUENCE_CTORS()
##
## Check whether the STL containers have templated sequence ctors,
## and #define GTKMM_HAVE_TEMPLATE_SEQUENCE_CTORS on success.
##
AC_DEFUN([GTKMM_CXX_HAS_TEMPLATE_SEQUENCE_CTORS],
[
  AC_REQUIRE([GTKMM_CXX_HAS_NAMESPACE_STD])

  AC_CACHE_CHECK(
    [whether STL containers have templated sequence constructors],
    [gtkmm_cv_cxx_has_template_sequence_ctors],
  [
    AC_TRY_COMPILE(
    [
      #include <vector>
      #include <deque>
      #include <list>
      #ifdef GTKMM_HAVE_NAMESPACE_STD
      using namespace std;
      #endif
    ],[
      const int array[8] = { 0, };
      vector<int>  test_vector (&array[0], &array[8]);
      deque<short> test_deque  (test_vector.begin(), test_vector.end());
      list<long>   test_list   (test_deque.begin(),  test_deque.end());
      test_vector.assign(test_list.begin(), test_list.end());
    ],
      [gtkmm_cv_cxx_has_template_sequence_ctors="yes"],
      [gtkmm_cv_cxx_has_template_sequence_ctors="no"]
    )
  ])

  if test "x${gtkmm_cv_cxx_has_template_sequence_ctors}" = "xyes"; then
  {
    AC_DEFINE([GTKMM_HAVE_TEMPLATE_SEQUENCE_CTORS],[1])
  }
  fi
])

