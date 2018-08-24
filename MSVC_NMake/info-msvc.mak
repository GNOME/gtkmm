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
	@echo A 'tests' target is supported to build the gtkmm's test programs.
	@echo ======
	@echo.
