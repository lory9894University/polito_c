//
// Created by lorenzodentis on 05/12/2018.
//

#ifndef ES_8_3_PG_H
#define ES_8_3_PG_H

#include "invArray.h"

typedef struct singleCharacter *link;
struct singleCharacter {
    char *name, *class, *id;
    int hp, mp, atk, def, mag, spr;
    item **gearEquipped; //vettore di puntatori a tipo item
    int gearInUse; //niente altro che la lunghezza di gear equipped
    link next;
};


#endif

