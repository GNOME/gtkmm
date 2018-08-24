# NMake Makefile portion for code generation and
# intermediate build directory creation
# Items in here should not need to be edited unless
# one is maintaining the NMake build files.

# Create the build directories
$(CFG)\$(PLAT)\gendef	\
$(CFG)\$(PLAT)\gdkmm	\
$(CFG)\$(PLAT)\gtkmm	\
$(CFG)\$(PLAT)\gtkmm3-demo	\
$(CFG)\$(PLAT)\gtkmm3-test-builder	\
$(CFG)\$(PLAT)\gtkmm3-test-child_widget	\
$(CFG)\$(PLAT)\gtkmm3-test-child_widget2	\
$(CFG)\$(PLAT)\gtkmm3-test-child_widget_managed	\
$(CFG)\$(PLAT)\gtkmm3-test-delete_cpp_child	\
$(CFG)\$(PLAT)\gtkmm3-test-dialog_deletethis	\
$(CFG)\$(PLAT)\gtkmm3-test-main_with_options	\
$(CFG)\$(PLAT)\gtkmm3-test-menu_destruction	\
$(CFG)\$(PLAT)\gtkmm3-test-object_move	\
$(CFG)\$(PLAT)\gtkmm3-test-property_notification	\
$(CFG)\$(PLAT)\gtkmm3-test-refcount_dialog	\
$(CFG)\$(PLAT)\gtkmm3-test-scrolledwindow	\
$(CFG)\$(PLAT)\gtkmm3-test-tree_model_iterator	\
$(CFG)\$(PLAT)\gtkmm3-test-wrap_existing:
	@-mkdir $@

# Generate .def files
$(CFG)\$(PLAT)\gdkmm\gdkmm.def: $(GENDEF) $(CFG)\$(PLAT)\gdkmm $(gdkmm_OBJS)
	$(CFG)\$(PLAT)\gendef.exe $@ $(GDKMM_LIBNAME) $(CFG)\$(PLAT)\gdkmm\*.obj

$(CFG)\$(PLAT)\gtkmm\gtkmm.def: $(GENDEF) $(CFG)\$(PLAT)\gtkmm $(gtkmm_OBJS)
	$(CFG)\$(PLAT)\gendef.exe $@ $(GTKMM_LIBNAME) $(CFG)\$(PLAT)\gtkmm\*.obj

# Generate demo GResource source file
$(CFG)\$(PLAT)\gtkmm3-demo\demo_resources.c:	\
$(gtkmm_demo_example_sources)	\
$(gtkmm_demo_resources)	\
..\demos\gtk-demo\demo.gresource.xml
	$(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=..\demos\gtk-demo --generate-source ..\demos\gtk-demo\demo.gresource.xml
