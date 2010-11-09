#!/bin/sh

if test $# -ne 1; then
	echo "build-installer.sh: Invalid number of arguments"
	echo "Usage: $0 <platform>"
	exit 1
fi

platform=$1
case $platform in
	win32)
		msvc_platform=Win32
		;;
	win64)
		msvc_platform=x64
		;;
	*)
		echo "Unknown platform: $platform"
		echo "Known platforms are 'win32' and 'win64'"
		exit 1
		;;
esac

echo "This builds the development and runtime installers for gtkmm. Make "
echo "sure to have everything (libsigc++, glibmm, cairomm, pangomm, gtkmm, "
echo "libglademm, libxml++) installed to /$platform/gtkmm_debug and "
echo "$/$platform/gtkmm_release, respectively and to have successfully built "
echo "everything with MSVC 2005, MSVC 2008 and MSVC 2010 (both $msvc_platform "
echo "Debug and $msvc_platform Release builds). Make also sure that the "
echo "official GTK+ bundle has been unzipped to /$platform/bundle, libxml2 "
echo "into /$platform/libxml2 and iconv runtime and development files into "
echo "/$platform/iconv Install libglade into /$platform/libglade. Finally, "
echo "make sure that makensis is in your PATH"

echo "Cleanup..."
rm -Rf bin lib share include etc MSVC demo bin_stripped

echo "Copying mingw files..."
cp -R /$platform/gtkmm_debug/bin . || exit 1
cp -R /$platform/gtkmm_debug/lib . || exit 1
cp -R /$platform/gtkmm_debug/share . || exit 1
cp -R /$platform/gtkmm_debug/include . || exit 1

# Same with /bundle, for GTK+
cp -R /$platform/bundle/bin . || exit 1
cp -R /$platform/bundle/lib . || exit 1
cp -R /$platform/bundle/share . || exit 1
cp -R /$platform/bundle/include . || exit 1
cp -R /$platform/bundle/etc . || exit 1

# libgcc runtime
cp /$platform/mingw/bin/libgcc_s_sjlj-1.dll bin || exit 1

# TODO: iconv

# libxml2
cp -R /$platform/libxml2/bin . || exit 1
cp -R /$platform/libxml2/include . || exit 1
cp -R /$platform/libxml2/lib . || exit 1
cp -R /$platform/libxml2/share . || exit 1

# libglade
cp -R /$platform/libglade/bin . || exit 1
cp -R /$platform/libglade/include . || exit 1
cp -R /$platform/libglade/lib . || exit 1
cp -R /$platform/libglade/share . || exit 1

# The license text in the installer
cp ../COPYING lgpl.txt

echo "Removing non-GTK locales..."
# Remove all locales we don't want, so the installer can simply copy share/locale recursively, in case there is more than just the GTK+ bundle in /bundle.
find share/locale -type f | grep -v libiconv.mo | grep -v glib20.mo | grep -v gtk20.mo | grep -v gtk20-properties.mo | xargs -r rm || exit -1
find share/locale -type d | xargs rmdir -p --ignore-fail-on-non-empty || exit -1

# Change prefix in .pc files to be /target instead of /usr/local. pkg-config
# then looks relative to the .pc file for the actual package.

# TODO: If someone knows how to do this more elegant, please tell me
# (armin@arbur.net). Note that perl -i does _not_ work on Windows (at least
# not with the msys one).
echo "Fixing pkg-config prefixes..."
mkdir -p temp || exit 1
for file in lib/pkgconfig/*.pc; do
	perl -pe 's/prefix=\/usr\/local/prefix=\/target/' $file > temp/`basename $file` || exit 1
done

for file in temp/*.pc; do
	mv $file lib/pkgconfig/`basename $file` || exit 1
done
rmdir temp

# Use the MS-Windows theme by default
echo "Setting GTK theme..."
echo "gtk-theme-name = \"MS-Windows\"" > etc/gtk-2.0/gtkrc || exit 1

# Strip DLLs for the runtime version
echo "Stripping binaries..."
mkdir -p bin_stripped || exit -1
cp -R bin/* bin_stripped || exit 1
# Use the gtkmm release binaries (they have been compiled with -O2 instead of -O0)
cp -R /$platform/gtkmm_release/bin* bin_stripped || exit 1
/$platform/mingw/bin/strip bin_stripped/*.dll || exit 1
/$platform/mingw/bin/strip bin_stripped/*.exe || exit 1

# TODO: Strip modules in lib/gtk-2.0?
# TODO: Strip .dll.a files with --strip-unneeded

# Get the MSVC files into here
echo "Copying MSVC files..."
for module in libsigc++ glibmm giomm cairomm pangomm atkmm gdkmm gtkmm libglademm libxml++; do
	for toolset in vc80 vc90 vc100; do
		./install-msvc-module.sh $module $toolset $msvc_platform MSVC || exit 1
	done
done

if test $platform = 'win32'; then
	cp gtkmm-vc80-2_4.vsprops MSVC || exit 1
	cp gtkmm-vc90-2_4.vsprops MSVC || exit 1
	cp gtkmm-vc100-2_4.props MSVC || exit 1
	cp gtkmm-vc80-d-2_4.vsprops MSVC || exit 1
	cp gtkmm-vc90-d-2_4.vsprops MSVC || exit 1
	cp gtkmm-vc100-d-2_4.props MSVC || exit 1
else
	perl -pe 's/GTKMM_BASEPATH/GTKMM64_BASEPATH/g; s/Win32/x64/' gtkmm-vc80-2_4.vsprops > MSVC/gtkmm-vc80-2_4.vsprops || exit 1
	perl -pe 's/GTKMM_BASEPATH/GTKMM64_BASEPATH/g; s/Win32/x64/' gtkmm-vc90-2_4.vsprops > MSVC/gtkmm-vc90-2_4.vsprops || exit 1
	perl -pe 's/GTKMM_BASEPATH/GTKMM64_BASEPATH/g; s/Win32/x64/' gtkmm-vc100-2_4.props > MSVC/gtkmm-vc100-2_4.props || exit 1
	perl -pe 's/GTKMM_BASEPATH/GTKMM64_BASEPATH/g; s/Win32/x64/' gtkmm-vc80-d-2_4.vsprops > MSVC/gtkmm-vc80-d-2_4.vsprops || exit 1
	perl -pe 's/GTKMM_BASEPATH/GTKMM64_BASEPATH/g; s/Win32/x64/' gtkmm-vc90-d-2_4.vsprops > MSVC/gtkmm-vc90-d-2_4.vsprops || exit 1
	perl -pe 's/GTKMM_BASEPATH/GTKMM64_BASEPATH/g; s/Win32/x64/' gtkmm-vc100-d-2_4.props > MSVC/gtkmm-vc100-d-2_4.props || exit 1
fi

# Compatibility with old naming scheme (TODO: drop for gtkmm3)
cp gtkmm-vc80-2_4.vsprops MSVC/gtkmm-2.4.vsprops || exit 1
cp gtkmm-vc80-d-2_4.vsprops MSVC/gtkmm-2.4d.vsprops || exit 1

echo "Copying gtk-demo..."
mkdir -p demo || exit 1
cp -R /home/Armin/gtkmmdemoinst/$platform/* demo/ || exit 1

echo "Creating installer..."

# Prepare installer script for 64 bit
if test $platform = 'win64'; then
	perl -pe 's/PRODUCT_PLATFORM_NAME "gtkmm"/PRODUCT_PLATFORM_NAME "gtkmm64"/; s/PRODUCT_FULLNAME "gtkmm Development Environment"/PRODUCT_FULLNAME "gtkmm Development Environment (x64)"/; s/PRODUCT_FULLNAME "gtkmm Runtime Environment"/PRODUCT_FULLNAME "gtkmm Runtime Environment (x64)"/; s/win32-runtime/win64-runtime/; s/win32-devel/win64-devel/; s/MUI_STARTMENUPAGE_DEFAULTFOLDER "Gtkmm"/MUI_STARTMENUPAGE "Gtkmm (x64)"/; s/PRODUCT_SMNAME "Gtkmm"/PRODUCT_SMNAME "Gtkmm (x64)"/; s/\$ICONS_GROUP "Gtkmm"/\$ICONS_GROUP "Gtkmm (x64)"/; s/\$PROGRAMFILES/\$PROGRAMFILES64/; s/GTKMM_BASEPATH/GTKMM64_BASEPATH/g; s/intl.dll$/libintl-8.dll/; s/freetype6.dll/libfreetype-6.dll/; s/gspawn-win32-helper.exe/gspawn-win64-helper.exe/; s/gspawn-win32-helper-console.exe/gspawn-win64-helper-console.exe/; s/cairo_1.10.0-1_win32/cairo_1.10.0-1_win64/' gtkmm-installer.nsi > gtkmm-installer.nsi.run || exit 1
else
	cp gtkmm-installer.nsi gtkmm-installer.nsi.run
fi

makensis gtkmm-installer.nsi.run || exit 1

echo "Creating runtime installer..."
perl -pe 's/; !define RUNTIME_ONLY 1/!define RUNTIME_ONLY 1/' gtkmm-installer.nsi.run > gtkmm-runtime-installer.nsi.run || exit 1
makensis gtkmm-runtime-installer.nsi.run || exit 1
