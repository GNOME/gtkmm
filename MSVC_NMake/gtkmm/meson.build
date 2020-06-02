# MSVC_NMake/gtkmm

# Input: pkg_conf_data, gtkmmconfig_h
# Output: gtkmm_rc

gtkmm_rc = configure_file(
  input: 'gtkmm.rc.in',
  output: '@BASENAME@',
  configuration: pkg_conf_data,
)

# Copy the generated configuration header into the MSVC project directory.
configure_file(
  input: gtkmmconfig_h,
  output: 'gtkmmconfig.h',
  copy: true,
)
