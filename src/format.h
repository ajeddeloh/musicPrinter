#ifndef FORMAT_H
#define FORMAT_H

#define VALID_FORMAT 0
#define INVALID_FORMAT -1

/*
 * lex's a format string and determines what metadata elements it needs, filling
 * out buffer as it goes. Buffer should be large enough to hold a string of all
 * metadata types plus room for a null terminator (i.e. should be at least
 * N_METADATA_TYPES + 1 bytes)
 * returns if the format string was valid
 */
int get_needed_metadata(const char *format, char *buffer);

void print_string(const char *format, const file_t *f);
#endif
