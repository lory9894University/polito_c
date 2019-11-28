//
// Created by lorenzodentis on 16/01/2019.
//
#include "ST.h"
#include "graph.h"

#ifndef E01_DAG_H
#define E01_DAG_H
typedef struct dag_t {
    int vertex;
    int edges;
    int **madj;
    ST tab;
} dag;

int **DagLonghestPath(dag graph);

#endif //E01_DAG_H
