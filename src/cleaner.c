#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "cleaner.h"

int replace_char = '\0';
char allowed_chars[256] = "";

static int validate_posix(int c) 
{
    return isalnum(c) || c == '.' || c == '_' || c =='-';
}

static int validate_unix_fs(int c) 
{
    return c != '/' && c != '\0';
}

static int validate_custom(int c) 
{
    (void) c; //TODO write this
    return 1;
}

static int no_validation(int c)
{
    (void) c; //silence compiler warnings
    return 1;
}

void set_replace_char(const char c)
{
    replace_char = c;
}

void set_allowed_chars(const char *chars)
{
    strncpy(allowed_chars, chars, 256);
}

int (*get_validation_func(char c)) (int) 
{
    switch (c) {
        case '\0': //no modifier
            return no_validation;
        case 'p':
            return validate_posix;
        case 'u':
            return validate_unix_fs;
        case 'v':
            return isprint;
        case 'c':
            return validate_custom;
    }
    return NULL;
}

void puts_with_validation(const char *src, int (*validate)(int c)) 
{
    while (*src != '\0') {
        if ( (*validate)(*src) ) {
            putchar(*src);
        } else {
            if (replace_char != '\0') {
                putchar(replace_char);
            }
        }
        src++;
    }
}
/*
void clean_string(const char *src, char *dest, int (*validate)(char c))
{
    do {
        if (strchr(charset, *src) == NULL) {
            *dest++ = *src;
        } else if((*replace)(*src) != '\0') {
            *dest++ = (*replace)(*src);
        }
    } while (*src++ != '\0');
}*/
