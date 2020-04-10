# NMake Makefile snippet for copying the built libraries, utilities and headers to
# a path under $(PREFIX).

install: all
	@if not exist $(PREFIX)\bin\ md $(PREFIX)\bin
	@if not exist $(PREFIX)\lib\gdkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include\ md $(PREFIX)\lib\gdkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include
	@if not exist $(PREFIX)\include\gdkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\private\ @md $(PREFIX)\include\gdkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\private
	@if not exist $(PREFIX)\lib\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include\ md $(PREFIX)\lib\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include
	@if not exist $(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\private\ @md $(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\private
	@if exist vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo.exe copy /b vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo.exe $(PREFIX)\bin
	@if exist vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo.pdb copy /b vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm3-demo.pdb $(PREFIX)\bin
	@copy /b vs$(PDBVER)\$(CFG)\$(PLAT)\$(GDKMM_LIBNAME).dll $(PREFIX)\bin
	@copy /b vs$(PDBVER)\$(CFG)\$(PLAT)\$(GTKMM_LIBNAME).dll $(PREFIX)\bin
	@copy /b vs$(PDBVER)\$(CFG)\$(PLAT)\$(GDKMM_LIBNAME).pdb $(PREFIX)\bin
	@copy /b vs$(PDBVER)\$(CFG)\$(PLAT)\$(GTKMM_LIBNAME).pdb $(PREFIX)\bin
	@copy /b vs$(PDBVER)\$(CFG)\$(PLAT)\$(GDKMM_LIBNAME).lib $(PREFIX)\lib
	@copy /b vs$(PDBVER)\$(CFG)\$(PLAT)\$(GTKMM_LIBNAME).lib $(PREFIX)\lib
	@copy ..\gdk\gdkmm.h "$(PREFIX)\include\gdkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\"
	@for %h in ($(gdkmm_files_extra_h)) do @copy ..\gdk\gdkmm\%h "$(PREFIX)\include\gdkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS)) do @if exist ..\gdk\gdkmm\%h copy ..\gdk\gdkmm\%h "$(PREFIX)\include\gdkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS)) do @if exist vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\%h copy vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\%h "$(PREFIX)\include\gdkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS_P)) do @if exist ..\gdk\gdkmm\private\%h copy ..\gdk\gdkmm\private\%h "$(PREFIX)\include\gdkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\private\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS_P)) do @if exist vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\private\%h copy vs$(PDBVER)\$(CFG)\$(PLAT)\gdkmm\private\%h "$(PREFIX)\include\gdkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\private\%h"
	@copy ".\gdkmm\gdkmmconfig.h" "$(PREFIX)\lib\gdkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include\"
	@copy ..\gtk\gtkmm.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\"
	@for %h in ($(GTKMM_INT_EXTRA_HEADERS)) do @copy ..\gtk\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\%h"
	@for %h in ($(GTKMM_INT_GENERATED_HEADERS)) do @if exist ..\gtk\gtkmm\%h copy ..\gtk\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\%h"
	@for %h in ($(GTKMM_INT_GENERATED_HEADERS)) do @if exist vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\%h copy vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\%h"
	@for %h in ($(GTKMM_INT_EXTRA_HEADERS_P)) do @copy ..\gtk\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\%h"
	@for %h in ($(GTKMM_HG_FILES)) do @if exist ..\gtk\gtkmm\private\%~nh_p.h copy ..\gtk\gtkmm\private\%~nh_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\private\%~nh_p.h"
	@for %h in ($(GTKMM_HG_FILES)) do @if exist vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\private\%~nh_p.h copy vs$(PDBVER)\$(CFG)\$(PLAT)\gtkmm\private\%~nh_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\private\%~nh_p.h"
	@copy ".\gtkmm\gtkmmconfig.h" "$(PREFIX)\lib\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include\"
