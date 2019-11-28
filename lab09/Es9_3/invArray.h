//
// Created by lorenzodentis on 12/12/2018.
//
#ifndef ES9_3_INVARRAY_T_H
#define ES9_3_INVARRAY_T_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

typedef struct singleEquipableItem *equipableItem;

void itemWrapperFree(equipableItem itemWrapper);

equipableItem itemInit();

void newItemVector(equipableItem *itemWrapper, char *inputFile);

int itemSearchInventary(char *itemName,
                        equipableItem itemWrapper);  //restituisce l'indice di itemName nel vettore itemVector
item *indexToPointer(equipableItem itemWrapper,
                     int index); //restituisce il puntatore all'item, così che PG possa equipaggiarlo
int emptyItem(equipableItem itemWrapper);

#endif //ES9_3_INVARRAY_T_H
