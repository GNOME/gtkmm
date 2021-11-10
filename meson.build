# This file is part of gtkmm.

# The resource compiler, used in demos/gtk-demo, requires a C compiler.
project('gtkmm', 'c', 'cpp',
  version: '3.24.5',
  license: 'LGPLv2.1+',
  default_options: [
    'cpp_std=c++11'
  ],
  meson_version: '>= 0.54.0', # required for meson.override_dependency()
                              # and dep.get_variable(internal:)
)

gtkmm_api_version = '3.0'
gtkmm_pcname = meson.project_name() + '-' + gtkmm_api_version
gdkmm_pcname = 'gdkmm-' + gtkmm_api_version

gtkmm_version_array = meson.project_version().split('.')
gtkmm_major_version = gtkmm_version_array[0].to_int()
gtkmm_minor_version = gtkmm_version_array[1].to_int()
gtkmm_micro_version = gtkmm_version_array[2].to_int()

# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
# The relation between libtool's current:revison:age interface versioning
# and the .so filename, .so.x.y.z, is
# x = current - age
# y = age
# z = revision
# If libtool_soversion is updated as described in libtool's documentation,
# x.y.z will usually *not* be equal to meson.project_version().
libtool_soversion = [2, 0, 1]
gtkmm_libversion = '@0@.@1@.@2@'.format(
  libtool_soversion[0] - libtool_soversion[2],
  libtool_soversion[2],
  libtool_soversion[1]
)
macos_darwin_versions = [
  libtool_soversion[0] + 1,
  '@0@.@1@'.format(libtool_soversion[0] + 1, libtool_soversion[1])
]

# Use these instead of meson.source_root() and meson.build_root() in subdirectories.
# source_root() and build_root() are not useful, if this is a subproject.
project_source_root = meson.current_source_dir()
project_build_root = meson.current_build_dir()

cpp_compiler = meson.get_compiler('cpp')
is_msvc = cpp_compiler.get_id() == 'msvc'
is_host_windows = host_machine.system() == 'windows'
python3 = import('python').find_installation('python3')

python_version = python3.language_version()
python_version_req = '>= 3.5'
if not python_version.version_compare(python_version_req)
  error('Requires Python @0@, found @1@.'.format(python_version_req, python_version))
endif

# Do we build from a git repository?
# Suppose we do if and only if a '.git' directory or file exists.
cmd_py = '''
import os
import sys
sys.exit(os.path.isdir("@0@") or os.path.isfile("@0@"))
'''.format(project_source_root / '.git')
is_git_build = run_command(python3, '-c', cmd_py).returncode() != 0

# Are we testing a dist tarball while it's being built?
# There ought to be a better way. https://github.com/mesonbuild/meson/issues/6866
is_dist_check = project_source_root.contains('dist-unpack') and \
                project_build_root.contains('dist-build')

# Options.
maintainer_mode_opt = get_option('maintainer-mode')
maintainer_mode = maintainer_mode_opt == 'true' or \
                 (maintainer_mode_opt == 'if-git-build' and is_git_build)
if is_dist_check
  message('Looks like a tarball is being tested. ' + \
  'Option "dist-warnings" is used instead of "warnings".')
  warning_level = get_option('dist-warnings')
else
  warning_level = get_option('warnings')
endif
build_deprecated_api = get_option('build-deprecated-api')
build_atkmm_api = get_option('build-atkmm-api')
build_x11_api_opt = get_option('build-x11-api')
build_documentation_opt = get_option('build-documentation')
build_documentation = build_documentation_opt == 'true' or \
                     (build_documentation_opt == 'if-maintainer-mode' and maintainer_mode)
build_demos = get_option('build-demos')
build_tests = get_option('build-tests')

# Installation directories are relative to {prefix}.
install_prefix = get_option('prefix')
install_includedir = get_option('includedir')
install_libdir = get_option('libdir')
install_datadir = get_option('datadir')
install_pkgconfigdir = install_libdir / 'pkgconfig'

# Dependencies. <pkg> = gdk and gtk
# <pkg>mm_build_dep: Dependencies when building the <pkg>mm library.
# <pkg>mm_dep (created in <pkg>/<pkg>mm/meson.build):
#   Dependencies when using the <pkg>mm library.

# glibmm recently gained Meson build support, so we can try looking
# for its pkg-config files on Visual Studio as well
glibmm_req = '>= 2.54.0'

# Gtk supported pkg-config files on MSVC files for a good while, so just use that
gtk_req = '>= 3.24.0'
gtk_dep = dependency('gtk+-3.0', version: gtk_req)

cairomm_req = '>= 1.12.0'
cairomm_dep = dependency('cairomm-1.0', version: cairomm_req)

pangomm_req = '>= 2.38.2'
pangomm_dep = dependency('pangomm-1.4', version: pangomm_req)

gdk_pixbuf_req = '>= 2.35.5'
gdk_pixbuf_dep = dependency('gdk-pixbuf-2.0', version: gdk_pixbuf_req)

# atkmm is required in maintainer mode even if atkmm API shall not be built.
# gmmproc must be able to find atkmm's installed M4 files.
atkmm_req = '>= 2.24.2'
atkmm_dep = dependency('atkmm-1.6', version: atkmm_req, required: build_atkmm_api or maintainer_mode)

epoxy_req = '>= 1.2'
epoxy_dep = dependency('epoxy', version: epoxy_req, required: build_demos)

# The -mm libraries do not yet have pkg-config files for MSVC builds,
# so check for them manually
glibmm_req_minor_ver = '4'

glibmm_dep = dependency('glibmm-2.@0@'.format(glibmm_req_minor_ver), version: glibmm_req)
giomm_dep = dependency('giomm-2.@0@'.format(glibmm_req_minor_ver), version: glibmm_req)

# Where to find gmmproc and generate_wrap_init.pl.
gmmproc_dir = glibmm_dep.get_variable(pkgconfig: 'gmmprocdir', internal: 'gmmprocdir')

gmmproc_extra_m4_dirs = [pangomm_dep.get_variable(pkgconfig: 'gmmprocm4dir', internal: 'gmmprocm4dir')]
if atkmm_dep.found()
  gmmproc_extra_m4_dirs += [atkmm_dep.get_variable(pkgconfig: 'gmmprocm4dir', internal: 'gmmprocm4dir')]
endif

# Is X11 backend available?
if build_x11_api_opt == 'false'
  build_x11_api = false
else
  if gtk_dep.type_name() == 'internal'
    x11_enabled_in_gdk = subproject('gtk+-3.0').get_variable('x11_enabled', fallback: true)
    if x11_enabled_in_gdk != subproject('gtk+-3.0').get_variable('x11_enabled', fallback: false)
      if is_host_windows or host_machine.system() == 'darwin'
        # X11 is never supported on Windows or MacOS.
        x11_enabled_in_gdk = false
      else
        warning('Variable x11_enabled not found in gtk+-3.0. Assuming X11 backend is supported.')
      endif
    endif
  else # gtk_dep from pkgconfig
    x11_enabled_in_gdk = gtk_dep.get_variable(pkgconfig: 'targets').contains('x11')
  endif
  if build_x11_api_opt == 'if-enabled-in-gdk'
    build_x11_api = x11_enabled_in_gdk
  else # build_x11_api_opt == 'true'
    build_x11_api = true
    if not x11_enabled_in_gdk
      error('Requested X11 backend not supported by installed gdk.')
    endif
  endif
endif

gdkmm_build_dep = [giomm_dep, gtk_dep, cairomm_dep, pangomm_dep, gdk_pixbuf_dep]
gdkmm_requires = [
  'giomm-2.@0@'.format(glibmm_req_minor_ver), glibmm_req,
  'gtk+-3.0', gtk_req,
  'cairomm-1.0', cairomm_req,
  'pangomm-1.4', cairomm_req,
  'gdk-pixbuf-2.0', gdk_pixbuf_req,
]

gtkmm_build_dep = gdkmm_build_dep
gtkmm_requires = gdkmm_requires

if build_atkmm_api
  gtkmm_build_dep += [atkmm_dep]
  gtkmm_requires += ['atkmm-1.6', atkmm_req]
endif

# not Windows
if host_machine.system() != 'windows'
  # gtk+-unix-print-3.0 consists of only header files (no library).
  # In gtk's source directory, those header files are stored in the same
  # directory as other gtk/gtk files. No extra directory need be searched for
  # header files, when gtk is used uninstalled.
  gtk_unix_print_dep = dependency('gtk+-unix-print-3.0',
                       required: gtk_dep.type_name() != 'internal')
  if gtk_unix_print_dep.found()
    gtkmm_build_dep += [gtk_unix_print_dep]
  endif
  gtkmm_requires += ['gtk+-unix-print-3.0', '']
endif

gdkmm_requires = ' '.join(gdkmm_requires)
gtkmm_requires = ' '.join(gtkmm_requires)

# Some dependencies are required only in maintainer mode and/or if
# reference documentation shall be built.
mm_common_get = find_program('mm-common-get', required: false)
if maintainer_mode and not mm_common_get.found()
  message('Maintainer mode requires the \'mm-common-get\' command. If it is not found,\n' +
          'install the \'mm-common\' package, version 1.0.0 or higher.')
  # If meson --wrap-mode != forcefallback, Meson falls back to the mm-common
  # subproject only if mm-common-get is required.
  mm_common_get = find_program('mm-common-get', required: true)
endif
m4 = find_program('m4', required: maintainer_mode) # Used by gmmproc (in glibmm)
perl = find_program('perl', required: maintainer_mode or build_documentation)
doxygen = find_program('doxygen', required: build_documentation)
dot = find_program('dot', required: build_documentation) # Used by Doxygen
xsltproc = find_program('xsltproc', required: build_documentation)

# Script files copied to 'untracked' by mm-common-get.
script_dir = project_source_root / 'untracked' / 'build_scripts'
generate_binding_py = script_dir / 'generate-binding.py'
doc_reference_py = script_dir / 'doc-reference.py'
dist_changelog_py = script_dir / 'dist-changelog.py'
dist_build_scripts_py = script_dir / 'dist-build-scripts.py'
check_dllexport_usage_py = script_dir / 'check-dllexport-usage.py'

if maintainer_mode
  # Copy files to untracked/build_scripts and untracked/doc.
  run_command(mm_common_get, '--force', script_dir,
    project_source_root / 'untracked' / 'docs')
else
  cmd_py = '''
import os
import sys
sys.exit(os.path.isfile("@0@"))
'''.format(generate_binding_py)
  file_exists = run_command(python3, '-c', cmd_py).returncode() != 0
  if not file_exists
    error('Missing files in untracked/. You must enable maintainer-mode.')
  endif
endif

# gtkmm's own script files.
gtkmm_script_dir = project_source_root / 'tools'
dummy_header_py = gtkmm_script_dir / 'dummy-header.py'

# Do we build the gdkmm/gtkmm without using gendef.exe?
gdkmm_extra_gendef_cpp_args = []
gtkmm_extra_gendef_cpp_args = []

# Include Visual Studio toolset version in DLL/.lib file names
# in Visual Studio 2015 and later (enabled by default)
use_msvc14x_toolset_ver = get_option('msvc14x-parallel-installable')
msvc14x_toolset_ver = ''

if is_msvc
  add_project_arguments(cpp_compiler.get_supported_arguments([ '/utf-8', '/wd4828']), language: 'cpp')
  add_project_arguments(cpp_compiler.get_supported_arguments([ '/utf-8']), language: 'c')

  # Check for the first line in a file generated with gmmproc,
  # to see which gmmproc version was used
  if maintainer_mode
    check_gmmproc_ver_cmd = [
      python3, check_dllexport_usage_py,
      '--gmmprocdir=@0@'.format(gmmproc_dir),
    ]
  else
    check_gmmproc_ver_cmd = [
      python3, check_dllexport_usage_py,
      '--file=@0@/untracked/gtk/gtkmm/aboutdialog.h'.format('/'.join(project_source_root.split('\\')))
    ]
  endif

  # Enable __declspec(dllexport) if the gtkmm headers generated from the .hg files
  # were generated using a recent enough gmmproc
  build_shared_libs_directly = run_command(check_gmmproc_ver_cmd).returncode() == 0
  message('Using __declspec(dllexport) to build gtkmm: @0@'.format(build_shared_libs_directly ? 'YES' : 'NO'))
  if not build_shared_libs_directly
    gdkmm_extra_gendef_cpp_args += '-DGDKMM_USE_GENDEF'
    gtkmm_extra_gendef_cpp_args = gdkmm_extra_gendef_cpp_args + [ '-DGTKMM_USE_GENDEF' ]
  endif

  if use_msvc14x_toolset_ver
    if cpp_compiler.version().version_compare('>=19.30')
      msvc14x_toolset_ver = '-vc143'
    elif cpp_compiler.version().version_compare('>=19.20')
      msvc14x_toolset_ver = '-vc142'
    elif cpp_compiler.version().version_compare('>=19.10')
      msvc14x_toolset_ver = '-vc141'
    elif cpp_compiler.version().version_compare('>=19.00')
      msvc14x_toolset_ver = '-vc140'
    else
      message('Visual Studio toolset version not applied for pre-Visual Studio 2015 builds')
    endif
  endif
else
  build_shared_libs_directly = true
endif

gtkmm_libname = meson.project_name() + msvc14x_toolset_ver + '-' + gtkmm_api_version
gdkmm_libname = 'gdkmm' + msvc14x_toolset_ver + '-' + gtkmm_api_version

# Set compiler warnings.
warning_flags = []
if warning_level == 'min'
  if is_msvc
    warning_flags = ['/W3']
  else
    warning_flags = ['-Wall']
  endif
elif warning_level == 'max' or warning_level == 'fatal'
  if is_msvc
    warning_flags = ['/W4']
  else
    warning_flags = '-pedantic -Wall -Wextra -Wformat-security -Wsuggest-override -Wshadow -Wno-long-long'.split()
  endif
  if warning_level == 'fatal'
    if is_msvc
      warning_flags += ['/WX']
    else
      warning_flags += ['-Werror']
    endif
    deprecations = 'G PANGO ATK GDK GDK_PIXBUF GTK GLIBMM ATKMM PANGOMM CAIROMM SIGCXX'.split()
    foreach d : deprecations
      warning_flags += '-D@0@_DISABLE_DEPRECATED'.format(d)
    endforeach
  endif
endif

warning_flags = cpp_compiler.get_supported_arguments(warning_flags)
add_project_arguments(warning_flags, language: 'cpp')

gui_app_ldflags = []

# MSVC: Ignore warnings that aren't really harmful, but make those
#       that should not be overlooked stand out.  For gtkmm applications
#       where we do not want a console window to show up with Visual Studio
#       builds, we must use '-entry:mainCRTStartup' in the linker flags,
#       otherwise the program will fail to link unless we defined a WinMain()
#       for them
if is_msvc
  foreach wd : ['/FImsvc_recommended_pragmas.h', '/wd4267', '/EHsc', '/wd4250', '/wd4805']
    disabled_warning = cpp_compiler.get_supported_arguments(wd)
    add_project_arguments(disabled_warning, language: 'cpp')
  endforeach
  gui_app_ldflags += '-entry:mainCRTStartup'
endif

# add_dist_script() is not allowed in a subproject if meson.version() < 0.58.0.
can_add_dist_script = not meson.is_subproject() or meson.version().version_compare('>= 0.58.0')

subdir('tools/extra_defs_gen')
subdir('MSVC_NMake/gendef')
subdir('gdk')
subdir('MSVC_NMake/gdkmm')
subdir('gdk/gdkmm')
subdir('gtk')
subdir('MSVC_NMake/gtkmm')
subdir('gtk/gtkmm')
subdir('tests')
subdir('demos/gtk-demo')
subdir('docs/reference')

if can_add_dist_script
  # Add a ChangeLog file to the distribution directory.
  meson.add_dist_script(
    python3.path(), dist_changelog_py,
    project_source_root,
  )

  # Don't distribute these files and directories.
  dont_distribute = [
    'docs' / 'tutorial.moved_to_gtkmm_documentation_module',
    'examples.moved_to_gtkmm_documentation_module',
    'HACKING',
    'win32_installer',
  ]
  # Add build scripts to the distribution directory, and delete .gitignore
  # files and an empty $MESON_PROJECT_DIST_ROOT/build/ directory.
  meson.add_dist_script(
    python3.path(), dist_build_scripts_py,
    project_source_root,
    'untracked' / 'build_scripts',
    dont_distribute,
  )
endif

if meson.is_subproject()
  pkgconfig_vars = {
    'htmlrefdir': install_prefix / install_docdir / 'reference' / 'html',
    'htmlrefpub': 'http://library.gnome.org/devel/' + pkg_conf_data.get_unquoted('PACKAGE_TARNAME') + '/3.24/'
  }
  if build_documentation
    pkgconfig_vars += {'doxytagfile': tag_file.full_path()}
    # May be used in a main project.
    global_tag_file_target = tag_file
  endif
  gdkmm_dep = declare_dependency(
    dependencies: gdkmm_own_dep,
    variables: pkgconfig_vars,
  )

  pkgconfig_vars += {'gmmprocm4dir': project_source_root / 'tools' / 'm4'}
  gtkmm_dep = declare_dependency(
    dependencies: gtkmm_own_dep,
    variables: pkgconfig_vars,
  )

  # A main project that looks for gdkmm_pcname.pc and gtkmm_pcname.pc
  # shall find gdkmm_dep and gtkmm_dep.
  meson.override_dependency(gdkmm_pcname, gdkmm_dep)
  meson.override_dependency(gtkmm_pcname, gtkmm_dep)
endif

# Print a summary.
real_maintainer_mode = ''
if maintainer_mode_opt == 'if-git-build'
  real_maintainer_mode = ' (@0@)'.format(maintainer_mode)
endif

real_build_documentation = ''
if build_documentation_opt == 'if-maintainer-mode'
  real_build_documentation = ' (@0@)'.format(build_documentation)
endif

real_build_x11_api = ''
if build_x11_api_opt == 'if-enabled-in-gdk'
  real_build_x11_api = ' (@0@)'.format(build_x11_api)
endif

summary = [
  '',
  '------',
  meson.project_name() + ' ' + meson.project_version(),
  '',
  '         Maintainer mode: @0@@1@'.format(maintainer_mode_opt, real_maintainer_mode),
  '       Compiler warnings: @0@'.format(warning_level),
  '    Build deprecated API: @0@'.format(build_deprecated_api),
  '         Build atkmm API: @0@'.format(build_atkmm_api),
  '           Build X11 API: @0@@1@'.format(build_x11_api_opt, real_build_x11_api),
  'Build HTML documentation: @0@@1@'.format(build_documentation_opt, real_build_documentation),
  '     Build demo programs: @0@'.format(build_demos),
  '     Build test programs: @0@'.format(build_tests),
  'Directories:',
  '                  prefix: @0@'.format(install_prefix),
  '              includedir: @0@'.format(install_prefix / install_includedir),
  '         includegdkmmdir: @0@'.format(install_prefix / install_includedir / gdkmm_pcname),
  '         includegtkmmdir: @0@'.format(install_prefix / install_includedir / gtkmm_pcname),
  '                  libdir: @0@'.format(install_prefix / install_libdir),
  '          gdkmmconfigdir: @0@'.format(install_prefix / install_gdkmmconfigdir),
  '          gtkmmconfigdir: @0@'.format(install_prefix / install_gtkmmconfigdir),
  '                   m4dir: @0@'.format(install_prefix / install_m4dir),
  '            pkgconfigdir: @0@'.format(install_prefix / install_pkgconfigdir),
  '                 datadir: @0@'.format(install_prefix / install_datadir),
  '                  docdir: @0@'.format(install_prefix / install_docdir),
  '              devhelpdir: @0@'.format(install_prefix / install_devhelpdir),
]
if maintainer_mode
  summary += [
    '              gmmprocdir: @0@'.format(gmmproc_dir),
  ]
endif
summary += ['------']

message('\n'.join(summary))
