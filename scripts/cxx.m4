
dnl
dnl AC_CXX_NAMESPACES(ACTION_FOUND,ACTION_NOT_FOUND)
dnl
AC_DEFUN([AC_CXX_NAMESPACES],[
AC_MSG_CHECKING(if C++ compiler supports namespaces)
AC_TRY_COMPILE(
[
namespace Foo { struct A {}; }
using namespace Foo;
],[
A a;
],[
 ac_cxx_namespaces=yes
 AC_MSG_RESULT([$ac_cxx_namespaces])
 $1
],[
 ac_cxx_namespaces=no
 AC_MSG_RESULT([$ac_cxx_namespaces])
 $2
])
])

dnl
dnl AC_CXX_NAMESPACES(ACTION_FOUND,ACTION_NOT_FOUND)
dnl
AC_DEFUN([AC_CXX_BOOL],[
AC_MSG_CHECKING(if C++ compiler supports bool)
AC_TRY_COMPILE(
[
],[
   bool b=true;
   bool b1=false;
],[
  ac_cxx_bool=yes
  AC_MSG_RESULT([$ac_cxx_bool])
  $1
],[
  ac_cxx_bool=no
  AC_MSG_RESULT([$ac_cxx_bool])
  $2
])
])

dnl
dnl AC_CXX_MUTABLE(ACTION_FOUND,ACTION_NOT_FOUND)
dnl
AC_DEFUN([AC_CXX_MUTABLE],[
AC_MSG_CHECKING(if C++ compiler supports mutable)
AC_TRY_COMPILE(
[
class k {   
  mutable char *c;
public:
   void foo() const { c=0; }
};
],[
],[
  ac_cxx_mutable=yes
  AC_MSG_RESULT([$ac_cxx_mutable])
  $1
],[
  ac_cxx_mutable=no
  AC_MSG_RESULT([$ac_cxx_mutable])
  $2
]) 
])


dnl
dnl AC_CXX_CONST_CAST(ACTION_FOUND,ACTION_NOT_FOUND)
dnl
AC_DEFUN([AC_CXX_CONST_CAST],[
AC_MSG_CHECKING([if C++ compiler supports const_cast<>])
AC_TRY_COMPILE(
[
   class foo;
],[
   const foo *c=0;
   foo *c1=const_cast<foo*>(c);
],[
  ac_cxx_const_cast=yes
  AC_MSG_RESULT([$ac_cxx_const_cast])
],[
  ac_cxx_const_cast=no
  AC_MSG_RESULT([$ac_cxx_const_cast])
])
])


dnl
dnl GTKMM_CXX_MEMBER_FUNCTIONS_MEMBER_TEMPLATES(ACTION_FOUND,ACTION_NOT_FOUND)
dnl
dnl Test whether the compiler allows member functions to refer to spezialized member function templates.
dnl Some compilers have problems with this. gcc 2.95.3 aborts with an internal compiler error.
dnl
AC_DEFUN([GTKMM_CXX_MEMBER_FUNCTIONS_MEMBER_TEMPLATES],[
AC_MSG_CHECKING([if C++ compiler allows member functions to refer to member templates])
AC_TRY_COMPILE(
[
  struct foo {
    template <class C> inline
    void doit();
    void thebug();
  };

  template <class C> inline
  void foo::doit() {
  }

  struct bar {
    void neitherabug();
  };

  void notabug() {
    void (foo::*func)();
    func = &foo::doit<int>;
  }

  void bar::neitherabug() {
    void (foo::*func)();
    func = &foo::doit<int>;
  }

  void foo::thebug() {
    void (foo::*func)();
    func = &foo::doit<int>; //Compiler bugs usually show here.
  }
],[],[
  gtkmm_cxx_member_functions_member_templates=yes
  AC_DEFINE([GTKMM_MEMBER_FUNCTIONS_MEMBER_TEMPLATES],[1],[does the C++ compiler allow member functions to refer to member templates])
  AC_MSG_RESULT([$gtkmm_cxx_member_functions_member_templates])
],[
  gtkmm_cxx_member_functions_member_templates=no
  AC_DEFINE([GTKMM_MEMBER_FUNCTIONS_MEMBER_TEMPLATES],[0])
  AC_MSG_RESULT([$gtkmm_cxx_member_functions_member_templates])
])
])


