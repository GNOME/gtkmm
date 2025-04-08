# demos/gtk-demo

# Input: gtkmm_own_dep, epoxy_dep, build_demos, gui_app_ldflags
# Output: -

gtkmm_demo_cc_files = [
  'main.cc',
  'demowindow.cc',
  'textwidget.cc',
  'example_appwindow.cc',
  'example_builder.cc',
  'example_colorsel.cc',
  'example_dialog.cc',
  'example_drawingarea.cc',
  'example_dropdown.cc',
  'example_flowbox.cc',
  'example_gestures.cc',
  'example_glarea.cc',
  'example_gridview.cc',
  'example_headerbar.cc',
  'example_iconbrowser.cc',
  'example_images.cc',
  'example_listview_applauncher.cc',
  'example_listview_columnview.cc',
  'example_listview_editable_cells.cc',
  'example_listview_liststore.cc',
  'example_listview_treelist.cc',
  'example_overlay.cc',
  'example_panes.cc',
  'example_pixbufs.cc',
  'example_shortcuts.cc',
  'example_sizegroup.cc',
  'example_stack.cc',
  'example_stacksidebar.cc',
  'example_textview.cc',
]

gnome = import('gnome')

if epoxy_dep.found()
  demo_resources = gnome.compile_resources('demo-resources',
    'demo.gresource.xml',
    source_dir: meson.current_source_dir(),
    install: false,
  )

  executable('gtkmm-demo',
    gtkmm_demo_cc_files, demo_resources,
    cpp_args: ['-DGLIBMM_DISABLE_DEPRECATED', '-DGIOMM_DISABLE_DEPRECATED',
               '-DGDKMM_DISABLE_DEPRECATED', '-DGSKMM_DISABLE_DEPRECATED',
               '-DGTKMM_DISABLE_DEPRECATED'],
    dependencies: [gtkmm_own_dep, epoxy_dep],
    implicit_include_directories: false,
    win_subsystem: 'windows',
    build_by_default: build_demos,
    link_args: gui_app_ldflags,
    install: false,
  )
endif
