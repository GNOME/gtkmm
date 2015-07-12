## gtkmm - a C++ wrapper for the Gtk toolkit
##
## Copyright 2003-2010 The gtkmm Development Team
##
## This library is free software; you can redistribute it and/or
## modify it under the terms of the GNU Lesser General Public
## License as published by the Free Software Foundation; either
## version 2.1 of the License, or (at your option) any later version.
##
## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public
## License along with this library; if not, write to the Free Software
## Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

include(convert_glib.m4)
include(convert_gio.m4)

_EQUAL(gint8[],gint8*)
_EQUAL(guchar,guint8)
_EQUAL(guchar*,guint8*)
_EQUAL(gfloat,float)

# Enums
_CONV_ENUM(Gdk,AxisUse)
_CONV_ENUM(Gdk,ByteOrder)
_CONV_ENUM(Gdk,CapStyle)
_CONV_ENUM(Gdk,Colorspace)
_CONV_ENUM(Gdk,CursorType)
_CONV_ENUM(Gdk,DeviceType)
_CONV_ENUM(Gdk,DragAction)
_CONV_ENUM(Gdk,DragProtocol)
_CONV_ENUM(Gdk,EventMask)
_CONV_ENUM(Gdk,EventType)
_CONV_ENUM(Gdk,ExtensionMode)
_CONV_ENUM(Gdk,Fill)
_CONV_ENUM(Gdk,FillRule)
_CONV_ENUM(Gdk,FullscreenMode)
_CONV_ENUM(Gdk,Function)
_CONV_ENUM(Gdk,GCValuesMask)
_CONV_ENUM(Gdk,Gravity)
_CONV_ENUM(Gdk,GrabOwnership)
_CONV_ENUM(Gdk,ImageType)
_CONV_ENUM(Gdk,InputCondition)
_CONV_ENUM(Gdk,InputMode)
_CONV_ENUM(Gdk,InputSource)
_CONV_ENUM(Gdk,InterpType)
_CONV_ENUM(Gdk,JoinStyle)
_CONV_ENUM(Gdk,LineStyle)
_CONV_ENUM(Gdk,ModifierType)
_CONV_ENUM(Gdk,ModifierIntent)
_CONV_ENUM(Gdk,OverlapType)
_CONV_ENUM(Gdk,PixbufAlphaMode)
_CONV_ENUM(Gdk,RgbDither)
_CONV_ENUM(Gdk,Status)
_CONV_ENUM(Gdk,SubwindowMode)
_CONV_ENUM(Gdk,VisualType)
_CONV_ENUM(Gdk,WindowAttributesType)
_CONV_ENUM(Gdk,WindowEdge)
_CONV_ENUM(Gdk,WindowHints)
_CONV_ENUM(Gdk,WindowState)
_CONV_ENUM(Gdk,WindowType)
_CONV_ENUM(Gdk,WindowTypeHint)
_CONV_ENUM(Gdk,WMDecoration)
_CONV_ENUM(Gdk,WMFunction)
_CONV_ENUM(Gdk,GrabStatus)
_CONV_ENUM(Gdk,PixbufRotation)
_CONV_ENUM(Gdk,GLError)

_CONVERSION(`guint32&',`guint32*',`&($3)')

_CONVERSION(`Gdk::EventMask',`gint',`$3')
_CONVERSION(`gint',`Gdk::EventMask',`static_cast<Gdk::EventMask>($3)')
_CONVERSION(`ModifierType&',`GdkModifierType*',`(($2) &($3))')
_CONVERSION(`WMDecoration&',`GdkWMDecoration*',`(($2) &($3))')
_CONVERSION(`GdkDragProtocol&',`GdkDragProtocol*',`&($3)')

_CONVERSION(`GdkRectangle&',`GdkRectangle*',`&$3',`*$3')
_CONVERSION(`GdkRgbCmap&',`GdkRgbCmap*',`&$3',`*$3')


_CONVERSION(`GdkKeymap*',`const GdkKeymap*',`$3')




# for GtkStyle public struct members
_CONVERSION(`Gdk::Color',`GdkColor', `(*($3).gobj())')
_CONVERSION(`GdkColor',`Gdk::Color', `Gdk::Color(const_cast<GdkColor*>(&($3)), true)')

# Ref (gdkmm) -> Ptr (gtk+)
_CONVERSION(`Color&',`GdkColor*',($3).gobj())
_CONVERSION(`const Gdk::Color&',`const GdkColor*',`($3).gobj()')
_CONVERSION(`const RGBA&',`const GdkRGBA*',`($3).gobj()')
_CONVERSION(`RGBA&',`GdkRGBA*',`($3).gobj()')
_CONVERSION(`Gdk::RGBA&',`GdkRGBA*',`($3).gobj()')
_CONVERSION(`const RGBA&',`GdkRGBA*',`const_cast<RGBA&>($3).gobj()')
_CONVERSION(`const Gdk::RGBA&',`const GdkRGBA*',`($3).gobj()')
_CONVERSION(`const Color&',`const GdkColor*',`($3).gobj()')
_CONVERSION(`Rectangle&',`GdkRectangle*',($3).gobj())
_CONVERSION(`Gdk::Rectangle&',`GdkRectangle*',($3).gobj())
_CONVERSION(`const Rectangle&',`const GdkRectangle*',($3).gobj())
_CONVERSION(`const Gdk::Rectangle&',`const GdkRectangle*',($3).gobj())
_CONVERSION(`Font&',`GdkFont*',($3).gobj())
_CONVERSION(`const ::Cairo::RefPtr< ::Cairo::Region>&',`const cairo_region_t*',`(($3) ? ($3)->cobj() : 0)')
_CONVERSION(`const ::Cairo::RefPtr<const ::Cairo::Region>&',`cairo_region_t*',`const_cast<cairo_region_t*>(($3) ? ($3)->cobj() : 0)')
_CONVERSION(`const ::Cairo::RefPtr<const ::Cairo::Region>&',`const cairo_region_t*',`(($3) ? ($3)->cobj() : 0)')

_CONVERSION(`const Glib::RefPtr<Cursor>&',`GdkCursor*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Cursor>&',`GdkCursor*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Pixmap>&',`GdkPixmap*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Window>&',`GdkWindow*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Window>&',`GdkWindow*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<GLContext>&',`GdkGLContext*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::GLContext>&',`GdkGLContext*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Pixmap>&',`GdkPixmap*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Pixmap>&',`GdkPixmap*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Bitmap>&',`GdkBitmap*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Bitmap>&',`GdkBitmap*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Drawable>&',`GdkDrawable*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Drawable>&',`GdkDrawable*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Drawable>&',`GdkDrawable*',__CONVERT_CONST_REFPTR_TO_P_SUN(Drawable))
_CONVERSION(`const Glib::RefPtr<Image>&',`GdkImage*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Image>&',`GdkImage*',__CONVERT_CONST_REFPTR_TO_P_SUN(Image))
_CONVERSION(`const Glib::RefPtr<Gdk::Image>&',`GdkImage*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Pixbuf>&',`GdkPixbuf*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Pixbuf>&',`const GdkPixbuf*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Pixbuf>&',`GdkPixbuf*',__CONVERT_CONST_REFPTR_TO_P_SUN(Pixbuf))
_CONVERSION(`const Glib::RefPtr<Gdk::Pixbuf>&',`GdkPixbuf*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`Glib::RefPtr<Gdk::Pixbuf>',`GdkPixbuf*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::PixbufAnimation>&',`GdkPixbufAnimation*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::PixbufAnimationIter>&',`GdkPixbufAnimationIter*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::DragContext>&',`GdkDragContext*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Display>&',`GdkDisplay*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Screen>&',`GdkScreen*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Display>&',`GdkDisplay*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Screen>&',`GdkScreen*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Screen>&',`GdkScreen*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Device>&',`GdkDevice*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Device>&',`GdkDevice*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Device>&',`GdkDevice*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Device))
_CONVERSION(`const Glib::RefPtr<const Gdk::Screen>&',`GdkScreen*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Screen))

define(`__CFR2P',`const_cast<$`'2>($`'3.gobj())')
_CONVERSION(const Font&,GdkFont*,__CFR2P)
_CONVERSION(const Gdk::Color&,GdkColor*,__CFR2P)
_CONVERSION(const Color&,GdkColor*,__CFR2P)
_CONVERSION(const Gdk::Rectangle&,GdkRectangle*,__CFR2P)
_CONVERSION(const Rectangle&,GdkRectangle*,__CFR2P)
_CONVERSION(const Geometry&,const GdkGeometry*,&($3))
_CONVERSION(const Gdk::Geometry&,GdkGeometry*,const_cast<$2>(&($3)))
_CONVERSION(const Geometry&,GdkGeometry*,const_cast<$2>(&($3)))
_CONVERSION(const RgbCmap&,GdkRgbCmap*,__CFR2P)

_CONVERSION(`Gdk::Rectangle*',`GdkRectangle*',`Glib::unwrap($3)')
_CONVERSION(`const Gdk::Rectangle*',`GdkRectangle*',`Glib::unwrap(const_cast<Gdk::Rectangle*>($3))')
_CONVERSION(`GdkRectangle*',`Gdk::Rectangle*',`&Glib::wrap($3)')
_CONVERSION(`GdkRectangle*',`const Gdk::Rectangle*',`&Glib::wrap($3)')

# Special treatment for the Sun Forte compiler
#_CONVERSION(const Glib::RefPtr<const Gdk::Pixmap>&,GdkPixmap*,__CONVERT_CONST_REFPTR_TO_P)
#_CONVERSION(const Glib::RefPtr<const Gdk::Window>&,GdkWindow*,__CONVERT_CONST_REFPTR_TO_P)
#_CONVERSION(const Glib::RefPtr<const Gdk::Colormap>&,GdkColormap*,__CONVERT_CONST_REFPTR_TO_P)
#_CONVERSION(const Glib::RefPtr<const Gdk::Visual>&,GdkVisual*,__CONVERT_CONST_REFPTR_TO_P)
#_CONVERSION(const Glib::RefPtr<const Gdk::Bitmap>&,GdkBitmap*,__CONVERT_CONST_REFPTR_TO_P)
#_CONVERSION(const Glib::RefPtr<const Gdk::Image>&,GdkImage*,__CONVERT_CONST_REFPTR_TO_P)
#_CONVERSION(const Glib::RefPtr<const Gdk::GC>&,GdkGC*,__CONVERT_CONST_REFPTR_TO_P)

_CONVERSION(`const Glib::RefPtr<const Gdk::Device>&', `GdkDevice*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Device))
_CONVERSION(`const Glib::RefPtr<const Gdk::Pixmap>&', `GdkPixmap*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Pixmap))
_CONVERSION(`const Glib::RefPtr<const Gdk::Window>&', `GdkWindow*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Window))
_CONVERSION(`const Glib::RefPtr<const Window>&', `GdkWindow*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Window))
_CONVERSION(`const Glib::RefPtr<const Gdk::GLContext>&', `GdkGLContext*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::GLContext))
_CONVERSION(`const Glib::RefPtr<const GLContext>&', `GdkGLContext*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::GLContext))
_CONVERSION(`const Glib::RefPtr<const Gdk::Colormap>&', `GdkColormap*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Colormap))
_CONVERSION(`const Glib::RefPtr<const Gdk::Visual>&', `GdkVisual*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Visual))
_CONVERSION(`const Glib::RefPtr<const Gdk::Bitmap>&', `GdkBitmap*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Bitmap))
_CONVERSION(`const Glib::RefPtr<const Gdk::Image>&', `GdkImage*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Image))
_CONVERSION(`const Glib::RefPtr<const Image>&', `GdkImage*',__CONVERT_CONST_REFPTR_TO_P_SUN(Image))
_CONVERSION(`const Glib::RefPtr<const Gdk::GC>&', `GdkGC*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::GC))
_CONVERSION(`const Glib::RefPtr<const GC>&', `GdkGC*',__CONVERT_CONST_REFPTR_TO_P_SUN(GC))
#_CONVERSION(`const Glib::RefPtr<const Gdk::Drawable>&', `GdkDrawable*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Drawable))
#_CONVERSION(`const Glib::RefPtr<const Drawable>&', `GdkDrawable*',__CONVERT_CONST_REFPTR_TO_P_SUN(Drawable))
#_CONVERSION(`const Glib::RefPtr<const Display>&', `GdkDrawable*',__CONVERT_CONST_REFPTR_TO_P_SUN(Drawable))


_CONVERSION(`GdkWindow*',`Glib::RefPtr<Window>', `Glib::wrap($3)')
_CONVERSION(`GdkWindow*',`Glib::RefPtr<const Window>', `Glib::wrap($3)')
_CONVERSION(`GdkWindow*',`Glib::RefPtr<Gdk::Window>', `Glib::wrap($3)')
_CONVERSION(`GdkWindow*',`Glib::RefPtr<const Gdk::Window>', `Glib::wrap($3)')
_CONVERSION(`GdkGLContext*',`Glib::RefPtr<GLContext>', `Glib::wrap($3)')
_CONVERSION(`GdkGLContext*',`Glib::RefPtr<const GLContext>', `Glib::wrap($3)')
_CONVERSION(`GdkGLContext*',`Glib::RefPtr<Gdk::GLContext>', `Glib::wrap($3)')
_CONVERSION(`GdkGLContext*',`Glib::RefPtr<const Gdk::GLContext>', `Glib::wrap($3)')
_CONVERSION(`GdkPixmap*',`Glib::RefPtr<Pixmap>', `Glib::wrap((GdkPixmapObject*)($3))')
_CONVERSION(`GdkPixmap*',`Glib::RefPtr<const Pixmap>', `Glib::wrap((GdkPixmapObject*)($3))')
_CONVERSION(`GdkPixmap*',`Glib::RefPtr<const Gdk::Pixmap>', `Glib::wrap((GdkPixmapObject*)($3))')
_CONVERSION(`GdkPixmap*',`Glib::RefPtr<Gdk::Pixmap>', `Glib::wrap((GdkPixmapObject*)($3))')
_CONVERSION(`GdkCursor*',`Glib::RefPtr<Cursor>', `Glib::wrap($3)')
_CONVERSION(`GdkCursor*',`Glib::RefPtr<const Cursor>', `Glib::wrap($3)')
_CONVERSION(`GdkVisual*',`Glib::RefPtr<Gdk::Visual>', `Glib::wrap($3)')
_CONVERSION(`GdkVisual*',`Glib::RefPtr<Visual>', `Glib::wrap($3)')
_CONVERSION(`GdkVisual*',`Glib::RefPtr<const Visual>', `Glib::wrap($3)')
_CONVERSION(`GdkImage*',`Glib::RefPtr<Image>', `Glib::wrap($3)')
_CONVERSION(`GdkPixbuf*',`Glib::RefPtr<Pixbuf>', `Glib::wrap($3)')
_CONVERSION(`GdkPixbuf*',`Glib::RefPtr<Gdk::Pixbuf>', `Glib::wrap($3)')
_CONVERSION(`GdkPixbuf*',`Glib::RefPtr<const Gdk::Pixbuf>', `Glib::wrap($3)')
_CONVERSION(`GdkPixbufAnimationIter*',`Glib::RefPtr<PixbufAnimationIter>', `Glib::wrap($3)')
_CONVERSION(`GdkPixbuf*',`Glib::RefPtr<Gdk::Pixbuf>', Glib::wrap($3))
_CONVERSION(`GdkPixbufAnimation*',`Glib::RefPtr<Gdk::PixbufAnimation>', `Glib::wrap($3)')
_CONVERSION(`GdkPixbufAnimation*',`Glib::RefPtr<const Gdk::PixbufAnimation>', `Glib::wrap($3)')
_CONVERSION(`GdkGC*',`Glib::RefPtr<Gdk::GC>', `Glib::wrap($3)')
_CONVERSION(`GdkGC*',`Glib::RefPtr<const Gdk::GC>', `Glib::wrap($3)')

_CONVERSION(`GdkDisplay*',`Glib::RefPtr<Display>', `Glib::wrap($3)')
_CONVERSION(`GdkDisplay*',`Glib::RefPtr<const Display>', `Glib::wrap($3)')
_CONVERSION(`GdkDisplay*',`Glib::RefPtr<Gdk::Display>', `Glib::wrap($3)')
_CONVERSION(`GdkDisplay*',`Glib::RefPtr<const Gdk::Display>', `Glib::wrap($3)')

_CONVERSION(`GdkDisplayManager*',`Glib::RefPtr<DisplayManager>', `Glib::wrap($3)')
_CONVERSION(`GdkDisplayManager*',`Glib::RefPtr<const DisplayManager>', `Glib::wrap($3)')

_CONVERSION(`GdkScreen*',`Glib::RefPtr<Screen>', `Glib::wrap($3)')
_CONVERSION(`GdkScreen*',`Glib::RefPtr<const Screen>', `Glib::wrap($3)')
_CONVERSION(`GdkScreen*',`Glib::RefPtr<Gdk::Screen>', `Glib::wrap($3)')
_CONVERSION(`GdkScreen*',`Glib::RefPtr<const Gdk::Screen>', `Glib::wrap($3)')

_CONVERSION(`GdkDevice*',`Glib::RefPtr<Device>', `Glib::wrap($3)')
_CONVERSION(`GdkDevice*',`Glib::RefPtr<Gdk::Device>', `Glib::wrap($3)')
_CONVERSION(`GdkDevice*',`Glib::RefPtr<const Device>', `Glib::wrap($3)')
_CONVERSION(`GdkDevice*',`Glib::RefPtr<const Gdk::Device>', `Glib::wrap($3)')

_CONVERSION(`GdkDeviceManager*',`Glib::RefPtr<DeviceManager>', `Glib::wrap($3)')
_CONVERSION(`GdkDeviceManager*',`Glib::RefPtr<const DeviceManager>', `Glib::wrap($3)')

_CONVERSION(`gpointer',`const void*', `($2)($3)')


# Glib::ListHandle<> (gdkmm) -> GList (gdk)
_CONVERSION(`const Glib::ListHandle< Glib::RefPtr<Gdk::Pixbuf> >&',`GList*',`$3.data()')
_CONVERSION(`const Glib::ListHandle< Glib::RefPtr<const Gdk::Pixbuf> >&',`GList*',`$3.data()')

# GList (gdk) -> Glib::ListHandle<> (gdkmm)
_CONVERSION(`GList*',`Glib::ListHandle< Glib::RefPtr<Gdk::Pixbuf> >',`$2($3, Glib::OWNERSHIP_SHALLOW)')
_CONVERSION(`GList*',`Glib::ListHandle< Glib::RefPtr<const Gdk::Pixbuf> >',`$2($3, Glib::OWNERSHIP_SHALLOW)')
_CONVERSION(`GList*',`Glib::ListHandle< Glib::RefPtr<Device> >',`$2($3, Glib::OWNERSHIP_NONE)')
_CONVERSION(`GList*',`Glib::ListHandle< Glib::RefPtr<const Device> >',`$2($3, Glib::OWNERSHIP_NONE)')
_CONVERSION(`GList*',`Glib::ListHandle< Glib::RefPtr<Visual> >',`$2($3, Glib::OWNERSHIP_SHALLOW)')
_CONVERSION(`GList*',`Glib::ListHandle< Glib::RefPtr<const Visual> >',`$2($3, Glib::OWNERSHIP_SHALLOW)')
_CONVERSION(`GList*',`Glib::ListHandle< Glib::RefPtr<Window> >',`$2($3, Glib::OWNERSHIP_SHALLOW)')
_CONVERSION(`GList*',`Glib::ListHandle< Glib::RefPtr<const Window> >',`$2($3, Glib::OWNERSHIP_SHALLOW)')
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<Display> >',`$2($3, Glib::OWNERSHIP_SHALLOW)')
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<const Display> >',`$2($3, Glib::OWNERSHIP_SHALLOW)')
_CONVERSION(`gchar**',`Glib::StringArrayHandle',`$2($3)')




# XPM data
_CONVERSION(`const char*const*',`const char**',`const_cast<const char**>($3)',`$3')


_CONVERSION(GdkFont*, Gdk::Font, `Gdk::Font($3)')
_CONVERSION(GdkEvent*, Event, `Event($3)')

_CONVERSION(`GdkTimeCoord**&',`GdkTimeCoord***',`&($3)')

dnl _CONVERSION(GdkPixmap*,Gdk::Pixmap&,`Glib::unwrap_boxed($3)',`$3')
dnl _CONVERSION(GdkBitmap*,Gdk::Bitmap&,`Glib::unwrap_boxed($3)',`$3')

dnl Atom -> string and vice versa
_CONVERSION(`GdkAtom',`Glib::ustring',`Gdk::AtomString::to_cpp_type($3)')
_CONVERSION(`const Glib::ustring&', `GdkAtom', `Gdk::AtomString::to_c_type($3)')
_CONVERSION(`Glib::ustring&',`GdkAtom',`Gdk::AtomString::to_c_type($3)')

dnl NativeWindow
_CONVERSION(`GdkNativeWindow',`Gdk::NativeWindow',`($2)($3)')
_CONVERSION(`GdkNativeWindow',`NativeWindow',`($2)($3)')
_CONVERSION(`Gdk::NativeWindow',`GdkNativeWindow',`($2)($3)')
_CONVERSION(`NativeWindow',`GdkNativeWindow',`($2)($3)')
_CONVERSION(`GdkEvent*',`const GdkEvent*',`($2)($3)')


_CONVERSION(`GdkDragContext*',`Glib::RefPtr<DragContext>',Glib::wrap($3, true))
_CONVERSION(`GdkDragContext*',`Glib::RefPtr<Gdk::DragContext>',Glib::wrap($3, true))

_CONVERSION(`const Widgetpath&',`GtkWidgetPath*',`const_cast<WidgetPath&>($3).gobj()')

