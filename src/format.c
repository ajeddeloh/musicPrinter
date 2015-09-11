#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "file.h"
#include "format.h"

typedef enum {
    STATE_TEXT, //doubles as start state. change this?
    STATE_PERCENT,
    STATE_MODIFIER,
    STATE_TYPE
} state_t;

const char valid_modifiers[] = "c"; //for now
const char *valid_types = metadata_type_char_map;

//modifier is actaully a true pointer to single char
static void print_type(const file_t *f, const char type, char *modifier)
{
    metadata_t tmp = char_to_metadata_t(type);
    if (f->entries[tmp] != NULL) {
        fputs(f->entries[tmp], stdout);
        *modifier = '\0';
    } else {
        fprintf(stderr, "Fatal error: file had no element %s\n", metadata_type_string_map[tmp]);
        exit(EXIT_FAILURE);
    }
}

/*
 * validates the string using a state machine for the regex:
 * (t*%(T+mT))* where t is text, % is itself, m is modifier
 * and T is a metadata type.
 */
int get_needed_metadata(const char *format, char *metadata) 
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
                    return INVALID_FORMAT;
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
                    return INVALID_FORMAT;
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
        return VALID_FORMAT;
    } else {
        return INVALID_FORMAT;
    }
}    

//assumes string has already been checked for validity
void print_string(const char *format, const file_t *f) {
    state_t state = STATE_TEXT;
    char active_modifier = '\0';
    while (*format != '\0') {
        char current = *format;
        switch (state) {
            case STATE_TEXT:
                if (current == '%') {
                    state = STATE_PERCENT;
                } else {
                    putchar(current);
                }
                break;
            case STATE_PERCENT:
                if (strchr(valid_modifiers, current) != NULL) {
                    active_modifier = current;
                    state = STATE_MODIFIER;
                } else { //is type
                    print_type(f, current, &active_modifier);
                    state = STATE_TYPE;
                }
                break;
            case STATE_MODIFIER:
                print_type(f, current, &active_modifier);
                state = STATE_TYPE;
                break;
            case STATE_TYPE:
                if (current == '%') {
                    state = STATE_PERCENT;
                } else {
                    putchar(current);
                    state = STATE_TEXT;
                }
                break;
        }
        format++;
    }
}
