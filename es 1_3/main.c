#include <stdio.h>
#define n 5
#define Mc 100

void ruotar (int v[n][n], int N, int index, int P, int dir);
void ruotac (int v[n][n], int N, int index ,int P, int dir);

int main() {
    int matrix [n][n], index, P,nr, nc, i, j, dir; //TODO dir non mi ricordo come l'ho chiamato nella function
    FILE *fp;
    char selector [Mc], direction [Mc];
    int flag=0;
    char filename [Mc];

    printf("inserire nome file \n");
    scanf("%c", filename);
    if ((fp = fopen(filename,"r"))==NULL){
        printf("errore, il nome del file non è corretto \n");
        return 1;
    }
    while (! feof(fp)){
        fscanf(fp,"%d %d",&nr, &nc);
        for (i=0; i<nr ; i++){
            for (j=0 ; j<nc; j++){
                fscanf(fp, "%d", &matrix[i][j]);
            }

        }
    }
    printf("inserire il selettore, l'indice, la direzione ed il numero di posizioni di cui si vuole rurotare la matrice \n");
    while (flag !=1 ){   //TODO magari farne una function, oppure mettere un'altro while attorno
        scanf("%s %d %s %d",selector,& index, direction, & P);
        if (selector == "fine")
            flag = 1;
        else {
            if ((direction == "destra" || direction == "sinistra") && selector == "riga") {//TODO sostituire con strcmp
                if (direction == "destra")
                    dir = -1;
                else
                    dir =1;
                ruotar(matrix,nr,index,P,dir);
            }
            else if ((direction == "giu" || direction == "su") && selector == "colonna"){
                if (direction == "giu")
                    dir = -1;
                else
                    dir = 1;
                ruotac(matrix,nc,index,P,dir);
            }
        }
    }
    fclose(fp);

    return 0;
}

void ruotar (int v[n][n], int N, int index, int P, int dir){
    int swap=0, i=0, j=0;

    for (i = 0; i < P; i++) {          //ripeti P volte il seguente codice
            if (dir == -1) {   //rotazione a destra
                swap = v[index][N - 1];
                for (j = N - 1; j > 0; j--) {
                    v[index][j] = v[index][j - 1];
                }
                v[index][0] = swap;
            } else {
                swap = v[index][0];
                for (j = 0; j < N - 1; j++) {
                    v[index][j] = v[index][j + 1];
                }
                v[index][N - 1] = swap;
            }
    }
}

void ruotac (int v[n][n], int N, int index, int P, int dir){
    int swap=0, i=0, j=0;

    for (i = 0; i < P; i++) {          //ripeti P volte il seguente codice
       if (dir == -1) {   //rotazione giù
           swap = v [N - 1] [index];
           for (j = N - 1; j > 0; j--) {
                v[j][index] = v[j - 1][index];
           }
             v[0] [index]= swap;
       } else {
          swap = v[0][index];
            for (j = 0; j < N - 1; j++) {
                v[j][index] = v[j + 1][index];
             }
            v[N - 1][index] = swap;
       }
    }

}