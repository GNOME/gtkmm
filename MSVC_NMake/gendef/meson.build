# MSVC_NMake/gendef

# Input: is_msvc
# Output: gendef, build_shared_libs_directly

# Used to generate the .def file required to obtain the import .lib file
if is_msvc and not build_shared_libs_directly
  gendef_cxx_flags = cpp_compiler.get_supported_arguments(['/wd4828'])
  gendef = executable('gendef', 'gendef.cc', cpp_args: gendef_cxx_flags, install: false,)
endif
