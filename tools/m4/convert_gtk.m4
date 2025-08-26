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
_CONVERSION(`double*',`double&',`*($3)')
_CONVERSION(`float&',`float*',`&($3)')

_CONVERSION(`time_t&',`time_t*',`&($3)')
_CONVERSION(`time_t',`std::time_t',`$3')

_CONVERSION(`ui_merge_id',`guint',`$3')
_CONVERSION(`guint',`ui_merge_id',`$3')

# Enums: TODO: It would be nice if gmmproc knew about these automatically.
_CONV_INCLASS_ENUM(Gtk,Accessible,Role)
_CONV_INCLASS_ENUM(Gtk,Accessible,State)
_CONV_INCLASS_ENUM(Gtk,Accessible,Property)
_CONV_INCLASS_ENUM(Gtk,Accessible,Relation)
_CONV_INCLASS_ENUM(Gtk,Accessible,PlatformState)
_CONV_INCLASS_ENUM(Gtk,Accessible,AnnouncementPriority)
_CONV_INCLASS_ENUM(Gtk,AccessibleText,ContentChange)
_CONV_INCLASS_ENUM(Gtk,AccessibleText,Granularity)
_CONV_ENUM(Gtk,Align)
_CONV_ENUM(Gtk,ArrowType)
_CONV_INCLASS_ENUM(Gtk,AssistantPage,Type)
_CONV_ENUM(Gtk,ButtonRole)
_CONV_ENUM(Gtk,ButtonsType)
_CONV_ENUM(Gtk,CellRendererMode)
_CONV_ENUM(Gtk,CellRendererState)
_CONV_ENUM(Gtk,Collation)
_CONV_INCLASS_ENUM(Gtk,Constraint,Attribute)
_CONV_INCLASS_ENUM(Gtk,Constraint,Relation)
_CONV_INCLASS_ENUM(Gtk,Constraint,Strength)
_CONV_ENUM(Gtk,ContentFit)
_CONV_ENUM(Gtk,CornerType)
_CONV_ENUM(Gtk,CssParserError)
_CONV_ENUM(Gtk,CssParserWarning)
_CONV_ENUM(Gtk,CurveType)
_CONV_ENUM(Gtk,DeleteType)
_CONV_ENUM(Gtk,DialogError)
_CONV_ENUM(Gtk,DirectionType)
_CONV_INCLASS_ENUM(Gtk,EventControllerScroll,Flags)
_CONV_ENUM(Gtk,EventSequenceState)
_CONV_INCLASS_ENUM(Gtk,Filter,Change)
_CONV_INCLASS_ENUM(Gtk,Filter,Match)
_CONV_INCLASS_ENUM(Gtk,FontChooser,Level)
_CONV_ENUM(Gtk,FontLevel)
_CONV_ENUM(Gtk,FontRendering)
_CONV_ENUM(Gtk,GraphicsOffloadEnabled)
_CONV_INCLASS_ENUM(Gtk,Image,Type)
_CONV_ENUM(Gtk,IconSize)
_CONV_INCLASS_ENUM(Gtk,Inscription,Overflow)
_CONV_ENUM(Gtk,InterfaceColorScheme)
_CONV_ENUM(Gtk,InterfaceContrast)
_CONV_ENUM(Gtk,Justification)
_CONV_ENUM(Gtk,License)
_CONV_ENUM(Gtk,ListScrollFlags)
_CONV_ENUM(Gtk,ListTabBehavior)
_CONV_ENUM(Gtk,MessageType)
_CONV_ENUM(Gtk,MovementStep)
_CONV_ENUM(Gtk,NaturalWrapMode)
_CONV_ENUM(Gtk,NotebookTab)
_CONV_ENUM(Gtk,Orientation)
_CONV_ENUM(Gtk,Ordering)
_CONV_ENUM(Gtk,Overflow)
_CONV_ENUM(Gtk,PackType)
_CONV_ENUM(Gtk,PanDirection)
_CONV_ENUM(Gtk,PickFlags)
_CONV_ENUM(Gtk,PolicyType)
_CONV_INCLASS_ENUM(Gtk,Popover,Constraint)
_CONV_INCLASS_ENUM(Gtk,PopoverMenu,Flags)
_CONV_ENUM(Gtk,PositionType)
_CONV_ENUM(Gtk,PreviewType)
_CONV_ENUM(Gtk,ProgressBarOrientation)
_CONV_ENUM(Gtk,ProgressBarStyle)
_CONV_ENUM(Gtk,PropagationLimit)
_CONV_ENUM(Gtk,PropagationPhase)
_CONV_ENUM(Gtk,RevealerTransitionType)
_CONV_ENUM(Gtk,ScrollType)
_CONV_ENUM(Gtk,SelectionMode)
_CONV_INCLASS_ENUM(Gtk,ShortcutAction,Flags)
_CONV_ENUM(Gtk,ShortcutScope)
_CONV_ENUM(Gtk,ShortcutType)
_CONV_INCLASS_ENUM(Gtk,SizeGroup,Mode)
_CONV_INCLASS_ENUM(Gtk,Sorter,Change)
_CONV_INCLASS_ENUM(Gtk,Sorter,Order)
_CONV_ENUM(Gtk,SortType)
_CONV_INCLASS_ENUM(Gtk,SpinButton,UpdatePolicy)
_CONV_ENUM(Gtk,SpinType)
_CONV_ENUM(Gtk,StackTransitionType)
_CONV_INCLASS_ENUM(Gtk,StringFilter,MatchMode)
_CONV_INCLASS_ENUM(Gtk,StyleContext,PrintFlags)
_CONV_INCLASS_ENUM(Gtk,TextBuffer,NotifyFlags)
_CONV_ENUM(Gtk,TextDirection)
_CONV_ENUM(Gtk,TextSearchFlags)
_CONV_ENUM(Gtk,TextWindowType)
_CONV_INCLASS_ENUM(Gtk,TreeModel,Flags)
_CONV_INCLASS_ENUM(Gtk,TreeViewColumn,Sizing)
_CONV_INCLASS_ENUM(Gtk,TreeView,DropPosition)
_CONV_INCLASS_ENUM(Gtk,TreeView,GridLines)
_CONV_ENUM(Gtk,UpdateType)
_CONV_ENUM(Gtk,Visibility)
_CONV_ENUM(Gtk,WrapMode)
_CONV_INCLASS_ENUM(Gtk,FileChooser,Action)
_CONV_ENUM(Gtk,IconLookupFlags)
_CONV_ENUM(Gtk,IconThemeError)
_CONV_ENUM(Gtk,SensitivityType)
_CONV_INCLASS_ENUM(Gtk,IconView,DropPosition)
_CONV_INCLASS_ENUM(Gtk,RecentFilter,Flags)
_CONV_ENUM(Gtk,RecentManagerError)
_CONV_ENUM(Gtk,RecentSortType)
_CONV_ENUM(Gtk,Unit)
_CONV_ENUM(Gtk,PadActionType)
_CONV_ENUM(Gtk,PageOrientation)
_CONV_ENUM(Gtk,PrintDuplex)
_CONV_ENUM(Gtk,PrintQuality)
_CONV_ENUM(Gtk,PrintPages)
_CONV_ENUM(Gtk,PageSet)
_CONV_ENUM(Gtk,PrintStatus)
_CONV_INCLASS_ENUM(Gtk,PrintOperation,Result)
_CONV_INCLASS_ENUM(Gtk,PrintOperation,Action)
_CONV_ENUM(Gtk,PrintError)
_CONV_ENUM(Gtk,PrintCapabilities)
_CONV_ENUM(Gtk,NumberUpLayout)
_CONV_INCLASS_ENUM(Gtk,Entry,IconPosition)
_CONV_ENUM(Gtk,WrapAllocationMode)
_CONV_ENUM(Gtk,WrapBoxPacking)
_CONV_ENUM(Gtk,WrapBoxSpreading)
_CONV_ENUM(Gtk,SizeRequestMode)
_CONV_INCLASS_ENUM(Gtk,Scrollable,Policy)
_CONV_ENUM(Gtk,StateFlags)
_CONV_INCLASS_ENUM(Gtk,Application,InhibitFlags)
_CONV_ENUM(Gtk,InputPurpose)
_CONV_ENUM(Gtk,InputHints)
_CONV_INCLASS_ENUM(Gtk,LevelBar,Mode)
_CONV_ENUM(Gtk,BaselinePosition)
_CONV_ENUM(Gtk,WindowGravity)

include(convert_pango.m4)
include(convert_gdk.m4)

_CONVERSION(`guint',`WindowType',`static_cast<WindowType>($3)')
_CONVERSION(`PolicyType&',`GtkPolicyType*',`(($2) &($3))')
_CONVERSION(`SortType&',`GtkSortType*',`(($2) &($3))')
_CONVERSION(`SortType*',`GtkSortType*',`(($2) ($3))')
_CONVERSION(`GtkSortType*',`SortType*',`(($2) ($3))')
_CONVERSION(`guint8',`Gtk::StateType',`static_cast<StateType>($3)')


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
_CONVERSION(`GtkPopover*',`Popover*',__RP2P)
_CONVERSION(`GtkStack*',`Stack*',__RP2P)
_CONVERSION(`GtkStackPage*',`Glib::RefPtr<StackPage>',`Glib::wrap($3)')
_CONVERSION(`GtkStackPage*',`Glib::RefPtr<const StackPage>',`Glib::wrap($3)')

# Ptr (gtk+) -> const Ptr (gtkmm)
_CONVERSION(`GtkWidget*',`const Gtk::Widget*',__RP2P)
_CONVERSION(`GtkWidget*',`const Widget*',__RP2P)
_CONVERSION(`GtkWindow*',`const Window*',__RP2P)

# Style:
_CONVERSION(`GtkStyleContext*',`Glib::RefPtr<StyleContext>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<StyleContext>&',`GtkStyleContext*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkStyleProvider*',`Glib::RefPtr<StyleProvider>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<StyleProvider>&',`GtkStyleProvider*',__CONVERT_REFPTR_TO_P)

_CONVERSION(`GtkCssProvider*',`Glib::RefPtr<CssProvider>',`Glib::wrap($3)')
_CONVERSION(`GtkCssSection*',`Glib::RefPtr<CssSection>',`Glib::wrap($3)')
_CONVERSION(`const CssLocation&',`const GtkCssLocation*',__FR2P)
_CONVERSION(`const GtkCssLocation*',`CssLocation',`Glib::wrap($3)')

_CONVERSION(`GtkAssistantPage*',`Glib::RefPtr<AssistantPage>',`Glib::wrap($3)')
_CONVERSION(`GtkAssistantPage*',`Glib::RefPtr<const AssistantPage>',`Glib::wrap($3)')
_CONVERSION(`GtkNotebookPage*',`Glib::RefPtr<NotebookPage>',`Glib::wrap($3)')
_CONVERSION(`GtkNotebookPage*',`Glib::RefPtr<const NotebookPage>',`Glib::wrap($3)')

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

#
# Ptr (gtk+) -> Ptr (gtkmm) (downcast)
_CONVERSION(`GtkWidget*',`Button*',`Glib::wrap((GtkButton*)($3))')
_CONVERSION(`GtkWidget*',`Box*',`Glib::wrap((GtkBox*)($3))')
_CONVERSION(`GtkWidget*',`Gtk::CheckButton*',__RP2PD)
_CONVERSION(`GtkWidget*',`Entry*',`Glib::wrap((GtkEntry*)($3))')
_CONVERSION(`GtkWidget*',`HeaderBar*',`Glib::wrap((GtkHeaderBar*)($3))')
_CONVERSION(`GtkWidget*',`Label*',`Glib::wrap((GtkLabel*)($3))')
_CONVERSION(`GtkWidget*',`Popover*',`Glib::wrap((GtkPopover*)($3))')
_CONVERSION(`GtkWidget*',`Gtk::Scrollbar*',__RP2PD)
_CONVERSION(`GtkWidget*',`Gtk::Tree*',__RP2PD)
_CONVERSION(`GtkWidget*',`ScrolledWindow*',`Glib::wrap((GtkScrolledWindow*)($3))')
_CONVERSION(`GtkWidget*',`Window*',`Glib::wrap((GtkWindow*)($3))')
_CONVERSION(`GtkWidget*',`TreeView*',`Glib::wrap((GtkTreeView*)($3))')
_CONVERSION(`GtkWidget*',`Image*',`Glib::wrap((GtkImage*)($3))')
_CONVERSION(`GtkWidget*',`FileChooserDialog*',`Glib::wrap((GtkFileChooserDialog*)($3))')
_CONVERSION(`GtkWidget*',`DragIcon*',`Glib::wrap((GtkDragIcon*)($3))')

# Ptr (gtk+) -> const Ptr (gtkmm) (downcast)
_CONVERSION(`GtkWidget*',`const Button*',`Glib::wrap((GtkButton*)($3))')
_CONVERSION(`GtkWidget*',`const Box*',`Glib::wrap((GtkBox*)($3))')
_CONVERSION(`GtkWidget*',`const Gtk::CheckButton*',__RP2CPD)
_CONVERSION(`GtkWidget*',`const Entry*',`Glib::wrap((GtkEntry*)($3))')
_CONVERSION(`GtkWidget*',`const Label*',`Glib::wrap((GtkLabel*)($3))')
_CONVERSION(`GtkWidget*',`const Popover*',`Glib::wrap((GtkPopover*)($3))')
_CONVERSION(`GtkWidget*',`const Gtk::Scrollbar*',__RP2CPD)
_CONVERSION(`GtkWidget*',`const Gtk::Tree*',__RP2CPD)
_CONVERSION(`GtkWidget*',`const ScrolledWindow*',`Glib::wrap((GtkScrolledWindow*)($3))')
_CONVERSION(`GtkWidget*',`const Window*',`Glib::wrap((GtkWindow*)($3))')
_CONVERSION(`GtkWidget*',`const TreeView*',`Glib::wrap((GtkTreeView*)($3))')
_CONVERSION(`GtkWidget*',`const FileChooserDialog*',`Glib::wrap((GtkFileChooserDialog*)($3))')

# Ptr (gtk+) -> Ref (Gtkmm)
_CONVERSION(`GtkWidget*', `Widget&', `*Glib::wrap($3)')
_CONVERSION(`GtkWidget*', `const Widget&', `*Glib::wrap($3)')

# Ref (Gtkmm) -> GtkWidget* Ptr (gtk+)
define(`__FR2PD',`($`'3).Gtk::Widget::gobj()')
_CONVERSION(`Popover&',`GtkWidget*',__FR2PD)
_CONVERSION(`Gtk::TreeItem&',`GtkWidget*',__FR2PD)
_CONVERSION(`FileChooserDialog&',`GtkWidget*',__FR2PD)

# Ref (Gtkmm) -> Ptr (gtk+)
define(`__FR2P',`($`'3).gobj()')
define(`__FCR2P',`const_cast<$`'2>(($`'3).gobj())')
_CONVERSION(`Gtk::Widget&',`GtkWidget*',__FR2P)
_CONVERSION(`Widget&',`GtkWidget*',__FR2P)
_CONVERSION(`Window&',`GtkWindow*',__FR2P)
_CONVERSION(`const Window&',`GtkWindow*',__FCR2P)
_CONVERSION(`CellRenderer&',`GtkCellRenderer*',__FR2P)
_CONVERSION(`const CellRenderer&',`GtkCellRenderer*',__FCR2P)
_CONVERSION(`Gtk::Entry&',`GtkEntry*',__FR2P)
_CONVERSION(`Stack&',`GtkStack*',__FR2P)
_CONVERSION(`CheckButton&',`GtkCheckButton*',__FR2P)
_CONVERSION(`ToggleButton&',`GtkToggleButton*',__FR2P)
_CONVERSION(`const Widget&',`GtkWidget*',__FCR2P)
_CONVERSION(`int&',`int*',`&$3',`*$3')
_CONVERSION(`ShortcutsSection&',`GtkShortcutsSection*',__FR2P)
_CONVERSION(`ShortcutsGroup&',`GtkShortcutsGroup*',__FR2P)
_CONVERSION(`ShortcutsShortcut&',`GtkShortcutsShortcut*',__FR2P)

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

_CONVERSION(`GtkIconPaintable*',`Glib::RefPtr<IconPaintable>',`Glib::wrap($3)')
_CONVERSION(`GtkIconPaintable*',`Glib::RefPtr<const IconPaintable>',`Glib::wrap($3)')
_CONVERSION(`GtkIconTheme*',`Glib::RefPtr<IconTheme>',`Glib::wrap($3)')

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
_CONVERSION(`TextBuffer::iterator&',`GtkTextIter*',__FR2P)
_CONVERSION(`TextBuffer::const_iterator&',`GtkTextIter*',__FR2P)
_CONVERSION(`iterator&',`GtkTextIter*',__FR2P)
_CONVERSION(`const_iterator&',`GtkTextIter*',__FR2P)
_CONVERSION(`const TextBuffer::iterator&',`const GtkTextIter*',__FR2P)
_CONVERSION(`const TextBuffer::const_iterator&',`const GtkTextIter*',__FR2P)
_CONVERSION(`const iterator&',`const GtkTextIter*',__FR2P)
_CONVERSION(`const iterator&',`GtkTextIter*',__FCR2P)
_CONVERSION(`const const_iterator&',`const GtkTextIter*',__FR2P)
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

_CONVERSION(`const Glib::RefPtr<EventController>&',`GtkEventController*',__CONVERT_REFPTR_TO_P)

# Tree:
_CONVERSION(`const iterator&',`const GtkTreeIter*',__FR2P)
_CONVERSION(`const iterator&',`GtkTreeIter*',__FCR2P)
_CONVERSION(`const const_iterator&',`GtkTreeIter*',__FCR2P)
_CONVERSION(`const TreeModel::Row&',`GtkTreeIter*',__FCR2P)
_CONVERSION(`iterator&',`GtkTreeIter*',__FR2P)
_CONVERSION(`const TreeModel::iterator&',`GtkTreeIter*',__FCR2P)
_CONVERSION(`const TreeModel::const_iterator&',`GtkTreeIter*',__FCR2P)
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

_CONVERSION(`GtkAccessible*',`Glib::RefPtr<Accessible>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Accessible>&', `GtkAccessible*', __CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkATContext*',`Glib::RefPtr<ATContext>',`Glib::wrap($3)')

_CONVERSION(`GtkCellEditable*',`CellEditable*',`dynamic_cast<$2>(Glib::wrap_auto((GObject*)($3), false))')
_CONVERSION(`CellEditable*',`GtkCellEditable*',`Glib::unwrap($3)')

_CONVERSION(`GtkEditable*',`Editable*',`dynamic_cast<$2>(Glib::wrap_auto((GObject*)($3), false))')
_CONVERSION(`Editable&',`GtkEditable*',__FR2P)

_CONVERSION(`GtkRoot*',`Root*',`dynamic_cast<$2>(Glib::wrap_auto((GObject*)($3), false))')
_CONVERSION(`GtkNative*',`Native*',`dynamic_cast<$2>(Glib::wrap_auto((GObject*)($3), false))')

_CONVERSION(`SelectionData',`GtkSelectionData*', `($3).gobj()')
_CONVERSION(`const SelectionData&',`const GtkSelectionData*', __FR2P)
_CONVERSION(`const SelectionData&',`GtkSelectionData*', __FCR2P)
_CONVERSION(`SelectionData&',`GtkSelectionData*', __FR2P)
#_CONVERSION(`GtkSelectionData*',`SelectionData', `Gtk::SelectionData(($3), true)')

_CONVERSION(`GtkApplication*',`Glib::RefPtr<Application>',`Glib::wrap($3)')
_CONVERSION(`GtkApplication*',`Glib::RefPtr<const Application>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Application>&',`GtkApplication*',__CONVERT_REFPTR_TO_P($3))

_CONVERSION(`GtkEntryCompletion*',`Glib::RefPtr<EntryCompletion>',`Glib::wrap($3)')
_CONVERSION(`GtkEntryCompletion*',`Glib::RefPtr<const EntryCompletion>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<EntryCompletion>&',`GtkEntryCompletion*',__CONVERT_REFPTR_TO_P($3))

_CONVERSION(`GtkFileFilter*',`Glib::RefPtr<FileFilter>',`Glib::wrap($3)')
_CONVERSION(`GtkFileFilter*',`Glib::RefPtr<const FileFilter>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<FileFilter>&',`GtkFileFilter*',__CONVERT_CONST_REFPTR_TO_P)

_CONVERSION(`GtkMediaStream*',`Glib::RefPtr<MediaStream>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<MediaStream>&',`GtkMediaStream*',__CONVERT_REFPTR_TO_P)

_CONVERSION(`GdkPixbufFormat*',`PixbufFormat',`PixbufFormat($3)')

_CONVERSION(const Gtk::Widget&,GtkWidget*,__CFR2P)

_CONVERSION(`const Glib::RefPtr<Tooltip>&',`GtkTooltip*',__CONVERT_REFPTR_TO_P)

_CONVERSION(`Requisition&', `GtkRequisition*', __FR2P)
_CONVERSION(`const Requisition&', `GtkRequisition*', __FCR2P)
_CONVERSION(`GtkRequisition*', `Requisition&', `Glib::wrap($3)')

_CONVERSION(`Allocation&',`GtkAllocation*',`($2)($3.gobj())')
_CONVERSION(`const Allocation&',`GtkAllocation*',`($2)($3.gobj())')
_CONVERSION(`const Allocation&',`const GtkAllocation*',`($3.gobj())')
_CONVERSION(`Allocation',`GtkAllocation',`static_cast<$2>(*($3.gobj()))')

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

_CONVERSION(`GtkShortcutAction*',`Glib::RefPtr<ShortcutAction>', `Glib::wrap($3)')
_CONVERSION(`GtkShortcutTrigger*',`Glib::RefPtr<ShortcutTrigger>', `Glib::wrap($3)')
_CONVERSION(`GtkShortcutTrigger*',`Glib::RefPtr<const ShortcutTrigger>', `Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<const ShortcutAction>&', `GtkShortcutAction*', __CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const ShortcutTrigger>&', `GtkShortcutTrigger*', __CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<ShortcutController>&', `GtkShortcutController*', __CONVERT_REFPTR_TO_P)

_CONVERSION(`const Glib::RefPtr<Gtk::Snapshot>&', `GtkSnapshot*', __CONVERT_REFPTR_TO_P)

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
_CONVERSION(`GtkRecentFilterFlags',`RecentFilterFlags',`static_cast<$2>($3)')
_CONVERSION(`const Glib::RefPtr<RecentFilter>&', `GtkRecentFilter*', __CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkRecentFilter*',`Glib::RefPtr<RecentFilter>', `Glib::wrap($3)')
_CONVERSION(`GtkRecentFilter*',`Glib::RefPtr<const RecentFilter>', `Glib::wrap($3)')

#RecentInfo
_CONVERSION(`GtkRecentInfo*',`Glib::RefPtr<RecentInfo>',`Glib::wrap($3)')
_CONVERSION(`GtkRecentInfo*',`Glib::RefPtr<const RecentInfo>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<RecentInfo>&',`GtkRecentInfo*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const RecentInfo>&',`GtkRecentInfo*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gtk::RecentInfo))

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
_CONVERSION(`GtkPageOrientation',`PageOrientation',`static_cast<$2>($3)')

_CONVERSION(`PageSetup&',`GtkPageSetup*',__FR2P)
_CONVERSION(`const PageSetup&',`GtkPageSetup*',__FCR2P)
_CONVERSION(`GtkPageSetup*',`Glib::RefPtr<PageSetup>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<PageSetup>',`GtkPageSetup*',__CONVERT_REFPTR_TO_P($3))
_CONVERSION(`const Glib::RefPtr<PageSetup>&',`GtkPageSetup*',__CONVERT_REFPTR_TO_P($3))

#PrintSettings
_CONVERSION(`GtkPrintDuplex',`PrintDuplex',`static_cast<$2>($3)')
_CONVERSION(`GtkPrintQuality',`PrintQuality',`static_cast<$2>($3)')
_CONVERSION(`GtkPrintPages',`PrintPages',`static_cast<$2>($3)')
_CONVERSION(`GtkPageSet',`PageSet',`static_cast<$2>($3)')

_CONVERSION(`PrintSettings&',`GtkPrintSettings*',__FR2P)
_CONVERSION(`const PrintSettings&',`GtkPrintSettings*',__FCR2P)
_CONVERSION(`GtkPrintSettings*',`Glib::RefPtr<PrintSettings>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<PrintSettings>&',`GtkPrintSettings*',__CONVERT_REFPTR_TO_P)

_CONVERSION(`GtkPrintSetup*',`Glib::RefPtr<PrintSetup>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<PrintSetup>&',`GtkPrintSetup*',__CONVERT_REFPTR_TO_P)

#PrintContext
_CONVERSION(`const Glib::RefPtr<PrintContext>',`GtkPrintContext*',__CONVERT_REFPTR_TO_P($3))
_CONVERSION(`const Glib::RefPtr<PrintContext>&',`GtkPrintContext*',__CONVERT_REFPTR_TO_P($3))

_CONVERSION(`GtkPrintOperationResult',`PrintOperationResult',`static_cast<$2>($3)')
_CONVERSION(`GtkPrintStatus',`PrintStatus',`static_cast<$2>($3)')

_CONVERSION(`const Cairo::RefPtr<Cairo::Context>&',`cairo_t*',`(($3) ? ($3)->cobj() : nullptr)')
_CONVERSION(`const Cairo::RefPtr<const Cairo::Context>&',`cairo_t*',`const_cast<cairo_t*>(($3) ? ($3)->cobj() : nullptr)')
_CONVERSION(`cairo_t*',`Cairo::RefPtr<Cairo::Context>',`Gdk::Cairo::wrap($3)')
_CONVERSION(`cairo_t*',`Cairo::RefPtr<const Cairo::Context>',`Gdk::Cairo::wrap($3)')
_CONVERSION(`const Cairo::FontOptions&',`const cairo_font_options_t*',`($3).cobj()')
_CONVERSION(`const Cairo::RefPtr<const Cairo::Region>&',`cairo_region_t*',`const_cast<cairo_region_t*>(($3) ? ($3)->cobj() : nullptr)')
_CONVERSION(`const Cairo::RefPtr<const Cairo::Region>&',`const cairo_region_t*',`(($3) ? ($3)->cobj() : nullptr)')
_CONVERSION(`const Cairo::RefPtr<Cairo::Surface>&',`cairo_surface_t*',`(($3) ? ($3)->cobj() : nullptr)')
_CONVERSION(`const Cairo::RefPtr<const Cairo::Surface>&',`cairo_surface_t*',`const_cast<cairo_surface_t*>(($3) ? ($3)->cobj() : nullptr)')
_CONVERSION(`cairo_surface_t*',`Cairo::RefPtr<Cairo::Surface>',`Gdk::Cairo::wrap($3)')
_CONVERSION(`cairo_surface_t*',`Cairo::RefPtr<const Cairo::Surface>',`Gdk::Cairo::wrap($3)')

#Printer
_CONVERSION(`GtkPrinter*',`Glib::RefPtr<Printer>',`Glib::wrap($3)')
_CONVERSION(`GtkPrinter*',`Glib::RefPtr<const Printer>',`Glib::wrap($3)')
#_CONVERSION(`Glib::RefPtr<Printer>&',`GtkPrinter*',__CONVERT_REFPTR_TO_P($3))
_CONVERSION(`const Glib::RefPtr<Printer>&',`GtkPrinter*',__CONVERT_REFPTR_TO_P($3))

#PrintJob
_CONVERSION(`GtkPrintCapabilities',`PrintCapabilities',`static_cast<$2>($3)')

# Used by Signals:
# TODO: Move these to the .hg files.
# The true here means "take reference", because the code that emits the signal does not do a ref for the receiving signal handler.
# For the return values of methods, we use the optional refreturn parameter instead.
_CONVERSION(`GtkTreePath*',`const TreeModel::Path&',`Gtk::TreePath($3, true)')
_CONVERSION(`GtkTreePath*',`const Path&',`Gtk::TreePath($3, true)')
_CONVERSION(`TreeViewColumn*',`GtkTreeViewColumn*',__FP2P)

_CONVERSION(`GtkSelectionData*',`const SelectionData&', `SelectionData_WithoutOwnership($3)')
_CONVERSION(`GtkSelectionData*',`SelectionData&', `SelectionData_WithoutOwnership($3)')
_CONVERSION(`const Glib::RefPtr<const TreeModel>&',`GtkTreeModel*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`CellRenderer*',`GtkCellRenderer*',__FP2P)
_CONVERSION(`GtkCellRenderer*',`CellRenderer*',__RP2P)

_CONVERSION(`Align',`float',`_gtkmm_align_float_from_enum($3)')

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
_CONVERSION(`GOutputStream*',`Glib::RefPtr<Gio::OutputStream>',`Glib::wrap($3)')

_CONVERSION(`const Glib::RefPtr<Gio::AppInfo>&',`GAppInfo*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gio::AppInfo))
_CONVERSION(`GAppInfo*',`Glib::RefPtr<Gio::AppInfo>',`Glib::wrap($3)')

_CONVERSION(`GMenu*',`Glib::RefPtr<Gio::Menu>',`Glib::wrap($3)')
_CONVERSION(`GMenu*',`Glib::RefPtr<const Gio::Menu>',`Glib::wrap($3)')

_CONVERSION(`const Glib::RefPtr<Gio::MenuModel>&',`GMenuModel*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Gio::MenuModel>&',`GMenuModel*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`GMenuModel*',`Glib::RefPtr<Gio::MenuModel>',`Glib::wrap($3)')
_CONVERSION(`GMenuModel*',`Glib::RefPtr<const Gio::MenuModel>',`Glib::wrap($3)')

_CONVERSION(`GListModel*',`Glib::RefPtr<Gio::ListModel>',`Glib::wrap($3)')
_CONVERSION(`GListModel*',`Glib::RefPtr<const Gio::ListModel>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gio::ListModel>&',`GListModel*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkSelectionModel*',`Glib::RefPtr<SelectionModel>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<SelectionModel>&',`GtkSelectionModel*',__CONVERT_REFPTR_TO_P)

_CONVERSION(`const Glib::RefPtr<const Bitset>&',`GtkBitset*',__CONVERT_CONST_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Bitset>&',`const GtkBitset*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkBitset*',`Glib::RefPtr<const Bitset>',`Glib::wrap($3)')
_CONVERSION(`GtkBitset*',`Glib::RefPtr<Bitset>',`Glib::wrap($3)')

_CONVERSION(`GtkScrollInfo*',`Glib::RefPtr<ScrollInfo>',`Glib::wrap($3)')

_CONVERSION(`const Glib::RefPtr<Gio::ActionGroup>&',`GActionGroup*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gio::ActionGroup))
_CONVERSION(`GActionGroup*',`Glib::RefPtr<Gio::ActionGroup>',`Glib::wrap($3)')
_CONVERSION(`GActionGroup*',`Glib::RefPtr<const Gio::ActionGroup>',`Glib::wrap($3)')

_CONVERSION(`GtkDragResult',`DragResult',`static_cast<$2>($3)')
_CONVERSION(`GtkDropTarget*',`Glib::RefPtr<DropTarget>',`Glib::wrap($3)')

# LayoutChild, LayoutManager
_CONVERSION(`GtkLayoutManager*',`Glib::RefPtr<LayoutManager>',`Glib::wrap($3)')
_CONVERSION(`GtkLayoutManager*',`Glib::RefPtr<const LayoutManager>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<LayoutManager>&',`GtkLayoutManager*',__CONVERT_REFPTR_TO_P)

_CONVERSION(`GtkLayoutChild*',`Glib::RefPtr<LayoutChild>',`Glib::wrap($3)')
_CONVERSION(`GtkLayoutChild*',`Glib::RefPtr<const LayoutChild>',`Glib::wrap($3)')

# Used by LockButton
_CONVERSION(`Glib::RefPtr<Gio::Permission>&',`GPermission*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Gio::Permission>&',`GPermission*',__CONVERT_CONST_REFPTR_TO_P_SUN(Gio::Permission))
_CONVERSION(`GPermission*',`Glib::RefPtr<Gio::Permission>',`Glib::wrap($3)')

_CONVERSION(`const Glib::RefPtr<Pango::FontMap>&',`PangoFontMap*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<const Pango::FontMap>&',`PangoFontMap*',__CONVERT_CONST_REFPTR_TO_P)

# Constraint, ConstraintGuide, ConstraintTarget
_CONVERSION(`const Glib::RefPtr<Constraint>&',`GtkConstraint*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<ConstraintGuide>&',`GtkConstraintGuide*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkConstraintTarget*',`Glib::RefPtr<ConstraintTarget>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<ConstraintTarget>&',`gpointer',__CONVERT_REFPTR_TO_P)

_CONVERSION(`const Glib::RefPtr<ListItemFactory>&', `GtkListItemFactory*', __CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkListItemFactory*',`Glib::RefPtr<ListItemFactory>',`Glib::wrap($3)')
_CONVERSION(`GtkStringObject*',`Glib::RefPtr<StringObject>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Sorter>&', `GtkSorter*', __CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkSorter*',`Glib::RefPtr<Sorter>',`Glib::wrap($3)')
_CONVERSION(`GtkTreeListRow*',`Glib::RefPtr<TreeListRow>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<TreeListRow>&', `GtkTreeListRow*', __CONVERT_REFPTR_TO_P)
_CONVERSION(`const Glib::RefPtr<Filter>&', `GtkFilter*', __CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkFilter*',`Glib::RefPtr<Filter>',`Glib::wrap($3)')

_CONVERSION(`const Glib::RefPtr<Expression<Glib::ustring>>&',`GtkExpression*',`(($3) ? ($3)->gobj() : nullptr)')
_CONVERSION(`GtkExpression*',`Glib::RefPtr<Expression<Glib::ustring>>',`Glib::wrap<Glib::ustring>($3)')
_CONVERSION(`GtkExpression*',`Glib::RefPtr<const Expression<Glib::ustring>>',`Glib::wrap<Glib::ustring>($3)')
_CONVERSION(`const Glib::RefPtr<Expression<bool>>&',`GtkExpression*',`(($3) ? ($3)->gobj() : nullptr)')
_CONVERSION(`GtkExpression*',`Glib::RefPtr<Expression<bool>>',`Glib::wrap<bool>($3)')
_CONVERSION(`GtkExpression*',`Glib::RefPtr<const Expression<bool>>',`Glib::wrap<bool>($3)')

# Dialogs
_CONVERSION(`const Glib::RefPtr<ColorDialog>&', `GtkColorDialog*', __CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkColorDialog*',`Glib::RefPtr<ColorDialog>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<FontDialog>&', `GtkFontDialog*', __CONVERT_REFPTR_TO_P)
_CONVERSION(`GtkFontDialog*',`Glib::RefPtr<FontDialog>',`Glib::wrap($3)')
