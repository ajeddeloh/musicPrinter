#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "file.h"
#include "extract.h"
#include "format.h"
#include "subst.h"
#include "cleaner.h"
#include "help.h"

int main(int argc, char *argv[]) 
{
    register_subst(TITLE, "Unknown Title");
    register_subst(TRACK_NO, "00");
    register_subst(DISC_NO, "00");
    register_subst(ALBUM, "Unknown Album");
    register_subst(ALBUM_ARTIST, "Unknown Artist");
    register_subst(ARTIST, "Unknown Artist");
    register_subst(FILENAME, "");
    register_subst(EXT, "");
    
    int opt;
    while ((opt = getopt(argc, argv, "s:c:r:h")) != -1) {
        switch(opt) {
            case 's':
                if( strchr(metadata_type_char_map, optarg[0]) == NULL) {
                    fprintf(stderr, "invalid substitution key %c\n", optarg[0]);
                    exit(EXIT_FAILURE);
                }
                register_subst(char_to_metadata_t(optarg[0]), optarg+1);
                break;
            case 'r':
                set_replace_char(optarg[0]);
                break;
            case 'c':
                set_allowed_chars(optarg);
                break;
            case 'h':
                print_help();
                break;

        }
    }
    if (argc < 3) { //TODO: handle options
        printf("Usage: muprint FORMAT_STRING path/to/file\n");
        exit(EXIT_FAILURE);
    }

    const char *format_string = argv[optind];
    const char *filename = argv[optind+1];

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

    print_string(format_string, &f);
    subst_free();
    file_free(&f);
    return EXIT_SUCCESS;
}
