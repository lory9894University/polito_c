#include <stdio.h>
#include <string.h>
#include <ctype.h>

int CompareText ( char word[],FILE * txt);
void strlower(char word[]); //TODO salvarsela da qualche parte, questa funzione è una figata
int CompareWord(char string[],char stringContained[]);      //restituisce 1 se una stringa è contenuta nell'altra

int main() {
    FILE *sequences, *txt;
    int l,i;
    char word[25];

    /*apertura dei file con relativo controllo di presenza del file.txt */
    if ((sequences = fopen("sequenze.txt","r"))==NULL){
        printf("errore, file non trovato");
        return 1;
    }
    if ((txt = fopen("testo.txt","r"))==NULL){
        printf("errore, file non trovato");
        return 1;
    }
    /*scansione della prima riga del file sequenze.txt*/
    fscanf(sequences,"%d",&l);
    /* scansione e confronto delle successive righe del file sequenze.txt*/
    for ( i = 0; i <l ; i++) {          //costrutto sostituibile da un while (!feof(sequences))
        fscanf(sequences, "%s", word);
        /*dopo aver salvato la parola prima vado a stamparla a video e poi a confrontarla con il file testo.txt per controllare se e dove è contenuta nel testo*/
        printf("la sequenza \" %s \" e' contenuta:\n",word);
        if (CompareText(word,txt)==-1){ //CompareText restituisce -1 se la parola non viene mai trovata nel testo
            printf("0 volte nel testo \n \n");
        } else{
            printf("\n");
        }
    }

    /*chiusura dei file*/
    fclose(sequences);
    fclose(txt);
    return 0;
}

int CompareText ( char word[],FILE *txt){
    int position=-1; // così ho un bel return -1 se non c'è alcuna occorrenza
    char found[25];
    char compareSequence[25], compareTxt[25];
    /*queste due stringhe sono la semplice copia di word e di found, mi servono in quanto mi permettono di confrontare
     * le due stringhe riscritte in minuscolo senza modificare le stringhe originali (quindi senza cambiare la formattazione).
     * in questo modo la funzione non è "case sensitive"*/

    int counter=0,l,occorrenze=0;

    /* creazione della stringa ausiliaria scritta in minuscolo*/
    strcpy(compareSequence,word);
    strlower(compareSequence);
    /*lettura di tutto il testo parola per parola confrontandolo con la parola (word) copiata in memoria*/
    while (! feof(txt) && occorrenze<10) { //TODO, chiedere se serve il occorrenze <10
        fscanf(txt, "%s", found);

        l=strlen(found);
        if (ispunct(found[l-1])) //in questo modo la funzione non stampa i segni di punteggiatura, a meno che
            found[l-1]='\0';    //non siano all'interno della parola (ad esempio le abbreviazioni)

        /* creazione della stringa ausiliaria scritta in minuscolo*/
        strcpy(compareTxt,found);
        strlower(compareTxt);
        counter++;
        if (CompareWord(compareTxt,compareSequence)) { //compare le due stringhe
            position=counter;       //stabilisce la posizione in cui si trova la parola
            printf("in \"%s\", in posizione %d \n", found, position);
            occorrenze++;
        }
    }
    rewind(txt);
    return position;
}

int CompareWord(char string[], char stringContained[]){       //sostituibile da una strstr
    int l,flag;

    l=strlen(stringContained);
    /*confonta la stringa di "sequenze.txt" con i primi l caratteri dell'altra stringa se non viene rilevato
    * alcun riscontro parte a confrontare dal carattere successivo (fino al carattere finale)*/
    for (unsigned i = 0; string[i] != '\0' ; i++) {
        flag=1;             //
        for (unsigned j = 0; j <l ; j++) {
            if (string[i+j]==stringContained[j]) {
                flag = 0;
            }
            else{
                flag=1;
                break;
            }
        }
        if (flag==0){
            return 1;
        }
    }
    return 0;
}

void strlower(char word[]) { //trasforma tutta la stringa in una stringa equivalente ma scritta in minuscolo
    int i;
    for (i = 0; word[i] != '\0'; i++) {
        word[i] = tolower(word[i]);
    }
}
