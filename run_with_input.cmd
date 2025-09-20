@echo off
setlocal
set EXE=%~1
set INPUT=%~2
if not exist "%EXE%" (
  echo Executable not found: "%EXE%"
  exit /b 1
)
if not exist "%INPUT%" (
  echo Input file not found: "%INPUT%"
  exit /b 1
)
"%EXE%" < "%INPUT%"
