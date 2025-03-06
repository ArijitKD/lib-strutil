@echo off

if %1 == 32 goto run
if %1 == 64 goto run

echo Invalid binary architecture: %1
exit /b 1

:run
    mkdir testbuild\win\lib%1   2>NUL

    echo Generating %1-bit binaries...
    gcc -m%1 -D ENABLE_STRUTIL_WCHAR -c strutil.c -o strutil_wchar.o -Wall -Wextra -Wpedantic
    ar rcs testbuild\win\lib%1\strutil_wchar.lib strutil_wchar.o
    del *.o

    gcc -m%1 -c strutil.c -o strutil.o  -Wall -Wextra -Wpedantic
    ar rcs testbuild\win\lib%1\strutil.lib strutil.o
    del *.o
    echo Done.
    