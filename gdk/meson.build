# gdk

# Input: install_prefix, install_libdir, install_datadir, install_includedir,
#        gdkmm_pcname, gtkmm_pcname, gtkmm_api_version, gdkmm_requires,
#        gtkmm_requires, build_deprecated_api, install_pkgconfigdir,
#        is_os_cocoa, cpp_compiler, gtkmm_major_version, gtkmm_minor_version,
#        gtkmm_micro_version, build_atkmm_api, build_x11_api
# Output: pkg_conf_data, install_gdkmmconfigdir, gdkmmconfig_h

pkg_conf_data = configuration_data()
pkg_conf_data.set('prefix', install_prefix)
pkg_conf_data.set('exec_prefix', '${prefix}')
pkg_conf_data.set('libdir', '${exec_prefix}' / install_libdir)
pkg_conf_data.set('datarootdir', '${prefix}' / install_datadir)
pkg_conf_data.set('datadir', '${datarootdir}')
pkg_conf_data.set('includedir', '${prefix}' / install_includedir)
pkg_conf_data.set('PACKAGE_TARNAME', meson.project_name())
pkg_conf_data.set('PACKAGE_VERSION', meson.project_version())
pkg_conf_data.set('GDKMM_MODULE_NAME', gdkmm_pcname)
pkg_conf_data.set('GDKMM_API_VERSION', gtkmm_api_version)
pkg_conf_data.set('GDKMM_MODULES', gdkmm_requires)
pkg_conf_data.set('GTKMM_MODULE_NAME', gtkmm_pcname)
pkg_conf_data.set('GTKMM_API_VERSION', gtkmm_api_version)
pkg_conf_data.set('GTKMM_MODULES', gtkmm_requires)
if not build_deprecated_api
  pkg_conf_data.set('GDKMM_DISABLE_DEPRECATED', 1)
  pkg_conf_data.set('GTKMM_DISABLE_DEPRECATED', 1)
endif
if build_atkmm_api
  pkg_conf_data.set('GTKMM_ATKMM_ENABLED', 1)
endif
if build_x11_api
  pkg_conf_data.set('GDKMM_X11_BACKEND_ENABLED', 1)
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
  pkg_conf_data.set('GDKMM_STATIC_LIB', 1)
  pkg_conf_data.set('GTKMM_STATIC_LIB', 1)
endif

configure_file(
  input: 'gdkmm.pc.in',
  output: gdkmm_pcname + '.pc',
  configuration: pkg_conf_data,
  install_dir: install_pkgconfigdir,
)

gdkmm_pkg_uninst_conf_data = configuration_data()
gdkmm_pkg_uninst_conf_data.merge_from(pkg_conf_data)
gdkmm_pkg_uninst_conf_data.set('srcdir', meson.current_source_dir())

configure_file(
  input: 'gdkmm-uninstalled.pc.in',
  output: gdkmm_pcname + '-uninstalled.pc',
  configuration: gdkmm_pkg_uninst_conf_data,
)

install_gdkmmconfigdir = install_libdir / gdkmm_pcname / 'include'
gdkmmconfig_h = configure_file(
  input: 'gdkmmconfig.h.meson',
  output: 'gdkmmconfig.h',
  configuration: pkg_conf_data,
  install_dir: install_gdkmmconfigdir,
)
