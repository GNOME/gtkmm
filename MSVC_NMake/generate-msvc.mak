# NMake Makefile portion for code generation and
# intermediate build directory creation
# Items in here should not need to be edited unless
# one is maintaining the NMake build files.

# Create the build directories
vs$(VSVER)\$(CFG)\$(PLAT)\gendef	\
vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-test-builder	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-test-child_widget	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-test-child_widget2	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-test-child_widget_managed	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-test-delete_cpp_child	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-test-dialog_deletethis	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-test-main_with_options	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-test-menu_destruction	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-test-object_move	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-test-property_notification	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-test-refcount_dialog	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-test-scrolledwindow	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-test-tree_model_iterator	\
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-test-wrap_existing:
	@-mkdir $@

# Generate .def files
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\gtkmm.def: $(GENDEF) vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm $(gdkmm_OBJS) $(gtkmm_OBJS)
	vs$(VSVER)\$(CFG)\$(PLAT)\gendef.exe $@ $(GTKMM_LIBNAME) vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\*.obj vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\*.obj

# Generate demo GResource source file
vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo\demo_resources.c:	\
$(gtkmm_demo_example_sources)	\
$(gtkmm_demo_resources)	\
..\demos\gtk-demo\demo.gresource.xml
	$(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=..\demos\gtk-demo --generate-source ..\demos\gtk-demo\demo.gresource.xml