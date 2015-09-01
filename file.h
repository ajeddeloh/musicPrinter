#ifndef FILE_H
#define FILE_H

#define TITLE 't'
#define TRACK_NO 'n'
#define DISK_NO 'd'
#define ALBUM 'b'
#define ARTIST 'a'
#define ALBUM_ARTIST 'A'

typedef struct File {
    char *title;
    char *track_no;
    char *disk_no;
    char *album;
    char *artist;
    char *album_artist;
} File;

char *get_attr(const File *f, char attr);

void free_file(File *f);

#endif
