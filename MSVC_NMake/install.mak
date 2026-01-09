# NMake Makefile snippet for copying the built libraries, utilities and headers to
# a path under $(PREFIX).

install: all
	@if not exist $(PREFIX)\bin\ mkdir $(PREFIX)\bin
	@if not exist $(PREFIX)\lib\gtkmm-$(GTKMM_API_VERSION)\include\ mkdir $(PREFIX)\lib\gtkmm-$(GTKMM_API_VERSION)\include
	@if not exist $(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gdkmm\private\ @mkdir $(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gdkmm\private
	@if not exist $(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gskmm\private\ @mkdir $(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gskmm\private
	@if not exist $(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\private\ @mkdir $(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\private
	@if not exist $(PREFIX)\lib\gtkmm-$(GTKMM_API_VERSION)\proc\m4\ md $(PREFIX)\lib\gtkmm-$(GTKMM_API_VERSION)\proc\m4
	@copy /b $(OUTDIR)\gtkmm4-demo.exe $(PREFIX)\bin
	@copy /b $(OUTDIR)\gtkmm4-demo.pdb $(PREFIX)\bin
	@copy /b $(OUTDIR)\$(GTKMM_LIBNAME).dll $(PREFIX)\bin
	@copy /b $(OUTDIR)\$(GTKMM_LIBNAME).pdb $(PREFIX)\bin
	@copy /b $(OUTDIR)\$(GTKMM_LIBNAME).lib $(PREFIX)\lib
	@copy ..\gdk\gdkmm.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\"
	@for %h in ($(gdkmm_files_extra_h)) do @copy ..\gdk\gdkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS)) do @if exist ..\gdk\gdkmm\%h copy ..\gdk\gdkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS)) do @if exist ..\untracked\gdk\gdkmm\%h copy ..\untracked\gdk\gdkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS)) do @if exist $(OUTDIR)\gdkmm\%h copy $(OUTDIR)\gdkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS_P)) do @if exist ..\gdk\gdkmm\private\%h copy ..\gdk\gdkmm\private\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gdkmm\private\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS_P)) do @if exist ..\untracked\gdk\gdkmm\private\%h copy ..\untracked\gdk\gdkmm\private\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gdkmm\private\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS_P)) do @if exist $(OUTDIR)\gdkmm\private\%h copy $(OUTDIR)\gdkmm\private\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gdkmm\private\%h"
	@copy ".\gdkmm\gdkmmconfig.h" "$(PREFIX)\lib\gtkmm-$(GTKMM_API_VERSION)\include\"
	@copy ..\gsk\gskmm.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\"
	@for %h in ($(gskmm_files_extra_h)) do @copy ..\gsk\gskmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gskmm\%h"
	@for %h in ($(GSKMM_HG_FILES:.hg=.h)) do @if exist ..\gsk\gskmm\%h copy ..\gsk\gskmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gskmm\%h"
	@for %h in ($(GSKMM_HG_FILES:.hg=.h)) do @if exist ..\untracked\gsk\gskmm\%h copy ..\untracked\gsk\gskmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gskmm\%h"
	@for %h in ($(GSKMM_HG_FILES:.hg=.h)) do @if exist $(OUTDIR)\gskmm\%h copy $(OUTDIR)\gskmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gskmm\%h"
	@for %h in ($(GSKMM_HG_FILES:.hg=)) do @if exist ..\gsk\gskmm\private\%h_p.h copy ..\gsk\gskmm\private\%h_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gskmm\private\%h_p.h"
	@for %h in ($(GSKMM_HG_FILES:.hg=)) do @if exist ..\untracked\gsk\gskmm\private\%h_p.h copy ..\untracked\gsk\gskmm\private\%h_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gskmm\private\%h_p.h"
	@for %h in ($(GSKMM_HG_FILES:.hg=)) do @if exist $(OUTDIR)\gskmm\private\%h_p.h copy $(OUTDIR)\gskmm\private\%h_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gskmm\private\%h_p.h"
	@copy ".\gskmm\gskmmconfig.h" "$(PREFIX)\lib\gtkmm-$(GTKMM_API_VERSION)\include\"
	@copy ..\gtk\gtkmm.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\"
	@for %h in ($(GTKMM_INT_EXTRA_HEADERS)) do @copy ..\gtk\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\%h"
	@for %h in ($(GTKMM_HG_FILES:.hg=)) do @if exist ..\gtk\gtkmm\%h.h copy ..\gtk\gtkmm\%h.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\%h.h"
	@for %h in ($(GTKMM_HG_FILES:.hg=)) do @if exist ..\untracked\gtk\gtkmm\%~nh.h copy ..\untracked\gtk\gtkmm\%~nh.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\%~nh.h"
	@for %h in ($(GTKMM_HG_FILES:.hg=)) do @if exist $(OUTDIR)\gtkmm\%h.h copy $(OUTDIR)\gtkmm\%h.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\%h.h"
	@for %h in ($(GTKMM_HG_FILES:.hg=)) do @if exist ..\gtk\gtkmm\private\%h_p.h copy ..\gtk\gtkmm\private\%h_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\private\%h_p.h"
	@for %h in ($(GTKMM_HG_FILES:.hg=)) do @if exist ..\untracked\gtk\gtkmm\private\%h_p.h copy ..\untracked\gtk\gtkmm\private\%h_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\private\%h_p.h"
	@for %h in ($(GTKMM_HG_FILES:.hg=)) do @if exist $(OUTDIR)\gtkmm\private\%h_p.h copy $(OUTDIR)\gtkmm\private\%h_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\private\%h_p.h"
	@for %h in ($(GTKMM_INT_EXTRA_HEADERS_P)) do @copy ..\gtk\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_API_VERSION)\gtkmm\%h"
	@copy ".\gtkmm\gtkmmconfig.h" "$(PREFIX)\lib\gtkmm-$(GTKMM_API_VERSION)\include\"
	@copy ..\tools\m4\*.m4 $(PREFIX)\lib\gtkmm-$(GTKMM_API_VERSION)\proc\m4
