dnl Gdk::Event and subclasses is a specific case where a class hierarchhy
dnl refers to a single pointer to a boxed type in the base class.
dnl
dnl Add this to Gdk::Event and subclasses (replace Event and GdkEvent with
dnl the actual name of the class.
dnl
dnl _CLASS_GDKEVENT(Event, GdkEvent)
dnl
dnl Add this to any subclass Gdk::Event. This instructs to use the functionality
dnl of the parent class for copying and destruction (note, that creation of new
dnl events is unsupported). If macro is not defined, gdk_event_copy and
dnl gdk_event_free are used for these purposes. Replace Event and GdkEvent with
dnl the identifiers appearing in _CLASS_GDKEVENT of the base class.
dnl
dnl _CLASS_GDKEVENT_INHERITS(Event, GdkEvent)
dnl

define(`_CLASS_GDKEVENT',`dnl
_PUSH()
dnl
dnl  Define the args for later macros
define(`__CPPNAME__',`$1')
define(`__CNAME__',`$2')

_POP()
_SECTION(SECTION_CLASS2)
') dnl End of _CLASS_GDKEVENT.

define(`_GDKEVENT_INHERITS',`dnl
_PUSH()
dnl Define this macro to be tested for later.
define(`__GDKEVENT_PARENT_CPPNAME__', `$1')
define(`__GDKEVENT_PARENT_CNAME__', `$2')
_POP()
')

dnl
dnl _END_CLASS_GDKEVENT()
dnl   denotes the end of a class
dnl
define(`_END_CLASS_GDKEVENT',`
_SECTION(SECTION_HEADER1)

_SECTION(SECTION_HEADER3)

__NAMESPACE_BEGIN__

/**
 * @relates __NAMESPACE__::__CPPNAME__
 * @param lhs The left-hand side
 * @param rhs The right-hand side
 */
inline void swap(__CPPNAME__& lhs, __CPPNAME__& rhs)
  { lhs.swap(rhs); }

/// @{
/**
 * Wraps a C event instance without making unnecessary copy when the ownership
 * can not be acquired.
 *
 * The @a event pointer must not be deleted until last usage of the returned
 * instance. Note, that this requirement applies to the pointer itself, in
 * addition to the object it is pointing to.
 */
const __CPPNAME__& wrap_event(const __CNAME__*& event);
__CPPNAME__& wrap_event(__CNAME__*& event);
/// @}

__NAMESPACE_END__

namespace Glib {

ifdef(`__BOOL_NO_WRAP_FUNCTION__',`',`dnl else

/**
 * A Glib::wrap() method for this object.
 *
 * @param object The C instance.
 * @param take_copy False if the result should take ownership of the C instance.
 * True if it should take a new copy or ref.
 * @result A C++ instance that wraps this C instance.
 *
 * @relates __NAMESPACE__::__CPPNAME__
 */
__NAMESPACE__::__CPPNAME__ wrap(__CNAME__* object, bool take_copy = false);
')dnl endif __BOOL_NO_WRAP_FUNCTION__

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <>
class Value<__NAMESPACE__::__CPPNAME__> : public Glib::Value_Boxed<__NAMESPACE__::__CPPNAME__>
{};
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

} // namespace Glib

_SECTION(SECTION_SRC_GENERATED)

ifdef(`__BOOL_NO_WRAP_FUNCTION__',`',`dnl else
namespace Glib
{

__NAMESPACE__::__CPPNAME__ wrap(__CNAME__* object, bool take_copy)
{
  return __NAMESPACE__::__CPPNAME__`'(object, take_copy);
}

} // namespace Glib
')dnl endif


__NAMESPACE_BEGIN__

dnl
dnl The implementation:
dnl

dnl All events have the same GType
// static
GType __CPPNAME__::get_type()
{
  return gdk_event_get_type();
}

__CPPNAME__::__CPPNAME__`'()
:
ifdef(`__GDKEVENT_PARENT_CPPNAME__',`dnl
  __GDKEVENT_PARENT_CPPNAME__`'()
',`dnl else
  gobject_(nullptr)
')dnl endif
{
}

__CPPNAME__::__CPPNAME__`'(__CNAME__* gobject, bool make_a_copy)
:
  // For Event wrappers, make_a_copy is false by default.  The static
  // Event wrappers must not take a copy, thus make_a_copy = false
  // ensures identical behaviour if the default argument is used.
ifdef(`__GDKEVENT_PARENT_CPPNAME__',`dnl
  __GDKEVENT_PARENT_CPPNAME__`'(reinterpret_cast<__GDKEVENT_PARENT_CNAME__*>(gobject), make_a_copy)
',`dnl else
  gobject_((make_a_copy && gobject) ? gdk_event_copy(gobject) : gobject)
')dnl endif
{}

ifdef(`__GDKEVENT_PARENT_CPPNAME__',`',`dnl We need those functions only for Gdk::Event

__CPPNAME__::__CPPNAME__`'(const __CPPNAME__& other)
:
  gobject_((other.gobject_) ? gdk_event_copy(other.gobject_) : nullptr)
{}

__CPPNAME__& __CPPNAME__::operator=(const __CPPNAME__`'& other)
{
  __CPPNAME__ temp(other);
  swap(temp);
  return *this;
}

__CPPNAME__::~__CPPNAME__`'()
{
  if(gobject_) {
    gdk_event_free(gobject_);
  }
}
')dnl endif

void __CPPNAME__::swap(__CPPNAME__& other)
{
ifdef(`__GDKEVENT_PARENT_CPPNAME__',`dnl
  __GDKEVENT_PARENT_CPPNAME__::swap(other);
',`dnl else
  __CNAME__ *const temp = gobject_;
  gobject_ = other.gobject_;
  other.gobject_ = temp;
')dnl endif
}

__CNAME__* __CPPNAME__::gobj_copy() const
{
ifdef(`__GDKEVENT_PARENT_CPPNAME__',`dnl
  return reinterpret_cast<__CNAME__*>(__GDKEVENT_PARENT_CPPNAME__::gobj_copy());
',`dnl else
  return gdk_event_copy(gobject_);
')dnl endif
}

const __CPPNAME__& wrap_event(const __CNAME__*& event)
{
  return reinterpret_cast<const __CPPNAME__&>(*event);
}

__CPPNAME__& wrap_event(__CNAME__*& event)
{
  return reinterpret_cast<__CPPNAME__&>(*event);
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
  typedef __CPPNAME__ CppObjectType;
  typedef __CNAME__ BaseObjectType;

  static GType get_type() G_GNUC_CONST;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

ifdef(`__GDKEVENT_PARENT_CPPNAME__',`', `dnl else Only add for Gdk::Event
private:
  __CNAME__* gobject_;
public:
')dnl endif

  /**
   * Creates an invalid event object. Calling any member functions is undefined
   * behavior.
   */
  __CPPNAME__`'();

  /**
   * Wraps a C event instance. This constructor either acquires ownership of
   * @c gobject, or copies it.
   *
   * @param gobject Event to wrap
   * @param make_a_copy if @c false, the ownership of @c gobject is acquired,
   *        otherwise, a copy is made.
   */
  explicit __CPPNAME__`'(__CNAME__* gobject, bool make_a_copy = false);

ifdef(`__GDKEVENT_PARENT_CPPNAME__',`', `dnl else Only add for Gdk::Event

  __CPPNAME__`'(const __CPPNAME__& other);
  __CPPNAME__& operator=(const __CPPNAME__& other);

_IMPORT(SECTION_DTOR_DOCUMENTATION)
  ~__CPPNAME__`'();

')dnl endif

  void swap(__CPPNAME__& other);

ifdef(`__GDKEVENT_PARENT_CPPNAME__',`dnl
  /// Provides access to the underlying C instance.
  __CNAME__*       gobj()       { return reinterpret_cast<__CNAME__*>(__GDKEVENT_PARENT_CPPNAME__::gobj()); }

  /// Provides access to the underlying C instance.
  const __CNAME__* gobj() const { return reinterpret_cast<const __CNAME__*>(__GDKEVENT_PARENT_CPPNAME__::gobj()); }
',`dnl else
  ///Provides access to the underlying C instance.
  __CNAME__*       gobj()       { return gobject_; }

  ///Provides access to the underlying C instance.
  const __CNAME__* gobj() const { return gobject_; }
')dnl endif
  /**
   * Provides access to the underlying C instance. The caller is responsible for
   * freeing it with @c gdk_event_free. Use when directly setting fields in structs.
   */
  __CNAME__* gobj_copy() const;

private:
_IMPORT(SECTION_CLASS2)
')
