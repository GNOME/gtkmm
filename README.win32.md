Building gtkmm on Win32
=

Currently, both the mingw (native win32) gcc compiler and MS Visual
Studio 2017 and later are supported. gtkmm can be built with
mingw32-gcc using the gnu autotools (automake, autoconf, libtool) or
Meson.  A `C++17`-compliant compiler is required.

As explicitly stated in the gtk for win32 distribution
(http://www.gimp.org/win32/), the gcc compiler provided by the cygwin
distribution should not be used to build gtk/gtkmm libraries and/or
applications (see the README.win32 that comes with the gtk DLLs).
This MIGHT cause conflicts between the cygwin and msvcrt runtime
environments.

### Mingw

The mingw distribution which has been tested with this release is the
following :

* MinGW-4.1 as the base distribution.

First, make sure that you have working distribution of the native port
of both libsigc++-3.x and gtk-4.x on win32 (see
http://www.gimp.org/win32). If you can't compile a simple gtk example
using gcc and `pkg-config --cflags --libs`, you should not even think
about trying to compile gtkmm, let alone using precompiled libgtkmm
DLLs to port your gtkmm application !

#### MinGW builds using autotools

The bare mingw distribution does not provide the necessary tools (`sh`, `perl`, 
`m4`, `autoconf`, `automake`, ...) to run the provided configure script "as is". One
(currently non supported) solution is to use mingw in conjunction with msys,
which is readily available on the mingw website (http://www.mingw.org/).

The preferred method is to combine the cygwin distribution (for the unix tools
that were mentioned above) with mingw by making sure that the mingw
tools (`gcc`, `ld`, `dlltool`, ...) are called first.

The configure script can then be called using (as an example) the
following options

```
./configure --prefix=/target --build=i386-pc-mingw32 --disable-static

make
make check
make install
```

#### Meson with MinGW
The standard Meson build instructions for *NIX should work, although it
is untested at the time of writing.  Please see `README.md` for more details.


### MS Visual Studio 2017 or later

#### Building using NMake
In a Visual Studio command prompt, navigate to the `MSVC_NMake` directory.
Run `nmake /f Makefile.vc CFG=[release|debug]` to build the gtkmm DLL.
If a prefix other than `$(srcroot)\..\vs$(VSVER)\$(Platform)` is desired,
pass in `PREFIX=$(your_prefix)` in the NMake command line.  In order to build the 
gtkmm demo program, the `glib-compile-resources` tool needs to reside in 
`$(PREFIX)\bin`, or it must be specified via passing in 
`GLIB_COMPILE_RESOURCES=...`  in the NMake command line.

If using C++ dependencies that are built with Meson, specify `USE_MESON_LIBS=1`
in your NMake command line.

The following list lists the `$(VSVER)` and the `vc1xx` in the NMake-built DLL
and .lib that corresponds to the Visual Studio version used
(Visual Studio versions at or before 2015 are not supported):
  * 2017: `15`, `gtkmm-vc141-4_0.[dll|pdb|lib]`
  * 2019: `16`, `gtkmm-vc142-4_0.[dll|pdb|lib]`
  * 2022: `17`: `gtkmm-vc143-4_0.[dll|pdb|lib]`
  * 2026: `18`: `gtkmm-vc145-4_0.[dll|pdb|lib]`

For Meson, the DLL/PDB filenames and .lib filenames will be like:
  * 2017: `gtkmm-vc141-4.0-0.[dll|pdb]`, `gtkmm-vc141-4.0.lib`
  * 2019: `gtkmm-vc142-4.0-0.[dll|pdb]`, `gtkmm-vc142-4.0.lib`
  * 2022: `gtkmm-vc143-4.0-0.[dll|pdb]`, `gtkmm-vc143-4.0.lib`
  * 2026: `gtkmm-vc145-4.0-0.[dll|pdb]`, `gtkmm-vc145-4.0.lib`

Notice that this is no longer always the `vc$(VSVER)0` that was used before, to be consistent with other common C++ libraries such as Boost.
Earlier gtkmm versions may still use the former `vc$(VSVER)0` naming scheme, so for 
situations like where rebuilding code using gtkmm became
inconvenient, a `USE_COMPAT_LIBS=1` NMake option is provided to use the older naming scheme.
(or use `-Dmsvc14x-parallel-installable=false` in the Meson configure command line
to avoid having the toolset version in the final DLL and .lib filenames);
again, this is only recommended if it is inconvenient to re-build the
dependent code.

For the NMake builds, the following targets are supported:

  * `all` (or no target specified): Build the gtkmm DLL and .lib and the gtkmm
demo program
  * `tests`: Build the test programs for gtkmm.
  * `install`: Copy the built gtkmm DLL, .lib and headers with the gtkmm demo
program to appropriate locations under `$(PREFIX)`.
  * `clean`: Remove all the built files.  This includes the generated sources
if building from a GIT checkout, as noted below.

There are also some options that are supported when building with NMake, use as needed:

 * USE_COMPAT_LIBS: Set this to `1` to use the old `vc140` naming scheme. Use only if
necessary or when rebuilding code using pangomm is inconvenient.
 * BASE_INCLUDEDIR: Base directory where headers of needed libraries can be found,
the default is `$(PREFIX)\include`; can be overridden with [DEP]_INCLUDEDIR as needed,
as noted below. See [DEP]_INCLUDEDIR for more info.
 * BASE_LIBDIR: Base directory where .lib's of needed libraries can be found as well as
their architecture-dependent headers, the default is `$(PREFIX)\lib`; can be overridden
with [DEP]_LIBDIR as needed, as noted below. See [DEP]_LIBDIR for more info.
 * [DEP]_INCLUDEDIR: Base directory where headers of [DEP] may be found, default is
`$(BASE_INCLUDEDIR)`; do not include the subdirectory of the headers here, i.e. use
`GLIB_INCLUDEDIR=<some_dir>` where the GLib headers are under `<some_dir>\glib-2.0`,
and so on. [DEP] includes GTK, GDK_PIXBUF, PANGO, PANGOMM, GLIB, GLIBMM, CAIRO, CAIROMM,
HARFBUZZ, GRAPHENE, FONTCONFIG, FREETYPE, EPOXY and SIGC.
(notice that HarfBuzz headers, and possibly FreeType/FontConfig headers are being
included in the process). Use as needed.
 * [DEP]_LIBDIR: Base directory where .lib's and architecture-dependent headers of [DEP]
may be found, default is `$(BASE_LIBDIR)`; do not include the subdirectory where the
architecture-dependent headers are, i.e. use `GLIB_LIBDIR=<some_dir>` where the GLib
architecture-dependent headers (`glibconfig.h`) is located under `<some_dir>\glib-2.0\include`,
and so on. [DEP] includes GTK, GDK_PIXBUF, PANGO, PANGOMM, GLIB, GLIBMM, CAIRO, CAIROMM,
GRAPHENE, EPOXY and SIGC. Use as needed.
* GMMPROC_DIR: Directory where glibmm's `gmmproc`/`generate_wrap_init.pl` m4/PERL scripts may
be found, along with their auxiliary m4/PERL scripts, for building from a GIT checkout, default
is `$(GLIBMM_LIBDIR)\glibmm-2.68\proc`. You need to ensure that `gmmproc`/`generate_wrap_init.pl`
contain the correct paths that corresponds to your system.
* GMMPROC_PANGO_DIR: Directory where the .m4 scripts from pangomm can be found, for building
from a GIT checkout,, default is `$(PANGOMM_LIBDIR)\pangomm-2.48\proc`.
* PERL, M4: Full paths to your PERL interpreter and the `m4` tool if they are not in `%PATH%`.
PERL is needed for all builds; if building from a GIT checkout, the `XML::Parser` module (that
depends on libexpat) is also required, and you are responsible for ensuring that `XML::Parser`
does indeed load in your build env. `m4` is needed if building from GIT, and it is recommended
that this `m4` is a part of your Cygwin or MSYS2/MSYS64 installation, as other UNIXy tools may
be used. As an alternative to using `M4`, you may use `UNIX_TOOLS_BINDIR` to point to the `bin`
directory of your Cygwin or MSYS2/MSYS64 installation so that `m4` and the other UNIXy tools can
can be found as well.

The NMake Makefiles now support building the pangomm libraries directly from a GIT 
checkout with a few manual steps required, namely:

  * Ensure that you have a copy of Cygwin or MSYS/MSYS64 installed, including
`m4.exe` and `sh.exe`.  You should also have a PERL for Windows installation
as well, and your `%PATH%` should contain the paths to your PERL interpreter
and the bin\ directory of your Cygwin or MSYS/MSYS64 installation, or use `PERL`,
`M4` and/or `UNIX_TOOLS_BINDIR` as noted above. If including these in `%PATH%`, it
is recommended that these paths are towards the end of your `%PATH%`. You need to
install the `XML::Parser` PERL module as well for your PERL installation, which
requires libexpat.

  * You may wish to pass in the directory where gmmproc and generate_wrap_init.pl
from glibmm is found, if they are not in `$(GLIBMM_LIBDIR)\glibmm-2.68\proc`, using
`GMMPROC_DIR=...` in the NMake commandline. You may also wish to pass in the directory
where the .m4 files from pangomm are located, if not in `$(PANGOMM_LIBDIR)\pangomm-2.48\proc`

  * Make a new copy of the entire source tree to some location, where the build
is to be done; then in `$(srcroot)\MSVC_NMake` run `nmake /f Makefile.vc CFG=[release|debug]`,
which will first copy and generate the following files with the proper info (this step will also
be run if the following files are not present in the unpacked source tarball):
```
$(srcroot)\MSVC_NMake\gtkmm\gdkmmconfig.h
$(srcroot)\MSVC_NMake\gtkmm\gtkmmconfig.h
$(srcroot)\MSVC_NMake\gtkmm\gtkmm.rc
```

For `gdkmmconfig.h` and `gtkmmconfig.h`, it is recommended to keep  
`GDKMM_DISABLE_DEPRECATED`, `GTKMM_DISABLE_DEPRECATED`, `GDKMM_STATIC_LIB` and
`GTKMM_STATIC_LIB` undefined unless you know what you are doing. Note that it
is generally not supported to build gtkmm as a static library with Visual Studio.

Note that to generate any of the above 3 files with NMake, a PERL installation is 
also required.

#### Building Using Meson

For building with Meson, please see `README.md` for further instructions. Please 
note that using `-Ddefault_library=[static|both]` for Visual Studio builds is not 
supported and is thus not allowed.

You will need to have a working copy of glibmm-2.68, cairomm-1.16, pangomm-2.48 and
gtk-4.x's pkg-config files, which point to the corresponding locations of its 
headers and .lib's and the headers and .lib's of all of its dependencies. You will 
need to set `%LIB%` to include the location where
`glibmm_generate_extra_defs-vc14[x]-2.68.lib` from glibmm is, if not already in
there, preferably to the start of your `%LIB%`. pangomm-2.48, glibmm-2.68 and 
cairomm-1.16 refer to the C++17 branches of pangomm, glibmm and cairomm,
where they refer to pangomm-2.48.x, glibmm-2.68.x and cairomm-1.16.x
(and later branches, including their master/main branches) respectively.

When building with Meson, if building from a GIT checkout or if building with 
`maintainer-mode` enabled, you will also need a PERL interpreter and the `m4.exe` 
and `sh.exe` from Cygwin or MSYS/MSYS64, and you will need to also install Doxygen,
LLVM (likely needed by Doxygen) and GraphViz unless you pass in 
`-Dbuild-documentation=false` in your Meson configure command line.  You will still
need to have `mm-common` installed with its `bin` directory in your `%PATH%`, along
with the `gmmproc` and `proc/m4` items from pangomm and glibmm, which will be found
with `pkg-config`.

The Ninja build tool is also required if not using
`--backend=[vs2017|vs2019|vs2022]` in the Meson
command line, as noted towards the end of this section.

Note that `debug` builds should only be used against dependencies that are built
as debug builds, and `release`and `debugoptimized` should be only used against
dependencies that are built as `release` or `debugoptimized`.  On Visual Studio
builds in Meson, `debugoptimized` is roughly equivilant to a Release build with
.PDB files enabled, perhaps with some debugging features that are specific to the
respective packages.

### Gtkmm methods and signals not available on win32

All gtkmm methods and signals are available on win32.

### Gtkmm examples and demos on win32

All demos and examples compile/run on win32

