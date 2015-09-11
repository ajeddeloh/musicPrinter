#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "file.h"
#include "extract.h"
#include "format.h"

int main(int argc, char *argv[]) 
{
    if (argc < 3) { //TODO: handle options
        printf("Usage: muprint FORMAT_STRING path/to/file\n");
        exit(EXIT_FAILURE);
    }
    const char *format_string = argv[1];
    const char *filename = argv[2];
    puts(filename);
    file_t f;
    //printf("Loaded format string: %s\n", format_string);
    char needed_metadata[N_METADATA_TYPES] = {0};
    int err = get_needed_metadata(format_string, needed_metadata);
    if (err != VALID_FORMAT) {
        fprintf(stderr, "Invalid format string\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    if (load_file(&f, filename) != 0) {
        fprintf(stderr, "Error loading file %s\n", filename);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    //file_print(&f);
    
    /*if (valid) {
        printf("Metadata: %s\n", needed_metadata);
        printf("valid string\n");
    } else {
        printf("invalid string\n");
    }*/
    print_string(format_string, &f);
    putchar('\n');
    file_free(&f);
    return EXIT_SUCCESS;
}
