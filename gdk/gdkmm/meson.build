# gdk/gdkmm

# Input: gdkmm_build_dep, gtkmm_pcname, maintainer_mode, project_source_root,
#        generate_binding_py, m4_files, install_includedir, python3,
#        dummy_header_py, gmmproc_dir, build_deprecated_api,
#        gmmproc_extra_m4_dirs
# Output: gdkmm_hg_ccg_basenames, gdkmm_extra_h_files, built_files_root,
#         gdkmm_built_h_file_targets, gdkmm_used_built_h_file_targets,
#         gdkmm_library

gdkmm_defs_basefiles = [
  'gdk.defs',
  'gdk_enums.defs',
  'gdk_extra.defs',
  'gdk_extra_objects.defs',
  'gdk_methods.defs',
  'gdk_pixbuf_enums.defs',
  'gdk_pixbuf_methods.defs',
  'gdk_graphene_methods.defs',
  'gdk_signals.defs',
  'gdk_vfuncs.defs',
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
  'cairocontext',
  'cicpparams',
  'clipboard',
  'colorstate',
  'contentformats',
  'contentformatsbuilder',
  'contentprovider',
  'cursor',
  'device',
  'devicepad',
  'devicetool',
  'display',
  'displaymanager',
  'dmabufformats',
  'dmabuftexture',
  'dmabuftexturebuilder',
  'drag',
  'dragsurface',
  'dragsurfacesize',
  'drawcontext',
  'drop',
  'enums',
  'event',
  'frameclock',
  'frametimings',
  'glcontext',
  'gltexture',
  'gltexturebuilder',
  'graphene_point',
  'graphene_rect',
  'graphene_size',
  'memorytexture',
  'memorytexturebuilder',
  'monitor',
  'paintable',
  'pixbuf',
  'pixbufformat',
  'pixbufloader',
  'popup',
  'popuplayout',
  'rectangle',
  'rgba',
  'seat',
  'snapshot',
  'surface',
  'texture',
  'texturedownloader',
  'timecoord',
  'toplevel',
  'toplevellayout',
  'toplevelsize',
]

gdkmm_deprecated_hg_ccg_basenames = [
  'pixbufanimation',
  'pixbufanimationiter',
]

# Pairs of hand-coded .h and .cc files.
gdkmm_extra_any_h_cc_basenames = [
  'cairoutils',
  'devicewithpad',
  'dragsurfaceimpl',
  'general',
  'popupsurfaceimpl',
  'slot_async',
  'toplevelsurfaceimpl',
  'value_cairo',
]

gdkmm_extra_cc_files = []

gdkmm_extra_h_files = [
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

foreach file : gdkmm_extra_any_h_cc_basenames
  gdkmm_extra_h_files += file + '.h'
  gdkmm_extra_cc_files += file + '.cc'
endforeach

install_headers('..' / 'gdkmm.h', subdir: gtkmm_pcname)
install_headers(gdkmm_extra_h_files, subdir: gtkmm_pcname / 'gdkmm')

untracked_gdkmm = 'untracked' / 'gdk' / 'gdkmm'
src_untracked_gdkmm = project_source_root / untracked_gdkmm

gdkmm_cpp_args = [ '-DGDKMM_BUILD=1' ]

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
    input: gdkmm_built_h_file_targets,
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

# This is an internal static library.
# The objects in this library will be included in gtkmm_library.
gdkmm_library = static_library('gdkmm',
  gdk_gen_sources, built_dummy_h_file_target, gdkmm_extra_cc_files,
  implicit_include_directories: false,
  include_directories: extra_include_dirs,
  cpp_args: gdkmm_cpp_args,
  dependencies: gdkmm_build_dep,
  install: false,
)

# Install built .h and _p.h files.
meson.add_install_script(
  python3, generate_binding_py, 'install_built_h_files',
  built_h_cc_dir,
  install_includedir / gtkmm_pcname / 'gdkmm', # subdir below {prefix}
  gdkmm_used_hg_ccg_basenames,
  install_tag: 'devel',
)

# Distribute built files.
meson.add_dist_script(
  python3, generate_binding_py, 'dist_built_files',
  built_h_cc_dir,
  untracked_gdkmm,
  gdkmm_hg_ccg_basenames,
)

# We don't define gdkmm_dep = declare_dependency() with gdkmm_library,
# which is an internal library.
