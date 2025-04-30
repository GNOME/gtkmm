## gtkmm - a C++ wrapper for the Gtk toolkit
##
## Copyright (C) 2025 The gtkmm Development Team
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

include(convert_glib.m4)

# Enums
_CONV_ENUM(Gsk,BlendMode)
_CONV_ENUM(Gsk,Corner)
_CONV_ENUM(Gsk,FillRule)
_CONV_ENUM(Gsk,MaskMode)
_CONV_ENUM(Gsk,ScalingFilter)
_CONV_INCLASS_ENUM(Gsk,Transform,Category)

_CONVERSION(`const Gsk::RoundedRect&',`const GskRoundedRect*',($3).gobj())

_CONVERSION(`const Glib::RefPtr<Transform>&',`GskTransform*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gsk::Transform>&',`GskTransform*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Transform>&',`GskTransform*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Gsk::Transform>&',`GskTransform*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`GskTransform*',`Glib::RefPtr<Transform>',`Glib::wrap($3)')
_CONVERSION(`GskTransform*',`Glib::RefPtr<Gsk::Transform>',`Glib::wrap($3)')
