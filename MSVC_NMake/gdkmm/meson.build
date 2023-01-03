# MSVC_NMake/gdkmm

# Input: pkg_conf_data, gdkmmconfig_h_meson
# Output: gdkmm_rc

gdkmm_rc = configure_file(
  input: 'gdkmm.rc.in',
  output: '@BASENAME@',
  configuration: pkg_conf_data,
)

# Make a copy of the generated configuration header in the MSVC project directory.
configure_file(
  input: gdkmmconfig_h_meson,
  output: 'gdkmmconfig.h',
  configuration: pkg_conf_data,
)
