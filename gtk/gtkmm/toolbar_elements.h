#ifndef _GTKMM_TOOLBAR_ELEMENTS_H
#define _GTKMM_TOOLBAR_ELEMENTS_H
/* $Id$ */

/* Copyright (C) 1998-2003 The gtkmm Development Team
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

#ifndef GTKMM_DISABLE_DEPRECATED

#include <glibmm/helperlist.h>
#include <gtkmm/container.h>
#include <gtkmm/stockid.h>

//TODO: Undef and redef it if's it's deprecated.
//#undef GTK_DISABLE_DEPRECATED
#include <gtk/gtktoolbar.h> // Needed for GtkToolbarChild (which is deprecated)
//#define GTK_DISABLE_DEPRECATED

namespace Gtk
{

/** @addtogroup gtkmmEnums Enums and Flags */

/**
 * @ingroup gtkmmEnums
 */
enum ToolbarChildType
{
  TOOLBAR_CHILD_SPACE,
  TOOLBAR_CHILD_BUTTON,
  TOOLBAR_CHILD_TOGGLEBUTTON,
  TOOLBAR_CHILD_RADIOBUTTON,
  TOOLBAR_CHILD_WIDGET
};

} //namespace Gtk

namespace Glib
{

template <>
class Value<Gtk::ToolbarChildType> : public Glib::Value_Enum<Gtk::ToolbarChildType>
{
public:
  static GType value_type() G_GNUC_CONST;
};

} //namespace Glib

namespace Gtk
{

/** @defgroup Toolbars Toolbar classes
 */

class Toolbar;

class RadioButtonGroup;


namespace Toolbar_Helpers
{

typedef SigC::Slot0<void> Callback0;

// Tool is the output class (very thin wrapper)
class Tool : private GtkToolbarChild
{
private:
  Tool(const Tool&);
  Tool& operator=(const Tool&);

public:
  ToolbarChildType get_type() const;
  Widget* get_widget()  const;
  Widget* get_content() const;
  Label*  get_label()   const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  friend class Dummy_; // silence the compiler (Child has only private ctors)
#endif
};

// Element is the input class
class ToolList;
class Element
{
friend class ToolList;
protected:
  ToolbarChildType    type_;
  Widget*             widget_;
  Glib::ustring       text_;
  bool                has_text_;
  StockID             stock_id_;
  Glib::ustring       tooltip_text_;
  Glib::ustring       tooltip_private_text_;
  Widget*             content_; // This does not need to be a pixmap.
  Callback0           callback_;
  RadioButtonGroup* group_;

private:
  Element& operator=(const Element&);

protected:
  // some fields are mutually exclusive
  Element(ToolbarChildType      type,
          Widget*               widget,
          const Glib::ustring&  text,
          bool                  has_text,
          const Gtk::StockID&   stock_id,
          const Glib::ustring&  tooltip_text,
          const Glib::ustring&  tooltip_private_text,
          Widget*               content,
          const Callback0&      callback);

public:
  Element(const Element& other);

  Element(Widget& widget,
          const Glib::ustring& tooltip_text         = Glib::ustring(),
          const Glib::ustring& tooltip_private_text = Glib::ustring());
};

/** @ingroup Toolbars
 */
struct Space : public Element
{
  Space();
};

/** @ingroup Toolbars
 */
struct StockElem : public Element
{
  StockElem(const Gtk::StockID&  stock_id,
            const Callback0&     callback,
            const Glib::ustring& tooltip_text         = Glib::ustring(),
            const Glib::ustring& tooltip_private_text = Glib::ustring());
};

typedef Element WidgetElem;

// Order here is different than gtk+, watch yourself
// Each button set has 3 forms
//   with a Glib::ustring and content
//   with a Glib::ustring
//   with content (ie Pixmap, images, etc)
//
/** @ingroup Toolbars
 */
struct ButtonElem : public Element
{
  ButtonElem(const Glib::ustring& text,
             Widget&         content,
             const Callback0&     callback,
             const Glib::ustring& tooltip_text         = Glib::ustring(),
             const Glib::ustring& tooltip_private_text = Glib::ustring());

  ButtonElem(Widget&         content,
             const Callback0&     callback,
             const Glib::ustring& tooltip_text         = Glib::ustring(),
             const Glib::ustring& tooltip_private_text = Glib::ustring());

  ButtonElem(const Glib::ustring& text,
             const Callback0&     callback,
             const Glib::ustring& tooltip_text         = Glib::ustring(),
             const Glib::ustring& tooltip_private_text = Glib::ustring());
};

/** @ingroup Toolbars
 */
struct ToggleElem : public Element
{
  ToggleElem(const Glib::ustring& text,
             Widget&         content,
             const Callback0&     callback,
             const Glib::ustring& tooltip_text         = Glib::ustring(),
             const Glib::ustring& tooltip_private_text = Glib::ustring());

  ToggleElem(Widget&         content,
             const Callback0&     callback,
             const Glib::ustring& tooltip_text         = Glib::ustring(),
             const Glib::ustring& tooltip_private_text = Glib::ustring());

  ToggleElem(const Glib::ustring& text,
             const Callback0&     callback,
             const Glib::ustring& tooltip_text         = Glib::ustring(),
             const Glib::ustring& tooltip_private_text = Glib::ustring());
};

/** @ingroup Toolbars
 */
struct RadioElem : public Element
{
  RadioElem(RadioButtonGroup& group,
            const Glib::ustring& text,
            Widget&         content,
            const Callback0&     callback             = Callback0(),
            const Glib::ustring& tooltip_text         = Glib::ustring(),
            const Glib::ustring& tooltip_private_text = Glib::ustring());

  RadioElem(RadioButtonGroup& group,
            Widget&         content,
            const Callback0&     callback             = Callback0(),
            const Glib::ustring& tooltip_text         = Glib::ustring(),
            const Glib::ustring& tooltip_private_text = Glib::ustring());

  RadioElem(RadioButtonGroup& group,
            const Glib::ustring& text,
            const Callback0&     callback             = Callback0(),
            const Glib::ustring& tooltip_text         = Glib::ustring(),
            const Glib::ustring& tooltip_private_text = Glib::ustring());
};

} // namespace Toolbar_Helpers

} // namespace Gtk

#endif //GTKMM_DISABLE_DEPRECATED

#endif //_GTKMM_TOOLBAR_ELEMENTS_H
