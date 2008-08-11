!ifndef WRITEENVSTR_INCLUDED
!define WRITEENVSTR_INCLUDED

!include WinMessages.nsh
!include IsNT.nsh

!define WriteSysEnvStr_RegKey 'HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"'
!define WriteEnvStr_RegKey 'HKCU "Environment"'

#
# WriteEnvStr - Writes an environment variable
# Note: Win9x systems requires reboot
#
# Example:
#  Push "HOMEDIR"           # name
#  Push "C:\New Home Dir\"  # value
#  Push 0                   # system
#  Call WriteEnvStr
#
!macro WriteEnvStr un
Function ${un}WriteEnvStr
  Exch $3
  Exch
  Exch $1
  Exch 2
  Exch $0
  Push $2
  
  Call ${un}IsNT
  Pop $2
  StrCmp $2 1 WriteEnvStr_NT
    ; Not on NT
    StrCpy $2 $WINDIR 2 ; Copy drive of windows (c:)
    FileOpen $2 "$2\autoexec.bat" a
    FileSeek $2 0 END
    FileWrite $2 "$\r$\nSET $0=$1$\r$\n"
    FileClose $2
    SetRebootFlag true
    Goto WriteEnvStr_done

    WriteEnvStr_NT:
    StrCmp $3 1 0 WriteEnvStr_User
      WriteRegStr ${WriteSysEnvStr_RegKey} $0 $1
      Goto WriteEnvStr_Pass
    WriteEnvStr_User:
      WriteRegStr ${WriteEnvStr_RegKey} $0 $1
    WriteEnvStr_Pass:
      SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} \
        0 "STR:Environment" /TIMEOUT=5000
  
  WriteEnvStr_done:
    Pop $2
    Pop $0
    Pop $3
    Pop $1
FunctionEnd
!macroend
!insertmacro WriteEnvStr ""
!insertmacro WriteEnvStr "un."

#
# un.DeleteEnvStr - Removes an environment variable
# Note: Win9x systems requires reboot
#
# Example:
#  Push "HOMEDIR"           # name
#  Push 0                   # system
#  Call un.DeleteEnvStr
#
Function un.DeleteEnvStr
  Exch $6 ; $0 now has the name of the variable
  Exch
  Exch $0
  Push $1
  Push $2
  Push $3
  Push $4
  Push $5
  
  Call un.IsNT
  Pop $1
  StrCmp $1 1 DeleteEnvStr_NT
    ; Not on NT
    StrCpy $1 $WINDIR 2
    FileOpen $1 "$1\autoexec.bat" r
    GetTempFileName $4
    FileOpen $2 $4 w
    StrCpy $0 "SET $0="
    SetRebootFlag true
    
    DeleteEnvStr_dosLoop:
      FileRead $1 $3
      StrLen $5 $0
      StrCpy $5 $3 $5
      StrCmp $5 $0 DeleteEnvStr_dosLoop
      StrCmp $5 "" DeleteEnvStr_dosLoopEnd
      FileWrite $2 $3
      Goto DeleteEnvStr_dosLoop
    
    DeleteEnvStr_dosLoopEnd:
      FileClose $2
      FileClose $1
      StrCpy $1 $WINDIR 2
      Delete "$1\autoexec.bat"
      CopyFiles /SILENT $4 "$1\autoexec.bat"
      Delete $4
      Goto DeleteEnvStr_done

  DeleteEnvStr_NT:
    StrCmp $6 1 0 DeleteEnvStr_User
      DeleteRegValue ${WriteSysEnvStr_RegKey} $0
      Goto DeleteEnvStr_Pass
    DeleteEnvStr_User:
      DeleteRegValue ${WriteEnvStr_RegKey} $0
    DeleteEnvStr_Pass:
    SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} \
      0 "STR:Environment" /TIMEOUT=5000
  
  DeleteEnvStr_done:
    Pop $5
    Pop $4
    Pop $3
    Pop $2
    Pop $1
    Pop $0
    Pop $6
FunctionEnd

!endif
