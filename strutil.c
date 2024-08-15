#include <stdlib.h>
#include "strutil.h"

unsigned int endswith (const char* endstr, const char* str)
{
    int j = strlen(endstr), i = strlen(str);
    while (j >= 0 && endstr[--j] == str[--i]);
    return (j == -1);
}

unsigned int startswith (const char* startstr, const char* str)
{
    int len_startstr = strlen(startstr), i = -1;
    while (i < len_startstr && startstr[++i] == str[i]);
    return (i == len_startstr);
}

unsigned int equals (const char* str1, const char* str2)
{
    return (strcmp(str1, str2) == 0);
}

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

char* reversecopy (const char* str)
{
    char* revstr = (char*)malloc(sizeof(str));
    strcpy(revstr, str);
    reverse(revstr);
    return revstr;
}

int find (const char* findstr, const char* str)
{
    unsigned int findstrlen = strlen(findstr), found_index = -1;
    if (findstrlen == 0)
    {
        found_index = 0;
    }
    else
    {
        int i, j;
        unsigned int strstrlen = strlen(str);
        for (i=0; i<strstrlen; ++i)
        {
            if (str[i] == findstr[0])
            {
                found_index = i;
                for (j=1; j<findstrlen; ++j)
                {
                    if (findstr[j] != str[++i])
                    {
                        found_index = -1;
                        break;
                    }
                }
                break;
            }
        }
    }
    return found_index;
}

int indexof (const char* substr, const char* str)
{
    return find(substr, str);
}

int rindexof (const char* substr, const char* str)
{
    unsigned int substrlen = strlen(substr), found_index = -1;
    if (substrlen == 0)
    {
        found_index = 0;
    }
    else
    {
        int i, j, k;
        unsigned int strstrlen = strlen(str);
        for (i=strstrlen-1; i>=0; --i)
        {
            if (str[i] == substr[0])
            {
                found_index = k = i;
                for (j=1; j<substrlen; ++j)
                {
                    if (substr[j] != str[++k])
                    {
                        found_index = -1;
                        break;
                    }
                }
                if (j==substrlen)
                {
                    break;
                }
            }
        }
    }
    return found_index;
}

char* substring (int start, int end, const char* str)
{
    char* substr = (char*)malloc((end-start+1)*sizeof(char));
    for (int i=start, j=0; i<end; ++i, ++j)
    {
        substr[j] = str[i];
    }
    substr[end-start] = 0;
    return substr;
}
