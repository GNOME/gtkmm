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

include(convert_glib.m4)

#
# Basic Types
_CONVERSION(`time_t&',`time_t*',`&($3)')
_CONVERSION(`time_t',`std::time_t',`$3')

_CONVERSION(`ui_merge_id',`guint',`$3')
_CONVERSION(`guint',`ui_merge_id',`$3')

# Enums: TODO: It would be nice if gmmproc knew about these automatically.
_CONV_ENUM(Gtk,AccelFlags)
_CONV_ENUM(Gtk,Align)
_CONV_ENUM(Gtk,ArrowType)
_CONV_ENUM(Gtk,AttachOptions)
_CONV_ENUM(Gtk,ButtonBoxStyle)
_CONV_ENUM(Gtk,ButtonRole)
_CONV_ENUM(Gtk,ButtonsType)
_CONV_ENUM(Gtk,CalendarDisplayOptions)
_CONV_ENUM(Gtk,CellRendererMode)
_CONV_ENUM(Gtk,CellRendererState)
_CONV_ENUM(Gtk,CornerType)
_CONV_ENUM(Gtk,CssProviderError)
_CONV_ENUM(Gtk,CssSectionType)
_CONV_ENUM(Gtk,CurveType)
_CONV_ENUM(Gtk,DeleteType)
_CONV_ENUM(Gtk,DestDefaults)
_CONV_ENUM(Gtk,DirectionType)
_CONV_ENUM(Gtk,EventSequenceState)
_CONV_ENUM(Gtk,ExpanderStyle)
_CONV_ENUM(Gtk,ImageType)
_CONV_ENUM(Gtk,Justification)
_CONV_ENUM(Gtk,License)
_CONV_ENUM(Gtk,MenuDirectionType)
_CONV_ENUM(Gtk,MessageType)
_CONV_ENUM(Gtk,MovementStep)
_CONV_ENUM(Gtk,NotebookTab)
_CONV_ENUM(Gtk,Orientation)
_CONV_ENUM(Gtk,PackType)
_CONV_ENUM(Gtk,PackDirection)
_CONV_ENUM(Gtk,PanDirection)
_CONV_ENUM(Gtk,PlacesOpenFlags)
_CONV_ENUM(Gtk,PolicyType)
_CONV_ENUM(Gtk,PopoverConstraint)
_CONV_ENUM(Gtk,PositionType)
_CONV_ENUM(Gtk,PreviewType)
_CONV_ENUM(Gtk,ProgressBarOrientation)
_CONV_ENUM(Gtk,ProgressBarStyle)
_CONV_ENUM(Gtk,PropagationPhase)
_CONV_ENUM(Gtk,ReliefStyle)
_CONV_ENUM(Gtk,ResizeMode)
_CONV_ENUM(Gtk,RevealerTransitionType)
_CONV_ENUM(Gtk,ScrollType)
_CONV_ENUM(Gtk,SelectionMode)
_CONV_ENUM(Gtk,ShadowType)
_CONV_ENUM(Gtk,ShortcutType)
_CONV_ENUM(Gtk,SizeGroupMode)
_CONV_ENUM(Gtk,SortType)
_CONV_ENUM(Gtk,SpinButtonUpdatePolicy)
_CONV_ENUM(Gtk,SpinType)
_CONV_ENUM(Gtk,StackTransitionType)
_CONV_ENUM(Gtk,StateType)
_CONV_ENUM(Gtk,TargetFlags)
_CONV_ENUM(Gtk,TextDirection)
_CONV_ENUM(Gtk,TextSearchFlags)
_CONV_ENUM(Gtk,TextWindowType)
_CONV_ENUM(Gtk,ToolbarChildType)
_CONV_ENUM(Gtk,ToolbarStyle)
_CONV_ENUM(Gtk,ToolPaletteDragTargets)
_CONV_ENUM(Gtk,TreeModelFlags)
_CONV_ENUM(Gtk,TreeViewColumnSizing)
_CONV_ENUM(Gtk,TreeViewDropPosition)
_CONV_ENUM(Gtk,TreeViewGridLines)
_CONV_ENUM(Gtk,UpdateType)
_CONV_ENUM(Gtk,Visibility)
_CONV_ENUM(Gtk,WidgetHelpType)
_CONV_ENUM(Gtk,WindowPosition)
_CONV_ENUM(Gtk,WindowType)
_CONV_ENUM(Gtk,WrapMode)
_CONV_ENUM(Gtk,UIManagerItemType)
_CONV_ENUM(Gtk,FileChooserAction)
_CONV_ENUM(Gtk,FileFilterFlags)
_CONV_ENUM(Gtk,IconLookupFlags)
_CONV_ENUM(Gtk,IconThemeError)
_CONV_ENUM(Gtk,FileChooserConfirmation)
_CONV_ENUM(Gtk,SensitivityType)
_CONV_ENUM(Gtk,AssistantPageType)
_CONV_ENUM(Gtk,IconViewDropPosition)
_CONV_ENUM(Gtk,RecentFilterFlags)
_CONV_ENUM(Gtk,RecentManagerError)
_CONV_ENUM(Gtk,RecentSortType)
_CONV_ENUM(Gtk,Unit)
_CONV_ENUM(Gtk,PageOrientation)
_CONV_ENUM(Gtk,PrintDuplex)
_CONV_ENUM(Gtk,PrintQuality)
_CONV_ENUM(Gtk,PrintPages)
_CONV_ENUM(Gtk,PageSet)
_CONV_ENUM(Gtk,PrintStatus)
_CONV_ENUM(Gtk,PrintOperationResult)
_CONV_ENUM(Gtk,PrintOperationAction)
_CONV_ENUM(Gtk,PrintError)
_CONV_ENUM(Gtk,PrintCapabilities)
_CONV_ENUM(Gtk,DragResult)
_CONV_ENUM(Gtk,NumberUpLayout)
_CONV_ENUM(Gtk,EntryIconPosition)
_CONV_ENUM(Gtk,WrapAllocationMode)
_CONV_ENUM(Gtk,WrapBoxPacking)
_CONV_ENUM(Gtk,WrapBoxSpreading)
_CONV_ENUM(Gtk,SizeRequestMode)
_CONV_ENUM(Gtk,ScrollablePolicy)
_CONV_ENUM(Gtk,RegionFlags)
_CONV_ENUM(Gtk,JunctionSides)
_CONV_ENUM(Gtk,StateFlags)
_CONV_ENUM(Gtk,ApplicationInhibitFlags)
_CONV_ENUM(Gtk,InputPurpose)
_CONV_ENUM(Gtk,InputHints)
_CONV_ENUM(Gtk,LevelBarMode)
_CONV_ENUM(Gtk,BaselinePosition)

_CONVERSION(`GtkIconSize',`IconSize',`IconSize(static_cast<int>($3))')
_CONVERSION(`GtkIconSize',`Gtk::IconSize',`Gtk::IconSize(static_cast<int>($3))')
_CONVERSION(`IconSize',`GtkIconSize',`static_cast<GtkIconSize>(int($3))')
_CONVERSION(`Gtk::IconSize',`GtkIconSize',`static_cast<GtkIconSize>(int($3))')
include(convert_atk.m4)
include(convert_pango.m4)
include(convert_gdk.m4)

_CONVERSION(`guint',`WindowType',`static_cast<WindowType>($3)')
_CONVERSION(`PolicyType&',`GtkPolicyType*',`(($2) &($3))')
_CONVERSION(`SortType&',`GtkSortType*',`(($2) &($3))')
_CONVERSION(`SortType*',`GtkSortType*',`(($2) ($3))')
_CONVERSION(`GtkSortType*',`SortType*',`(($2) ($3))')
_CONVERSION(`guint8',`Gtk::StateType',`static_cast<StateType>($3)')
_CONVERSION(`RegionFlags&',`GtkRegionFlags*',`(($2) &($3))')



# StockID:
_CONVERSION(`const StockID&',`const char*',`($3).get_c_str()')
_CONVERSION(`const Gtk::StockID&',`const char*',`($3).get_c_str()')
_CONVERSION(`char*',`StockID',`StockID($3)') # the StockID ctor handles 0
_CONVERSION(`const char*',`StockID',`StockID($3)') # the StockID ctor handles 0


#
# Ptr (gtk+) -> Ptr (gtkmm)
define(`__FP2P',`($`'2)Glib::unwrap($`'3)')
define(`__RP2P',`Glib::wrap($`'3)')
define(`__RP2PD',`Glib::wrap((tran`'slit($`'2,:,))($`'3))')
define(`__RP2CPD',`Glib::wrap((tran`'slit(pat`'subst($`'2,^const ,),:,))($`'3))')

_CONVERSION(`GtkAdjustment*',`Glib::RefPtr<Adjustment>',`Glib::wrap($3)')
_CONVERSION(`GtkAdjustment*',`Glib::RefPtr<const Adjustment>',`Glib::wrap($3)')
_CONVERSION(`GtkWidget*',`Gtk::Widget*',__RP2P)
_CONVERSION(`GtkWidget*',`Widget*',__RP2P)
_CONVERSION(`GtkWindow*',`Window*',__RP2P)
_CONVERSION(`GtkMenu*',`Menu*',__RP2P)
_CONVERSION(`GtkMenu*',`Gtk::Menu*',__RP2P)
_CONVERSION(`GtkPopover*',`Popover*',__RP2P)
_CONVERSION(`GtkToolItem*',`ToolItem*',__RP2P)
_CONVERSION(`GtkToolItemGroup*',`ToolItemGroup*',__RP2P)
_CONVERSION(`GtkStack*',`Stack*',__RP2P)

# Ptr (gtk+) -> const Ptr (gtkmm)
_CONVERSION(`GtkWidget*',`const Gtk::Widget*',__RP2P)
_CONVERSION(`GtkWidget*',`const Widget*',__RP2P)
_CONVERSION(`GtkWindow*',`const Window*',__RP2P)
_CONVERSION(`GtkToolItem*',`const ToolItem*',__RP2P)

# Style:
_CONVERSION(`GtkStyleContext*',`Glib::RefPtr<StyleContext>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<StyleContext>&',`GtkStyleContext*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkStyleProvider*',`Glib::RefPtr<StyleProvider>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<StyleProvider>&',`GtkStyleProvider*',__CONVERT_REFPTR_TO_P)

_CONVERSION(`GtkCssProvider*',`Glib::RefPtr<CssProvider>',`Glib::wrap($3)')
_CONVERSION(`GtkCssSection*',`Glib::RefPtr<CssSection>',`Glib::wrap($3)')

# AccelGroup:
_CONVERSION(`GtkAccelGroup*',`Glib::RefPtr<AccelGroup>',`Glib::wrap($3)')
_CONVERSION(`GtkAccelGroup*',`Glib::RefPtr<const AccelGroup>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<AccelGroup>&',`GtkAccelGroup*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`Gtk::Object&',`GObject*', `($3).Glib::Object::gobj()')

_CONVERSION(`GtkCellArea*',`Glib::RefPtr<CellArea>',`Glib::wrap($3)')
_CONVERSION(`GtkCellArea*',`Glib::RefPtr<const CellArea>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<CellArea>&',`GtkCellArea*',__CONVERT_REFPTR_TO_P)

_CONVERSION(`GtkCellAreaContext*',`Glib::RefPtr<CellAreaContext>',`Glib::wrap($3)')
_CONVERSION(`GtkCellAreaContext*',`Glib::RefPtr<const CellAreaContext>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<CellAreaContext>&',`GtkCellAreaContext*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const CellAreaContext>&',`GtkCellAreaContext*',__CONVERT_CONST_REFPTR_TO_P)

#
# Ptr (Gtkmm) -> Ptr (gtk+)
_CONVERSION(`const Glib::RefPtr<Adjustment>&',`GtkAdjustment*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`Gtk::Widget*',`GtkWidget*',__FP2P)
_CONVERSION(`Widget*',`GtkWidget*',__FP2P)
_CONVERSION(`Window*',`GtkWindow*',__FP2P)
_CONVERSION(`Menu*',`GtkMenu*',__FP2P)

#
# Ptr (gtk+) -> Ptr (gtkmm) (downcast)
_CONVERSION(`GtkWidget*',`Button*',`Glib::wrap((GtkButton*)($3))')
_CONVERSION(`GtkWidget*',`Box*',`Glib::wrap((GtkBox*)($3))')
_CONVERSION(`GtkWidget*',`HBox*',`Glib::wrap((GtkHBox*)($3))')
_CONVERSION(`GtkWidget*',`VBox*',`Glib::wrap((GtkVBox*)($3))')
_CONVERSION(`GtkWidget*',`ColorSelection*',`Glib::wrap((GtkColorSelection*)($3))')
_CONVERSION(`GtkWidget*',`Gtk::CheckButton*',__RP2PD)
_CONVERSION(`GtkWidget*',`Container*',`Glib::wrap((GtkContainer*)($3))')
_CONVERSION(`GtkWidget*',`const Container*',`Glib::wrap((GtkContainer*)($3))')
_CONVERSION(`GtkWidget*',`Entry*',`Glib::wrap((GtkEntry*)($3))')
_CONVERSION(`GtkWidget*',`FontSelection*',`Glib::wrap((GtkFontSelection*)($3))')
_CONVERSION(`GtkWidget*',`HeaderBar*',`Glib::wrap((GtkHeaderBar*)($3))')
_CONVERSION(`GtkWidget*',`Label*',`Glib::wrap((GtkLabel*)($3))')
_CONVERSION(`GtkWidget*',`Menu*',`Glib::wrap((GtkMenu*)($3))')
_CONVERSION(`GtkWidget*',`MenuItem*',`Glib::wrap((GtkMenuItem*)($3))')
_CONVERSION(`GtkWidget*',`OptionMenu*',`Glib::wrap((GtkOptionMenu*)($3))')
_CONVERSION(`GtkWidget*',`RadioButton*',`Glib::wrap((GtkRadioButton*)($3))')
_CONVERSION(`GtkWidget*',`Gtk::Scrollbar*',__RP2PD)
_CONVERSION(`GtkWidget*',`Gtk::HScrollbar*',__RP2PD)
_CONVERSION(`GtkWidget*',`Gtk::VScrollbar*',__RP2PD)
_CONVERSION(`GtkWidget*',`Table*',`Glib::wrap((GtkTable*)($3))')
_CONVERSION(`GtkWidget*',`Gtk::Tree*',__RP2PD)
_CONVERSION(`GtkWidget*',`ScrolledWindow*',`Glib::wrap((GtkScrolledWindow*)($3))')
_CONVERSION(`GtkWidget*',`Window*',`Glib::wrap((GtkWindow*)($3))')
_CONVERSION(`GtkWidget*',`TreeView*',`Glib::wrap((GtkTreeView*)($3))')
_CONVERSION(`GtkWidget*',`ButtonBox*',`Glib::wrap((GtkButtonBox*)($3))')
_CONVERSION(`GtkWidget*',`HButtonBox*',`Glib::wrap((GtkHButtonBox*)($3))')
_CONVERSION(`GtkWidget*',`ComboDropDown*',`Glib::wrap((GtkList*)($3))')
_CONVERSION(`GtkWidget*',`Image*',`Glib::wrap((GtkImage*)($3))')
_CONVERSION(`GtkWidget*',`ToolItem*',`Glib::wrap((GtkToolItem*)($3))')
_CONVERSION(`GtkWidget*',`FileChooserDialog*',`Glib::wrap((GtkFileChooserDialog*)($3))')

# Ptr (gtk+) -> const Ptr (gtkmm) (downcast)
_CONVERSION(`GtkWidget*',`const Button*',`Glib::wrap((GtkButton*)($3))')
_CONVERSION(`GtkWidget*',`const Box*',`Glib::wrap((GtkBox*)($3))')
_CONVERSION(`GtkWidget*',`const HBox*',`Glib::wrap((GtkHBox*)($3))')
_CONVERSION(`GtkWidget*',`const VBox*',`Glib::wrap((GtkVBox*)($3))')
_CONVERSION(`GtkWidget*',`const ColorSelection*',`Glib::wrap((GtkColorSelection*)($3))')
_CONVERSION(`GtkWidget*',`const Gtk::CheckButton*',__RP2CPD)
_CONVERSION(`GtkWidget*',`const Entry*',`Glib::wrap((GtkEntry*)($3))')
_CONVERSION(`GtkWidget*',`const FontSelection*',`Glib::wrap((GtkFontSelection*)($3))')
_CONVERSION(`GtkWidget*',`const Label*',`Glib::wrap((GtkLabel*)($3))')
_CONVERSION(`GtkWidget*',`const Menu*',`Glib::wrap((GtkMenu*)($3))')
_CONVERSION(`GtkWidget*',`const MenuItem*',`Glib::wrap((GtkMenuItem*)($3))')
_CONVERSION(`GtkWidget*',`const OptionMenu*',`Glib::wrap((GtkOptionMenu*)($3))')
_CONVERSION(`GtkWidget*',`const RadioButton*',`Glib::wrap((GtkRadioButton*)($3))')
_CONVERSION(`GtkWidget*',`const Gtk::Scrollbar*',__RP2CPD)
_CONVERSION(`GtkWidget*',`const Gtk::HScrollbar*',__RP2CPD)
_CONVERSION(`GtkWidget*',`const Gtk::VScrollbar*',__RP2CPD)
_CONVERSION(`GtkWidget*',`const Table*',`Glib::wrap((GtkTable*)($3))')
_CONVERSION(`GtkWidget*',`const Gtk::Tree*',__RP2CPD)
_CONVERSION(`GtkWidget*',`const ScrolledWindow*',`Glib::wrap((GtkScrolledWindow*)($3))')
_CONVERSION(`GtkWidget*',`const Window*',`Glib::wrap((GtkWindow*)($3))')
_CONVERSION(`GtkWidget*',`const TreeView*',`Glib::wrap((GtkTreeView*)($3))')
_CONVERSION(`GtkWidget*',`const HButtonBox*',`Glib::wrap((GtkHButtonBox*)($3))')
_CONVERSION(`GtkWidget*',`const ComboDropDown*',`Glib::wrap((GtkList*)($3))')
_CONVERSION(`GtkWidget*',`const FileChooserDialog*',`Glib::wrap((GtkFileChooserDialog*)($3))')

_CONVERSION(`RadioButton&',`GtkRadioButton*',`($3).gobj()')

# Ptr (gtk+) -> Ref (Gtkmm)
_CONVERSION(`GtkWidget*', `Widget&', `*Glib::wrap($3)')

# Ref (Gtkmm) -> GtkWidget* Ptr (gtk+)
define(`__FR2PD',`($`'3).Gtk::Widget::gobj()')
_CONVERSION(`MenuShell&',`GtkWidget*',__FR2PD)
_CONVERSION(`MenuItem&',`GtkWidget*',__FR2PD)
_CONVERSION(`Menu&',`GtkWidget*',__FR2PD)
_CONVERSION(`Popover&',`GtkWidget*',__FR2PD)
_CONVERSION(`Gtk::TreeItem&',`GtkWidget*',__FR2PD)
_CONVERSION(`FileChooserDialog&',`GtkWidget*',__FR2PD)

# Ref (Gtkmm) -> Ptr (gtk+)
define(`__FR2P',`($`'3).gobj()')
define(`__FCR2P',`const_cast<$`'2>(($`'3).gobj())')
_CONVERSION(`Gtk::Style&',`GtkStyle*',__FR2P)
_CONVERSION(`Gtk::Widget&',`GtkWidget*',__FR2P)
_CONVERSION(`Widget&',`GtkWidget*',__FR2P)
_CONVERSION(`Window&',`GtkWindow*',__FR2P)
_CONVERSION(`CellRenderer&',`GtkCellRenderer*',__FR2P)
_CONVERSION(`const CellRenderer&',`GtkCellRenderer*',__FCR2P)
_CONVERSION(`ToolItem&',`GtkToolItem*',__FR2P)
_CONVERSION(`const ToolItem&',`GtkToolItem*',__FCR2P)
_CONVERSION(`ToolItemGroup&',`GtkToolItemGroup*',__FR2P)
_CONVERSION(`Gtk::Entry&',`GtkEntry*',__FR2P)
_CONVERSION(`Stack&',`GtkStack*',__FR2P)

# Glib::ListHandle<> (gtkmm) -> GList (gtk+)
_CONVERSION(`const Glib::ListHandle<Glib::ustring>&',`GList*',`$3.data()')
_CONVERSION(`const Glib::ListHandle<Widget*>&',`GList*',`$3.data()')
_CONVERSION(`const Glib::ListHandle<const Widget*>&',`GList*',`$3.data()')
_CONVERSION(`const Glib::ListHandle<Window*>&',`GList*',`$3.data()')
_CONVERSION(`const Glib::ListHandle<const Window*>&',`GList*',`$3.data()')
_CONVERSION(`const Glib::SListHandle< Glib::RefPtr<RadioAction> >&',`GSList*',`$3.data()')
_CONVERSION(`const Glib::SListHandle< Glib::RefPtr<const RadioAction> >&',`GSList*',`$3.data()')

# GList (gtk+) -> Glib::ListHandle<> (gtkmm)
define(`__FL2H_DEEP',`$`'2($`'3, Glib::OWNERSHIP_DEEP)')
define(`__FL2H_SHALLOW',`$`'2($`'3, Glib::OWNERSHIP_SHALLOW)')
define(`__FL2H_NONE',`$`'2($`'3, Glib::OWNERSHIP_NONE)')

_CONVERSION(`GList*',`Glib::ListHandle<Widget*>',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle<const Widget*>',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`Glib::SListHandle<Widget*>',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`Glib::SListHandle<const Widget*>',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle<Window*>',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle<TreeViewColumn*>',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle<const TreeViewColumn*>',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle<CellRenderer*>',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle<const CellRenderer*>',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle<TreeModel::Row>',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle<const TreeModel::Row>',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle< Glib::RefPtr<Action> >',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle< Glib::RefPtr<const Action> >',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle< Glib::RefPtr<ActionGroup> >',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle< Glib::RefPtr<const ActionGroup> >',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle< Glib::RefPtr<RecentInfo> >',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle<RecentInfo>',__FL2H_SHALLOW)
_CONVERSION(`GList*',`Glib::ListHandle<const RecentInfo>', __FL2H_SHALLOW)
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<Tag> >',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<const Tag> >',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<TextTag> >',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<const TextTag> >',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<TextMark> >',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<const TextMark> >',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<TextBuffer::Mark> >',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<const TextBuffer::Mark> >',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<RadioAction> >',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<const RadioAction> >',__FL2H_SHALLOW)

_CONVERSION(`GSList*',`Glib::SListHandle<Glib::ustring>',__FL2H_DEEP)
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<PixbufFormat> >',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<const PixbufFormat> >',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`SListHandle_PixbufFormat',__FL2H_DEEP)
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<RecentFilter> >',__FL2H_SHALLOW)
_CONVERSION(`GSList*',`Glib::SListHandle< Glib::RefPtr<const RecentFilter> >', __FL2H_SHALLOW)

_CONVERSION(`const Widget&',`GtkWidget*',__FCR2P)

_CONVERSION(`int&',`int*',`&$3',`*$3')

dnl
dnl # TODO: These are for fixmegtkconst
_CONVERSION(`gdouble*',`const gdouble*',`const_cast<const gdouble*>($3)',`$3')
_CONVERSION(`const double*',`gdouble*',`const_cast<gdouble*>($3)',`$3')
_CONVERSION(`const guchar*',`guchar*',`const_cast<guchar*>($3)',`$3')

#_CONVERSION(`GSList*',`const Group&',`Group($3)')
_CONVERSION(`GSList*',`Group',`Group($3)')
_CONVERSION(`Group&',`GSList*',`$3.group_')
_CONVERSION(`Group',`GSList*',`$3.group_')

_CONVERSION(`Gtk::Item&',`GtkItem*',__FR2P)
_CONVERSION(Gtk::Notebook_Helpers::Page*,GtkNotebookPage*,`($1)((void*)($3))',`($2)((void*)($3))')

_CONVERSION(`GtkSettings*',`Glib::RefPtr<Settings>', Glib::wrap($3))

_CONVERSION(`Glib::RefPtr<IconSet>&',`GtkIconSet*',__CONVERT_REFPTR_TO_P($3))
_CONVERSION(`const Glib::RefPtr<IconSet>&',`GtkIconSet*',__CONVERT_REFPTR_TO_P($3))
_CONVERSION(`GtkIconSet*',`Glib::RefPtr<IconSet>',`Glib::wrap($3)')

_CONVERSION(`IconSource&',`GtkIconSource*',__FR2P)
_CONVERSION(`const IconSource&',`const GtkIconSource*',__FR2P)
_CONVERSION(`const GtkIconSource*',`const IconSource&',`Glib::wrap(const_cast<GtkIconSource*>($3), true)')

_CONVERSION(`GtkIconTheme*',`Glib::RefPtr<IconTheme>',`Glib::wrap($3)')
_CONVERSION(`GList*',`Glib::ListHandle<Glib::ustring>',__FL2H_SHALLOW)

_CONVERSION(`GtkWindowGroup*',`Glib::RefPtr<WindowGroup>',`Glib::wrap($3)')
_CONVERSION(`GtkWindowGroup*',`Glib::RefPtr<const WindowGroup>',`Glib::wrap($3)')

# gpointer conversions:
# There's doesn't seem to be a way to tell g_signal_new that it's a pointer to a gint, for instance:
#_CONVERSION(`int*',`gpointer',`($1)$3')
#_CONVERSION(`gpointer',`int*',`($1)$3')


# Text:
_CONVERSION(`GtkTextTagTable*',`Glib::RefPtr<TextTagTable>',`Glib::wrap($3)')
_CONVERSION(`GtkTextTagTable*',`Glib::RefPtr<TagTable>',`Glib::wrap($3)')
_CONVERSION(`GtkTextTagTable*',`Glib::RefPtr<TextBuffer::TagTable>',`Glib::wrap($3)')
_CONVERSION(`GtkTextTagTable*',`Glib::RefPtr<const TextBuffer::TagTable>',`Glib::wrap($3)')
_CONVERSION(`GtkTextMark*',`Glib::RefPtr<Mark>',`Glib::wrap($3)')
_CONVERSION(`GtkTextMark*',`Glib::RefPtr<TextBuffer::Mark>',`Glib::wrap($3)')
_CONVERSION(`GtkTextMark*',`Glib::RefPtr<const TextBuffer::Mark>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Mark>&',`GtkTextMark*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<TextBuffer::Mark>&',`GtkTextMark*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkTextTag*',`Glib::RefPtr<TextTag>',`Glib::wrap($3)')
_CONVERSION(`GtkTextTag*',`Glib::RefPtr<const TextTag>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<TextTag>&',`GtkTextTag*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const TextTag>&',`GtkTextTag*',__CONVERT_CONST_REFPTR_TO_P_SUN(TextTag))
_CONVERSION(`const Glib::RefPtr<Tag>&',`GtkTextTag*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<TextBuffer::Tag>&',`GtkTextTag*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkTextBuffer*',`Glib::RefPtr<TextBuffer>',`Glib::wrap($3)')
_CONVERSION(`GtkTextBuffer*',`Glib::RefPtr<const TextBuffer>',`Glib::wrap($3)')
_CONVERSION(`TextIter&',`GtkTextIter*',__FR2P)
_CONVERSION(`TextBuffer::iterator&',`GtkTextIter*',__FR2P)
_CONVERSION(`iterator&',`GtkTextIter*',__FR2P)
_CONVERSION(`const TextIter&',`const GtkTextIter*',__FR2P)
_CONVERSION(`const TextBuffer::iterator&',`const GtkTextIter*',__FR2P)
_CONVERSION(`const iterator&',`const GtkTextIter*',__FR2P)
_CONVERSION(`TextAttributes&',`GtkTextAttributes*',__FR2P)
_CONVERSION(`GtkTextAttributes*',`TextAttributes',TextAttributes($3))
_CONVERSION(`const Glib::RefPtr<TextTagTable>&',`GtkTextTagTable*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<TextBuffer>&',`GtkTextBuffer*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<TextChildAnchor>&',`GtkTextChildAnchor*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<ChildAnchor>&',`GtkTextChildAnchor*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<TextBuffer::ChildAnchor>&',`GtkTextChildAnchor*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkTextChildAnchor*',`Glib::RefPtr<ChildAnchor>',`Glib::wrap($3)')
_CONVERSION(`GtkTextChildAnchor*',`Glib::RefPtr<TextChildAnchor>',`Glib::wrap($3)')
_CONVERSION(`GtkTextChildAnchor*',`Glib::RefPtr<const TextChildAnchor>',`Glib::wrap($3)')
_CONVERSION(`GtkSizeGroup*',`Glib::RefPtr<SizeGroup>',`Glib::wrap($3)')
_CONVERSION(`GtkSizeGroup*',`Glib::RefPtr<const SizeGroup>',`Glib::wrap($3)')

_CONVERSION(`GtkEntryBuffer*',`Glib::RefPtr<EntryBuffer>',`Glib::wrap($3)')
_CONVERSION(`GtkEntryBuffer*',`Glib::RefPtr<const EntryBuffer>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<EntryBuffer>&',`GtkEntryBuffer*',__CONVERT_REFPTR_TO_P)

# Tree:
#_CONVERSION(`const TreeIter&',`const GtkTreeIter*',__FR2P)
_CONVERSION(`const iterator&',`const GtkTreeIter*',__FR2P)
#_CONVERSION(`const TreeIter&',`GtkTreeIter*',__FCR2P)
_CONVERSION(`const iterator&',`GtkTreeIter*',__FCR2P)
_CONVERSION(`const TreeModel::Row&',`GtkTreeIter*',__FCR2P)
_CONVERSION(`iterator&',`GtkTreeIter*',__FR2P)
_CONVERSION(`const TreeModel::iterator&',`GtkTreeIter*',__FCR2P)
_CONVERSION(`const iterator&',`GtkTreeIter*',__FCR2P)
_CONVERSION(`TreeViewColumn&',`GtkTreeViewColumn*',__FR2P)
_CONVERSION(`GtkTreeViewColumn*',`TreeViewColumn*',`Glib::wrap($3)')
_CONVERSION(`GtkTreeViewColumn*',`const TreeViewColumn*',`Glib::wrap($3)')
_CONVERSION(`TreePath&',`GtkTreePath*',__FR2P)
_CONVERSION(`const TreePath&',`const GtkTreePath*',__FR2P)
_CONVERSION(`const TreePath&',`GtkTreePath*',__FCR2P)
_CONVERSION(`const Path&',`GtkTreePath*',__FCR2P)
_CONVERSION(`const TreeModel::Path&',`GtkTreePath*',__FCR2P)
_CONVERSION(`GtkTreeView*',`TreeView*',`Glib::wrap($3)')
_CONVERSION(`GtkTreeView*',`const TreeView*',`Glib::wrap($3)')
_CONVERSION(`GtkTreeModel*',`Glib::RefPtr<TreeModel>',`Glib::wrap($3)')
_CONVERSION(`GtkTreeModel*',`Glib::RefPtr<const TreeModel>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<TreeModel>&',`GtkTreeModel*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkTreeSelection*',`Glib::RefPtr<TreeSelection>',`Glib::wrap($3)')
_CONVERSION(`GtkTreeSelection*',`Glib::RefPtr<const TreeSelection>',`Glib::wrap($3)')
_CONVERSION(`const TreeModelColumnBase&',`int',`($3).index`'()')
_CONVERSION(`GtkTreePath*',`TreePath', `Gtk::TreePath($3, false)')
_CONVERSION(`GtkTreePath*',`Path', `Gtk::TreePath($3, false)')
_CONVERSION(`GtkTreePath*',`TreeModel::Path', `Gtk::TreePath($3, false)')
_CONVERSION(`GtkIconSize&',`GtkIconSize*',`&($3)')
_CONVERSION(`GtkCellEditable*',`CellEditable*',`dynamic_cast<$2>(Glib::wrap_auto((GObject*)($3), false))')
_CONVERSION(`CellEditable*',`GtkCellEditable*',`Glib::unwrap($3)')


#_CONVERSION(`Clipboard&',`GtkClipboard*',`($3).gobj()')
_CONVERSION(`GtkClipboard*',`Glib::RefPtr<Clipboard>',`Glib::wrap($3)')
_CONVERSION(`GtkClipboard*',`Glib::RefPtr<const Clipboard>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Clipboard>&',`GtkClipboard*',__CONVERT_REFPTR_TO_P($3))
#_CONVERSION(`GtkClipboard*',`Gtk::Clipboard&',`Glib::wrap($3, true)')

_CONVERSION(`SelectionData',`GtkSelectionData*', `($3).gobj()')
_CONVERSION(`const SelectionData&',`const GtkSelectionData*', __FR2P)
_CONVERSION(`const SelectionData&',`GtkSelectionData*', __FCR2P)
_CONVERSION(`SelectionData&',`GtkSelectionData*', __FR2P)
#_CONVERSION(`GtkSelectionData*',`SelectionData', `Gtk::SelectionData(($3), true)')

_CONVERSION(`GtkAction*',`Glib::RefPtr<Action>',`Glib::wrap($3)')
_CONVERSION(`GtkAction*',`Glib::RefPtr<const Action>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Action>&',`GtkAction*',__CONVERT_REFPTR_TO_P($3))
_CONVERSION(`const Glib::RefPtr<RadioAction>&',`GtkRadioAction*',__CONVERT_REFPTR_TO_P($3))

_CONVERSION(`GtkActionGroup*',`Glib::RefPtr<ActionGroup>',`Glib::wrap($3)')
#_CONVERSION(`GtkActionGroup*',`Glib::RefPtr<const ActionGroup>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<ActionGroup>&',`GtkActionGroup*',__CONVERT_REFPTR_TO_P($3))

_CONVERSION(`GtkApplication*',`Glib::RefPtr<Application>',`Glib::wrap($3)')
_CONVERSION(`GtkApplication*',`Glib::RefPtr<const Application>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Application>&',`GtkApplication*',__CONVERT_REFPTR_TO_P($3))

_CONVERSION(`GtkEntryCompletion*',`Glib::RefPtr<EntryCompletion>',`Glib::wrap($3)')
_CONVERSION(`GtkEntryCompletion*',`Glib::RefPtr<const EntryCompletion>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<EntryCompletion>&',`GtkEntryCompletion*',__CONVERT_REFPTR_TO_P($3))

_CONVERSION(`GtkFileFilter*',`Glib::RefPtr<FileFilter>',`Glib::wrap($3)')
_CONVERSION(`GtkFileFilter*',`Glib::RefPtr<const FileFilter>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<FileFilter>&',`GtkFileFilter*',__CONVERT_CONST_REFPTR_TO_P)

_CONVERSION(`GdkPixbufFormat*',`PixbufFormat',`PixbufFormat($3)')

_CONVERSION(const Gtk::Widget&,GtkWidget*,__CFR2P)

#_CONVERSION(`GtkTooltips*',`Tooltips&', `Glib::wrap($3)')
_CONVERSION(`GtkTooltips*',`Tooltips*', `Glib::wrap($3)')
_CONVERSION(`Tooltips*',`GtkTooltips*',`Glib::unwrap($3)')
_CONVERSION(`Tooltips&',`GtkTooltips*',__FR2P)

_CONVERSION(`const Glib::RefPtr<Tooltip>&',`GtkTooltip*',__CONVERT_REFPTR_TO_P)

#_CONVERSION(`GtkAllocation*',`Allocation&',`($2)(Glib::wrap($3))')

#TargetList
_CONVERSION(`const Glib::RefPtr<TargetList>&',`GtkTargetList*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`Glib::RefPtr<TargetList>&',`GtkTargetList*',__CONVERT_REFPTR_TO_P($3))
_CONVERSION(`GtkTargetList*',`Glib::RefPtr<TargetList>',`Glib::wrap($3)')
_CONVERSION(`GtkTargetList*',`Glib::RefPtr<const TargetList>',`Glib::wrap($3)')

#IconInfo
_CONVERSION(`GtkIconInfo*',`IconInfo',`Glib::wrap($3)')

_CONVERSION(`Requisition&', `GtkRequisition*', `($2)(&$3)')
_CONVERSION(`const Requisition&', `GtkRequisition*', `($2)(&$3)')
_CONVERSION(`GtkRequisition*', `Requisition&', `($2)(*$3)')
_CONVERSION(`GtkRequisition*', `Requisition*', `($2)($3)')
_CONVERSION(`Requisition*', `GtkRequisition*', `($2)($3)')
_CONVERSION(`GtkRequisition', `Requisition', `($2)($3)')

_CONVERSION(`Allocation&',`GtkAllocation*',`($2)($3.gobj())')
_CONVERSION(`const Allocation&',`GtkAllocation*',`($2)($3.gobj())')
_CONVERSION(`Allocation',`GtkAllocation',`($2)(*($3.gobj()))')

_CONVERSION(`GtkEntry*',`Entry*',__RP2P)
_CONVERSION(`GtkEntry*',`const Entry*',__RP2P)
_CONVERSION(`Entry&',`GtkEntry*',__FR2P)


_CONVERSION(`Gtk::Border&',`GtkBorder*',__FR2P)
_CONVERSION(`GtkBorder*',`Gtk::Border&',`Glib::wrap($3)')
_CONVERSION(`const Border&',`const GtkBorder*',__FR2P)
_CONVERSION(`Border&',`GtkBorder*',__FR2P)
_CONVERSION(`const GtkBorder*',`Border',`Glib::wrap(const_cast<GtkBorder*>($3))')

_CONVERSION(`GtkShortcutsWindow*',`ShortcutsWindow*',__RP2P)
_CONVERSION(`GtkShortcutsWindow*',`const ShortcutsWindow*',__RP2P)
_CONVERSION(`ShortcutsWindow&',`GtkShortcutsWindow*',__FR2P)

#FlowBoxChild
_CONVERSION(`GtkFlowBoxChild*',`FlowBoxChild*',__RP2P)
_CONVERSION(`GtkFlowBoxChild*',`const FlowBoxChild*',__RP2P)
_CONVERSION(`FlowBoxChild&',`GtkFlowBoxChild*',__FR2P)
_CONVERSION(`FlowBoxChild*',`GtkFlowBoxChild*',__FP2P)

#ListBoxRow
_CONVERSION(`GtkListBoxRow*',`ListBoxRow*',__RP2P)
_CONVERSION(`GtkListBoxRow*',`const ListBoxRow*',__RP2P)
_CONVERSION(`ListBoxRow&',`GtkListBoxRow*',__FR2P)
_CONVERSION(`ListBoxRow*',`GtkListBoxRow*',__FP2P)

#RecentFilter
_CONVERSION(`GtkRecentFilterFlags',`RecentFilterFlags',`($2)$3')
_CONVERSION(`const Glib::RefPtr<RecentFilter>&', `GtkRecentFilter*', __CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkRecentFilter*',`Glib::RefPtr<RecentFilter>', `Glib::wrap($3)')
_CONVERSION(`GtkRecentFilter*',`Glib::RefPtr<const RecentFilter>', `Glib::wrap($3)')

#RecentInfo
_CONVERSION(`GtkRecentInfo*',`Glib::RefPtr<RecentInfo>',`Glib::wrap($3)')
_CONVERSION(`GtkRecentInfo*',`Glib::RefPtr<const RecentInfo>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<RecentInfo>&',`GtkRecentInfo*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const RecentInfo>&',`GtkRecentInfo*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gtk::RecentInfo))

_CONVERSION(`Glib::StringArrayHandle&',`gchar**',`const_cast<gchar**>(($3).data())')
_CONVERSION(`Glib::StringArrayHandle&',`const gchar**',`const_cast<const gchar**>(($3).data())')
_CONVERSION(`gchar**',`Glib::StringArrayHandle',`Glib::StringArrayHandle($3)')

#RecentManager
_CONVERSION(`GtkRecentManager*',`Glib::RefPtr<RecentManager>',`Glib::wrap($3)')
_CONVERSION(`GtkRecentManager*',`Glib::RefPtr<const RecentManager>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<RecentManager>&',`GtkRecentManager*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`Glib::RefPtr<RecentManager>',`GtkRecentManager*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`Glib::RefPtr<const RecentManager>', `GtkRecentManager*', __CONVERT_CONST_REFPTR_TO_P_SUN(Gtk::RecentManager))

#PaperSize
_CONVERSION(`GtkPaperSize*',`PaperSize',`Glib::wrap($3, true)')
_CONVERSION(`GtkPaperSize*',`const PaperSize',`Glib::wrap($3, true)')
_CONVERSION(`const PaperSize&',`GtkPaperSize*',__FCR2P)

#PageSetup
_CONVERSION(`GtkPageOrientation',`PageOrientation',`($2)$3')

_CONVERSION(`PageSetup&',`GtkPageSetup*',__FR2P)
_CONVERSION(`const PageSetup&',`GtkPageSetup*',__FCR2P)
_CONVERSION(`GtkPageSetup*',`Glib::RefPtr<PageSetup>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<PageSetup>',`GtkPageSetup*',__CONVERT_REFPTR_TO_P($3))
_CONVERSION(`const Glib::RefPtr<PageSetup>&',`GtkPageSetup*',__CONVERT_REFPTR_TO_P($3))

#PrintSettings
_CONVERSION(`GtkPrintDuplex',`PrintDuplex',`($2)$3')
_CONVERSION(`GtkPrintQuality',`PrintQuality',`($2)$3')
_CONVERSION(`GtkPrintPages',`PrintPages',`($2)$3')
_CONVERSION(`GtkPageSet',`PageSet',`($2)$3')

_CONVERSION(`PrintSettings&',`GtkPrintSettings*',__FR2P)
_CONVERSION(`const PrintSettings&',`GtkPrintSettings*',__FCR2P)
_CONVERSION(`GtkPrintSettings*',`Glib::RefPtr<PrintSettings>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<PrintSettings>&',`GtkPrintSettings*',__CONVERT_REFPTR_TO_P)

#PrintContext
_CONVERSION(`const Glib::RefPtr<PrintContext>',`GtkPrintContext*',__CONVERT_REFPTR_TO_P($3))
_CONVERSION(`const Glib::RefPtr<PrintContext>&',`GtkPrintContext*',__CONVERT_REFPTR_TO_P($3))

_CONVERSION(`GtkPrintOperationResult',`PrintOperationResult',`($2)$3')
_CONVERSION(`GtkPrintStatus',`PrintStatus',`($2)$3')

_CONVERSION(`const ::Cairo::RefPtr< ::Cairo::Context>&',`cairo_t*',`($3)->cobj()')
_CONVERSION(`const ::Cairo::RefPtr<const ::Cairo::Context>&',`cairo_t*',`const_cast<cairo_t*>(($3)->cobj())')
_CONVERSION(`const ::Cairo::FontOptions&',`const cairo_font_options_t*',`($3).cobj()')


#Printer
_CONVERSION(`GtkPrinter*',`Glib::RefPtr<Printer>',`Glib::wrap($3)')
_CONVERSION(`GtkPrinter*',`Glib::RefPtr<const Printer>',`Glib::wrap($3)')
#_CONVERSION(`Glib::RefPtr<Printer>&',`GtkPrinter*',__CONVERT_REFPTR_TO_P($3))
_CONVERSION(`const Glib::RefPtr<Printer>&',`GtkPrinter*',__CONVERT_REFPTR_TO_P($3))

#PrintJob
_CONVERSION(`GtkPrintCapabilities',`PrintCapabilities',`($2)$3')

#Tooltip
#TODO: This should not be here:
_CONVERSION(`const Glib::RefPtr<Tooltip>&',`GtkTooltip*',__CONVERT_REFPTR_TO_P($3))


# Used by Signals:
# TODO: Move these to the .hg files.
# The true here means "take reference", because the code that emits the signal does not do a ref for the receiving signal handler.
# For the return values of methods, we use the optional refreturn parameter instead.
_CONVERSION(`GtkTextIter*',`const TextIter&',Glib::wrap($3))
_CONVERSION(`GtkTextIter*',`const TextBuffer::iterator&',Glib::wrap($3))
_CONVERSION(`const GtkTextIter*',`const TextIter&',Glib::wrap($3))
_CONVERSION(`const GtkTextIter*',`const TextBuffer::iterator&',Glib::wrap($3))
_CONVERSION(`const TextIter&',`GtkTextIter*',__FCR2P)
_CONVERSION(`const TextBuffer::iterator&',`GtkTextIter*',__FCR2P)
_CONVERSION(`GtkTreePath*',`const TreeModel::Path&',`Gtk::TreePath($3, true)')
_CONVERSION(`GtkTreePath*',`const Path&',`Gtk::TreePath($3, true)')
_CONVERSION(`TreeViewColumn*',`GtkTreeViewColumn*',__FP2P)

_CONVERSION(`GtkSelectionData*',`const SelectionData&', `SelectionData_WithoutOwnership($3)')
_CONVERSION(`GtkSelectionData*',`SelectionData&', `SelectionData_WithoutOwnership($3)')
_CONVERSION(`const Glib::RefPtr<const TreeModel>&',`GtkTreeModel*',__CONVERT_CONST_REFPTR_TO_P)
#_CONVERSION(`GtkTreeIter*',`const TreeModel::iterator&',Glib::wrap($3, true))
_CONVERSION(`CellRenderer*',`GtkCellRenderer*',__FP2P)
_CONVERSION(`GtkCellRenderer*',`CellRenderer*',__RP2P)

_CONVERSION(`Align',`float',`_gtkmm_align_float_from_enum($3)')

# Used by AboutDialog:
#_CONVERSION(`const Glib::StringArrayHandle&',`const gchar**',`($3).data())')
_CONVERSION(`const Glib::StringArrayHandle&',`const gchar**',`const_cast<const gchar**>(($3).data())')

_CONVERSION(`const Glib::RefPtr<Gio::AsyncResult>&',`GAsyncResult*',__CONVERT_REFPTR_TO_P)

_CONVERSION(`const Glib::RefPtr<const Gio::Icon>&',`GIcon*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gio::Icon))
_CONVERSION(`GIcon*',`Glib::RefPtr<Gio::Icon>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gio::Icon>&',`GIcon*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gio::Icon))
_CONVERSION(`const Glib::RefPtr<const Gio::File>&',`GFile*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gio::File))
_CONVERSION(`const Glib::RefPtr<Gio::File>&',`GFile*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gio::File))
_CONVERSION(`GFile*',`Glib::RefPtr<Gio::File>',`Glib::wrap($3)')
_CONVERSION(`GFile*',`Glib::RefPtr<const Gio::File>',`Glib::wrap($3)')

_CONVERSION(`const Glib::RefPtr<Gio::Cancellable>&',`GCancellable*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Gio::InputStream>&',`GInputStream*',__CONVERT_CONST_REFPTR_TO_P)

_CONVERSION(`const Glib::RefPtr<Gio::AppInfo>&',`GAppInfo*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gio::AppInfo))
_CONVERSION(`GAppInfo*',`Glib::RefPtr<Gio::AppInfo>',`Glib::wrap($3)')

_CONVERSION(`GMenu*',`Glib::RefPtr<Gio::Menu>',`Glib::wrap($3)')
_CONVERSION(`GMenu*',`Glib::RefPtr<const Gio::Menu>',`Glib::wrap($3)')

_CONVERSION(`const Glib::RefPtr<Gio::MenuModel>&',`GMenuModel*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Gio::MenuModel>&',`GMenuModel*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`GMenuModel*',`Glib::RefPtr<Gio::MenuModel>',`Glib::wrap($3)')
_CONVERSION(`GMenuModel*',`Glib::RefPtr<const Gio::MenuModel>',`Glib::wrap($3)')

_CONVERSION(`const Glib::RefPtr<Gio::ActionGroup>&',`GActionGroup*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gio::ActionGroup))
_CONVERSION(`GActionGroup*',`Glib::RefPtr<Gio::ActionGroup>',`Glib::wrap($3)')
_CONVERSION(`GActionGroup*',`Glib::RefPtr<const Gio::ActionGroup>',`Glib::wrap($3)')

_CONVERSION(`GtkDragResult',`DragResult',`($2)$3')

_CONVERSION(`GtkWidgetPath*',`WidgetPath',`Glib::wrap($3, true)')
_CONVERSION(`const GtkWidgetPath*',`WidgetPath',`Glib::wrap(const_cast<GtkWidgetPath*>($3), true)')

# Used by LockButton
_CONVERSION(`Glib::RefPtr<Gio::Permission>&',`GPermission*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Gio::Permission>&',`GPermission*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gio::Permission))
_CONVERSION(`GPermission*',`Glib::RefPtr<Gio::Permission>',`Glib::wrap($3)')

_CONVERSION(`const Glib::RefPtr<Pango::FontMap>&',`PangoFontMap*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Pango::FontMap>&',`PangoFontMap*',__CONVERT_CONST_REFPTR_TO_P)
