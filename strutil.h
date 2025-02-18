#ifndef LIBC_STRUTIL_H
    #define LIBC_STRUTIL_H
    #ifdef _WIN32
        #include <stddef.h>
        typedef ptrdiff_t ssize_t;  // win32 might not define ssize_t
    #endif

    #ifdef LIBC_STRUTIL_WCHAR
        #include <wchar.h>
        #define STRLEN wcslen
        #define STRCMP wcscmp
        #define STRNCMP wcsncmp
        #define STRCPY wcscpy
        #define STRNCPY wcsncpy
        #define STRSTR wcsstr
        typedef unsigned short LIBC_STRUTIL_CHARTYPE;
    #else
        #include <string.h>
        #define STRLEN strlen
        #define STRCMP strcmp
        #define STRNCMP strncmp
        #define STRCPY strcpy
        #define STRNCPY strncpy
        #define STRSTR strstr
        typedef unsigned char LIBC_STRUTIL_CHARTYPE;
    #endif


    unsigned int equals (const LIBC_STRUTIL_CHARTYPE* string1, const LIBC_STRUTIL_CHARTYPE* string2);
    LIBC_STRUTIL_CHARTYPE* copy (const LIBC_STRUTIL_CHARTYPE* string);
    void reverse (LIBC_STRUTIL_CHARTYPE* string);
    LIBC_STRUTIL_CHARTYPE* reversecopy (const LIBC_STRUTIL_CHARTYPE* string);
    int startswith (const LIBC_STRUTIL_CHARTYPE* pattern, const LIBC_STRUTIL_CHARTYPE* string);
    int endswith (const LIBC_STRUTIL_CHARTYPE* pattern, const LIBC_STRUTIL_CHARTYPE* string);
    ssize_t find (const LIBC_STRUTIL_CHARTYPE* pattern, const LIBC_STRUTIL_CHARTYPE* string);
    ssize_t indexof (const LIBC_STRUTIL_CHARTYPE* pattern, const LIBC_STRUTIL_CHARTYPE* string);
    ssize_t rindexof (const LIBC_STRUTIL_CHARTYPE* pattern, const LIBC_STRUTIL_CHARTYPE* string);
    LIBC_STRUTIL_CHARTYPE* substring (size_t start, size_t end, const LIBC_STRUTIL_CHARTYPE* string);
#endif
