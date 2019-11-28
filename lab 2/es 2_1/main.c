#include <stdio.h>
#include <stdlib.h>
#define MAXN 50

typedef struct measurment{
    int x,y; //posizione, x=righe, y=colonne
    int baseMax, heightMax, areaMax;
}measurment;
void leggiMatrice (int M[MAXN][MAXN], int MAXR, int *nr, int *nc);
int riconosciRegione(int M[MAXN][MAXN],  int nr, int nc, int r, int c, int *b, int *h, int *a);

int main(){

    int M [MAXN][MAXN], nr, nc, MAXR=MAXN;
    int base, height, r,c,area;
    int notFound =1; //flag che mi indica se un almeno un rettangolo è stato trovato
    measurment baseM, heightM,areaM;

    /*lettura matrice da file e salvataggio in memoria*/
    leggiMatrice(M,MAXR,&nr,&nc);

    for (r = 0; r < nr; r++) {
        for (c = 0; c <nc ; c++) {
            if (riconosciRegione(M,nr,nc,r,c,&base,&height,&area)) {
                notFound=0; //un rettangolo è stato trovato
                /* aggiornamento delle struct dei valori massimi*/
               if (base > baseM.baseMax){
                    baseM.baseMax=base;
                    baseM.heightMax=height;
                    baseM.areaMax=area;
                    baseM.x=r;
                    baseM.y=c;
                }
                if (height > heightM.heightMax){
                    heightM.heightMax=height;
                    heightM.baseMax=height;
                    heightM.areaMax=area;
                    heightM.x=r;
                    heightM.y=c;
                }
                if (area > areaM.areaMax){
                    areaM.areaMax=area;
                    areaM.heightMax=height;
                    areaM.baseMax=area;
                    areaM.x=r;
                    areaM.y=c;
                }
                /*azzeramento dei valori di confronto */
                base=0;
                area=0;
                height=0;
            }
        }
    }
    /*caso nessun rettangolo trovato */
    if (notFound)
        printf("nessun rettangolo trovato \n");
    else{
        printf("Max Base: estr. sup SX=<%d,%d> b=%d, h=%d, Area=%d\n", baseM.x,baseM.y,baseM.baseMax,baseM.heightMax,baseM.areaMax);
        printf("Max altezza: estr. sup SX=<%d,%d> b=%d, h=%d, Area=%d\n", heightM.x,heightM.y,heightM.baseMax,heightM.heightMax,heightM.areaMax);
        printf("Max area: estr. sup SX=<%d,%d> b=%d, h=%d, Area=%d\n", areaM.x,areaM.y,areaM.baseMax,areaM.heightMax,areaM.areaMax);
    }

    return 0;
}

void leggiMatrice (int M[MAXN][MAXN] ,int MAXR, int *nr, int *nc){
    FILE *fp;

    /*controllo riguardso all'effettiva presenza del file*/
    if((fp=fopen("matrice.txt","r"))==NULL){
        printf("errore, file non trovato\n");
        exit(1);
    }
    /*controllo riguardo alla formattazione del file in maniera corretta*/
    fscanf(fp,"%d %d", &*nr,&*nc);
    if (*nc>MAXR || *nr>MAXR){
        printf("errore, il numero di righe o il numero di colonne eccedono il valore massimo");
    }
    /*copia del file in memoria*/
    for (unsigned i=0 ; i<*nr; i++){
        for (unsigned j=0; j<*nc; j++){
            fscanf(fp,"%d", &M[i][j]);
        }
    }
    fclose(fp);
}

int riconosciRegione(int M[MAXN][MAXN],  int nr, int nc, int r, int c, int *b, int *h,int *area){
    int found=0;

    if (M[r][c] == 1){   //la casella è nera
        if ((r-1)<0 || M[r][c-1] == 0) { //la casella precedente (rispetto alla riga) è bianca o è un bordo
            if ((c-1)<0 || M[r-1][c] == 0){ //la casella precedente (rispetto alla colonna) è bianca o è un bordo
                /*un rettangolo è stato trovato */
                found = 1;
                for (int i = r; i < nr; i++) {
                    if (M[i][c]==1)
                        *h = *h + 1;
                    else
                        break;
                }
                for (int j = c; j < nc ; j++) {
                    if (M[r][j]==1)
                        *b = *b + 1;
                    else
                        break;
                }
                *area = *b * *h;
            }
        }
    }
    return found;
}
