# Convert the source listing to object (.obj) listing in
# another NMake Makefile module, include it, and clean it up.
# This is a "fact-of-life" regarding NMake Makefiles...
# This file does not need to be changed unless one is maintaining the NMake Makefiles

# For those wanting to add things here:
# To add a list, do the following:
# # $(description_of_list)
# if [call create-lists.bat header $(makefile_snippet_file) $(variable_name)]
# endif
#
# if [call create-lists.bat file $(makefile_snippet_file) $(file_name)]
# endif
#
# if [call create-lists.bat footer $(makefile_snippet_file)]
# endif
# ... (repeat the if [call ...] lines in the above order if needed)
# !include $(makefile_snippet_file)
#
# (add the following after checking the entries in $(makefile_snippet_file) is correct)
# (the batch script appends to $(makefile_snippet_file), you will need to clear the file unless the following line is added)
#!if [del /f /q $(makefile_snippet_file)]
#!endif

# In order to obtain the .obj filename that is needed for NMake Makefiles to build DLLs/static LIBs or EXEs, do the following
# instead when doing 'if [call create-lists.bat file $(makefile_snippet_file) $(file_name)]'
# (repeat if there are multiple $(srcext)'s in $(source_list), ignore any headers):
# !if [for %c in ($(source_list)) do @if "%~xc" == ".$(srcext)" @call create-lists.bat file $(makefile_snippet_file) $(intdir)\%~nc.obj]
#
# $(intdir)\%~nc.obj needs to correspond to the rules added in build-rules-msvc.mak
# %~xc gives the file extension of a given file, %c in this case, so if %c is a.cc, %~xc means .cc
# %~nc gives the file name of a given file without extension, %c in this case, so if %c is a.cc, %~nc means a

NULL=

gdkmm_generated_private_headers = $(files_hg:.hg=_p.h)

# For gdkmm

!if [call create-lists.bat header $(BUILD_MKFILE_SNIPPET) gdkmm_OBJS]
!endif

!if [for %c in ($(GDKMM_INT_GENERATED_SOURCES)) do @if "%~xc" == ".cc" @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) ^$(OUTDIR)\gdkmm\%~nc.obj]
!endif

!if [for %c in ($(gdkmm_files_extra_cc)) do @if "%~xc" == ".cc" @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) ^$(OUTDIR)\gdkmm\%~nc.obj]
!endif

!if [call create-lists.bat footer $(BUILD_MKFILE_SNIPPET)]
!endif

!if [call create-lists.bat header $(BUILD_MKFILE_SNIPPET) gdkmm_real_hg]
!endif

!if [for %c in ($(gdkmm_files_any_hg)) do @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) ..\gdk\src\%c]
!endif

!if [call create-lists.bat footer $(BUILD_MKFILE_SNIPPET)]
!endif

# gskmm

!if [call create-lists.bat header $(BUILD_MKFILE_SNIPPET) gskmm_OBJS]
!endif

!if [for %c in ($(GSKMM_INT_GENERATED_SOURCES)) do @if "%~xc" == ".cc" @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) ^$(OUTDIR)\gskmm\%~nc.obj]
!endif

!if [for %c in ($(gskmm_files_extra_cc)) do @if "%~xc" == ".cc" @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) ^$(OUTDIR)\gskmm\%~nc.obj]
!endif

!if [call create-lists.bat footer $(BUILD_MKFILE_SNIPPET)]
!endif

!if [call create-lists.bat header $(BUILD_MKFILE_SNIPPET) gskmm_real_hg]
!endif

!if [for %c in ($(gskmm_files_any_hg)) do @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) ..\gsk\src\%c]
!endif

!if [call create-lists.bat footer $(BUILD_MKFILE_SNIPPET)]
!endif

# For gtkmm
!if [call create-lists.bat header $(BUILD_MKFILE_SNIPPET) gtkmm_OBJS]
!endif

!if [for %c in ($(GTKMM_INT_GENERATED_SOURCES:.cc=)) do @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) ^$(OUTDIR)\gtkmm\%~nc.obj]
!endif

!if [for %c in ($(GTKMM_INT_EXTRA_SOURCES)) do @if "%~xc" == ".cc" @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) ^$(OUTDIR)\gtkmm\%~nc.obj]
!endif

!if [@call create-lists.bat file $(BUILD_MKFILE_SNIPPET) ^$(OUTDIR)\gtkmm\gtkmm.res]
!endif

!if [call create-lists.bat footer $(BUILD_MKFILE_SNIPPET)]
!endif

!if [call create-lists.bat header $(BUILD_MKFILE_SNIPPET) gtkmm_real_hg]
!endif

!if [for %c in ($(gtkmm_files_any_hg:.hg=)) do @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) ..\gtk\src\%c.hg]
!endif

!if [call create-lists.bat footer $(BUILD_MKFILE_SNIPPET)]
!endif

# For gtkmm demos
!if [call create-lists.bat header $(BUILD_MKFILE_SNIPPET) gtkmm_demo_OBJS]
!endif

!if [for %s in (..\demos\gtk-demo\*.cc) do @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) ^$(OUTDIR)\gtkmm4-demo\%~ns.obj]
!endif

!if [@call create-lists.bat file $(BUILD_MKFILE_SNIPPET) ^$(OUTDIR)\gtkmm4-demo\demo_resources.obj]
!endif

!if [call create-lists.bat footer $(BUILD_MKFILE_SNIPPET)]
!endif

!if [call create-lists.bat header $(BUILD_MKFILE_SNIPPET) gtkmm_demo_example_sources]
!endif

!if [for %s in (..\demos\gtk-demo\example_*.cc) do @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) %s]
!endif

!if [call create-lists.bat footer $(BUILD_MKFILE_SNIPPET)]
!endif

!if [call create-lists.bat header $(BUILD_MKFILE_SNIPPET) gtkmm_demo_resources]
!endif

!if [for %x in (gif jpg png webm ui glsl) do @for %s in (..\demos\gtk-demo\*.%x) do @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) %s]
!endif

!if [call create-lists.bat footer $(BUILD_MKFILE_SNIPPET)]
!endif

!if [call create-lists.bat header $(BUILD_MKFILE_SNIPPET) gtkmm_tests]
!endif

!if [for /f %d in ('dir /ad /b ..\tests\') do @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) ^$(OUTDIR)\gtkmm4-test-%d.exe]
!endif

!if [call create-lists.bat footer $(BUILD_MKFILE_SNIPPET)]
!endif

!if [call create-lists.bat header $(BUILD_MKFILE_SNIPPET) gtkmm_tests & @(for /f %t in ('dir /ad /b ..\tests') do @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) vs$(VSVER)\$(CFG)\$(PLAT)\%t.exe) & @call create-lists.bat footer $(BUILD_MKFILE_SNIPPET)]
!endif

!if [for /f %t in ('dir /ad /b ..\tests') do @for %s in (..\tests\%t\*.cc) do @echo ^$(OUTDIR)\gtkmm-tests\%t-%~ns.obj: %s>>$(BUILD_MKFILE_SNIPPET) & @echo. if not exist ^$(@D)\ md ^$(@D)>>$(BUILD_MKFILE_SNIPPET) & @echo.	^$(CXX) ^$(GTKMM_DEMO_CFLAGS) ^$(LIBGTKMM_INCLUDES) /Fo^$(@D)\%t-%~ns.obj /Fd^$(@D)\ ^$** /c>>$(BUILD_MKFILE_SNIPPET) & @echo.>>$(BUILD_MKFILE_SNIPPET)]
!endif

!if [for /f %t in ('dir /ad /b ..\tests\') do @call create-lists.bat header $(BUILD_MKFILE_SNIPPET) %t_OBJS & @(for %s in (..\tests\%t\*.cc) do @call create-lists.bat file $(BUILD_MKFILE_SNIPPET) vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm-tests\%t-%~ns.obj) & @call create-lists.bat footer $(BUILD_MKFILE_SNIPPET)]
!endif
!if [for /f %t in ('dir /ad /b ..\tests') do @echo ^$(OUTDIR)\%t.exe: ^$(GTKMM_LIB) ^$(GDKMM_LIB) ^$(%t_OBJS)>>$(BUILD_MKFILE_SNIPPET) & @echo.	link ^$(LDFLAGS) ^$** ^$(DEP_LDFLAGS) ^$(SIGC_LIB) /out:^$@>>$(BUILD_MKFILE_SNIPPET) & @echo.>>$(BUILD_MKFILE_SNIPPET)]

!endif

!include $(BUILD_MKFILE_SNIPPET)

!if [del /f /q $(BUILD_MKFILE_SNIPPET)]
!endif
