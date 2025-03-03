# gdk

# Input: install_libdir, gtkmm_pcname, build_deprecated_api, cpp_compiler,
#        gtkmm_major_version, gtkmm_minor_version, gtkmm_micro_version
# Output: pkg_conf_data, install_gtkmmconfigdir, gdkmmconfig_h_meson

pkg_conf_data = configuration_data()
pkg_conf_data.set('PACKAGE_VERSION', meson.project_version())
pkg_conf_data.set('GTKMM_MODULE_NAME', gtkmm_pcname)
if not build_deprecated_api
  pkg_conf_data.set('GDKMM_DISABLE_DEPRECATED', 1)
  pkg_conf_data.set('GTKMM_DISABLE_DEPRECATED', 1)
endif
pkg_conf_data.set('GDKMM_MAJOR_VERSION', gtkmm_major_version)
pkg_conf_data.set('GDKMM_MINOR_VERSION', gtkmm_minor_version)
pkg_conf_data.set('GDKMM_MICRO_VERSION', gtkmm_micro_version)
pkg_conf_data.set('GTKMM_MAJOR_VERSION', gtkmm_major_version)
pkg_conf_data.set('GTKMM_MINOR_VERSION', gtkmm_minor_version)
pkg_conf_data.set('GTKMM_MICRO_VERSION', gtkmm_micro_version)

library_build_type = get_option('default_library')

if cpp_compiler.get_argument_syntax() == 'msvc'
  if library_build_type == 'static' or library_build_type == 'both'
    error('Static builds are not supported by MSVC-style builds')
  endif
endif

if library_build_type == 'static'
  pkg_conf_data.set('GTKMM_STATIC_LIB', 1)
endif

gdkmmconfig_h_meson = files('gdkmmconfig.h.meson')
install_gtkmmconfigdir = install_libdir / gtkmm_pcname / 'include'
configure_file(
  input: gdkmmconfig_h_meson,
  output: 'gdkmmconfig.h',
  configuration: pkg_conf_data,
  install: true,
  install_dir: install_gtkmmconfigdir,
  install_tag: 'devel',
)
