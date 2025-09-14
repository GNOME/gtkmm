# gtk/gtkmm

# Input: gtkmm_build_dep, gtkmm_pcname, maintainer_mode, project_source_root,
#        generate_binding_py, m4_files, gtkmm_libversion, install_includedir,
#        python3, gtkmm_rc, dummy_header_py, gmmproc_dir, macos_darwin_versions,
#        build_deprecated_api, gmmproc_extra_m4_dirs, is_host_windows,
#        gdkmm_library, gskmm_library, gdkmm_used_built_h_file_targets,
#        gskmm_used_built_h_file_targets, gtkmm_libname,
#        gtkmm_pc_requires
# Output: gtkmm_hg_ccg_basenames, gtkmm_extra_h_files, built_files_root,
#         gtkmm_built_h_file_targets, gtkmm_own_dep

gtkmm_defs_basefiles = [
  'gtk.defs',
  'gtk_enums.defs',
  'gtk_extra_objects.defs',
  'gtk_methods.defs',
  'gtk_signals.defs',
  'gtk_vfuncs.defs',
  'gtk_docs.xml',
  'gtk_docs_override.xml',
]

gtkmm_defs_files = []
foreach file : gtkmm_defs_basefiles
  gtkmm_defs_files += '..' / 'src' / file
endforeach

# Generated from pairs of .hg and .ccg files.
gtkmm_any_hg_ccg_basenames = [
  'aboutdialog',
  'accessible',
  'accessibletext',
  'actionable',
  'actionbar',
  'adjustment',
  'alertdialog',
  'application',
  'applicationwindow',
  'aspectframe',
  'atcontext',
  'binlayout',
  'bitset',
  'boolfilter',
  'border',
  'box',
  'boxlayout',
  'buildable',
  'builder',
  'buildercscope',
  'builderscope',
  'button',
  'calendar',
  'celleditable',
  'centerbox',
  'centerlayout',
  'checkbutton',
  'colordialog',
  'colordialogbutton',
  'columnview',
  'columnviewcell',
  'columnviewcolumn',
  'columnviewrow',
  'columnviewsorter',
  'constraint',
  'constraintguide',
  'constraintlayout',
  'constrainttarget',
  'csslocation',
  'cssprovider',
  'csssection',
  'dialog',
  'directorylist',
  'dragicon',
  'dragsource',
  'drawingarea',
  'dropcontrollermotion',
  'dropdown',
  'droptarget',
  'droptargetasync',
  'editable',
  'editablelabel',
  'emojichooser',
  'entry',
  'entrybuffer',
  'enums',
  'error',
  'eventcontroller',
  'eventcontrollerfocus',
  'eventcontrollerkey',
  'eventcontrollerlegacy',
  'eventcontrollermotion',
  'eventcontrollerscroll',
  'expander',
  'expression',
  'expressionwatch',
  'filedialog',
  'filefilter',
  'filelauncher',
  'filter',
  'filterlistmodel',
  'fixed',
  'fixedlayout',
  'fixedlayoutchild',
  'flattenlistmodel',
  'flowbox',
  'flowboxchild',
  'fontdialog',
  'fontdialogbutton',
  'frame',
  'gesture',
  'gestureclick',
  'gesturedrag',
  'gesturelongpress',
  'gesturepan',
  'gesturerotate',
  'gesturesingle',
  'gesturestylus',
  'gestureswipe',
  'gesturezoom',
  'glarea',
  'graphicsoffload',
  'grid',
  'gridlayout',
  'gridlayoutchild',
  'gridview',
  'headerbar',
  'iconpaintable',
  'icontheme',
  'image',
  'inscription',
  'label',
  'layoutchild',
  'layoutmanager',
  'levelbar',
  'linkbutton',
  'listbase',
  'listbox',
  'listboxrow',
  'listheader',
  'listitem',
  'listitemfactory',
  'listview',
  'mediacontrols',
  'mediafile',
  'mediastream',
  'menubutton',
  'multifilter',
  'multiselection',
  'multisorter',
  'native',
  'nativedialog',
  'noselection',
  'notebook',
  'notebookpage',
  'numericsorter',
  'orientable',
  'overlay',
  'padactionentry',
  'padcontroller',
  'pagesetup',
  'paned',
  'papersize',
  'passwordentry',
  'picture',
  'popover',
  'popovermenu',
  'popovermenubar',
  'printcontext',
  'printdialog',
  'printoperation',
  'printoperationpreview',
  'printsettings',
  'printsetup',
  'progressbar',
  'range',
  'recentinfo',
  'recentmanager',
  'requisition',
  'revealer',
  'root',
  'scale',
  'scalebutton',
  'scrollable',
  'scrollbar',
  'scrollinfo',
  'scrolledwindow',
  'searchbar',
  'searchentry2',
  'sectionmodel',
  'selectionfiltermodel',
  'selectionmodel',
  'separator',
  'settings',
  'signallistitemfactory',
  'shortcut',
  'shortcutaction',
  'shortcutcontroller',
  'shortcutmanager',
  'shortcuttrigger',
  'singleselection',
  'sizegroup',
  'slicelistmodel',
  'snapshot',
  'sorter',
  'sortlistmodel',
  'spinbutton',
  'spinner',
  'stack',
  'stackpage',
  'stacksidebar',
  'stackswitcher',
  'stringfilter',
  'stringlist',
  'stringobject',
  'stringsorter',
  'styleprovider',
  'switch',
  'symbolicpaintable',
  'text',
  'textbuffer',
  'textchildanchor',
  'textiter',
  'textmark',
  'texttag',
  'texttagtable',
  'textview',
  'togglebutton',
  'tooltip',
  'treeexpander',
  'treelistmodel',
  'treelistrow',
  'urilauncher',
  'video',
  'viewport',
  'widget',
  'widgetpaintable',
  'window',
  'windowcontrols',
  'windowgroup',
  'windowhandle',
]

gtkmm_posix_hg_ccg_basenames = [
  'pagesetupunixdialog',
  'printer',
  'printjob',
  'printunixdialog',
]

gtkmm_deprecated_hg_ccg_basenames = [
  'appchooser',
  'appchooserbutton',
  'appchooserdialog',
  'appchooserwidget',
  'assistant',
  'assistantpage',
  'cellarea',
  'cellareabox',
  'cellareacontext',
  'celllayout',
  'cellrenderer',
  'cellrendereraccel',
  'cellrenderercombo',
  'cellrendererpixbuf',
  'cellrendererprogress',
  'cellrendererspin',
  'cellrendererspinner',
  'cellrenderertext',
  'cellrenderertoggle',
  'cellview',
  'colorbutton',
  'colorchooser',
  'colorchooserdialog',
  'combobox',
  'comboboxtext',
  'entrycompletion',
  'filechooser',
  'filechooserdialog',
  'filechoosernative',
  'filechooserwidget',
  'fontbutton',
  'fontchooser',
  'fontchooserdialog',
  'fontchooserwidget',
  'iconview',
  'infobar',
  'liststore',
  'lockbutton',
  'messagedialog',
  'searchentry',
  'shortcutlabel',
  'shortcutsgroup',
  'shortcutssection',
  'shortcutsshortcut',
  'shortcutswindow',
  'statusbar',
  'stylecontext',
  'treedragdest',
  'treedragsource',
  'treeiter',
  'treemodel',
  'treemodelfilter',
  'treemodelsort',
  'treepath',
  'treerowreference',
  'treeselection',
  'treesortable',
  'treestore',
  'treeview',
  'treeviewcolumn',
  'volumebutton',
]

# Pairs of hand-coded .h and .cc files.
gtkmm_extra_any_h_cc_basenames = [
  'accelerator',
  'accelkey',
  'bitsetconstiter',
  'init',
  'object',
  'selectionlistmodelimpl',
]

gtkmm_extra_deprecated_h_cc_basenames = [
  'cellrenderer_generation',
  'listviewtext',
  'treemodelcolumn',
  'treeview_private',
]

gtkmm_extra_h_files = [
  'version.h',
  'wrap_init.h',
]

gtkmm_extra_cc_files = []

gtkmm_extra_ph_files = [
  'private' / 'object_p.h',
]

# All .hg/.ccg files, regardless of deprecation and type of host.
gtkmm_hg_ccg_basenames = \
  gtkmm_any_hg_ccg_basenames + \
  gtkmm_posix_hg_ccg_basenames + \
  gtkmm_deprecated_hg_ccg_basenames

# Used .hg/.ccg files in the present build.
gtkmm_used_hg_ccg_basenames = gtkmm_any_hg_ccg_basenames
if not is_host_windows
  gtkmm_used_hg_ccg_basenames += gtkmm_posix_hg_ccg_basenames
endif
if build_deprecated_api
  gtkmm_used_hg_ccg_basenames += gtkmm_deprecated_hg_ccg_basenames
endif

foreach file : gtkmm_extra_any_h_cc_basenames
  gtkmm_extra_h_files += file + '.h'
  gtkmm_extra_cc_files += file + '.cc'
endforeach
gtkmm_extra_deprecated_h_files = []
gtkmm_extra_deprecated_cc_files = []
foreach file : gtkmm_extra_deprecated_h_cc_basenames
  gtkmm_extra_deprecated_h_files += file + '.h'
  gtkmm_extra_deprecated_cc_files += file + '.cc'
endforeach
gtkmm_extra_used_h_files = gtkmm_extra_h_files
gtkmm_extra_used_cc_files = gtkmm_extra_cc_files
gtkmm_extra_h_files += gtkmm_extra_deprecated_h_files
gtkmm_extra_cc_files += gtkmm_extra_deprecated_cc_files
if build_deprecated_api
  gtkmm_extra_used_h_files += gtkmm_extra_deprecated_h_files
  gtkmm_extra_used_cc_files += gtkmm_extra_deprecated_cc_files
endif

install_headers('..' / 'gtkmm.h', subdir: gtkmm_pcname)
install_headers(gtkmm_extra_used_h_files, subdir: gtkmm_pcname / 'gtkmm')
install_headers(gtkmm_extra_ph_files, subdir: gtkmm_pcname / 'gtkmm' / 'private')

untracked_gtkmm = 'untracked' / 'gtk' / 'gtkmm'
src_untracked_gtkmm = project_source_root / untracked_gtkmm

gtkmm_cpp_args = [ '-DGTKMM_BUILD=1' ]

if maintainer_mode

  # Maintainer mode. Generate .h and .cc files from .hg and .ccg files in ../src.

  # docs/reference/meson.build needs these.
  built_files_root = project_build_root
  gtkmm_built_h_file_targets = []

  # Force meson+ninja to generate source files before anything is compiled.
  # Compilation must depend on these targets.
  gtkmm_used_built_cc_file_targets = []
  gtkmm_used_built_h_file_targets = []

  hg_files = []
  foreach file : gtkmm_hg_ccg_basenames
    hg_files += '..' / 'src' / file + '.hg'
  endforeach

  # Create wrap_init.cc in project_build_root/gtk/gtkmm.
  gtkmm_used_built_cc_file_targets += custom_target('gtkmm-wrap_init.cc',
    input: hg_files,
    output: 'wrap_init.cc',
    command: [
      python3, generate_binding_py, 'generate_wrap_init',
      gmmproc_dir,
      '@OUTPUT@',
      'Gtk', # namespace
      '@INPUT@',
    ],
    build_by_default: maintainer_mode,
    install: false,
  )

  # Create .h/_p.h/.cc files in project_build_root/gtk/gtkmm
  # from .hg/.ccg files in project_source_root/gtk/src.
  foreach file : gtkmm_hg_ccg_basenames
    hg_file = '..' / 'src' / file + '.hg'
    ccg_file = '..' / 'src' / file + '.ccg'
    built_file_target = custom_target('gtkmm-' + file + '.cc',
      input: [hg_file, ccg_file],
      output: [file + '.stamp', file + '.cc', file + '.h'],
      command: [
        python3, generate_binding_py, 'gmmproc',
        gmmproc_dir,
        '@OUTPUT0@',
        file,
        meson.current_source_dir() / '..' / 'src',
        project_source_root / 'tools' / 'm4',
        gmmproc_extra_m4_dirs,
      ],
      depend_files: gtkmm_defs_files + m4_files,
      build_by_default: maintainer_mode,
      install: false,
    )
    gtkmm_built_h_file_targets += built_file_target[2]
    if gtkmm_used_hg_ccg_basenames.contains(file)
      gtkmm_used_built_cc_file_targets += built_file_target[1]
      gtkmm_used_built_h_file_targets += built_file_target[2]
    endif
  endforeach

  # Create dummy_header.h, depending on all generated headers.
  # It's created if it does not exist, but it's never updated.
  # It guarantees that all generated headers are built before gtkmm_library
  # is built, at the same time avoiding unnecessary recompilations.
  # If gtkmm_used_built_h_file_targets would be listed as sources to gtkmm_library,
  # all generated .cc files could be recompiled if one generated .h file has
  # been changed.
  built_dummy_h_file_target = custom_target('gtkmm-dummy_header.h',
    input: gtkmm_built_h_file_targets,
    output: 'dummy_header.h',
    command: [
      python3, dummy_header_py,
      '@OUTPUT@',
    ],
    build_by_default: maintainer_mode,
    install: false,
  )

  extra_include_dirs = ['..', '..' / '..' / 'gdk', '..' / '..' / 'gsk']

  gtk_gen_sources = gtkmm_used_built_cc_file_targets

  built_h_cc_dir = meson.current_build_dir()

else # not maintainer_mode

  # Not maintainer mode. Compile built source code files in
  # project_source_root/untracked/gtk/gtkmm.

  gtkmm_used_built_h_file_targets = []

  # docs/reference/meson.build needs these.
  built_files_root = project_source_root / 'untracked'
  gtkmm_built_h_file_targets = []

  # Two cases:
  # 1. The source code comes from a tarball, where the built files
  #    are stored in project_source_root/untracked.
  #    There are no built files in the build tree.
  # 2. Files have been built in the build tree. Then maintainer_mode has
  #    been changed from true to false. Files that are missing or not up to date
  #    in project_source_root/untracked are copied from the build tree.

  # Try to copy built source code files to the source tree.
  run_command(
    python3, generate_binding_py, 'copy_built_files',
    meson.current_build_dir(),
    src_untracked_gtkmm,
    gtkmm_hg_ccg_basenames,
    check: true,
  )

  built_cc_files = [ '../..' / untracked_gtkmm / 'wrap_init.cc' ]
  foreach file : gtkmm_used_hg_ccg_basenames
    built_cc_files += '../..' / untracked_gtkmm / file + '.cc'
  endforeach

  gtk_gen_sources = built_cc_files
  built_dummy_h_file_target = []

  extra_include_dirs = [ '..', '..' / '..' / 'untracked' / 'gtk',
          '..' / '..' / 'gdk', '..' / '..' / 'untracked' / 'gdk',
          '..' / '..' / 'gsk', '..' / '..' / 'untracked' / 'gsk',
  ]

  built_h_cc_dir = src_untracked_gtkmm

endif

extra_gtkmm_objects = []

# Build the .rc file for Windows builds and link to it
if is_host_windows
  windows = import('windows')
  gtkmm_res = windows.compile_resources(gtkmm_rc)
  extra_gtkmm_objects += gtkmm_res
endif

gtkmm_library = library(gtkmm_libname, extra_gtkmm_objects,
  gtk_gen_sources, built_dummy_h_file_target, gtkmm_extra_used_cc_files,
  implicit_include_directories: false,
  include_directories: extra_include_dirs,
  cpp_args: gtkmm_cpp_args,
  version: gtkmm_libversion,
  darwin_versions: macos_darwin_versions,
  dependencies: gtkmm_build_dep,
  link_whole: [gdkmm_library, gskmm_library],
  install: true,
)

# Generate .pc files, used by pkg-config.
pkg_config = import('pkgconfig')
pc_common_variables = [
  'doxytagfile=${docdir}/reference/' + gtkmm_pcname + '.tag',
  'htmlrefdir=${docdir}/reference/html',
  'htmlrefpub=https://gnome.pages.gitlab.gnome.org/' + meson.project_name(),
]
pc_variables = [
  'exec_prefix=${prefix}',
  'datarootdir=${datadir}',
  'gmmprocm4dir=${libdir}/' + gtkmm_pcname + '/proc/m4',
  'docdir=${datadir}/doc/' + gtkmm_pcname,
] + pc_common_variables
pc_uninstalled_variables = [
  'gmmprocm4dir=${srcdir}/tools/m4',
  'docdir=${prefix}/docs',
] + pc_common_variables

pkg_config.generate(gtkmm_library,
  filebase: gtkmm_pcname,
  variables: pc_variables,
  uninstalled_variables: pc_uninstalled_variables,
  name: meson.project_name(),
  description: 'C++ binding for the GTK toolkit',
  url: 'https://gtkmm.gnome.org/',
  requires: gtkmm_pc_requires,
  subdirs: [gtkmm_pcname],
  extra_cflags: ['-I${libdir}/' + gtkmm_pcname + '/include'],
)

# Install built .h and _p.h files.
meson.add_install_script(
  python3, generate_binding_py, 'install_built_h_files',
  built_h_cc_dir,
  install_includedir / gtkmm_pcname / 'gtkmm', # subdir below {prefix}
  gtkmm_used_hg_ccg_basenames,
  install_tag: 'devel',
)

# Distribute built files.
meson.add_dist_script(
  python3, generate_binding_py, 'dist_built_files',
  built_h_cc_dir,
  untracked_gtkmm,
  gtkmm_hg_ccg_basenames,
)

# This is used when building demo programs and test programs.
# It's also a part of gtkmm_dep, when gtkmm is a subproject.
gtkmm_own_dep = declare_dependency(
  sources: gdkmm_used_built_h_file_targets + gskmm_used_built_h_file_targets + gtkmm_used_built_h_file_targets,
  link_with: gtkmm_library,
  include_directories: extra_include_dirs,
  dependencies: gtkmm_build_dep,
)
