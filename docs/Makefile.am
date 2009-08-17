## Copyright (c) 2009  Openismus GmbH  <http://www.openismus.com/>
##
## This file is part of gtkmm.
##
## gtkmm is free software: you can redistribute it and/or modify it
## under the terms of the GNU Lesser General Public License as published
## by the Free Software Foundation, either version 2.1 of the License,
## or (at your option) any later version.
##
## gtkmm is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
## See the GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this library.  If not, see <http://www.gnu.org/licenses/>.

include $(top_srcdir)/atk/src/filelist.am
include $(top_srcdir)/atk/atkmm/filelist.am
include $(top_srcdir)/gdk/src/filelist.am
include $(top_srcdir)/gdk/gdkmm/filelist.am
include $(top_srcdir)/gtk/src/filelist.am
include $(top_srcdir)/gtk/gtkmm/filelist.am

atkmm_files_h = $(atkmm_files_built_h) $(filter-out wrap_init.h,$(atkmm_files_extra_h))
gdkmm_files_h = $(gdkmm_files_built_h) $(filter-out wrap_init.h,$(gdkmm_files_extra_h))
gtkmm_files_h = $(gtkmm_files_built_h) $(filter-out wrap_init.h,$(gtkmm_files_extra_h))

book_name = $(GTKMM_MODULE_NAME)
doc_input = $(addprefix $(top_srcdir)/atk/atkmm/,$(atkmm_files_h)) \
            $(addprefix $(top_srcdir)/gdk/gdkmm/,$(gdkmm_files_h)) \
            $(addprefix $(top_srcdir)/gtk/gtkmm/,$(gtkmm_files_h))

# Override the web location to use the old-style path with redundant
# directory components.
htmlrefpub = http://www.gtkmm.org/docs/$(book_name)/docs/reference/html/

docimagesdir = $(libdocdir)/images
dist_docimages_DATA = images/gtkmm_logo.gif images/top.gif

include $(top_srcdir)/build/doc-reference.am

dist_noinst_DATA +=				\
	reference/gtkmm_header.html_fragment	\
	reference/gtkmm_footer.html_fragment	\
	reference/widget_hierarchy.dia		\
	reference/widget_hierarchy.html		\
	reference/widget_hierarchy.png
