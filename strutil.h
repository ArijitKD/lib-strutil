#ifndef LIBC_STRUTIL_H
    #define LIBC_STRUTIL_H
    #ifdef _WIN32
        #include <stddef.h>
        typedef ptrdiff_t ssize_t;  // win32 might not define ssize_t
    #endif
    #include <string.h>
    unsigned int equals (const char* string1, const char* string2);
    char* copy (const char* string);
    void reverse (char* string);
    char* reversecopy (const char* string);
    unsigned int startswith (const char* pattern, const char* string);
    unsigned int endswith (const char* pattern, const char* string);
    ssize_t find (const char* pattern, const char* string);
    ssize_t indexof (const char* pattern, const char* string);
    ssize_t rindexof (const char* pattern, const char* string);
    char* substring (size_t start, size_t end, const char* string);
#endif
