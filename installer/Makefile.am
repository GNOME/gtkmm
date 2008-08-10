SUBDIRS = NSISLibrary translations

BUILT_SOURCES = lgpl.txt

MAINTAINERCLEANFILES = $(built_sources)
DISTCLEANFILES = $(built_sources)

EXTRA_DIST = lgpl.txt gtkmm.ico gtkmm_win32.txt gtkmm-installer.nsi gtk_devel_setup-2.10.ini gtk_runtime_setup-2.10.ini

# Copy COPYING file to lgpl.txt, used as license text by the installer

lgpl.txt: $(top_srcdir)/COPYING
	cp -f $(top_srcdir)/COPYING $@
