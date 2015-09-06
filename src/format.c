#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "file.h"

typedef enum {
    STATE_TEXT, //doubles as start state. change this?
    STATE_PERCENT,
    STATE_MODIFIER,
    STATE_TYPE
} state_t;

const char valid_modifiers[] = "c"; //for now
const char *valid_types = metadata_type_char_map;

/*
 * validates the string using a state machine for the regex:
 * (t*%(T+mT))* where t is text, % is itself, m is modifier
 * and T is a metadata type.
 */
bool get_needed_metadata(const char *format, char *metadata) 
{
    state_t state = STATE_TEXT;
    char *metadata_cursor = metadata;
    while (*format != '\0') {
        char current = *format;
        switch (state) {
            case STATE_TEXT:
                if (current == '%') {
                    state = STATE_PERCENT;
                }
                break;
            case STATE_PERCENT:
                if (strchr(valid_modifiers, current) != NULL) {
                    state = STATE_MODIFIER;
                } else if (strchr(valid_types, current) != NULL) {
                    if (strchr(metadata, current) == NULL) { //if metadata doesnt have it
                        *metadata_cursor = current;
                        metadata_cursor++;
                    }
                    state = STATE_TYPE;
                } else {
                    return false;
                }
                break;
            case STATE_MODIFIER:
                if (strchr(valid_types, current) != NULL) {
                    if (strchr(metadata, current) == NULL) { //if metadata doesnt have it
                        *metadata_cursor = current;
                        metadata_cursor++;
                    }
                    state = STATE_TYPE;
                } else {
                    return false;
                }
                break;
            case STATE_TYPE:
                if (current == '%') {
                    state = STATE_PERCENT;
                } else {
                    state = STATE_TEXT;
                }
                break;
        }
        format++;
    }
    if (state == STATE_TYPE || state == STATE_TEXT) {
        *metadata_cursor = '\0';
        return true;
    } else {
        return false;
    }
}    


