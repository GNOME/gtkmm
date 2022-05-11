# win32_installer

# Input: pkg_conf_data, lgpl_license
# Output: win32_installer_data, gtkmm_installer_nsi, lgpl_license_txt

if host_machine.system() != 'windows'
  message('NSIS installer is only possible on Windows')
  subdir_done()
endif

win32_installer_data = configuration_data()
win32_installer_data.merge_from(pkg_conf_data)
win32_installer_data.set('top_srcdir', meson.source_root())
win32_installer_data.set('top_builddir', meson.build_root())
win32_installer_data.set10('IS_SOURCES_REGEN', maintainer_mode)
win32_installer_data.set10('IS_MESON_BUILD', true)

configure_file(
  input: 'gtkmm-installer.nsi.in',
  output: 'gtkmm-installer.nsi',
  configuration: win32_installer_data,
  install: false,
)

configure_file(
  input: 'build-installer.mak.in',
  output: 'build-installer.mak',
  configuration: win32_installer_data,
  install: false,
)

installer_data_files = [
  'gtkmm-3.0.props',
  'gtkmm.ico'
]

foreach f: installer_data_files
  configure_file(input: f, output: f, copy: true)
endforeach

lgpl_license_txt = configure_file(input: lgpl_license, output: 'lgpl.txt', copy: true)

subdir('NSISLibrary')
subdir('translations')
