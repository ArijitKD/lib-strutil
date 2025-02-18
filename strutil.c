#include <stdlib.h>
#include "strutil.h"

// Perfected
unsigned int equals (const LIBC_STRUTIL_CHARTYPE* string1, const LIBC_STRUTIL_CHARTYPE* string2)
{
    if (string1 == NULL || string2 == NULL)
        return (string1 == string2);
    return (STRCMP(string1, string2) == 0);
}

// Perfected
LIBC_STRUTIL_CHARTYPE* copy (const LIBC_STRUTIL_CHARTYPE* string)
{
    if (string == NULL)
        return NULL;
    LIBC_STRUTIL_CHARTYPE* strcopy = (LIBC_STRUTIL_CHARTYPE*)malloc((STRLEN(string)+1)*sizeof(LIBC_STRUTIL_CHARTYPE));
    if (strcopy == NULL)
        return NULL;
    STRCPY(strcopy, string);
    return strcopy;
}

// Perfected
void reverse (LIBC_STRUTIL_CHARTYPE* string)
{
    if (string != NULL)
    {
        size_t len = STRLEN(string);
        for (size_t i=0; i<len/2; ++i)
        {
            string[i] = string[i] + string[len-(i+1)];
            string[len-(i+1)] = string[i] - string[len-(i+1)];
            string[i] = string[i] - string[len-(i+1)];
        }
    }
}

// Perfected
LIBC_STRUTIL_CHARTYPE* reversecopy (const LIBC_STRUTIL_CHARTYPE* string)
{
    if (string == NULL)
        return NULL;
    LIBC_STRUTIL_CHARTYPE* newstring = copy(string);
    if (newstring == NULL)
        return NULL;
    reverse(newstring);
    return newstring;
}

// Perfected
int startswith (const LIBC_STRUTIL_CHARTYPE* pattern, const LIBC_STRUTIL_CHARTYPE* string)
{
    if (pattern == NULL || string == NULL)
        return -1;
    if (*pattern == 0)
        return 1;
    size_t patternlen = STRLEN(pattern), stringlen = STRLEN(string);
    if (patternlen > stringlen)
        return 0;
    size_t i = 0;
    while (i < patternlen && pattern[i] == string[i])
        i++;
    return (i == patternlen);
}

// Perfected
int endswith (const LIBC_STRUTIL_CHARTYPE* pattern, const LIBC_STRUTIL_CHARTYPE* string)
{
    if (pattern == NULL || string == NULL)
        return -1;
    if (*pattern == 0)
        return 1;
    size_t j = STRLEN(pattern), i = STRLEN(string);
    if (j > i)
        return 0;
    while (j > 0)
        if (pattern[--j] != string[--i])
            return 0;
    return 1;
}

// TODO: Use Boyer-Moore algorithm with the current brute-force one and
// implement a hybrid search algorithm
ssize_t find (const LIBC_STRUTIL_CHARTYPE* pattern, const LIBC_STRUTIL_CHARTYPE* string)
{
    if (pattern == NULL || string == NULL)
        return -1;
    if (*pattern==0)
        return 0;
    if (*string==0 && *pattern!=0)
        return -1;
    size_t patternlen = STRLEN(pattern);
    size_t stringlen = STRLEN(string);
    if (patternlen > stringlen)
        return -1;

    for (size_t i = 0; i <= stringlen - patternlen; ++i)
    {
        if (STRNCMP(&string[i], pattern, patternlen) == 0)
            return i;
    }
    return -1;

    // It doesn't feel good to ditch the code that you've spent your time and energy to write, does it?
    // Commenting out my version, but using strncmp() version for better performance
    /*
    ssize_t i, j, k, found_index = -1;
    for (i=0; i<stringlen; ++i)
    {
        if (string[i] == pattern[0])
        {
            k = i;
            for (j=1; j<patternlen; ++j)
            {
                if (pattern[j] != string[++k])
                    break;
            }
            if (j == patternlen)
            {
                found_index = i;
                break;
            }
        }
    }
    return found_index;
    */
}

// Perfected
ssize_t indexof (const LIBC_STRUTIL_CHARTYPE* pattern, const LIBC_STRUTIL_CHARTYPE* string)
{
    return find(pattern, string);
}

// Perfected
ssize_t rindexof (const LIBC_STRUTIL_CHARTYPE* pattern, const LIBC_STRUTIL_CHARTYPE* string)
{
    if (pattern == NULL || string == NULL)
        return -1;
    if (*pattern==0)
        return 0;
    if (*string==0 && *pattern!=0)
        return -1;
    size_t patternlen = STRLEN(pattern);
    size_t stringlen = STRLEN(string);
    if (patternlen > stringlen)
        return -1;
    
    for (ssize_t i = stringlen - patternlen; i >= 0; --i)
    {
        if (STRNCMP(&string[i], pattern, patternlen) == 0)
            return i;
    }

    return -1;

    /*
    LIBC_STRUTIL_CHARTYPE* revpattern = reversecopy(pattern);
    LIBC_STRUTIL_CHARTYPE* revstring = reversecopy(string);
    ssize_t found_index = indexof(revpattern, revstring);
    if (found_index != -1)
        found_index = (STRLEN(revstring)-found_index)-STRLEN(revpattern);
    free(revpattern);
    free(revstring);
    return found_index;
    */
}

// Perfected
LIBC_STRUTIL_CHARTYPE* substring (size_t start, size_t end, const LIBC_STRUTIL_CHARTYPE* string)
{
    if (string == NULL)
        return NULL;
    if (equals(string, ""))
    {
        if (start == 0 && end == 0)
            return (LIBC_STRUTIL_CHARTYPE*)calloc(1, sizeof(LIBC_STRUTIL_CHARTYPE));
        else
            return NULL;
    }
    size_t maxindex = STRLEN(string)-1;
    if (start > maxindex || end > maxindex || start > end)
        return NULL;
    LIBC_STRUTIL_CHARTYPE* substr = (LIBC_STRUTIL_CHARTYPE*)malloc((end-start+1)*sizeof(LIBC_STRUTIL_CHARTYPE));
    if (substr == NULL)
        return NULL;
    for (size_t i=start, j=0; i<end; ++i, ++j)
    {
        substr[j] = string[i];
    }
    substr[end-start] = 0;
    return substr;
}
