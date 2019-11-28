#include <stdio.h>
#include <stdlib.h>

int **malloc2dr(int *nc,int *nr);
void malloc2dp(int ***mat,int *nc,int *nr);
void separa(int **mat, int nr, int nc, int **black, int **white,int dimBlack,int dimWhite );
void freeAll (int ***mat, int **black, int **white, int nr, int nc);

void printVector(int *vector, int dim){ //funzione di stampa
    printf("{");
    for (int i = 0; i <dim ; i++) {
        printf("%d", vector[i]);
        if (i!=dim-1)
            printf(", ");
    }
    printf("}\n");
}

int main() {
    int **mat;
    int nc,nr;
    int *black, *white, dimBlack, dimWhite;

    /*funzioni di allocazione e copia in memoria dei dati*/
    mat=malloc2dr(&nc,&nr);
    //malloc2dp(&mat,&nr,&nc); //lascio la funzione commentata per comodità nello scambiarle

    /*studio la parità di righe e colonne*/
   if (nr%2!=0 && nc%2!=0){
       /*se entrambe sono dispari uno dei due vettori avrà un elemento in più*/
       dimBlack=(nr*nc)/2;
       dimWhite=dimBlack+1;
   } else //alemno una è pari quindi hanno lo stesso numero di elementi
       dimBlack=dimWhite=(nr*nc)/2;

   /*funzione che si occupa dell'allocazione dei due vettori e della copia dei dati negli stessi*/
    separa(mat,nr,nc,&black,&white,dimBlack,dimWhite);

    printf("\nvettore elementi neri: \n");
    printVector(black,dimBlack);
    printf("\nvettore elementi bianchi: \n");
    printVector(white,dimWhite);
    freeAll(&mat,&black,&white,nr,nc);

    return 0;
}

int **malloc2dr(int *nc,int *nr){
    FILE *fPtr;
    int **mat;

    /*apertura e controllo del file*/
    if((fPtr=fopen("matrix.txt","r"))==NULL){
        printf("errore, il file non e' presente\n");
        exit(1);
    }
    /*lettura di numero righe e numero colonne*/
    fscanf(fPtr,"%d %d",nr,nc);
    /*allocazione del vettore di puntatori (righe)*/
    mat=(int **)malloc((*nr) * sizeof(int*));
    /*allocazione dei vettore contenenti dati(colonne)*/
    for (int i = 0; i <*nr ; i++) {
        mat[i]=(int*)malloc((*nc)* sizeof(int));
        /*copia dei dati nella matrice appena allocata*/
        for (int j = 0; j <*nc ; j++) {
            fscanf(fPtr,"%d", &(mat[i][j]));
        }
    }
    fclose(fPtr);
    return mat;
}

void malloc2dp(int ***mat,int *nc,int *nr){ //non commentata poichè uguale alla precedente
    FILE *fPtr;

    if((fPtr=fopen("matrix.txt","r"))==NULL){
        printf("errore, il file non e' presente\n");
        exit(1);
    }
    fscanf(fPtr,"%d %d",nr,nc);
    *mat=(int **)malloc(*nr * sizeof(int*));
    for (int i = 0; i <*nr ; i++) {
        *(mat[i])=(int*)malloc(*nc * sizeof(int));
        for (int j = 0; j <*nc ; j++) {
            fscanf(fPtr,"%d", mat[i][j]);
        }
    }
    fclose(fPtr);
}

void separa(int **mat, int nr, int nc, int ** black, int **white, int dimBlack, int dimWhite){
    int flag=0, counterBlack=0, counterWhite=0;

    /*allocazione dei vettori black e white*/
    *black=(int *) malloc(sizeof(int)* dimBlack);
    *white=(int *) malloc(sizeof(int)* dimWhite);
    /*copia dei dati dalla matrice ai vettori (alternativamente white e black)*/
    for (int i = 0; i <nr ; i++) {  //TODO guardare size_t
        for (int j = 0; j <nc ; j++) {
            if(flag){
                (*white)[counterWhite]=mat[i][j];
                flag=0;
                counterWhite++;
            }else{ //dato che black potrebbe avere un elemento in più meglio farlo partire per primo
                (*black)[counterBlack]=mat[i][j];
                flag=1;
                counterBlack++;
            }
        }

    }
}

void freeAll (int ***mat, int **black, int **white, int nr, int nc){
    /*free di tutti i vettori allocati*/
    for (int i = 0; i <nr ; i++) {
        for (int j = 0; j <nc ; j++) {
            free((*mat)[j]);
        }
        free(*mat);
    }
    free(*black);
    free(*white);
}
