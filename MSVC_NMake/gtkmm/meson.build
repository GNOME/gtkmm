# MSVC_NMake/gtkmm

# Input: pkg_conf_data, gtkmmconfig_h_meson
# Output: gtkmm_rc

gtkmm_rc = configure_file(
  input: 'gtkmm.rc.in',
  output: '@BASENAME@',
  configuration: pkg_conf_data,
)

# Make a copy of the generated configuration header in the MSVC project directory.
configure_file(
  input: gtkmmconfig_h_meson,
  output: 'gtkmmconfig.h',
  configuration: pkg_conf_data,
)
