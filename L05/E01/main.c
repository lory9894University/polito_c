#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct amico{
    int numSong;
    char **song; //vettore di stringhe, una sequenziale all'altra (per allocare dinamicamente anche i nomi delle canzoni)
}friend;

void copy (friend* *vectSongFriends, int *nrFriends);
void playlistGenerator (friend *vectSongFriends, int nrFriend, int wichFriend, FILE* fptr, char **solution);
void playlistGeneratorWrapper(friend *vectSongFriends, int nrFriends, char **solution){
    FILE *fptr; //per poter controllare i risultati li voglio su file, non a schermo
    fptr=fopen("playlist.txt","w");
    playlistGenerator(vectSongFriends, nrFriends,0, fptr,solution);
    fclose(fptr);
}

int main() {
    friend *vectSongFriends;
    int nrFriends;
    char **solutions;

    /*copio i dati da file in memoria*/
    copy(&vectSongFriends,&nrFriends);
    solutions = (char**)malloc(nrFriends*sizeof(char *));
    for (int i = 0; i <nrFriends ; i++) {
        solutions[i]=(char *)malloc(255*sizeof(char)); //TODO meglio sovrallocare o allocare e liberare 900 volte?
    }
    /*creo le soluzioni e lw stampo*/
    playlistGeneratorWrapper(vectSongFriends,nrFriends,solutions);

    //liberazione della memoria allocata
    free(*solutions);
    free(solutions);
    for (int i = 0; i <nrFriends ; i++) {
        for (int j = 0; j <vectSongFriends[i].numSong ; j++) {
            free(vectSongFriends[i].song[j]);
        }
        free(vectSongFriends[i].song);
    }
    free(vectSongFriends);
    return 0;
}

void copy (friend **vectSongFriends, int *nrFriends){
    FILE *fPtr;
    int i,j;
    int SongsForPerson;
    char songName[255];


    if((fPtr=fopen("brani.txt","r"))==NULL){
        printf("errore, il file non è presente\n");
        exit(1);
    }
    fscanf(fPtr,"%d",nrFriends);
    (*vectSongFriends)=(friend*) malloc((*nrFriends)*sizeof(friend));
    for (i = 0; i <*nrFriends ; i++) {
        (*vectSongFriends)[i].song=(char**)malloc(*nrFriends*sizeof(char*));
        fscanf(fPtr,"%d",&SongsForPerson);
        (*vectSongFriends)[i].numSong=SongsForPerson;   //meglio una variabile in più che un indice molto brutto
        for (j = 0; j <SongsForPerson ; j++) {
            fscanf(fPtr,"%s",songName);
            (*vectSongFriends)[i].song[j]=(char*)malloc((strlen(songName)+1)* sizeof(char));
            strcpy((*vectSongFriends)[i].song[j],songName);
        }
    }
}

void playlistGenerator (friend *vectSongFriends, int nrFriend, int wichFriend, FILE * fptr, char **solution){
    /*condizione di terminazione, quando viene raggiunto l' ultimo amico la ricorsione viene esgeguita
     * ancora una volta per permettere di stampare la soluzione trovata*/
    if (wichFriend==nrFriend){
        for (int i = 0; i <nrFriend ; i++) {
            fprintf(fptr,"%s ",solution[i]);
        }
        fprintf(fptr,"\n");
        return;
    }
    for (int i = 0; i <vectSongFriends[wichFriend].numSong ; ++i) {
        /*per ogni amico viene salvata la canzone in una vettore contenente la soluzione (incompleta)
         * poi la funzione viene chiamata ricosivamente in modo da scorrere tutte le canzoni di tutti gli amici*/
        strcpy(solution[wichFriend],vectSongFriends[wichFriend].song[i]);
        playlistGenerator(vectSongFriends,nrFriend,wichFriend+1,fptr,solution);
    }
}
