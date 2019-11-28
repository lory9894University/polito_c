//
// Created by lorenzodentis on 14/01/2019.
//

#ifndef E01_ST_H
#define E01_ST_H

typedef struct symbtab *ST;

ST STinit(int maxN);

void STfree(ST st);

void STinsert(ST st, char *val);

int STsearch(ST st, char *k);

char *STselect(ST st, int r);

int STdim(ST st);

#endif //E01_ST_H
