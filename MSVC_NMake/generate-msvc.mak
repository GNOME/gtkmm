# NMake Makefile portion for code generation and
# intermediate build directory creation
# Items in here should not need to be edited unless
# one is maintaining the NMake build files.

# Create the build directories
$(CFG)\$(PLAT)\gendef	\
$(CFG)\$(PLAT)\gdkmm	\
$(CFG)\$(PLAT)\gtkmm	\
$(CFG)\$(PLAT)\gtkmm4-demo	\
$(CFG)\$(PLAT)\gtkmm4-test-builder	\
$(CFG)\$(PLAT)\gtkmm4-test-child_widget	\
$(CFG)\$(PLAT)\gtkmm4-test-child_widget2	\
$(CFG)\$(PLAT)\gtkmm4-test-child_widget_managed	\
$(CFG)\$(PLAT)\gtkmm4-test-delete_cpp_child	\
$(CFG)\$(PLAT)\gtkmm4-test-dialog_deletethis	\
$(CFG)\$(PLAT)\gtkmm4-test-main_with_options	\
$(CFG)\$(PLAT)\gtkmm4-test-menu_destruction	\
$(CFG)\$(PLAT)\gtkmm4-test-object_move	\
$(CFG)\$(PLAT)\gtkmm4-test-property_notification	\
$(CFG)\$(PLAT)\gtkmm4-test-refcount_dialog	\
$(CFG)\$(PLAT)\gtkmm4-test-scrolledwindow	\
$(CFG)\$(PLAT)\gtkmm4-test-tree_model_iterator	\
$(CFG)\$(PLAT)\gtkmm4-test-wrap_existing:
	@-mkdir $@

# Generate .def files
$(CFG)\$(PLAT)\gtkmm\gtkmm.def: $(GENDEF) $(CFG)\$(PLAT)\gdkmm $(CFG)\$(PLAT)\gtkmm $(gdkmm_OBJS) $(gtkmm_OBJS)
	$(CFG)\$(PLAT)\gendef.exe $@ $(GTKMM_LIBNAME) $(CFG)\$(PLAT)\gdkmm\*.obj $(CFG)\$(PLAT)\gtkmm\*.obj

# Generate demo GResource source file
$(CFG)\$(PLAT)\gtkmm4-demo\demo_resources.c:	\
$(gtkmm_demo_example_sources)	\
$(gtkmm_demo_resources)	\
..\demos\gtk-demo\demo.gresource.xml
	$(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=..\demos\gtk-demo --generate-source ..\demos\gtk-demo\demo.gresource.xml