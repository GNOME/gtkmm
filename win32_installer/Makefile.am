SUBDIRS = NSISLibrary translations

BUILT_SOURCES = lgpl.txt

MAINTAINERCLEANFILES = $(built_sources)
DISTCLEANFILES = $(built_sources)

EXTRA_DIST = lgpl.txt gtkmm.ico gtkmm_win32.txt gtk_devel_setup-2.12.ini gtk_runtime_setup-2.12.ini README gtkmm-2.4.vsprops gtkmm-2.4d.vsprops install-msvc-module build-installer

# Copy COPYING file to lgpl.txt, used as license text by the installer

lgpl.txt: $(top_srcdir)/COPYING
	cp -f $(top_srcdir)/COPYING $@
