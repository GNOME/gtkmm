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

binding_name    = gtkmm
wrap_init_flags = --namespace=Gtk --parent_dir=gtkmm
codegen_srcdir  = $(top_srcdir)/tools

include $(srcdir)/filelist.gmake.am
include $(top_srcdir)/tools/m4/filelist.am

files_defs = $(gtkmm_files_defs)
files_ccg  = $(gtkmm_files_ccg)
files_hg   = $(gtkmm_files_hg)

include $(top_srcdir)/build/generate-binding.am
