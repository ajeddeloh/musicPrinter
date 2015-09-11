#ifndef SUBST_H
#define SUBST_H

#include "file.h"

typedef struct subst {
    char *string;
    struct subst *next;
} subst_t;

extern subst_t *subs[N_METADATA_TYPES];

void register_subst(const metadata_t type, const char *sub);

char *get_sub(const metadata_t type, const file_t *f);
#endif
