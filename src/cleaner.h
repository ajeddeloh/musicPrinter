#ifndef CLEANER_H
#define CLEANER_H

#include <stdbool.h>
/*
 * Works like strcpy but for 
 */

//void clean_string(const char *src, char *dest, const char* charset, char (*replace)(char c));

void puts_with_validation(const char *src, int (*validate)(int));

void set_allowed_chars(const char *chars);

void set_replace_char(const char c);

int (*get_validation_func(char c))(int);
#endif
