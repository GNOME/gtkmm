BUILT_SOURCES = gdkmmconfig.h gdkmm-2.4.rc

MAINTAINERCLEANFILES = $(built_sources)
DISTCLEANFILES = gdkmmconfig.h

EXTRA_DIST = gdkmmconfig.h gdkmm.vcproj gdkmm-2.4.rc

gdkmmconfig.h: $(top_builddir)/gdk/gdkmmconfig.h
	cp -f $< $@
