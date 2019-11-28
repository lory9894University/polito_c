//
// Created by lorenzodentis on 09/01/2019.
//
#include "date.h"
#ifndef E_1_RATING_H
#define E_1_RATING_H
typedef struct rtBst_t *rtBst;
typedef struct quotation_t *quotation;
struct quotation_t{
    float rating;
    float num,den;
    int subTree;
    dateType date;
    quotation right,left;
};
/*struct di transizione fra i dati salvati come elenco di transazioni ed il BST
 * l'elenco di transazione in realtà è un errore dovuto ad un'errata interpretazione della consegna
 * ma considerato il fatto che lo spreco di memoria è veramente trascurabile ho preferito continuare così che rifare da capo*/
typedef struct transaction_t{
    char date[11],time[6];
    float value;
    int quantity, nrDate;
}transaction;

void rawToBst(transaction *raw, int dim,rtBst bst); //funzione che crea il bst se non presente, se presente lo aggiorna
rtBst BSTCreation(transaction *raw, int dim);
quotation quotationSearch(rtBst bst,char *key);
dateType minDateFind(rtBst bst);
dateType maxDateFind(rtBst bst);
void bstExploration(rtBst bst,dateType minDate,dateType maxDate);
void needPartition(rtBst bst,int S);
#endif //E_1_RATING_H
