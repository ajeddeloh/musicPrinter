#ifndef FORMAT_H
#define FORMAT_H

#include <stdbool.h>

/*
 * lex's a format string and determines what metadata elements it needs, filling
 * out buffer as it goes. Buffer should be large enough to hold a string of all
 * metadata types plus room for a null terminator (i.e. should be at least
 * N_METADATA_TYPES + 1 bytes)
 * returns if the format string was valid
 */
bool get_needed_metadata(const char *format, char *buffer);

#endif
