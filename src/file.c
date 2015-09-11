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

char *metadata_type_subst_map[] = 
{
    "Unknown Title",
    "0",
    "0",
    "Unknown Album",
    "Unknown Artist",
    "Unknown Artist",
};

metadata_t char_to_metadata_t(char in)
{
    return strchr(metadata_type_char_map, in) - metadata_type_char_map;
}

void file_print(const file_t *f) {
    for(size_t i = 0; i < N_METADATA_TYPES; i++) {
        if (f->entries[i] == NULL) continue;

        const char *key = metadata_type_string_map[i];
        printf("%s : %s\n", key, f->entries[i]);
    }
}

void file_free(file_t *f) 
{
    for (int i = 0; i < N_METADATA_TYPES; i++) {
        free(f->entries[i]);
    }
}

bool has_needed_metadata(const file_t *f, const char *needed_metadata)
{
    while (*needed_metadata != '\0') {
        metadata_t needed = char_to_metadata_t(*needed_metadata);
        if (f->entries[needed] == NULL) {
            return false;
        }
    }
    return true;
}
