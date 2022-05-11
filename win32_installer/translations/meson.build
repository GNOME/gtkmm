# win32_installer

# Input:
# Output: installer_translations_data_files

installer_translations_data_files = [
  'english.nsh',
  'french.nsh',
  'simpchinese.nsh',
# 'tradchinese.nsh',  #TODO
]

foreach f: installer_translations_data_files
  configure_file(input: f, output: f, copy: true)
endforeach