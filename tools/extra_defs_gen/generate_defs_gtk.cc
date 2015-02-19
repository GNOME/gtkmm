/*
 * Copyright (C) 2001 The Free Software Foundation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif
// We always need to generate the .defs for all types because the code
// using deprecated API is generated unconditionally and only disabled
// at compile time.
#undef GDK_PIXBUF_DISABLE_DEPRECATED
#undef GDK_DISABLE_DEPRECATED
#undef GTK_DISABLE_DEPRECATED
#define GDK_DISABLE_DEPRECATION_WARNINGS 1

#include <glibmm_generate_extra_defs/generate_extra_defs.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>

#ifdef GDK_WINDOWING_X11
#include <gtk/gtkx.h>
#endif

#ifndef G_OS_WIN32
# include <gtk/gtkunixprint.h>
#endif

std::string get_child_properties(GType gtype);

int main(int argc, char** argv)
{
  gtk_init(&argc, &argv);

  std::cout << get_defs( GTK_TYPE_ABOUT_DIALOG )
            << get_defs( GTK_TYPE_ACCEL_GROUP )
            << get_defs( GTK_TYPE_ACCEL_LABEL )
            << get_defs( GTK_TYPE_ACTION )
            << get_defs( GTK_TYPE_ACTION_GROUP )
            << get_defs( GTK_TYPE_ACTIONABLE )
            << get_defs( GTK_TYPE_ACTION_BAR )
            << get_defs( GTK_TYPE_ACTIVATABLE )
            << get_defs( GTK_TYPE_ADJUSTMENT )
            << get_defs( GTK_TYPE_ALIGNMENT)
            << get_defs( GTK_TYPE_APP_CHOOSER )
            << get_defs( GTK_TYPE_APP_CHOOSER_BUTTON )
            << get_defs( GTK_TYPE_APP_CHOOSER_DIALOG )
            << get_defs( GTK_TYPE_APP_CHOOSER_WIDGET )
            << get_defs( GTK_TYPE_APPLICATION )
            << get_defs( GTK_TYPE_APPLICATION_WINDOW )
            << get_defs( GTK_TYPE_ARROW )
            << get_defs( GTK_TYPE_ASPECT_FRAME )
            << get_defs( GTK_TYPE_ASSISTANT )
            << get_defs( GTK_TYPE_BIN )
            << get_defs( GTK_TYPE_BORDER )
            << get_defs( GTK_TYPE_BOX )
            << get_defs( GTK_TYPE_BUILDER )
            << get_defs( GTK_TYPE_BUTTON )
            << get_defs( GTK_TYPE_BUTTON_BOX )
            << get_defs( GTK_TYPE_CALENDAR )
            << get_defs( GTK_TYPE_CHECK_BUTTON )
            << get_defs( GTK_TYPE_CHECK_MENU_ITEM )
            << get_defs( GTK_TYPE_CELL_AREA )
            << get_defs( GTK_TYPE_CELL_AREA_BOX )
            << get_defs( GTK_TYPE_CELL_AREA_CONTEXT )
            << get_defs( GTK_TYPE_CELL_EDITABLE )
            << get_defs( GTK_TYPE_CELL_LAYOUT )
            << get_defs( GTK_TYPE_CELL_RENDERER )
            << get_defs( GTK_TYPE_CELL_RENDERER_ACCEL )
            << get_defs( GTK_TYPE_CELL_RENDERER_COMBO )
            << get_defs( GTK_TYPE_CELL_RENDERER_PROGRESS )
            << get_defs( GTK_TYPE_CELL_RENDERER_TEXT )
            << get_defs( GTK_TYPE_CELL_RENDERER_TOGGLE )
            << get_defs( GTK_TYPE_CELL_RENDERER_PIXBUF )
            << get_defs( GTK_TYPE_CELL_RENDERER_PROGRESS )
            << get_defs( GTK_TYPE_CELL_RENDERER_SPIN )
            << get_defs( GTK_TYPE_CELL_RENDERER_SPINNER )
            << get_defs( GTK_TYPE_CLIPBOARD )
            << get_defs( GTK_TYPE_COLOR_BUTTON )
            << get_defs( GTK_TYPE_COLOR_CHOOSER )
            << get_defs( GTK_TYPE_COLOR_CHOOSER_DIALOG )
            << get_defs( GTK_TYPE_COLOR_SELECTION )
            << get_defs( GTK_TYPE_COLOR_SELECTION_DIALOG )
            << get_defs( GTK_TYPE_COMBO_BOX )
            << get_defs( GTK_TYPE_CONTAINER )
            << get_defs( GTK_TYPE_CELL_VIEW )
            << get_defs( GTK_TYPE_CSS_PROVIDER )
            << get_defs( GTK_TYPE_DIALOG )
            << get_defs( GTK_TYPE_DRAWING_AREA )
            << get_defs( GTK_TYPE_EDITABLE )
            << get_defs( GTK_TYPE_ENTRY )
            << get_defs( GTK_TYPE_ENTRY_COMPLETION )
            << get_defs( GTK_TYPE_ENTRY_BUFFER )
            << get_defs( GTK_TYPE_EVENT_BOX )
            << get_defs( GTK_TYPE_EVENT_CONTROLLER )
            << get_defs( GTK_TYPE_EXPANDER )
            << get_defs( GTK_TYPE_FILE_FILTER )
            << get_defs( GTK_TYPE_FILE_CHOOSER )
            << get_defs( GTK_TYPE_FILE_CHOOSER_BUTTON )
            << get_defs( GTK_TYPE_FILE_CHOOSER_DIALOG )
            << get_defs( GTK_TYPE_FILE_CHOOSER_WIDGET )
            << get_defs( GTK_TYPE_FIXED )
            << get_defs( GTK_TYPE_FLOW_BOX )
            << get_defs( GTK_TYPE_FLOW_BOX_CHILD )
            << get_defs( GTK_TYPE_FONT_BUTTON )
            << get_defs( GTK_TYPE_FONT_CHOOSER )
            << get_defs( GTK_TYPE_FONT_CHOOSER_DIALOG )
            << get_defs( GTK_TYPE_FONT_CHOOSER_WIDGET )
            << get_defs( GTK_TYPE_FONT_SELECTION )
            << get_defs( GTK_TYPE_FONT_SELECTION_DIALOG )
            << get_defs( GTK_TYPE_FRAME )
            << get_defs( GTK_TYPE_GESTURE )
            << get_defs( GTK_TYPE_GESTURE_DRAG )
            << get_defs( GTK_TYPE_GESTURE_LONG_PRESS )
            << get_defs( GTK_TYPE_GESTURE_MULTI_PRESS )
            << get_defs( GTK_TYPE_GESTURE_PAN )
            << get_defs( GTK_TYPE_GESTURE_ROTATE )
            << get_defs( GTK_TYPE_GESTURE_SINGLE )
            << get_defs( GTK_TYPE_GESTURE_SWIPE )
            << get_defs( GTK_TYPE_GESTURE_ZOOM )
            << get_defs( GTK_TYPE_GRID )
            << get_defs( GTK_TYPE_HANDLE_BOX )
            << get_defs( GTK_TYPE_HEADER_BAR )
            << get_defs( GTK_TYPE_ICON_THEME )
            << get_defs( GTK_TYPE_IMAGE )
            << get_defs( GTK_TYPE_IMAGE_MENU_ITEM )
            << get_defs( GTK_TYPE_INFO_BAR )
            << get_defs( GTK_TYPE_INVISIBLE )
            << get_defs( GTK_TYPE_ICON_VIEW )
            << get_defs( GTK_TYPE_LABEL )
            << get_defs( GTK_TYPE_LAYOUT )
            << get_defs( GTK_TYPE_LEVEL_BAR)
            << get_defs( GTK_TYPE_LINK_BUTTON )
            << get_defs( GTK_TYPE_LIST_BOX )
            << get_defs( GTK_TYPE_LIST_BOX_ROW )
            << get_defs( GTK_TYPE_LOCK_BUTTON )
            << get_defs( GTK_TYPE_MENU )
            << get_defs( GTK_TYPE_MENU_BAR )
            << get_defs( GTK_TYPE_MENU_BUTTON )
            << get_defs( GTK_TYPE_MENU_ITEM )
            << get_defs( GTK_TYPE_MENU_SHELL )
            << get_defs( GTK_TYPE_MENU_TOOL_BUTTON )
            << get_defs( GTK_TYPE_MESSAGE_DIALOG )
            << get_defs( GTK_TYPE_MISC )
            << get_defs( GTK_TYPE_NOTEBOOK )
            << get_defs( GTK_TYPE_NUMERABLE_ICON )
            << get_defs( GTK_TYPE_OFFSCREEN_WINDOW )
            << get_defs( GTK_TYPE_ORIENTABLE )
            << get_defs( GTK_TYPE_OVERLAY )
            << get_defs( GTK_TYPE_PANED )
            << get_defs( GTK_TYPE_PLACES_SIDEBAR )
#ifdef GDK_WINDOWING_X11
            << get_defs( GTK_TYPE_PLUG )
#endif
            << get_defs( GTK_TYPE_POPOVER )
#if !defined(G_OS_WIN32) 
            << get_defs( GTK_TYPE_PRINTER )
            << get_defs( GTK_TYPE_PRINT_JOB )
#endif /* G_OS_WIN32 */
            << get_defs( GTK_TYPE_PRINT_OPERATION )
            << get_defs( GTK_TYPE_PRINT_OPERATION_PREVIEW )
#if !defined(G_OS_WIN32)
            << get_defs( GTK_TYPE_PAGE_SETUP_UNIX_DIALOG )
            << get_defs( GTK_TYPE_PRINT_UNIX_DIALOG )
#endif /* G_OS_WIN32 */
            << get_defs( GTK_TYPE_PRINT_SETTINGS )
            << get_defs( GTK_TYPE_PRINT_OPERATION_PREVIEW )
            << get_defs( GTK_TYPE_PROGRESS_BAR )
            << get_defs( GTK_TYPE_RADIO_BUTTON )
            << get_defs( GTK_TYPE_RADIO_TOOL_BUTTON )
            << get_defs( GTK_TYPE_RADIO_ACTION )
            << get_defs( GTK_TYPE_RADIO_MENU_ITEM )
            << get_defs( GTK_TYPE_RANGE )
            << get_defs( GTK_TYPE_RECENT_ACTION )
            << get_defs( GTK_TYPE_RECENT_CHOOSER )
            << get_defs( GTK_TYPE_RECENT_CHOOSER_MENU )
            << get_defs( GTK_TYPE_RECENT_CHOOSER_WIDGET )
            << get_defs( GTK_TYPE_RECENT_FILTER )
            << get_defs( GTK_TYPE_RECENT_MANAGER )
            << get_defs( GTK_TYPE_REVEALER )
            << get_defs( GTK_TYPE_SCALE )
            << get_defs( GTK_TYPE_SCALE_BUTTON )
            << get_defs( GTK_TYPE_SCROLLABLE )
            << get_defs( GTK_TYPE_SCROLLBAR )
            << get_defs( GTK_TYPE_SCROLLED_WINDOW )
            << get_defs( GTK_TYPE_SEARCH_BAR )
            << get_defs( GTK_TYPE_SEARCH_ENTRY )
            << get_defs( GTK_TYPE_SEPARATOR )
            << get_defs( GTK_TYPE_SEPARATOR_TOOL_ITEM )
            << get_defs( GTK_TYPE_SETTINGS )
            << get_defs( GTK_TYPE_SIZE_GROUP )
#ifdef GDK_WINDOWING_X11
            << get_defs( GTK_TYPE_SOCKET )
#endif
            << get_defs( GTK_TYPE_SPINNER )
            << get_defs( GTK_TYPE_SPIN_BUTTON )
            << get_defs( GTK_TYPE_STACK )
            << get_defs( GTK_TYPE_STACK_SIDEBAR )
            << get_defs( GTK_TYPE_STACK_SWITCHER )
            << get_defs( GTK_TYPE_STATUSBAR )
            << get_defs( GTK_TYPE_STATUS_ICON )
            << get_defs( GTK_TYPE_STYLE_CONTEXT )
            << get_defs( GTK_TYPE_STYLE_PROVIDER )
            << get_defs( GTK_TYPE_SWITCH )
            << get_defs( GTK_TYPE_TABLE )
            << get_defs( GTK_TYPE_TEAROFF_MENU_ITEM )
            << get_defs( GTK_TYPE_TOGGLE_BUTTON )
            << get_defs( GTK_TYPE_TOOLBAR )
            << get_defs( GTK_TYPE_TOOL_ITEM )
            << get_defs( GTK_TYPE_TOOL_ITEM_GROUP )
            << get_defs( GTK_TYPE_TOOL_PALETTE )
            << get_defs( GTK_TYPE_TOOL_BUTTON )
            << get_defs( GTK_TYPE_TEXT_BUFFER )
            << get_defs( GTK_TYPE_TEXT_MARK )
            << get_defs( GTK_TYPE_TEXT_TAG )
            << get_defs( GTK_TYPE_TEXT_TAG_TABLE )
            << get_defs( GTK_TYPE_TEXT_VIEW )
            << get_defs( GTK_TYPE_TOGGLE_ACTION )
            << get_defs( GTK_TYPE_TOGGLE_TOOL_BUTTON )
            << get_defs( GTK_TYPE_TOOLTIP )
            << get_defs( GTK_TYPE_TREE_SELECTION )
            << get_defs( GTK_TYPE_TREE_MODEL )
            << get_defs( GTK_TYPE_TREE_SELECTION )
            << get_defs( GTK_TYPE_TREE_SORTABLE )
            << get_defs( GTK_TYPE_TREE_MODEL_FILTER )
            << get_defs( GTK_TYPE_TREE_MODEL_SORT )
            << get_defs( GTK_TYPE_TREE_STORE )
            << get_defs( GTK_TYPE_TREE_VIEW )
            << get_defs( GTK_TYPE_TREE_VIEW_COLUMN )
            << get_defs( GTK_TYPE_UI_MANAGER )
            << get_defs( GTK_TYPE_VIEWPORT )
            << get_defs( GTK_TYPE_VOLUME_BUTTON )
            << get_defs( GTK_TYPE_WIDGET )
            << get_defs( GTK_TYPE_WINDOW )
            ;

  std::cout << get_child_properties( GTK_TYPE_BIN )
            << get_child_properties( GTK_TYPE_BOX )
            << get_child_properties( GTK_TYPE_FIXED )
            << get_child_properties( GTK_TYPE_FLOW_BOX )
            << get_child_properties( GTK_TYPE_GRID )
            << get_child_properties( GTK_TYPE_HEADER_BAR )
            << get_child_properties( GTK_TYPE_PANED )
            << get_child_properties( GTK_TYPE_ICON_VIEW )
            << get_child_properties( GTK_TYPE_LAYOUT )
            << get_child_properties( GTK_TYPE_LIST_BOX )
            << get_child_properties( GTK_TYPE_MENU_SHELL )
            << get_child_properties( GTK_TYPE_NOTEBOOK )
#ifdef GDK_WINDOWING_X11
            << get_child_properties( GTK_TYPE_SOCKET )
#endif
            << get_child_properties( GTK_TYPE_STACK )
            << get_child_properties( GTK_TYPE_TEXT_VIEW )
            << get_child_properties( GTK_TYPE_TOOLBAR )
            << get_child_properties( GTK_TYPE_TOOL_ITEM_GROUP )
            << get_child_properties( GTK_TYPE_TOOL_PALETTE )
            << get_child_properties( GTK_TYPE_TREE_VIEW )
            ;

  return 0;
}

std::string get_child_properties(GType gtype)
{
  std::string strResult; std::string strObjectName = g_type_name(gtype);

  //Get the list of properties:
  GParamSpec** ppParamSpec = 0;
  guint iCount = 0;
  if(g_type_is_a(gtype, GTK_TYPE_CONTAINER))
  {
    GObjectClass* pGClass = G_OBJECT_CLASS(g_type_class_ref(gtype));
    ppParamSpec = gtk_container_class_list_child_properties (pGClass, &iCount);
    g_type_class_unref(pGClass);

    if(!ppParamSpec)
    {
      strResult += ";; Warning: gtk_container_class_list_child_properties() returned NULL for " + std::string(g_type_name(gtype)) + "\n";
      iCount = 0;
    }
  }

  for(guint i = 0; i < iCount; i++)
  {
    GParamSpec* pParamSpec = ppParamSpec[i];

    if(pParamSpec && pParamSpec->owner_type == gtype)
    {
      strResult += get_property_with_node_name(pParamSpec, strObjectName, "define-child-property");
    }
  }

  g_free(ppParamSpec);

  return strResult;
}
