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
