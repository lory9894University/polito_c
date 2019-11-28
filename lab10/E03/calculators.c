//
// Created by lorenzodentis on 19/12/2018.
//

#include "calculators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 31
#define dbg 1
/*strutture che identificano i dati "sporchi", cioè copiati e basta, senza alcuna organizzazione*/
typedef struct {
    char *name1,*name2;
    int weight;
} edgesRow;
struct edgesList_t{
    int used;
    edgesRow *rowsList;
};
void swap (char *vet1,char *vet2){
    char swap[MAXCHAR];

    strcpy(swap,vet1);
    strcpy(vet1,vet2);
    strcpy(vet2,swap);
}  //funzioni private?!
rowsSaved rawAcquisition(char *fileName){
    FILE *fptr;
    rowsSaved edges=malloc(sizeof(struct edgesList_t *));


    char name1[MAXCHAR],name2[MAXCHAR];
    char subnet1[MAXCHAR],subnet2[MAXCHAR];
    int weight;
    int allocated;

    allocated=1;
    edges->used=0;
    edges->rowsList=(edgesRow *)malloc(sizeof(edgesRow) * allocated);
    if ((fptr=fopen(fileName,"r"))==NULL) {
        printf("file non trovato\n");
        exit(1);
    }
    while (fscanf(fptr,"%s %s %s %s %d",name1,subnet1,name2,subnet2,&weight)!=EOF){
        if (edges->used==allocated){
                allocated=allocated*2;
                edges->rowsList=(edgesRow *)realloc(edges->rowsList,allocated * sizeof(edgesRow));
            }
        edges->rowsList[edges->used].name1=strdup(name1);
        edges->rowsList[edges->used].name2=strdup(name2);
        edges->rowsList[edges->used].weight=weight;
        edges->used++;
    };
    //todo, funziona, guai a te se la tocchi
    fclose(fptr);

    return edges;
}
void auxiliarFree(rowsSaved edges){
    int i;

    for (i = 0; i <edges->used ; i++) {
        free(edges->rowsList[i].name1);
        free(edges->rowsList[i].name2);
        free(edges->rowsList);
    }
}
indexTable tableOrganization (rowsSaved edges){
    int i=0,j=0;
    int k,flag=0;
    indexTable table;
    int max;
    char **tempTable;

    tempTable=malloc(edges->used*2* sizeof(char*));
    for (i=0; i<edges->used;i++){
        flag=0;
        for (k = 0; k <j ; k++) {
            if (!strcmp(edges->rowsList[i].name1,tempTable[k])){
                flag=1;
                break;
            }
        }
        if (!flag){
            tempTable[j]=strdup(edges->rowsList[i].name1);
            j++;
        }
        flag=0;
        for (k = 0; k <j ; k++) {
            if (!strcmp(edges->rowsList[i].name2,tempTable[k])){
                flag=1;
                break;
            }
        }
        if (!flag){
            tempTable[j]=strdup(edges->rowsList[i].name2);
            j++;
        }
    }
    /*creazione della tabella di simboli di dimensione adeguata*/
    table=tableCreation(j);
    //selection sort
    for (i = 0; i <j ; i++) {
        max=i;
        for (k = i+1; k <j ; k++) {
            if (strcmp(tempTable[max],tempTable[k])>0)
                max=k;
        }
        swap(tempTable[max],tempTable[i]);
    }

    for (k = 0; k <j ; k++) {
        addElement(table,k,tempTable[k]);
    }

    return table;
}
graphEdges edgesOrganization (rowsSaved edges,indexTable table){
    graphEdges graph=malloc(sizeof(struct edges_t));
    graph->edgesVect=malloc(sizeof(edge)* edges->used);

    graph->edgesNr=edges->used;
    for (int i = 0; i <edges->used ; i++) {
        graph->edgesVect[i].v1=nameToIndex(edges->rowsList[i].name1,table);
        graph->edgesVect[i].v2=nameToIndex(edges->rowsList[i].name2,table);
        graph->edgesVect[i].weight=edges->rowsList[i].weight;
    }
    return graph;

}

