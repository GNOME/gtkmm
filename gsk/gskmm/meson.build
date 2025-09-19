# gsk/gskmm

# Input: gskmm_build_dep, gtkmm_pcname, maintainer_mode, project_source_root,
#        generate_binding_py, m4_files, install_includedir, python3,
#        dummy_header_py, gmmproc_dir, build_deprecated_api,
#        gmmproc_extra_m4_dirs
# Output: gskmm_hg_ccg_basenames, gskmm_extra_h_files, built_files_root,
#         gskmm_built_h_file_targets, gskmm_used_built_h_file_targets,
#         gskmm_library

gskmm_defs_basefiles = [
  'gsk.defs',
  'gsk_enums.defs',
  'gsk_extra_objects.defs',
  'gsk_methods.defs',
  'gsk_signals.defs',
  'gsk_vfuncs.defs',
  'gsk_docs.xml',
  'gsk_docs_override.xml',
]

gskmm_defs_files = []
foreach file : gskmm_defs_basefiles
  gskmm_defs_files += '..' / 'src' / file
endforeach

# Generated from pairs of .hg and .ccg files.
gskmm_any_hg_ccg_basenames = [
  'enums',
  'roundedrect',
  'transform',
]

gskmm_deprecated_hg_ccg_basenames = []

# Pairs of hand-coded .h and .cc files.
gskmm_extra_any_h_cc_basenames = []

gskmm_extra_cc_files = []

gskmm_extra_h_files = [
  'wrap_init.h',
]

# All .hg/.ccg files, regardless of deprecation.
gskmm_hg_ccg_basenames = \
  gskmm_any_hg_ccg_basenames + \
  gskmm_deprecated_hg_ccg_basenames

# Used .hg/.ccg files in the present build.
gskmm_used_hg_ccg_basenames = gskmm_any_hg_ccg_basenames
if build_deprecated_api
  gskmm_used_hg_ccg_basenames += gskmm_deprecated_hg_ccg_basenames
endif

foreach file : gskmm_extra_any_h_cc_basenames
  gskmm_extra_h_files += file + '.h'
  gskmm_extra_cc_files += file + '.cc'
endforeach

install_headers('..' / 'gskmm.h', subdir: gtkmm_pcname)
install_headers(gskmm_extra_h_files, subdir: gtkmm_pcname / 'gskmm')

untracked_gskmm = 'untracked' / 'gsk' / 'gskmm'
src_untracked_gskmm = project_source_root / untracked_gskmm

gskmm_cpp_args = [ '-DGSKMM_BUILD=1' ]

if maintainer_mode

  # Maintainer mode. Generate .h and .cc files from .hg and .ccg files in ../src.

  # docs/reference/meson.build needs these.
  built_files_root = project_build_root
  gskmm_built_h_file_targets = []

  # Force meson+ninja to generate source files before anything is compiled.
  # Compilation must depend on these targets.
  gskmm_used_built_cc_file_targets = []
  gskmm_used_built_h_file_targets = []

  hg_files = []
  foreach file : gskmm_hg_ccg_basenames
    hg_files += '..' / 'src' / file + '.hg'
  endforeach

  # Create wrap_init.cc in project_build_root/gsk/gskmm.
  gskmm_used_built_cc_file_targets += custom_target('gskmm-wrap_init.cc',
    input: hg_files,
    output: 'wrap_init.cc',
    command: [
      python3, generate_binding_py, 'generate_wrap_init',
      gmmproc_dir,
      '@OUTPUT@',
      'Gsk', # namespace
      '@INPUT@',
    ],
    build_by_default: maintainer_mode,
    install: false,
  )

  # Create .h/_p.h/.cc files in project_build_root/gsk/gskmm
  # from .hg/.ccg files in project_source_root/gsk/src.
  foreach file : gskmm_hg_ccg_basenames
    hg_file = '..' / 'src' / file + '.hg'
    ccg_file = '..' / 'src' / file + '.ccg'
    built_file_target = custom_target('gskmm-' + file + '.cc',
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
      depend_files: gskmm_defs_files + m4_files,
      build_by_default: maintainer_mode,
      install: false,
    )
    gskmm_built_h_file_targets += built_file_target[2]
    if gskmm_used_hg_ccg_basenames.contains(file)
      gskmm_used_built_cc_file_targets += built_file_target[1]
      gskmm_used_built_h_file_targets += built_file_target[2]
    endif
  endforeach

  # Create dummy_header.h, depending on all generated headers.
  # It's created if it does not exist, but it's never updated.
  # It guarantees that all generated headers are built before gskmm_library
  # is built, at the same time avoiding unnecessary recompilations.
  # If gskmm_used_built_h_file_targets would be listed as sources to gskmm_library,
  # all generated .cc files could be recompiled if one generated .h file has
  # been changed.
  built_dummy_h_file_target = custom_target('gskmm-dummy_header.h',
    input: gskmm_built_h_file_targets,
    output: 'dummy_header.h',
    command: [
      python3, dummy_header_py,
      '@OUTPUT@',
    ],
    build_by_default: maintainer_mode,
    install: false,
  )

  extra_include_dirs = ['..', '..' / '..' / 'gdk']

  gsk_gen_sources = gskmm_used_built_cc_file_targets

  built_h_cc_dir = meson.current_build_dir()

else # not maintainer_mode

  # Not maintainer mode. Compile built source code files in
  # project_source_root/untracked/gsk/gskmm.

  gskmm_used_built_h_file_targets = []

  # docs/reference/meson.build needs these.
  built_files_root = project_source_root / 'untracked'
  gskmm_built_h_file_targets = []

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
    src_untracked_gskmm,
    gskmm_hg_ccg_basenames,
    check: true,
  )

  built_cc_files = [ '../..' / untracked_gskmm / 'wrap_init.cc' ]
  foreach file : gskmm_used_hg_ccg_basenames
    built_cc_files += '../..' / untracked_gskmm / file + '.cc'
  endforeach

  gsk_gen_sources = built_cc_files
  built_dummy_h_file_target = []

  extra_include_dirs = [ '..', '..' / '..' / 'untracked' / 'gsk',
          '..' / '..' / 'gdk', '..' / '..' / 'untracked' / 'gdk']

  built_h_cc_dir = src_untracked_gskmm

endif

# This is an internal static library.
# The objects in this library will be included in gtkmm_library.
gskmm_library = static_library('gskmm',
  gsk_gen_sources, built_dummy_h_file_target, gskmm_extra_cc_files,
  implicit_include_directories: false,
  include_directories: extra_include_dirs,
  cpp_args: gskmm_cpp_args,
  dependencies: gskmm_build_dep,
  install: false,
)

# Install built .h and _p.h files.
meson.add_install_script(
  python3, generate_binding_py, 'install_built_h_files',
  built_h_cc_dir,
  install_includedir / gtkmm_pcname / 'gskmm', # subdir below {prefix}
  gskmm_used_hg_ccg_basenames,
  install_tag: 'devel',
)

# Distribute built files.
meson.add_dist_script(
  python3, generate_binding_py, 'dist_built_files',
  built_h_cc_dir,
  untracked_gskmm,
  gskmm_hg_ccg_basenames,
)

# We don't define gskmm_dep = declare_dependency() with gskmm_library,
# which is an internal library.
