## gtkmm - a C++ wrapper for the Gtk toolkit
##
## Copyright (C) 2003-2010 The gtkmm Development Team
##
## This library is free software; you can redistribute it and/or
## modify it under the terms of the GNU Lesser General Public
## License as published by the Free Software Foundation; either
## version 2.1 of the License, or (at your option) any later version.
##
## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public
## License along with this library; if not, see <http://www.gnu.org/licenses/>.

include(class_gtkobject.m4)
include(convert_base.m4)
include(convert_gtk.m4)
include(convert_gdk.m4)
include(convert_gsk.m4)

# From pangomm: The path to this is obtained in configure.ac or meson.build.
include(convert_pango.m4)

include(convert_glib.m4)
