
; Title:        NSIS Script to compare version strings
; Author:       Afrow UK (NSIS Archive)
; Date:         2005/01/10
;
; Usage:        ${VersionCheckNew2} "version 1" "version 2" "output variable"
; Example:      ${VersionCheckNew2} "1.0.1" "1.1.0" "$R0"
;               MessageBox MB_OK "Return value: $R0" ;outputs 2

!ifndef VERSIONCHECK_NSH
!define VERSIONCHECK_NSH

!macro VersionCheck Ver1 Ver2 OutVar
 Push "${Ver1}"
 Push "${Ver2}"
  Call VersionCheckNew2
 Pop "${OutVar}"
!macroend
!define VersionCheck "!insertmacro VersionCheck"

Function VersionCheckNew2
 Exch $R0 ; second version number
 Exch
 Exch $R1 ; first version number
 Push $R2
 Push $R3
 Push $R4
 Push $R5
 Push $R6

  StrCpy $R0 $R0.
  StrCpy $R1 $R1.
  StrLen $R2 $R0
  StrLen $R3 $R1

  LoopVer1:
  StrCpy $R4 $R0 1 -$R2
  StrCmp $R2 0 0 +3
   StrCpy $R5 0
   Goto LoopVer2
  StrCmp $R4 . +3
   IntOp $R2 $R2 - 1
   Goto LoopVer1

    StrCpy $R5 $R0 -$R2
    IntOp $R2 $R2 - 1
    StrCpy $R0 $R0 "" -$R2

  LoopVer2:
  StrCpy $R4 $R1 1 -$R3
  StrCmp $R3 0 0 +3
   StrCpy $R6 0
   Goto Compare
  StrCmp $R4 . +3
   IntOp $R3 $R3 - 1
   Goto LoopVer2

    StrCpy $R6 $R1 -$R3
    IntOp $R3 $R3 - 1
    StrCpy $R1 $R1 "" -$R3

 Compare:
 StrCpy $R5 1$R5
 StrCpy $R6 1$R6
 IntCmp $R5 $R6 SameVers NewerVer1 NewerVer2

 SameVers:
  StrCmp $R2 0 +2 LoopVer1
  StrCmp $R3 0 0 LoopVer1
  StrCpy $R0 0
  Goto Done

 NewerVer1:
  StrCpy $R0 1
  Goto Done

 NewerVer2:
  StrCpy $R0 2

 Done:

 Pop $R6
 Pop $R5
 Pop $R4
 Pop $R3
 Pop $R2
 Pop $R1
 Exch $R0 ; output
FunctionEnd

!endif ; VERSIONCHECK_NSH
