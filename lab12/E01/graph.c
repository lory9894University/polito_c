//
// Created by lorenzodentis on 14/01/2019.
//

#include "graph.h"
#include <stdlib.h>

#define MAXC 30
struct graph {
    int V;
    int E;
    int **madj;
    ST tab;
};

int VertexNr(Graph G) {
    return G->V;
}

ST getSt(Graph G) {
    return G->tab;
}

int EdgesNr(Graph g) {
    return g->E;
}

int GETmadj(Graph G, int ***matrix) {
    *matrix = G->madj;
    return G->V;
}

void matrixPrint(Graph G) {
    int i, j;

    for (i = 0; i < 14; i++) {
        for (j = 0; j < 14; j++) {
            printf("%d ", G->madj[i][j]);
        }
        printf("\n");
    }
}

void insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    if (G->madj[v][w] == 0)
        G->E++;
    G->madj[v][w] = 1;
    G->madj[v][w] = wt;
}

int **MATRIXinit(int r, int c, int value) {
    int **matrix, i, j;

    matrix = malloc(sizeof(int **) * r);
    for (i = 0; i < r; i++) {
        matrix[i] = malloc(sizeof(int *) * c);
        for (j = 0; j < c; j++) {
            matrix[i][j] = value;
        }
    }
    return matrix;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof(*G));
    G->V = V;
    G->E = 0;
    G->madj = MATRIXinit(V, V, 0);
    G->tab = STinit(V);
}

Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    Graph G;

    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);
    for (i = 0; i < V; i++) {
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1);
    }
    while (fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >= 0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}

Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}
