#! /bin/sh

# This installs MSVC-built libraries of a module such as libsigc++, glibmm or
# gtkmm into the MSVC subdirectory

if test $# -ne 4; then
	echo "install-msvc-module.sh: Invalid number of arguments";
	echo "Usage: $0 <module> <toolset> <platform> <target directory>";
	exit 1
fi

module=$1
toolset=$2
platform=$3
targetpath=$4

# Assume all the other libraries are at same point as gtkmm:
basepath=../..

# TODO: Automatically find latest version of package: First try SVN checkout, then look for latest installed tarball version.
case $module in
    libsigc++)
	# Path to extracted tarball or SVN checkout
	sourcepath="${basepath}/libsigc++2"
	# Basename of DLL
	basename='sigc'
	# Version tag of DLL name
	vername='2_0'
	# Abiname of package
	abiname='sigc++-2.0'
	# Subdirectory in MSVC_Net2005
	subdir='.'
	;;
    glibmm)
	sourcepath="${basepath}/glibmm"
	basename='glibmm'
	vername='2_4'
	abiname='glibmm-2.4'
	subdir='glibmm'
	;;
    giomm)
	sourcepath="${basepath}/glibmm"
	basename='giomm'
	vername='2_4'
	abiname='giomm-2.4'
	subdir='giomm'
	;;
    cairomm)
	sourcepath="${basepath}/cairomm"
	basename='cairomm'
	vername='1_0'
	abiname='cairomm-1.0'
	subdir='cairomm'
	;;
    pangomm)
	sourcepath="${basepath}/pangomm"
	basename='pangomm'
	vername='1_4'
	abiname='pangomm-1.4'
	subdir='pangomm'
	;;
    atkmm)
	sourcepath="${basepath}/atkmm"
	basename='atkmm'
	vername='1_6'
	abiname='atkmm-1.6'
	subdir='atkmm'
	;;
    gdkmm)
	sourcepath="${basepath}/gtkmm"
	basename='gdkmm'
	vername='2_4'
	abiname='gdkmm-2.4'
	subdir='gdkmm'
	;;
    gtkmm)
	sourcepath="${basepath}/gtkmm"
	basename='gtkmm'
	vername='2_4'
	abiname='gtkmm-2.4'
	subdir='gtkmm'
	;;
    libglademm)
	sourcepath="${basepath}/libglademm"
	basename='glademm'
	vername='2_4'
	abiname='glademm-2.4'
	subdir='libglademm'
	;;
    libxml++)
	sourcepath="${basepath}/libxml++"
	basename='xml++'
	vername='2_6'
	abiname='libxml++-2.6'
	subdir='libxml++'
	;;
    *)
	echo "Module $module not known"
	exit 1
	;;
esac

case $toolset in
    vc80)
	vcdir='MSVC_Net2005'
	;;
    vc90)
	vcdir='MSVC_Net2008'
	;;
    vc100)
        vcdir='MSVC_Net2010'
	;;
    *)
	echo "Toolset $toolset not known"
	exit 1
	;;
esac

case $platform in
    Win32)
        platformdir='Win32'
	;;
    x64)
        platformdir='x64'
	;;
    *)
        echo "Platform $platform not known"
	exit 1
	;;
esac

#echo "Source Path: $sourcepath"
#echo "Basename: $basename"
#echo "Abiname: $abiname"
#echo "Subdir: $subdir"

#targetpath=MSVC

mkdir -p "${targetpath}" || exit 1
cp "$sourcepath/$vcdir/$subdir/$platformdir/Release/${basename}-${toolset}-${vername}.dll" "$targetpath" || exit 1
cp "$sourcepath/$vcdir/$subdir/$platformdir/Debug/${basename}-${toolset}-d-${vername}.dll" "$targetpath" || exit 1
cp "$sourcepath/$vcdir/$subdir/$platformdir/Debug/${basename}-${toolset}-d-${vername}.pdb" "$targetpath" || exit 1

#mkdir -p "${targetpath}/lib" || exit 1
cp "$sourcepath/$vcdir/$subdir/$platformdir/Release/${basename}-${toolset}-${vername}.lib" "$targetpath" || exit 1
cp "$sourcepath/$vcdir/$subdir/$platformdir/Debug/${basename}-${toolset}-d-${vername}.lib" "$targetpath" || exit 1

# Configfile is used from mingw, thus commented out:
#configfile=$sourcepath/MSVC_Net2005/$subdir/*config.h
#if test -f configfile; then
#	mkdir -p $targetpath/lib/${abiname}/include/ || exit 1
#	cp $configfile $targetpath/lib/${abiname}/include/ || exit 1
#fi
