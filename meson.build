# This file is part of gtkmm.

# The resource compiler, used in demos/gtk-demo, requires a C compiler.
project('gtkmm', 'c', 'cpp',
  version: '4.20.0',
  license: 'LGPL-2.1-or-later',
  default_options: [
    'cpp_std=c++17',
    'warning_level=1',
  ],
  meson_version: '>= 0.62.0', # required for variables in pkgconfig.generate()
)

gtkmm_api_version = '4.0'
gtkmm_pcname = meson.project_name() + '-' + gtkmm_api_version

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
libtool_soversion = [0, 0, 0]
gtkmm_libversion = '@0@.@1@.@2@'.format(
  libtool_soversion[0] - libtool_soversion[2],
  libtool_soversion[2],
  libtool_soversion[1]
)
macos_darwin_versions = [
  libtool_soversion[0] + 1,
  '@0@.@1@'.format(libtool_soversion[0] + 1, libtool_soversion[1])
]

# Source and build root directories of the current (sub)project.
project_source_root = meson.project_source_root()
project_build_root = meson.project_build_root()

c_compiler = meson.get_compiler('c')
cpp_compiler = meson.get_compiler('cpp')
is_msvc = cpp_compiler.get_id() == 'msvc'
is_host_windows = host_machine.system() == 'windows'

# Use the Python installation that Meson uses. Its version is >= 3.7.
python3 = import('python').find_installation()

# Do we build from a git repository?
# Suppose we do if and only if the meson.build file is tracked by git.
cmd_py = '''
import shutil, subprocess, sys
git_exe = shutil.which('git')
if not git_exe:
  sys.exit(1)
cmd = [ git_exe, 'ls-files', '--error-unmatch', 'meson.build' ]
sys.exit(subprocess.run(cmd, cwd=sys.argv[1], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL).returncode)
'''
is_git_build = run_command(
  python3, '-c', cmd_py,
  project_source_root,
  check: false,
).returncode() == 0

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
  cpp_warnings = get_option('dist-warnings')
else
  cpp_warnings = get_option('warnings')
endif
if get_option('warning_level') in ['0','1','2','3','4','5']
  warning_level = get_option('warning_level').to_int()
else
  # For instance get_option('warning_level') == 'everything'
  warning_level = 99
endif
werror = get_option('werror')
build_deprecated_api = get_option('build-deprecated-api')
build_documentation_opt = get_option('build-documentation')
build_documentation = build_documentation_opt == 'true' or \
                     (build_documentation_opt == 'if-maintainer-mode' and maintainer_mode)
build_demos = get_option('build-demos')
build_tests = get_option('build-tests')

# When a dist tarball is being built and the environment variable GTKMM_NO_DIST_TESTS
# is set, tests are not run by 'meson dist' even if they are built.
run_tests = build_tests
if run_tests and is_dist_check
  cmd_py = '''
import os, sys
sys.exit(0 if os.getenv('GTKMM_NO_DIST_TESTS') == None else 1)
'''
  run_tests = run_command(
    python3, '-c', cmd_py,
    check: false,
  ).returncode() == 0
  if not run_tests
    message('Test programs will be built but not run.')
  endif
endif

# Installation directories are relative to {prefix}.
install_prefix = get_option('prefix')
install_includedir = get_option('includedir')
install_libdir = get_option('libdir')
install_datadir = get_option('datadir')
install_pkgconfigdir = install_libdir / 'pkgconfig'

# Dependencies. <pkg> = gdk, gsk and gtk
# <pkg>mm_build_dep: Dependencies when building the <pkg>mm library.
# gtkmm_dep (created in gtk/gtkmm/meson.build):
#   Dependencies when using the gtkmm library.

# glibmm recently gained Meson build support, so we can try looking
# for its pkg-config files on Visual Studio as well
glibmm_req = '>= 2.75.0'

# Gtk supported pkg-config files on MSVC files for a good while, so just use that
gtk_req = '>= 4.19.4'
gtk_dep = dependency('gtk4', version: gtk_req)

cairomm_req = '>= 1.15.4'
cairomm_dep = dependency('cairomm-1.16', version: cairomm_req)

pangomm_req = '>= 2.50.0'
pangomm_dep = dependency('pangomm-2.48', version: pangomm_req)

gdk_pixbuf_req = '>= 2.35.5'
gdk_pixbuf_dep = dependency('gdk-pixbuf-2.0', version: gdk_pixbuf_req)

epoxy_req = '>= 1.2'
epoxy_dep = dependency('epoxy', version: epoxy_req, required: build_demos)

# Vulkan (optional, but needed here if GTK was built with Vulkan support for its headers)
# Uses meson's custom vulkan dependency searching. Set the VULKAN_SDK env var
# to use a custom path for the Vulkan SDK. Bugs that are found with it should
# be reported upstream and fixed.
vulkan_dep = dependency('vulkan', required: false)

# The -mm libraries do not yet have pkg-config files for MSVC builds,
# so check for them manually
glibmm_req_minor_ver = '68'

glibmm_dep = dependency('glibmm-2.@0@'.format(glibmm_req_minor_ver), version: glibmm_req)
giomm_dep = dependency('giomm-2.@0@'.format(glibmm_req_minor_ver), version: glibmm_req)

# Where to find gmmproc and generate_wrap_init.pl.
gmmproc_dir = glibmm_dep.get_variable('gmmprocdir')

gmmproc_extra_m4_dirs = [pangomm_dep.get_variable('gmmprocm4dir')]

gdkmm_build_dep = [giomm_dep, gtk_dep, cairomm_dep, pangomm_dep, gdk_pixbuf_dep, vulkan_dep]
gskmm_build_dep = gdkmm_build_dep
gtkmm_build_dep = gdkmm_build_dep

gtkmm_pc_requires = [
  'giomm-2.@0@'.format(glibmm_req_minor_ver) + glibmm_req,
  'gtk4' + gtk_req,
  'cairomm-1.16' + cairomm_req,
  'pangomm-2.48' + pangomm_req,
  'gdk-pixbuf-2.0' + gdk_pixbuf_req,
]

# not Windows
if host_machine.system() != 'windows'
  # gtk4-unix-print consists of only header files (no library).
  # In gtk's source directory, those header files are stored in the same
  # directory as other gtk/gtk files. No extra directory need be searched for
  # header files, when gtk is used uninstalled.
  gtk_unix_print_dep = dependency('gtk4-unix-print',
                       required: gtk_dep.type_name() != 'internal')
  if gtk_unix_print_dep.found()
    gtkmm_build_dep += [gtk_unix_print_dep]
    gtkmm_pc_requires += ['gtk4-unix-print']
  endif
endif

if get_option('force_fallback_for').contains('mm-common')
  # Make sure find_program('mm-common-get') finds the command in the subproject.
  # Use --force-fallback-for=mm-common if you want the latest mm-common version
  # in the git repository.
  mm_common_sub = subproject('mm-common')
endif

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
doxygen = find_program('doxygen', required: build_documentation)
dot = find_program('dot', required: build_documentation) # Used by Doxygen
xsltproc = find_program('xsltproc', required: build_documentation)

# Script files copied to 'untracked' by mm-common-get.
script_dir = project_source_root / 'untracked' / 'build_scripts'
generate_binding_py = script_dir / 'generate-binding.py'
doc_reference_py = script_dir / 'doc-reference.py'
dist_changelog_py = script_dir / 'dist-changelog.py'
dist_build_scripts_py = script_dir / 'dist-build-scripts.py'

if maintainer_mode
  # Copy files to untracked/build_scripts and untracked/doc.
  run_command(mm_common_get, '--force', script_dir,
    project_source_root / 'untracked' / 'docs',
    check: true,
  )
elif not import('fs').is_file(generate_binding_py)
  error('Missing files in untracked/. You must enable maintainer-mode.')
endif

# Check if perl is required and available.
doc_perl_prop = run_command(
  python3, doc_reference_py, 'get_script_property',
  '', # MMDOCTOOLDIR is not used
  'requires_perl',
  check: false,
)
doc_requires_perl = true
if doc_perl_prop.returncode() == 0 and doc_perl_prop.stdout() == 'false'
  doc_requires_perl = false
endif

perl = find_program('perl', required: maintainer_mode or \
  (build_documentation and doc_requires_perl))

# gtkmm's own script files.
gtkmm_script_dir = project_source_root / 'tools'
dummy_header_py = gtkmm_script_dir / 'dummy-header.py'

# Include Visual Studio toolset version in DLL/.lib file names
# in Visual Studio 2017 and later (enabled by default)
use_msvc14x_toolset_ver = get_option('msvc14x-parallel-installable')
msvc14x_toolset_ver = ''

if is_msvc
  add_project_arguments(cpp_compiler.get_supported_arguments([ '/utf-8', '/wd4828']), language: ['cpp','c'])

  if use_msvc14x_toolset_ver
    if cpp_compiler.version().version_compare('>=19.30')
      msvc14x_toolset_ver = '-vc143'
    elif cpp_compiler.version().version_compare('>=19.20')
      msvc14x_toolset_ver = '-vc142'
    elif cpp_compiler.version().version_compare('>=19.10')
      msvc14x_toolset_ver = '-vc141'
    endif
  endif
endif

gtkmm_libname = meson.project_name() + msvc14x_toolset_ver + '-' + gtkmm_api_version

# Set compiler warnings.
# Meson warns if any of the /W1, /W2, /W3, /W4, /Wall, -Wall, -Wextra, -Werror
# compiler options are added with add_project_arguments().
# Avoid such warnings, when possible.
# See _warn_about_builtin_args() in meson/mesonbuild/interpreter/interpreter.py.
warning_flags = []
if cpp_warnings == 'min'
  if warning_level == 0
    warning_flags = is_msvc ? ['/W2'] : ['-Wall']
  endif
elif cpp_warnings == 'max' or cpp_warnings == 'fatal'
  if warning_level < 3
    warning_flags = is_msvc ? ['/W4'] : ['-pedantic', '-Wall', '-Wextra']
  endif
  if not is_msvc
    warning_flags += '-Wformat-security -Wsuggest-override -Wshadow -Wno-long-long'.split()
  endif
  if cpp_warnings == 'fatal'
    if not werror
      warning_flags += is_msvc ? ['/WX'] : ['-Werror']
    endif
    deprecations = 'G PANGO GDK GDK_PIXBUF GSK GTK GLIBMM GIOMM PANGOMM CAIROMM SIGCXX'.split()
    foreach d : deprecations
      warning_flags += '-D@0@_DISABLE_DEPRECATED'.format(d)
    endforeach
  endif
endif

warning_flags = cpp_compiler.get_supported_arguments(warning_flags)
add_project_arguments(warning_flags, language: 'cpp')

# Don't warn about a long string in a C file.
# gnome.compile_resources() generates such a file.
c_warning_flags = is_msvc ? [] : ['-Wno-overlength-strings']
add_project_arguments(c_compiler.get_supported_arguments(c_warning_flags), language: 'c')

gui_app_ldflags = []

# MSVC: Ignore warnings that aren't really harmful, but make those
#       that should not be overlooked stand out.  For gtkmm applications
#       where we do not want a console window to show up with Visual Studio
#       builds, we must use '-entry:mainCRTStartup' in the linker flags,
#       otherwise the program will fail to link unless we defined a WinMain()
#       for them
if is_msvc
  disable_warnings_list = [
    '/FImsvc_recommended_pragmas.h', # Turn off harmless warnings but make potentially
                                     # dangerous ones glaring, distributed with GLib
    '/EHsc',  # avoid warnings caused by exception handling model used
    '/wd4152', # nonstandard extension, function/data pointer conversion in expression
    '/wd4201', # warning C4201: nonstandard extension used: nameless struct/union
    '/wd4245', # 'argument': conversion from 'int' to 'guint', signed/unsigned mismatch
    '/wd4250', # 'class1' : inherits 'class2::member' via dominance
    '/wd4702', # unreachable code
    '/wd4706', # assignment within conditional expression
    '/wd4805' # unsafe mix of type 'type' and type 'type' in operation
  ]
  if host_machine.cpu_family() == 'x86_64' or host_machine.cpu_family() == 'aarch64'
  # 'var' : conversion from 'size_t' to 'type', possible loss of data (applies on 64-bit builds)
    disable_warnings_list += '/wd4267'
  endif
  add_project_arguments(
    cpp_compiler.get_supported_arguments(disable_warnings_list),
    language: ['cpp', 'c']
  )
  gui_app_ldflags += '-entry:mainCRTStartup'
endif

subdir('tools/extra_defs_gen')
subdir('gdk')
subdir('MSVC_NMake/gdkmm')
subdir('gdk/gdkmm')
subdir('gsk')
subdir('MSVC_NMake/gskmm')
subdir('gsk/gskmm')
subdir('gtk')
subdir('MSVC_NMake/gtkmm')
subdir('gtk/gtkmm')
subdir('tests')
subdir('demos/gtk-demo')
subdir('docs/reference')

# Add a ChangeLog file to the distribution directory.
meson.add_dist_script(
  python3, dist_changelog_py,
  project_source_root,
)

# Don't distribute these files and directories.
dont_distribute = [
  'docs' / 'tutorial.moved_to_gtkmm_documentation_module',
  'examples.moved_to_gtkmm_documentation_module',
  'win32_installer',
  'gtkmm.doap',
  '.gitlab-ci.yml',
]
# Add build scripts to the distribution directory, and delete .gitignore
# files and an empty $MESON_PROJECT_DIST_ROOT/build/ directory.
meson.add_dist_script(
  python3, dist_build_scripts_py,
  project_source_root,
  'untracked' / 'build_scripts',
  dont_distribute,
)

if meson.is_subproject()
  pkgconfig_vars = {
    'gmmprocm4dir': project_source_root / 'tools' / 'm4',
    'htmlrefdir': install_prefix / install_docdir / 'reference' / 'html',
    'htmlrefpub': 'https://gnome.pages.gitlab.gnome.org/' + meson.project_name(),
  }
  if build_documentation
    pkgconfig_vars += {'doxytagfile': tag_file.full_path()}
    # May be used in a main project.
    global_tag_file_target = tag_file
  endif
  gtkmm_dep = declare_dependency(
    dependencies: gtkmm_own_dep,
    variables: pkgconfig_vars,
  )

  # A main project that looks for gtkmm_pcname.pc shall find gtkmm_dep.
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

summary = [
  '',
  '------',
  meson.project_name() + ' ' + meson.project_version(),
  '',
  '         Maintainer mode: @0@@1@'.format(maintainer_mode_opt, real_maintainer_mode),
  '       Compiler warnings: @0@ (warning_level: @1@, werror: @2@)'. \
                             format(cpp_warnings, warning_level, werror),
  '    Build deprecated API: @0@'.format(build_deprecated_api),
  'Build HTML documentation: @0@@1@'.format(build_documentation_opt, real_build_documentation),
  '     Build demo programs: @0@'.format(build_demos),
  '     Build test programs: @0@'.format(build_tests),
  'Directories:',
  '                  prefix: @0@'.format(install_prefix),
  '              includedir: @0@'.format(install_prefix / install_includedir),
  '         includegtkmmdir: @0@'.format(install_prefix / install_includedir / gtkmm_pcname),
  '                  libdir: @0@'.format(install_prefix / install_libdir),
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
