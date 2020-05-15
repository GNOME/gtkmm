@echo off
REM get-gmmproc-ver: Grab first line of a gmmproc-generated
REM .h file to see which version of gmmproc is used to
REM generate the header

if "%1" == "" goto :usage

call :print_first_line %1
goto :eof

:print_first_line
setlocal EnableDelayedExpansion
set /a line=0

for /f ^"usebackq^ eol^=^ delims^=^" %%l in (%1) do (
  if "!line!" == "1" goto :eof
  echo %%l>tmp.txt
  for /f "tokens=1-5" %%a in (tmp.txt) do (
    if not "%%a" == "//" goto :not_gmmproc
    if not "%%b" == "Generated" goto :not_gmmproc
    if not "%%c" == "by" goto :not_gmmproc
    if not "%%d" == "gmmproc" goto :not_gmmproc
    echo GMMPROC_VER=%%e
  )
  del /f tmp.txt
  set /a line+=1
)

:not_gmmproc
echo This is not a gmmproc generated file.
goto :eof

:usage
echo Usage: get-gmmproc-ver ^<generated-header^>