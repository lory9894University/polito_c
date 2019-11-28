//
// Created by lorenzodentis on 19/12/2018.
//

#ifndef E03_INDEXTABLE_H
#define E03_INDEXTABLE_H
typedef struct indexTable_t *indexTable;
indexTable tableCreation(int tableDimension);
void tableFree(indexTable genericTable);
char* indexToName(int index,indexTable genericTable);
int nameToIndex(char *name,indexTable genericTable);
void addElement(indexTable table,int position,char *name);
int howManyVertex (indexTable genericTable);

#endif //E03_INDEXTABLE_H
