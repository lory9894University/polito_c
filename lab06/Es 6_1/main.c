#include <stdio.h>
#include <stdlib.h>

typedef struct arco{
    int vertex_u;
    int vertex_w;
} arch;

void simpleCombination(int pos ,arch *archesVect,size_t currentElement, int cardinality, int nrArches, int nrVertex, int *sol);

void copy (arch **ArchesVect , int *vertex, int *nrArches){
    FILE *fPtr= NULL;

    if((fPtr=fopen("grafo.txt","r"))==NULL){
        printf("errore,file non trovato");
        exit(1);
    }

    fscanf(fPtr,"%d %d",vertex, nrArches);
    *ArchesVect=(arch*)malloc((*nrArches) * sizeof(arch));
    for (size_t i = 0; i <*nrArches ; i++) {
        fscanf(fPtr,"%d %d",&((*ArchesVect)[i].vertex_u),&((*ArchesVect)[i].vertex_w));
    }
    fclose(fPtr);
}

int vertexCover(arch *archesVect, int vertex, int nrArches){ //funzuone wrapper che inizializza e dimensiona il vettore delle soluzioni
    int *sol;

    sol=malloc(vertex * sizeof(int));
    for (int i = 0; i <=vertex ; i++) {
        simpleCombination(0,archesVect,0, i ,nrArches,vertex,sol);
    }
}

int main() {
    arch *archesVect;
    int vertexNum;
    int nrArches;

    setbuf(stdout,0);
    copy(&archesVect,&vertexNum,&nrArches);
    vertexCover(archesVect,vertexNum,nrArches);

    return 0;
}

void simpleCombination(int pos, arch *archesVect,size_t currentElement, int cardinality,int nrArches,int nrVertex, int *sol) {
    size_t i=0;
    int flag=0;

    if (pos >= cardinality) {
        /*in questo caso sono arrivato a fine del ciclo: il numero di elementi presenti in sol è esattamente uguale
         * alla dimensione dell'insieme che voglio confrontare (prima singolo elemento, poi due e così via)*/
        for (size_t j = 0; j < nrArches; j++){
            /*ogni vertice viene avviato un ciclo che confronta gli elementi del vertice con quelli della possibile soluzione*/
            flag=0;
            for (i = 0; i <cardinality && !flag; i++) {
                if (sol[i] == archesVect[j].vertex_u || sol[i] == archesVect[j].vertex_w)
                    flag = 1;
            }
            /*se per anche solo un vertice non viene trovata alcuna corrispondenza allora quell'insieme non è vertex-cover
             * e di conseguenza non va stampato*/
            if (flag==0)
                break; //o un break o due flag
        }
        if (!flag)
            return;
        printf("{ ");
        for ( i = 0; i < cardinality; i++) {
            printf("%d ", sol[i]);
        }
        printf("}");
        return;
    }
    for (i = currentElement;  i<nrVertex ; i++) {
        sol[pos]=i; //i vertici sono numerati da 0 a nrVertici-1, utilizzo questo comando per creare l'insieme delle soluzioni
        /*la funzione viene richiamata ricorsivamente ma con l'elemento corrente incrementato di uno (vado a studiare l'elemento successivo)
         * e naturalmente anche la posizione in cui scrivere tale elemento nel vettore di soluzione*/
        simpleCombination(pos+1,archesVect,i+1,cardinality,nrArches,nrVertex,sol);
    }
    return;
}
//TODO soluzione altrernativa e più rapida: partendo dal sottoinsieme coincidente con l'insieme completo ricorrere su insiemi di k-1 elementi
/*in tal modo è possibile effettuare prunning (se 1,2 non è vertex cover ne uno ne 2 saranno vertex cover)*/