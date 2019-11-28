#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCHAR 30


typedef struct automezzi{
    int dataN ,ritardo; //uso dataN per poter trattare la data come intero
    char tratta[MAXCHAR],partenza[MAXCHAR],destinazione[MAXCHAR],dataC[MAXCHAR],ora_partenzaC[MAXCHAR],ora_arrivoC[MAXCHAR];
}automezzi;

enum comando_e { r_date = 0,r_partenza,r_capolinea,r_ritardo,r_ritardo_tot,r_fine,r_errore};
void stampa (automezzi riga);
void copia(automezzi riga[], int *nr);
void selezionaDati(automezzi riga[], int nr, enum comando_e comando, char row[]);
int DateToInt(char data[]); //nome inglese poichè presa da una libreria a cui sto lavorando //TODO altra funzione da salvare nella mia libreria
enum comando_e scelta (char row[]);

int main() {
    automezzi riga[1000];
    int nr;
    enum comando_e comando;
    char row [MAXCHAR];

    copia(riga,&nr);
    do{
        comando=scelta(row);
        selezionaDati(riga,nr,comando,row);
    } while(comando!=r_fine);
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
        riga[i].dataN= DateToInt(riga[i].dataC);
    }

    fclose(corse);
}

enum comando_e scelta (char row[]){
    enum comando_e comando;
    char scelta[12]; //ritado_tot (scelta più lunga) ha 12 caratteri

    printf("\ninserire la propria scelta: una parola tra \"date\", \"partenza\",\n"
           "\"capolinea\", \"ritardo\", \"ritardo_tot\" e \"fine\", eventualmente seguita sulla stessa riga da altre\n"
           "informazioni, ad esempio due date per \"date\", una fermata di partenza per \"partenza\", una fermata di arrivo per \"capolinea\"\n"
           "due date per \"ritardo\" ed un codice tratta per \"ritardo_tot\" \ninserire le date nel formato aaaa/mm/gg\n");

    gets(row);
    printf("\n");
    sscanf(row,"%s",scelta);
    if(!strcmp(scelta,"partenza"))
        return r_partenza;
    if(!strcmp(scelta,"date"))
        return r_date;
    if(!strcmp(scelta,"capolinea"))
        return r_capolinea;
    if(!strcmp(scelta,"ritardo"))
        return r_ritardo;
    if(!strcmp(scelta,"ritardo_tot"))
        return r_ritardo_tot;
    if(!strcmp(scelta,"fine"))
        return r_fine;
    return r_errore;
}

void selezionaDati(automezzi riga[], int nr, enum comando_e comando,char row[]){  //qui lo switch avente come default: comando errato e come case 'r_fine' solamente un break;
    int i,temp, ritardo =0;
    char data1[MAXCHAR],data2[MAXCHAR];      //le date viste come stringhe
    int dataN1,dataN2;     //le date ma come interi
    char genericString[MAXCHAR]; //stringa valida per partenza e destinazione
    char trash [MAXCHAR],codice[MAXCHAR]; //stringa che contiene la scelta fatta nella funzione scelta, ho deciso di darle un nome diverso per evitare ulteriore confusione //codice si riferisce al codice di tratta
    int flag=1; //per stabilire se sono state trovate corrispondenze

    switch (comando){
        case r_fine:
            break;

        case r_date:
            sscanf(row,"%s %s %s",trash, data1,data2);
            dataN1=DateToInt(data1);
            dataN2=DateToInt(data2);
            if (dataN1>dataN2){
                temp=dataN1;
                dataN1=dataN2;
                dataN2=temp;
            }
            for (i = 0; i <nr ; i++) {
                if (riga[i].dataN <= dataN2 && riga[i].dataN >= dataN1){
                    stampa(riga[i]);
                    flag=0;
                }
            }
            if (flag)
                printf("nessuna corsa trovata\n");
            break;
        case r_partenza:
            sscanf(row,"%s %s",trash, genericString);
            printf("le seguenti corse partono da %s:\n",genericString);
            for (i = 0; i <nr ; i++) {
                if (!strcmp(genericString,riga[i].partenza)){
                    stampa(riga[i]);
                    flag=0;
                }
                if (flag)
                    printf("nessuna corsa trovata\n");
            }
            break;
        case r_capolinea:
            sscanf(row,"%s %s",trash, genericString);
            printf("le seguenti corse fermano a %s:\n",genericString);
            for (i = 0; i <nr ; i++) {
                if (!strcmp(genericString,riga[i].destinazione)){
                    stampa(riga[i]);
                    flag=0;
                }
            }
            if (flag)
                printf("nessuna corsa trovata\n");
            break;
        case r_ritardo:
            sscanf(row,"%s %s %s",trash, data1,data2);
            dataN1=DateToInt(data1);
            dataN2=DateToInt(data2);
            if (dataN1>dataN2){
                temp=dataN1;
                dataN1=dataN2;
                dataN2=temp;
            }
            for (i = 0; i <nr ; i++) {
                if (riga[i].dataN <= dataN2 && riga[i].dataN >= dataN1 && riga[i].ritardo!=0){
                    stampa(riga[i]);
                    flag=0;
                }
            }
            if (flag)
                printf("nessuna corsa trovata\n");
            break;
        case r_ritardo_tot:
            sscanf(row,"%s %s", trash, codice);
            for (i = 0; i < nr; i++) {
                if (!strcmp(riga[i].tratta,codice)){
                    ritardo = ritardo + riga[i].ritardo;
                    flag=0;
                }
            }
            if (flag)
                printf("nessuna corsa trovata\n");
            else
                printf("il ritardo totale accumulato da questa linea e' di %d minuti\n",ritardo);
            break;
        case r_errore:
            printf("errore, comando non riconosciuto\n");
            break;
    }
    printf("\n\n");

}

int DateToInt(char data[]){
    int giorno, mese, anno;
    int dataNumerica;

    sscanf(data,"%d/%d/%d",&anno, &mese,&giorno);     //modifica alla funzione originale
    dataNumerica = (anno*10000) + (mese*100) + giorno;
    return dataNumerica;
}

void stampa ( automezzi riga){
    printf("%d %s %s %s %s %s %d \n", riga.tratta, riga.partenza, riga.destinazione, riga.dataC, riga.ora_partenzaC, riga.ora_arrivoC, riga.ritardo);
}
