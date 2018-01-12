dnl Gdk::Event and subclasses is a specific case where a class hierarchy
dnl refers to a single pointer to a GObject type in the base class.
dnl
dnl Add this to Gdk::Event (Replace Event, GdkEvent and GDK_EVENT with
dnl the actual name of the class.)
dnl
dnl _CLASS_GOBJECT(Event, GdkEvent, GDK_EVENT, Glib::Object, GObject)
dnl
dnl Add this to any subclass of Gdk::Event. This instructs to use the functionality
dnl of the parent class for copying and destruction (note, that creation of new
dnl events is unsupported). Replace EventKey and GdkEventKey with the actual
dnl name of the class, and Event and GdkEvent with the name of the base class.
dnl
dnl _CLASS_GDKEVENT(EventKey, GdkEventKey, Event, GdkEvent)
dnl _CLASS_GDKEVENT(C++ class, C class, C++ base class, C base class)
dnl

define(`_CLASS_GDKEVENT',`dnl
_PUSH()
dnl
dnl  Define the args for later macros
define(`__CPPNAME__',`$1')
define(`__CNAME__',`$2')
define(`__CPPPARENT__',`$3')
define(`__CPARENT__',`$4')
_POP()
_SECTION(SECTION_CLASS2)
') dnl End of _CLASS_GDKEVENT.

dnl
dnl _END_CLASS_GDKEVENT()
dnl   denotes the end of a class
dnl
define(`_END_CLASS_GDKEVENT',`
_SECTION(SECTION_HEADER3)

ifdef(`__BOOL_NO_WRAP_FUNCTION__',`',`dnl else
namespace Glib
{

/** A Glib::wrap() method for this object.
 *
 * @param object The C instance.
 * @param take_copy @c false if the result should take ownership of the C instance.
 *        @c true if it should take a new copy or ref.
 * @result A C++ instance that wraps this C instance.
 *
 * @relates __NAMESPACE__::__CPPNAME__
 */
Glib::RefPtr<__NAMESPACE__::__CPPNAME__> wrap(__CNAME__* object, bool take_copy = false);

} // namespace Glib
')dnl endif __BOOL_NO_WRAP_FUNCTION__

_SECTION(SECTION_SRC_GENERATED)

ifdef(`__BOOL_NO_WRAP_FUNCTION__',`',`dnl else
namespace Glib
{

Glib::RefPtr<__NAMESPACE__::__CPPNAME__> wrap(__CNAME__* object, bool take_copy)
{
  return std::static_pointer_cast<__NAMESPACE__::__CPPNAME__>(wrap((__CPARENT__*)object, take_copy));
}

} // namespace Glib
')dnl endif

__NAMESPACE_BEGIN__

dnl
dnl The implementation:
dnl

dnl All events have the same GType. Only the base class need a get_type() method.

__CNAME__* __CPPNAME__::gobj_copy()
{
  reference();
  return gobj();
}

_IMPORT(SECTION_CC)

__NAMESPACE_END__

dnl
dnl
_POP()
dnl
dnl The actual class declaration:
dnl
_IMPORT(SECTION_CLASS1)
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  using CppObjectType = __CPPNAME__;
  using BaseObjectType = __CNAME__;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  /// Provides access to the underlying C instance.
  __CNAME__* gobj() noexcept { return reinterpret_cast<__CNAME__*>(__CPPPARENT__::gobj()); }

  /// Provides access to the underlying C instance.
  const __CNAME__* gobj() const noexcept { return reinterpret_cast<const __CNAME__*>(__CPPPARENT__::gobj()); }

  /** Provides access to the underlying C instance.
   * The caller is responsible for unrefing it with g_object_unref().
   * Use when directly setting fields in structs.
   */
  __CNAME__* gobj_copy();

private:
_IMPORT(SECTION_CLASS2)
')
