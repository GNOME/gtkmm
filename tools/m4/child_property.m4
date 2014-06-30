dnl
dnl
dnl  Code generation sections for GtkContainer child properties
dnl
dnl

dnl                       $1         $2            $3          $4           $5        $6
dnl _CHILD_PROPERTY_PROXY(name, name_underscored, cpp_type, proxy_suffix, deprecated, docs)
dnl proxy_suffix could be "", "_WriteOnly" or "_ReadOnly"
dnl The method will be const if the propertyproxy is _ReadOnly.
dnl
define(`_CHILD_PROPERTY_PROXY',`dnl
dnl
dnl Put spaces around the template parameter if necessary.
pushdef(`__PROXY_TYPE__',`dnl
Gtk::ChildPropertyProxy$4< _QUOTE($3) >'dnl
)dnl
/** $6
   *
   * @return A ChildPropertyProxy$4 that allows you to dnl
ifelse($4,_ReadOnly,get,`ifelse($4,_WriteOnly,set,get or set)') the value of the property,
   * or receive notification when the value of the property changes.
   */
  __PROXY_TYPE__ child_property_$2`'(ifelse($4,_ReadOnly,const ,)Gtk::Widget& child) ifelse($4,_ReadOnly, const,);
_PUSH(SECTION_CC_PROPERTYPROXIES)
ifelse(`$5',,,`_DEPRECATE_IFDEF_START
')dnl
__PROXY_TYPE__ __CPPNAME__::child_property_$2`'(ifelse($4,_ReadOnly,const ,)Gtk::Widget& child) ifelse($4,_ReadOnly, const,)
{
  return __PROXY_TYPE__`'(this, child, "$1");
}
ifelse(`$5',,,`_DEPRECATE_IFDEF_END
')dnl

_POP()
popdef(`__PROXY_TYPE__')dnl
')dnl
