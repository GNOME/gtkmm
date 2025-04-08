# gsk

# Input: pkg_conf_data, install_gtkmmconfigdir, install_libdir
# Output: gskmmconfig_h_meson

gskmmconfig_h_meson = files('gskmmconfig.h.meson')
configure_file(
  input: gskmmconfig_h_meson,
  output: 'gskmmconfig.h',
  configuration: pkg_conf_data,
  install: true,
  install_dir: install_gtkmmconfigdir,
  install_tag: 'devel',
)
