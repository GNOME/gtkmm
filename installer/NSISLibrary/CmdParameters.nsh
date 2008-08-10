
; Title          Command line parameter utilities
; Author         Cedric Gustin <cedric.gustin@swing.be>

; Shamely borrowed from NSIS Archive

!ifndef CMD_PARAMETERS_NSH
!define CMD_PARAMETERS_NSH

!include "StrFunc.nsh"
${StrLoc} # Supportable for Install Sections and Functions

; Cmd_GetParameter
 ; Input, top of stack = parameter to search for
 ; Output, top of stack = string with value of the parameter
 ; 
 ; Modifies no other variables.
 
Function Cmd_GetParameter

  Push $R0
  Exch
  Pop $R0
  Push $0
  Push $1
  Push $2
  Push $R1
  Call Cmd_GetAllParameters
  Pop $2
  # Search for  standalone parameter
  ${StrLoc} $R1 $2 "/$R0" ">"
  StrCmp $R1 "" "" +3
  StrCpy $0 ""
  Goto done
  # search for quoted /parameter
  StrCpy $1 '"'
  Push $2
  StrCpy $R0 "/$R0="
  Push '"$R0'
  Call String_StrCut
  Pop $0
  StrCpy $0 $0 "" 1 # skip quote
  StrCmp $0 "" "" next
  # search for non quoted /parameter
  StrCpy $1 ' '
  Push $2
  Push '$R0'
  Call String_StrCut
  Pop $0
next:
  StrCmp $0 "" "" +3
  StrCpy $0 "1"
  Goto done
  # copy the value after /parameter=
  StrLen $R1 $R0
  StrCpy $0 $0 "" $R1
  # search for the next parameter
  Push $0
  Push $1
  Call String_StrCut
  Pop $1
  StrCmp $1 "" done
  StrLen $1 $1
  StrCpy $0 $0 -$1
done:
  Pop $R1
  Pop $2
  Pop $1
  Exch
  Pop $R0 
  Exch $0

FunctionEnd

; Cmd_GetAllParameters
 ; Input, none
 ; Output, top of stack = Command line parameters
 ;
 ; Modifies no other variables.

Function Cmd_GetAllParameters
 
   Push $R0
   Push $R1
   Push $R2
   Push $R3
   
   StrCpy $R2 1
   StrLen $R3 $CMDLINE
   
   ;Check for quote or space
   StrCpy $R0 $CMDLINE $R2
   StrCmp $R0 '"' 0 +3
     StrCpy $R1 '"'
     Goto loop
   StrCpy $R1 " "
   
   loop:
     IntOp $R2 $R2 + 1
     StrCpy $R0 $CMDLINE 1 $R2
     StrCmp $R0 $R1 get
     StrCmp $R2 $R3 get
     Goto loop
   
   get:
     IntOp $R2 $R2 + 1
     StrCpy $R0 $CMDLINE 1 $R2
     StrCmp $R0 " " get
     StrCpy $R0 $CMDLINE "" $R2
   
   Pop $R3
   Pop $R2
   Pop $R1
   Exch $R0
 
FunctionEnd

!endif ; CMD_PARAMETERS_NSH
