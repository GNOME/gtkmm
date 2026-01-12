# NMake Makefile portion for displaying config info

all-build-info:
	@echo.
	@echo ----------
	@echo Build info
	@echo ---------
	@echo Build Type: $(CFG)
	@echo Enabled Deprecated APIs: $(ENABLED_DEPRECATED)

help:
	@echo.
	@echo ============================
	@echo Building gtkmm Using NMake
	@echo ============================
	@echo nmake /f Makefile.vc CFG=[release^|debug] ^<option1=xxx option2=xxx^>
	@echo.
	@echo Where:
	@echo ------
	@echo CFG: Required, use CFG=release for an optimized build and CFG=debug
	@echo for a debug build.  PDB files are generated for all builds.
	@echo.
	@echo Options include:
	@echo ----------------
	@echo PREFIX: Optional, the path where dependent libraries and tools may be
	@echo found, default is $$(srcrootdir)\..\vs$$(short_vs_ver)\$$(platform),
	@echo where $$(short_vs_ver) is 14 for VS 2015 and so on; and $$(platform)
	@echo is Win32 for 32-bit builds and x64 for x64 builds.
	@echo.
	@echo USE_MESON_LIBS: Use this (USE_MESON_LIBS=1) if linking to Meson-built
	@echo variants of glibmm, pangomm and libsigc++ is desired.
	@echo By using this option, pangomm, atkmm and cairomm
	@echo should be linked to the Meson-built variants of
	@echo glibmm and libsigc++ as well.
	@echo.
	@echo BASE_INCLUDEDIR: Base directory to the headers of the various dependencies
	@echo that are used to build gtkmm, except Vulkan, which is listed below. This can
	@echo be overridden with [DEP]_INCLUDEDIR for individual dependencies, as described
	@echo below. Default is $$(PREFIX)\include.
	@echo.
	@echo BASE_LIBDIR: Base directory to the .lib's and architecture-dependent headers
	@echo of the various dependencies that are used to build gtkmm. This can be overridden
	@echo with [DEP]_LIBDIR for individual dependencies, as described below. Default
	@echo is $$(PREFIX)\lib.
	@echo.
	@echo BASE_TOOLSDIR: Base directory to the binary programs that are needed to build
	@echo gtkmm. Default is $$(PREFIX)\bin.
	@echo.
	@echo [DEP]_INCLUDEDIR: Base directory to the headers of [DEP], default is
	@echo $$(BASE_INCLUDEDIR). [DEP] includes GTK, PANGOMM, GDK_PIXBUF, PANGO, ATKMM,
	@echo GLIBMM, CAIROMM, SIGC, CAIRO, ATK, HARFBUZZ, FONTCONFIG, FREETYPE, GLIB and
	@echo EPOXY. Note that if there is a subdir for the dependency in the include
	@echo directory, it will be searched for, e.g. $$(GLIB_INCLUDEDIR)\glib-2.0 will
	@echo be searched for the GLib headers.
	@echo.
	@echo [DEP]_LIBDIR: Base directory to the .lib's and possibly architecture-dependent
	@echo headers of [DEP], default is $$(BASE_LIBDIR). [DEP] includes GTK, PANGOMM,
	@echo GDK_PIXBUF, PANGO, ATKMM, GLIBMM, CAIROMM, SIGC, CAIRO, ATK, GLIB and EPOXY.
	@echo Note that for archtecture-dependent headers, the subdir that they reside in
	@echo will be searched for, e.g. $$(GLIB_LIBDIR)\glib-2.0\include will be searched for
	@echo GLib's glibconfig.h.
	@echo.
	@echo [DEP]_BINDIR: Base directory to the binary programs of [DEP],
	@echo default is $$(BASE_TOOLSDIR). [DEP] includes GLIB; can be overridden with
	@echo an explicit path to 'glib-compile-resources' for GLIB_COMPILE_RESOURCES.
	@echo.
	@echo GMMPROC_DIR, GMMPROC_PANGO_DIR, GMMPROC_ATK_DIR: Required if building directly
	@echo from a GIT checkout. GMMPROC_DIR, GMMPROC_PANGO_DIR and GMMPROC_ATK_DIR are by
	@echo default in $$(GLIBMM_LIBDIR)\glibmm-$(GLIBMM_API_VERSION)\proc,
	@echo $$(PANGOMM_LIBDIR)\pangomm-$(PANGOMM_API_VERSION)\proc\m4 and
	@echo $$(PANGOMM_LIBDIR)\atkmm-$(ATKMM_API_VERSION)\proc\m4 respectively.
	@echo These are the path to the scripts, .m4 and PERL files from glibmm and
	@echo pangomm, which will be used to generate the source files. You need to
	@echo ensure the paths in the scripts correspond to your system's setup.
	@echo.
	@echo PERL, M4: Path to the PERL intepreter and the m4 utility program, if not in ^%PATH^%.
	@echo PERL is needed for all builds and m4 is needed if building from a GIT checkout. As
	@echo an alternative to using M4, one can use UNIX_TOOLS_BINDIR instead to point to the
	@echo directory where m4.exe is located, such as Cygwin's or MSYS2/MSYS64's 'bin' directory,
	@echo as other UNIXy tools may be used during code generation for a build from a GIT checkout.
	@echo.
	@echo DISABLE_DEPRECATED: Set to 1 to not build the deprecated APIs into
	@echo the final DLLs.
	@echo.
	@echo ======
	@echo A 'clean' target is supported to remove all generated files, intermediate
	@echo object files and binaries for the specified configuration.
	@echo.
	@echo An 'install' target is supported to copy the build (DLLs, utility programs,
	@echo LIBs, along with the introspection files if applicable) to appropriate
	@echo locations under $$(PREFIX).
	@echo.
	@echo A 'prep-git-build' target is supported for building from GIT checkouts, which
	@echo will generate gdkmm.rc, gtkmm.rc, gdkmmconfig.h and gtkmmconfig.h.  Use this target
	@echo before building any other targets when building from GIT checkouts.
	@echo.
	@echo A 'tests' target is supported to build the gtkmm's test programs.
	@echo ======
	@echo.
