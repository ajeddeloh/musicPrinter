#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "file.h"
#include "extract.h"
#include "format.h"
#include "subst.h"

int main(int argc, char *argv[]) 
{
    if (argc < 3) { //TODO: handle options
        printf("Usage: muprint FORMAT_STRING path/to/file\n");
        exit(EXIT_FAILURE);
    }
    const char *format_string = argv[1];
    const char *filename = argv[2];
    
    file_t f;
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

    register_subst(TITLE, "Unknown Title");
    register_subst(TRACK_NO, "00");
    register_subst(DISC_NO, "00");
    register_subst(ALBUM, "Unknown Album");
    register_subst(ALBUM_ARTIST, "Unknown Artist");
    register_subst(ARTIST, "Unknown Artist");
    
    print_string(format_string, &f);
    putchar('\n');
    file_free(&f);
    return EXIT_SUCCESS;
}
