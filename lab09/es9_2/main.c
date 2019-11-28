#include <stdio.h>
#include <stdlib.h>

#define dbg 0

/*ATTENZIONE programma non funzionante, ho dedicato troppo tempo a questo programma pur non riuscendo a completarlo,
 * la logica mi sembra corretta ed in ogni caso l'ho fatto, lo consegno incompleto*/
typedef struct {
    int gem[4];
    int maxNecklaceLength;
} jewel;
typedef struct {
    int *sol;
    int length;
} solution;

int filter(int gemInserted, int *sol, int pos);

void necklaceCreation(int *****lenghtMatrix, jewel jewelsVect); //wrapper
int
combination(int solutionFound, solution *globalsol, int k, solution *localsol, int (*gem)[4], int (*gemUsed)[], int pos,
            int type[], int *****lenghtMatrix); //ritorna 1 se viene trovata una combinazione
/*dichiarazione funzioni semplici*/
void inserimento(jewel **vect, int *necklaceNumber) {
    FILE *fptr;

    if ((fptr = fopen("gioielli.txt", "r")) == NULL) {
        printf("errore, nessun file trovato\n");
        exit(1);
    }
    fscanf(fptr, "%d", necklaceNumber);
    *vect = (jewel *) malloc(*necklaceNumber * sizeof(jewel));
    for (size_t i = 0; i < *necklaceNumber; i++) {
        fscanf(fptr, "%d %d %d %d", &((*vect)[i].gem[0]), &((*vect)[i].gem[1]), &((*vect)[i].gem[2]),
               &((*vect)[i].gem[3]));
        (*vect)[i].maxNecklaceLength = (*vect)[i].gem[0] + (*vect)[i].gem[1] + (*vect)[i].gem[2] + (*vect)[i].gem[3];
    }
    fclose(fptr);
}

void solutionPrint(int *sol, int solLength, int value, int *solJewels) {
    printf("prima collana :\ncollana di lunghezza: %d, contenente:\n\t-%d zaffiri\n\t-%d rubini\n\t-%d topazi\n\t-%d smeraldi\n"
           "per un volore di: %d", solLength, solJewels[0], solJewels[1], solJewels[2], solJewels[2], value);
}

/*allocazione della matrice quadridimensionale*/
void malloc4d(int *****mat, int nz, int nr, int nt, int ns) {

    *mat = (int ****) malloc((nz + 1) * sizeof(int ***));
    for (int i = 0; i <= nz; i++) {
        (*mat)[i] = (int ***) malloc((nr + 1) * sizeof(int **));
        for (int j = 0; j <= nr; j++) {
            (*mat)[i][j] = (int **) malloc((nt + 1) * sizeof(int *));
            for (int k = 0; k <= nt; k++) {
                (*mat)[i][j][k] = (int *) malloc((ns + 1) * sizeof(int));
                for (int l = 0; l <= ns; l++) {
                    (*mat)[i][j][k][l] = 0;
                }
            }
        }
    }
}

int main() {
    jewel *jewelsVect;
    int necklaceNumber;
    int ****lenghtMatrix;
    size_t i;
    setbuf(stdout, 0);
    inserimento(&jewelsVect, &necklaceNumber);

    for (i = 0; i < necklaceNumber; i++) {
        malloc4d(&lenghtMatrix, jewelsVect[i].gem[0], jewelsVect[i].gem[1], jewelsVect[i].gem[2], jewelsVect[i].gem[3]);
        printf("# %d collana: ", i + 1);
        printf("%d zafiri,%d rubini,%d topazi,%d smeraldi\n", jewelsVect[i].gem[0], jewelsVect[i].gem[1],
               jewelsVect[i].gem[2], jewelsVect[i].gem[3]);
        necklaceCreation(&lenghtMatrix, jewelsVect[i]);
        printf("\n");
    }
    return 0;
}

void necklaceCreation(int *****lenghtMatrix, jewel jewelsVect) {
    solution localsol, globalsol;
    localsol.sol = (int *) malloc(sizeof(int) * jewelsVect.maxNecklaceLength);
    globalsol.sol = (int *) malloc(sizeof(int) * jewelsVect.maxNecklaceLength);
    int gem[4] = {jewelsVect.gem[0], jewelsVect.gem[1], jewelsVect.gem[2], jewelsVect.gem[3]};
    int gemUsed[4] = {0, 0, 0, 0};
    int type[4] = {0, 1, 2, 3};
    int i, l, r, possComb = 0;

    //todo, si potrebbe usare la ricerca dicotomica?
    /*l=0;
    r=jewelsVect.maxNecklaceLength;
    while(l<=r) {
        i=(l+r)/2;
        possComb=combination(0,&globalsol,i,&localsol,&gem,&gemUsed,0,type,lenghtMatrix);
        if (possComb==1){
            l=i+1;
        }
        if (possComb==0){
            r=i-1;
        }
    }
     */
    for (i = 0; i < jewelsVect.maxNecklaceLength; i++) {
        possComb = combination(0, &globalsol, i, &localsol, &gem, &gemUsed, 0, type, lenghtMatrix);
    }
    /*printf("{ ");
    for (i=0 ; i < globalsol.length; i++){
        printf("%d ",globalsol.sol[i]);
    }
    */
    printf("lunghezza della collana:%d\n", globalsol.length);
    //todo funzione di ricavo della collana a partire dalla sua lunghezza
    //funzione di free di quel mostro quadridimensionale

}

int filter(int gemInserted, int sol[], int pos) { //restituisce 1 se la pietra può essere messa lì
    if (pos == 0)
        return 1;
    if (sol[pos - 1] == 0) { //0=zaffiri
        if (gemInserted == 0 || gemInserted == 1)
            return 1;
    }
    if (sol[pos - 1] == 1) { //rubini
        if (gemInserted == 2 || gemInserted == 3)
            return 1;
    }
    if (sol[pos - 1] == 2) { //topazi
        if (gemInserted == 0 || gemInserted == 1)
            return 1;
    }
    if (sol[pos - 1] == 3) { //smaraldi
        if (gemInserted == 3 || gemInserted == 2)
            return 1;
    }
    return 0;
}

int
combination(int solutionFound, solution *globalsol, int k, solution *localsol, int (*gem)[4], int (*gemUsed)[], int pos,
            int type[], int *****lenghtMatrix) {
    int i = 0;

    if (pos >= k && globalsol->length < k) {
        globalsol->length = k;
        /*aggiunta della soluzione trovata nella matrice*/
        (*lenghtMatrix)[(*gemUsed)[0]][(*gemUsed)[1]][(*gemUsed)[2]][(*gemUsed)[3]] = k;
        for (i = 0; i < globalsol->length; i++) {
            globalsol->sol[i] = localsol->sol[i];
        }
        return 1;
    }

    for (i = 0; i < 4; i++) {
        if ((*lenghtMatrix)[(*gemUsed)[0]][(*gemUsed)[1]][(*gemUsed)[2]][(*gemUsed)[3]] != 0)
            /*se la soluzione è già stata calcolata in precendenza non la si ricalcola, la vado a prendere nella matrice*/
            localsol->length = (*gemUsed)[0] + (*gemUsed)[0] + (*gemUsed)[0] + (*gemUsed)[0];
        else {
            if ((*gemUsed)[type[i]] < (*gem)[type[i]]) {
                if (filter(type[i], localsol->sol, pos)) {
                    localsol->sol[pos] = type[i];
                    (*gemUsed)[type[i]]++;
                    solutionFound = combination(solutionFound, globalsol, k, localsol, gem, gemUsed, pos + 1, type,
                                                lenghtMatrix);
                    (*gemUsed)[type[i]]--;
                }
            }
        }
    }
    return solutionFound;
}
