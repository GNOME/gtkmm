# NMake Makefile portion for code generation and
# intermediate build directory creation
# Items in here should not need to be edited unless
# one is maintaining the NMake build files.

# Create the build directories
vs$(PDBVER)\$(CFG)\$(PLAT)\gendef	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-builder	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-child_widget	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-child_widget2	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-child_widget_managed	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-delete_cpp_child	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-dialog_deletethis	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-main_with_options	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-menu_destruction	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-object_move	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-property_notification	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-refcount_dialog	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-scrolledwindow	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-tree_model_iterator	\
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-test-wrap_existing:
	@-mkdir $@

# Generate .def files
vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\gdkmm.def: $(GENDEF) vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm $(gdkmm_OBJS)
	vs$(PDBVER)\$(CFG)\$(PLAT)\gendef.exe $@ $(GDKMM_LIBNAME) vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\*.obj

vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\gtkmm.def: $(GENDEF) vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm $(gtkmm_OBJS)
	vs$(PDBVER)\$(CFG)\$(PLAT)\gendef.exe $@ $(GTKMM_LIBNAME) vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\*.obj

# Generate demo GResource source file
vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo\demo_resources.c:	\
$(gtkmm_demo_example_sources)	\
$(gtkmm_demo_resources)	\
..\demos\gtk-demo\demo.gresource.xml
	$(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=..\demos\gtk-demo --generate-source ..\demos\gtk-demo\demo.gresource.xml

prep-git-build: pkg-ver.mak

gdkmm\gdkmm.rc: pkg-ver.mak
	@echo Generating $@...
	@copy $@.in $@
	@$(PERL) -pi.bak -e "s/\@GDKMM_MAJOR_VERSION\@/$(PKG_MAJOR_VERSION)/g" $@
	@$(PERL) -pi.bak -e "s/\@GDKMM_MINOR_VERSION\@/$(PKG_MINOR_VERSION)/g" $@
	@$(PERL) -pi.bak -e "s/\@GDKMM_MICRO_VERSION\@/$(PKG_MICRO_VERSION)/g" $@
	@$(PERL) -pi.bak -e "s/\@PACKAGE_VERSION\@/$(PKG_MAJOR_VERSION).$(PKG_MINOR_VERSION).$(PKG_MICRO_VERSION)/g" $@
	@$(PERL) -pi.bak -e "s/\@GDKMM_MODULE_NAME\@/gdkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)/g" $@
	@del $@.bak

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
	$(MAKE) /f Makefile.vc CFG=$(CFG) GENERATE_VERSIONED_FILES=1 gdkmm\gdkmm.rc gdkmm\gdkmmconfig.h gtkmm\gtkmm.rc gtkmm\gtkmmconfig.h
