#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdbool.h>
#include <libgen.h>

#include <libavformat/avformat.h>
#include <libavutil/dict.h>

#include "extract.h"

int load_file(file_t *f, const char *fname)
{
    av_register_all();
    AVFormatContext *handle = NULL;
    
    if (avformat_open_input(&handle, fname, NULL, NULL) != 0) {
        avformat_close_input(&handle);
        return -1;
    }

    AVDictionary *metadata = handle->metadata;
    if(metadata == NULL) {
        for (unsigned int i = 0; i < handle->nb_streams; i++) {
            if(handle->streams[i]->metadata != NULL) {
                av_dict_copy(&metadata, handle->streams[i]->metadata, 0);
            }
        }
    }


    if (metadata == NULL) {
        avformat_close_input(&handle);
        return -1;
    }

    AVDictionaryEntry *entry = NULL;
    for (size_t i = 0; i < N_METADATA_TYPES; i ++) {
        const char *key = metadata_type_string_map[i];
        entry = av_dict_get(metadata, key, NULL, 0);
        if (entry != NULL) {
            f->entries[i] = strdup(entry->value);
        } else {
            f->entries[i] = NULL;
        }
    }
    char *path = strdup(fname); //since basename can modify it
    char *bname = strdup(basename(path));
    free(path);//bname might have changed it, no longer a source of truth

    char *period = strrchr(bname, '.');
    if (period != NULL) {
        f->entries[EXT] = strdup(period+1);
        *period = '\0';
    }
    f->entries[FILENAME] = bname;

    avformat_close_input(&handle);
    return 0; //success
}
