# NMake Makefile portion for compilation rules
# Items in here should not need to be edited unless
# one is maintaining the NMake build files.  The format
# of NMake Makefiles here are different from the GNU
# Makefiles.  Please see the comments about these formats.

# Inference rules for compiling the .obj files.
# Used for libs and programs with more than a single source file.
# Format is as follows
# (all dirs must have a trailing '\'):
#
# {$(srcdir)}.$(srcext){$(destdir)}.obj::
# 	$(CC)|$(CXX) $(cflags) /Fo$(destdir) /c @<<
# $<
# <<
{..\gdk\gdkmm\}.cc{$(CFG)\$(PLAT)\gdkmm\}.obj::
	$(CXX) $(LIBGDKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(CFG)\$(PLAT)\gdkmm\ /c @<<
$<
<<

{..\gtk\gtkmm\}.cc{$(CFG)\$(PLAT)\gtkmm\}.obj::
	$(CXX) $(LIBGTKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(CFG)\$(PLAT)\gtkmm\ /c @<<
$<
<<

{.\gtkmm\}.rc{$(CFG)\$(PLAT)\gtkmm\}.res:
	rc /fo$@ $<

{..\demos\gtk-demo\}.cc{$(CFG)\$(PLAT)\gtkmm4-demo\}.obj::
	$(CXX) $(GTKMM_DEMO_CFLAGS) $(CFLAGS) /Fo$(CFG)\$(PLAT)\gtkmm4-demo\ /c @<<
$<
<<

{$(CFG)\$(PLAT)\gtkmm4-demo\}.c{$(CFG)\$(PLAT)\gtkmm4-demo\}.obj::
	$(CC) $(GTKMM_DEMO_CFLAGS) $(CFLAGS) /Fo$(CFG)\$(PLAT)\gtkmm4-demo\ /c @<<
$<
<<

# Rules for building .lib files
$(GTKMM_LIB): $(GTKMM_DLL)

# Rules for linking DLLs
# Format is as follows (the mt command is needed for MSVC 2005/2008 builds):
# $(dll_name_with_path): $(dependent_libs_files_objects_and_items)
#	link /DLL [$(linker_flags)] [$(dependent_libs)] [/def:$(def_file_if_used)] [/implib:$(lib_name_if_needed)] -out:$@ @<<
# $(dependent_objects)
# <<
# 	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;2

$(GTKMM_DLL): $(CFG)\$(PLAT)\gtkmm\gtkmm.def $(gtkmm_OBJS) $(gdkmm_OBJS)
	link /DLL $(LDFLAGS_NOLTCG) $(GTKMM_DEP_LIBS) /implib:$(GTKMM_LIB) /def:$(CFG)\$(PLAT)\gtkmm\gtkmm.def -out:$@ @<<
$(gtkmm_OBJS) $(gdkmm_OBJS)
<<
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;2

# Rules for linking Executables
# Format is as follows (the mt command is needed for MSVC 2005/2008 builds):
# $(dll_name_with_path): $(dependent_libs_files_objects_and_items)
#	link [$(linker_flags)] [$(dependent_libs)] -out:$@ @<<
# $(dependent_objects)
# <<
# 	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;1

# For the gendef tool
{.\gendef\}.cc{$(CFG)\$(PLAT)\}.exe:
	@if not exist $(CFG)\$(PLAT)\gendef\ $(MAKE) -f Makefile.vc CFG=$(CFG) $(CFG)\$(PLAT)\gendef
	$(CXX) $(GTKMM_BASE_CFLAGS) $(CFLAGS) /Fo$(CFG)\$(PLAT)\gendef\ $< /link $(LDFLAGS) /out:$@
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;1

$(GTKMM4_DEMO): $(GTKMM_LIB) $(CFG)\$(PLAT)\gtkmm4-demo $(gtkmm_demo_OBJS)
	link $(LDFLAGS) $(GTKMM_LIB) $(GTKMM_DEMO_DEP_LIBS) -out:$@ @<<
$(gtkmm_demo_OBJS)
<<
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;1

$(CFG)\$(PLAT)\gtkmm4-test-builder.exe: ..\tests\builder\main.cc
$(CFG)\$(PLAT)\gtkmm4-test-child_widget.exe: ..\tests\child_widget\main.cc ..\tests\child_widget\testwindow.cc
$(CFG)\$(PLAT)\gtkmm4-test-child_widget2.exe: ..\tests\child_widget2\main.cc
$(CFG)\$(PLAT)\gtkmm4-test-child_widget_managed.exe: ..\tests\child_widget_managed\main.cc
$(CFG)\$(PLAT)\gtkmm4-test-delete_cpp_child.exe: ..\tests\delete_cpp_child\main.cc
$(CFG)\$(PLAT)\gtkmm4-test-dialog_deletethis.exe: ..\tests\dialog_deletethis\main.cc
$(CFG)\$(PLAT)\gtkmm4-test-main_with_options.exe: ..\tests\main_with_options\main.cc
$(CFG)\$(PLAT)\gtkmm4-test-menu_destruction.exe: ..\tests\menu_destruction\main.cc
$(CFG)\$(PLAT)\gtkmm4-test-object_move.exe: ..\tests\object_move\main.cc
$(CFG)\$(PLAT)\gtkmm4-test-property_notification.exe: ..\tests\property_notification\main.cc
$(CFG)\$(PLAT)\gtkmm4-test-refcount_dialog.exe: ..\tests\refcount_dialog\main.cc
$(CFG)\$(PLAT)\gtkmm4-test-scrolledwindow.exe: ..\tests\scrolledwindow\main.cc
$(CFG)\$(PLAT)\gtkmm4-test-tree_model_iterator.exe: ..\tests\tree_model_iterator\main.cc
$(CFG)\$(PLAT)\gtkmm4-test-wrap_existing.exe: ..\tests\wrap_existing\main.cc

$(CFG)\$(PLAT)\gtkmm4-test-builder.exe	\
$(CFG)\$(PLAT)\gtkmm4-test-child_widget.exe	\
$(CFG)\$(PLAT)\gtkmm4-test-child_widget2.exe	\
$(CFG)\$(PLAT)\gtkmm4-test-child_widget_managed.exe	\
$(CFG)\$(PLAT)\gtkmm4-test-delete_cpp_child.exe	\
$(CFG)\$(PLAT)\gtkmm4-test-dialog_deletethis.exe	\
$(CFG)\$(PLAT)\gtkmm4-test-main_with_options.exe	\
$(CFG)\$(PLAT)\gtkmm4-test-menu_destruction.exe	\
$(CFG)\$(PLAT)\gtkmm4-test-object_move.exe	\
$(CFG)\$(PLAT)\gtkmm4-test-property_notification.exe	\
$(CFG)\$(PLAT)\gtkmm4-test-refcount_dialog.exe	\
$(CFG)\$(PLAT)\gtkmm4-test-scrolledwindow.exe	\
$(CFG)\$(PLAT)\gtkmm4-test-tree_model_iterator.exe	\
$(CFG)\$(PLAT)\gtkmm4-test-wrap_existing.exe:
	@if not exist $(GTKMM_LIB) $(MAKE) /f Makefile.vc $(SAVED_OPTIONS) $(GTKMM_LIB)
	@if not exist $(CFG)\$(PLAT)\$(@B) $(MAKE) /f Makefile.vc $(SAVED_OPTIONS) $(CFG)\$(PLAT)\$(@B)
	$(CXX) $(GTKMM_DEMO_CFLAGS) $(CFLAGS) /Fo$(CFG)\$(PLAT)\$(@B)\ $**	\
	/link  $(LDFLAGS) $(GTKMM_LIB) $(GTKMM_DEMO_DEP_LIBS) -out:$@
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;1

clean:
	@-del /f /q $(CFG)\$(PLAT)\*.exe
	@-del /f /q $(CFG)\$(PLAT)\*.dll
	@-del /f /q $(CFG)\$(PLAT)\*.pdb
	@-del /f /q $(CFG)\$(PLAT)\*.ilk
	@-del /f /q $(CFG)\$(PLAT)\*.exp
	@-del /f /q $(CFG)\$(PLAT)\*.lib
	@-for /f %d in ('dir /ad /b $(CFG)\$(PLAT)\gtkmm4-test-*') do @del /f/q $(CFG)\$(PLAT)\%d\*.obj
	@-del /f /q $(CFG)\$(PLAT)\gtkmm4-demo\demo_resources.c
	@-del /f /q $(CFG)\$(PLAT)\gtkmm4-demo\*.obj
	@-del /f /q $(CFG)\$(PLAT)\gtkmm\*.def
	@-del /f /q $(CFG)\$(PLAT)\gtkmm\*.res
	@-del /f /q $(CFG)\$(PLAT)\gtkmm\*.obj
	@-del /f /q $(CFG)\$(PLAT)\gdkmm\*.obj
	@-del /f /q $(CFG)\$(PLAT)\gendef\*.obj
	@-for /f %d in ('dir /ad /b $(CFG)\$(PLAT)\gtkmm4-test-*') do @rd $(CFG)\$(PLAT)\%d
	@-rd $(CFG)\$(PLAT)\gtkmm4-demo
	@-rd $(CFG)\$(PLAT)\gtkmm
	@-rd $(CFG)\$(PLAT)\gdkmm
	@-rd $(CFG)\$(PLAT)\gendef
	@-del /f /q vc$(PDBVER)0.pdb
