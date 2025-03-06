#include <stdbool.h>
#include <stdlib.h>
#include "strutil.h"

/*
 * Checks if two strings are equal and returns 1 if true, 0 otherwise.
 */
bool equals(const STRUTIL_CHARTYPE *string1, const STRUTIL_CHARTYPE *string2)
{
    if (string1 == NULL || string2 == NULL)
        return string1 == string2;
    return STRCMP(string1, string2) == 0;
}

/* 
 * Returns a pointer to a shallow copy of the given string. This function dynamically allocates
 * memory for the string. This memory may need to be freed by the caller to avoid memory
 * leaks. If memory allocation fails or the function receives a NULL pointer, returns NULL.
 */
STRUTIL_CHARTYPE *copy(const STRUTIL_CHARTYPE *string)
{
    STRUTIL_CHARTYPE *strcopy;

    if (string == NULL)
        return NULL;
    strcopy = (STRUTIL_CHARTYPE *)malloc(strbuflen(string) * sizeof(STRUTIL_CHARTYPE));
    if (strcopy == NULL)
        return NULL;
    STRCPY(strcopy, string);
    return strcopy;
}

/*
 * Reverses the given string. This function attempts to modify the given string. Make sure
 * that the string being passed is a modifiable character array or a dynamically allocated
 * character buffer. Use reversecopy() for read-only strings.
 */
void reverse(STRUTIL_CHARTYPE *string)
{
    size_t len, i;

    if (string != NULL) {
        len = STRLEN(string);
        for (i = 0; i < len / 2; ++i) {
            string[i] = string[i] + string[len - (i + 1)];
            string[len - (i + 1)] = string[i] - string[len - (i + 1)];
            string[i] = string[i] - string[len - (i + 1)];
        }
    }
}

/*
 * Creates a new dynamically allocated copy of the given string, reverses it, and returns
 * a pointer to the newly created buffer. Needs to be freed by the caller to prevent
 * memory leaks. If memory allocation fails or the function receives a NULL pointer,
 * returns NULL.
 */
STRUTIL_CHARTYPE *reversecopy(const STRUTIL_CHARTYPE *string)
{
    STRUTIL_CHARTYPE *newstring;

    if (string == NULL)
        return NULL;
    newstring = copy(string);
    if (newstring == NULL)
        return NULL;
    reverse(newstring);
    return newstring;
}

/*
 * Check if the given string starts with the given pattern. Returns 1 if true, 0 otherwise.
 */
bool startswith(const STRUTIL_CHARTYPE *pattern, const STRUTIL_CHARTYPE *string)
{
    size_t patternlen, stringlen, i = 0;

    if (pattern == NULL || string == NULL)
        return -1;
    if (*pattern == 0)
        return 1;
    patternlen = STRLEN(pattern);
    stringlen = STRLEN(string);
    if (patternlen > stringlen)
        return 0;
    while (i < patternlen && pattern[i] == string[i])
        i++;
    return i == patternlen;
}

/*
 * Check if the given string ends with the given pattern. Returns 1 if true, 0 otherwise.
 */
bool endswith(const STRUTIL_CHARTYPE *pattern, const STRUTIL_CHARTYPE *string)
{
    size_t j, i;

    if (pattern == NULL || string == NULL)
        return -1;
    if (*pattern == 0)
        return 1;
    j = STRLEN(pattern);
    i = STRLEN(string);
    if (j > i)
        return 0;
    while (j > 0)
        if (pattern[--j] != string[--i])
            return 0;
    return 1;
}

/*
 * Searches for the given pattern in the string and returns the index of the first matching character.
 * If the pattern cannot be found, returns -1.
 */
ssize_t find(const STRUTIL_CHARTYPE *pattern, const STRUTIL_CHARTYPE *string)
{
    size_t patternlen, stringlen, i;

    if (pattern == NULL || string == NULL)
        return -1;
    if (*pattern == 0)
        return 0;
    if (*string == 0 && *pattern != 0)
        return -1;
    patternlen = STRLEN(pattern);
    stringlen = STRLEN(string);
    if (patternlen > stringlen)
        return -1;
    for (i = 0; i <= stringlen - patternlen; ++i) {
        if (STRNCMP(string + i, pattern, patternlen) == 0)
            return i;
    }
    return -1;
}

/*
 * Searches for the given pattern in the string and returns the index of the first matching character.
 * If the pattern cannot be found, returns -1.
 */
ssize_t indexof(const STRUTIL_CHARTYPE *pattern, const STRUTIL_CHARTYPE *string)
{
    return find(pattern, string);
}

/*
 * Searches for the given pattern in the string from the right and returns the index of the first matching
 * character. If the pattern cannot be found, returns -1.
 */
ssize_t rindexof(const STRUTIL_CHARTYPE *pattern, const STRUTIL_CHARTYPE *string)
{
    ssize_t i;
    size_t patternlen, stringlen;

    if (pattern == NULL || string == NULL)
        return -1;
    if (*pattern == 0)
        return 0;
    if (*string == 0 && *pattern != 0)
        return -1;
    patternlen = STRLEN(pattern);
    stringlen = STRLEN(string);
    if (patternlen > stringlen)
        return -1;
    for (i = stringlen - patternlen; i >= 0; --i) {
        if (STRNCMP(string + i, pattern, patternlen) == 0)
            return i;
    }
    return -1;
}

/*
 * Returns a pointer to a dynamically allocated character buffer containing a substring from the given string, 
 * starting with index (start) and ending with index (end - 1).
 */
STRUTIL_CHARTYPE *substring(size_t start, size_t end, const STRUTIL_CHARTYPE *string)
{
    size_t maxindex, i, j;
    STRUTIL_CHARTYPE *substr;

    if (string == NULL)
        return NULL;
    if (equals(string, (STRUTIL_CHARTYPE *)"")) {
        if (start == 0 && end == 0)
            return (STRUTIL_CHARTYPE *)calloc(1, sizeof(STRUTIL_CHARTYPE));
        else
            return NULL;
    }
    maxindex = STRLEN(string) - 1;
    if (start > maxindex || end > maxindex || start > end)
        return NULL;
    substr = (STRUTIL_CHARTYPE *)calloc(nullterm(end - start + 1), sizeof(STRUTIL_CHARTYPE));
    if (substr == NULL)
        return NULL;
    for (i = start, j = 0; i < end; ++i, ++j) {
        substr[j] = string[i];
    }
    return substr;
}
