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
{..\gdk\gdkmm\}.cc{vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\}.obj::
	$(CXX) $(LIBGDKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\ /c @<<
$<
<<

{.\gdkmm\}.rc{vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\}.res:
	rc /fo$@ $<

{..\gtk\gtkmm\}.cc{vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\}.obj::
	$(CXX) $(LIBGTKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\ /c @<<
$<
<<

{.\gtkmm\}.rc{vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\}.res:
	rc /fo$@ $<

{..\demos\gtk-demo\}.cc{vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo\}.obj::
	$(CXX) $(GTKMM_DEMO_CFLAGS) $(CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo\ /c @<<
$<
<<

{vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo\}.c{vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo\}.obj::
	$(CC) $(GTKMM_DEMO_CFLAGS) $(CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo\ /c @<<
$<
<<

# Rules for building .lib files
$(GDKMM_LIB): $(GDKMM_DLL)
$(GTKMM_LIB): $(GTKMM_DLL)

# Rules for linking DLLs
# Format is as follows (the mt command is needed for MSVC 2005/2008 builds):
# $(dll_name_with_path): $(dependent_libs_files_objects_and_items)
#	link /DLL [$(linker_flags)] [$(dependent_libs)] [/def:$(def_file_if_used)] [/implib:$(lib_name_if_needed)] -out:$@ @<<
# $(dependent_objects)
# <<
# 	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;2
$(GDKMM_DLL): vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\gdkmm.def $(gdkmm_OBJS)
	link /DLL $(LDFLAGS_NOLTCG) $(GDKMM_DEP_LIBS) /implib:$(GDKMM_LIB) /def:vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\gdkmm.def -out:$@ @<<
$(gdkmm_OBJS)
<<
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;2

$(GTKMM_DLL): $(GDKMM_LIB) vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\gtkmm.def $(gtkmm_OBJS)
	link /DLL $(LDFLAGS_NOLTCG) $(GDKMM_LIB) $(GTKMM_DEP_LIBS) /implib:$(GTKMM_LIB) /def:vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\gtkmm.def -out:$@ @<<
$(gtkmm_OBJS)
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
{.\gendef\}.cc{vs$(PDBVER)\$(CFG)\$(PLAT)\}.exe:
	@if not exist vs$(PDBVER)\$(CFG)\$(PLAT)\gendef\ $(MAKE) -f Makefile.vc CFG=$(CFG) vs$(PDBVER)\$(CFG)\$(PLAT)\gendef
	$(CXX) $(GTKMM_BASE_CFLAGS) $(CFLAGS) /Fo$(@D)\gendef\ /Fd$(@D)\gendef\ $< /link $(LDFLAGS) /out:$@
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;1

$(GTKMM3_DEMO): $(GTKMM_LIB) vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo $(gtkmm_demo_OBJS)
	link $(LDFLAGS) $(GTKMM_LIB) $(GDKMM_LIB) $(GTKMM_DEMO_DEP_LIBS) -out:$@ @<<
$(gtkmm_demo_OBJS)
<<
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;1

vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-builder.exe: ..\tests\builder\main.cc
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-child_widget.exe: ..\tests\child_widget\main.cc ..\tests\child_widget\testwindow.cc
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-child_widget2.exe: ..\tests\child_widget2\main.cc
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-child_widget_managed.exe: ..\tests\child_widget_managed\main.cc
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-delete_cpp_child.exe: ..\tests\delete_cpp_child\main.cc
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-dialog_deletethis.exe: ..\tests\dialog_deletethis\main.cc
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-main_with_options.exe: ..\tests\main_with_options\main.cc
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-menu_destruction.exe: ..\tests\menu_destruction\main.cc
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-object_move.exe: ..\tests\object_move\main.cc
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-property_notification.exe: ..\tests\property_notification\main.cc
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-refcount_dialog.exe: ..\tests\refcount_dialog\main.cc
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-scrolledwindow.exe: ..\tests\scrolledwindow\main.cc
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-tree_model_iterator.exe: ..\tests\tree_model_iterator\main.cc
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-wrap_existing.exe: ..\tests\wrap_existing\main.cc

vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-builder.exe	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-child_widget.exe	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-child_widget2.exe	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-child_widget_managed.exe	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-delete_cpp_child.exe	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-dialog_deletethis.exe	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-main_with_options.exe	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-menu_destruction.exe	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-object_move.exe	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-property_notification.exe	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-refcount_dialog.exe	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-scrolledwindow.exe	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-tree_model_iterator.exe	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-wrap_existing.exe:
	@if not exist $(GTKMM_LIB) $(MAKE) /f Makefile.vc $(SAVED_OPTIONS) $(GTKMM_LIB)
	@if not exist vs$(PDBVER)\$(CFG)\$(PLAT)\$(@B) $(MAKE) /f Makefile.vc $(SAVED_OPTIONS) vs$(PDBVER)\$(CFG)\$(PLAT)\$(@B)
	$(CXX) $(GTKMM_DEMO_CFLAGS) $(CFLAGS) /Fo$(@D)\$(@B)\ /Fd$(@D)\$(@B)\ $**	\
	/link  $(LDFLAGS) $(GTKMM_LIB) $(GDKMM_LIB) $(GTKMM_DEMO_DEP_LIBS) -out:$@
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;1

clean:
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\*.exe
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\*.dll
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\*.pdb
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\*.ilk
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\*.exp
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\*.lib
	@-for /f %d in ('dir /ad /b vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-*') do @(for %x in (obj pdb) do @del /f/q vs$(PDBVER)\$(CFG)\$(PLAT)\%d\*.%x)
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo\demo_resources.c
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo\*.pdb
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo\*.obj
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\*.def
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\*.res
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\*.pdb
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\*.obj
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\*.def
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\*.res
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\*.pdb
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\*.obj
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\gendef\*.pdb
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\gendef\*.obj
	@-for /f %d in ('dir /ad /b vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-*') do @rd vs$(PDBVER)\$(CFG)\$(PLAT)\%d
	@-rd vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo
	@-rd vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm
	@-rd vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm
	@-rd vs$(PDBVER)\$(CFG)\$(PLAT)\gendef
