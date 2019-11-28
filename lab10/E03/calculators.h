//
// Created by lorenzodentis on 19/12/2018.
//

#ifndef E03_CALCULATORS_H
#define E03_CALCULATORS_H
#include "indexTable.h"
typedef struct edgesList_t *rowsSaved;
/*strutture che identificano gli archi organizzati secondo id e peso*/
typedef struct {
    int v1, v2, weight;
}edge; //singolo arco
struct edges_t{
    edge *edgesVect;
    int edgesNr;
}; //wrapper della lista di archi
typedef struct edges_t *graphEdges; //TODO questo ADT è un casino, voglio che il main non possa vederlo ma che adj lo possa vedere
/*questo puntatore ad un quasi ADT mi permette di trattarlo come ADT nel main, e come quasi Adt negli altri moduli (mi semplifica molto la vita)*/
rowsSaved rawAcquisition(char *fileName);
indexTable tableOrganization (rowsSaved edges);
graphEdges edgesOrganization (rowsSaved edges,indexTable table);
void auxiliarFree(rowsSaved edges);
int edgesCounter(graphEdges graph);


#endif //E03_CALCULATORS_H
