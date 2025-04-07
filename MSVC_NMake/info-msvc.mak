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
	@echo nmake /f Makefile.vc CFG=[release^|debug] ^<PREFIX=PATH^> ^<option1=xxx option2=xxx^>
	@echo.
	@echo Where:
	@echo ------
	@echo CFG: Required, use CFG=release for an optimized build and CFG=debug
	@echo for a debug build.  PDB files are generated for all builds.
	@echo.
	@echo PREFIX: Optional, the path where dependent libraries and tools may be
	@echo found, default is ^$(srcrootdir)\..\vs^$(short_vs_ver)\^$(platform),
	@echo where ^$(short_vs_ver) is 15 for VS 2017 and so on; and
	@echo ^$(platform) is Win32 for 32-bit builds and x64 for x64 builds.
	@echo.
	@echo USE_MESON_LIBS: Use this if linking to Meson-built
	@echo variants of glibmm, pangomm and libsigc++ is desired.
	@echo By using this option, pangomm and cairomm should be linked to the
	@echo Meson-built variants of glibmm and libsigc++ as well.
	@echo.
	@echo GMMPROC_DIR, GMMPROC_PANGO_DIR:
	@echo Required if building directly from a GIT checkout,
	@echo or re-generating the source files from the .hg/.ccg
	@echo files.  GMMPROC_PANGO_DIR is by default in
	@echo ^$(GMMPROC_DIR)/../../pangomm-$(PANGOMM_MAJOR_VERSION).$(PANGOMM_MINOR_VERSION)/proc/m4.
	@echo PERL with XML::Parser and some common *nix  commands
	@echo are required, as well as the .m4 and PERL files from
	@echo glibmm and pangomm, which will be used by gmmproc.
	@echo ------
	@echo Possible options include the following:
	@echo.
	@echo DISABLE_DEPRECATED: Set to 1 to not build the deprecated APIs into
	@echo the final DLLs.
	@echo.
	@echo VULKAN_SDK_DIR: Path to the base installation directory of the LunarG
	@echo Vulkan SDK.  This may be necessary if the gtk+-4.x DLLs are built with
	@echo Vulkan enabled, so that Vulkan's headers and libraries could be found.
	@echo.
	@echo ======
	@echo A 'clean' target is supported to remove all generated files, intermediate
	@echo object files and binaries for the specified configuration.
	@echo.
	@echo An 'install' target is supported to copy the build (DLLs, utility programs,
	@echo LIBs, along with the introspection files if applicable) to appropriate
	@echo locations under ^$(PREFIX).
	@echo.
	@echo A 'prep-git-build' target is supported for building from GIT checkouts, which
	@echo will generate gtkmm.rc and g[d^|s^|t]kmmconfig.h.  Use this target
	@echo before building any other targets when building from GIT checkouts.
	@echo.
	@echo A 'tests' target is supported to build the gtkmm's test programs.
	@echo ======
	@echo.
