## Copyright (c) 2001
## The gtkmm development team.

include $(srcdir)/../../src/Makefile_list_of_hg.am_fragment
files_built_h = $(files_hg:.hg=_p.h)

private_includedir	= $(includedir)/atkmm-1.3/atkmm/private
private_include_HEADERS	= $(files_built_h)

maintainer-clean-local:
	(cd $(srcdir) && rm -f $(files_built_h))



