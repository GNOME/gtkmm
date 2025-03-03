# gtk

# Input: pkg_conf_data, install_gtkmmconfigdir, install_libdir
# Output: gtkmmconfig_h_meson

gtkmmconfig_h_meson = files('gtkmmconfig.h.meson')
configure_file(
  input: gtkmmconfig_h_meson,
  output: 'gtkmmconfig.h',
  configuration: pkg_conf_data,
  install: true,
  install_dir: install_gtkmmconfigdir,
  install_tag: 'devel',
)
