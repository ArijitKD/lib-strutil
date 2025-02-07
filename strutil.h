#ifndef LIBC_STRUTIL_H
    #define LIBC_STRUTIL_H
    #ifdef _WIN32
        #include <stddef.h>
        typedef ptrdiff_t ssize_t;  // win32 might not define ssize_t
    #endif
    #include <string.h>
    unsigned int equals (const char* str1, const char* str2);
    char* copy (const char* str);
    void reverse (char* str);
    char* reversecopy (const char* str);
    unsigned int startswith (const char* startstr, const char* str);
    unsigned int endswith (const char* endstr, const char* str);
    ssize_t find (const char* findstr, const char* str);
    ssize_t indexof (const char* substr, const char* str);
    ssize_t rindexof (const char* substr, const char* str);
    char* substring (size_t start, size_t end, const char* str);
#endif
