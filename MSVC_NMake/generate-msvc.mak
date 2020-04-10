# NMake Makefile portion for code generation and
# intermediate build directory creation
# Items in here should not need to be edited unless
# one is maintaining the NMake build files.

# Create the build directories
vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo:
	@-mkdir $@

# Generate wrap_init.cc files
vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\wrap_init.cc: $(gdkmm_real_hg)
	@if not exist $(@D)\ md $(@D)
	@if not exist ..\gdk\gdkmm\wrap_init.cc $(PERL) -- "$(GMMPROC_DIR)/generate_wrap_init.pl" --namespace=Gdk --parent_dir=gdkmm $(gdkmm_real_hg:\=/)>$@

# Avoid the dreaded U1095 command line error... @#$@#!
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\wrap_init.cc: $(gtkmm_real_hg)
	@if not exist $(@D)\ md $(@D)
	@if exist $@ del $@
	@echo @echo off>gen_$(@B).bat
	@echo.>>gen_$(@B).bat
	@echo $(PERL) -- "$(GMMPROC_DIR)\generate_wrap_init.pl" ^^>>gen_$(@B).bat
	@echo --namespace=Gtk --parent_dir=gtkmm ^^>>gen_$(@B).bat
	@for %%f in ($(GTKMM_HG_FILES)) do @echo ../gtk/src/%%f ^^>>gen_$(@B).bat
	@if not exist ..\gtk\gtkmm\wrap_init.cc call gen_$(@B).bat>$@
	@del gen_$(@B).bat

# Generate .def files
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\gtkmm.def: $(GENDEF) $(gdkmm_OBJS) $(gtkmm_OBJS)
	vs$(VSVER)\$(CFG)\$(PLAT)\gendef.exe $@ $(GTKMM_LIBNAME) vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\*.obj vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\*.obj

# Generate demo GResource source file
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo\demo_resources.c:	\
$(gtkmm_demo_example_sources)	\
$(gtkmm_demo_resources)	\
..\demos\gtk-demo\demo.gresource.xml
	$(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=..\demos\gtk-demo --generate-source ..\demos\gtk-demo\demo.gresource.xml


prep-git-build: pkg-ver.mak

gtkmm\gtkmm.rc: pkg-ver.mak
	@echo Generating $@...
	@copy $@.in $@
	@$(PERL) -pi.bak -e "s/\@GTKMM_MAJOR_VERSION\@/$(PKG_MAJOR_VERSION)/g" $@
	@$(PERL) -pi.bak -e "s/\@GTKMM_MINOR_VERSION\@/$(PKG_MINOR_VERSION)/g" $@
	@$(PERL) -pi.bak -e "s/\@GTKMM_MICRO_VERSION\@/$(PKG_MICRO_VERSION)/g" $@
	@$(PERL) -pi.bak -e "s/\@PACKAGE_VERSION\@/$(PKG_MAJOR_VERSION).$(PKG_MINOR_VERSION).$(PKG_MICRO_VERSION)/g" $@
	@$(PERL) -pi.bak -e "s/\@GTKMM_MODULE_NAME\@/gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)/g" $@
	@del $@.bak

# You may change GTKMM_DISABLE_DEPRECATED and GTKMM_STATIC_LIB if you know what you are doing
gdkmm\gdkmmconfig.h: pkg-ver.mak ..\gdk\gdkmmconfig.h.in
	@echo Generating $@...
	@if not exist $(@D) mkdir $(@D)
	@copy ..\gdk\$(@F).in $@
	@$(PERL) -pi.bak -e "s/\#undef GDKMM_DISABLE_DEPRECATED/\/\* \#undef GDKMM_DISABLE_DEPRECATED \*\//g" $@
	@$(PERL) -pi.bak -e "s/\#undef GDKMM_STATIC_LIB/\/\* \#undef GDKMM_STATIC_LIB \*\//g" $@
	@$(PERL) -pi.bak -e "s/\#undef GDKMM_MAJOR_VERSION/\#define GDKMM_MAJOR_VERSION $(PKG_MAJOR_VERSION)/g" $@
	@$(PERL) -pi.bak -e "s/\#undef GDKMM_MINOR_VERSION/\#define GDKMM_MINOR_VERSION $(PKG_MINOR_VERSION)/g" $@
	@$(PERL) -pi.bak -e "s/\#undef GDKMM_MICRO_VERSION/\#define GDKMM_MICRO_VERSION $(PKG_MICRO_VERSION)/g" $@
	@del $@.bak

gtkmm\gtkmmconfig.h: pkg-ver.mak ..\gtk\gtkmmconfig.h.in
	@echo Generating $@...
	@copy ..\gtk\$(@F).in $@
	@$(PERL) -pi.bak -e "s/\#undef GTKMM_ATKMM_ENABLED/\#define GTKMM_ATKMM_ENABLED 1/g" $@
	@$(PERL) -pi.bak -e "s/\#undef GTKMM_DISABLE_DEPRECATED/\/\* \#undef GTKMM_DISABLE_DEPRECATED \*\//g" $@
	@$(PERL) -pi.bak -e "s/\#undef GTKMM_STATIC_LIB/\/\* \#undef GTKMM_STATIC_LIB \*\//g" $@
	@$(PERL) -pi.bak -e "s/\#undef GTKMM_MAJOR_VERSION/\#define GTKMM_MAJOR_VERSION $(PKG_MAJOR_VERSION)/g" $@
	@$(PERL) -pi.bak -e "s/\#undef GTKMM_MINOR_VERSION/\#define GTKMM_MINOR_VERSION $(PKG_MINOR_VERSION)/g" $@
	@$(PERL) -pi.bak -e "s/\#undef GTKMM_MICRO_VERSION/\#define GTKMM_MICRO_VERSION $(PKG_MICRO_VERSION)/g" $@
	@del $@.bak

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
	$(MAKE) /f Makefile.vc CFG=$(CFG) GENERATE_VERSIONED_FILES=1 gdkmm\gdkmmconfig.h gtkmm\gtkmm.rc gtkmm\gtkmmconfig.h
