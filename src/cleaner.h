#ifndef CLEANER_H
#define CLEANER_H

#include <stdbool.h>
/*
 * Works like strcpy but for 
 */

void clean_string(const char *src, char *dest, const char* charset, char (*replace)(char c));

#endif
