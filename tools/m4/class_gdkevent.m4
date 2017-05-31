dnl Gdk::Event and subclasses is a specific case where a class hierarchy
dnl refers to a single pointer to a boxed type in the base class.
dnl
dnl Add this to Gdk::Event (Replace Event and GdkEvent with the actual name
dnl of the class.)
dnl
dnl _CLASS_GDKEVENT(Event, GdkEvent)
dnl
dnl Add this to any subclass Gdk::Event. This instructs to use the functionality
dnl of the parent class for copying and destruction (note, that creation of new
dnl events is unsupported). With only two parameters, gdk_event_copy and
dnl gdk_event_free are used for these purposes. Replace EventKey and GdkEventKey
dnl with the actual name of the class, and Event and GdkEvent with the name of
dnl the base class.
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

__NAMESPACE_BEGIN__

/**
 * @param lhs The left-hand side
 * @param rhs The right-hand side
 *
 * @relates __NAMESPACE__::__CPPNAME__
 */
inline void swap(__CPPNAME__& lhs, __CPPNAME__& rhs) noexcept
  { lhs.swap(rhs); }

/** Wraps a C event instance without making unnecessary copy when the ownership
 * can not be acquired.
 *
 * The @a event pointer must not be deleted until last usage of the returned
 * instance. Note, that this requirement applies to the pointer itself, in
 * addition to the object it is pointing to.
 *
 * @relates __NAMESPACE__::__CPPNAME__
 */
const __CPPNAME__& wrap_event(const __CNAME__*& event);

/** See wrap_event(const __CNAME__*& event).
 *
 * @relates __NAMESPACE__::__CPPNAME__
 */
__CPPNAME__& wrap_event(__CNAME__*& event);

__NAMESPACE_END__

namespace Glib
{
ifdef(`__BOOL_NO_WRAP_FUNCTION__',`',`dnl else

/** A Glib::wrap() method for this object.
 *
 * @param object The C instance.
 * @param take_copy @c false if the result should take ownership of the C instance,
 *        @c true if it should take a new copy.
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

dnl All events have the same GType. Only the base class need a get_type() method.
ifelse(__CPPPARENT__,,`dnl
// static
GType __CPPNAME__::get_type()
{
  return _GET_TYPE_FUNC(__CNAME__);
}
')dnl endif not __CPPPARENT__

__CPPNAME__::__CPPNAME__`'()
:
ifelse(__CPPPARENT__,,`dnl base class
  gobject_(nullptr)
',`dnl else, i.e. subclass
  __CPPPARENT__`'()
')dnl endif
{
}

__CPPNAME__::__CPPNAME__`'(__CNAME__* gobject, bool make_a_copy)
:
ifelse(__CPPPARENT__,,`dnl base class
  gobject_((make_a_copy && gobject) ? gdk_event_copy(gobject) : gobject)
',`dnl else i.e. subclass
  __CPPPARENT__`'(reinterpret_cast<__CPARENT__*>(gobject), make_a_copy)
')dnl endif
{}

ifelse(__CPPPARENT__,`',`dnl We need those functions only for Gdk::Event

__CPPNAME__::__CPPNAME__`'(const __CPPNAME__& other)
:
  gobject_((other.gobject_) ? gdk_event_copy(other.gobject_) : nullptr)
{}

__CPPNAME__::__CPPNAME__`'(__CPPNAME__&& other) noexcept
:
  gobject_(other.gobject_)
{
  other.gobject_ = nullptr;
}

__CPPNAME__& __CPPNAME__::operator=(const __CPPNAME__`'& other)
{
  __CPPNAME__ temp(other);
  swap(temp);
  return *this;
}

__CPPNAME__& __CPPNAME__::operator=(__CPPNAME__`'&& other) noexcept
{
  __CPPNAME__ temp(std::move(other));
  swap(temp);
  return *this;
}

__CPPNAME__::~__CPPNAME__`'() noexcept
{
  if (gobject_)
    gdk_event_free(gobject_);
}
')dnl endif not __CPPPARENT__

void __CPPNAME__::swap(__CPPNAME__& other) noexcept
{
ifelse(__CPPPARENT__,,`dnl base class
  __CNAME__ *const temp = gobject_;
  gobject_ = other.gobject_;
  other.gobject_ = temp;
',`dnl else i.e. subclass
  __CPPPARENT__::swap(other);
')dnl endif
}

__CNAME__* __CPPNAME__::gobj_copy() const
{
ifelse(__CPPPARENT__,,`dnl base class
  return gdk_event_copy(gobject_);
',`dnl else i.e. subclass
  return reinterpret_cast<__CNAME__*>(__CPPPARENT__::gobj_copy());
')dnl endif
}

// The reinterpret_cast works because __CPPNAME__ is a standard-layout class
// whose only data member is a ifelse(__CPARENT__,,`__CNAME__',`__CPARENT__') pointer.
const __CPPNAME__& wrap_event(const __CNAME__*& event)
{
  return reinterpret_cast<const __CPPNAME__&>(event);
}

__CPPNAME__& wrap_event(__CNAME__*& event)
{
  return reinterpret_cast<__CPPNAME__&>(event);
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

ifelse(__CPPPARENT__,,`dnl base class
  /// Get the GType for this class, for use with the underlying GObject type system.
  static GType get_type() G_GNUC_CONST;
')dnl

  /** Creates an invalid event object.
   * Calling any member functions other than operator bool() is undefined behavior.
   * An invalid event object can be used in a function call, if the underlying
   * C function expects a NULL __CNAME__ pointer.
   */
  __CPPNAME__`'();

  /** Wraps a C event instance.
   * This constructor either acquires ownership of @a gobject, or copies it.
   *
   * @param gobject %Event to wrap.
   * @param make_a_copy If @c false, the ownership of @a gobject is acquired,
   *        otherwise a copy is made.
   */
  explicit __CPPNAME__`'(__CNAME__* gobject, bool make_a_copy = false);
ifelse(__CPPPARENT__,`',`dnl Only add for Gdk::Event

  __CPPNAME__`'(const __CPPNAME__& other);
  __CPPNAME__& operator=(const __CPPNAME__& other);

  __CPPNAME__`'(__CPPNAME__&& other) noexcept;
  __CPPNAME__& operator=(__CPPNAME__&& other) noexcept;

_IMPORT(SECTION_DTOR_DOCUMENTATION)
  ~__CPPNAME__`'() noexcept;
')dnl endif

  void swap(__CPPNAME__& other) noexcept;

ifelse(__CPPPARENT__,,`dnl
  /// Provides access to the underlying C instance.
  __CNAME__* gobj() noexcept { return gobject_; }

  /// Provides access to the underlying C instance.
  const __CNAME__* gobj() const noexcept { return gobject_; }
',`dnl else
  /// Provides access to the underlying C instance.
  __CNAME__* gobj() noexcept { return reinterpret_cast<__CNAME__*>(__CPPPARENT__::gobj()); }

  /// Provides access to the underlying C instance.
  const __CNAME__* gobj() const noexcept { return reinterpret_cast<const __CNAME__*>(__CPPPARENT__::gobj()); }
')dnl endif

  /** Provides access to the underlying C instance.
   * The caller is responsible for freeing it with gdk_event_free().
   * Use when directly setting fields in structs.
   */
  __CNAME__* gobj_copy() const;

private:
ifelse(__CPPPARENT__,`',`dnl Only add for Gdk::Event
  __CNAME__* gobject_;
')dnl
_IMPORT(SECTION_CLASS2)
')
