!ifndef PATHMANI_INCLUDED
!define PATHMANI_INCLUDED

!verbose 3
!include WriteEnvStr.nsh
!verbose 4

; AddToPath - Adds the given dir to the search path.
;        Input - head of the stack
;        Note - Win9x systems requires reboot

Function AddToPath
  Exch $0
  Exch
  Exch $4
  Push $1
  Push $2
  Push $3

  # don't add if the path doesn't exist
  #IfFileExists $0 "" AddToPath_done

  Push $4
  Push "PATH"  
  Call MyReadRegStr
  Pop $1

  Push "$1;"
  Push "$0;"
  Call StrStr
  Pop $2
  StrCmp $2 "" "" AddToPath_done
  Push "$1;"
  Push "$0\;"
  Call StrStr
  Pop $2
  StrCmp $2 "" "" AddToPath_done

  Call IsNT
  Pop $1
  StrCmp $1 1 AddToPath_NT
    ; Not on NT
    StrCpy $1 $WINDIR 2
    FileOpen $1 "$1\autoexec.bat" a
    FileSeek $1 -1 END
    FileReadByte $1 $2
    IntCmp $2 26 0 +2 +2 # DOS EOF
      FileSeek $1 -1 END # write over EOF
    FileWrite $1 "$\r$\nSET PATH=%PATH%;$0$\r$\n"
    FileClose $1
    SetRebootFlag true
    Goto AddToPath_done

  AddToPath_NT:
    StrCmp $4 "1" 0 +3
    ReadRegStr $1 HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "PATH"
    Goto +2
    ReadRegStr $1 HKCU "Environment" "PATH"
    # StrCpy $2 $1 1 -1 # copy last char
    # StrCmp $2 ";" 0 +2 # if last char == ;
    #   StrCpy $1 $1 -1 # remove last char
    # StrCmp $1 "" AddToPath_NTdoIt
    #    StrCpy $0 "$1;$0"
    StrCpy $0 "$0;$1"
    # AddToPath_NTdoIt:
      StrCmp $4 "1" 0 +3
      WriteRegExpandStr HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "PATH" $0
      Goto +2
      WriteRegExpandStr HKCU "Environment" "PATH" $0
      SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=5000

AddToPath_done:
  Pop $3
  Pop $2
  Pop $1
  Pop $4
  Pop $0
FunctionEnd

Function AddPathToRegVal
  Exch $0
  Exch
  Exch $3
  Exch 2
  Exch $2
  Exch 3
  Exch $1
  Push $4

  StrCmp $1 "HKCU" 0 +4
  ClearErrors
  ReadRegStr $4 HKCU $2 $3
  Goto +3
  ClearErrors
  ReadRegStr $4 HKLM $2 $3
  IfErrors AddPathToRegVal_skip
  
  StrCpy $0 "$0;$4"
  StrCmp $1 "HKCU" 0 +3
  WriteRegStr HKCU $2 $3 $0
  Goto +2
  WriteRegStr HKLM $2 $3 $0

AddPathToRegVal_skip:

  Pop $4
  Pop $1
  Pop $0
  Pop $3
  Pop $2
FunctionEnd

Function AddPathToEnvVar
  Exch $3
  Exch
  Exch $2
  Exch 2
  Exch $1
  Push $4

  Push $1
  Push $2
  Call MyReadRegStr
  Pop $4

  StrCpy $3 "$3;$4"
  Push $2
  Push $3
  Push $1
  Call WriteEnvStr

  Pop $4
  Pop $1
  Pop $3
  Pop $2
FunctionEnd

; RemoveFromPath - Remove a given dir from the path
;     Input: head of the stack

Function un.RemoveFromPath
  Exch $0
  Exch
  Exch $7
  Push $1
  Push $2
  Push $3
  Push $4
  Push $5
  Push $6

  IntFmt $6 "%c" 26 # DOS EOF

  Call un.IsNT
  Pop $1
  StrCmp $1 1 unRemoveFromPath_NT
    ; Not on NT
    StrCpy $1 $WINDIR 2
    FileOpen $1 "$1\autoexec.bat" r
    GetTempFileName $4
    FileOpen $2 $4 w
    StrCpy $0 "SET PATH=%PATH%;$0"
    Goto unRemoveFromPath_dosLoop

    unRemoveFromPath_dosLoop:
      FileRead $1 $3
      StrCpy $5 $3 1 -1 # read last char
      StrCmp $5 $6 0 +2 # if DOS EOF
        StrCpy $3 $3 -1 # remove DOS EOF so we can compare
      StrCmp $3 "$0$\r$\n" unRemoveFromPath_dosLoopRemoveLine
      StrCmp $3 "$0$\n" unRemoveFromPath_dosLoopRemoveLine
      StrCmp $3 "$0" unRemoveFromPath_dosLoopRemoveLine
      StrCmp $3 "" unRemoveFromPath_dosLoopEnd
      FileWrite $2 $3
      Goto unRemoveFromPath_dosLoop
      unRemoveFromPath_dosLoopRemoveLine:
        SetRebootFlag true
        Goto unRemoveFromPath_dosLoop

    unRemoveFromPath_dosLoopEnd:
      FileClose $2
      FileClose $1
      StrCpy $1 $WINDIR 2
      Delete "$1\autoexec.bat"
      CopyFiles /SILENT $4 "$1\autoexec.bat"
      Delete $4
      Goto unRemoveFromPath_done

  unRemoveFromPath_NT:
    StrCmp $7 "1" 0 +3
    ReadRegStr $1 HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "PATH"
    Goto +2
    ReadRegStr $1 HKCU "Environment" "PATH"
    StrCpy $5 $1 1 -1 # copy last char
    StrCmp $5 ";" +2 # if last char != ;
      StrCpy $1 "$1;" # append ;
    Push $1
    Push "$0;"
    Call un.StrStr ; Find `$0;` in $1
    Pop $2 ; pos of our dir
    StrCmp $2 "" unRemoveFromPath_done
      ; else, it is in path
      # $0 - path to add
      # $1 - path var
      StrLen $3 "$0;"
      StrLen $4 $2
      StrCpy $5 $1 -$4 # $5 is now the part before the path to remove
      StrCpy $6 $2 "" $3 # $6 is now the part after the path to remove
      StrCpy $3 $5$6

      StrCpy $5 $3 1 -1 # copy last char
      StrCmp $5 ";" 0 +2 # if last char == ;
        StrCpy $3 $3 -1 # remove last char

      StrCmp $7 "1" 0 +3
      WriteRegExpandStr HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "PATH" $3
      Goto +2
      WriteRegExpandStr HKCU "Environment" "PATH" $3
      SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=5000

  unRemoveFromPath_done:
    Pop $6
    Pop $5
    Pop $4
    Pop $3
    Pop $2
    Pop $1
    Pop $7
    Pop $0
FunctionEnd

Function un.RemovePathFromRegVal
  Exch $0
  Exch
  Exch $9
  Exch 2
  Exch $8
  Exch 3
  Exch $7
  Push $1
  Push $2
  Push $3
  Push $4
  Push $5
  Push $6

  StrCmp $7 "HKCU" 0 +4
  ClearErrors
  ReadRegStr $1 HKCU $8 $9
  Goto +3
  ClearErrors
  ReadRegStr $1 HKLM $8 $9
  IfErrors RemovePathFromRegVal_done

  StrCpy $5 $1 1 -1 # copy last char
  StrCmp $5 ";" +2 # if last char != ;
  StrCpy $1 "$1;" # append ;
  Push $1
  Push "$0;"
  Call un.StrStr ; Find `$0;` in $1
  Pop $2 ; pos of our dir
  StrCmp $2 "" RemovePathFromRegVal_done
  ; else, it is in path
  # $0 - path to add
  # $1 - path var
  StrLen $3 "$0;"
  StrLen $4 $2
  StrCpy $5 $1 -$4 # $5 is now the part before the path to remove
  StrCpy $6 $2 "" $3 # $6 is now the part after the path to remove
  StrCpy $3 $5$6
  StrCpy $5 $3 1 -1 # copy last char
  StrCmp $5 ";" 0 +2 # if last char == ;
  StrCpy $3 $3 -1 # remove last char

  StrCmp $7 "HKCU" 0 +3
  WriteRegStr HKCU $8 $9 $3
  Goto +2
  WriteRegStr HKLM $8 $9 $3

RemovePathFromRegVal_done:

  Pop $6
  Pop $5
  Pop $4
  Pop $3
  Pop $2
  Pop $1
  Pop $7
  Pop $0
  Pop $9
  Pop $8
FunctionEnd

Function un.RemovePathFromEnvVar
  Exch $9
  Exch
  Exch $8
  Exch 2
  Exch $7
  Push $1
  Push $2
  Push $3
  Push $4
  Push $5
  Push $6

  Push $7
  Push $8
  Call un.MyReadRegStr
  Pop $1

  StrCpy $5 $1 1 -1 # copy last char
  StrCmp $5 ";" +2 # if last char != ;
  StrCpy $1 "$1;" # append ;
  Push $1
  Push "$9;"
  Call un.StrStr ; Find `$9;` in $1
  Pop $2 ; pos of our dir
  StrCmp $2 "" RemovePathFromEnvVar_done
  ; else, it is in path
  # $9 - path to add
  # $1 - path var
  StrLen $3 "$9;"
  StrLen $4 $2
  StrCpy $5 $1 -$4 # $5 is now the part before the path to remove
  StrCpy $6 $2 "" $3 # $6 is now the part after the path to remove
  StrCpy $3 $5$6
  StrCpy $5 $3 1 -1 # copy last char
  StrCmp $5 ";" 0 +2 # if last char == ;
  StrCpy $3 $3 -1 # remove last char

  Push $8
  Push $3
  Push $7
  Call un.WriteEnvStr

RemovePathFromEnvVar_done:

  Pop $6
  Pop $5
  Pop $4
  Pop $3
  Pop $2
  Pop $1
  Pop $7
  Pop $9
  Pop $8
FunctionEnd

###########################################
#            Utility Functions            #
###########################################

; StrStr
; input, top of stack = string to search for
;        top of stack-1 = string to search in
; output, top of stack (replaces with the portion of the string remaining)
; modifies no other variables.
;
; Usage:
;   Push "this is a long ass string"
;   Push "ass"
;   Call StrStr
;   Pop $R0
;  ($R0 at this point is "ass string")

!macro StrStr un
Function ${un}StrStr
Exch $R1 ; st=haystack,old$R1, $R1=needle
  Exch    ; st=old$R1,haystack
  Exch $R2 ; st=old$R1,old$R2, $R2=haystack
  Push $R3
  Push $R4
  Push $R5
  StrLen $R3 $R1
  StrCpy $R4 0
  ; $R1=needle
  ; $R2=haystack
  ; $R3=len(needle)
  ; $R4=cnt
  ; $R5=tmp
  loop:
    StrCpy $R5 $R2 $R3 $R4
    StrCmp $R5 $R1 done
    StrCmp $R5 "" done
    IntOp $R4 $R4 + 1
    Goto loop
done:
  StrCpy $R1 $R2 "" $R4
  Pop $R5
  Pop $R4
  Pop $R3
  Pop $R2
  Exch $R1
FunctionEnd
!macroend
!insertmacro StrStr ""
!insertmacro StrStr "un."

!macro MyReadRegStr un
Function ${un}MyReadRegStr
  Exch $1
  Exch
  Exch $0
  Push $2

  Call ${un}IsNT
  Pop $2
  StrCmp $2 1 0 MyReadRegStr_NonNT

  StrCmp $0 "1" 0 +3
  ReadRegStr $2 ${WriteSysEnvStr_RegKey} $1
  Goto MyReadRegStr_done
  ReadRegStr $2 ${WriteEnvStr_RegKey} $1
  Goto MyReadRegStr_done

MyReadRegStr_NonNT:
  ReadEnvStr $2 $1

MyReadRegStr_done:

  Exch
  Pop $0
  Exch
  Pop $1
  Exch $2
FunctionEnd
!macroend
!insertmacro MyReadRegStr ""
!insertmacro MyReadRegStr "un."

!endif
