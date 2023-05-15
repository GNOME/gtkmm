dnl This is a copy of a file in glibmm.
dnl This version of the file is available in glibmm > 2.72.1.
dnl It can be deleted from gtkmm, when gtkmm requires glibmm > 2.72.1.
dnl It shall not be included from convert_gtkmm.m4.
dnl It's included from glibmm/tools/m4/base.m4.

dnl This is just a hint to generate_wrap_init.pl.
dnl It does not generate any code in the actual .h and .cc file.
m4_define(`_GMMPROC_EXTRA_NAMESPACE',`')

define(`_CLASS_START',`dnl
_PUSH(SECTION_CLASS1)
')

dnl
dnl
dnl
define(`_H_VFUNCS_AND_SIGNALS',`dnl

public:
  //C++ methods used to invoke GTK+ virtual functions:
_IMPORT(SECTION_H_VFUNCS_CPPWRAPPER)

protected:
  //GTK+ Virtual Functions (override these to change behaviour):
_IMPORT(SECTION_H_VFUNCS)

  //Default Signal Handlers::
_IMPORT(SECTION_H_DEFAULT_SIGNAL_HANDLERS)
')


dnl
dnl
dnl
define(`_IMPLEMENTS_INTERFACE_CC',`dnl
_PUSH(SECTION_CC_IMPLEMENTS_INTERFACES)
ifelse(`$2',,,`#ifdef $2'
)dnl
  $1`'::add_interface(get_type());
ifelse(`$2',,,`
#endif // $2
')dnl
_POP()
_PUSH(SECTION_CC_MOVE_CONSTRUCTOR_INTERFACES)
ifelse(`$2',,,`#ifdef $2'
)dnl
  , $1`'(std::move(src))
ifelse(`$2',,,`
#endif // $2
')dnl
_POP()
_PUSH(SECTION_CC_MOVE_ASSIGNMENT_OPERATOR_INTERFACES)
ifelse(`$2',,,`#ifdef $2'
)dnl
  $1`'::operator=(std::move(src));
ifelse(`$2',,,`
#endif // $2
')dnl
_POP()
')

dnl Use if the C base type is declared G_DECLARE_FINAL_TYPE
dnl or GDK_DECLARE_INTERNAL_TYPE.
dnl https://gitlab.gnome.org/GNOME/glib/-/issues/2661
define(`_DO_NOT_DERIVE_GTYPE',`dnl
_PUSH()
dnl Define this macro to be tested for later.
define(`__BOOL_DO_NOT_DERIVE_GTYPE__',`$1')
_POP()
')

dnl If you add _DO_NOT_DERIVE_GTYPE to an existing class, and ABI must not be broken.
define(`_ABI_AS_WITH_DERIVED_GTYPE',`dnl
_PUSH()
dnl Define this macro to be tested for later.
define(`__BOOL_ABI_AS_WITH_DERIVED_GTYPE__',`$1')
_POP()
')

define(`_DYNAMIC_GTYPE_REGISTRATION',`dnl
_PUSH()
dnl Define this macro to be tested for later.
define(`__BOOL_DYNAMIC_GTYPE_REGISTRATION__',`$1')
_POP()
')

dnl This macro inserts the supplied text as a Doxygen comment block before the
dnl automatically generated declaration of a class' destructor.  The inner
dnl m4_ifelse() attempts to remove double quotes before and after the text if
dnl it is a single line.  If it is not, it returns the supplied lines, removing
dnl trailing spaces from each of them (with an m4_patsubst()).  The following
dnl outer m4_patsubst() prepends possible multiple lines below the first one
dnl with ' * ' by assuming that these lines are preceded by at least one space.
dnl Finally, the outer m4_patsubst() inserts spaces after commas which are
dnl removed by m4 in the processing.
dnl
dnl
dnl
dnl
define(`_DOCUMENT_DTOR',`dnl
_PUSH(SECTION_DTOR_DOCUMENTATION)
m4_ifelse(`$*',,,`dnl
  m4_patsubst(`m4_patsubst(`/** m4_ifelse(m4_regexp(`$*',`".*"'),-1,`m4_patsubst(`$*',`\s*$')',`m4_regexp(`$*',`"\s*\(.*\)\(\S\)\s*"',`\1\2')')',`^\s+',`   * ')',`,',`, ')
   */
')dnl
_POP()
')



dnl
dnl
dnl
define(`_PH_CLASS_DECLARATION',`dnl
class __FUNC_DECORATION__ __CPPNAME__`'_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  using CppObjectType = __CPPNAME__;
  using BaseObjectType = __REAL_CNAME__;
ifdef(`__BOOL_DO_NOT_DERIVE_GTYPE__',`dnl
ifdef(`__BOOL_ABI_AS_WITH_DERIVED_GTYPE__',`dnl
  using BaseClassType = __REAL_CNAME__`'Class;
  using CppClassParent = __CPPPARENT__`'_Class;
  using BaseClassParent = __REAL_CPARENT__`'Class;
',`dnl
  using CppClassParent = __CPPPARENT__`'_Class;
')',`dnl
  using BaseClassType = __REAL_CNAME__`'Class;
  using CppClassParent = __CPPPARENT__`'_Class;
  using BaseClassParent = __REAL_CPARENT__`'Class;
')dnl

  friend class __CPPNAME__;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  const Glib::Class& init();

ifdef(`__BOOL_DYNAMIC_GTYPE_REGISTRATION__',`
  const Glib::Class& init(GTypeModule* module);
',`')

ifdef(`__BOOL_DO_NOT_DERIVE_GTYPE__',`dnl
ifdef(`__BOOL_ABI_AS_WITH_DERIVED_GTYPE__',`dnl
  static void class_init_function(void* g_class, void* class_data);
',`dnl
')',`dnl
  static void class_init_function(void* g_class, void* class_data);
')dnl

  static Glib::ObjectBase* wrap_new(GObject*);

protected:

  //Callbacks (default signal handlers):
  //These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
  //You could prevent the original default signal handlers being called by overriding the *_impl method.
_IMPORT(SECTION_PH_DEFAULT_SIGNAL_HANDLERS)

  //Callbacks (virtual functions):
_IMPORT(SECTION_PH_VFUNCS)
};
')


dnl
dnl
dnl
define(`_PCC_CLASS_IMPLEMENTATION',`dnl
const Glib::Class& __CPPNAME__`'_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
ifdef(`__BOOL_DO_NOT_DERIVE_GTYPE__',`dnl
ifdef(`__BOOL_ABI_AS_WITH_DERIVED_GTYPE__',`dnl
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &__CPPNAME__`'_Class::class_init_function;

    // Do not derive a GType, or use a derived class:
    gtype_ = _LOWER(__CCAST__)_get_type();
',`dnl
    // Do not derive a GType, or use a derived class:
    gtype_ = _LOWER(__CCAST__)_get_type();
')',`dnl not __BOOL_DO_NOT_DERIVE_GTYPE__
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &__CPPNAME__`'_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(_LOWER(__CCAST__)_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:
_IMPORT(SECTION_CC_IMPLEMENTS_INTERFACES)
')
  }

  return *this;
}

ifdef(`__BOOL_DYNAMIC_GTYPE_REGISTRATION__',`
const Glib::Class& __CPPNAME__`'_Class::init(GTypeModule* module)
{
  if(!gtype_) // create the GType if necessary
  {
ifdef(`__BOOL_DO_NOT_DERIVE_GTYPE__',`dnl
ifdef(`__BOOL_ABI_AS_WITH_DERIVED_GTYPE__',`dnl
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &__CPPNAME__`'_Class::class_init_function;

    // Do not derive a GType, or use a derived class:
    gtype_ = _LOWER(__CCAST__)_get_type();
',`dnl
    // Do not derive a GType, or use a derived class:
    gtype_ = _LOWER(__CCAST__)_get_type();
')',`dnl
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &__CPPNAME__`'_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(_LOWER(__CCAST__)_get_type(), module);

    // Add derived versions of interfaces, if the C type implements any interfaces:
_IMPORT(SECTION_CC_IMPLEMENTS_INTERFACES)
')
  }

  return *this;
',`')

ifdef(`__BOOL_DO_NOT_DERIVE_GTYPE__',`dnl
ifdef(`__BOOL_ABI_AS_WITH_DERIVED_GTYPE__',`dnl

void __CPPNAME__`'_Class::class_init_function(void* g_class, void* class_data)
{
  const auto klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);

_IMPORT(SECTION_PCC_CLASS_INIT_VFUNCS)

_IMPORT(SECTION_PCC_CLASS_INIT_DEFAULT_SIGNAL_HANDLERS)
}
',`dnl
')',`dnl not __BOOL_DO_NOT_DERIVE_GTYPE__

void __CPPNAME__`'_Class::class_init_function(void* g_class, void* class_data)
{
  const auto klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);

_IMPORT(SECTION_PCC_CLASS_INIT_VFUNCS)

_IMPORT(SECTION_PCC_CLASS_INIT_DEFAULT_SIGNAL_HANDLERS)
}
')dnl

_IMPORT(SECTION_PCC_VFUNCS)

_IMPORT(SECTION_PCC_DEFAULT_SIGNAL_HANDLERS)
')



dnl
dnl
dnl
define(`_CC_CLASS_IMPLEMENTATION',`dnl
__CPPNAME__::CppClassType __CPPNAME__::`'__BASE__`'_class_; // initialize static member

GType __CPPNAME__::get_type()
{
  return __BASE__`'_class_.init().get_type();
}

ifdef(`__BOOL_DYNAMIC_GTYPE_REGISTRATION__',`
GType __CPPNAME__::get_type(GTypeModule* module)
{
  return __BASE__`'_class_.init(module).get_type();
}
'dnl
,`'dnl
)

GType __CPPNAME__::get_base_type()
{
  return _LOWER(__CCAST__)_get_type();
}

_IMPORT(SECTION_CC)

dnl _IMPORT(SECTION_CC_SIGNALPROXIES_CUSTOM)

_IMPORT(SECTION_CC_SIGNALPROXIES)

_IMPORT(SECTION_CC_PROPERTYPROXIES)

_IMPORT(SECTION_CC_DEFAULT_SIGNAL_HANDLERS)

_IMPORT(SECTION_CC_VFUNCS)
_IMPORT(SECTION_CC_VFUNCS_CPPWRAPPER)
')

dnl _PARENT_GCLASS_FROM_OBJECT(object_instance_name)
define(`_PARENT_GCLASS_FROM_OBJECT',`dnl
g_type_class_peek_parent`'(G_OBJECT_GET_CLASS`'($1)) // Get the parent class of the object class (The original underlying C class).
')

dnl _IFACE_PARENT_FROM_OBJECT(object_instance_name)
define(`_IFACE_PARENT_FROM_OBJECT',`dnl
g_type_interface_peek_parent`'( // Get the parent interface of the interface (The original underlying C interface).
g_type_interface_peek`'(G_OBJECT_GET_CLASS`'($1), CppObjectType::get_type`'()) // Get the interface.
)dnl
')

dnl Bonobo doesn't use the "typedef struct _somestruct struct" system.
define(`_STRUCT_NOT_HIDDEN',`dnl
_PUSH()
dnl Define this macro to be tested for later.
define(`__BOOL_STRUCT_NOT_HIDDEN__',`$1')
_POP()
')

dnl _STRUCT_PROTOTYPE()
define(`_STRUCT_PROTOTYPE',`dnl
#ifndef DOXYGEN_SHOULD_SKIP_THIS
ifdef(`__BOOL_STRUCT_NOT_HIDDEN__',`dnl
',`dnl
using __CNAME__ = struct _`'__CNAME__;
using __CNAME__`'Class = struct _`'__CNAME__`'Class;
')dnl
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
undefine(`__BOOL_STRUCT_NOT_HIDDEN__')dnl
')

dnl _GTKMMPROC_WIN32_NO_WRAP
dnl Just process it to remove it from the generated file.
dnl generate_wrap_init.pl will look for this in the original .hg file.
dnl
define(`_GTKMMPROC_WIN32_NO_WRAP', dnl
`//This is not available on Win32.
//This source file will not be compiled on Win32,
//and no class defined in it will be registered by wrap_init`'().
')dnl

dnl _GMMPROC_WRAP_CONDITIONALLY(preprocessor_if/ifdef/ifndef_directive_without_#)
dnl Just process it to remove it from the generated file.
dnl generate_wrap_init.pl will look for this in the original .hg file.
dnl
dnl Example calls:
dnl _GMMPROC_WRAP_CONDITIONALLY(ifndef G_OS_WIN32) # Same as _GTKMMPROC_WIN32_NO_WRAP
dnl _GMMPROC_WRAP_CONDITIONALLY(ifdef GDK_WINDOWING_X11)
dnl _GMMPROC_WRAP_CONDITIONALLY(`if defined(GDK_WINDOWING_X11) || defined(GDK_WINDOWING_QUARTZ)')
dnl
define(`_GMMPROC_WRAP_CONDITIONALLY', dnl
`//This is available only #$1.
//Otherwise this source file will not be compiled,
//and no class defined in it will be registered by wrap_init`'().
')dnl

dnl _INCLUDE_IN_WRAP_INIT(file)
dnl Usually used in combination with _GMMPROC_WRAP_CONDITIONALLY.
dnl It does not generate any code in the .h and .cc files.
dnl generate_wrap_init.pl will look for this in the original .hg file.
dnl
define(`_INCLUDE_IN_WRAP_INIT',`')dnl

dnl _IS_DEPRECATED
dnl ifdef-out the whole .h and .cc files.
dnl generate_wrap_init.pl will look for this in the original .hg file.
define(`_IS_DEPRECATED',`dnl
_PUSH()
dnl Define this macro to be tested for later. See base.m4.
define(`__BOOL_DEPRECATED__',`$1')
_POP()
')

dnl _NO_WRAP_INIT_REGISTRATION
dnl Used to tag the classes in a file as one not be registered by the
dnl wrap_init() function (all the classes in the file will not be registered).
dnl This macro does not generate any code in the .h and .cc files.
dnl generate_wrap_init.pl will look for this in the original .hg file.
dnl
define(`_NO_WRAP_INIT_REGISTRATION',`')dnl
