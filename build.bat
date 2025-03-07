@echo off

if "%1" == "" (
    echo Usage: %0 ^<32^|64^>
    exit /b 1
)

if "%1" == "32" goto run
if "%1" == "64" goto run

echo Invalid binary architecture: %1
exit /b 1

:run
    if not exist build\win\lib%1 mkdir build\win\lib%1

    echo Generating %1-bit binaries...

    gcc -m%1 -D ENABLE_STRUTIL_WCHAR -c strutil.c -o strutil_wchar.o -Wall -Wextra -Wpedantic -O2
    if %errorlevel% neq 0 exit /b %errorlevel%

    ar rcs build\win\lib%1\strutil_wchar.lib strutil_wchar.o
    if %errorlevel% neq 0 exit /b %errorlevel%
    del /f strutil_wchar.o

    gcc -m%1 -c strutil.c -o strutil.o -Wall -Wextra -Wpedantic -O2
    if %errorlevel% neq 0 exit /b %errorlevel%

    ar rcs build\win\lib%1\strutil.lib strutil.o
    if %errorlevel% neq 0 exit /b %errorlevel%
    del /f strutil.o

    echo Done.