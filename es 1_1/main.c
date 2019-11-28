#include <stdio.h>
#include <stdlib.h>

#define M 6
#define N 5

void loadMatrix(int tournament[N][M],FILE *fp);    //volendo avrei potuto usare una struct
int firstsquad (int tournament [N][M], int i);



int main() {
    int tournament[N][M],i=0;
    FILE *fp;

    loadMatrix(tournament,fp);
    for (int i = 0; i < M; i++) {
        printf("la capolista della giornata %d e' la squadra nella riga %d \n" ,i+1,firstsquad(tournament,i)+1);
    }
    return 0;
}

void loadMatrix(int tournament [N][M],FILE *fp){
    int i=0, j=0;

    if ((fp=fopen("campionato.txt","r"))==NULL){      //assumo che il file si chiami così
        printf("errore, file non presente\n");
        exit(1);
    }
    for (i=0; i<N ; i++){
        for (j=0; j<M ; j++){
            fscanf(fp,"%d",&tournament[i][j]);
            if (tournament[i][j] != 0 && tournament[i][j] != 1 && tournament[i][j] != 3) {
                printf("errore, dati inseriti non corretti \n");
                exit(1);
            }
        }
    }

    /*for (i=0; i<N ; i++){
        for (j=0; j<M ; j++){
            printf("%d ",tournament [i][j]);       //for testing purpose
        }
        printf("\n");
    }*/
}

int firstsquad (int tournament [N][M], int i){
    int j=0, k=0, result[2] = {0 , -1}, total = 0;
    for (int j = 0; j <N ; j++) {
        total = 0;
        for (k = 0; k <= i; k++) {
            total = total + tournament[j][k];
        }
        if (total > result[1]){
            result[1] = total;
            result[0]=j;
        }
    }
    return result [0];
}
