#include <stdlib.h>
#include <stdio.h>

#include "file.h"

//make sure these stay in sync with the enum defined in file.h
const char metadata_type_char_map[] = "tTdbAa";
const char *metadata_type_string_map[] = {
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

void file_free(file_t *f) 
{
    for (size_t i = 0; i < f->n_entries; i++) {
        metadata_entry_free(&(f->entries[i]));
    }
    free(f->entries);
    free(f);
}

void metadata_entry_free(metadata_entry_t *m) 
{
    free(m->value);
    free(m->value_clean);
    free(m);
}
