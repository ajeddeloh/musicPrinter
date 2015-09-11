#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "subst.h"

subst_t *subs[N_METADATA_TYPES] = {0};

static void print_all_subs(const metadata_t type)
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
    print_all_subs(type);
}

