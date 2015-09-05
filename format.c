#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include <stdbool.h>

typedef enum {
    STATE_TEXT,
    STATE_MODIFIER,
    STATE_TYPE,
    STATE_ILLEGAL
} state_t;

bool validate_format(const char *format) 
{
    state_t state = STATE_TEXT;
    (void) state;
    while (*format != '\0') {
    }
    return true;
}    

char *get_needed_metadata(const char *format)
{
    (void) format;
    return NULL;
}

