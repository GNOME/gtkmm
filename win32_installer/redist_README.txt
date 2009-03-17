This directory contains files which are meant to be redistributed with
applications using gtkmm. It contains stripped versions of all GTK+ DLLs and
the MinGW-built gtkmm DLLs. The gtkmm DLLs in this directory have been
compiled using the "-O2" compiler switch whereas the ones in bin/ have been
compiled with "-O0 -g", to ease debugging.

When redistributing a MinGW-built application, use all the files from here.
When redistributing a MSVC-built application, use the GTK+ DLLs from here
(all but libsigc-*.dll, libglibmm-*.dll libgiomm-*.dll libcairomm-*.dll,
libpangomm*-.dll, libatkmm*-.dll, libgdkmm*-.dll, libgtkmm*-.dll,
libxml++-*.dll and libglademm*-.dll) and the gtkmm MSVC DLLs from bin/.
