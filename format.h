#ifndef FORMAT_H
#define FORMAT_H

#include <stdbool.h>

bool validate_format(const char *format);

char *get_needed_metadata(const char *format);

#endif
