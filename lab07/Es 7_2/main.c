#include <stdio.h>
#include <stdlib.h>
#define dbg 0

typedef struct {
    int gem[4], gemvalue[4];
    int necklaceLength, max_rep;
}jewel;
typedef struct {
    int *sol;
    int length;
    int value;
}solution;

int filter(int gemInserted,int *sol,int pos,int max_rep,int gem[]);
void necklaceCreation(jewel jewelsVect); //wrapper
int combination(int possibleSolution,solution *globalsol, int k, solution *localsol,int (*gem)[],int pos,int type[],jewel jewelsVect);
/*dichiarazione funzioni semplici*/
void inserimento (jewel **vect,int *necklaceNumber){
    FILE *fptr;

    if ((fptr=fopen("gioielli.txt","r"))==NULL){
        printf("errore, nessun file trovato\n");
        exit(1);
    }
    fscanf(fptr,"%d",necklaceNumber);
    *vect=(jewel *)malloc(*necklaceNumber * sizeof(jewel));
    for (size_t i = 0; i <*necklaceNumber ; i++) {
        fscanf(fptr, "%d %d %d %d",&((*vect)[i].gem[0]),&((*vect)[i].gem[1]),&((*vect)[i].gem[2]),&((*vect)[i].gem[3]));
        (*vect)[i].necklaceLength=(*vect)[i].gem[0]+(*vect)[i].gem[1]+(*vect)[i].gem[2]+(*vect)[i].gem[3];
        fscanf(fptr, "%d %d %d %d",&((*vect)[i].gemvalue[0]),&((*vect)[i].gemvalue[1]),&((*vect)[i].gemvalue[2]),&((*vect)[i].gemvalue[3]));
        fscanf(fptr,"%d",&((*vect)[i].max_rep));
    }

    fclose(fptr);
}

int main() {
    jewel *jewelsVect;
    int necklaceNumber;
    size_t i;
    /*caricamento in memoria dei dati*/
    inserimento(&jewelsVect,&necklaceNumber);
    /*ripetizione su tutti i test */
    for (i = 0; i <necklaceNumber; i++) {
        printf("# %d collana: ", i+1);
        printf("%d zafiri [%d],%d rubini[%d],%d topazi[%d],%d smeraldi[%d]\n",jewelsVect[i].gem[0],jewelsVect[i].gemvalue[0],jewelsVect[i].gem[1],jewelsVect[i].gemvalue[1],jewelsVect[i].gem[2],jewelsVect[i].gemvalue[2],jewelsVect[i].gem[3],jewelsVect[i].gemvalue[3]);
        printf("maxrip=%d\n",jewelsVect->max_rep);
        necklaceCreation(jewelsVect[i]);
        printf("\n");
    }
    free(jewelsVect);
    return 0;
}

int filter(int gemInserted,int sol[],int pos,int max_rep,int gem[]){ //restituisce 1 se la pietra può essere messa lì

    if (pos==0) //prima pietra sempre inseribile
        return 1;
    /*contollo riguardo alle max pietre consecutive, fare riferimento alla specifica*/
    for (size_t i=pos-1 ,flag=0; i>pos-1-max_rep ; i--){
        if (gemInserted==sol[i])
            flag++;
        if (flag>=max_rep)
            return 0;
    }

    if (gemInserted==0 && (gem[0]>=gem[3])){
        /*se la funzione sta tentando di inserire uno zaffiro e il numero di zaffiri è maggiore o uguale al numero di smeraldi
         * la pietra non può essere inserita*/
        return 0;
    }
    if (sol[pos-1]==0){ //rubini
        if (gemInserted==0 || gemInserted==1)
            return 1;
    }
    if (sol[pos-1]==1){ //zafiri
        if (gemInserted==2 || gemInserted==3)
            return 1;
    }
    if (sol[pos-1]==2){ //smeraldi
        if (gemInserted==0 || gemInserted==1)
            return 1;
    }
    if (sol[pos-1]==3){ //topazi
        if (gemInserted==3|| gemInserted==2)
            return 1;
    }
    return 0;
}

void necklaceCreation(jewel jewelsVect) {
    solution localsol,globalsol;
    localsol.sol=(int *)malloc(sizeof(int)*jewelsVect.necklaceLength);
    globalsol.sol=(int *)malloc(sizeof(int)*jewelsVect.necklaceLength);
    int gem[4]={0,0,0,0};
    int type[4]={0,1,2,3};
    globalsol.length=0;
    globalsol.value=0;

    /*combinazioni semplici (controllare sugli appunti)*/
    for (int i =jewelsVect.necklaceLength ; i>0 ; i++) { //non è possibile usare la ricerca dicotomica
      combination(0,&globalsol,i,&localsol,&gem,0,type,jewelsVect);
    }
    free(localsol.sol);
    /*stampa della composizione ottimale*/
    printf("composizione della collana usando %d gemme\n", globalsol.length);
    printf("{ ");
    for (size_t i=0 ; i < globalsol.length; i++){
        printf("%d ",globalsol.sol[i]);
    }
    printf("} valore della collana:%d\n",globalsol.value);
    free(globalsol.sol);

}
int combination(int possibleSolution,solution *globalsol, int k, solution *localsol,int (*gem)[],int pos,int type[],jewel jewelsVect){
    int i=0;

    if (pos==k) {
        /*condizione di terminazione (con ritorno 0 "non trovato" in caso non sia possibile aggiornare la soluzione ad un valore maggiore)*/
        localsol->value=((*gem)[0]*jewelsVect.gemvalue[0])+((*gem)[1]*jewelsVect.gemvalue[1])+((*gem)[2]*jewelsVect.gemvalue[2])+((*gem)[3]*jewelsVect.gemvalue[3]);//calcolo del valore
        /*aggiornamento della soluzione a valore massimo*/
        if (globalsol->value<localsol->value) {
            globalsol->value=localsol->value;
            globalsol->length = k;
            for (i = 0; i < k; i++) {
                globalsol->sol[i] = localsol->sol[i];
            }
            return 1;
        }
        return 0;
    }

    for (i = 0; i <4 ; i++) {
        if (filter(type[i], localsol->sol, pos, jewelsVect.max_rep,*gem)){ //controllo posizionamento della pietra
            if ((*gem)[type[i]]<jewelsVect.gem[type[i]]){ //controllo disponibilità pietra
                localsol->sol[pos]=type[i];
                /*viene inserita la gemma e si prosegue alla gemma successiva*/
                (*gem)[type[i]]++;
                possibleSolution=combination(possibleSolution, globalsol,k,localsol,gem,pos+1,type,jewelsVect);
                /*viene rimossa l'ultima gemma inserita*/
                (*gem)[type[i]]--;
            }
        }

    }
    return possibleSolution;
}

/*TODO mancano la funzione di stampa e la free*/