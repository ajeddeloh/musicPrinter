#include <stdlib.h>
#include <stdio.h>

#include "file.h"

char *get_attr(const File *f, char attr) {
    switch (attr) {
        case TITLE:
            return f->title;
        case TRACK_NO:
            return f->track_no;
        case DISK_NO:
            return f->disk_no;
        case ALBUM:
            return f->album;
        case ARTIST:
            return f->artist;
        case ALBUM_ARTIST:
            return f->album_artist;
        default:
            fprintf(stderr, "Unsupported character in format string %c", attr);
            exit(EXIT_FAILURE);
    }
}

void free_file(File *f) {
    free(f->title);
    free(f->disk_no);
    free(f->track_no);
    free(f->album);
    free(f->album_artist);
    free(f->artist);
    free(f);
}
