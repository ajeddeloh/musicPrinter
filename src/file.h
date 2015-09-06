#ifndef FILE_H
#define FILE_H

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

typedef struct metadata_entry {
    metadata_t type;
    char *value;
    char *value_clean;
} metadata_entry_t;

typedef struct file {
    metadata_entry_t *entries;
    size_t n_entries;
} file_t;

void init_map();

const char *metadata_get_name(metadata_t type);

char *get_attr(const file_t *f, const metadata_t attr);

void file_free(file_t *f);

void metadata_entry_free(metadata_entry_t *m);

void file_init(file_t *t, const char *needed_metadata);

void file_print(const file_t *f);
#endif
