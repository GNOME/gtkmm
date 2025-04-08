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

AUTOMAKE_OPTIONS = subdir-objects

check_PROGRAMS =			\
	bitset_iterator/test \
	builder/test		\
	child_widget/test		\
	child_widget2/test		\
	child_widget_managed/test	\
	delete_cpp_child/test		\
	dialog_deletethis/test		\
	filedialog/test \
	gdk_graphene/test \
	gdk_rgba/test \
	get_children/test \
	main_with_options/test		\
	object_move/test		\
	property_notification/test	\
	refcount_dialog/test		\
	scrolledwindow/test		\
	tree_model_iterator/test \
	wrap_existing/test

TESTS = bitset_iterator/test \
	object_move/test \
  gdk_graphene/test \
  gdk_rgba/test \
  test_validate_docs_xhtml.sh

bitset_iterator_test_SOURCES       = bitset_iterator/main.cc
builder_test_SOURCES               = builder/main.cc
child_widget_test_SOURCES          = child_widget/main.cc	\
                                     child_widget/testwindow.cc	\
                                     child_widget/testwindow.h
child_widget2_test_SOURCES         = child_widget2/main.cc
child_widget_managed_test_SOURCES  = child_widget_managed/main.cc
delete_cpp_child_test_SOURCES      = delete_cpp_child/main.cc
dialog_deletethis_test_SOURCES     = dialog_deletethis/main.cc
filedialog_test_SOURCES            = filedialog/main.cc
gdk_graphene_test_SOURCES          = gdk_graphene/main.cc
gdk_rgba_test_SOURCES              = gdk_rgba/main.cc
get_children_test_SOURCES          = get_children/main.cc
main_with_options_test_SOURCES     = main_with_options/main.cc
object_move_test_SOURCES           = object_move/main.cc
property_notification_test_SOURCES = property_notification/main.cc
refcount_dialog_test_SOURCES       = refcount_dialog/main.cc
scrolledwindow_test_SOURCES        = scrolledwindow/main.cc
tree_model_iterator_test_SOURCES   = tree_model_iterator/main.cc
wrap_existing_test_SOURCES         = wrap_existing/main.cc

gdkmm_includes = -I$(top_builddir)/gdk $(if $(srcdir:.=),-I$(top_srcdir)/gdk)
gdkmm_ldadd    =

gskmm_includes = -I$(top_builddir)/gsk $(if $(srcdir:.=),-I$(top_srcdir)/gsk)
gskmm_ldadd    =

gtkmm_includes = -I$(top_builddir)/gtk $(if $(srcdir:.=),-I$(top_srcdir)/gtk)
gtkmm_ldadd    = $(top_builddir)/gtk/gtkmm/libgtkmm-$(GTKMM_API_VERSION).la

local_includes = -I$(top_builddir) $(gdkmm_includes) $(gskmm_includes) $(gtkmm_includes)
local_ldadd    = $(gdkmm_ldadd) $(gskmm_ldadd) $(gtkmm_ldadd)

AM_CPPFLAGS = $(local_includes) $(GTHREAD_CFLAGS) $(GTKMM_CFLAGS)
AM_CXXFLAGS = $(GTKMM_WXXFLAGS)
LDADD       = $(GTKMM_LIBS) $(local_ldadd)

EXTRA_DIST = test_validate_docs_xhtml.sh
