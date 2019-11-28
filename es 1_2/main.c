#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct substitute {
    char original[26];   //la parola di senso compiuto più lunga in italiano è di 26 caratteri
    char code [26];    //presuppongo che nessuno inserisca un codice con più di 24 cifre.
} substitute;

int Hotwater(substitute sub[], char word[],int* S);  /* funzione che compara le parole in source.txt con le parole in dictionary.txt, ho mantenuto quel nome perchè ero affezionato (spiegazione in fondo) */
void copy (int *S, substitute sub[]); /*funzione che copia i dati dal file alla memoria*/
void rotation (char word[], int lenght);
void substitution (int j, substitute sub[], int i,char word[], int lenght_w); /*funzione che sostituisce la parte di stringa comparata con il relativo codice*/


int main (){
	FILE	*src,*ric;
	int S=0;
	char word[200], row [200];                   //valore massimo della riga 200 caratteri, al massimo ci potrà essere una riga con dentro una sola parola
	char* token;
    substitute sub[30];      /* vettore di strutture contenete tutti i dati presenti nel file dictionary.txt*/

    /*controllo l'effettiva presenza dei file*/
	if ((src=fopen("source.txt","r"))==NULL){
			printf("errore, file non trovato \n");
			exit(1);
	}

	copy(&S, sub);

    ric=fopen("ricodificato.txt","w");

    /*lettura e comparazione del file sorgente con i dati contenuti nella memoria, più precisamente nella vettore di strutture sub[] */
	while ( ! (feof(src))){
        /*leggo una riga intera, poi uso strtok per scomporla in varie stringhe che vado ad analizzare una per volta*/
        fgets(row, 200, src);
        token = strtok(row ," ");
        while (token != NULL){      //lettura della riga, ogni singola parola avvia la funzione di comparazione Hotwater
            sscanf(token, "%s", word);
            Hotwater(sub, word, &S);
            /*finito il confronto la nuova parola viene scritta sul file */
            fprintf(ric,"%s ", word);
            token = strtok(NULL," ");
        }
        fprintf(ric,"\n");
    }


    fclose(src);
    fclose(ric);

    printf("codifica completata con successo\n");
    system("PAUSE");
    return 0;
}

void copy (int *S, substitute sub[]){    //copio i dati in memoria, sempre presupponendo una dimensione massima non specificata nel problema
    FILE *dic;
    int i=0;

    if ((dic=fopen("dictionary.txt","r"))==NULL){
        printf("errore, file non trovato \n");
        exit(1);
    }
    fscanf(dic,"%d",&*S);
    /*controllo sulla formattazione del file dictionary*/
    if (*S<0 || *S>30){
        printf("errore nel file dictionary txt, il numero di ricodifiche non è accettato dal programma\n ci devono essere al massimo 30 ricodifiche\n");
        exit(1);
    }
    /* copia dei dati del file dictionary.txt in memoria*/

	for (
	        i=0; i<*S ; i++) {
        fscanf(dic,"%s %s",sub[i].code, sub[i].original);
	}

    fclose(dic);
}

int Hotwater (substitute sub[], char word[], int* S){       //la funzione compara due parole e se trova coincidenze richiama substitution
    int lenght_w=0,i=0, j=0;
    char new_word [200];

    lenght_w= strlen(word);
    for (j=0 ; j<*S; j++){
        /*setto la stringa new_word = word, dato che la funzione rotation me la modifica*/
        strcpy(new_word,word);
        for(i=0; i<lenght_w; i++){
            if((strncmp(new_word,sub[j].original,strlen(sub[j].original)))==0){
                    substitution(j,sub,i,word, lenght_w);
                return 0;   /*la funzione ha trovato una corrispondenza, perciò ritorna al main per la scrittura*/
            }
            rotation(new_word, lenght_w);                          //riutilizzo il codice sviluppato per lab 0 esercizio 3 per creare una nuova stringa spostata a sinistra di una posizione
        }
    }
 return 3;         /*la funzione non ha trovato alcuna corrispondenza, ritorna al main con valore 3, ho scelto un valore casuale che non fosse 1 (di solito usato per gli errori)*/
}

void substitution(int j, substitute sub[], int i, char word[],int lenght_w ){
    char before[26], after[26];
    int lenght_s,k=0,c=0;
    before [0]='\0';
    after[0]='\0';

    /* lo scopo di queste istruzioni e quello di separare la stringa in 3 parti: parte prima del codice, parte da sostituire con il codice, parte dopo il codice.
    in fase di ricostruzione della stringa originaria la parte interessata, cioè sub[j].original, viene sostituitas dal codice*/
    lenght_s =  strlen(sub[j].original);
    for (k=0;k<i;k++){
        before[k]=word[k];
    }
    before[i]='\0';                        //codice molto brutto, sostituibile da una strncpy
    k=i + lenght_s;
    while (word[k] !='\0'){
        after[c]=word[k],
        c++;
        k++;
    }
     /*le 3 stringhe vengono riunite in una parola sola*/
    strcat(before,sub[j].code);
    strcat(before,after);
    strcpy(word,before);
}

void rotation(char word[], int lenght){
    int i=0;

    for (i=0; i<lenght; i++){
                    word[i]=word[i+1];
                }

}

/*Attenzione, per creare il codice ho dovuto supporre ci fossero limitazioni alla quantità di caratteri presenti su ogni riga di "dizionario.txt", condizione non presente nella consegna.
* nonostante il tempo dedicato alla ricerca di una soluzione alternativa l'unica possibilità da me trovata consisteva nella comparazione del file "sorgente.txt" con il file "dizonario.txt"
* per ogni carattere presente nel testo. la soluzione sopra esposta è stata provata ma risultava inadatta per tre motivi: 1 complessita del codice, il codice era praticamente illeggibile
* 2 necessitava la creazione di una funzione che comparasse due stringhe carattere per carattere, funzione tranquillamente sostituibile con una strncmp (ma solo se la dimensione è limitata),
* insomma si trattava di riscoprire l'acqua calda (da qui il nome della funzione che ho mantenuto) 3 risultava malamente ottimizzato, per una semplice filastrocca rileggeva il file talmente
* frequentemente da necessitare un paio di secondi per la sua esecuzione, un'applicazione in campo reale di tale programma non sarebbe per nulla efficiente.*/

/* la lettura riga per riga nella prima versione del programma era sostituito da una fscanf in modo che prendesse una parola per volta.
 * ho preferito questo metodo più complicato (fgets e strtok) poichè facilita l'individuazione di eventuali errori e perchè
 * mi permette di inserire anche i caratteri "a capo" (forse quest'ultima cosa poteva essere ottenuta anche in altro modo)*/
