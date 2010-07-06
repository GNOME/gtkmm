## gtkmm - a C++ wrapper for the Gtk toolkit
##
## Copyright 2003-2010 The gtkmm Development Team
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
## License along with this library; if not, write to the Free
## Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

include(convert_glib.m4)

_EQUAL(State,AtkState)

_CONV_ENUM(Atk,Role)
_CONV_ENUM(Atk,Layer)
_CONV_ENUM(Atk,RelationType)
_CONV_ENUM(Atk,StateType)
_CONV_ENUM(Atk,CoordType)
_CONV_ENUM(Atk,TextBoundary)
_CONV_ENUM(Atk,TextClipType)


_CONVERSION(`AtkObject*',`Glib::RefPtr<Atk::Object>',Glib::wrap($3))
_CONVERSION(`AtkObject*',`Glib::RefPtr<Object>',Glib::wrap($3))
_CONVERSION(`AtkObject*',`Glib::RefPtr<Atk::Object>',Glib::wrap($3))
_CONVERSION(`AtkObject*',`Glib::RefPtr<const Object>',Glib::wrap($3))
_CONVERSION(`AtkObject*',`Glib::RefPtr<const Atk::Object>',Glib::wrap($3))
_CONVERSION(`const Glib::RefPtr<Object>&',`AtkObject*',`Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<Atk::Object>&',`AtkObject*',`Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Atk::Object>',`AtkObject*',`Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Object>',`AtkObject*',`Glib::unwrap($3)')
_CONVERSION(`AtkRelationSet*',`Glib::RefPtr<RelationSet>',Glib::wrap($3))
_CONVERSION(`const Glib::RefPtr<Relation>&',`AtkRelation*',`Glib::unwrap($3)')
_CONVERSION(`AtkRelation*',`Glib::RefPtr<Relation>',Glib::wrap($3))
_CONVERSION(`AtkStateSet*',`Glib::RefPtr<StateSet>',Glib::wrap($3))
_CONVERSION(`const Glib::RefPtr<StateSet>&',`AtkStateSet*',`Glib::unwrap($3)')

_CONVERSION(`AtkGObjectAccessible*',`Glib::RefPtr<ObjectAccessible>',Glib::wrap($3))
_CONVERSION(`AtkGObjectAccessible*',`Glib::RefPtr<const ObjectAccessible>',Glib::wrap($3))

_CONVERSION(`AtkHyperlink*',`Glib::RefPtr<Hyperlink>',Glib::wrap($3))
_CONVERSION(`AtkHyperlink*',`Glib::RefPtr<const Hyperlink>',Glib::wrap($3))

_CONVERSION(`AtkAttributeSet*', `AttributeSet', `AttributeSet($3, Glib::OWNERSHIP_DEEP)')
_CONVERSION(`const AttributeSet&', `AtkAttributeSet*', `($3).data()')

_CONVERSION(`GIOChannel*',`Glib::RefPtr<Glib::IOChannel>',Glib::wrap($3))

_CONVERSION(`Rectangle&', `AtkTextRectangle*', `&($3)')
_CONVERSION(`const Rectangle&', `AtkTextRectangle*', `const_cast<AtkTextRectangle*>(&($3))')



