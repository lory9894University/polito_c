//
// Created by lorenzodentis on 14/01/2019.
//

#ifndef E01_GRAPH_H
#define E01_GRAPH_H

#include <stdio.h>
#include "ST.h"

typedef struct edge {
    int v, w, wt;
} Edge;
typedef struct graph *Graph;

void GRAPHfree(Graph G);

int GETmadj(Graph G, int ***matrix);

int EdgesNr(Graph g);

Graph GRAPHload(FILE *fin);

void GRAPHinsertE(Graph G, int id1, int id2, int wt);

ST getSt(Graph G);

int VertexNr(Graph G);

void matrixPrint(Graph G);

#endif //E01_GRAPH_H
