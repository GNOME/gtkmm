## Copyright (c) 2001
## The gtkmm development team.

include $(srcdir)/../../src/Makefile_list_of_hg.am_fragment
include $(top_srcdir)/build_shared/Makefile_gensrc_platform.am_fragment

files_built_h		= $(files_hg:.hg=_p.h)
files_built_all_h	= $(files_all_hg:.hg=_p.h)
files_extra_h		= 
files_extra_all_h	= 

dist_sources = $(files_built_all_h) $(files_extra_all_h)
DISTFILES = $(DIST_COMMON) $(dist_sources)

private_includedir	= $(includedir)/gtkmm-2.4/pangomm/private
private_include_HEADERS	= $(files_built_h)

maintainer-clean-local:
	(cd $(srcdir) && rm -f $(files_built_h))

