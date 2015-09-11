#ifndef FILE_H
#define FILE_H

#include <stdbool.h>

#define TITLE_CHAR 't'
#define TRACK_NO_CHAR 'n'
#define DISK_NO_CHAR 'd'
#define ALBUM_CHAR 'b'
#define ARTIST_CHAR 'a'
#define ALBUM_ARTIST_CHAR 'A'

typedef enum {
    TITLE,
    TRACK_NO,
    DISC_NO,
    ALBUM,
    ALBUM_ARTIST,
    ARTIST,
    N_METADATA_TYPES
} metadata_t;

//parallel arrays, indices match up with the metadata_t enum
extern const char metadata_type_char_map[];
extern const char *metadata_type_string_map[];
extern char* metadata_type_subst_map[];

typedef struct {
    char *entries[N_METADATA_TYPES];
} file_t;

metadata_t char_to_metadata_t(char in);

char *get_attr(const file_t *f, const metadata_t attr);

void file_free(file_t *f);

void file_print(const file_t *f);

bool has_all_metadata(const file_t *f, const char *needed_metadata);
#endif
