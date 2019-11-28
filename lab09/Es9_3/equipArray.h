//
// Created by lorenzodentis on 12/12/2018.
//

#ifndef ES9_3_EQUIPARRAY_H
#define ES9_3_EQUIPARRAY_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "item.h"

int itemSearchEquip(char *itemName, item **itemVector,
                    int itemNr); //restituisce l'indice di itemName nel vettore itemVector
void itemFree(item **itemVector, int nItem);

#endif //ES9_3_EQUIPARRAY_H
