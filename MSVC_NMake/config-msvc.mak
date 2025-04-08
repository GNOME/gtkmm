# NMake Makefile portion for enabling features for Windows builds

!ifndef VULKAN_SDK_DIR
!message If you see compilation errors due to a missing vulkan/vulkan.h, or
!message missing vulkan-1.lib, consider passing
!message VULKAN_SDK_DIR=$$(root_directory_of_your_LunarG_Vulkan_SDK), which is
!message normally c:\VulkanSDK\$$(YOUR_LUNARG_VULKAN_SDK_VER) to the
!message NMake command line, and retry the build.
!message
VULKAN_SDK_DIR=$(VULKAN_SDK)
!endif

# These are the base minimum libraries required for building gtkmm.
BASE_INCLUDES =	/I$(PREFIX)\include

# Please do not change anything beneath this line unless maintaining the NMake Makefiles

# NMake Options
SAVED_OPTIONS = CFG^=$(CFG)

!ifdef VULKAN_SDK_DIR
SAVED_OPTIONS = $(SAVED_OPTIONS) VULKAN_SDK_DIR^=$(VULKAN_SDK_DIR)
!endif

!ifdef DISABLE_DEPRECATED
SAVED_OPTIONS = $(SAVED_OPTIONS) DISABLE_DEPRECATED^=$(DISABLE_DEPRECATED)
!endif

# Debug/Release builds
!if "$(CFG)" == "debug" || "$(CFG)" == "Debug"
DEBUG_SUFFIX = -d
!else
DEBUG_SUFFIX =
!endif

!ifndef GMMPROC_DIR
GMMPROC_DIR=$(PREFIX)\share\glibmm-$(GLIBMM_MAJOR_VERSION).$(GLIBMM_MINOR_VERSION)\proc
!endif

!ifndef GMMPROC_PANGO_DIR
GMMPROC_PANGO_DIR=$(GMMPROC_DIR)\..\..\pangomm-$(PANGOMM_MAJOR_VERSION).$(PANGOMM_MINOR_VERSION)\proc\m4
!endif

# Dependencies

GLIB_API_VERSION = 2.0
PANGO_API_VERSION = 1.0
GDK_PIXBUF_API_VERSION = 2.0
GRAPHENE_API_VERSION = 1.0
GTK_API_VERSION = 4

LIBSIGC_MAJOR_VERSION = 3
LIBSIGC_MINOR_VERSION = 0
CAIROMM_MAJOR_VERSION = 1
CAIROMM_MINOR_VERSION = 16
GLIBMM_MAJOR_VERSION = 2
GLIBMM_MINOR_VERSION = 68
PANGOMM_MAJOR_VERSION = 2
PANGOMM_MINOR_VERSION = 48
GTKMM_MAJOR_VERSION = 4
GTKMM_MINOR_VERSION = 0

GTKMM_CXX_INCLUDES =	\
	/I$(PREFIX)\include\pangomm-$(PANGOMM_MAJOR_VERSION).$(PANGOMM_MINOR_VERSION)	\
	/I$(PREFIX)\lib\pangomm-$(PANGOMM_MAJOR_VERSION).$(PANGOMM_MINOR_VERSION)\include	\
	/I$(PREFIX)\include\giomm-$(GLIBMM_MAJOR_VERSION).$(GLIBMM_MINOR_VERSION)	\
	/I$(PREFIX)\lib\giomm-$(GLIBMM_MAJOR_VERSION).$(GLIBMM_MINOR_VERSION)\include	\
	/I$(PREFIX)\include\glibmm-$(GLIBMM_MAJOR_VERSION).$(GLIBMM_MINOR_VERSION)	\
	/I$(PREFIX)\lib\glibmm-$(GLIBMM_MAJOR_VERSION).$(GLIBMM_MINOR_VERSION)\include	\
	/I$(PREFIX)\include\cairomm-$(CAIROMM_MAJOR_VERSION).$(CAIROMM_MINOR_VERSION)	\
	/I$(PREFIX)\lib\cairomm-$(CAIROMM_MAJOR_VERSION).$(CAIROMM_MINOR_VERSION)\include	\
	/I$(PREFIX)\include\sigc++-$(LIBSIGC_MAJOR_VERSION).$(LIBSIGC_MINOR_VERSION)	\
	/I$(PREFIX)\lib\sigc++-$(LIBSIGC_MAJOR_VERSION).$(LIBSIGC_MINOR_VERSION)\include

GTKMM_C_INCLUDES =	\
	/I$(PREFIX)\include\gtk-$(GTK_API_VERSION).0	\
	/I$(PREFIX)\include\gdk-pixbuf-$(GDK_PIXBUF_API_VERSION)	\
	/I$(PREFIX)\include\graphene-$(GRAPHENE_API_VERSION)	\
	/I$(PREFIX)\lib\graphene-$(GRAPHENE_API_VERSION)\include	\
	/I$(PREFIX)\include\pango-$(PANGO_API_VERSION)	\
	/I$(PREFIX)\include\glib-$(GLIB_API_VERSION)	\
	/I$(PREFIX)\lib\glib-$(GLIB_API_VERSION)\include	\
	/I$(PREFIX)\include\harfbuzz	\
	/I$(PREFIX)\include

# If gtk+ is built with Vulkan, we need to include the Vulkan headers and
# possibly the Vulkan import libraries
!ifdef VULKAN_SDK_DIR
GTKMM_C_INCLUDES = $(GTKMM_C_INCLUDES) /I$(VULKAN_SDK_DIR)\include
VULKAN_LIB = vulkan-1.lib
!if "$(PLAT)" == "x64"
VULKAN_LIBDIR_LDFLAG = /libpath:$(VULKAN_SDK_DIR)\lib
!else
VULKAN_LIBDIR_LDFLAG = /libpath:$(VULKAN_SDK_DIR)\lib32
!endif
!endif

GTKMM_INCLUDES =	\
	$(GTKMM_CXX_INCLUDES)	\
	$(GTKMM_C_INCLUDES)

VULKAN_LIBDIR_LDFLAG =
VULKAN_LIB =

GOBJECT_LIBS = gobject-$(GLIB_API_VERSION).lib gmodule-$(GLIB_API_VERSION).lib glib-$(GLIB_API_VERSION).lib
GIO_LIBS = gio-$(GLIB_API_VERSION).lib $(GOBJECT_LIBS)

CAIRO_LIBS = cairo-gobject.lib cairo.lib
EPOXY_LIB = epoxy.lib
GDK_PIXBUF_LIB = gdk_pixbuf-$(GDK_PIXBUF_API_VERSION).lib
GRAPHENE_LIB = graphene-$(GRAPHENE_API_VERSION).lib
GTK_LIB = gtk-$(GTK_API_VERSION).lib
PANGO_LIBS = pangocairo-$(PANGO_API_VERSION).lib pango-$(PANGO_API_VERSION).lib

GTKMM_LIBS_C_BASE =	\
	$(GDK_PIXBUF_LIB)	\
	$(GIO_LIBS)	\
	$(CAIRO_LIBS)	\
	$(VULKAN_LIBDIR_LDFLAG)	\
	$(VULKAN_LIB)

GDKMM_LIBS_C = \
	$(GTK_LIB)	\
	$(GTKMM_LIBS_C_BASE)

GDKMM_LIBS_CXX =	\
	$(GIOMM_LIB)	\
	$(GLIBMM_LIB)	\
	$(CAIROMM_LIB)	\
	$(LIBSIGC_LIB)

GTKMM_LIBS_C =	\
	$(GTK_LIB)	\
	$(GRAPHENE_LIB)	\
	$(PANGO_LIBS)	\
	$(GTKMM_LIBS_C_BASE)

GDKMM_DEP_LIBS = $(GDKMM_LIBS_CXX) $(GDKMM_LIBS_C)

GTKMM_DEP_LIBS =	\
	$(PANGOMM_LIB)	\
	$(GDKMM_LIBS_CXX)	\
	$(GTKMM_LIBS_C)

GTKMM_DEMO_DEP_LIBS = $(GTKMM_DEP_LIBS) $(EPOXY_LIB)

# CXXFLAGS
GDKMM_BASE_CFLAGS =		\
	/Ivs$(VSVER)\$(CFG)\$(PLAT)	\
	/I..\untracked\gdk /I..\untracked\gdk\gdkmm	\
	/I..\gdk /I.\gdkmm	\
	/std:c++17 /EHsc /FImsvc_recommended_pragmas.h /utf-8

GSKMM_BASE_CFLAGS =		\
	/Ivs$(VSVER)\$(CFG)\$(PLAT)	\
	/I..\untracked\gsk /I..\untracked\gsk\gskmm	\
	/I..\gsk /I.\gskmm	\
	$(GDKMM_BASE_CFLAGS)

GTKMM_BASE_CFLAGS =		\
	/Ivs$(VSVER)\$(CFG)\$(PLAT)	\
	/I..\untracked\gtk /I..\untracked\gtk\gtkmm	\
	/I..\gtk /I.\gtkmm	\
	/wd4250				\
	$(GSKMM_BASE_CFLAGS)

LIBGDKMM_CFLAGS =	\
	/DGDKMM_BUILD	\
	$(GDKMM_BASE_CFLAGS)	\
	$(GTKMM_INCLUDES)

LIBGSKMM_CFLAGS =	\
	/DGSKMM_BUILD	\
	$(GSKMM_BASE_CFLAGS)	\
	$(GTKMM_INCLUDES)

LIBGTKMM_CFLAGS =	\
	/DGTKMM_BUILD	\
	$(GTKMM_BASE_CFLAGS)	\
	$(GTKMM_INCLUDES)

GTKMM_DEMO_CFLAGS =	\
	$(GTKMM_BASE_CFLAGS)	\
	$(GTKMM_INCLUDES)	\
	$(CFLAGS)

# We build gtkmm-vc$(VSVER_LIB)-$(GTKMM_MAJOR_VERSION)_$(GTKMM_MINOR_VERSION).dll or
#          gtkmm-vc$(VSVER_LIB)-d-$(GTKMM_MAJOR_VERSION)_$(GTKMM_MINOR_VERSION).dll at least

# With /GL, gtkmm3-demo fails on VS 2015 and 2017 32 bit
# with an internal compiler error...
!if $(VSVER) < 16 && "$(PLAT)" == "Win32"
GTKMM_DEMO_CFLAGS = $(GTKMM_DEMO_CFLAGS:/GL=)
GTKMM_DEMO_LDFLAGS = $(LDFLAGS_NOLTCG)
!else
GTKMM_DEMO_LDFLAGS = $(LDFLAGS)
!endif

!if $(VSVER) > 14 && "$(USE_COMPAT_LIBS)" != ""
MESON_VERVER_LIB =
VSVER_LIB = 150
!else
VSVER_LIB = $(PDBVER)$(VSVER_SUFFIX)
MESON_VERVER_LIB = -vc$(VSVER_LIB)
!endif

!ifdef USE_MESON_LIBS
LIBSIGC_LIBNAME = sigc-$(LIBSIGC_MAJOR_VERSION).$(LIBSIGC_MINOR_VERSION)
GLIBMM_LIBNAME = glibmm$(MESON_VERVER_LIB)-$(GLIBMM_MAJOR_VERSION).$(GLIBMM_MINOR_VERSION)
GIOMM_LIBNAME = giomm$(MESON_VERVER_LIB)-$(GLIBMM_MAJOR_VERSION).$(GLIBMM_MINOR_VERSION)
CAIROMM_LIBNAME = cairomm$(MESON_VERVER_LIB)-$(CAIROMM_MAJOR_VERSION).$(CAIROMM_MINOR_VERSION)
PANGOMM_LIBNAME = pangomm$(MESON_VERVER_LIB)-$(PANGOMM_MAJOR_VERSION).$(PANGOMM_MINOR_VERSION)
GTKMM_LIBNAME = gtkmm$(MESON_VERVER_LIB)-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)
GTKMM_DLLNAME = $(GTKMM_LIBNAME)-1
!else
LIBSIGC_LIBNAME = sigc-vc$(VSVER_LIB)$(DEBUG_SUFFIX)-$(LIBSIGC_MAJOR_VERSION)_$(LIBSIGC_MINOR_VERSION)
GLIBMM_LIBNAME = glibmm-vc$(VSVER_LIB)$(DEBUG_SUFFIX)-$(GLIBMM_MAJOR_VERSION)_$(GLIBMM_MINOR_VERSION)
GIOMM_LIBNAME = giomm-vc$(VSVER_LIB)$(DEBUG_SUFFIX)-$(GLIBMM_MAJOR_VERSION)_$(GLIBMM_MINOR_VERSION)
CAIROMM_LIBNAME = cairomm-vc$(VSVER_LIB)$(DEBUG_SUFFIX)-$(CAIROMM_MAJOR_VERSION)_$(CAIROMM_MINOR_VERSION)
PANGOMM_LIBNAME = pangomm-vc$(VSVER_LIB)$(DEBUG_SUFFIX)-$(PANGOMM_MAJOR_VERSION)_$(PANGOMM_MINOR_VERSION)
GTKMM_LIBNAME = gtkmm-vc$(VSVER_LIB)$(DEBUG_SUFFIX)-$(GTKMM_MAJOR_VERSION)_$(GTKMM_MINOR_VERSION)
GTKMM_DLLNAME = $(GTKMM_LIBNAME)
!endif

LIBSIGC_LIB = $(LIBSIGC_LIBNAME).lib
GLIBMM_LIB = $(GLIBMM_LIBNAME).lib
GIOMM_LIB = $(GIOMM_LIBNAME).lib
CAIROMM_LIB = $(CAIROMM_LIBNAME).lib
PANGOMM_LIB = $(PANGOMM_LIBNAME).lib
GTKMM_LIB = $(GTKMM_LIBNAME).lib


GTKMM_DLL = vs$(VSVER)\$(CFG)\$(PLAT)\$(GTKMM_DLLNAME).dll
GTKMM_LIB = vs$(VSVER)\$(CFG)\$(PLAT)\$(GTKMM_LIBNAME).lib

GTKMM4_DEMO = vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo$(DEBUG_SUFFIX).exe

GTKMM_INT_EXTRA_SOURCES = $(gtkmm_files_extra_any_cc)
GTKMM_INT_EXTRA_HEADERS = $(gtkmm_files_extra_any_h)
GTKMM_INT_EXTRA_HEADERS_P = $(gtkmm_files_extra_ph:/=\)

GDKMM_HG_FILES = $(gdkmm_files_any_hg)
GSKMM_HG_FILES = $(gskmm_files_any_hg)
GTKMM_HG_FILES = $(gtkmm_files_any_hg)

ENABLED_DEPRECATED = no

!ifndef DISABLE_DEPRECATED
GTKMM_INT_EXTRA_SOURCES = $(GTKMM_INT_EXTRA_SOURCES) $(gtkmm_files_extra_deprecated_cc)
GTKMM_INT_EXTRA_HEADERS = $(GTKMM_INT_EXTRA_HEADERS) $(gtkmm_files_extra_deprecated_h)

GDKMM_HG_FILES = $(GDKMM_HG_FILES) $(gdkmm_files_deprecated_hg)
GSKMM_HG_FILES = $(GSKMM_HG_FILES) $(gskmm_files_deprecated_hg)
GTKMM_HG_FILES = $(GTKMM_HG_FILES) $(gtkmm_files_deprecated_hg)
ENABLED_DEPRECATED = yes
!endif

GDKMM_INT_GENERATED_HEADERS = $(GDKMM_HG_FILES:.hg=.h)
GDKMM_INT_GENERATED_HEADERS_P = $(GDKMM_HG_FILES:.hg=_p.h)
GDKMM_INT_GENERATED_SOURCES = $(GDKMM_HG_FILES:.hg=.cc) wrap_init.cc
GSKMM_INT_GENERATED_SOURCES = $(GSKMM_HG_FILES:.hg=.cc) wrap_init.cc
GTKMM_INT_GENERATED_SOURCES = $(GTKMM_HG_FILES:.hg=.cc) wrap_init.cc

# Path to glib-compile-resources.exe
!ifndef GLIB_COMPILE_RESOURCES
GLIB_COMPILE_RESOURCES = $(PREFIX)\bin\glib-compile-resources.exe
!endif
