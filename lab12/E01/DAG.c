//
// Created by lorenzodentis on 16/01/2019.
//

#include "DAG.h"
#include <stdlib.h>

void TSdfsR(dag D, int v, int *ts, int *pre, int *time) {
    int w;
    pre[v] = 0;
    for (w = 0; w < D.vertex; w++)
        if (D.madj[w][v] != 0)
            if (pre[w] == -1)
                TSdfsR(D, w, ts, pre, time);
    ts[(*time)++] = v;
}

int **DagLonghestPath(dag graph) {
    int v, time = 0, *pre, *ts;
    int j;
    pre = malloc(graph.vertex * sizeof(int));
    ts = malloc(graph.vertex * sizeof(int));
    for (v = 0; v < graph.vertex; v++) {
        pre[v] = -1;
        ts[v] = -1;
    }
    for (v = 0; v < graph.vertex; v++)
        if (pre[v] == -1)
            TSdfsR(graph, v, ts, pre, &time);
    for (v = 0; v < graph.vertex; v++)
        printf("%d ", ts[v]);

    for (v = 0; v < graph.vertex; v++) {
        for (j = 0; j < graph.vertex; j++) {

        }
    }
    return graph.madj;
}