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
{$(OUTDIR)\gdkmm\}.cc{$(OUTDIR)\gdkmm\}.obj::
	$(CXX) $(CFLAGS) $(LIBGDKMM_CXXFLAGS) $(LIBGDKMM_INCLUDES) /Fo$(OUTDIR)\gdkmm\ /Fd$(OUTDIR)\gdkmm\ /c @<<
$<
<<

{..\gdk\gdkmm\}.cc{$(OUTDIR)\gdkmm\}.obj::
	@if not exist $(OUTDIR)\gdkmm\ md $(OUTDIR)\gdkmm
	$(CXX) $(CFLAGS) $(LIBGDKMM_CXXFLAGS) $(LIBGDKMM_INCLUDES) /Fo$(OUTDIR)\gdkmm\ /Fd$(OUTDIR)\gdkmm\ /c @<<
$<
<<

{..\untracked\gdk\gdkmm\}.cc{$(OUTDIR)\gdkmm\}.obj::
	@if not exist $(OUTDIR)\gdkmm\ md $(OUTDIR)\gdkmm
	$(CXX) $(CFLAGS) $(LIBGDKMM_CXXFLAGS) $(LIBGDKMM_INCLUDES) /Fo$(OUTDIR)\gdkmm\ /Fd$(OUTDIR)\gdkmm\ /c @<<
$<
<<

{..\gdk\src\}.ccg{$(OUTDIR)\gdkmm\}.obj:
	@if not exist $(@D)\private\ md $(@D)\private
	@if not exist gdkmm\gdkmmconfig.h $(MAKE) /f Makefile.vc CFG=$(CFG) prep-git-build
	@if "$(UNIX_TOOLS_BINDIR_CHECKED)" == "" echo Warning: m4 is not in %PATH% or specified M4 or UNIX_TOOLS_BINDIR is not valid. Builds may fail!
	@set PATH=$(PATH);$(UNIX_TOOLS_BINDIR_CHECKED)
	@for %%s in ($(<D)\*.ccg) do @if not exist ..\untracked\gdk\gdkmm\%%~ns.cc if not exist ..\gdk\gdkmm\%%~ns.cc if not exist $(@D)\%%~ns.cc $(PERL) -- $(GMMPROC_DIR)/gmmproc -I ../tools/m4 -I $(GMMPROC_PANGO_DIR) -I $(GMMPROC_ATK_DIR) --defs $(<D:\=/) %%~ns $(<D:\=/) $(@D)
	@if exist $(@D)\$(<B).cc $(CXX) $(CFLAGS) $(LIBGDKMM_CXXFLAGS) $(LIBGDKMM_INCLUDES) /Fo$(@D)\ /Fd$(@D)\ /c $(@D)\$(<B).cc
	@if exist ..\gdk\gdkmm\$(<B).cc $(CXX) $(CFLAGS) $(LIBGDKMM_CXXFLAGS) $(LIBGDKMM_INCLUDES) /Fo$(@D)\ /Fd$(@D)\ /c ..\gdk\gdkmm\$(<B).cc
	@if exist ..\untracked\gdk\gdkmm\$(<B).cc $(CXX) $(CFLAGS) $(LIBGDKMM_CXXFLAGS) $(LIBGDKMM_INCLUDES) /Fo$(@D)\ /Fd$(@D)\ /c ..\untracked\gdk\gdkmm\$(<B).cc

{.\gdkmm\}.rc{$(OUTDIR)\gdkmm\}.res:
	rc /fo$@ $<

{$(OUTDIR)\gtkmm\}.cc{$(OUTDIR)\gtkmm\}.obj::
	$(CXX) $(CFLAGS) $(LIBGTKMM_CXXFLAGS) $(LIBGTKMM_INCLUDES) /Fo$(OUTDIR)\gtkmm\ /Fd$(OUTDIR)\gtkmm\ /c @<<
$<
<<

{..\gtk\gtkmm\}.cc{$(OUTDIR)\gtkmm\}.obj::
	@if not exist $(OUTDIR)\gtkmm\ md $(OUTDIR)\gtkmm
	$(CXX) $(CFLAGS) $(LIBGTKMM_CXXFLAGS) $(LIBGTKMM_INCLUDES) /Fo$(OUTDIR)\gtkmm\ /Fd$(OUTDIR)\gtkmm\ /c @<<
$<
<<

{..\untracked\gtk\gtkmm\}.cc{$(OUTDIR)\gtkmm\}.obj::
	@if not exist $(OUTDIR)\gtkmm\ md $(OUTDIR)\gtkmm
	$(CXX) $(CFLAGS) $(LIBGTKMM_CXXFLAGS) $(LIBGTKMM_INCLUDES) /Fo$(OUTDIR)\gtkmm\ /Fd$(OUTDIR)\gtkmm\ /c @<<
$<
<<

{..\gtk\src\}.ccg{$(OUTDIR)\gtkmm\}.obj:
	@if not exist $(@D)\private\ md $(@D)\private
	@if not exist gtkmm\gtkmmconfig.h $(MAKE) /f Makefile.vc CFG=$(CFG) prep-git-build
	@if "$(UNIX_TOOLS_BINDIR_CHECKED)" == "" echo Warning: m4 is not in %PATH% or specified M4 or UNIX_TOOLS_BINDIR is not valid. Builds may fail!
	@set PATH=$(PATH);$(UNIX_TOOLS_BINDIR_CHECKED)
	@for %%s in ($(<D)\*.ccg) do @if not exist ..\gtk\gtkmm\%%~ns.cc if not exist ..\untracked\gtk\gtkmm\%%~ns.cc if not exist $(@D)\%%~ns.cc $(PERL) -- $(GMMPROC_DIR)/gmmproc -I ../tools/m4 -I $(GMMPROC_PANGO_DIR) -I $(GMMPROC_ATK_DIR) --defs $(<D:\=/) %%~ns $(<D:\=/) $(@D)
	@if exist $(@D)\$(<B).cc $(CXX) $(CFLAGS) $(LIBGTKMM_CXXFLAGS) $(LIBGTKMM_INCLUDES) /Fo$(@D)\ /Fd$(@D)\ /c $(@D)\$(<B).cc
	@if exist ..\untracked\gtk\gtkmm\$(<B).cc $(CXX) $(CFLAGS) $(LIBGTKMM_CXXFLAGS) $(LIBGTKMM_INCLUDES) /Fo$(@D)\ /Fd$(@D)\ /c ..\untracked\gtk\gtkmm\$(<B).cc
	@if exist ..\gtk\gtkmm\$(<B).cc $(CXX) $(CFLAGS) $(LIBGTKMM_CXXFLAGS) $(LIBGTKMM_INCLUDES) /Fo$(@D)\ /Fd$(@D)\ /c ..\gtk\gtkmm\$(<B).cc

{.\gtkmm\}.rc{$(OUTDIR)\gtkmm\}.res:
	@if not exist $(@D)\ md $(@D)
	rc /fo$@ $<

{..\demos\gtk-demo\}.cc{$(OUTDIR)\gtkmm3-demo\}.obj::
	@if not exist $(OUTDIR)\gtkmm3-demo\ md $(OUTDIR)\gtkmm3-demo
	$(CXX) $(GTKMM_DEMO_CFLAGS) $(LIBGTKMM_INCLUDES) /Fo$(OUTDIR)\gtkmm3-demo\ /Fd$(OUTDIR)\gtkmm3-demo\ /c @<<
$<
<<

{$(OUTDIR)\gtkmm3-demo\}.c{$(OUTDIR)\gtkmm3-demo\}.obj::
	$(CC) $(GTKMM_DEMO_CFLAGS) $(LIBGTKMM_INCLUDES) /Fo$(OUTDIR)\gtkmm3-demo\ /Fd$(OUTDIR)\gtkmm3-demo\ /c @<<
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
	link /DLL $(LDFLAGS) $(DEP_LDFLAGS) /implib:$(GDKMM_LIB) $(GDKMM_DEF_LDFLAG) -out:$@ @<<
$(gdkmm_OBJS)
<<
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;2

$(GTKMM_DLL): $(GDKMM_LIB) $(GTKMM_INT_TARGET) $(gtkmm_OBJS)
	link /DLL $(LDFLAGS) $(GDKMM_LIB) $(DEP_LDFLAGS) /implib:$(GTKMM_LIB) $(GTKMM_DEF_LDFLAG) -out:$@ @<<
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
{.\gendef\}.cc{$(OUTDIR)\}.exe:
	@if not exist $(OUTDIR)\gendef\ md $(OUTDIR)\$(@B)
	$(CXX) $(CFLAGS) /Fo$(@D)\gendef\ /Fd$(@D)\gendef\ $< /link $(LDFLAGS) /out:$@
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;1

$(GTKMM3_DEMO): $(GTKMM_LIB) $(OUTDIR)\gtkmm3-demo $(gtkmm_demo_OBJS)
	link $(GTKMM_DEMO_LDFLAGS) $(GTKMM_LIB) $(GDKMM_LIB) $(DEP_LDFLAGS) -out:$@ @<<
$(gtkmm_demo_OBJS)
<<
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;1

clean:
	@-del /f /q $(OUTDIR)\*.exe
	@-del /f /q $(OUTDIR)\*.dll
	@-del /f /q $(OUTDIR)\*.pdb
	@-del /f /q $(OUTDIR)\*.ilk
	@-del /f /q $(OUTDIR)\*.exp
	@-del /f /q $(OUTDIR)\*.lib
	@-del /f /q $(OUTDIR)\gtkmm-tests\*.pdb
	@-del /f /q $(OUTDIR)\gtkmm-tests\*.obj
	@-del /f /q $(OUTDIR)\gtkmm3-demo\demo_resources.c
	@-del /f /q $(OUTDIR)\gtkmm3-demo\*.pdb
	@-del /f /q $(OUTDIR)\gtkmm3-demo\*.obj
	@-del /f /q $(OUTDIR)\gtkmm\private\*.h
	@-del /f /q $(OUTDIR)\gtkmm\*.def
	@-del /f /q $(OUTDIR)\gtkmm\*.res
	@-del /f /q $(OUTDIR)\gtkmm\*.pdb
	@-del /f /q $(OUTDIR)\gtkmm\*.obj
	@-del /f /q $(OUTDIR)\gtkmm\*.h
	@-del /f /q $(OUTDIR)\gtkmm\*.cc
	@-del /f /q $(OUTDIR)\gdkmm\private\*.h
	@-del /f /q $(OUTDIR)\gdkmm\*.def
	@-del /f /q $(OUTDIR)\gdkmm\*.res
	@-del /f /q $(OUTDIR)\gdkmm\*.pdb
	@-del /f /q $(OUTDIR)\gdkmm\*.obj
	@-del /f /q $(OUTDIR)\gdkmm\*.cc
	@-del /f /q $(OUTDIR)\gdkmm\*.h
	@-del /f /q $(OUTDIR)\gendef\*.pdb
	@-del /f /q $(OUTDIR)\gendef\*.obj
	@-rd $(OUTDIR)\gtkmm-tests
	@-rd $(OUTDIR)\gtkmm3-demo
	@-rd $(OUTDIR)\gtkmm\private
	@-rd $(OUTDIR)\gtkmm
	@-rd $(OUTDIR)\gdkmm\private
	@-rd $(OUTDIR)\gdkmm
	@-rd $(OUTDIR)\gendef

.SUFFIXES: .cc .ccg .h .hg .obj
