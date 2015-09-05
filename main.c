#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "extract.h"
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
    char *format_string = argv[1];
    char *filename = argv[2];
    file_t f;
    load_file(&f, filename);
    printf("Loaded format string: %s\n", format_string);
    return EXIT_SUCCESS;
}
