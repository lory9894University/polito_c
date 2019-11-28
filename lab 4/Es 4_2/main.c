#include <stdio.h>
#include <stdlib.h>
#define N 8

int majoritywrap (int *vet, int dim);
int majority (int* vet, int l, int r);

int main() {
    //unsigned int vet[]={4,3,3,3,3,3,2,3};
    unsigned int vet[]={3,4,3,5,3,8,3,3};
    int maj;

    maj=majoritywrap(vet,N);
    if (maj==-1){
        printf("nessun numero maggioritario trovato nel vettore\n");
    }
    else
        printf("il numero maggioritario e': %d\n",maj);
    return 0;
}

int majoritywrap (int *vet, int dim){ //wrapper della funzione ricorsiva majority
    return majority(vet,0,dim-1);
}

int majority (int* vet, int l, int r) {
    int occ; //numero di occorrenze del maggiorante
    int PossibleMajor1=0, PossibleMajor2=0, i = 0;

    /*se il vettore è di un solo elemento questo è sicuramente un maggiorante*/
    if (l >= r) {
        return vet[l];
    }
    /*viene effettuato un controllo sul vettore, se ci sono piu di lunghezza/2 elementi uguali al possibile maggiorante
     * esso viene ritornato come possibile maggiorante ala funzione chiamante*/
    PossibleMajor1 = majority(vet, l, r / 2);
    occ = 0;
    if (PossibleMajor1 != -1) {
        for (i = l; i <= r; i++) {
            if (vet[i] == PossibleMajor1)
                occ++;
        }
    }

    if (occ > ((r - l) + 1) / 2)
        return PossibleMajor1;
    /*stesso controllo ma sul secondo maggiorante*/
    PossibleMajor2 = majority(vet, (r / 2) + l + 1, r);
    occ = 0;
    if (PossibleMajor2 != -1) {
        for (i = l; i <= r; i++) {
            if (vet[i] == PossibleMajor2)
                occ++;
        }
        if (occ > ((r - l) + 1) / 2)
            return PossibleMajor2;
    }

    return -1;
}