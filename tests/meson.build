# tests

# Input: gtkmm_own_dep, build_tests, run_tests, gui_app_ldflags
# Output: -

test_programs = [
# [[dir-name], exe-name, [sources], GUI, execute]
  [['bitset_iterator'], 'test', ['main.cc'], false, true],
  [['builder'], 'test', ['main.cc'], true, false],
  [['child_widget'], 'test', ['main.cc', 'testwindow.cc'], true, false],
  [['child_widget2'], 'test', ['main.cc'], true, false],
  [['child_widget_managed'], 'test', ['main.cc'], true, false],
  [['delete_cpp_child'], 'test', ['main.cc'], true, false],
  [['dialog_deletethis'], 'test', ['main.cc'], true, false],
  [['filedialog'], 'test', ['main.cc'], true, false],
  [['gdk_graphene'], 'test', ['main.cc'], false, true],
  [['gdk_rgba'], 'test', ['main.cc'], false, true],
  [['get_children'], 'test', ['main.cc'], true, true],
  [['main_with_options'], 'test', ['main.cc'], true, false],
  [['object_move'], 'test', ['main.cc'], false, true],
  [['property_notification'], 'test', ['main.cc'], true, false],
  [['refcount_dialog'], 'test', ['main.cc'], true, false],
  [['scrolledwindow'], 'test', ['main.cc'], true, false],
  [['tree_model_iterator'], 'test', ['main.cc'], false, true],
  [['wrap_existing'], 'test', ['main.cc'], false, true],
]

foreach ex : test_programs
  dir = ''
  foreach dir_part : ex[0]
    dir = dir / dir_part
  endforeach
  ex_name = (dir / ex[1]).underscorify()
  ex_sources = []
  foreach src : ex[2]
    ex_sources += dir / src
  endforeach

  exe_file = executable(ex_name, ex_sources,
    dependencies: gtkmm_own_dep,
    implicit_include_directories: false,
    win_subsystem: ex[3] ? 'windows' : 'console',
    build_by_default: build_tests,
    link_args: ex[3] ? gui_app_ldflags : [],
    install: false,
  )

  # If exe_file is a test program, it is built by default unconditionally.
  if ex[4] and run_tests
    test(ex_name, exe_file)
  endif
endforeach

# An Autotools build also contains a test that is supposed to check all
# docs/reference/html/*.html files with xmllint. It's omitted here because
# 1. the test does not do anything since the wrong directory is searched,
# 2. it's not clear why 'make check' or 'ninja test' in gtkmm shall fail
#    if Doxygen writes non-standard html files. (If the right directory is
#    searched, the test finds errors in at least one html file.)

#test('test_validate_docs_html', python3,
#  args: [
#    meson.current_source_dir() / 'test_validate_docs_html.py',
#    project_build_root / 'docs' / 'reference' / 'html',
#  ],
#)
