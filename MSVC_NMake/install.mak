# NMake Makefile snippet for copying the built libraries, utilities and headers to
# a path under $(PREFIX).

install: all
	@if not exist $(PREFIX)\bin\ mkdir $(PREFIX)\bin
	@if not exist $(PREFIX)\lib\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include\ mkdir $(PREFIX)\lib\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include
	@if not exist $(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\private\ @mkdir $(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\private
	@if not exist $(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\private\ @mkdir $(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\private
	@copy /b vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo.exe $(PREFIX)\bin
	@copy /b vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo.pdb $(PREFIX)\bin
	@copy /b vs$(VSVER)\$(CFG)\$(PLAT)\$(GTKMM_LIBNAME).dll $(PREFIX)\bin
	@copy /b vs$(VSVER)\$(CFG)\$(PLAT)\$(GTKMM_LIBNAME).pdb $(PREFIX)\bin
	@copy /b vs$(VSVER)\$(CFG)\$(PLAT)\$(GTKMM_LIBNAME).lib $(PREFIX)\lib
	@copy ..\gdk\gdkmm.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS) $(gdkmm_files_extra_h)) do @copy ..\gdk\gdkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS_P)) do @copy ..\gdk\gdkmm\private\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\private\%h"
	@copy ".\gdkmm\gdkmmconfig.h" "$(PREFIX)\lib\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include\"
	@copy ..\gtk\gtkmm.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\"
	@for %h in ($(GTKMM_INT_GENERATED_HEADERS)) do @copy ..\gtk\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\%h"
	@for %h in ($(gtkmm_files_extra_any_h) $(gtkmm_files_extra_deprecated_h)) do @copy ..\gtk\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\%h"
	@for %h in ($(GTKMM_INT_GENERATED_HEADERS_P)) do @copy ..\gtk\gtkmm\private\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\private\%h"
	@for %h in ($(GTKMM_INT_EXTRA_HEADERS_P)) do @copy ..\gtk\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\%h"
	@copy ".\gtkmm\gtkmmconfig.h" "$(PREFIX)\lib\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include\"
