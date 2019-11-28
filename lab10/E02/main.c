#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct movement_t{
    char name[100];
    int type,inDir,outDir,notStart,ending,difficulty;
    float grade;
}stunt; //si lo so che la traduzione di acrobazia è pessima, non avevo fantasia
typedef struct movementWrapper{
    struct movement_t *moves;
    int movesNr;

}movements;
void acquisition(stunt **moves,int *lineNr){
    FILE *fPtr;
    
    if ((fPtr=fopen("elementi.txt","r"))==NULL){
        printf("errore, file non trovato\n");
        exit(1);
    }
    fscanf(fPtr,"%d",lineNr);
    *moves=malloc(sizeof(stunt) * *lineNr);
    for (int i = 0; i <*lineNr ; i++) {
        fscanf(fPtr,"%s %d %d %d %d %d %f %d",(*moves)[i].name,&(*moves)[i].type,&(*moves)[i].inDir,&(*moves)[i].outDir,&(*moves)[i].notStart,&(*moves)[i].ending,&(*moves)[i].grade,&(*moves)[i].difficulty);

    }
}
int canEnter(stunt move1,stunt move2){
    if (move1.outDir==move2.outDir)
        return 1;
    else
        return 0;
}
void forceExit(){
    printf("errore, impossibile le 3 diagonali\n");
    exit(1);
}
void prioritySet(stunt move,int *front, int *back, int *acrobatic);
movements* diagCreation(movements possibleMoves,int DD, int DP);
void copyMovement(stunt *moveTo,stunt *moveFrom);

int main() {
    movements possibleMoves;
    int DD=10,DP=20;
    acquisition(&(possibleMoves.moves),&possibleMoves.movesNr);
    if (DP==0 && DD==0) {  //TODO testing purpose
        printf("inserire di seguito DD e DP separati da uno spazio");
        scanf("%d %d", &DD, &DP);
    }
    /*for (int i = 0; i <possibleMoves.movesNr ; i++) {
        printf("%s %d %d %d %d %d %.2f %d\n",possibleMoves.moves[i].name,possibleMoves.moves[i].type,possibleMoves.moves[i].inDir,possibleMoves.moves[i].outDir,possibleMoves.moves[i].notStart,possibleMoves.moves[i].ending,possibleMoves.moves[i].grade,possibleMoves.moves[i].difficulty);

    }*/


    return 0;
}
void prioritySet(stunt move,int *front, int *back, int *acrobatic){
    if (move.type==2){
        *acrobatic=1;
        *front=1;
    }
    if (move.type==1){
        *acrobatic=1;
        *back=1;
    }
}

movements* diagCreation(movements possibleMoves,int DD, int DP){
    char diagonals[3][5][500]; //tre diagonali di 5 movimenti max composti da 100 caratteri
    int frontput=0, backPut=0, acrobaticElement=0; //ogni diagonale deve settare questo flag a 1 (va risettato a zero per ogni nuova diagonale)
    int i,found=0, localDD,localDP;
    int inSequence=0; // la prima diagonale conterrà due elementi in sequenza, poi il flag sarà settato ad 1 e dimenticato
    stunt *tempMove; //puntatore ad un movimento che potrebbe essere accettato
    //todo, questo flag può ben essere eliminato se faccio un for x ogni diagonale
    for (i = 0; i <possibleMoves.movesNr ; i++) {

    }

    for (i = 0; i <3 ; ++i) {
        for (int k = 0; k <5 ; k++) {
            for (int j = 0; j < possibleMoves.movesNr; j++) { //start
                found = 0;
                if (!possibleMoves.moves[j].notStart) {
                    found=1;
                }
                if (!found)
                    forceExit();
            }
            if (k==4){
                for (int j = 0; j < possibleMoves.movesNr; j++) { //start
                    found = 0;
                    if (possibleMoves.moves[j].ending || localDD<=DD) {
                        found=1;
                        strcpy(diagonals[i][j],possibleMoves.moves->name);
                    }
                    if (!found)
                        forceExit();
                }
            }
        }

    }

    return diagonals;
}

