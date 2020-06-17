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

{..\gdk\gdkmm\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\}.obj::
	$(CXX) $(LIBGDKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\ /c @<<
$<
<<

{..\untracked\gdk\gdkmm\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\}.obj::
	$(CXX) $(LIBGDKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\ /c @<<
$<
<<

{..\gdk\src\}.ccg{vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\}.obj:
	@if not exist $(@D)\private\ md $(@D)\private
	@for %%s in ($(<D)\*.ccg) do @if not exist ..\untracked\gdk\gdkmm\%%~ns.cc if not exist ..\gdk\gdkmm\%%~ns.cc if not exist $(@D)\%%~ns.cc $(PERL) -- $(GMMPROC_DIR)/gmmproc -I ../tools/m4 -I $(GMMPROC_PANGO_DIR) -I $(GMMPROC_ATK_DIR) --defs $(<D:\=/) %%~ns $(<D:\=/) $(@D)
	@if exist $(@D)\$(<B).cc $(CXX) $(LIBGDKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c $(@D)\$(<B).cc
	@if exist ..\untracked\gdk\gdkmm\$(<B).cc if not exist ..\gdk\gdkmm\$(<B).cc if not exist $(@D)\$(<B).cc $(CXX) $(LIBGDKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c ..\gdk\gdkmm\$(<B).cc
	@if exist ..\gdk\gdkmm\$(<B).cc if not exist ..\untracked\gdk\gdkmm\$(<B).cc if not exist $(@D)\$(<B).cc $(CXX) $(LIBGDKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c ..\gdk\gdkmm\$(<B).cc

{.\gdkmm\}.rc{vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\}.res:
	rc /fo$@ $<

{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\}.obj::
	$(CXX) $(LIBGTKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\ /c @<<
$<
<<

{..\gtk\gtkmm\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\}.obj::
	$(CXX) $(LIBGTKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\ /c @<<
$<
<<

{..\untracked\gtk\gtkmm\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\}.obj::
	$(CXX) $(LIBGTKMM_CFLAGS) $(CFLAGS_NOGL) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\ /c @<<
$<
<<

{..\gtk\src\}.ccg{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\}.obj:
	@if not exist $(@D)\private\ md $(@D)\private
	@for %%s in ($(<D)\*.ccg) do @if not exist ..\gtk\gtkmm\%%~ns.cc if not exist ..\untracked\gtk\gtkmm\%%~ns.cc if not exist $(@D)\%%~ns.cc $(PERL) -- $(GMMPROC_DIR)/gmmproc -I ../tools/m4 -I $(GMMPROC_PANGO_DIR) -I $(GMMPROC_ATK_DIR) --defs $(<D:\=/) %%~ns $(<D:\=/) $(@D)
	@if exist $(@D)\$(<B).cc $(CXX) $(LIBGTKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c $(@D)\$(<B).cc
	@if exist ..\untracked\gtk\gtkmm\$(<B).cc if not exist ..\gtk\gtkmm\$(<B).cc if not exist $(@D)\$(<B).cc $(CXX) $(LIBGTKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c ..\gtk\gtkmm\$(<B).cc
	@if exist ..\gtk\gtkmm\$(<B).cc if not exist ..\untracked\gtk\gtkmm\$(<B).cc if not exist $(@D)\$(<B).cc $(CXX) $(LIBGTKMM_CFLAGS) $(CFLAGS_NOGL) /Fo$(@D)\ /Fd$(@D)\ /c ..\gtk\gtkmm\$(<B).cc

{.\gtkmm\}.rc{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\}.res:
	rc /fo$@ $<

{..\demos\gtk-demo\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm3-demo\}.obj::
	$(CXX) $(GTKMM_DEMO_CFLAGS) $(CFLAGS) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gtkmm3-demo\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gtkmm3-demo\ /c @<<
$<
<<

{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm3-demo\}.c{vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm3-demo\}.obj::
	$(CC) $(GTKMM_DEMO_CFLAGS) $(CFLAGS) /Fovs$(VSVER)\$(CFG)\$(PLAT)\gtkmm3-demo\ /Fdvs$(VSVER)\$(CFG)\$(PLAT)\gtkmm3-demo\ /c @<<
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
$(GDKMM_DLL): $(GDKMM_INT_TARGET) $(gdkmm_OBJS)
	link /DLL $(LDFLAGS_NOLTCG) $(GDKMM_DEP_LIBS) /implib:$(GDKMM_LIB) $(GDKMM_DEF_LDFLAG) -out:$@ @<<
$(gdkmm_OBJS)
<<
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;2

$(GTKMM_DLL): $(GDKMM_LIB) $(GTKMM_INT_TARGET) $(gtkmm_OBJS)
	link /DLL $(LDFLAGS_NOLTCG) $(GDKMM_LIB) $(GTKMM_DEP_LIBS) /implib:$(GTKMM_LIB) $(GTKMM_DEF_LDFLAG) -out:$@ @<<
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
{.\gendef\}.cc{vs$(VSVER)\$(CFG)\$(PLAT)\}.exe:
	@if not exist vs$(VSVER)\$(CFG)\$(PLAT)\gendef\ md vs$(VSVER)\$(CFG)\$(PLAT)\$(@B)
	$(CXX) $(GTKMM_BASE_CFLAGS) $(CFLAGS) /Fo$(@D)\gendef\ /Fd$(@D)\gendef\ $< /link $(LDFLAGS) /out:$@
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;1

$(GTKMM3_DEMO): $(GTKMM_LIB) vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm3-demo $(gtkmm_demo_OBJS)
	link $(LDFLAGS) $(GTKMM_LIB) $(GDKMM_LIB) $(GTKMM_DEMO_DEP_LIBS) -out:$@ @<<
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
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm3-demo\demo_resources.c
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm3-demo\*.pdb
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm3-demo\*.obj
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\private\*.h
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\*.def
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\*.res
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\*.pdb
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\*.obj
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\*.h
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\*.cc
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\private\*.h
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\*.def
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\*.res
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\*.pdb
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\*.obj
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\*.cc
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\*.h
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gendef\*.pdb
	@-del /f /q vs$(VSVER)\$(CFG)\$(PLAT)\gendef\*.obj
	@-rd vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm-tests
	@-rd vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm3-demo
	@-rd vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\private
	@-rd vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm
	@-rd vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\private
	@-rd vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm
	@-rd vs$(VSVER)\$(CFG)\$(PLAT)\gendef

.SUFFIXES: .cc .ccg .h .hg .obj
