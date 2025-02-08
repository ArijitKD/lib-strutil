#include <stdlib.h>
#include "strutil.h"

// Perfected
unsigned int equals (const char* string1, const char* string2)
{
    return (strcmp(string1, string2) == 0);
}

// Perfected
char* copy (const char* string)
{
    char* strcopy = (char*)malloc((strlen(string)+1)*sizeof(char));
    if (strcopy == NULL)
        return NULL;
    strcpy(strcopy, string);
    return strcopy;
}

// Perfected
void reverse (char* string)
{
    unsigned int len = strlen(string);
    for (unsigned int i=0; i<len/2; ++i)
    {
        string[i] = string[i] + string[len-(i+1)];
        string[len-(i+1)] = string[i] - string[len-(i+1)];
        string[i] = string[i] - string[len-(i+1)];
    }
}

// Perfected
char* reversecopy (const char* string)
{
    char* newstring = copy(string);
    reverse(newstring);
    return newstring;
}

// Perfected
unsigned int startswith (const char* pattern, const char* string)
{
    if (*pattern == 0)
        return 1;
    size_t patternlen = strlen(pattern), i = 0;
    while (i < patternlen && pattern[i] == string[i])
        i++;
    return (i == patternlen);
}

// Perfected
unsigned int endswith (const char* pattern, const char* string)
{
    if (*pattern == 0)
        return 1;
    ssize_t j = strlen(pattern), i = strlen(string);
    while (j >= 0 && pattern[--j] == string[--i]);
    return (j == -1);
}

// TODO: Use Boyer-Moore algorithm with the current brute-force one and
// implement a hybrid search algorithm
ssize_t find (const char* pattern, const char* string)
{
    if (*pattern==0)
        return 0;
    if (*string==0 && *pattern!=0)
        return -1;
    ssize_t patternlen = strlen(pattern);
    ssize_t stringlen = strlen(string);
    if (patternlen > stringlen)
        return -1;
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
}

// Perfected
ssize_t indexof (const char* pattern, const char* string)
{
    return find(pattern, string);
}

// Perfected
ssize_t rindexof (const char* pattern, const char* string)
{
    char* revpattern = reversecopy(pattern);
    char* revstring = reversecopy(string);
    ssize_t found_index = indexof(revpattern, revstring);
    if (found_index != -1)
        found_index = (strlen(revstring)-found_index)-strlen(revpattern);
    free(revpattern);
    free(revstring);
    return found_index;
}

// Perfected
char* substring (size_t start, size_t end, const char* string)
{
    if (equals(string, ""))
    {
        if (start == 0 && end == 0)
            return (char*)calloc(1, sizeof(char));
        else
            return NULL;
    }
    size_t maxindex = strlen(string)-1;
    if (start > maxindex || end > maxindex || start > end)
        return NULL;
    char* substr = (char*)malloc((end-start+1)*sizeof(char));
    if (substr == NULL)
        return NULL;
    for (size_t i=start, j=0; i<end; ++i, ++j)
    {
        substr[j] = string[i];
    }
    substr[end-start] = 0;
    return substr;
}
