// -*- c++ -*-
#ifndef _GTKMM_ACCELMAP_H
#define _GTKMM_ACCELMAP_H

/* $Id$ */

/* accelmap.h
 *
 * Copyright (C) 2002 The Gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <string>

#include <gdkmm/types.h>

namespace Gtk
{

namespace AccelMap
{

void add_entry(const std::string& accel_path, 
               guint accel_key, 
               Gdk::ModifierType accel_mods);
bool change_entry(const std::string& accel_path, 
                  guint accel_key, 
                  Gdk::ModifierType accel_mods,
                  bool replace);

void load(const std::string& filename);
void save(const std::string& filename);

} // namespace AccelMap

} // namespace Gtk


#endif /* _GTKMM_ACCELMAP_H */

