# win32_installer

# Input:
# Output: installer_library_data_files

installer_library_data_files = [
  'CmdParameters.nsh',
  'DetectGTK.nsh',
  'IsNT.nsh',
  'ParseVersion.nsh',
  'PathManipulation.nsh',
  'PathQuestion.ini',
  'SetContext.ini',
  'StringUtilities.nsh',
  'VersionCheck.nsh',
  'WriteEnvStr.nsh',
]

foreach f: installer_library_data_files
  configure_file(input: f, output: f, copy: true)
endforeach