# Build the library, to be installed and used by other defs-generating code:

files_h = generate_extra_defs.h
files_cc = generate_extra_defs.cc

if PLATFORM_WIN32
no_undefined = -no-undefined
else
no_undefined =
endif

lib_LTLIBRARIES		= libgtkmm_generate_extra_defs-2.0.la
libgtkmm_generate_extra_defs_2_0_la_SOURCES = $(files_h) $(files_cc)
libgtkmm_generate_extra_defs_2_0_la_LDFLAGS = $(no_undefined) -version-info $(LIBGTKMM_SO_VERSION) $(LIBSTDCPP_LIBS)
libgtkmm_generate_extra_defs_2_0_la_LIBADD = $(GLIBMM_LIBS)

sublib_includedir	= $(includedir)/gtkmm-2.0/gtkmm_generate_extra_defs
sublib_include_HEADERS	= $(files_h)


# Build the generate_properties_defs utility executable.
# This is not used to build the rest of gtkmm.

INCLUDES = $(GTKMM_CFLAGS)
LIBS = $(GTKMM_LIBS)

noinst_PROGRAMS = generate_extra_defs
generate_extra_defs_SOURCES = generate_defs_gtk.cc
generate_extra_defs_LDADD = libgtkmm_generate_extra_defs-2.0.la
