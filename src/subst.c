#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "subst.h"
#include "file.h"
#include "format.h"

subst_t *subs[N_METADATA_TYPES] = {0};

static void free_chain(subst_t *sub)
{
    if (sub == NULL) return;
    free_chain(sub->next);
    free(sub->string);
    free(sub);
}

//for debug
void print_all_subs(const metadata_t type)
{
    subst_t *current = subs[type];
    while (current != NULL) {
        puts(current->string);
        current = current->next;
    }
}

void register_subst(const metadata_t type, const char *sub) 
{
    subst_t *new_subst = malloc(sizeof(subst_t));
    new_subst->string = strdup(sub);
    new_subst->next = subs[type];
    subs[type] = new_subst;
}

char *get_sub(const metadata_t type, const file_t *f)
{
    subst_t *current = subs[type];
    char metadata[N_METADATA_TYPES] = {0};
    while (current != NULL) {
        int err = get_needed_metadata(current->string, metadata);
        if (err == INVALID_FORMAT) {
            return NULL;
        }
        if (has_all_metadata(f, metadata)) {
            return current->string;
        }
        current = current -> next;
    }
    return NULL;
}

void subst_free()
{
    for (int i = 0; i < N_METADATA_TYPES; i++) {
        free_chain(subs[i]);
    }
}
