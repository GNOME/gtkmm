# win32_installer

# Input: pkg_conf_data, lgpl_license
# Output: gtkmm_installer_nsi, lgpl_license_txt

if host_machine.system() != 'windows'
  message('NSIS installer is only possible on Windows')
  subdir_done()
endif

configure_file(
  input: 'gtkmm-installer.nsi.in',
  output: 'gtkmm-installer.nsi',
  configuration: pkg_conf_data,
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
