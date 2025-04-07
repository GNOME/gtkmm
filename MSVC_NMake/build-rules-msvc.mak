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
{vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\}.obj::
	$(CXX) $(LIBGDKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\ /c @<<
$<
<<

{..\untracked\gdk\gdkmm\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\}.obj::
	@if not exist vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\ md vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm
	$(CXX) $(LIBGDKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\ /c @<<
$<
<<

{..\gdk\gdkmm\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\}.obj::
	@if not exist vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\ md vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm
	$(CXX) $(LIBGDKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\ /c @<<
$<
<<

{..\gdk\src\}.ccg{vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\}.obj:
	@if not exist $(@D)\private\ md $(@D)\private
	@for %%s in ($(<D)\*.ccg) do @if not exist ..\untracked\gdk\gdkmm\%%~ns.cc if not exist ..\gdk\gdkmm\%%~ns.cc if not exist $(@D)\%%~ns.cc $(PERL) -- $(GMMPROC_DIR)/gmmproc -I ../tools/m4 -I $(GMMPROC_PANGO_DIR) --defs $(<D:\=/) %%~ns $(<D:\=/) $(@D)
	@if exist $(@D)\$(<B).cc $(CXX) $(LIBGDKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c $(@D)\$(<B).cc
	@if exist ..\gdk\gdkmm\$(<B).cc $(CXX) $(LIBGDKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c ..\gdk\gdkmm\$(<B).cc
	@if exist ..\untracked\gdk\gdkmm\$(<B).cc $(CXX) $(LIBGDKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c ..\untracked\gdk\gdkmm\$(<B).cc

{vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\}.obj::
	$(CXX) $(LIBGSKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gskmm\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gskmm\ /c @<<
$<
<<

{..\untracked\gsk\gskmm\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\}.obj::
	@if not exist vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\ md vs$(VSVER)\$(CFG)\$(PLAT)\gskmm
	$(CXX) $(LIBGSKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gskmm\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gskmm\ /c @<<
$<
<<

{..\gsk\gskmm\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\}.obj::
	@if not exist vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\ md vs$(VSVER)\$(CFG)\$(PLAT)\gskmm
	$(CXX) $(LIBGSKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gskmm\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gskmm\ /c @<<
$<
<<

{..\gsk\src\}.ccg{vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\}.obj:
	@if not exist $(@D)\private\ md $(@D)\private
	@for %%s in ($(<D)\*.ccg) do @if not exist ..\untracked\gsk\gskmm\%%~ns.cc if not exist ..\gsk\gskmm\%%~ns.cc if not exist $(@D)\%%~ns.cc $(PERL) -- $(GMMPROC_DIR)/gmmproc -I ../tools/m4 -I $(GMMPROC_PANGO_DIR) --defs $(<D:\=/) %%~ns $(<D:\=/) $(@D)
	@if exist $(@D)\$(<B).cc $(CXX) $(LIBGSKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c $(@D)\$(<B).cc
	@if exist ..\gsk\gskmm\$(<B).cc $(CXX) $(LIBGSKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c ..\gsk\gskmm\$(<B).cc
	@if exist ..\untracked\gsk\gskmm\$(<B).cc $(CXX) $(LIBGSKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c ..\untracked\gsk\gskmm\$(<B).cc

{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\}.obj::
	$(CXX) $(LIBGTKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\ /c @<<
$<
<<

{..\gtk\gtkmm\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\}.obj::
	@if not exist vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\ md vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm
	$(CXX) $(LIBGTKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\ /c @<<
$<
<<

{..\untracked\gtk\gtkmm\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\}.obj::
	@if not exist vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\ md vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm
	$(CXX) $(LIBGTKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\ /c @<<
$<
<<

{..\gtk\src\}.ccg{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\}.obj:
	@if not exist $(@D)\private\ md $(@D)\private
	@for %%s in ($(<D)\*.ccg) do @if not exist ..\untracked\gtk\gtkmm\%%~ns.cc if not exist ..\gtk\gtkmm\%%~ns.cc if not exist $(@D)\%%~ns.cc $(PERL) -- $(GMMPROC_DIR)/gmmproc -I ../tools/m4 -I $(GMMPROC_PANGO_DIR) --defs $(<D:\=/) %%~ns $(<D:\=/) $(@D)
	@if exist $(@D)\$(<B).cc $(CXX) $(LIBGTKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c $(@D)\$(<B).cc
	@if exist ..\gtk\gtkmm\$(<B).cc $(CXX) $(LIBGTKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c ..\gtk\gtkmm\$(<B).cc
	@if exist ..\untracked\gtk\gtkmm\$(<B).cc $(CXX) $(LIBGTKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c ..\untracked\gtk\gtkmm\$(<B).cc

{.\gtkmm\}.rc{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\}.res:
	@if not exist $(@D)\ md $(@D)
	rc /fo$@ $<

{..\demos\gtk-demo\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo\}.obj::
	@if not exist vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo\ md vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo
	$(CXX) $(GTKMM_DEMO_CFLAGS) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo\ /c @<<
$<
<<

{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo\}.c{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo\}.obj::
	$(CC) $(GTKMM_DEMO_CFLAGS) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo\ /c @<<
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

$(GTKMM_DLL): $(gdkmm_OBJS) $(gskmm_OBJS) $(gtkmm_OBJS)
	link /DLL $(LDFLAGS_NOLTCG) $(GTKMM_DEP_LIBS) /implib:$(GTKMM_LIB) -out:$@ @<<
$(gdkmm_OBJS) $(gskmm_OBJS) $(gtkmm_OBJS)
<<
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;2

# Rules for linking Executables
# Format is as follows (the mt command is needed for MSVC 2005/2008 builds):
# $(dll_name_with_path): $(dependent_libs_files_objects_and_items)
#	link [$(linker_flags)] [$(dependent_libs)] -out:$@ @<<
# $(dependent_objects)
# <<
# 	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;1

$(GTKMM4_DEMO): $(GTKMM_LIB) vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo $(gtkmm_demo_OBJS)
	link $(GTKMM_DEMO_LDFLAGS) $(GTKMM_LIB) $(GTKMM_DEMO_DEP_LIBS) -out:$@ @<<
$(gtkmm_demo_OBJS)
<<
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;1

clean:
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\*.exe
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\*.dll
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\*.pdb
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\*.ilk
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\*.exp
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\*.lib
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm-tests\*.pdb
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm-tests\*.obj
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo\demo_resources.c
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo\*.pdb
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo\*.obj
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\private\*.h
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\*.res
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\*.pdb
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\*.obj
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\*.cc
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\*.h
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\private\*.h
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\*.pdb
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\*.obj
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\*.cc
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\*.h
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\private\*.h
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\*.pdb
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\*.obj
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\*.cc
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\*.h
	@-rd vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm-tests
	@-rd vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo
	@-rd vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\private
	@-rd vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm
	@-rd vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\private
	@-rd vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm

.SUFFIXES: .cc .h .ccg .hg .obj
