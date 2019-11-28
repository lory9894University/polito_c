#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCHAR 255

/*dichiarazioni di struct ed enum*/
typedef struct corse{
    int ritardo; //uso dataN per poter trattare la data come intero
    char tratta[MAXCHAR],partenza[MAXCHAR],destinazione[MAXCHAR],dataC[MAXCHAR],ora_partenzaC[MAXCHAR],ora_arrivoC[MAXCHAR];
}automezzi;
enum comando_e {ord_data, ord_tratta,ord_partenza,ord_arrivo,s_partenza, nuovo_file, stop, error};

/*prototipi di funzioni*/
void copia(automezzi ***p_riga, automezzi ***a_riga, automezzi ***t_riga, automezzi ***d_riga,automezzi **riga, int *nr);
void ordina (automezzi **p_riga, automezzi **a_riga, automezzi **t_riga, automezzi **d_riga, int nr);
enum comando_e menu (char row[]);
int operazione (automezzi ***p_riga, automezzi ***a_riga, automezzi ***t_riga, automezzi ***d_riga,automezzi **riga, enum comando_e comando, char *row, int *nr);
void stampa (automezzi *riga[], char row[],int nr); //stampa su file o su schermo

/*funzione di swap, essendo molto corta metterla qui peggiora la leggibilità del codice?*/
void swap(automezzi *riga1[],automezzi *riga2[]){
    automezzi *swap;

    swap = *riga2;
    *riga2 = *riga1;
    *riga1 = swap;
}

int main() {

    automezzi *riga;
    automezzi **p_riga,**a_riga,**t_riga, **d_riga;
    int nr, end=0; //end rappresenta un flag per stabilire quando l'utente vuole uscire
    enum comando_e comando;
    char row [MAXCHAR];

    /*copia dei valori in memoria*/
    copia(&p_riga,&a_riga,&t_riga,&d_riga,&riga,&nr);

    /*ciclo che permette all'utente di richiedere più oomandi, finchè l'utente non scrive "fine" il loop continua*/
    while (!end) {
        comando=menu(row);
        /*funzione che a seconda di cosa ha scelto l'utente esegue un'operazione diversa*/
        end=operazione(&p_riga,&a_riga,&t_riga,&d_riga,&riga,comando,row,&nr);
    }

    return 0;
}

void copia (automezzi ***p_riga, automezzi ***a_riga, automezzi ***t_riga, automezzi ***d_riga,automezzi **riga, int *nr){
    FILE *corse;
    int i;
    char FileName[255];

    printf("inserire nome file \n");
    gets(FileName);
    /*apertura del file e controllo*/
    if ((corse=fopen(FileName,"r"))==NULL){
        printf("errore, file non trovato \n");
        return;
    }
    /*lettura del numero di righe del file*/
    fscanf(corse,"%d",nr);
    /*allocazione dinamica di nr celle di tutti quanti i vettori*/
    *riga=(automezzi *)malloc(sizeof(automezzi)*(*nr));
    *p_riga=(automezzi **)malloc(sizeof(automezzi*)*(*nr));
    *a_riga=(automezzi **)malloc(sizeof(automezzi*)*(*nr));
    *t_riga=(automezzi **)malloc(sizeof(automezzi*)*(*nr));
    *d_riga=(automezzi **)malloc(sizeof(automezzi*)*(*nr));
    /*copia delle righe del file in memoria, in un vettore di struct*/
    for (i=0; i<*nr; i++){
        fscanf(corse,"%s %s %s %s %s %s %d", (*riga)[i].tratta, (*riga)[i].partenza, (*riga)[i].destinazione, (*riga)[i].dataC, (*riga)[i].ora_partenzaC, (*riga)[i].ora_arrivoC, &(*riga)[i].ritardo);
    }
    /*creazione di 4 vettori di puntatori uguali al vettore di struct*/
    for (int i = 0; i <*nr ; i++) {
        (*d_riga)[i]=(*t_riga)[i]=(*a_riga)[i]=(*p_riga)[i]=&((*riga)[i]);
    }
    /*ordinamento in parallelo di tutti e 4 i vettori*/
    ordina(*p_riga,*a_riga,*t_riga,*d_riga,*nr);
    fclose(corse);
}

void ordina (automezzi **p_riga, automezzi **a_riga, automezzi **t_riga, automezzi **d_riga, int nr){
    int i, j;
    int max=0;

    /*insertionsort*/
    for (i = 0; i <nr ; i++) {
        max=i;
        for (j = i+1; j<nr ; j++) {
            if (strcmp(p_riga[max]->partenza, p_riga[j]->partenza) > 0) {
                max=j;
            }
        }
        if (max!=i)//giusto per evitare inutili scambi nel caso l'elemento sia già in posizione esatta
            swap(&(p_riga[max]),&(p_riga[i]));
    }

    for (i = 0; i <nr ; i++) {
        max=i;
        for (j = i+1; j<nr ; j++) {
            if (strcmp(t_riga[max]->tratta, t_riga[j]->tratta) > 0) {
                max=j;
            }
        }
        if (max!=i)
            swap(&(t_riga[max]),&(t_riga[i]));
    }

    for (int i = 0; i <nr ; i++) {
        max=i;
        for (int j = i+1; j<nr ; j++) {
            if (strcmp(a_riga[max]->destinazione, a_riga[j]->destinazione) > 0) {
                max=j;
            }
        }
        if (max!=i)
            swap(&a_riga[max],&(a_riga[i]));
    }

    for (int i = 0; i <nr ; i++) {
        max=i;
        for (int j = i; j<nr ; j++) {
            if (strcmp(d_riga[max]->dataC, d_riga[j]->dataC) > 0) {
                max =j;
            }
            if (strcmp(d_riga[max]->dataC, d_riga[j]->dataC) ==0){
                if (strcmp(d_riga[max]->ora_partenzaC, d_riga[j]->ora_partenzaC) > 0){
                    max=j;
                }
            }
        }
        if(max!=i)
            swap(&(d_riga[max]),&(d_riga[i]));
    }
}

enum comando_e menu (char row[]){
    char scelta[8]; //partenza (scelta più lunga) ha 8 caratteri

    printf("\ninserire la propria scelta, una parola tra:\n\"data\" per ordinare le corse per data,"
           "\"tratta\" per ordinare le corse per tratta\n\"partenza\" per ordinare le corse per fermata di partenza,"
           "\"arrivo\" per ordinare le corse per fermata di arrivo\n(seguiti da \"file\" se si vuole stampare su file o \"video\" per stampare a video)\n"
           "\"cerca\" per cercare le corse in una stazione (seguito dalla stazione cercata)\n"
           "\"nuovo\" per inserire un nuovo file, \"fine\" per interrompere il programma\n");

    gets(row);
    /*menù di scelte, dato che devo considerare sia l'ordinamento che il tipo di stampa (video file) salvo tutto su una stringa (row)
     * andrò poi a leggere la stringa con una sscanf per capire cosa ha inserito l'utente*/
    printf("\n");
    sscanf(row,"%s",scelta);
    if (!strcmp(scelta,"nuovo"))
        return nuovo_file;
    if(!strcmp(scelta,"data"))
        return ord_data;
    if(!strcmp(scelta,"tratta"))
        return ord_tratta;
    if(!strcmp(scelta,"partenza"))
        return ord_partenza;
    if(!strcmp(scelta,"arrivo"))
        return ord_arrivo;
    if(!strcmp(scelta,"cerca"))
        return s_partenza;
    if(!strcmp(scelta,"fine"))
        return stop;
    return error;
}

int operazione (automezzi ***p_riga, automezzi ***a_riga, automezzi ***t_riga, automezzi ***d_riga,automezzi **riga, enum comando_e comando, char *row, int *nr){
    int s_compare=1,dim_s; //la prima variabile è un flag, la seconda è la dimensione di input_station;
    char input_station[MAXCHAR];
    int i, l, r; //i contatore e punto medio del vettore durante la mia ricerca dicotomica, l ed r estremi
    switch (comando){
        case nuovo_file:
            free(*riga);
            free(*p_riga);
            free(*a_riga);
            free(*d_riga);
            free(*t_riga);
            copia(p_riga,a_riga,t_riga,d_riga,riga,nr);
            break;
        case ord_partenza:
            stampa(*p_riga,row,*nr);
            break;
        case ord_data:
            stampa(*d_riga,row,*nr);
            break;
        case ord_tratta:
            stampa(*t_riga,row,*nr);
            break;
        case ord_arrivo:
            stampa(*a_riga,row,*nr);
            break;

        case s_partenza:
            sscanf(row, "%s %s", input_station,input_station); //mi serve salvare solamente la seconda parola inserita
            dim_s=strlen(input_station);
            // il vettore è sicuramente già ordinato quindi uso una ricerca dicotomica
            l=0;
            r=*nr-1;
            /*ricerca dicotomica*/
            while(l<=r && s_compare!=0) {
                i=(l+r)/2;
                s_compare = strncmp((*p_riga)[i]->partenza, input_station,dim_s);
                if (s_compare > 0) {
                    r=i-1;
                }
                if (s_compare < 0) {
                    l=i+1;
                }
            }
            /*fine ricerca dicotomica, ora vado a controllare il caso in cui ci sono più stazioni*/
            if (s_compare==0){
                /*la specifica chiedeva di mostrare UNA tratta, presuppongo sia un errore e stampo tutte le tratte
                 * perciò scorro il vettore fino alla prima occorrenza e lo riscorro in avanti fino all'ultima stampandole*/
                for (i = i ; i>=0 ; i--) { //TODO sostituire i for con dei while
                    if (strncmp((*p_riga)[i]->partenza, input_station,dim_s)!=0)
                        break;
                }
                i++; //i viene decrementato a fine ciclo, perciò lo riporto al suo valore corretto
                for (i = i; i <*nr ; i++) {
                    if (strncmp((*p_riga)[i]->partenza, input_station,dim_s)==0) {
                        printf( "%s %s %s %s %s %s %d \n", (*p_riga)[i]->tratta,  (*p_riga)[i]->partenza, (*p_riga)[i]->destinazione, (*p_riga)[i]->dataC, (*p_riga)[i]->ora_partenzaC, (*p_riga)[i]->ora_arrivoC, (*p_riga)[i]->ritardo);
                    } else
                        break;
                }
            }
            else{
                printf("errore, stazione non presente\n");
            }
            break;

        case stop:
            return 1;

        case error:
            printf("comando non riconosciuto\n");
            break;
    }
    return 0;
}

void stampa ( automezzi *riga[],char row[], int nr){
    FILE *ordered;
    char choice[MAXCHAR];
    int i;

    sscanf(row,"%s %s", choice, choice); //mi serve salvare solo il secondo, non ha senso sprecare una variabile che non userò
    /*a seconda che l'utente voglia stampare a video o su file */
    if ((strcmp(choice,"file"))==0) {
        /*stampa su file*/
        ordered=fopen("ordinati.txt","w");
        for (i = 0; i <nr ; i++) {
            fprintf(ordered, "%s %s %s %s %s %s %d \n", riga[i]->tratta, riga[i]->partenza, riga[i]->destinazione, riga[i]->dataC, riga[i]->ora_partenzaC, riga[i]->ora_arrivoC, riga[i]->ritardo);
        }
        printf("stampa su file eseguita, il file si chiama \"ordinati.txt\"\n");
        fclose(ordered);
    }else if ((strcmp(choice,"video"))==0){
        /*stampa a video (fprintf poichè a volte printf stampava risultati strani in questo programma)*/
        for (i = 0; i <nr ; i++) {
            fprintf(stdout,"%s %s %s %s %s %s %d \n", riga[i]->tratta, riga[i]->partenza, riga[i]->destinazione, riga[i]->dataC, riga[i]->ora_partenzaC, riga[i]->ora_arrivoC, riga[i]->ritardo);
        }
    }else{
        printf("errore, secondo comando non riconosciuto, scrivere video per stampare a video e file per stampare su file\n");
    }
}