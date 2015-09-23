#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdbool.h>
#include <libgen.h>
#include <stdio.h>

#include <libavformat/avformat.h>
#include <libavutil/dict.h>

#include "extract.h"

//Wrapper that handles any conversion that needs to be done (e.g. converting
//a track like "03/14" to "03" as well as null dict entries
static void add_entry(file_t *f, metadata_t type, const AVDictionaryEntry *entry)
{
    if (entry == NULL) {
        f->entries[type] = NULL;
        return;
    }
    const char *toadd = entry->value;
    size_t len = 0;

    switch (type) {
        case TRACK_NO: //handle cases of '04/12' and convert to '04'
        case DISC_NO:
            len = strspn(toadd, "0123456789");
            f->entries[type] = malloc(strlen(toadd)+1); //wont be any bigger
            strncpy(f->entries[type], toadd, len);
            f->entries[type][len] = '\0'; //because linux doesnt have strlcpy
            break;
        default:
            f->entries[type] = strdup(toadd);
            break;
    }
}

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
        add_entry(f, i, entry);
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
