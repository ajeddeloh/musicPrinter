#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "file.h"

//make sure these stay in sync with the enum defined in file.h
const char metadata_type_char_map[] = "tTdbAa";
const char *metadata_type_string_map[] = 
{
    "title",
    "track",
    "disc",
    "album",
    "album_artist",
    "artist"
};

//public funcs
char *file_get_attr(const file_t *f, const metadata_t attr) 
{
    for (size_t i = 0; i < f->n_entries; i++) {
        if (f->entries[i].type == attr) {
            return f->entries[i].value;
        }
    }
    return NULL;
}

void file_init(file_t *f, const char *needed_metadata) 
{
    f->n_entries = strlen(needed_metadata);
    f->entries = calloc(sizeof(metadata_entry_t), f->n_entries);
    assert(f->entries != NULL);
    for (size_t i = 0; i < f->n_entries; i++) {
        metadata_t type = strchr(metadata_type_char_map, needed_metadata[i]) - metadata_type_char_map;
        f->entries[i] = (metadata_entry_t) {.type = type, .value = NULL, .value_clean=NULL};
    }
}

void file_print(const file_t *f) {
    for(size_t i = 0; i < f->n_entries; i++) {
        if (f->entries[i].value == NULL) continue;
        const char *key = metadata_type_string_map[f->entries[i].type];
        printf("%s : %s\n", key, f->entries[i].value);
    }
}

void file_free(file_t *f) 
{
    for (size_t i = 0; i < f->n_entries; i++) {
        metadata_entry_free(&(f->entries[i]));
    }
    free(f->entries);
}

void metadata_entry_free(metadata_entry_t *m) 
{
    free(m->value);
    free(m->value_clean);
}
