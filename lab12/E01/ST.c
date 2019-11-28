//
// Created by lorenzodentis on 14/01/2019.
//

#include "ST.h"
#include <stdlib.h>
#include <string.h>

struct symbtab {
    char **name;
    int size;
    int used;
};

int STdim(ST st) {
    return st->used;
}

void STinsert(ST st, char *val) {
    strcpy(st->name[st->used], val);
    st->used++;
}

int STsearch(ST st, char *k) {
    int i;
    for (i = 0; i < st->used && strcmp(st->name[i], k); i++);
    if (i == st->used && strcmp(st->name[i], k))
        i = -1;

    return i;
}

ST STinit(int maxN) {
    ST st;
    int i;

    st = malloc(sizeof(*st));
    st->name = malloc(maxN * sizeof(char *));
    for (i = 0; i < maxN; i++) {
        st->name[i] = malloc(30 * sizeof(char));
    }
    st->size = maxN;
    st->used = 0;
    return st;
}

char *STselect(ST st, int r) {
    if (r > st->used)
        return NULL;
    return st->name[r];
}
