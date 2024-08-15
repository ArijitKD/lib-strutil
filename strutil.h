#ifndef LIBC_STRUTIL_H
#define LIBC_STRUTIL_H

#include <string.h>

unsigned int endswith (const char* endstr, const char* str);
unsigned int startswith (const char* startstr, const char* str);
unsigned int equals (const char* str1, const char* str2);
void reverse (char* str);
char* reversecopy (const char* str);
int find (const char* findstr, const char* str);
int indexof (const char* substr, const char* str);
int rindexof (const char* substr, const char* str);
char* substring (int start, int end, const char* str);

#endif
