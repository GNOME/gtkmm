BUILT_SOURCES = gtkmmconfig.h gtkmm-2.4.rc

MAINTAINERCLEANFILES = $(built_sources)
DISTCLEANFILES = gtkmmconfig.h

EXTRA_DIST = gtkmmconfig.h gtkmm.vcproj gtkmm-2.4.rc

gtkmmconfig.h: $(top_builddir)/gtk/gtkmmconfig.h
	cp -f $< $@
