#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXCHAR 100

char* cercaRegexp (char *src, char *regex);
char* findUppercase (char **src, char * meta, int upper);
int makeMeta (char *meta, char *regex, int i);

int main() { /*TODO main da cancellare, vogliono solo la funzione*/
    char src[MAXCHAR], regexp[MAXCHAR];
    char *regexptr;
    FILE* fpt;

    fpt=fopen("source.txt","r");
    fgets(src,100,fpt);
    printf("inserire regex\n");
    scanf("%s",regexp);
    regexptr=cercaRegexp(src,regexp);
    if (regexptr!=NULL)
        printf("%s",regexptr);
    else
        printf("nessuna occorrenza della rexeg trovata");
    fclose(fpt);
    return 0;
}
char* cercaRegexp (char *src, char *regex) {
    int i = 0, j, first_correspondance= 0, meta_lenght, correspond=0;
    char meta[26];
    char *regexptr=NULL;

    /*il confronto con regex viene ripetuto fintanto che tutta src non è stata fatta scorrere, utilizzo il termine scorrere
     * in quanto non viene spostato un indice ma il puntatore in memoria (perciò while (*src) e non src[i])*/
    while (*src != '\0' && correspond==0) {
        /*il flag delle corrispondenze "correspond" è settato ad 1, se questo valore non viene cambiato significa che
         * per ogni*/
        correspond=1;
        /* l'idea alla base del programma e di scorrere*/
        while (regex[i] != '\0') {
            /*mi salvo il valore di i, mi servirà per controllare se prima dello switch, il valore era zero*/
            first_correspondance = i;
            switch (regex[i]) {
                case '.': //TODO maybe salvarlo in un'altra func
                    i++; //escludo dalla copia la cella contenente "."
                    i = makeMeta(meta, regex, i);
                    meta_lenght = strlen(meta);
                    while (src[meta_lenght - 1] != '\0') {
                        if (strncmp(meta, src, meta_lenght) == 0) { //trovata corrispondenza della regex
                            if (first_correspondance==0) //se è il primo metacarattere della regex devo salvarmi il puntatore alla prima occorrenza nella stringa
                                regexptr = src;
                            /*se invece non è il primo metacarattere, non devo salvarmelo perchè è già stato salvato*/
                            break;
                        }
                        src++;
                    }
                    if (regexptr != src) {
                        /*nessuna corrispondenza con la regex trovata*/
                        correspond = 0;
                    }
                    break;

                case '\\':
                    /*escludo dalla copia la cella i contenente \*/
                    i++;
                    if (regex[i] == 'A') {
                        /*escludo dalla copia la cella i contenente A*/
                        i=makeMeta(meta, regex, i);
                        /*se il metacarattere corrisponde continuo la ricerca per tutta la regex, altrimenti esco
                         * non ho necessità di passare al metacarattere successivo, ciò avviene gia quando finisce il ciclo for*/
                        if ((findUppercase(&src, meta, 1)) == NULL) {
                           if (regexptr != src) {
                                correspond = 0;
                            }
                        }
                        if (first_correspondance==0)
                            regexptr = src;

                    } else if (regex[i] == 'a') {
                        /*escludo dalla copia la cella i contenente a*/
                        i++;
                        i=makeMeta(meta, regex, i);
                        if ((findUppercase(&src, meta, 0)) == NULL) {
                            correspond=0;
                        }
                        if (first_correspondance==0)
                            regexptr = src;
                    } else {
                        if (regexptr != src) {
                            correspond = 0;
                        }
                    }
                    break;
                case '[':
                    i++;
                    if (regex[i] == '^') {
                        i+2; //escludo dal makeMeta ^]
                        i=makeMeta(meta, regex, i);
                        while (*src!= '\0') {
                            if (regex[i-2]!=*src) {
                                if (strncmp(meta, src, meta_lenght) != 0) {
                                    if (first_correspondance == 0)
                                        regexptr = src;
                                    break;
                                }
                                src++;
                            }
                        }
                    } else {
                        for (j = i; regex[j]!=']' ; j++){}  //conta quanti caratteri separano dalla ]
                        i=i+j;
                        i=makeMeta(meta,regex,i);
                        for ( j = i; regex[j]!=']' ; j++) { //TODO, purtroppo non posso usare la mia makemeta. inventati qualcosa
                            while (*src != '\0') {
                                if (strncmp(meta, src, meta_lenght) == 0) {
                                    if (first_correspondance==0)
                                        regexptr = src;
                                    break;
                                }
                                src++;
                            }
                            if (regexptr == src) { //appena uno dei caratteri soddisfa le condizioni della regex non è necessario continuare
                                break;
                            }
                        }
                    }
                    if (regexptr != src) {
                        correspond = 0;
                    }
                    break;

                default:
                    return NULL;

            }
        }
        if (correspond==0) {
            i = 0;
            regexptr=NULL;
        }
        }
        return regexptr; //TODO, devo farmi passare la posizione del primo meta corrispondente (un flag che mi dice se il meta trovato è il primo)
    }

char* findUppercase (char **src, char * meta, int upper){
    int meta_lenght;

    meta_lenght=strlen(meta);
    if (upper){
        while (**src!='\0'){ //evitiamo sigsev per piacere
            if (isupper(**src)){ //ricordo che nella mia variabile meta non ho salvato \A,
                *src=*src + 1;
                if (strncmp(*src,meta,meta_lenght)==0)
                    return *src;
            }else
                *src= *src+ 1; /* mi serve che in qualunque caso il puntatore venga incrementato
                * ammetto che è un escamotage un po' brutto */
        }

    } else{
        while (**src!='\0'){
            if (islower(**src)){
                *src=*src + 1;
                if (strncmp(*src,meta,meta_lenght)==0)
                    return *src;
            } else
                *src= *src + 1;
        }
    }
    return NULL;
}

int makeMeta ( char *meta, char *regex, int i) {
    int j;

    /*salvo in una varaiabile meta il metacarattere trovato (con relativi caratteri alfabetici)
    * e incremento i di tante posizioni quanti sono i caratteri alfabetici
    * appena trovo il metacarattere successivo so di aver finito i caratteri alfabetici*/
    for (j = 0; regex[i] != '.' && regex[i] != '[' && regex[i] != ']' && regex[i] != '\\' && regex[i] != '\0'; j++) {
        meta[j] = regex[i];
        i++;
    }
    /*inserisco il terminatore di stringa, in modo che il mio vettore contenente i caratteri alfabetici
    * successivi al metacarattere sia utilizzabile come stringa*/
    meta[j] = '\0';
    return i; //in questo modo la regex non riparte da prima dei caratteri alfabetici ma dalla metacarattere successivo
}