
; Title          NSIS Script to detect the installation of a GTK+ runtime
; Author         Cedric Gustin <cedric.gustin@swing.be>

;    Copyright (C) 2004 Cedric Gustin
;
;    This program is free software; you can redistribute it and/or modify
;    it under the terms of the GNU General Public License as published by
;    the Free Software Foundation; either version 2 of the License, or
;    (at your option) any later version.
;
;    This program is distributed in the hope that it will be useful,
;    but WITHOUT ANY WARRANTY; without even the implied warranty of
;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;    GNU General Public License for more details.
;
;    You should have received a copy of the GNU General Public License
;    along with this program; if not, write to the Free Software
;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

!ifndef VERSION_STRING_NSH
!define VERSION_STRING_NSH

!include "StrFunc.nsh"
${StrTok} # Supportable for Install Sections and Functions

; Name : ParseVersionString
;
; Description:
; Parse a typical version string ("2.0.1") and return the major, minor and
; micro version numbers separately
;
; Input : Full version string at the top of the stack
; Output : macro, minor and micro version numbers from to of the stack
;
; Usage :
;   Push "2.0.1"
;   Call ParseVersionString
;   Pop $R0
;   Pop $R1
;   Pop $R2
;
; $R0, $R1, $R2 will be equal to "2", "0" and "1", respectively)

Function ParseVersionString

  ; Backup variables
  Push $0
  Push $1
  Exch 2
  Pop $0
  
  ; Get major version number
  ${StrTok} $1 $0 "." 0 1
  Push $1
  ; Get minor version number
  ${StrTok} $1 $0 "." 1 1
  Push $1
  ; Get micro version number
  ${StrTok} $1 $0 "." 2 1
  Push $1
  
  ; Restore variable
  Exch 4
  Pop $0
  Exch 2
  Pop $1
  
FunctionEnd

!endif ; VERSION_STRING_NSH
