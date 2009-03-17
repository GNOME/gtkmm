SUBDIRS = NSISLibrary translations

BUILT_SOURCES = lgpl.txt

MAINTAINERCLEANFILES = $(built_sources)
DISTCLEANFILES = $(built_sources)

EXTRA_DIST = lgpl.txt gtkmm.ico gtkmm_win32.txt redist_README.txt README \
             gtkmm-vc80-2_4.vsprops gtkmm-vc80-d-2_4.vsprops \
             gtkmm-vc90-2_4.vsprops gtkmm-vc90-d-2_4.vsprops \
             install-msvc-module build-installer

# Copy COPYING file to lgpl.txt, used as license text by the installer

lgpl.txt: $(top_srcdir)/COPYING
	cp -f $(top_srcdir)/COPYING $@
