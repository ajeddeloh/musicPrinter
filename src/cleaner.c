#include <string.h>

#include "cleaner.h"

void clean_string(const char *src, char *dest, const char *charset, char (*replace)(char c))
{
    do {
        if (strchr(charset, *src) == NULL) {
            *dest++ = *src;
        } else if((*replace)(*src) != '\0') {
            *dest++ = (*replace)(*src);
        }
    } while (*src++ != '\0');
}
