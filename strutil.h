#ifndef STRUTIL_H
    #define STRUTIL_H

    #ifdef __cplusplus
        extern "C" {
    #endif

    #ifdef ENABLE_STRUTIL_WCHAR
        #include <wchar.h>
        #define STRLEN wcslen
        #define STRCMP wcscmp
        #define STRNCMP wcsncmp
        #define STRCPY wcscpy
        #define STRNCPY wcsncpy
        #define STRSTR wcsstr
        typedef wchar_t STRUTIL_CHARTYPE;
    #else
        #include <string.h>
        #define STRLEN strlen
        #define STRCMP strcmp
        #define STRNCMP strncmp
        #define STRCPY strcpy
        #define STRNCPY strncpy
        #define STRSTR strstr
        typedef char STRUTIL_CHARTYPE;
    #endif

    #ifdef _WIN32                       // Platform is Windows
        #if defined(_MSC_VER)           // Compiler is MSVC
            #include <BaseTsd.h>
            typedef SSIZE_T ssize_t;
        #elif defined(__MINGW32__)      // MinGW compiler
            #include <sys/types.h>
        #else                           // For other less common/unknown compilers
            typedef long int ssize_t;   // Fallback to type-aliasing with long int for ssize_t
        #endif
    #else
        #ifdef __has_include
            #if __has_include(<unistd.h>)   // Implies a POSIX-compatible system
                #include <sys/types.h>
            #else                           // Implies a non-POSIX system
                typedef long int ssize_t;   // Fallback to type-aliasing with long int for ssize_t
            #endif
        #else                               // No __has_include (means no proper way to verify for POSIX)
            typedef long int ssize_t;       // Fallback to type-aliasing with long int for ssize_t
        #endif
    #endif

    unsigned int equals (const STRUTIL_CHARTYPE* string1, const STRUTIL_CHARTYPE* string2);
    STRUTIL_CHARTYPE* copy (const STRUTIL_CHARTYPE* string);
    void reverse (STRUTIL_CHARTYPE* string);
    STRUTIL_CHARTYPE* reversecopy (const STRUTIL_CHARTYPE* string);
    int startswith (const STRUTIL_CHARTYPE* pattern, const STRUTIL_CHARTYPE* string);
    int endswith (const STRUTIL_CHARTYPE* pattern, const STRUTIL_CHARTYPE* string);
    ssize_t find (const STRUTIL_CHARTYPE* pattern, const STRUTIL_CHARTYPE* string);
    ssize_t indexof (const STRUTIL_CHARTYPE* pattern, const STRUTIL_CHARTYPE* string);
    ssize_t rindexof (const STRUTIL_CHARTYPE* pattern, const STRUTIL_CHARTYPE* string);
    STRUTIL_CHARTYPE* substring (size_t start, size_t end, const STRUTIL_CHARTYPE* string);

    #ifdef __cplusplus
        }
    #endif
#endif
