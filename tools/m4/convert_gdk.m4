## gtkmm - a C++ wrapper for the Gtk toolkit
##
## Copyright (C) 2003-2010 The gtkmm Development Team
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
## License along with this library; if not, see <http://www.gnu.org/licenses/>.

include(convert_glib.m4)
include(convert_gio.m4)

_EQUAL(gint8[],gint8*)
_EQUAL(guchar,guint8)
_EQUAL(guchar*,guint8*)
_EQUAL(gfloat,float)

# Enums
_CONV_ENUM(Gdk,AnchorHints)
_CONV_ENUM(Gdk,AxisFlags)
_CONV_ENUM(Gdk,AxisUse)
_CONV_ENUM(Gdk,CapStyle)
_CONV_INCLASS_ENUM(Gdk,CicpParams,Range,GdkCicpRange)
_CONV_ENUM(Gdk,Colorspace)
_CONV_ENUM(Gdk,CrossingMode)
_CONV_INCLASS_ENUM(Gdk,Device,Type)
_CONV_INCLASS_ENUM(Gdk,DevicePad,Feature)
_CONV_INCLASS_ENUM(Gdk,DeviceTool,Type)
_CONV_ENUM(Gdk,DragAction)
_CONV_ENUM(Gdk,DragCancelReason)
_CONV_INCLASS_ENUM(Gdk,Event,Type)
_CONV_ENUM(Gdk,ExtensionMode)
_CONV_ENUM(Gdk,Fill)
_CONV_ENUM(Gdk,FillRule)
_CONV_INCLASS_ENUM(Gdk,FrameClock,Phase)
_CONV_ENUM(Gdk,FullscreenMode)
_CONV_ENUM(Gdk,Function)
_CONV_ENUM(Gdk,GLAPI)
#TODO: When we can break ABI, remove _CONV_ENUM(Gdk,GLAPI) and activate the
# following _CONV_ENUM. See glcontext.hg. The conversions are case-insensitive.
#_CONV_ENUM(Gdk,GLApi,GdkGLAPI)
_CONV_ENUM(Gdk,Gravity)
_CONV_ENUM(Gdk,InputCondition)
_CONV_ENUM(Gdk,InputSource)
_CONV_ENUM(Gdk,InterpType)
_CONV_ENUM(Gdk,JoinStyle)
_CONV_ENUM(Gdk,KeyMatch)
_CONV_ENUM(Gdk,LineStyle)
_CONV_ENUM(Gdk,MemoryFormat)
_CONV_INCLASS_ENUM(Gdk,MemoryTexture,Format,GdkMemoryFormat)
_CONV_ENUM(Gdk,ModifierType)
_CONV_ENUM(Gdk,NotifyType)
_CONV_ENUM(Gdk,OverlapType)
_CONV_ENUM(Gdk,OwnerChange)
_CONV_INCLASS_ENUM(Gdk,Paintable,Flags)
_CONV_ENUM(Gdk,PropertyState)
_CONV_ENUM(Gdk,ScrollDirection)
_CONV_ENUM(Gdk,ScrollRelativeDirection)
_CONV_ENUM(Gdk,ScrollUnit)
_CONV_INCLASS_ENUM(Gdk,Seat,Capabilities)
_CONV_ENUM(Gdk,SettingAction)
_CONV_ENUM(Gdk,Status)
_CONV_ENUM(Gdk,SubpixelLayout)
_CONV_ENUM(Gdk,SurfaceEdge)
_CONV_ENUM(Gdk,TitlebarGesture)
_CONV_INCLASS_ENUM(Gdk,Toplevel,Capabilities)
_CONV_INCLASS_ENUM(Gdk,Toplevel,State)
_CONV_ENUM(Gdk,TouchpadGesturePhase)
_CONV_INCLASS_ENUM(Gdk,Pixbuf,AlphaMode)
_CONV_INCLASS_ENUM(Gdk,Pixbuf,Rotation)
_CONV_ENUM(Gdk,GLError)

_CONVERSION(`guint32&',`guint32*',`&($3)')

_CONVERSION(`EventMask',`gint',`static_cast<gint>($3)')
_CONVERSION(`Gdk::EventMask',`gint',`static_cast<gint>($3)')
_CONVERSION(`gint',`Gdk::EventMask',`static_cast<Gdk::EventMask>($3)')
_CONVERSION(`ModifierType&',`GdkModifierType*',`(($2) &($3))')
_CONVERSION(`WMDecoration&',`GdkWMDecoration*',`(($2) &($3))')
_CONVERSION(`GdkDragProtocol&',`GdkDragProtocol*',`&($3)')

_CONVERSION(`GdkRectangle&',`GdkRectangle*',`&$3',`*$3')

_CONVERSION(`GdkKeymap*',`const GdkKeymap*',`$3')


# Ref (gdkmm) -> Ptr (gtk+)
_CONVERSION(`const RGBA&',`const GdkRGBA*',`($3).gobj()')
_CONVERSION(`RGBA&',`GdkRGBA*',`($3).gobj()')
_CONVERSION(`Gdk::RGBA&',`GdkRGBA*',`($3).gobj()')
_CONVERSION(`const RGBA&',`GdkRGBA*',`const_cast<RGBA&>($3).gobj()')
_CONVERSION(`const Gdk::RGBA&',`const GdkRGBA*',`($3).gobj()')
_CONVERSION(`Rectangle&',`GdkRectangle*',($3).gobj())
_CONVERSION(`Gdk::Rectangle&',`GdkRectangle*',($3).gobj())
_CONVERSION(`const Rectangle&',`const GdkRectangle*',($3).gobj())
_CONVERSION(`const Gdk::Rectangle&',`const GdkRectangle*',($3).gobj())

_CONVERSION(`const ::Cairo::RefPtr< ::Cairo::Context>&',`cairo_t*',`(($3) ? ($3)->cobj() : nullptr)')
_CONVERSION(`cairo_t*',`::Cairo::RefPtr< ::Cairo::Context>',`Gdk::Cairo::wrap($3)')
_CONVERSION(`cairo_t*',`::Cairo::RefPtr<const ::Cairo::Context>',`Gdk::Cairo::wrap($3)')
_CONVERSION(`const ::Cairo::RefPtr< ::Cairo::Region>&',`cairo_region_t*',`(($3) ? ($3)->cobj() : nullptr)')
_CONVERSION(`const ::Cairo::RefPtr< ::Cairo::Region>&',`const cairo_region_t*',`(($3) ? ($3)->cobj() : nullptr)')
_CONVERSION(`const ::Cairo::RefPtr<const ::Cairo::Region>&',`cairo_region_t*',`const_cast<cairo_region_t*>(($3) ? ($3)->cobj() : nullptr)')
_CONVERSION(`const ::Cairo::RefPtr<const ::Cairo::Region>&',`const cairo_region_t*',`(($3) ? ($3)->cobj() : nullptr)')
_CONVERSION(`cairo_region_t*',`::Cairo::RefPtr< ::Cairo::Region>',`Gdk::Cairo::wrap($3)')
_CONVERSION(`const cairo_region_t*',`::Cairo::RefPtr<const ::Cairo::Region>',`Gdk::Cairo::wrap(const_cast<cairo_region_t*>($3))')
_CONVERSION(`const ::Cairo::RefPtr< ::Cairo::Surface>&',`cairo_surface_t*',`(($3) ? ($3)->cobj() : nullptr)')
_CONVERSION(`cairo_surface_t*',`::Cairo::RefPtr< ::Cairo::Surface>',`Gdk::Cairo::wrap($3)')

_CONVERSION(`const Glib::RefPtr<Cursor>&',`GdkCursor*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Cursor>&',`GdkCursor*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Cursor>&',`GdkCursor*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Gdk::Cursor>&',`GdkCursor*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<PopupLayout>&',`GdkPopupLayout*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const PopupLayout>&',`GdkPopupLayout*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<ToplevelLayout>&',`GdkToplevelLayout*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const ToplevelLayout>&',`GdkToplevelLayout*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Surface>&',`GdkSurface*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Surface>&',`GdkSurface*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<GLContext>&',`GdkGLContext*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::GLContext>&',`GdkGLContext*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<DrawContext>&',`GdkDrawContext*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<DrawingContext>&',`GdkDrawingContext*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Bitmap>&',`GdkBitmap*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Bitmap>&',`GdkBitmap*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Gdk::Paintable>&',`GdkPaintable*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Paintable>&',`GdkPaintable*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Pixbuf>&',`GdkPixbuf*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Pixbuf>&',`const GdkPixbuf*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Pixbuf>&',`GdkPixbuf*',__CONVERT_CONST_REFPTR_TO_P_SUN(Pixbuf))
_CONVERSION(`const Glib::RefPtr<const Gdk::Pixbuf>&',`GdkPixbuf*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Pixbuf>&',`GdkPixbuf*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`Glib::RefPtr<Gdk::Pixbuf>',`GdkPixbuf*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::PixbufAnimation>&',`GdkPixbufAnimation*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::PixbufAnimationIter>&',`GdkPixbufAnimationIter*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Drag>&',`GdkDrag*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Drop>&',`GdkDrop*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Display>&',`GdkDisplay*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Display>&',`GdkDisplay*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Gdk::Display>&',`GdkDisplay*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Device>&',`GdkDevice*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Device>&',`GdkDevice*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Device>&',`GdkDevice*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Device))
_CONVERSION(`const Glib::RefPtr<Monitor>&',`GdkMonitor*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Monitor>&',`GdkMonitor*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Snapshot>&',`GdkSnapshot*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Texture>&',`GdkTexture*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Texture>&',`GdkTexture*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Gdk::Texture>&',`GdkTexture*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Texture>&',`GdkTexture*',__CONVERT_REFPTR_TO_P)

define(`__CFR2P',`const_cast<$`'2>($`'3.gobj())')
_CONVERSION(const Gdk::Rectangle&,GdkRectangle*,__CFR2P)
_CONVERSION(const Rectangle&,GdkRectangle*,__CFR2P)
_CONVERSION(const Geometry&,const GdkGeometry*,&($3))
_CONVERSION(const Gdk::Geometry&,GdkGeometry*,const_cast<$2>(&($3)))
_CONVERSION(const Geometry&,GdkGeometry*,const_cast<$2>(&($3)))

_CONVERSION(`Gdk::Rectangle*',`GdkRectangle*',`Glib::unwrap($3)')
_CONVERSION(`const Gdk::Rectangle*',`GdkRectangle*',`Glib::unwrap(const_cast<Gdk::Rectangle*>($3))')
_CONVERSION(`GdkRectangle*',`Gdk::Rectangle*',`&Glib::wrap($3)')
_CONVERSION(`GdkRectangle*',`const Gdk::Rectangle*',`&Glib::wrap($3)')
_CONVERSION(`const GdkRectangle*',`Rectangle',`Rectangle($3)')

# Special treatment for the Sun Forte compiler
#_CONVERSION(const Glib::RefPtr<const Gdk::Surface>&,GdkSurface*,__CONVERT_CONST_REFPTR_TO_P)
#_CONVERSION(const Glib::RefPtr<const Gdk::Bitmap>&,GdkBitmap*,__CONVERT_CONST_REFPTR_TO_P)

_CONVERSION(`const Glib::RefPtr<const Gdk::Device>&', `GdkDevice*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Device))
_CONVERSION(`const Glib::RefPtr<const Gdk::Surface>&', `GdkSurface*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Surface))
_CONVERSION(`const Glib::RefPtr<const Surface>&', `GdkSurface*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Surface))
_CONVERSION(`const Glib::RefPtr<const Gdk::GLContext>&', `GdkGLContext*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::GLContext))
_CONVERSION(`const Glib::RefPtr<const GLContext>&', `GdkGLContext*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::GLContext))
_CONVERSION(`const Glib::RefPtr<const Gdk::Bitmap>&', `GdkBitmap*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gdk::Bitmap))

_CONVERSION(`GdkPopupLayout*',`Glib::RefPtr<PopupLayout>', `Glib::wrap($3)')
_CONVERSION(`GdkToplevelLayout*',`Glib::RefPtr<ToplevelLayout>', `Glib::wrap($3)')
_CONVERSION(`GdkSurface*',`Glib::RefPtr<Surface>', `Glib::wrap($3)')
_CONVERSION(`GdkSurface*',`Glib::RefPtr<const Surface>', `Glib::wrap($3)')
_CONVERSION(`GdkSurface*',`Glib::RefPtr<Gdk::Surface>', `Glib::wrap($3)')
_CONVERSION(`GdkSurface*',`Glib::RefPtr<const Gdk::Surface>', `Glib::wrap($3)')
_CONVERSION(`GdkCairoContext*',`Glib::RefPtr<Gdk::CairoContext>', `Glib::wrap($3)')
_CONVERSION(`GdkGLContext*',`Glib::RefPtr<GLContext>', `Glib::wrap($3)')
_CONVERSION(`GdkGLContext*',`Glib::RefPtr<const GLContext>', `Glib::wrap($3)')
_CONVERSION(`GdkGLContext*',`Glib::RefPtr<Gdk::GLContext>', `Glib::wrap($3)')
_CONVERSION(`GdkGLContext*',`Glib::RefPtr<const Gdk::GLContext>', `Glib::wrap($3)')
_CONVERSION(`GdkDrawContext*',`Glib::RefPtr<DrawContext>', `Glib::wrap($3)')
_CONVERSION(`GdkDrawContext*',`Glib::RefPtr<const DrawContext>', `Glib::wrap($3)')
_CONVERSION(`GdkDrawingContext*',`Glib::RefPtr<DrawingContext>', `Glib::wrap($3)')
_CONVERSION(`GdkCursor*',`Glib::RefPtr<Cursor>', `Glib::wrap($3)')
_CONVERSION(`GdkCursor*',`Glib::RefPtr<const Cursor>', `Glib::wrap($3)')
_CONVERSION(`GdkCursor*',`Glib::RefPtr<Gdk::Cursor>', `Glib::wrap($3)')
_CONVERSION(`GdkCursor*',`Glib::RefPtr<const Gdk::Cursor>', `Glib::wrap($3)')
_CONVERSION(`GdkPixbuf*',`Glib::RefPtr<Pixbuf>', `Glib::wrap($3)')
_CONVERSION(`GdkPixbuf*',`Glib::RefPtr<Gdk::Pixbuf>', `Glib::wrap($3)')
_CONVERSION(`GdkPixbuf*',`Glib::RefPtr<const Gdk::Pixbuf>', `Glib::wrap($3)')
_CONVERSION(`GdkPixbufAnimationIter*',`Glib::RefPtr<PixbufAnimationIter>', `Glib::wrap($3)')
_CONVERSION(`GdkPixbuf*',`Glib::RefPtr<Gdk::Pixbuf>', Glib::wrap($3))
_CONVERSION(`GdkPixbufAnimation*',`Glib::RefPtr<PixbufAnimation>', `Glib::wrap($3)')
_CONVERSION(`GdkPixbufAnimation*',`Glib::RefPtr<Gdk::PixbufAnimation>', `Glib::wrap($3)')
_CONVERSION(`GdkPixbufAnimation*',`Glib::RefPtr<const Gdk::PixbufAnimation>', `Glib::wrap($3)')

_CONVERSION(`GdkDisplay*',`Glib::RefPtr<Display>', `Glib::wrap($3)')
_CONVERSION(`GdkDisplay*',`Glib::RefPtr<const Display>', `Glib::wrap($3)')
_CONVERSION(`GdkDisplay*',`Glib::RefPtr<Gdk::Display>', `Glib::wrap($3)')
_CONVERSION(`GdkDisplay*',`Glib::RefPtr<const Gdk::Display>', `Glib::wrap($3)')

_CONVERSION(`GdkDisplayManager*',`Glib::RefPtr<DisplayManager>', `Glib::wrap($3)')
_CONVERSION(`GdkDisplayManager*',`Glib::RefPtr<const DisplayManager>', `Glib::wrap($3)')

_CONVERSION(`GdkDevice*',`Glib::RefPtr<Device>', `Glib::wrap($3)')
_CONVERSION(`GdkDevice*',`Glib::RefPtr<Gdk::Device>', `Glib::wrap($3)')
_CONVERSION(`GdkDevice*',`Glib::RefPtr<const Device>', `Glib::wrap($3)')
_CONVERSION(`GdkDevice*',`Glib::RefPtr<const Gdk::Device>', `Glib::wrap($3)')

_CONVERSION(`GdkDeviceTool*',`Glib::RefPtr<DeviceTool>', `Glib::wrap($3)')
_CONVERSION(`GdkDeviceTool*',`Glib::RefPtr<Gdk::DeviceTool>', `Glib::wrap($3)')

_CONVERSION(`GdkPaintable*',`Glib::RefPtr<Paintable>', `Glib::wrap($3)')
_CONVERSION(`GdkPaintable*',`Glib::RefPtr<const Paintable>', `Glib::wrap($3)')
_CONVERSION(`GdkPaintable*',`Glib::RefPtr<Gdk::Paintable>', `Glib::wrap($3)')
_CONVERSION(`GdkPaintable*',`Glib::RefPtr<const Gdk::Paintable>', `Glib::wrap($3)')

_CONVERSION(`GdkSeat*',`Glib::RefPtr<Seat>', `Glib::wrap($3)')
_CONVERSION(`GdkSeat*',`Glib::RefPtr<Gdk::Seat>', `Glib::wrap($3)')
_CONVERSION(`GdkSeat*',`Glib::RefPtr<const Seat>', `Glib::wrap($3)')
_CONVERSION(`GdkSeat*',`Glib::RefPtr<const Gdk::Seat>', `Glib::wrap($3)')

_CONVERSION(`GdkDmabufFormats*',`Glib::RefPtr<DmabufFormats>', `Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<const DmabufFormats>&',`const GdkDmabufFormats*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`GdkTexture*',`Glib::RefPtr<Texture>', `Glib::wrap($3)')
_CONVERSION(`GdkTexture*',`Glib::RefPtr<Gdk::Texture>', `Glib::wrap($3)')
_CONVERSION(`GdkTexture*',`Glib::RefPtr<const Texture>', `Glib::wrap($3)')
_CONVERSION(`GdkTexture*',`Glib::RefPtr<const Gdk::Texture>', `Glib::wrap($3)')

_CONVERSION(`GdkMonitor*',`Glib::RefPtr<Monitor>', `Glib::wrap($3)')
_CONVERSION(`GdkMonitor*',`Glib::RefPtr<const Monitor>', `Glib::wrap($3)')

_CONVERSION(`gpointer',`const void*', `static_cast<$2>($3)')

# Clipboard
_CONVERSION(`const Glib::RefPtr<Gdk::Clipboard>&',`GdkClipboard*',__CONVERT_REFPTR_TO_P($3))
_CONVERSION(`GdkClipboard*',`Glib::RefPtr<Clipboard>',`Glib::wrap($3)')
_CONVERSION(`GdkClipboard*',`Glib::RefPtr<const Clipboard>',`Glib::wrap($3)')
_CONVERSION(`GdkClipboard*',`Glib::RefPtr<Gdk::Clipboard>',`Glib::wrap($3)')
_CONVERSION(`GdkClipboard*',`Glib::RefPtr<const Gdk::Clipboard>',`Glib::wrap($3)')

# CicpParams, ColorState
_CONVERSION(`GdkCicpParams*',`Glib::RefPtr<CicpParams>',`Glib::wrap($3)')
_CONVERSION(`GdkColorState*',`Glib::RefPtr<ColorState>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<const ColorState>&',`GdkColorState*',__CONVERT_CONST_REFPTR_TO_P)

# ContentFormats, ContentFormatsBuilder
_CONVERSION(`const Glib::RefPtr<ContentFormats>&',`GdkContentFormats*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const ContentFormats>&',`GdkContentFormats*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const ContentFormats>&',`const GdkContentFormats*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::ContentFormats>&',`GdkContentFormats*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Gdk::ContentFormats>&',`GdkContentFormats*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`GdkContentFormats*',`Glib::RefPtr<ContentFormats>',`Glib::wrap($3)')
_CONVERSION(`GdkContentFormats*',`Glib::RefPtr<const ContentFormats>',`Glib::wrap($3)')
_CONVERSION(`GdkContentFormats*',`Glib::RefPtr<Gdk::ContentFormats>',`Glib::wrap($3)')
_CONVERSION(`GdkContentFormats*',`Glib::RefPtr<const Gdk::ContentFormats>',`Glib::wrap($3)')
_CONVERSION(`GdkContentFormatsBuilder*',`Glib::RefPtr<ContentFormatsBuilder>',`Glib::wrap($3)')

# ContentProvider
_CONVERSION(`const Glib::RefPtr<ContentProvider>&',`GdkContentProvider*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::ContentProvider>&',`GdkContentProvider*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const ContentProvider>&',`GdkContentProvider*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`GdkContentProvider*',`Glib::RefPtr<ContentProvider>',`Glib::wrap($3)')
_CONVERSION(`GdkContentProvider*',`Glib::RefPtr<Gdk::ContentProvider>',`Glib::wrap($3)')

_CONVERSION(`const Glib::RefPtr<Gio::OutputStream>&',`GOutputStream*',__CONVERT_REFPTR_TO_P)

# FrameClock, FrameTimings
_CONVERSION(`GdkFrameClock*',`Glib::RefPtr<FrameClock>',`Glib::wrap($3)')
_CONVERSION(`GdkFrameClock*',`Glib::RefPtr<Gdk::FrameClock>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gdk::FrameClock>&',`GdkFrameClock*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`GdkFrameTimings*',`Glib::RefPtr<FrameTimings>',`Glib::wrap($3)')

# XPM data
_CONVERSION(`const char*const*',`const char**',`const_cast<const char**>($3)',`$3')


_CONVERSION(`GdkTimeCoord**&',`GdkTimeCoord***',`&($3)')

dnl _CONVERSION(GdkBitmap*,Gdk::Bitmap&,`Glib::unwrap_boxed($3)',`$3')

dnl GdkEvent and GdkEventSequence
_CONVERSION(`GdkEvent*',`Glib::RefPtr<Event>',`Glib::wrap($3)')
_CONVERSION(`GdkEvent*',`Glib::RefPtr<Gdk::Event>',`Glib::wrap($3)')
_CONVERSION(`GdkEvent*',`Glib::RefPtr<const Gdk::Event>',`Glib::wrap($3)')
_CONVERSION(`const GdkEvent*',`Glib::RefPtr<const Gdk::Event>',`Glib::wrap(const_cast<GdkEvent*>($3))')
_CONVERSION(`const Glib::RefPtr<Event>&',`GdkEvent*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gdk::Event>&',`GdkEvent*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Event>&',`GdkEvent*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Gdk::Event>&',`GdkEvent*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Event>&',`const GdkEvent*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Gdk::Event>&',`const GdkEvent*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`Gdk::EventSequence*',`GdkEventSequence*',`reinterpret_cast<$2>($3)')
_CONVERSION(`GdkEventSequence*',`Gdk::EventSequence*',`reinterpret_cast<$2>($3)')
_CONVERSION(`GdkEventSequence*',`const EventSequence*',`reinterpret_cast<$2>($3)')

_CONVERSION(`GdkDrag*',`Glib::RefPtr<Drag>',Glib::wrap($3))
_CONVERSION(`GdkDrag*',`Glib::RefPtr<Gdk::Drag>',Glib::wrap($3))
_CONVERSION(`GdkDrop*',`Glib::RefPtr<Drop>',Glib::wrap($3))
_CONVERSION(`GdkDrop*',`Glib::RefPtr<Gdk::Drop>',Glib::wrap($3))

# Graphene
_CONVERSION(`const Point&',`const graphene_point_t*',`($3).gobj()')
_CONVERSION(`const Gdk::Graphene::Point&',`const graphene_point_t*',`($3).gobj()')
_CONVERSION(`const Rect&',`const graphene_rect_t*',`($3).gobj()')
_CONVERSION(`const Gdk::Graphene::Rect&',`const graphene_rect_t*',`($3).gobj()')
_CONVERSION(`const Size&',`const graphene_size_t*',`($3).gobj()')
_CONVERSION(`const Gdk::Graphene::Size&',`const graphene_size_t*',`($3).gobj()')

