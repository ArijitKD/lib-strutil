#include <stdlib.h>
#include "strutil.h"

// Perfected
unsigned int equals (const char* str1, const char* str2)
{
    return (strcmp(str1, str2) == 0);
}

// Perfected
char* copy (const char* str)
{
    char* strcopy = (char*)malloc((strlen(str)+1)*sizeof(char));
    if (strcopy == NULL)
        return NULL;
    strcpy(strcopy, str);
    return strcopy;
}

// Perfected
void reverse (char* str)
{
    unsigned int len = strlen(str);
    for (unsigned int i=0; i<len/2; ++i)
    {
        str[i] = str[i] + str[len-(i+1)];
        str[len-(i+1)] = str[i] - str[len-(i+1)];
        str[i] = str[i] - str[len-(i+1)];
    }
}

// Perfected
char* reversecopy (const char* str)
{
    char* newstr = copy(str);
    reverse(newstr);
    return newstr;
}

unsigned int startswith (const char* startstr, const char* str)
{
    size_t len_startstr = strlen(startstr), i = 0;
    while (i < len_startstr && startstr[i] == str[i])
        i++;
    return (i == len_startstr);
}

unsigned int endswith (const char* endstr, const char* str)
{
    ssize_t j = strlen(endstr), i = strlen(str);
    while (j >= 0 && endstr[--j] == str[--i]);
    return (j == -1);
}

ssize_t find (const char* findstr, const char* str)
{
    if (equals(str, ""))
    {
        if (equals(findstr, ""))
            return 0;
        else
            return -1;
    }
    
    ssize_t findstrlen = strlen(findstr), found_index = -1;
    ssize_t strstrlen = strlen(str);
    
    if (findstrlen > strstrlen)
    {
        return -1;
    }
    if (findstrlen == 0)
    {
        found_index = 0;
    }
    else
    {
        ssize_t i, j, k, count = 0;
        for (i=0; i<strstrlen; ++i)
        {
            if (str[i] == findstr[0])
            {
                count = 0;
                k = i;
                for (j=1; j<findstrlen; ++j)
                {
                    if (findstr[j] != str[++k])
                        break;
                    else
                        count++;
                }
                if (count == findstrlen-1)
                {
                    found_index = i;
                    break;
                }
            }
        }
    }
    return found_index;
}

ssize_t indexof (const char* substr, const char* str)
{
    return find(substr, str);
}

ssize_t rindexof (const char* substr, const char* str)
{
    char* revsubstr = reversecopy(substr);
    char* revstr = reversecopy(str);
    printf ("len(revsubstr): %d\n", strlen(revsubstr));
    printf ("%s %s\n", revsubstr, revstr);
    ssize_t found_index = indexof(revsubstr, revstr);
    if (found_index != -1)
        found_index = (strlen(revstr)-found_index)-strlen(revsubstr);
    free(revsubstr);
    free(revstr);
    return found_index;
}

// Perfected
char* substring (size_t start, size_t end, const char* str)
{
    if (equals(str, ""))
    {
        if (start == 0 && end == 0)
            return (char*)calloc(1, sizeof(char));
        else
            return NULL;
    }
    size_t maxindex = strlen(str)-1;
    if (start > maxindex || end > maxindex || start > end)
        return NULL;
    char* substr = (char*)malloc((end-start+1)*sizeof(char));
    if (substr == NULL)
        return NULL;
    for (size_t i=start, j=0; i<end; ++i, ++j)
    {
        substr[j] = str[i];
    }
    substr[end-start] = 0;
    return substr;
}
