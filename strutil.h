#ifndef STRUTIL_H
#define STRUTIL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

#ifdef ENABLE_STRUTIL_WCHAR
    #include <wchar.h>
    #define STRLEN  wcslen
    #define STRCMP  wcscmp
    #define STRNCMP wcsncmp
    #define STRCPY  wcscpy
    #define STRNCPY wcsncpy
    #define STRSTR  wcsstr
    typedef wchar_t STRUTIL_CHARTYPE;
#else
    #include <string.h>
    #define STRLEN  strlen
    #define STRCMP  strcmp
    #define STRNCMP strncmp
    #define STRCPY  strcpy
    #define STRNCPY strncpy
    #define STRSTR  strstr
    typedef char STRUTIL_CHARTYPE;
#endif

#ifdef _WIN32                          // Platform is Windows
    #ifdef _MSC_VER                    // Compiler is MSVC
        #include <BaseTsd.h>
        typedef SSIZE_T ssize_t;
    #elif (!defined(__MINGW32__))      // For non-MinGW compilers
        typedef long int ssize_t;      // Fallback: alias long int to ssize_t
    #endif
#else                                  // Non-Windows platforms
    #if defined(__has_include)
        #if (!__has_include(<unistd.h>))  // Implies a non-POSIX-compatible system
            typedef long int ssize_t;     // Fallback: alias long int to ssize_t
        #endif
    #else
        #error "Please compile using a C/C++17 or newer compiler."
    #endif
#endif

#define EOB ((void*)-1)     // End of buffer character for pointer buffers

#define strbuflen(string)   (STRLEN(string) + 1)        // Gives the length of the string's buffer.
#define nullterm(_Strlen)   (_Strlen + 1)               // Accounts for the null byte in string length functions.

/*
 * Checks if two strings are equal and returns 1 if true, 0 otherwise.
 */
bool equals (const STRUTIL_CHARTYPE *string1, const STRUTIL_CHARTYPE *string2);

/* 
 * Returns a pointer to a shallow copy of the given string. This function dynamically allocates
 * memory for the string. This memory may need to be freed by the caller to avoid memory
 * leaks. If memory allocation fails or the function receives a NULL pointer, returns NULL.
 */
STRUTIL_CHARTYPE *copy (const STRUTIL_CHARTYPE *string);

/*
 * Reverses the given string. This function attempts to modify the given string. Make sure
 * that the string being passed is a modifiable character array or a dynamically allocated
 * character buffer. Use reversecopy() for read-only strings.
 */
void reverse (STRUTIL_CHARTYPE *string);

/*
 * Creates a new dynamically allocated copy of the given string, reverses it, and returns
 * a pointer to the newly created buffer. Needs to be freed by the caller to prevent
 * memory leaks. If memory allocation fails or the function receives a NULL pointer,
 * returns NULL.
 */
STRUTIL_CHARTYPE *reversecopy (const STRUTIL_CHARTYPE *string);

/*
 * Check if the given string starts with the given pattern. Returns 1 if true, 0 otherwise.
 */
bool startswith (const STRUTIL_CHARTYPE *pattern, const STRUTIL_CHARTYPE *string);

/*
 * Check if the given string ends with the given pattern. Returns 1 if true, 0 otherwise.
 */
bool endswith (const STRUTIL_CHARTYPE *pattern, const STRUTIL_CHARTYPE *string);

/*
 * Searches for the given pattern in the string and returns the index of the first matching character.
 * If the pattern cannot be found, returns -1.
 */
ssize_t find (const STRUTIL_CHARTYPE *pattern, const STRUTIL_CHARTYPE *string);

/*
 * Searches for the given pattern in the string and returns the index of the first matching character.
 * If the pattern cannot be found, returns -1.
 */
ssize_t indexof (const STRUTIL_CHARTYPE *pattern, const STRUTIL_CHARTYPE *string);

/*
 * Searches for the given pattern in the string from the right and returns the index of the first matching
 * character. If the pattern cannot be found, returns -1.
 */
ssize_t rindexof (const STRUTIL_CHARTYPE *pattern, const STRUTIL_CHARTYPE *string);

/*
 * Returns a pointer to a dynamically allocated character buffer containing a substring from the given string, 
 * starting with index (start) and ending with index (end - 1).
 */
STRUTIL_CHARTYPE *substring (size_t start, size_t end, const STRUTIL_CHARTYPE *string);

#ifdef __cplusplus
}
#endif

#endif
