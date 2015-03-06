// -*- c++ -*-
#ifndef _GTKMM_STOCK_H
#define _GTKMM_STOCK_H

#ifndef GTKMM_DISABLE_DEPRECATED // This whole file is deprecated.

/* $Id$ */

/* Copyright (C) 2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <gtkmm/stockitem.h>
#include <gtkmm/stockid.h>
#include <gtkmm/iconset.h>
#include <gtkmm/image.h>

/* Shadow DELETE macro (from winnt.h).
 */
#if defined(DELETE) && !defined(GTKMM_MACRO_SHADOW_DELETE)
enum { GTKMM_MACRO_DEFINITION_DELETE = DELETE };
#undef DELETE
enum { DELETE = GTKMM_MACRO_DEFINITION_DELETE };
#define DELETE DELETE
#define GTKMM_MACRO_SHADOW_DELETE 1
#endif


namespace Gtk
{

// Created like so:
// const BuiltinStockID DIALOG_INFO = { GTK_STOCK_DIALOG_INFO }

/** See the list of pre-defined stock items, in the Stock namespace.
 * @deprecated Use icon names or labels instead of StockItem, StockID and BuiltinStockID.
 */
struct BuiltinStockID
{
  /**
   * The text representation of the stock id, usually something like "gtk-about".
   */
  const char* id;
};

namespace Stock
{

extern GTKMM_API const Gtk::BuiltinStockID DIALOG_AUTHENTICATION; /*!< @image html gtk-dialog-authentication.png
                                                                   * @deprecated Use named icon "dialog-password". */

extern GTKMM_API const Gtk::BuiltinStockID DIALOG_INFO;      /*!< @image html gtk-dialog-info.png
                                                              * @deprecated Use named icon "dialog-information". */
extern GTKMM_API const Gtk::BuiltinStockID DIALOG_WARNING;   /*!< @image html gtk-dialog-warning.png
                                                              * @deprecated Use named icon "dialog-warning". */
extern GTKMM_API const Gtk::BuiltinStockID DIALOG_ERROR;     /*!< @image html gtk-dialog-error.png
                                                              * @deprecated Use named icon "dialog-error". */
extern GTKMM_API const Gtk::BuiltinStockID DIALOG_QUESTION;  /*!< @image html gtk-dialog-question.png
                                                              * @deprecated Use named icon "dialog-question". */

// These aren't real stock items, because they provide only an icon.
extern GTKMM_API const Gtk::BuiltinStockID DND;              /*!< @image html gtk-dnd.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID DND_MULTIPLE;     /*!< @image html gtk-dnd-multiple.png
                                                              * @deprecated No replacement available. */

extern GTKMM_API const Gtk::BuiltinStockID ABOUT;            /*!< @image html gtk-about.png
                                                              * @deprecated Use named icon "help-about" or the label "_About". */
extern GTKMM_API const Gtk::BuiltinStockID ADD;              /*!< @image html gtk-add.png
                                                              * @deprecated Use named icon "list-add" or the label "_Add". */
extern GTKMM_API const Gtk::BuiltinStockID APPLY;            /*!< @image html gtk-apply.png
                                                              * @deprecated Do not use an icon. Use label "_Apply". */
extern GTKMM_API const Gtk::BuiltinStockID BOLD;             /*!< @image html gtk-bold.png
                                                              * @deprecated Use named icon "format-text-bold". */
extern GTKMM_API const Gtk::BuiltinStockID CANCEL;           /*!< @image html gtk-cancel.png
                                                              * @deprecated Do not use an icon. Use label "_Cancel". */
extern GTKMM_API const Gtk::BuiltinStockID CAPS_LOCK_WARNING; /*!< @image html gtk-caps-lock-warning.png
                                                              * @deprecated Use named icon "dialog-warning-symbolic". */
extern GTKMM_API const Gtk::BuiltinStockID CDROM;            /*!< @image html gtk-cdrom.png
                                                              * @deprecated Use named icon "media-optical". */
extern GTKMM_API const Gtk::BuiltinStockID CLEAR;            /*!< @image html gtk-clear.png
                                                              * @deprecated Use named icon "edit-clear". */
extern GTKMM_API const Gtk::BuiltinStockID CLOSE;            /*!< @image html gtk-close.png
                                                              * @deprecated Use named icon "window-close" or the label "_Close". */
extern GTKMM_API const Gtk::BuiltinStockID COLOR_PICKER;     /*!< @image html gtk-color-picker.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID CONVERT;          /*!< @image html gtk-convert.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID CONNECT;          /*!< @image html gtk-connect.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID COPY;             /*!< @image html gtk-copy.png
                                                              * @deprecated Use the named icon edit-copy or the label "_Copy". */
extern GTKMM_API const Gtk::BuiltinStockID CUT;              /*!< @image html gtk-cut.png
                                                              * @deprecated Use the named icon edit-cut or the label "Cu_t". */
extern GTKMM_API const Gtk::BuiltinStockID DELETE;           /*!< @image html gtk-delete.png
                                                              * @deprecated Use the named icon edit-delete or the  label "_Delete". */
extern GTKMM_API const Gtk::BuiltinStockID DIRECTORY;        /*!< @image html gtk-directory.png
                                                              * @deprecated Use named icon "folder". */
extern GTKMM_API const Gtk::BuiltinStockID DISCARD;          /*!< @image html gtk-discard.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID DISCONNECT;       /*!< @image html gtk-disconnect.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID EDIT;             /*!< @image html gtk-edit.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID EXECUTE;          /*!< @image html gtk-execute.png
                                                              * @deprecated Use named icon "system-run". */
extern GTKMM_API const Gtk::BuiltinStockID FILE;             /*!< @image html gtk-file.png
                                                              * @deprecated Use named icon "text-x-generic". */
extern GTKMM_API const Gtk::BuiltinStockID FIND;             /*!< @image html gtk-find.png
                                                              * @deprecated Use named icon "edit-find". */
extern GTKMM_API const Gtk::BuiltinStockID FIND_AND_REPLACE; /*!< @image html gtk-find-and-replace.png
                                                              * @deprecated Use named icon "edit-find-replace". */
extern GTKMM_API const Gtk::BuiltinStockID FLOPPY;           /*!< @image html gtk-floppy.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID FULLSCREEN;       /*!< @image html gtk-fullscreen.png
                                                              * @deprecated Use named icon "view-fullscreen". */
extern GTKMM_API const Gtk::BuiltinStockID LEAVE_FULLSCREEN; /*!< @image html gtk-leave-fullscreen.png
                                                              * @deprecated Use named icon "view-restore". */
extern GTKMM_API const Gtk::BuiltinStockID GOTO_BOTTOM;      /*!< @image html gtk-goto-bottom.png
                                                              * @deprecated Use named icon "go-bottom". */
extern GTKMM_API const Gtk::BuiltinStockID GOTO_FIRST;       /*!< left-to-right languages: @image html gtk-goto-first-ltr.png
                                                              *   right-to-left languages: @image html gtk-goto-first-rtl.png
                                                              * @deprecated Use named icon "go-first". */
extern GTKMM_API const Gtk::BuiltinStockID GOTO_LAST;        /*!< left-to-right languages: @image html gtk-goto-last-ltr.png
                                                              *   right-to-left languages: @image html gtk-goto-last-rtl.png
                                                              * @deprecated Use named icon "go-last". */
extern GTKMM_API const Gtk::BuiltinStockID GOTO_TOP;         /*!< @image html gtk-goto-top.png
                                                              * @deprecated Use named icon "go-top". */
extern GTKMM_API const Gtk::BuiltinStockID GO_BACK;          /*!< left-to-right languages: @image html gtk-go-back-ltr.png
                                                              *   right-to-left languages: @image html gtk-go-back-rtl.png
                                                              * @deprecated Use named icon "go-previous". */
extern GTKMM_API const Gtk::BuiltinStockID GO_DOWN;          /*!< @image html gtk-go-down.png
                                                              * @deprecated Use named icon "go-down". */
extern GTKMM_API const Gtk::BuiltinStockID GO_FORWARD;       /*!< left-to-right languages: @image html gtk-go-forward-ltr.png
                                                                  right-to-left languages: @image html gtk-go-forward-rtl.png
                                                              * @deprecated Use named icon "go-next". */
extern GTKMM_API const Gtk::BuiltinStockID GO_UP;            /*!< @image html gtk-go-up.png
                                                              * @deprecated Use named icon "go-up". */
extern GTKMM_API const Gtk::BuiltinStockID HARDDISK;         /*!< @image html gtk-harddisk.png
                                                              * @deprecated Use named icon "drive-harddisk". */
extern GTKMM_API const Gtk::BuiltinStockID HELP;             /*!< @image html gtk-help.png
                                                              * @deprecated Use named icon "help-browser". */
extern GTKMM_API const Gtk::BuiltinStockID HOME;             /*!< @image html gtk-home.png
                                                              * @deprecated Use named icon "go-home". */
extern GTKMM_API const Gtk::BuiltinStockID INDEX;            /*!< @image html gtk-index.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID INFO;             /*!< @image html gtk-info.png
                                                              * @deprecated Use named icon "dialog-information". */
extern GTKMM_API const Gtk::BuiltinStockID INDENT;           /*!< left-to-right languages: @image html gtk-indent-ltr.png
                                                              *   right-to-left languages: @image html gtk-indent-rtl.png
                                                              * @deprecated Use named icon "format-indent-more". */
extern GTKMM_API const Gtk::BuiltinStockID UNINDENT;         /*!< left-to-right languages: @image html gtk-unindent-ltr.png
                                                              *   right-to-left languages: @image html gtk-unindent-rtl.png
                                                              * @deprecated Use named icon "format-indent-less". */
extern GTKMM_API const Gtk::BuiltinStockID ITALIC;           /*!< @image html gtk-italic.png
                                                              * @deprecated Use named icon "format-text-italic". */
extern GTKMM_API const Gtk::BuiltinStockID JUMP_TO;          /*!< left-to-right languages: @image html gtk-jump-to-ltr.png
                                                              *   right-to-left languages: @image html gtk-jump-to-rtl.png
                                                              * @deprecated Use named icon "go-jump". */
extern GTKMM_API const Gtk::BuiltinStockID JUSTIFY_CENTER;   /*!< @image html gtk-justify-center.png
                                                              * @deprecated Use named icon "format-justify-center". */
extern GTKMM_API const Gtk::BuiltinStockID JUSTIFY_FILL;     /*!< @image html gtk-justify-fill.png
                                                              * @deprecated Use named icon "format-justify-fill". */
extern GTKMM_API const Gtk::BuiltinStockID JUSTIFY_LEFT;     /*!< @image html gtk-justify-left.png
                                                              * @deprecated Use named icon "format-justify-left". */
extern GTKMM_API const Gtk::BuiltinStockID JUSTIFY_RIGHT;    /*!< @image html gtk-justify-right.png
                                                              * @deprecated Use named icon "format-justify-right". */
extern GTKMM_API const Gtk::BuiltinStockID MISSING_IMAGE;    /*!< @image html gtk-missing-image.png
                                                              * @deprecated Use named icon "image-missing". */
extern GTKMM_API const Gtk::BuiltinStockID MEDIA_FORWARD;    /*!< left-to-right languages: @image html gtk-media-forward-ltr.png
                                                              *   right-to-left languages: @image html gtk-media-forward-rtl.png
                                                              * @deprecated Use named icon "media-seek-forward" or the label "_Forward". */
extern GTKMM_API const Gtk::BuiltinStockID MEDIA_NEXT;       /*!< left-to-right languages: @image html gtk-media-next-ltr.png
                                                              *   right-to-left languages: @image html gtk-media-next-rtl.png
                                                              * @deprecated Use named icon "media-skip-forward" or the label "_Next". */
extern GTKMM_API const Gtk::BuiltinStockID MEDIA_PAUSE;      /*!< @image html gtk-media-pause.png
                                                              * @deprecated Use named icon "media-playback-pause" or the label "P_ause". */
extern GTKMM_API const Gtk::BuiltinStockID MEDIA_PLAY;       /*!< left-to-right languages: @image html gtk-media-play-ltr.png
                                                              *   right-to-left languages: @image html gtk-media-play-rtl.png
                                                              * @deprecated Use named icon "media-playback-start" or the label "_Play". */
extern GTKMM_API const Gtk::BuiltinStockID MEDIA_PREVIOUS;   /*!< left-to-right languages: @image html gtk-media-previous-ltr.png
                                                              *   right-to-left languages: @image html gtk-media-previous-rtl.png
                                                              * @deprecated Use named icon "media-skip-backward" or the label "Pre_vious". */
extern GTKMM_API const Gtk::BuiltinStockID MEDIA_RECORD;     /*!< @image html gtk-media-record.png
                                                              * @deprecated Use named icon "media-record" or the label "_Record". */
extern GTKMM_API const Gtk::BuiltinStockID MEDIA_REWIND;     /*!< left-to-right languages: @image html gtk-media-rewind-ltr.png
                                                              *   right-to-left languages: @image html gtk-media-rewind-rtl.png
                                                              * @deprecated Use named icon "media-seek-backward" or the label "R_ewind". */
extern GTKMM_API const Gtk::BuiltinStockID MEDIA_STOP;       /*!< @image html gtk-media-stop.png
                                                              * @deprecated Use named icon "media-playback-stop" or the label "_Stop". */
extern GTKMM_API const Gtk::BuiltinStockID NETWORK;          /*!< @image html gtk-network.png
                                                              * @deprecated Use named icon "network-workgroup". */
extern GTKMM_API const Gtk::BuiltinStockID NEW;              /*!< @image html gtk-new.png
                                                              * @deprecated Use named icon "document-new" or the label "_New". */
extern GTKMM_API const Gtk::BuiltinStockID NO;               /*!< @image html gtk-no.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID OK;               /*!< @image html gtk-ok.png
                                                              * @deprecated Do not use an icon. Use label "_OK". */
extern GTKMM_API const Gtk::BuiltinStockID OPEN;             /*!< @image html gtk-open.png
                                                              * @deprecated Use named icon "document-open" or the label "_Open". */
extern GTKMM_API const Gtk::BuiltinStockID ORIENTATION_PORTRAIT; /*!< @image html gtk-orientation-portrait.png
                                                                  * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID ORIENTATION_LANDSCAPE; /*!< @image html gtk-orientation-landscape.png
                                                                   * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID ORIENTATION_REVERSE_LANDSCAPE; /*!< @image html gtk-orientation-reverse-landscape.png
                                                                           * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID ORIENTATION_REVERSE_PORTRAIT; /*!< @image html gtk-orientation-reverse-portrait.png
                                                                          * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID PASTE;            /*!< @image html gtk-paste.png
                                                              * @deprecated Use the named icon edit-paste or the label "_Paste". */
extern GTKMM_API const Gtk::BuiltinStockID PREFERENCES;      /*!< @image html gtk-preferences.png
                                                              * @deprecated Use named icon "preferences-system" or the label "_Preferences". */
extern GTKMM_API const Gtk::BuiltinStockID PAGE_SETUP;       /*!< @image html gtk-page-setup.png
                                                              * @deprecated Use named icon "document-page-setup" or the label "Page Set_up". */
extern GTKMM_API const Gtk::BuiltinStockID PRINT;            /*!< @image html gtk-print.png
                                                              * @deprecated Use named icon "document-print" or the label "_Print". */
extern GTKMM_API const Gtk::BuiltinStockID PRINT_ERROR;      /*!< @image html gtk-print-error.png
                                                              * @deprecated Use named icon "printer-error". */
extern GTKMM_API const Gtk::BuiltinStockID PRINT_PREVIEW;    /*!< @image html gtk-print-preview.png
                                                              * @deprecated Use label "Pre_view". */
extern GTKMM_API const Gtk::BuiltinStockID PRINT_REPORT;     /*!< @image html gtk-print-report.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID PRINT_WARNING;    /*!< @image html gtk-print-warning.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID PROPERTIES;       /*!< @image html gtk-properties.png
                                                              * @deprecated Use named icon "document-properties" or the label "_Properties". */
extern GTKMM_API const Gtk::BuiltinStockID QUIT;             /*!< @image html gtk-quit.png
                                                              * @deprecated Use named icon "application-exit" or the label "_Quit". */
extern GTKMM_API const Gtk::BuiltinStockID REDO;             /*!< left-to-right languages: @image html gtk-redo-ltr.png
                                                              *   right-to-left languages: @image html gtk-redo-rtl.png
                                                              * @deprecated Use named icon "edit-redo" or the label "_Redo". */
extern GTKMM_API const Gtk::BuiltinStockID REFRESH;          /*!< @image html gtk-refresh.png
                                                              * @deprecated Use named icon "view-refresh" or the label "_Refresh". */
extern GTKMM_API const Gtk::BuiltinStockID REMOVE;           /*!< @image html gtk-remove.png
                                                              * @deprecated Use named icon "list-remove" or the label "_Remove". */
extern GTKMM_API const Gtk::BuiltinStockID REVERT_TO_SAVED;  /*!< left-to-right languages: @image html gtk-revert-to-saved-ltr.png
                                                              *   right-to-left languages: @image html gtk-revert-to-saved-rtl.png
                                                              * @deprecated Use named icon "document-revert" or the label "_Revert". */
extern GTKMM_API const Gtk::BuiltinStockID SAVE;             /*!< @image html gtk-save.png
                                                              * @deprecated Use named icon "document-save" or the label "_Save". */
extern GTKMM_API const Gtk::BuiltinStockID SAVE_AS;          /*!< @image html gtk-save-as.png
                                                              * @deprecated Use named icon "document-save-as" or the label "Save _As". */
extern GTKMM_API const Gtk::BuiltinStockID SELECT_ALL;       /*!< @image html gtk-select-all.png
                                                              * @deprecated Use named icon "edit-select-all" or the label "Select _All". */
extern GTKMM_API const Gtk::BuiltinStockID SELECT_COLOR;     /*!< @image html gtk-select-color.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID SELECT_FONT;      /*!< @image html gtk-select-font.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID SORT_ASCENDING;   /*!< @image html gtk-sort-ascending.png
                                                              * @deprecated Use named icon "view-sort-ascending". */
extern GTKMM_API const Gtk::BuiltinStockID SORT_DESCENDING;  /*!< @image html gtk-sort-descending.png
                                                              * @deprecated Use named icon "view-sort-descending". */
extern GTKMM_API const Gtk::BuiltinStockID SPELL_CHECK;      /*!< @image html gtk-spell-check.png
                                                              * @deprecated Use named icon "tools-check-spelling". */
extern GTKMM_API const Gtk::BuiltinStockID STOP;             /*!< @image html gtk-stop.png
                                                              * @deprecated Use named icon "process-stop" or the label "_Stop". */
extern GTKMM_API const Gtk::BuiltinStockID STRIKETHROUGH;    /*!< @image html gtk-strikethrough.png
                                                              * @deprecated Use named icon "format-text-strikethrough" or the label "_Strikethrough". */
extern GTKMM_API const Gtk::BuiltinStockID UNDELETE;         /*!< left-to-right languages: @image html gtk-undelete-ltr.png
                                                              *   right-to-left languages: @image html gtk-undelete-rtl.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID UNDERLINE;        /*!< @image html gtk-underline.png
                                                              * @deprecated Use named icon "format-text-underline" or the label "_Underline". */
extern GTKMM_API const Gtk::BuiltinStockID UNDO;             /*!< left-to-right languages: @image html gtk-undo-ltr.png
                                                              *   right-to-left languages: @image html gtk-undo-rtl.png
                                                              * @deprecated Use named icon "edit-undo" or the label "_Undo". */
extern GTKMM_API const Gtk::BuiltinStockID YES;              /*!< @image html gtk-yes.png
                                                              * @deprecated No replacement available. */
extern GTKMM_API const Gtk::BuiltinStockID ZOOM_100;         /*!< @image html gtk-zoom-100.png
                                                              * @deprecated Use named icon "zoom-original" or the label "_Normal Size". */
extern GTKMM_API const Gtk::BuiltinStockID ZOOM_FIT;         /*!< @image html gtk-zoom-fit.png
                                                              * @deprecated Use named icon "zoom-fit-best" or the label "Best _Fit". */
extern GTKMM_API const Gtk::BuiltinStockID ZOOM_IN;          /*!< @image html gtk-zoom-in.png
                                                              * @deprecated Use named icon "zoom-in" or the label "Zoom _In". */
extern GTKMM_API const Gtk::BuiltinStockID ZOOM_OUT;         /*!< @image html gtk-zoom-out.png
                                                              * @deprecated Use named icon "zoom-out" or the label "Zoom _Out". */

/** Add a stock item to the list of registered stock items.
 * @param item StockItem to register. If an item already exists with the same
 *             stock ID the old item gets replaced. 
 * @deprecated Use icon names instead of StockItem, StockID and BuiltinStockID.
 */
void add(const Gtk::StockItem& item);

/** Fills item with the registered values for stock_id.
  * @param stock_id StockID to search for.
  * @param item item to fill in case stockid was found.
  *
  * @return <tt>true</tt> if the item was found - <tt>false</tt> otherwise.
  * @deprecated Use icon names instead of StockItem, StockID and BuiltinStockID.
  */
bool lookup(const Gtk::StockID& stock_id, Gtk::StockItem& item);

/** See IconSet::lookup_default()
  * @param stock_id StockID to search for.
  * @param iconset to fill.
  *
  * @return <tt>true</tt> if the item was found - <tt>false</tt> otherwise.
  * @deprecated Use icon names instead of StockItem, StockID and BuiltinStockID.
  */
bool lookup(const Gtk::StockID& stock_id, Glib::RefPtr<Gtk::IconSet>& iconset);

/** Receive an Image of the registered stock id with the correct size.
  * @param stock_id StockID to search for.
  * @param size: IconSize of the desired Image.
  * @param image: Image to fill.
  *
  * @return <tt>true</tt> if the item was found - <tt>false</tt> otherwise
  * @deprecated Use icon names instead of StockItem, StockID and BuiltinStockID.
  */  
bool lookup(const Gtk::StockID& stock_id, Gtk::IconSize size, Gtk::Image& image);

/** Retrieves a list of all known stock IDs added to an IconFactory or registered with Stock::add().
  *
  * @return list of all known stock IDs.
  * @deprecated Use icon names instead of StockItem, StockID and BuiltinStockID.
  */
std::vector<Gtk::StockID> get_ids();

} // namespace Stock

} // namespace Gtk

#endif // GTKMM_DISABLE_DEPRECATED

#endif /* _GTKMM_STOCK_H */

