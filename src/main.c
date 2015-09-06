#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "file.h"
#include "extract.h"
#include "format.h"
/*
 * Format spec: 
 * TODO: write this
 */


int main(int argc, char *argv[]) 
{
    if (argc < 3) { //TODO: handle options
        printf("Usage: muprint FORMAT_STRING path/to/file\n");
        exit(EXIT_FAILURE);
    }
    const char *format_string = argv[1];
    const char *filename = argv[2];
    file_t f;
    printf("Loaded format string: %s\n", format_string);
    char needed_metadata[N_METADATA_TYPES] = {0};
    bool valid = get_needed_metadata(format_string, needed_metadata);
    file_init(&f, needed_metadata);
    load_file(&f, filename);
    file_print(&f);
    if (valid) {
        printf("Metadata: %s\n", needed_metadata);
        printf("valid string\n");
    } else {
        printf("invalid string\n");
    }
    file_free(&f);
    return EXIT_SUCCESS;
}
