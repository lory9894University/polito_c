#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCHAR 30


typedef struct automezzi{
    int ritardo; //uso dataN per poter trattare la data come intero
    char tratta[MAXCHAR],partenza[MAXCHAR],destinazione[MAXCHAR],dataC[MAXCHAR],ora_partenzaC[MAXCHAR],ora_arrivoC[MAXCHAR];
}automezzi;

enum comando_e { c_stampa = 0,ord_data, ord_tratta,ord_partenza,ord_arrivo,s_partenza, stop, error};
void stampa (automezzi riga, int p_file,FILE *ordered); //stampa su file o su schermo
int operazione (automezzi *p_riga[], enum comando_e comando, char *row, int nr, int* state);
void copia(automezzi riga[], int *nr);
enum comando_e menu (char row[]);
void ordina (enum comando_e comando, automezzi *p_riga[], int nr, int *state);
void swap(automezzi *p_riga[],automezzi *riga[]);

int main() {
    automezzi riga[1000];
    automezzi *p_riga[1000];
    int nr, end=0, state=0; //end rappresenta un flag per stabilire quando l'utente vuole uscire, state rappresenta se l'algoritmo è ordinato per partenza (cartteristica necessaria alla ricerca)
    enum comando_e comando;
    char row [MAXCHAR];

    copia(riga,&nr);
    for (int i = 0; i <nr ; i++) {
        p_riga[i]=&riga[i];
    }
    while (!end) {
        comando=menu(row);
        end=operazione(p_riga,comando,row,nr,&state);
    }
    return 0;
}

void copia (automezzi riga [], int *nr){
    FILE *corse;
    int i;

    if ((corse=fopen("corse.txt","r"))==NULL){
        printf("errore, file non trovato \n");
        exit(1);
    }
    fscanf(corse,"%d",&*nr);
    for (i=0; i<*nr; i++){
        fscanf(corse,"%s %s %s %s %s %s %d", riga[i].tratta, riga[i].partenza, riga[i].destinazione, riga[i].dataC, riga[i].ora_partenzaC, riga[i].ora_arrivoC, &riga[i].ritardo);
    }

    fclose(corse);
}

void stampa ( automezzi riga, int p_file, FILE *ordered){

    if (p_file) {
        fprintf(ordered,"%s %s %s %s %s %s %d \n", riga.tratta, riga.partenza, riga.destinazione, riga.dataC, riga.ora_partenzaC, riga.ora_arrivoC, riga.ritardo);
    }else{
        fprintf(stdout,"%s %s %s %s %s %s %d \n", riga.tratta, riga.partenza, riga.destinazione, riga.dataC, riga.ora_partenzaC, riga.ora_arrivoC, riga.ritardo);
    }
}

enum comando_e menu (char row[]){
    enum comando_e comando;
    char scelta[8]; //partenza (scelta più lunga) ha 8 caratteri

    printf("\ninserire la propria scelta: una parola tra:\n\"stampa\" (seguito da \"file\""
           " se si vuole stampare su file o \"video\" per stampare a video).\n\"data\" per ordinare le corse per data,"
           "\"tratta\" per ordinare le corse per tratta\n\"partenza\" per ordinare le corse per fermata di partenza,"
           "\"arrivo\" per ordinare le corse per fermata di arrivo\n\"cerca\" per cercare le corse in una stazione (seguito dalla stazione cercata)\n"
           "\"fine\" per interrompere il programma\n");

    gets(row);
    printf("\n");
    sscanf(row,"%s",scelta);
    if(!strcmp(scelta,"stampa"))
        return c_stampa;
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

int operazione (automezzi *p_riga[], enum comando_e comando, char *row, int nr, int *state){
    int p_file, s_compare=1,dim_s; //le prime due variabli sono flag, la terza è la dimensione di generic_s;
    char trash[8], generic_s[MAXCHAR]; //stringa di vario uso (risparmio memoria così)
    int i; //i contatore della mia ricerca dicotomica,
    FILE *ordered;

    switch (comando){
        case c_stampa:
            sscanf(row, "%s %s", trash,generic_s);
            if (strcmp(generic_s,"file")==0) {
                p_file = 1;
                /*apro il file in questa funzione in modo da non doverlo aprire nel main
                 * (risparmio l'apertura in caso non sia necessaria)*/
                if ((ordered=fopen("out_page.txt","w"))==NULL) {
                    /*nel caso l'utente tenti di stampare su un file in una cartella
                     * protetta da password o una cartella di sistema*/
                    printf("impossibile creare il file \n");
                    exit(1);
                }
            }
            else if (strcmp(generic_s,"video")==0)
                p_file=0;
            else {
                printf("errore, inserire \"file\" se si vuole stampare su file o \"video\" per stampare a video\n");
                break;
            }
            for (i = 0; i <nr ; i++) {
                stampa(*p_riga[i], p_file, ordered);
            }
            if (p_file){
                fclose(ordered);
            }
            break;
        /*il caso degli ordinamenti viene trattato in un'altra funzione per favorire la modularità*/
        case ord_partenza:
            ordina(comando,p_riga,nr,state);
            break;
        case ord_data:
            ordina(comando,p_riga,nr,state);
            break;
        case ord_tratta:
            ordina(comando,p_riga,nr,state);
            break;
        case ord_arrivo:
            ordina(comando,p_riga,nr,state);
            break;

        case s_partenza: //todo, questa ricerca dicotomica non funziona
            sscanf(row, "%s %s", trash,generic_s);
            dim_s=strlen(generic_s);
            p_file=0; //in questo modo la funzione stampa stampa a video
            if (*state) {
                i=0;

                while(s_compare!=0 && ) {
                    s_compare = strncmp(p_riga[i]->partenza, generic_s,dim_s);
                    if (s_compare > 0) {
                       i++;
                    }
                    if (s_compare < 0) {
                        f--;
                    }
                }
                if (s_compare==0){
                    /*TODO la specifica chiedeva di mostrare UNA tratta, presuppongo sia un errore e stampo tutte le tratte
                     * perciò scorro il vettore fino alla prima occorrenza, lo riscorro in avanti fino all'ultima stampandole*/
                    for (i = i ; i>=0 ; i--) {
                        if (strncmp(p_riga[i]->partenza, generic_s,dim_s)!=0)
                            break;
                    }
                    i++; //i viene decrementato a fine ciclo, perciò lo riporto al suo valore corretto
                    for (i = i; i <nr ; i++) {
                        if (strncmp(p_riga[i]->partenza, generic_s,dim_s)==0) {
                            stampa(*p_riga[i], p_file, ordered);
                        } else
                            break;
                    }
                }
                else{
                    printf("errore, stazione non presente\n");
                }
            }else{
                for (i = 0; i < nr; i++) {
                    if (strncmp(p_riga[i]->partenza, generic_s,dim_s)==0)
                        stampa(*p_riga[i], p_file, ordered);

                }
            }
            break;

        case stop:
            return 1;

        case error:
            break;
    }
    return 0;
}

void ordina (enum comando_e comando, automezzi *p_riga[], int nr, int *state){
    int i;
    int max;

    switch (comando){
        case ord_partenza:
            /*insertionsort, nei "case" seguenti non è commentato;
             * non sono riuscito a scriverlo in una funzion a se, altrimenti avrei usato il mergesort
             * approfondimento a fondo programma*/
            for(i = 0; i < nr-1; i++){
                max=i;
                for (int j = i; j <nr -1; j++) {
                    if (strcmp(p_riga[max]->partenza, p_riga[j]->partenza) > 0) {
                        max=j;
                    }
                }
                swap(&p_riga[max], &p_riga[i]);
            }
            *state=1;
            break;

        case ord_arrivo:
            for(i = 0; i < nr-1; i++){
                max=i;
                for (int j = nr-1; j > i; j++) {
                    if (strcmp(p_riga[max]->destinazione, p_riga[j]->destinazione) > 0) {
                        max=j;
                    }
                }
                swap(&p_riga[max], &p_riga[i]);
            }
            *state=0;
            break;

        case ord_tratta:
            for(i = 0; i < nr-1; i++){
                for (int j = nr-1; j > i; j--) {
                    if (strcmp(p_riga[j]->tratta, p_riga[j - 1]->tratta) > 0) {
                        swap(&p_riga[j], &p_riga[j - 1]);
                    }
                }
            }
            *state=0;
            break;

        case ord_data:
            for(i = 0; i < nr-1; i++){
                for (int j = nr-1; j > i; j--) {
                    if (strcmp(p_riga[j]->dataC, p_riga[j - 1]->dataC) < 1) {
                        swap(&p_riga[j], &p_riga[j - 1]);
                    }
                    if (strcmp(p_riga[j]->dataC, p_riga[j - 1]->dataC) ==0){
                        if (strcmp(p_riga[j]->ora_partenzaC, p_riga[j - 1]->ora_partenzaC) < 0)
                            swap(&p_riga[j], &p_riga[j - 1]);
                    }
                }
            }
            *state=0;
            break;
    }
}

void swap(automezzi *p_riga[],automezzi *riga[]){
    automezzi* swap;

    swap = *p_riga;
    *p_riga=*riga;
    *riga=swap;
}


/*avrei voluto ordinare i vettori tramite un mergesort, ma ai campi di una struct non si può accedere in modo parametrizzato
 * avrei dovuto perciò scrivere 4 mergesort diversi, certamente diminuendo la complessità dell'algoritmo ma rendendo
 * troppo confuso il codice, in favore di una migliore leggibilità ho preferito una maggiore complessità
 * (che già il codice è bruttissimo)*/