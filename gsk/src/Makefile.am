## Copyright (C) 2025 The gtkmm Development Team
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

binding_name    = gskmm
wrap_init_flags = --namespace=Gsk --parent_dir=gskmm
codegen_srcdir  = $(top_srcdir)/tools

include $(srcdir)/filelist.gmake.am
include $(top_srcdir)/tools/m4/filelist.am

files_defs = $(gskmm_files_defs)
files_ccg  = $(gskmm_files_ccg)
files_hg   = $(gskmm_files_hg)

include $(top_srcdir)/build/generate-binding.am
