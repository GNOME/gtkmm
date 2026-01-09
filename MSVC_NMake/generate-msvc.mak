# NMake Makefile portion for code generation and
# intermediate build directory creation
# Items in here should not need to be edited unless
# one is maintaining the NMake build files.

# Create the build directories
$(OUTDIR)\gdkmm	\
$(OUTDIR)\gtkmm	\
$(OUTDIR)\gtkmm3-demo:
	@-md $@

# Generate .def files
$(OUTDIR)\gdkmm\gdkmm.def: $(GENDEF) $(OUTDIR)\gdkmm $(gdkmm_OBJS)
	$(OUTDIR)\gendef.exe $@ $(GDKMM_DLLNAME).dll $(OUTDIR)\gdkmm\*.obj

$(OUTDIR)\gtkmm\gtkmm.def: $(GENDEF) $(OUTDIR)\gtkmm $(gtkmm_OBJS)
	$(OUTDIR)\gendef.exe $@ $(GTKMM_DLLNAME).dll $(OUTDIR)\gtkmm\*.obj

# Generate wrap_init.cc files
$(OUTDIR)\gdkmm\wrap_init.cc: $(gdkmm_real_hg)
	@if not exist ..\gdk\gdkmm\wrap_init.cc $(PERL) -- "$(GMMPROC_DIR)/generate_wrap_init.pl" --namespace=Gdk --parent_dir=gdkmm $(gdkmm_real_hg:\=/)>$@

# Avoid the dreaded U1095 command line error... @#$@#!
$(OUTDIR)\gtkmm\wrap_init.cc: $(gtkmm_real_hg)
	@if not exist $(@D)\ md $(@D)
	@if exist $@ del $@
	@echo @echo off>gen_$(@B).bat
	@echo.>>gen_$(@B).bat
	@echo $(PERL) -- "$(GMMPROC_DIR)\generate_wrap_init.pl" ^^>>gen_$(@B).bat
	@echo --namespace=Gtk --parent_dir=gtkmm ^^>>gen_$(@B).bat
	@for %%f in ($(GTKMM_HG_FILES)) do @echo ../gtk/src/%%f ^^>>gen_$(@B).bat
	@if not exist ..\gtk\gtkmm\wrap_init.cc call gen_$(@B).bat>$@
	@del gen_$(@B).bat

# Generate demo GResource source file
$(OUTDIR)\gtkmm3-demo\demo_resources.c:	\
$(gtkmm_demo_example_sources)	\
$(gtkmm_demo_resources)	\
..\demos\gtk-demo\demo.gresource.xml
	$(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=..\demos\gtk-demo --generate-source ..\demos\gtk-demo\demo.gresource.xml

prep-git-build: pkg-ver.mak

gdkmm\gdkmm.rc: ..\configure.ac
	@if not "$(DO_REAL_GEN)" == "1" if exist pkg-ver.mak del pkg-ver.mak
	@if not exist pkg-ver.mak $(MAKE) /f Makefile.vc CFG=$(CFG) prep-git-build
	@if "$(DO_REAL_GEN)" == "1" echo Generating $@...
	@if "$(DO_REAL_GEN)" == "1" copy $@.in $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\@GDKMM_MAJOR_VERSION\@/$(PKG_MAJOR_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\@GDKMM_MINOR_VERSION\@/$(PKG_MINOR_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\@GDKMM_MICRO_VERSION\@/$(PKG_MICRO_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\@PACKAGE_VERSION\@/$(PKG_MAJOR_VERSION).$(PKG_MINOR_VERSION).$(PKG_MICRO_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\@GDKMM_MODULE_NAME\@/gdkmm-$(GTKMM_API_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" del $@.bak

gtkmm\gtkmm.rc: ..\configure.ac
	@if not "$(DO_REAL_GEN)" == "1" if exist pkg-ver.mak del pkg-ver.mak
	@if not exist pkg-ver.mak $(MAKE) /f Makefile.vc CFG=$(CFG) prep-git-build
	@if "$(DO_REAL_GEN)" == "1" echo Generating $@...
	@if "$(DO_REAL_GEN)" == "1" copy $@.in $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\@GTKMM_MAJOR_VERSION\@/$(PKG_MAJOR_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\@GTKMM_MINOR_VERSION\@/$(PKG_MINOR_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\@GTKMM_MICRO_VERSION\@/$(PKG_MICRO_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\@PACKAGE_VERSION\@/$(PKG_MAJOR_VERSION).$(PKG_MINOR_VERSION).$(PKG_MICRO_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\@GTKMM_MODULE_NAME\@/gtkmm-$(GTKMM_API_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" del $@.bak

# You may change GTKMM_DISABLE_DEPRECATED and GTKMM_STATIC_LIB if you know what you are doing
gdkmm\gdkmmconfig.h: ..\configure.ac ..\gdk\gdkmmconfig.h.in
	@if not "$(DO_REAL_GEN)" == "1" if exist pkg-ver.mak del pkg-ver.mak
	@if not exist pkg-ver.mak $(MAKE) /f Makefile.vc CFG=$(CFG) prep-git-build
	@if "$(DO_REAL_GEN)" == "1" echo Generating $@...
	@if "$(DO_REAL_GEN)" == "1" copy ..\gdk\$(@F).in $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\#undef GDKMM_DISABLE_DEPRECATED/\/\* \#undef GDKMM_DISABLE_DEPRECATED \*\//g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\#undef GDKMM_STATIC_LIB/\/\* \#undef GDKMM_STATIC_LIB \*\//g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\#undef GDKMM_MAJOR_VERSION/\#define GDKMM_MAJOR_VERSION $(PKG_MAJOR_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\#undef GDKMM_MINOR_VERSION/\#define GDKMM_MINOR_VERSION $(PKG_MINOR_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\#undef GDKMM_MICRO_VERSION/\#define GDKMM_MICRO_VERSION $(PKG_MICRO_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" del $@.bak

gtkmm\gtkmmconfig.h: ..\configure.ac ..\gtk\gtkmmconfig.h.in
	@if not "$(DO_REAL_GEN)" == "1" if exist pkg-ver.mak del pkg-ver.mak
	@if not exist pkg-ver.mak $(MAKE) /f Makefile.vc CFG=$(CFG) prep-git-build
	@if "$(DO_REAL_GEN)" == "1" echo Generating $@...
	@if "$(DO_REAL_GEN)" == "1" copy ..\gtk\$(@F).in $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\#undef GTKMM_ATKMM_ENABLED/\#define GTKMM_ATKMM_ENABLED 1/g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\#undef GTKMM_DISABLE_DEPRECATED/\/\* \#undef GTKMM_DISABLE_DEPRECATED \*\//g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\#undef GTKMM_STATIC_LIB/\/\* \#undef GTKMM_STATIC_LIB \*\//g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\#undef GTKMM_MAJOR_VERSION/\#define GTKMM_MAJOR_VERSION $(PKG_MAJOR_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\#undef GTKMM_MINOR_VERSION/\#define GTKMM_MINOR_VERSION $(PKG_MINOR_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" $(PERL) -pi.bak -e "s/\#undef GTKMM_MICRO_VERSION/\#define GTKMM_MICRO_VERSION $(PKG_MICRO_VERSION)/g" $@
	@if "$(DO_REAL_GEN)" == "1" del $@.bak

pkg-ver.mak: ..\configure.ac
	@echo Generating version info Makefile Snippet...
	@$(PERL) -00 -ne "print if /AC_INIT\(/" $** |	\
	$(PERL) -pe "tr/, /\n/s" |	\
	$(PERL) -ne "print if 2 .. 2" |	\
	$(PERL) -ne "print /\[(.*)\]/" > ver.txt
	@echo @echo off>pkg-ver.bat
	@echo.>>pkg-ver.bat
	@echo set /p glibmm_ver=^<ver.txt>>pkg-ver.bat
	@echo for /f "tokens=1,2,3 delims=." %%%%a IN ("%glibmm_ver%") do (echo PKG_MAJOR_VERSION=%%%%a^& echo PKG_MINOR_VERSION=%%%%b^& echo PKG_MICRO_VERSION=%%%%c)^>$@>>pkg-ver.bat
	@pkg-ver.bat
	@del ver.txt pkg-ver.bat
	$(MAKE) /f Makefile.vc CFG=$(CFG) GENERATE_VERSIONED_FILES=1 gdkmm\gdkmm.rc gdkmm\gdkmmconfig.h gtkmm\gtkmm.rc gtkmm\gtkmmconfig.h
