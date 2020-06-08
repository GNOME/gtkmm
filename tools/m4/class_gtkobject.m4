dnl $Id$

define(`_CLASS_GTKOBJECT',`dnl
_PUSH()
dnl
dnl  Define the args for later macros
define(`__CPPNAME__',`$1')
define(`__CNAME__',`$2')
define(`__CCAST__',`$3')
define(`__BASE__',_LOWER(__CPPNAME__))
define(`__CPPPARENT__',`$4')
define(`__CPARENT__',`$5')
define(`__PCAST__',`($5*)')

dnl Some C types, e.g. GdkWindow or GdkPixmap, are a typedef to their base type,
dnl rather than the real instance type.  That is really ugly, yes.  We get around
dnl the problem by supporting optional __REAL_* arguments to this macro.
define(`__REAL_CNAME__',ifelse(`$6',,__CNAME__,`$6'))
define(`__REAL_CPARENT__',ifelse(`$7',,__CPARENT__,`$7'))
define(`__FUNC_DECORATION__',`$8')


dnl
dnl ----------------------- Constructors -------------------------
dnl


_POP()
_SECTION(SECTION_CLASS2)
')dnl end of _CLASS_GTKOBJECT

dnl Widget and Object, and some others, have custom-written destructor implementations:
define(`_CUSTOM_DTOR',`dnl
_PUSH()
dnl Define this macro to be tested for later.
define(`__BOOL_CUSTOM_DTOR__',`$1')
_POP()
')

dnl For classes that need custom code for move operations.
define(`_CUSTOM_MOVE_OPERATIONS', `dnl
_PUSH()
dnl Define this macro to be tested for later.
define(`__BOOL_CUSTOM_MOVE_OPERATIONS__',`$1')
_POP()
')

dnl For classes that need custom code in their cast and construct_params
dnl constructors.
define(`_CUSTOM_CTOR_CAST',`dnl
_PUSH()
dnl Define this macro to be tested for later.
define(`__BOOL_CUSTOM_CTOR_CAST__',`$1')
_POP()
')

dnl Top-level windows can not be manage()ed, so we should not use manage() in wrap_new().
define(`_UNMANAGEABLE',`dnl
_PUSH()
dnl Define this macro to be tested for later.
define(`__BOOL_UNMANAGEABLE__',`$1')
_POP()
')

dnl Optionally ifdef-out the whole .h and .cc files:
define(`_IS_DEPRECATED',`dnl
_PUSH()
dnl Define this macro to be tested for later.
define(`__BOOL_DEPRECATED__',`$1')
_POP()
')

dnl Gnome::Canvas::CanvasAA::CanvasAA() needs access to the
dnl normally-private canvas_class_ member variable. See comments there.
define(`_GMMPROC_PROTECTED_GCLASS',`dnl
_PUSH()
dnl Define this macro to be tested for later.
define(`__BOOL_PROTECTED_GCLASS__',`1')
_POP()
')

dnl In case a class needs to write its own declaration and implementation of
dnl its Glib::wrap() function, or it does not need a wrap() function.
define(`_NO_WRAP_FUNCTION',`dnl
_PUSH()
dnl Define this macro to be tested for later.
define(`__BOOL_NO_WRAP_FUNCTION__',`$1')
_POP()
')

dnl In case a class needs to write its own implementation of its Glib::wrap()
dnl function. The function will be declared in the header, but the body is not
dnl generated.
define(`_CUSTOM_WRAP_FUNCTION',`dnl
_PUSH()
dnl Define this macro to be tested for later.
define(`__BOOL_CUSTOM_WRAP_FUNCTION__',`$1')
_POP()
')


dnl
dnl _END_CLASS_GTKOBJECT()
dnl   denotes the end of a class
dnl
define(`_END_CLASS_GTKOBJECT',`

_SECTION(SECTION_HEADER1)
dnl _END_CLASS_GOBJECT does not call _STRUCT_PROTOTYPE(), if __BOOL_NO_WRAP_FUNCTION__
dnl is defined. That may not always be appropriate, and if necessary
dnl _STRUCT_PROTOTYPE() can be disabled with _STRUCT_NOT_HIDDEN.
_STRUCT_PROTOTYPE()

#ifndef DOXYGEN_SHOULD_SKIP_THIS
__NAMESPACE_BEGIN__ class __FUNC_DECORATION__ __CPPNAME__`'_Class; __NAMESPACE_END__
#endif //DOXYGEN_SHOULD_SKIP_THIS

_SECTION(SECTION_HEADER3)

ifdef(`__BOOL_NO_WRAP_FUNCTION__',`dnl
',`dnl
namespace Glib
{
  /** A Glib::wrap() method for this object.
   *
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates __NAMESPACE__::__CPPNAME__
   */
  __FUNC_DECORATION__
  __NAMESPACE__::__CPPNAME__`'* wrap(__CNAME__`'* object, bool take_copy = false);
} //namespace Glib
')dnl endif __BOOL_NO_WRAP_FUNCTION__

dnl
dnl
_SECTION(SECTION_PHEADER)

#include <glibmm/class.h>

__NAMESPACE_BEGIN__

_PH_CLASS_DECLARATION()

__NAMESPACE_END__

_SECTION(SECTION_SRC_GENERATED)

ifdef(`__BOOL_CUSTOM_WRAP_FUNCTION__',`dnl
',`dnl else
ifdef(`__BOOL_NO_WRAP_FUNCTION__',`dnl
',`dnl else
namespace Glib
{

__NAMESPACE__::__CPPNAME__`'* wrap(__CNAME__`'* object, bool take_copy)
{
  return dynamic_cast<__NAMESPACE__::__CPPNAME__ *> (Glib::wrap_auto ((GObject*)(object), take_copy));
}

} /* namespace Glib */
')dnl endif __BOOL_NO_WRAP_FUNCTION__
')dnl endif __BOOL_CUSTOM_WRAP_FUNCTION__

__NAMESPACE_BEGIN__


/* The *_Class implementation: */

_PCC_CLASS_IMPLEMENTATION()

Glib::ObjectBase* __CPPNAME__`'_Class::wrap_new(GObject* o)
{
ifdef(`__BOOL_UNMANAGEABLE__',`dnl
  return new __CPPNAME__`'((__CNAME__*)`'(o)); //top-level windows can not be manage()ed.
',`dnl
  return manage(new __CPPNAME__`'((__CNAME__*)`'(o)));
')
}


/* The implementation: */

ifdef(`__BOOL_CUSTOM_CTOR_CAST__',`dnl necessary for Gtk::Object implementation
',`dnl
__CPPNAME__::__CPPNAME__`'(const Glib::ConstructParams& construct_params)
:
  __CPPPARENT__`'(construct_params)
{
  _IMPORT(SECTION_CC_INITIALIZE_CLASS_EXTRA) dnl Does not seem to work - custom implement it instead.
}

__CPPNAME__::__CPPNAME__`'(__CNAME__* castitem)
:
  __CPPPARENT__`'(__PCAST__`'(castitem))
{
  _IMPORT(SECTION_CC_INITIALIZE_CLASS_EXTRA)  dnl Does not seem to work - custom implement it instead.
}

')dnl

ifdef(`__BOOL_CUSTOM_MOVE_OPERATIONS__',`dnl
',`dnl
__CPPNAME__::__CPPNAME__`'(__CPPNAME__&& src) noexcept
: __CPPPARENT__`'(std::move(src))
_IMPORT(SECTION_CC_MOVE_CONSTRUCTOR_INTERFACES)
{}

__CPPNAME__& __CPPNAME__::operator=(__CPPNAME__&& src) noexcept
{
  __CPPPARENT__::operator=`'(std::move(src));
_IMPORT(SECTION_CC_MOVE_ASSIGNMENT_OPERATOR_INTERFACES)
  return *this;
}
')dnl

ifdef(`__BOOL_CUSTOM_DTOR__',`dnl
',`dnl
__CPPNAME__::~__CPPNAME__`'() noexcept
{
  destroy_();
}

')dnl
_CC_CLASS_IMPLEMENTATION()

__NAMESPACE_END__

dnl
dnl
dnl
dnl
_POP()
dnl The actual class, e.g. Gtk::Widget, declaration:
dnl _IMPORT(SECTION_H_SIGNALPROXIES_CUSTOM)

_IMPORT(SECTION_CLASS1)
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef __CPPNAME__ CppObjectType;
  typedef __CPPNAME__`'_Class CppClassType;
  typedef __CNAME__ BaseObjectType;
  typedef __REAL_CNAME__`'Class BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

ifdef(`__BOOL_CUSTOM_MOVE_OPERATIONS__',`dnl
',`dnl
  __CPPNAME__`'(__CPPNAME__&& src) noexcept;
  __CPPNAME__& operator=(__CPPNAME__&& src) noexcept;
')dnl

  // noncopyable
  __CPPNAME__`'(const __CPPNAME__&) = delete;
  __CPPNAME__& operator=(const __CPPNAME__&) = delete;

_IMPORT(SECTION_DTOR_DOCUMENTATION)
  ~__CPPNAME__`'() noexcept override;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

m4_ifdef(`__BOOL_PROTECTED_GCLASS__',
`protected:',`dnl else
private:')dnl endif

  friend __FUNC_DECORATION__ class __CPPNAME__`'_Class;
  static CppClassType `'__BASE__`'_class_;

protected:
  explicit __CPPNAME__`'(const Glib::ConstructParams& construct_params);
  explicit __CPPNAME__`'(__CNAME__* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
ifdef(`__BOOL_DYNAMIC_GTYPE_REGISTRATION__',`
  static GType get_type(GTypeModule* module)      G_GNUC_CONST;
',`')

  static GType get_base_type() G_GNUC_CONST;
#endif

  /// Provides access to the underlying C GObject.
  __CNAME__*       gobj()       { return reinterpret_cast<__CNAME__*>(gobject_); }

  /// Provides access to the underlying C GObject.
  const __CNAME__* gobj() const { return reinterpret_cast<__CNAME__*>(gobject_); }

private:
_IMPORT(SECTION_CLASS2)

public:
_H_VFUNCS_AND_SIGNALS()

')
