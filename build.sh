#!/bin/sh

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <32|64>"
    exit 1
fi

if [ "$1" != "32" ] && [ "$1" != "64" ]; then
    echo "Invalid binary architecture: $1"
    exit 1
fi

mkdir -p build/posix/lib$1

echo "Generating $1-bit binaries..."

cc -m$1 -D ENABLE_STRUTIL_WCHAR -c strutil.c -o strutil_wchar.o -Wall -Wextra -Wpedantic -O2
if [ $? -ne 0 ]; then exit $?; fi

ar rcs build/posix/lib$1/strutil_wchar.lib strutil_wchar.o
rm -f strutil_wchar.o

cc -m$1 -c strutil.c -o strutil.o -Wall -Wextra -Wpedantic -O2
if [ $? -ne 0 ]; then exit $?; fi

ar rcs build/posix/lib$1/strutil.lib strutil.o
rm -f strutil.o

echo "Done."
