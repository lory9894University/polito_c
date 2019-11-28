//
// Created by lorenzodentis on 05/12/2018.
//

#ifndef ES_8_3_ITEM_H
#define ES_8_3_ITEM_H
#define SMALLCHAR 51

typedef struct singleItem{
    char name[SMALLCHAR],type[SMALLCHAR];
    int hp, mp, atk, def, mag,spr;
} item;
typedef struct singleEquipableItem{
    item** itemList;
    int numberOfItem;
    int maxNumberOfItem;
}equipableItem;

void newItemVector(equipableItem *itemWrapper, char *inputFile);
int itemSearch(char *itemName,item **itemVector,int itemNr);
void itemPrint(item itemToPrint);
void itemInit(equipableItem *itemWrapper);
int emptyItem(equipableItem itemWrapper);
void itemWrapperFree(equipableItem itemWrapper);
void itemFree(item **itemVector,int nItem);
#endif //ES_8_3_ITEM_H
