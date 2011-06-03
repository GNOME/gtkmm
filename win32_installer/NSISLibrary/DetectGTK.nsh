
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
;    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

!ifndef DETECT_GTK_NSH
!define DETECT_GTK_NSH

!include "VersionCheck.nsh"

Function CheckGTKRuntime
  Pop $R1

  ClearErrors
  ReadRegStr $R0 HKLM "Software\GTK\2.0" "Version"
  IfErrors 0 +2
  ReadRegStr $R0 HKCU "Software\GTK\2.0" "Version"
  ${VersionCheck} $R1 $R0 "$R2"
  StrCmp $R2 "1" "" gtk_ok
!ifdef RUNTIME_ONLY
  Push "$(GTK_RUNTIME_REQUIRED)"
!else
  Push "$(GTK_DEVEL_REQUIRED)"
!endif
  Pop $R0
  ; Do not install GTK+ in silent mode
  IfSilent gtk_ok
  MessageBox MB_YESNOCANCEL|MB_ICONEXCLAMATION $R0 IDNO gtk_ok IDCANCEL abortInstall
  DetailPrint "$(GTK_DOWNLOADING)"
!ifdef RUNTIME_ONLY
  Push "gtk_runtime_setup"
  Pop $R0
!else
  Push "gtk_devel_setup"
  Pop $R0
!endif
  NSISdl::download /TIMEOUT=30000 "http://ftp.gnome.org/pub/GNOME/binaries/win32/gtkmm/${PRODUCT_VERSION_MAJOR}.${PRODUCT_VERSION_MINOR}/$R0-$R1.ini" "$TEMP\gtk_setup.ini"
  Pop $0 ;Get the return value
  StrCmp $0 "Success" DownloadGTK 0
  StrCmp $0 "Cancel" 0 +3
  Push "$(MISC_DOWNLOAD_CANCELLED)"
  Goto ExitInstallGTK
  Push "$(MISC_DOWNLOAD_ERROR)"
  Goto ExitInstallGTK
  
DownloadGTK:
  ; Get the current GTK+ installer version
  ReadINIStr $R0 "$TEMP\gtk_setup.ini" "General" "Filename"
  StrCmp $R0 0 ExitInstallGTK
  DetailPrint "$(GTK_DOWNLOADING)"
  NSISdl::download /TIMEOUT=30000 "http://heanet.dl.sourceforge.net/sourceforge/gladewin32/$R0" "$TEMP\gtk_setup.exe"
  Pop $0 ;Get the return value
  StrCmp $0 "success" InstallGTK 0
  StrCmp $0 "cancel" 0 +3
  Push "$(MISC_DOWNLOAD_CANCELLED)"
  Goto ExitInstallGTK
  Push "$(MISC_DOWNLOAD_ERROR)"
  Goto ExitInstallGTK
InstallGTK:
  DetailPrint "$(GTK_STARTING)"
  ExecWait "$TEMP\gtk_setup.exe" $0
  DetailPrint "$(GTK_FINISHED)"
  Delete "$TEMP\gtk_setup.exe"
  StrCmp $0 "0" gtk_ok 0
  Push "$(GTK_INTERRUPTED)"
  Goto ExitInstallGTK

ExitInstallGTK:
  Pop $2
  MessageBox MB_YESNO "$(GTK_INTERRUPT_REASON)" IDYES gtk_ok IDNO abortInstall

abortInstall:
  Quit

gtk_ok:

FunctionEnd

!endif ; DETECT_GTK_NSH
