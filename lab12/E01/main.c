#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ST.h"
#include "graph.h"
#include "DAG.h"

typedef struct vertex_t {
    int v1, v2; //occhio che il grafo è orientato, v1 e v2 non sono commutabili
    int wt;
} edges;
typedef struct solvect_t {
    edges **solutions;
    int alocated, used, cardinality;
} solVect;

edges *bestDAG(solVect sol);

int eliminationRecursive(int pos, int k, int **madj, int dim, solVect *sol, edges *solTmp);

int DAGfilter(int **mat, int dim);

solVect possibleElimination(Graph g);

int DAGfilter(int **mat, int dim);

Graph acquisition();

int **madjCreation(edges *E, int edgesNum, int vertexNum);

int main() {
    Graph grafo;
    solVect delEdges; //vettore di insiemi di archi eliminabili
    edges *bestDag;
    int dagDimension;
    dag graphResult;

    setbuf(stdout, 0);
    grafo = acquisition();
    matrixPrint(grafo);
    delEdges = possibleElimination(grafo);
    dagDimension = delEdges.cardinality;
    bestDag = malloc(sizeof(edges) * delEdges.cardinality);
    bestDag = bestDAG(delEdges);
    graphResult.tab = getSt(grafo);
    graphResult.vertex = VertexNr(grafo);
    graphResult.madj = madjCreation(bestDag, dagDimension, graphResult.vertex);
    DagLonghestPath(graphResult);
    return 0;
}

int **madjCreation(edges *E, int edgesNum, int vertexNum) {
    int **matrix, i, j;

    matrix = malloc(sizeof(int **) * vertexNum);
    for (i = 0; i < vertexNum; i++) {
        matrix[i] = malloc(sizeof(int *) * vertexNum);
        for (j = 0; j < vertexNum; j++) {
            matrix[i][j] = 0;
        }
    }
    for (i = 0; i < edgesNum; i++) {
        matrix[E[i].v1][E[i].v2] = E[i].wt;
    }

    return matrix;
}

Graph acquisition() {
    Graph G;

    FILE *fptr = fopen("grafo.txt", "r");
    G = GRAPHload(fptr);
    fclose(fptr);
    return G;
}

solVect possibleElimination(Graph g) {
    int **madj, matrixDim;
    solVect x;
    int i, j;
    edges *solTmp; //vettore sovrallocato, mi sembra accettabile come spreco, volendo fare meglio si può usare una lista
    //la realloc è da escludere a causa del fatto che devo riallocare ogni ricorsione, complessità potenzialmente elevata

    matrixDim = GETmadj(g, &madj);
    solTmp = malloc(sizeof(*solTmp) * (int) pow(matrixDim, 2));
    x.used = 0;
    x.alocated = 1;
    x.solutions = malloc(sizeof(*x.solutions) * x.alocated);

    for (i = 0; i < EdgesNr(g); i++) {
        if (eliminationRecursive(0, i, madj, matrixDim, &x, solTmp))
            break;
    }
    printf("gli insiemi di cardinalita' %d eliminabili sono:\n", i);
    x.cardinality = i;
    for (i = 0; i < x.used; i++) {
        printf("{ ");
        for (j = 0; j < x.cardinality; j++) {
            printf("%d-%d ", x.solutions[i][j].v1, x.solutions[i][j].v2);
        }
        printf("}\n");
    }
    return x;
}

int eliminationRecursive(int pos, int k, int **madj, int dim, solVect *sol, edges *solTmp) {
    int found = 0;
    int i = 0, j = 0;

    if (pos == k) {
        if (!DAGfilter(madj, dim))
            return 0;
        if (sol->used >= sol->alocated) {
            sol->alocated = sol->alocated * 2;
            sol->solutions = realloc(sol->solutions, sizeof(*sol->solutions) * sol->alocated);
        }
        sol->solutions[sol->used] = malloc(sizeof(edges) * k);
        for (i = 0; i < k; i++) {
            sol->solutions[sol->used][i].v1 = solTmp[i].v1;
            sol->solutions[sol->used][i].v2 = solTmp[i].v2;
        }
        sol->used++;
        return 1;
    }

    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            if (madj[i][j] != 0) {
                solTmp[pos].v1 = i;
                solTmp[pos].v2 = j;
                solTmp[pos].wt = madj[i][j];
                madj[i][j] = 0;
                found = eliminationRecursive(pos + 1, k, madj, dim, sol, solTmp);
                if (found)
                    return 1;
                madj[i][j] = solTmp[pos].wt;
            }
        }
    }

    return found;
}

int deepVisit(int **mat, int dim, int *pre, int *st, int *time, int i) {
    int j, Found;

    pre[i] = (*time)++;
    for (j = 0; j < dim; j++) {
        if (mat[i][j] != 0) {
            if (pre[j] == -1) {
                Found = deepVisit(mat, dim, pre, st, time, j);
                if (!Found)
                    return 0;
            } else {
                if (pre[j] < pre[i])
                    return 0;
            }
        }
    }

    return 1;
}

int DAGfilter(int **mat, int dim) {
    int *pre, *st, time = 0;
    int i;

    pre = malloc(sizeof(int) * dim);
    st = malloc(sizeof(int) * dim);
    for (i = 0; i < dim; i++) {
        pre[i] = st[i] = -1;
    }

    return deepVisit(mat, dim, pre, st, &time, 0);
}

edges *bestDAG(solVect sol) {
    int i, j;
    int bestIndex = 0;
    int localWt, bestWt = 0;

    for (i = 0; i < sol.used; i++) {
        localWt = 0;
        for (j = 0; j < sol.cardinality; j++) {
            localWt += sol.solutions[i][j].wt;
        }
        if (localWt > bestWt) {
            bestWt = localWt;
            bestIndex = i;
        }
    }

    return sol.solutions[bestIndex];
}

