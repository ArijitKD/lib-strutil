@echo off

if "%1" == "32" goto run
if "%1" == "64" goto run

echo Invalid binary architecture: %1
exit /b 1

:run
    mkdir build\win\lib%1   2>NUL

    echo Generating %1-bit binaries...
    gcc -m%1 -D ENABLE_STRUTIL_WCHAR -c strutil.c -o strutil_wchar.o -Wall -Wextra -Wpedantic -O2
    ar rcs build\win\lib%1\strutil_wchar.lib strutil_wchar.o
    del strutil_wchar.o

    gcc -m%1 -c strutil.c -o strutil.o  -Wall -Wextra -Wpedantic -O2
    ar rcs build\win\lib%1\strutil.lib strutil.o
    del strutil.o
    echo Done.
