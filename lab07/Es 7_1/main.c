#include <stdio.h>
#include <stdlib.h>
#define dbg 0

typedef struct {
    int gem[4];
    int necklaceLength;
}jewel;
typedef struct {
    int *sol;
    int length;
}solution;

int filter(int gemInserted,int *sol,int pos);
void necklaceCreation(jewel jewelsVect); //wrapper
int combination(int solutionFound,solution *globalsol, int k, solution *localsol,int (*gem)[],int pos,int type[]); //ritorna 1 se viene trovata una combinazione
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
    }

    fclose(fptr);
}
void solutionPrint(int *sol, int solLength, int value, int *solJewels) {
    printf("prima collana :\ncollana di lunghezza: %d, contenente:\n\t-%d zaffiri\n\t-%d rubini\n\t-%d topazi\n\t-%d smeraldi\n"
           "per un volore di: %d",solLength, solJewels[0], solJewels[1], solJewels[2],solJewels[2], value);
}

int main() {
    jewel *jewelsVect;
    int necklaceNumber;
    size_t i;
    setbuf(stdout,0);
    inserimento(&jewelsVect,&necklaceNumber);
#if dbg
    for (i = 0; i <necklaceNumber ; ++i) {
        printf("%d %d %d %d\n",jewelsVect[i].gem[0],jewelsVect[i].gem[1],jewelsVect[i].gem[2],jewelsVect[i].gem[3]);
    }
#endif

    for (i = 0; i <necklaceNumber ; i++) {
        printf("# %d collana: ", i+1);
        printf("%d zafiri,%d rubini,%d topazi,%d smeraldi\n",jewelsVect[i].gem[0],jewelsVect[i].gem[1],jewelsVect[i].gem[2],jewelsVect[i].gem[3]);
        necklaceCreation(jewelsVect[i]);
        printf("\n");
    }
    return 0;
}
void necklaceCreation(jewel jewelsVect) {
    solution localsol,globalsol;
    localsol.sol=(int *)malloc(sizeof(int)*jewelsVect.necklaceLength);
    globalsol.sol=(int *)malloc(sizeof(int)*jewelsVect.necklaceLength);
    int gem[4]={jewelsVect.gem[0],jewelsVect.gem[1],jewelsVect.gem[2],jewelsVect.gem[3]};
    int type[4]={0,1,2,3};
    int i, l, r, possComb=0;

    l=0;
    r=jewelsVect.necklaceLength;
    while(l<=r) {
        i=(l+r)/2;
        possComb=combination(0,&globalsol,i,&localsol,&gem,0,type);
        if (possComb==1){
            l=i+1;
        }
        if (possComb==0){
            r=i-1;
        }
    }
    printf("{ ");
    for (i=0 ; i < globalsol.length; i++){
        printf("%d ",globalsol.sol[i]);
    }
    printf("} lunghezza della collana:%d\n",globalsol.length);


}
int filter(int gemInserted,int sol[],int pos){ //restituisce 1 se la pietra può essere messa lì
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

int combination(int solutionFound,solution *globalsol, int k, solution *localsol,int (*gem)[4],int pos,int type[]){
    int i=0;

    if (pos>=k && globalsol->length<k){
        globalsol->length=k;
        for (i = 0; i<globalsol->length ; i++) {
            globalsol->sol[i]=localsol->sol[i];
        }
        return 1;
    }

    for (i = 0; i <4; i++) {
        if((*gem)[type[i]]!=0){
            if (filter(type[i],localsol->sol,pos)){
                localsol->sol[pos]=type[i];
                (*gem)[type[i]]--;
                solutionFound=combination(solutionFound,globalsol,k,localsol,gem,pos+1,type);
                (*gem)[type[i]]++;
            }
        }
    }
    return solutionFound;
}