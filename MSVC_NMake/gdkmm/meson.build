# MSVC_NMake/gdkmm

# Input: pkg_conf_data, gdkmmconfig_h
# Output: gdkmm_rc

gdkmm_rc = configure_file(
  input: 'gdkmm.rc.in',
  output: '@BASENAME@',
  configuration: pkg_conf_data,
)

# Copy the generated configuration header into the MSVC project directory.
configure_file(
  input: gdkmmconfig_h,
  output: 'gdkmmconfig.h',
  copy: true,
)
