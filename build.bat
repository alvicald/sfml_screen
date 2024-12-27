@echo off

cmake -S . -B build
cmake --build build

if %ERRORLEVEL%==0 
(
    echo Build finished.
) 
else 
(
    echo Build error: %ERRORLEVEL%
)