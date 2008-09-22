SUBDIRS = NSISLibrary translations

BUILT_SOURCES = lgpl.txt

MAINTAINERCLEANFILES = $(built_sources)
DISTCLEANFILES = $(built_sources)

EXTRA_DIST = lgpl.txt gtkmm.ico gtkmm_win32.txt README gtkmm-2.4.vsprops gtkmm-2.4d.vsprops install-msvc-module build-installer

# Copy COPYING file to lgpl.txt, used as license text by the installer

lgpl.txt: $(top_srcdir)/COPYING
	cp -f $(top_srcdir)/COPYING $@
