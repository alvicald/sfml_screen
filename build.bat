@echo off

set BUILD_PATH=%~dp0build
set BIN_PATH=%~dp0bin

if exist %BUILD_PATH% (
  rmdir /s /q %BUILD_PATH%
)

if exist %BIN_PATH% (
  rmdir /s /q %BIN_PATH%
)

cmake -S . -B build && cmake --build build

if %ERRORLEVEL%==0 (
  echo Build finished.
) else (
	echo Build error: %ERRORLEVEL%
)
