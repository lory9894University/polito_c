//
// Created by lorenzodentis on 05/12/2018.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
void itemInit(equipableItem *itemWrapper){
    itemWrapper->itemList=NULL;
}
void itemPrint(item itemToPrint){
    printf("\t-nome:%s tipo:%s hp:%d mp:%d atk:%d def:%d mag:%d spr:%d\n",itemToPrint.name,itemToPrint.type,itemToPrint.hp,itemToPrint.mp,itemToPrint.atk,itemToPrint.def,itemToPrint.mag,itemToPrint.spr);
}
void newItemVector(equipableItem *itemWrapper, char *inputFile){
    FILE *fPtr;

    if (itemWrapper->itemList!=NULL){
        itemWrapperFree(*itemWrapper);
    }
    if ((fPtr=fopen(inputFile,"r"))==NULL) {
        printf("errore, file non trovato\n");
        return;
    }
    fscanf(fPtr,"%d",&itemWrapper->numberOfItem);
    itemWrapper->itemList=(item **)malloc(itemWrapper->numberOfItem*sizeof(*itemWrapper->itemList));
    for (int i = 0; i <(itemWrapper->numberOfItem) ; i++) {
        itemWrapper->itemList[i]=(item*)malloc(sizeof(item));
        fscanf(fPtr,"%s %s %d %d %d %d %d %d", itemWrapper->itemList[i]->name,itemWrapper->itemList[i]->type, &itemWrapper->itemList[i]->hp,&itemWrapper->itemList[i]->mp,&itemWrapper->itemList[i]->atk,&itemWrapper->itemList[i]->def,&itemWrapper->itemList[i]->mag,&itemWrapper->itemList[i]->spr);
    }
   fclose(fPtr);
}
int itemSearch(char *itemName,item **itemVector,int itemNr){
    int i=0;
    int flag=0;

    for (i = 0; i <itemNr ; i++){
        if(strcmp(itemVector[i]->name,itemName)==0) {
            flag=1;
            break;
        }
    }
    if(!flag)
        return -1;
    return i;

}
int emptyItem(equipableItem itemWrapper){
    if (itemWrapper.itemList==NULL)
        return 1;
    return 0;
}
void itemFree(item **itemVector,int nItem){
    int i;

    if (itemVector!=NULL) { //se il vettore è vuoto non bisogna deallocarlo
        for (i = 0; i < nItem; i++) {
            free(itemVector[i]);
        }
    }
}
void itemWrapperFree(equipableItem itemWrapper){
    itemFree(itemWrapper.itemList,itemWrapper.numberOfItem);
    free(itemWrapper.itemList);
}