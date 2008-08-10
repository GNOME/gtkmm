
; Title          String Utilities
; Author         Cedric Gustin <cedric.gustin@swing.be>

; Shamely borrowed from NSIS Archive

!ifndef STRING_UTILITIES_NSH
!define STRING_UTILITIES_NSH

; StrCut
 ; Input, top of stack = string to search for
 ;        top of stack-1 = string to search in
 ; Output, top of stack : Part of the string starting with occurence of pattern
 ;
 ; Modifies no other variables.
 ;
 ; Usage:
 ;   Push "this is a long ass string"
 ;   Push "ass"
 ;   Call String_StrCut
 ;   Pop $R0
 ;  ($R0 at this point is "ass string")

Function String_StrCut

   Exch $R1
   Exch 
   Exch $R2
   Push $R3
   Push $R4
   Push $R5
   StrLen $R3 $R1
   StrCpy $R4 0
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


!endif ; STRING_UTILITIES_NSH
