//
// Created by lorenzodentis on 19/12/2018.
//

#include "indexTable.h"
#include <string.h>
#include <stdlib.h>
struct indexTable_t{
    int elementsNr;
    char **nameVector;
};
void addElement(indexTable table,int position,char *name){
    table->nameVector[position]=strdup(name);
}
indexTable tableCreation(int tableDimension){
    indexTable genericTable;

    genericTable=malloc(sizeof(*genericTable));
    genericTable->elementsNr=tableDimension;
    genericTable->nameVector=malloc(sizeof(*genericTable->nameVector)*tableDimension);
    return genericTable;
}
char* indexToName(int index,indexTable genericTable){
    return genericTable->nameVector[index];
}
int nameToIndex(char *name,indexTable genericTable){
    int i;
    for (i = 0; i <genericTable->elementsNr ; i++) {
        if (!strcmp(name,genericTable->nameVector[i]))
            return i;
    }
    return -1;
}
void tableFree(indexTable genericTable){
    int i;
    for (i=0; i<genericTable->elementsNr;i++){
        free(genericTable->nameVector[i]);
    }
    free(genericTable->nameVector);
}
int howManyVertex (indexTable genericTable){
    return genericTable->elementsNr;
}