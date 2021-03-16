# tools/extra_defs_gen

# Input: cpp_compiler, gdkmm_build_dep, gtkmm_build_dep, install_libdir,
#        gtkmm_pcname, msvc14x_toolset_ver, glibmm_dep
# Output: m4_files, install_m4dir

glibmm_generate_extra_defs_dep = cpp_compiler.find_library(
  'glibmm_generate_extra_defs@0@-2.68'.format(msvc14x_toolset_ver),
  required: glibmm_dep.type_name() != 'internal',
)
if not glibmm_generate_extra_defs_dep.found()
  glibmm_generate_extra_defs_dep = dependency(
    '', fallback: ['glibmm-2.68', 'glibmm_generate_extra_defs_dep'],
  )
endif

executable('generate_defs_gdk', 'generate_defs_gdk.cc',
  dependencies: [gdkmm_build_dep, glibmm_generate_extra_defs_dep],
  install: false,
)

executable('generate_defs_gtk', 'generate_defs_gtk.cc',
  dependencies: [gtkmm_build_dep, glibmm_generate_extra_defs_dep],
  install: false,
)

# Install m4 files for reuse by other *mm projects, when building from git.
m4_basefiles = [
  'class_gtkobject.m4',
  'convert.m4',
  'convert_gdk.m4',
  'convert_gtk.m4',
  'convert_gtkmm.m4',
]
m4_files = []
foreach file : m4_basefiles
  m4_files += '..' / 'm4' / file
endforeach
m4_files = files(m4_files)
install_m4dir = install_libdir / gtkmm_pcname / 'proc' / 'm4'
install_data(m4_files, install_dir: install_m4dir)
