# docs/reference

# Input: built_files_root, project_source_root, gtkmm_pcname,
#        gdkmm_hg_ccg_basenames, gskmm_hg_ccg_basenames, gtkmm_hg_ccg_basenames,
#        gdkmm_extra_h_files, gskmm_extra_h_files, gtkmm_extra_h_files,
#        gdkmm_built_h_file_targets, gskmm_built_h_file_targets,
#        gtkmm_built_h_file_targets, install_datadir, python3,
#        doc_reference_py, build_documentation
# Output: install_docdir, install_devhelpdir, if build_documentation: tag_file

tag_file_modules = [
  'mm-common-libstdc++',
  'sigc++-3.0',
  'glibmm-2.68',
  'cairomm-1.16',
  'pangomm-2.48',
]
doxygen_tagfiles = ''
doxygen_tag_targets = []
docinstall_flags = []
foreach module : tag_file_modules
  depmod = dependency(module, required: false)
  if depmod.found()
    doxytagfile = depmod.get_variable('doxytagfile', default_value: '')
    if doxytagfile != ''
      if depmod.type_name() == 'internal'
        # Subprojects must build their tag files before doxygen is called.
        if module.startswith('mm-common')
          doxygen_tag_targets += subproject('mm-common').get_variable('global_tag_file_target')
        else
          doxygen_tag_targets += subproject(module).get_variable('global_tag_file_target')
        endif
      endif
      htmlrefpub = depmod.get_variable('htmlrefpub', default_value: '')
      htmlrefdir = depmod.get_variable('htmlrefdir', default_value: '')
      if htmlrefpub == ''
        htmlrefpub = htmlrefdir
      elif htmlrefdir == ''
        htmlrefdir = htmlrefpub
      endif
      doxygen_tagfiles += ' "' + doxytagfile + '=' + htmlrefpub + '"'

      # Doxygen <= 1.8.15
      docinstall_flags += ['-l', doxytagfile.split('/')[-1] + '@' + htmlrefdir]
      if htmlrefpub != htmlrefdir
        # Doxygen >= 1.8.16
        docinstall_flags += ['-l', 's@' + htmlrefpub + '@' + htmlrefdir]
      endif
    endif
  endif
endforeach

book_name = gtkmm_pcname
book_title = meson.project_name() + ' Reference Manual'

# Configuration data for Doxyfile.
doc_conf_data = configuration_data()
doc_conf_data.set('configure_input',
  'docs/reference/Doxyfile. Generated from Doxyfile.in by meson.configure_file().')
doc_conf_data.set('PACKAGE_NAME', meson.project_name())
doc_conf_data.set('PACKAGE_VERSION', meson.project_version())
doc_conf_data.set('abs_top_builddir', built_files_root)
doc_conf_data.set('abs_top_srcdir', project_source_root)
doc_conf_data.set('GTKMM_MODULE_NAME', book_name)
doc_conf_data.set('DOXYGEN_TAGFILES', doxygen_tagfiles)

doxyfile = configure_file(
  input: 'Doxyfile.in',
  output: '@BASENAME@',
  configuration: doc_conf_data,
)

# Installation directories relative to {prefix}.
install_docdir = install_datadir / 'doc' / book_name
install_reference_docdir = install_docdir / 'reference'
install_image_docdir = install_docdir / 'images'
install_devhelpdir = install_datadir / 'devhelp' / 'books' / book_name

if not build_documentation
  # Documentation shall not be built or installed.
  # Return to the calling meson.build file.
  subdir_done()
endif

# Built input .h files to Doxygen.
built_h_files = []
foreach file : gdkmm_hg_ccg_basenames
  built_h_files += built_files_root / 'gdk' / 'gdkmm' / file + '.h'
endforeach
foreach file : gskmm_hg_ccg_basenames
  built_h_files += built_files_root / 'gsk' / 'gskmm' / file + '.h'
endforeach
foreach file : gtkmm_hg_ccg_basenames
  built_h_files += built_files_root / 'gtk' / 'gtkmm' / file + '.h'
endforeach

# Hand-coded input .h files to Doxygen.
src_h_files = []
foreach file : gdkmm_extra_h_files
  if file != 'wrap_init.h'
    src_h_files += project_source_root / 'gdk' / 'gdkmm' / file
  endif
endforeach
foreach file : gskmm_extra_h_files
  if file != 'wrap_init.h'
    src_h_files += project_source_root / 'gsk' / 'gskmm' / file
  endif
endforeach
foreach file : gtkmm_extra_h_files
  if file != 'wrap_init.h'
    src_h_files += project_source_root / 'gtk' / 'gtkmm' / file
  endif
endforeach
src_h_files += project_source_root / 'gdk' / 'gdkmm.h'
src_h_files += project_source_root / 'gsk' / 'gskmm.h'
src_h_files += project_source_root / 'gtk' / 'gtkmm.h'

doctool_dir = project_source_root / 'untracked' / 'docs' # MMDOCTOOLDIR
doctool_dist_dir = 'untracked' / 'docs' # Relative to MESON_DIST_ROOT

doc_h_files = src_h_files
if gdkmm_built_h_file_targets.length() + gskmm_built_h_file_targets.length() + gtkmm_built_h_file_targets.length() > 0
  # .h files have been generated from .hg files (maintainer mode).
  # Use built_h_file_targets instead of built_h_files here, or else Meson won't
  # know that Doxygen must not be executed until the .h files have been built.
  doc_h_files += gdkmm_built_h_file_targets + gskmm_built_h_file_targets + gtkmm_built_h_file_targets
else
  # All .h files are stored in the source tree (not maintainer mode).
  doc_h_files += built_h_files
endif

# Can't use @INPUT@ in the command. It requires absolute file paths.
# Paths in built_h_file_targets are relative to project_build_root.
tag_file = custom_target('html_and_tag',
  input: doc_h_files,
  output: book_name + '.tag',
  command: [
    python3, doc_reference_py, 'doxygen',
    doctool_dir,
    '@OUTPUT@',
    src_h_files,
    built_h_files,
  ],
  depend_files: doxyfile,
  depends: doxygen_tag_targets,
  build_by_default: build_documentation,
  install: true,
  install_dir: install_reference_docdir,
  install_tag: 'doc',
)

devhelp_file = custom_target('devhelp',
  input: tag_file,
  output: book_name + '.devhelp2',
  command: [
    python3, doc_reference_py, 'devhelp',
    doctool_dir,
    '@INPUT@',
    '@OUTPUT@',
    book_name,
    book_title,
  ],
  build_by_default: build_documentation,
)

# Install Devhelp file and html files.
meson.add_install_script(
  python3, doc_reference_py, 'install_doc',
  doctool_dir,
  devhelp_file.full_path(),
  install_devhelpdir,
  install_reference_docdir / 'html',
  docinstall_flags,
  install_tag: 'doc',
)

# Install images.
image_basefiles = [
  'gtkmm_logo.gif',
  'top.gif',
]
image_files = []
foreach file : image_basefiles
  image_files += '..' / 'images' / file
endforeach

install_data(image_files,
  install_dir: install_image_docdir,
  install_tag: 'doc',
)

# Distribute built files and files copied by mm-common-get.
meson.add_dist_script(
  python3, doc_reference_py, 'dist_doc',
  doctool_dir,
  doctool_dist_dir,
  meson.current_build_dir(),
  tag_file.full_path(),
  devhelp_file.full_path(),
)
