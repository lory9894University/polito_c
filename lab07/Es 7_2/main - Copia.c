#include <stdio.h>
#include <stdlib.h>
#define dbg 1

typedef struct {
    int gem[4], gemvalue[4];
    int necklaceLength, max_rep;
}jewel;
typedef struct {
    int *sol;
    int length;
    int value;
}solution;

int filter(int gemInserted,int *sol,int pos,int max_rep);
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
#if dbg
    setbuf(stdout,0);
#endif
    inserimento(&jewelsVect,&necklaceNumber);
#if dbg
    for (i = 0; i <necklaceNumber ; ++i) {
        printf("%d %d %d %d\n",jewelsVect[i].gem[0],jewelsVect[i].gem[1],jewelsVect[i].gem[2],jewelsVect[i].gem[3]);
        printf("%d\n",jewelsVect[i].max_rep);
    }
#endif

    for (i = 0; i <necklaceNumber ; i++) {
        printf("# %d collana: ", i);
        printf("%d zafiri,%d rubini,%d cosa e' s,%d topazi\n",jewelsVect[i].gem[0],jewelsVect[i].gem[1],jewelsVect[i].gem[2],jewelsVect[i].gem[3]);
        necklaceCreation(jewelsVect[i]);
        printf("\n");
    }
    /**/
    return 0;
}

int filter(int gemInserted,int sol[],int pos,int max_rep){ //restituisce 1 se la pietra può essere messa lì
    for (int i=pos-1; i>pos-1-max_rep ; i--){
        if (gemInserted==sol[i])
            return 0;
    }
    if (pos==0)
        return 1;
    if (sol[pos-1]==0){
        if (gemInserted==0 || gemInserted==1)
            return 1;
    }
    if (sol[pos-1]==1){
        if (gemInserted==2 || gemInserted==3)
            return 1;
    }
    if (sol[pos-1]==2){
        if (gemInserted==0 || gemInserted==1)
            return 1;
    }
    if (sol[pos-1]==3){
        if (gemInserted==3|| gemInserted==2)
            return 1;
    }
    return 0;
}

void necklaceCreation(jewel jewelsVect) {
    solution localsol,globalsol;
    localsol.sol=(int *)malloc(sizeof(int)*jewelsVect.necklaceLength);
    globalsol.sol=(int *)malloc(sizeof(int)*jewelsVect.necklaceLength);
    int gem[4]={jewelsVect.gem[0],jewelsVect.gem[1],jewelsVect.gem[2],jewelsVect.gem[3]};//per favorire la modularità preferisco non permettere alla funzione di modificare i valori della struct
    int type[4]={0,1,2,3}; //se dovessi stampare userei dei char
    int i, l, r, possComb=0;
    globalsol.length=0;
    //TODO trasformare gem in un vettore contenente quante gemme ho usato e cambiare l'if ricorsivo in un gem[i]=!jewelsVect.gem[i]
    /*in questo modo posso calcolare direttamente sia se smeraldi>topazi sia il valore della collana*/
    l=0;
    r=jewelsVect.necklaceLength;
    while(l<=r) {
        i=(l+r)/2;
        possComb=combination(0,&globalsol,i,&localsol,&gem,0,type,jewelsVect);
        if (possComb==1){
            l=i+1;
        }
        if (possComb==0){
            r=i-1;
        }
        printf("%d ",i);
    }
    printf("{ ");

    for (size_t i=0 ; i < globalsol.length; i++){
        printf("%d ",globalsol.sol[i]);
    }
    printf("} lunghezza della collana:%d\n",globalsol.length);


}
int combination(int possibleSolution,solution *globalsol, int k, solution *localsol,int (*gem)[],int pos,int type[],jewel jewelsVect){
    int i=0;

    if (pos==k) {
        globalsol->length = k;
        for (i = 0; i <k ; i++) {
            globalsol->sol[i]=localsol->sol[i];
        }
        return 1;
    }

    for (i = 0; i <4 ; i++) {
        if (filter(type[i], localsol->sol, pos, jewelsVect.max_rep)){
            if ((*gem)[type[i]]!=0){
                localsol->sol[pos]=type[i];
                (*gem)[type[i]]--;
                possibleSolution=combination(possibleSolution, globalsol,k,localsol,gem,pos+1,type,jewelsVect);
                (*gem)[type[i]]++;
            }
        }

    }
    return possibleSolution;
}