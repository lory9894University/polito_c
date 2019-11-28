//
// Created by lory9 on 28/12/2018.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "adj.h"
struct adjMatrix_t{
    int dimension; //che poi sarebbe il numero di vertici
    int **matrix;
};
struct adjList_t{
    link *listVector;
    int dimension; //che poi sarebbe il numero di vertici
};
struct adjNode_t{
    link next;
    int nodeId;
};
link newNode(int nodeId){
    link x=malloc(sizeof(*x));
    x->next=NULL;
    x->nodeId=nodeId;
    return x;
}
adjMatrix adjMatrixCreation(graphEdges graph,indexTable table){
    adjMatrix matrixWrapper =malloc(sizeof(struct adjMatrix_t));
    int i,j;

    matrixWrapper->dimension=howManyVertex(table);
    matrixWrapper->matrix=malloc(sizeof(int*)* matrixWrapper->dimension);
    for (i = 0; i <matrixWrapper->dimension ; i++) {
        matrixWrapper->matrix[i]=malloc(sizeof(int)* matrixWrapper->dimension);
        for (j=0; j <matrixWrapper->dimension ; j++){
            matrixWrapper->matrix[i][j]=-1;
        }
    }
    for (i = 0; i <graph->edgesNr ; i++) {
           matrixWrapper->matrix[graph->edgesVect[i].v1][graph->edgesVect[i].v2]=graph->edgesVect[i].weight;
           matrixWrapper->matrix[graph->edgesVect[i].v2][graph->edgesVect[i].v1]=graph->edgesVect[i].weight;
    }

    return matrixWrapper;
}
void printAdj(adjMatrix matrix,indexTable table){
    int flag=0;
    for (int i = 0; i <matrix->dimension ; i++) {
        printf("vertice: %s, vertici collegati: ",indexToName(i,table));
        flag=0;
        for (int j = 0; j <matrix->dimension ; j++) {
            if (matrix->matrix[i][j]!=-1){
                flag=1;
                printf("%s ",indexToName(j,table));
            }
        }
        if (!flag)
            printf("nessun vertice collegato al vertice cercato\n");
        else
            printf("\n");
    }
}
int adjCheckMatrix(char *v1, char *v2, char *v3, adjMatrix matrix,indexTable table){
    int first=nameToIndex(v1,table),second=nameToIndex(v2,table),third=nameToIndex(v3,table);
    if (first == -1 || second == -1 || third==-1) {
        printf("impossibile trovare uno o più vertici\n");
        return 0;
    }
    if (matrix->matrix[first][second]==-1 || matrix->matrix[second][third]==-1 || matrix->matrix[second][third]==-1)
        return 0;

    return 1;
}
adjList adjListCreation(adjMatrix matrix){ //todo non funzionante
    adjList list=malloc(sizeof(*list));
    link lastNode=malloc(sizeof(*lastNode));

    list->dimension=matrix->dimension;
    list->listVector=malloc(sizeof(link) * list->dimension);
    for (int i = 0; i <matrix->dimension ; i++) {
        list->listVector[i]=malloc(sizeof(link));
        lastNode=newNode(i);
        list->listVector[i]=lastNode;
        for (int j = 0; j <matrix->dimension ; j++) {
            if (matrix->matrix[i][j]!=-1){
                lastNode->next=newNode(j);
                lastNode=lastNode->next;
            }
        }
    }
    return list;
}
int adjCheckList(char *v1, char *v2, char *v3, adjList list,indexTable table){
    int flag1=0,flag2=0,flag3=0;
    int first=nameToIndex(v1,table),second=nameToIndex(v2,table),third=nameToIndex(v3,table);
    link x;

    if (first == -1 || second == -1 || third==-1) {
        printf("impossibile trovare uno o più vertici\n");
        return 0;
    }
    x=list->listVector[first];
    while(x!=NULL && !(flag1 && flag2)) {
        if (x->nodeId==second)
            flag1=1;
        if (x->nodeId==third)
            flag2=1;
        x=x->next;
    }
    if (flag1 && flag2){
        x=list->listVector[second];
        while (x!=NULL && !(flag3)) {
            if (x->nodeId == third)
                flag3=1;
            x=x->next;
        }
    }
    if (flag1 && flag2 && flag3 )
        return 1;
    return 0;
}