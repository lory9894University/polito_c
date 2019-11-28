#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char t1Color, t2Color;
    int t1Value, t2Value;
    int used,orientation;
}card;
typedef struct{
    card *cards;
    int cardNumber;
}cardWrapper;
typedef struct{
        int r,c;
        card** *position;
        int value;
}boardtype;

void acquisition(cardWrapper *disposableCard, boardtype *board){
    FILE *fptr;
    int i;
    int orientation, cardIndex;

    if((fptr=fopen("tiles.txt","r"))==NULL){
      printf("errore, file non trovato\n");
        return;
    }
    fscanf(fptr,"%d",&disposableCard->cardNumber);
    disposableCard->cards=(card *)malloc((disposableCard->cardNumber) * sizeof(card));
    for (i=0 ; i<disposableCard->cardNumber ;i++){
        fscanf(fptr,"\n%c %d %c %d",&disposableCard->cards[i].t1Color,&disposableCard->cards[i].t1Value,&disposableCard->cards[i].t2Color,&disposableCard->cards[i].t2Value);
        disposableCard->cards[i].used=0;
        disposableCard->cards[i].orientation=1;
    }
    fclose(fptr);
    if ((fptr=fopen("board.txt","r"))==NULL){
        printf("errore,file non trovato\n");
        return;
    }
    fscanf(fptr,"%d %d",&board->r,&board->c);
    board->position=(card ***)malloc(sizeof(card**)*board->r);
    for (i = 0; i<board->r ; i++) {
        board->position[i]=(card **)malloc(sizeof(card*)* board->c);
        for (int j = 0; j < board->c; j++) {
                 fscanf(fptr,"%d/%d",&cardIndex,&orientation);
                 if (cardIndex==-1)
                     board->position[i][j]=NULL;
                 else
                    board->position[i][j]=&disposableCard->cards[cardIndex];
                 disposableCard->cards[cardIndex].orientation=orientation;
                 disposableCard->cards[cardIndex].used=1;
        }
    }
};
void combination(int k,int pos, cardWrapper *disposableCard, boardtype *board,boardtype *globalSolution);
int valueCalculation (boardtype board);
int main() {
    boardtype board,globalsolution;
    cardWrapper disposableCard;
    int i,j;

    globalsolution.value=0;
    acquisition(&disposableCard, &board);
    combination(board.r*board.c,0,&disposableCard,&board,&globalsolution);
    printf("%d",globalsolution.value);
    for (i=0;i<board.r;i++){
        for (j=0;j<board.c;j++){
            if (globalsolution.position[i][j]->orientation == 1)
                printf("orizzontal: %d vertical: %d",globalsolution.position[i][j]->t1Value,globalsolution.position[i][j]->t2Value);
            else
                printf("orizzontal: %d vertical: %d",globalsolution.position[i][j]->t2Value,globalsolution.position[i][j]->t1Value);
        }
        printf("\n");
    }
    return 0;
}
void combination(int k,int pos, cardWrapper *disposableCard, boardtype *board,boardtype *globalSolution){
    int i,r=0,c=pos;

    /*identifico la cella tramite [riga][colonna] al posto che come indice di un solo vettore*/
    for (i=0;i<pos;i++){ //todo sicuramente c'è un modo migliore
        if (c>board->r){
            r++;
            c=-board->r;
        }
    }
    if (pos>=k){
        board->value=valueCalculation(*board);
        if (globalSolution->value<board->value){
            for (i = 0; i <board->r ; i++) {
                for (int j = 0; j <board->c ; j++) {
                    globalSolution->position[i][j]=board->position[i][j];
                }
            }
            globalSolution->value=board->value;
        }
        return;
    }

    if (board->position[r][c]==NULL){
        for (i=0;i<disposableCard->cardNumber;i++) {
            if (disposableCard->cards[i].used==0) {
                disposableCard->cards[i].used = 1;
                board->position[r][c] = &disposableCard->cards[i];
                combination(k, pos + 1, disposableCard, board, globalSolution);
                disposableCard->cards[i].orientation=0;
                combination(k, pos + 1, disposableCard, board, globalSolution);
                disposableCard->cards[i].used = 0;
            }
        }
    } else{
        combination(k, pos + 1, disposableCard, board, globalSolution);
    }
}

int valueCalculation (boardtype board){
    int i,j;
    int globalValue=0,value=0;

    for (i = 0; i <board.r ; i++) { //per le righe, farlo uguale per le colonne
        for (j = 0; j <board.c ; j++) {
            if(j==0) {
                if (board.position[i][j]->orientation==0) {
                    value = board.position[i][j]->t1Value;
                } else{
                    value = board.position[i][j]->t2Value;
                }
            } else{
                if (board.position[i][j]->orientation==0) {
                    if (board.position[i][j]->t1Color!=board.position[i][j-1]->t1Color){
                        value=0;
                        break;
                    } else{
                        value+= board.position[i][j]->t1Value;
                    }

                } else{
                    if (board.position[i][j]->t2Color!=board.position[i][j-1]->t2Color){
                        value=0;
                        break;
                    } else{
                        value+=board.position[i][j]->t2Value;
                    }
                }
            }

        }
        globalValue+=value;
    }
    for (i = 0; i <board.r ; i++) { //per le colonne
        for (j = 0; j <board.c ; j++) {
            if(i==0) {
                if (board.position[i][j]->orientation==1) {
                    value = board.position[i][j]->t1Value;
                } else{
                    value = board.position[i][j]->t2Value;
                }
            } else{
                if (board.position[i][j]->orientation==1) {
                    if (board.position[i][j]->t1Color!=board.position[i-1][j]->t1Color){
                        value=0;
                        break;
                    } else{
                        value+= board.position[i][j]->t1Value;
                    }

                } else{
                    if (board.position[i][j]->t2Color!=board.position[i-1][j]->t2Color){
                        value=0;
                        break;
                    } else{
                        value+=board.position[i][j]->t2Value;
                    }
                }
            }

        }
        globalValue+=value;
    }
    return globalValue;
}