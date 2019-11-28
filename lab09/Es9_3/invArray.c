//
// Created by lorenzodentis on 12/12/2018.
//

#include "invArray.h"
#include "equipArray.h"

struct singleEquipableItem {
    item **itemList;
    int numberOfItem;
    int maxNumberOfItem;
};

void itemWrapperFree(equipableItem itemWrapper) {
    itemFree(itemWrapper->itemList, itemWrapper->numberOfItem);
    free(itemWrapper->itemList);
}

equipableItem itemInit() {
    equipableItem itemWrapper = malloc(sizeof(*itemWrapper));

    itemWrapper->itemList = NULL;
    return itemWrapper;
}

void newItemVector(equipableItem *itemWrapper, char *inputFile) {
    FILE *fPtr;

    if ((*itemWrapper)->itemList != NULL) {
        itemWrapperFree(*itemWrapper);
    }
    if ((fPtr = fopen(inputFile, "r")) == NULL) {
        printf("errore, file non trovato\n");
        return;
    }
    fscanf(fPtr, "%d", &(*itemWrapper)->numberOfItem);
    (*itemWrapper)->itemList = (item **) malloc((*itemWrapper)->numberOfItem * sizeof(*(*itemWrapper)->itemList));
    for (int i = 0; i < ((*itemWrapper)->numberOfItem); i++) {
        (*itemWrapper)->itemList[i] = (item *) malloc(sizeof(item));
        fscanf(fPtr, "%s %s %d %d %d %d %d %d", (*itemWrapper)->itemList[i]->name, (*itemWrapper)->itemList[i]->type,
               &(*itemWrapper)->itemList[i]->hp, &(*itemWrapper)->itemList[i]->mp, &(*itemWrapper)->itemList[i]->atk,
               &(*itemWrapper)->itemList[i]->def, &(*itemWrapper)->itemList[i]->mag, &(*itemWrapper)->itemList[i]->spr);
    }
    fclose(fPtr);
}

int itemSearchInventary(char *itemName, equipableItem itemWrapper) {
    int i = 0;
    int flag = 0;

    for (i = 0; i < itemWrapper->numberOfItem; i++) {
        if (strcmp(itemWrapper->itemList[i]->name, itemName) == 0) {
            flag = 1;
            break;
        }
    }
    if (!flag)
        return -1;
    return i;

}

int emptyItem(equipableItem itemWrapper) {
    if (itemWrapper->itemList == NULL)
        return 1;
    return 0;
}

item *indexToPointer(equipableItem itemWrapper, int index) {
    return itemWrapper->itemList[index];
}