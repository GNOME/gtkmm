// -*- c++ -*-
/* $Id$ */

/*
 *
 * Copyright 1998-2003 The gtkmm Development Team
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

#include <gtkmm/toolbar_elements.h>
#include <glib.h>
#include <gtkmm/button.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/tooltips.h>
#include <gtkmm/label.h>
#include <gtk/gtklabel.h>


// static
GType Glib::Value<Gtk::ToolbarChildType>::value_type()
{
  return gtk_toolbar_child_type_get_type();
}

namespace Gtk
{

// Everything here is deprecated. See toolbar.h.
namespace Toolbar_Helpers
{

/*********************************************************************
***** Item classes (This should be an easy and cool interface)
*********************************************************************/

Element::Element(const Element& other)
:
  type_                 (other.type_),
  widget_               (other.widget_),
  text_                 (other.text_),
  has_text_             (other.has_text_),
  stock_id_             (other.stock_id_),
  tooltip_text_         (other.tooltip_text_),
  tooltip_private_text_ (other.tooltip_private_text_),
  content_              (other.content_),
  callback_             (other.callback_),
  group_                (0)
{}

Element::Element(ToolbarChildType  type,
                                  Widget*              widget,
                                  const Glib::ustring& text,
                                  bool                 has_text,
                                  const Gtk::StockID&  stock_id,
                                  const Glib::ustring& tooltip_text,
                                  const Glib::ustring& tooltip_private_text,
                                  Widget*              content,
                                  const Callback0&     callback)
:
  type_                 (type),
  widget_               (widget),
  text_                 (text),
  has_text_             (has_text),
  stock_id_             (stock_id),
  tooltip_text_         (tooltip_text),
  tooltip_private_text_ (tooltip_private_text),
  content_              (content),
  callback_             (callback),
  group_                (0)
{}

Element::Element(Widget&         widget,
                                  const Glib::ustring& tooltip_text,
                                  const Glib::ustring& tooltip_private_text)
:
  type_                 (TOOLBAR_CHILD_WIDGET),
  widget_               (&widget),
  text_                 (),
  has_text_             (false),
  stock_id_             (Glib::ustring()),
  tooltip_text_         (tooltip_text),
  tooltip_private_text_ (tooltip_private_text),
  content_              (0),
  callback_             (),
  group_                (0)
{}

Space::Space()
:
  Element(TOOLBAR_CHILD_SPACE,
          0,
          Glib::ustring(),
          false,
          Gtk::StockID(Glib::ustring()),
          Glib::ustring(),
          Glib::ustring(),
          0,
          Callback0())
{}

StockElem::StockElem(const Gtk::StockID&   stock_id,
                     const Callback0&      callback,
                     const Glib::ustring&  tooltip_text,
                     const Glib::ustring&  tooltip_private_text)
:
  Element(TOOLBAR_CHILD_SPACE,
          0,
          Glib::ustring(),
          false,
          stock_id,
          tooltip_text,
          tooltip_private_text,
          0,
          callback)
{}

ButtonElem::ButtonElem(const Glib::ustring& text,
                                        Widget&         content,
                                        const Callback0&     callback,
                                        const Glib::ustring& tooltip_text,
                                        const Glib::ustring& tooltip_private_text)
:
  Element(TOOLBAR_CHILD_BUTTON,
          0,
          text,
          true,
          Gtk::StockID(Glib::ustring()),
          tooltip_text,
          tooltip_private_text,
          &content,
          callback)
{}

ButtonElem::ButtonElem(const Glib::ustring& text,
                                        const Callback0&     callback,
                                        const Glib::ustring& tooltip_text,
                                        const Glib::ustring& tooltip_private_text)

:
  Element(TOOLBAR_CHILD_BUTTON,
          0,
          text,
          true,
          Gtk::StockID(Glib::ustring()),
          tooltip_text,
          tooltip_private_text,
          0,
          callback)
{}

ButtonElem::ButtonElem(Widget&         content,
                                        const Callback0&     callback,
                                        const Glib::ustring& tooltip_text,
                                        const Glib::ustring& tooltip_private_text)
:
  Element(TOOLBAR_CHILD_BUTTON,
          0,
          Glib::ustring(),
          false,
          Gtk::StockID(Glib::ustring()),
          tooltip_text,
          tooltip_private_text,
          &content,
          callback)
{}

ToggleElem::ToggleElem(const Glib::ustring& text,
                                        Widget&         content,
                                        const Callback0&     callback,
                                        const Glib::ustring& tooltip_text,
                                        const Glib::ustring& tooltip_private_text)
:
  Element(TOOLBAR_CHILD_TOGGLEBUTTON,
          0,
          text,
          true,
          Gtk::StockID(Glib::ustring()),
          tooltip_text,
          tooltip_private_text,
          &content,
          callback)
{}

ToggleElem::ToggleElem(const Glib::ustring& text,
                                        const Callback0&     callback,
                                        const Glib::ustring& tooltip_text,
                                        const Glib::ustring& tooltip_private_text)
:
  Element(TOOLBAR_CHILD_TOGGLEBUTTON,
          0,
          text,
          true,
          Gtk::StockID(Glib::ustring()),
          tooltip_text,
          tooltip_private_text,
          0,
          callback)
{}

ToggleElem::ToggleElem(Widget&         content,
                                        const Callback0&     callback,
                                        const Glib::ustring& tooltip_text,
                                        const Glib::ustring& tooltip_private_text)
:
  Element(TOOLBAR_CHILD_TOGGLEBUTTON,
          0,
          Glib::ustring(),
          false,
          Gtk::StockID(Glib::ustring()),
          tooltip_text,
          tooltip_private_text,
          &content,
          callback)
{}

RadioElem::RadioElem(RadioButton::Group&  group,
                                      const Glib::ustring& text,
                                      Widget&         content,
                                      const Callback0&     callback,
                                      const Glib::ustring& tooltip_text,
                                      const Glib::ustring& tooltip_private_text)
:
  Element(TOOLBAR_CHILD_RADIOBUTTON,
          0,
          text,
          true,
          Gtk::StockID(Glib::ustring()),
          tooltip_text,
          tooltip_private_text,
          &content,
          callback)
{
  group_ = &group;
}

RadioElem::RadioElem(RadioButton::Group&  group,
                                      const Glib::ustring& text,
                                      const Callback0&     callback,
                                      const Glib::ustring& tooltip_text,
                                      const Glib::ustring& tooltip_private_text)
:
  Element(TOOLBAR_CHILD_RADIOBUTTON,
          0,
          text,
          true,
          Gtk::StockID(Glib::ustring()),
          tooltip_text,
          tooltip_private_text,
          0,
          callback)
{
  group_ = &group;
}

RadioElem::RadioElem(RadioButton::Group&  group,
                                      Widget&         content,
                                      const Callback0&     callback,
                                      const Glib::ustring& tooltip_text,
                                      const Glib::ustring& tooltip_private_text)
:
  Element(TOOLBAR_CHILD_RADIOBUTTON,
          0,
          Glib::ustring(),
          false,
          Gtk::StockID(Glib::ustring()),
          tooltip_text,
          tooltip_private_text,
          &content,
          callback)
{
  group_ = &group;
}


/*********************************************************************
***** List properties
*********************************************************************/
ToolList::iterator ToolList::insert(ToolList::iterator position, const Element& e)
{
  int pos = gparent()->num_children;

  // locate the items desired position
  if(position.node_)
    pos = g_list_position(glist(), position.node_);

  const char* text    = 0;
  const char* tooltip = 0;
  const char* tooltip_private = 0;
  Widget* w = NULL;

  if(e.has_text_)
    text = e.text_.c_str();

  if(!e.tooltip_text_.empty())
    tooltip = e.tooltip_text_.c_str();

  if(!e.tooltip_private_text_.empty())
    tooltip_private = e.tooltip_private_text_.c_str();

  // give item to gtk+
  if (e.stock_id_.get_string().empty ()) {
    w = Glib::wrap(
      gtk_toolbar_insert_element(gparent(),
                                 (GtkToolbarChildType)e.type_,
                                 ((e.widget_) ? e.widget_->gobj() : 0),
                                 text, tooltip, tooltip_private,
                                 ((e.content_) ? e.content_->gobj() : 0),
                                 0, 0,
                                 pos));
  } else {
    w = Glib::wrap(
      gtk_toolbar_insert_stock(gparent(),
                               e.stock_id_.get_string().c_str(),
                               tooltip, tooltip_private,
                               0, 0,
                               pos));
  }

  if(e.group_ && w)
  {
    RadioButton* rb = dynamic_cast<RadioButton*>(w);
    rb->set_group(*e.group_);
    *(e.group_) = rb->get_group(); // TODO: What is this for?
  }

  // connect slot
  if(e.callback_ && w)
  {
    if(Button* btn = dynamic_cast<Button*>(w))
      btn->signal_clicked().connect(e.callback_);
  }

  // return the right iterator
  if(pos == 0)
    return begin();

  if(!position.node_)
    return --end();

  return --position;
}


ToolList::iterator ToolList::erase(ToolList::iterator position)
{
  if(!position.node_)
    return end();

  iterator next = position;
  ++next;

  if(position->get_type() == TOOLBAR_CHILD_SPACE)
  {
    gtk_toolbar_remove_space(gparent(), g_list_position(glist(), position.node_));
  }
  else
  {
    gtk_container_remove(
        reinterpret_cast<GtkContainer*>(gparent()),
        position->get_widget()->gobj());
  }

  return next;
}

void ToolList::remove(const_reference t)
{
  erase(find(t));
}

void ToolList::remove(Widget& widget)
{
  gtk_container_remove(
      reinterpret_cast<GtkContainer*>(gparent()), widget.gobj());
}

ToolbarChildType Tool::get_type() const
{
  return (ToolbarChildType) type;
}

Widget* Tool::get_widget() const
{
  return Glib::wrap(widget);
}

Widget* Tool::get_content() const
{
  return Glib::wrap(icon);
}

Label* Tool::get_label() const
{
  return Glib::wrap(reinterpret_cast<GtkLabel*>(label));
}

} // namespace Toolbar_Helpers


} // namespace Gtk

