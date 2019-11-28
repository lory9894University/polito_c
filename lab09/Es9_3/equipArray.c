//
// Created by lorenzodentis on 12/12/2018.
//

#include "equipArray.h"

int itemSearchEquip(char *itemName, item **itemVector, int itemNr) {
    int i = 0;
    int flag = 0;

    for (i = 0; i < itemNr; i++) {
        if (strcmp(itemVector[i]->name, itemName) == 0) {
            flag = 1;
            break;
        }
    }
    if (!flag)
        return -1;
    return i;

}

void itemFree(item **itemVector, int nItem) {
    int i;

    if (itemVector != NULL) { //se il vettore è vuoto non bisogna deallocarlo
        for (i = 0; i < nItem; i++) {
            free(itemVector[i]);
        }
    }
}