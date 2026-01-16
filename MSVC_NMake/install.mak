# NMake Makefile snippet for copying the built libraries, utilities and headers to
# a path under $(PREFIX).

install: all
	@if not exist $(PREFIX)\bin\ md $(PREFIX)\bin
	@if not exist $(PREFIX)\lib\gdkmm-$(GTKMM_API_VERSION)\include\ md $(PREFIX)\lib\gdkmm-$(GTKMM_API_VERSION)\include
	@if not exist $(PREFIX)\include\gdkmm-$(GTKMM_API_VERSION)\gdkmm\private\ @md $(PREFIX)\include\gdkmm-$(GTKMM_API_VERSION)\gdkmm\private
	@if not exist $(PREFIX)\lib\gtkmm-$(GTKMM_API_VERSION)\include\ md $(PREFIX)\lib\gtkmm-$(GTKMM_API_VERSION)\include
	@if not exist $(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\private\ @md $(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\private
	@if not exist $(PREFIX)\lib\gtkmm-$(GTKMM_API_VERSION)\proc\m4\ md $(PREFIX)\lib\gtkmm-$(GTKMM_API_VERSION)\proc\m4
	@copy /b $(OUTDIR)\gtkmm3-demo.exe $(PREFIX)\bin
	@copy /b $(OUTDIR)\gtkmm3-demo.pdb $(PREFIX)\bin
	@copy /b $(OUTDIR)\$(GDKMM_LIBNAME).dll $(PREFIX)\bin
	@copy /b $(OUTDIR)\$(GTKMM_LIBNAME).dll $(PREFIX)\bin
	@copy /b $(OUTDIR)\$(GDKMM_LIBNAME).pdb $(PREFIX)\bin
	@copy /b $(OUTDIR)\$(GTKMM_LIBNAME).pdb $(PREFIX)\bin
	@copy /b $(OUTDIR)\$(GDKMM_LIBNAME).lib $(PREFIX)\lib
	@copy /b $(OUTDIR)\$(GTKMM_LIBNAME).lib $(PREFIX)\lib
	@copy ..\gdk\gdkmm.h "$(PREFIX)\include\gdkmm-$(GTKMM_API_VERSION)\"
	@for %h in ($(gdkmm_files_extra_h)) do @copy ..\gdk\gdkmm\%h "$(PREFIX)\include\gdkmm-$(GTKMM_API_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS)) do @if exist ..\gdk\gdkmm\%h copy ..\gdk\gdkmm\%h "$(PREFIX)\include\gdkmm-$(GTKMM_API_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS)) do @if exist $(OUTDIR)\gdkmm\%h copy $(OUTDIR)\gdkmm\%h "$(PREFIX)\include\gdkmm-$(GTKMM_API_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS_P)) do @if exist ..\gdk\gdkmm\private\%h copy ..\gdk\gdkmm\private\%h "$(PREFIX)\include\gdkmm-$(GTKMM_API_VERSION)\gdkmm\private\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS_P)) do @if exist $(OUTDIR)\gdkmm\private\%h copy $(OUTDIR)\gdkmm\private\%h "$(PREFIX)\include\gdkmm-$(GTKMM_API_VERSION)\gdkmm\private\%h"
	@copy ".\gdkmm\gdkmmconfig.h" "$(PREFIX)\lib\gdkmm-$(GTKMM_API_VERSION)\include\"
	@copy ..\gtk\gtkmm.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\"
	@for %h in ($(GTKMM_INT_EXTRA_HEADERS)) do @copy ..\gtk\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\%h"
	@for %h in ($(GTKMM_INT_GENERATED_HEADERS)) do @if exist ..\gtk\gtkmm\%h copy ..\gtk\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\%h"
	@for %h in ($(GTKMM_INT_GENERATED_HEADERS)) do @if exist $(OUTDIR)\gtkmm\%h copy $(OUTDIR)\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\%h"
	@for %h in ($(GTKMM_INT_EXTRA_HEADERS_P)) do @copy ..\gtk\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\%h"
	@for %h in ($(GTKMM_HG_FILES)) do @if exist ..\gtk\gtkmm\private\%~nh_p.h copy ..\gtk\gtkmm\private\%~nh_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\private\%~nh_p.h"
	@for %h in ($(GTKMM_HG_FILES)) do @if exist $(OUTDIR)\gtkmm\private\%~nh_p.h copy $(OUTDIR)\gtkmm\private\%~nh_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\private\%~nh_p.h"
	@copy ".\gtkmm\gtkmmconfig.h" "$(PREFIX)\lib\gtkmm-$(GTKMM_API_VERSION)\include\"
	@copy ..\tools\m4\*.m4 $(PREFIX)\lib\gtkmm-$(GTKMM_API_VERSION)\proc\m4
