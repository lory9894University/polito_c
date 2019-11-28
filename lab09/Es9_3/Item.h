//
// Created by lorenzodentis on 05/12/2018.
//

#ifndef ES_8_3_ITEM_H
#define ES_8_3_ITEM_H
#define SMALLCHAR 51

#include "Item.h"

typedef struct singleItem {
    char name[SMALLCHAR], type[SMALLCHAR];
    int hp, mp, atk, def, mag, spr;
} item;

void itemPrint(item itemToPrint);

#endif //ES_8_3_ITEM_H
