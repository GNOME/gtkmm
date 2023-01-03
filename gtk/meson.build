# gtk

# Input: pkg_conf_data, gtkmm_pcname, install_pkgconfigdir, install_libdir
# Output: install_gtkmmconfigdir, gtkmmconfig_h_meson

configure_file(
  input: 'gtkmm.pc.in',
  output: gtkmm_pcname + '.pc',
  configuration: pkg_conf_data,
  install_dir: install_pkgconfigdir,
)

gtkmm_pkg_uninst_conf_data = configuration_data()
gtkmm_pkg_uninst_conf_data.merge_from(pkg_conf_data)
gtkmm_pkg_uninst_conf_data.set('srcdir', meson.current_source_dir())

configure_file(
  input: 'gtkmm-uninstalled.pc.in',
  output: gtkmm_pcname + '-uninstalled.pc',
  configuration: gtkmm_pkg_uninst_conf_data,
)

gtkmmconfig_h_meson = files('gtkmmconfig.h.meson')
install_gtkmmconfigdir = install_libdir / gtkmm_pcname / 'include'
configure_file(
  input: gtkmmconfig_h_meson,
  output: 'gtkmmconfig.h',
  configuration: pkg_conf_data,
  install_dir: install_gtkmmconfigdir,
)
