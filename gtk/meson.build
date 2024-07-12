# gtk

# Input: pkg_conf_data, gtkmm_pcname, install_libdir
# Output: install_gtkmmconfigdir, gtkmmconfig_h_meson

gtkmmconfig_h_meson = files('gtkmmconfig.h.meson')
install_gtkmmconfigdir = install_libdir / gtkmm_pcname / 'include'
configure_file(
  input: gtkmmconfig_h_meson,
  output: 'gtkmmconfig.h',
  configuration: pkg_conf_data,
  install_dir: install_gtkmmconfigdir,
)
