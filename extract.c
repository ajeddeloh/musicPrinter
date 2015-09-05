#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <libavformat/avformat.h>
#include <libavutil/dict.h>

#include "extract.h"

int load_file(file_t *f, const char *fname)
{
    av_register_all();
    AVFormatContext *handle = NULL;
    
    if (avformat_open_input(&handle, fname, NULL, NULL) != 0) {
        fprintf(stderr, "Error opening file: %s\n", fname);
        return -1;
    }

    AVDictionary *metadata = handle->metadata;
    if (metadata == NULL) {
        return -1;
    }
    AVDictionaryEntry *entry = NULL;
    for (size_t i = 0; i < f->n_entries; i ++) {
        const char *key = metadata_type_string_map[f->entries[i].type];
        entry = av_dict_get(metadata, key, NULL, 0);
        if (entry != NULL) {
            f->entries[i].value = strdup(entry->value);
        }
    }
    return 0; //success
}
