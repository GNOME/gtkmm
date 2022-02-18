# gdk/gdkmm

# Input: gdkmm_build_dep, gdkmm_pcname, maintainer_mode, project_source_root,
#        generate_binding_py, m4_files, gtkmm_libversion, install_includedir,
#        python3, gdkmm_rc, dummy_header_py, gmmproc_dir, build_shared_libs_directly,
#        build_deprecated_api, gmmproc_extra_m4_dirs, is_host_windows,
#        gdkmm_extra_gendef_cpp_args, gdkmm_libname, macos_darwin_versions,
#        can_add_dist_script
# Output: gdkmm_hg_ccg_basenames, gdkmm_extra_h_files, built_files_root,
#         gdkmm_built_h_file_targets, gdkmm_used_built_h_file_targets, gdkmm_own_dep

gdkmm_defs_basefiles = [
  'gdk.defs',
  'gdk_enums.defs',
  'gdk_extra.defs',
  'gdk_extra_objects.defs',
  'gdk_methods.defs',
  'gdk_pixbuf_enums.defs',
  'gdk_pixbuf_methods.defs',
  'gdk_signals.defs',
  'gdk_docs.xml',
  'gdk_docs_override.xml',
]

gdkmm_defs_files = []
foreach file : gdkmm_defs_basefiles
  gdkmm_defs_files += '..' / 'src' / file
endforeach

# Generated from pairs of .hg and .ccg files.
gdkmm_any_hg_ccg_basenames = [
  'applaunchcontext',
  'cursor',
  'device',
  'devicemanager',
  'display',
  'displaymanager',
  'dragcontext',
  'drawingcontext',
  'event',
  'frameclock',
  'frametimings',
  'glcontext',
  'monitor',
  'pixbuf',
  'pixbufanimation',
  'pixbufanimationiter',
  'pixbufformat',
  'pixbufloader',
  'rectangle',
  'rgba',
  'screen',
  'seat',
  'timecoord',
  'types',
  'visual',
  'window',
]

gdkmm_deprecated_hg_ccg_basenames = [
  'color',
]

gdkmm_extra_cc_files = [
  'general.cc',
]

gdkmm_extra_h_files = [
  'general.h',
  'wrap_init.h',
]

# All .hg/.ccg files, regardless of deprecation.
gdkmm_hg_ccg_basenames = \
  gdkmm_any_hg_ccg_basenames + \
  gdkmm_deprecated_hg_ccg_basenames

# Used .hg/.ccg files in the present build.
gdkmm_used_hg_ccg_basenames = gdkmm_any_hg_ccg_basenames
if build_deprecated_api
  gdkmm_used_hg_ccg_basenames += gdkmm_deprecated_hg_ccg_basenames
endif

install_headers('..' / 'gdkmm.h', subdir: gdkmm_pcname)
install_headers(gdkmm_extra_h_files, subdir: gdkmm_pcname / 'gdkmm')

untracked_gdkmm = 'untracked' / 'gdk' / 'gdkmm'
src_untracked_gdkmm = project_source_root / untracked_gdkmm

gdkmm_cpp_args = [ '-DGDKMM_BUILD=1' ] + gdkmm_extra_gendef_cpp_args

if maintainer_mode

  # Maintainer mode. Generate .h and .cc files from .hg and .ccg files in ../src.

  # docs/reference/meson.build needs these.
  built_files_root = project_build_root
  gdkmm_built_h_file_targets = []

  # Force meson+ninja to generate source files before anything is compiled.
  # Compilation must depend on these targets.
  gdkmm_used_built_cc_file_targets = []
  gdkmm_used_built_h_file_targets = []

  hg_files = []
  foreach file : gdkmm_hg_ccg_basenames
    hg_files += '..' / 'src' / file + '.hg'
  endforeach

  # Create wrap_init.cc in project_build_root/gdk/gdkmm.
  gdkmm_used_built_cc_file_targets += custom_target('gdkmm-wrap_init.cc',
    input: hg_files,
    output: 'wrap_init.cc',
    command: [
      python3, generate_binding_py, 'generate_wrap_init',
      gmmproc_dir,
      '@OUTPUT@',
      'Gdk', # namespace
      '@INPUT@',
    ],
    build_by_default: maintainer_mode,
    install: false,
  )

  # Create .h/_p.h/.cc files in project_build_root/gdk/gdkmm
  # from .hg/.ccg files in project_source_root/gdk/src.
  foreach file : gdkmm_hg_ccg_basenames
    hg_file = '..' / 'src' / file + '.hg'
    ccg_file = '..' / 'src' / file + '.ccg'
    built_file_target = custom_target('gdkmm-' + file + '.cc',
      input: [hg_file, ccg_file],
      output: [file + '.stamp', file + '.cc', file + '.h'],
      command: [
        python3, generate_binding_py, 'gmmproc',
        gmmproc_dir,
        '@OUTPUT0@',
        file,
        meson.current_source_dir() / '..' / 'src',
        project_source_root / 'tools' / 'm4',
        gmmproc_extra_m4_dirs,
      ],
      depend_files: gdkmm_defs_files + m4_files,
      build_by_default: maintainer_mode,
      install: false,
    )
    gdkmm_built_h_file_targets += built_file_target[2]
    if gdkmm_used_hg_ccg_basenames.contains(file)
      gdkmm_used_built_cc_file_targets += built_file_target[1]
      gdkmm_used_built_h_file_targets += built_file_target[2]
    endif
  endforeach

  # Create dummy_header.h, depending on all generated headers.
  # It's created if it does not exist, but it's never updated.
  # It guarantees that all generated headers are built before gdkmm_library
  # is built, at the same time avoiding unnecessary recompilations.
  # If gdkmm_used_built_h_file_targets would be listed as sources to gdkmm_library,
  # all generated .cc files could be recompiled if one generated .h file has
  # been changed.
  built_dummy_h_file_target = custom_target('gdkmm-dummy_header.h',
    input: gdkmm_used_built_h_file_targets,
    output: 'dummy_header.h',
    command: [
      python3, dummy_header_py,
      '@OUTPUT@',
    ],
    build_by_default: maintainer_mode,
    install: false,
  )

  extra_include_dirs = ['..']

  gdk_gen_sources = gdkmm_used_built_cc_file_targets

  built_h_cc_dir = meson.current_build_dir()

else # not maintainer_mode

  # Not maintainer mode. Compile built source code files in
  # project_source_root/untracked/gdk/gdkmm.

  gdkmm_used_built_h_file_targets = []

  # docs/reference/meson.build needs these.
  built_files_root = project_source_root / 'untracked'
  gdkmm_built_h_file_targets = []

  # Two cases:
  # 1. The source code comes from a tarball, where the built files
  #    are stored in project_source_root/untracked.
  #    There are no built files in the build tree.
  # 2. Files have been built in the build tree. Then maintainer_mode has
  #    been changed from true to false. Files that are missing or not up to date
  #    in project_source_root/untracked are copied from the build tree.

  # Try to copy built source code files to the source tree.
  run_command(
    python3, generate_binding_py, 'copy_built_files',
    meson.current_build_dir(),
    src_untracked_gdkmm,
    gdkmm_hg_ccg_basenames,
    check: true,
  )

  built_cc_files = [ '../..' / untracked_gdkmm / 'wrap_init.cc' ]
  foreach file : gdkmm_used_hg_ccg_basenames
    built_cc_files += '../..' / untracked_gdkmm / file + '.cc'
  endforeach

  gdk_gen_sources = built_cc_files
  built_dummy_h_file_target = []

  extra_include_dirs = [ '..', '..' / '..' / 'untracked' / 'gdk' ]

  built_h_cc_dir = src_untracked_gdkmm

endif

extra_gdkmm_objects = []

# Build the .rc file for Windows builds and link to it
if is_host_windows
  windows = import('windows')
  gdkmm_res = windows.compile_resources(gdkmm_rc)
  extra_gdkmm_objects += gdkmm_res
endif

if build_shared_libs_directly
  gdkmm_library = library(gdkmm_libname, extra_gdkmm_objects,
    gdk_gen_sources, built_dummy_h_file_target, gdkmm_extra_cc_files,
    implicit_include_directories: false,
    include_directories: extra_include_dirs,
    cpp_args: gdkmm_cpp_args,
    version: gtkmm_libversion,
    darwin_versions: macos_darwin_versions,
    dependencies: gdkmm_build_dep,
    install: true,
  )
else
  # Building with headers generated from *.hg files with
  # gmmproc < 2.64.3 on Visual Studio: We need this so
  # that we can run gendef.exe to get the .def file
  # needed for obtaining the .lib file for the gdkmm DLL
  gdk_int_lib = static_library('gdkmm-int',
    gdk_gen_sources, built_dummy_h_file_target, gdkmm_extra_cc_files,
    implicit_include_directories: false,
    include_directories: extra_include_dirs,
    cpp_args: gdkmm_cpp_args,
    dependencies: gdkmm_build_dep,
    install: false,
  )

  gdkmm_def = custom_target('gdkmm.def',
    output: 'gdkmm.def',
    depends: gdk_int_lib,
    command: [ gendef,
      '@OUTPUT@',
      '@0@-@1@.dll'.format(gdkmm_libname, gtkmm_libversion.split('.')[0]),
      gdk_int_lib.full_path(),
    ],
    install: false,
  )
  gdkmm_extra_link_args = ['/def:@0@'.format(gdkmm_def.full_path())]

  gdkmm_library = library(gdkmm_libname, extra_gdkmm_objects,
    objects: gdk_int_lib.extract_all_objects(),
    version: gtkmm_libversion,
    darwin_versions: macos_darwin_versions,
    implicit_include_directories: false,
    dependencies: gdkmm_build_dep,
    link_depends: gdkmm_def,
    link_args: gdkmm_extra_link_args,
    install: true,
  )
endif

# Install built .h and _p.h files.
meson.add_install_script(
  python3, generate_binding_py, 'install_built_h_files',
  built_h_cc_dir,
  install_includedir / gdkmm_pcname / 'gdkmm', # subdir below {prefix}
  gdkmm_used_hg_ccg_basenames
)

if can_add_dist_script
  # Distribute built files.
  meson.add_dist_script(
    python3, generate_binding_py, 'dist_built_files',
    built_h_cc_dir,
    untracked_gdkmm,
    gdkmm_hg_ccg_basenames,
  )
endif

# This is used when building demo programs and test programs.
# It's also a part of gdkmm_dep, when gdkmm is a subproject.
gdkmm_own_dep = declare_dependency(
  sources: gdkmm_used_built_h_file_targets,
  link_with: gdkmm_library,
  include_directories: extra_include_dirs,
  dependencies: gdkmm_build_dep,
)
