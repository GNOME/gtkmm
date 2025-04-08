# NMake Makefile snippet for copying the built libraries, utilities and headers to
# a path under $(PREFIX).

install: all
	@if not exist $(PREFIX)\bin\ mkdir $(PREFIX)\bin
	@if not exist $(PREFIX)\lib\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include\ mkdir $(PREFIX)\lib\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include
	@if not exist $(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\private\ @mkdir $(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\private
	@if not exist $(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gskmm\private\ @mkdir $(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gskmm\private
	@if not exist $(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\private\ @mkdir $(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\private
	@if not exist $(PREFIX)\share\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\proc\m4\ md $(PREFIX)\share\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\proc\m4
	@copy /b vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo.exe $(PREFIX)\bin
	@copy /b vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm4-demo.pdb $(PREFIX)\bin
	@copy /b vs$(VSVER)\$(CFG)\$(PLAT)\$(GTKMM_LIBNAME).dll $(PREFIX)\bin
	@copy /b vs$(VSVER)\$(CFG)\$(PLAT)\$(GTKMM_LIBNAME).pdb $(PREFIX)\bin
	@copy /b vs$(VSVER)\$(CFG)\$(PLAT)\$(GTKMM_LIBNAME).lib $(PREFIX)\lib
	@copy ..\gdk\gdkmm.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\"
	@for %h in ($(gdkmm_files_extra_h)) do @copy ..\gdk\gdkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS)) do @if exist ..\gdk\gdkmm\%h copy ..\gdk\gdkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS)) do @if exist ..\untracked\gdk\gdkmm\%h copy ..\untracked\gdk\gdkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS)) do @if exist vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\%h copy vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS_P)) do @if exist ..\gdk\gdkmm\private\%h copy ..\gdk\gdkmm\private\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\private\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS_P)) do @if exist ..\untracked\gdk\gdkmm\private\%h copy ..\untracked\gdk\gdkmm\private\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\private\%h"
	@for %h in ($(GDKMM_INT_GENERATED_HEADERS_P)) do @if exist vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\private\%h copy vs$(VSVER)\$(CFG)\$(PLAT)\gdkmm\private\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gdkmm\private\%h"
	@copy ".\gdkmm\gdkmmconfig.h" "$(PREFIX)\lib\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include\"
	@copy ..\gsk\gskmm.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\"
	@for %h in ($(gskmm_files_extra_h)) do @copy ..\gsk\gskmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gskmm\%h"
	@for %h in ($(GSKMM_HG_FILES:.hg=.h)) do @if exist ..\gsk\gskmm\%h copy ..\gsk\gskmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gskmm\%h"
	@for %h in ($(GSKMM_HG_FILES:.hg=.h)) do @if exist ..\untracked\gsk\gskmm\%h copy ..\untracked\gsk\gskmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gskmm\%h"
	@for %h in ($(GSKMM_HG_FILES:.hg=.h)) do @if exist vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\%h copy vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gskmm\%h"
	@for %h in ($(GSKMM_HG_FILES:.hg=)) do @if exist ..\gsk\gskmm\private\%h_p.h copy ..\gsk\gskmm\private\%h_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gskmm\private\%h_p.h"
	@for %h in ($(GSKMM_HG_FILES:.hg=)) do @if exist ..\untracked\gsk\gskmm\private\%h_p.h copy ..\untracked\gsk\gskmm\private\%h_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gskmm\private\%h_p.h"
	@for %h in ($(GSKMM_HG_FILES:.hg=)) do @if exist vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\private\%h_p.h copy vs$(VSVER)\$(CFG)\$(PLAT)\gskmm\private\%h_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gskmm\private\%h_p.h"
	@copy ".\gskmm\gskmmconfig.h" "$(PREFIX)\lib\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include\"
	@copy ..\gtk\gtkmm.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\"
	@for %h in ($(GTKMM_INT_EXTRA_HEADERS)) do @copy ..\gtk\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\%h"
	@for %h in ($(GTKMM_HG_FILES:.hg=)) do @if exist ..\gtk\gtkmm\%h.h copy ..\gtk\gtkmm\%h.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\%h.h"
	@for %h in ($(GTKMM_HG_FILES:.hg=)) do @if exist ..\untracked\gtk\gtkmm\%~nh.h copy ..\untracked\gtk\gtkmm\%~nh.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\%~nh.h"
	@for %h in ($(GTKMM_HG_FILES:.hg=)) do @if exist vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\%h.h copy vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\%h.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\%h.h"
	@for %h in ($(GTKMM_HG_FILES:.hg=)) do @if exist ..\gtk\gtkmm\private\%h_p.h copy ..\gtk\gtkmm\private\%h_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\private\%h_p.h"
	@for %h in ($(GTKMM_HG_FILES:.hg=)) do @if exist ..\untracked\gtk\gtkmm\private\%h_p.h copy ..\untracked\gtk\gtkmm\private\%h_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\private\%h_p.h"
	@for %h in ($(GTKMM_HG_FILES:.hg=)) do @if exist vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\private\%h_p.h copy vs$(VSVER)\$(CFG)\$(PLAT)\gtkmm\private\%h_p.h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\private\%h_p.h"
	@for %h in ($(GTKMM_INT_EXTRA_HEADERS_P)) do @copy ..\gtk\gtkmm\%h "$(PREFIX)\include\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\gtkmm\%h"
	@copy ".\gtkmm\gtkmmconfig.h" "$(PREFIX)\lib\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\include\"
	@copy ..\tools\m4\*.m4 $(PREFIX)\share\gtkmm-$(GTKMM_MAJOR_VERSION).$(GTKMM_MINOR_VERSION)\proc\m4
