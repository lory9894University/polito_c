//
// Created by lory9 on 28/12/2018.
//

#ifndef E03_ADJ_H
#define E03_ADJ_H
#include "calculators.h"
typedef struct adjMatrix_t * adjMatrix;
typedef struct adjList_t * adjList;
typedef struct adjNode_t * link;
adjMatrix adjMatrixCreation(graphEdges graph,indexTable table);
void printAdj(adjMatrix matrix,indexTable table);
int adjCheckMatrix(char *v1, char *v2, char *v3, adjMatrix matrix,indexTable table);
adjList adjListCreation(adjMatrix matrix);
int adjCheckList(char *v1, char *v2, char *v3, adjList list,indexTable table);

#endif //E03_ADJ_H
