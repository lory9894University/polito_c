#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#define MAXCHAR 50

typedef struct person* link;
struct person{
    int cap, numericDate;
    char *code;
    char *name, *surname, *address,*city, *date; //possibile allocarli dinamicamente strdup

    link next;
};
typedef enum command_e{acquisition=0, search, delete, print_usr, end, error,showhelp,nodata} command;

void copysize(link x, char *code,char *name, char *surname, char *address, char *city, char *date, int cap);
command menu (char insertion[], link menu);
void operation(command menuChoice, char stringInserted[], link *head);
void newPerson (link *head, FILE *fPtr);
link searchElement (link head, char stringToCompare[], char finalDate[]);

/*prototipo funzioni più semplici*/
/*creazione di un nuovo nodo*/
link newNode(link next){
    link x=malloc(sizeof(struct person));
    x->next=next;
    return x;
}
/*stampa di una linea di anagrafica*/
void printPerson (FILE *fPtr,link printPointer) {//TODO, che funzione del cazzo
    fprintf(fPtr, "%s %s %s %s %s %s %d\n", printPointer->code, printPointer->name, printPointer->surname,
            printPointer->date, printPointer->address, printPointer->city, printPointer->cap);
}
/*funzione che trasforma una data gg/mm/aaa in una data numerica aaaammgg confrontabile con altre date*/
int DateInt(char *date){
    int year=0,month=0,day=0;
    sscanf(date, "%d/%d/%d", &day, &month, &year);
    return year * 10000 + month * 100 + day;
}

int main() {
    link head=NULL, oldNode;
    command menuChoice=error;
    char stringInserted[255];

    /*ciclo per permettere all'utente di eseguire quante scelte vuole*/
    while (menuChoice!=end) {
        menuChoice = menu(stringInserted, head);
        operation(menuChoice,stringInserted,&head);
    }

    /*liberazione della memoria*/
    if (head==NULL)
        return 0; //uscita dal programma senza deallocare se non c'è nulla di salvato in memoria
    while(head->next!=NULL){
        oldNode=head;
        free(oldNode);
        head=head->next;
    }
    free(head);

    return 0;
}

void newPerson (link *head, FILE *fPtr){//fPtr non è per forza puntatore a file, nel caso l'utente inserisca "tastiera"
    link x, p;
    int cap, numericDateTemp;
    char dateOfBirth[11], code [9];//bug non risolto mi obbliga a creare una stringa code di dimensione maggiore del dovuto
    char name[MAXCHAR], surname[MAXCHAR], address[MAXCHAR],city[MAXCHAR];

    while (fscanf(fPtr,"%s %s %s %s %s %s %d",code, name, surname, dateOfBirth, address, city, &cap)!=EOF) {
        numericDateTemp = DateInt(dateOfBirth);
        if (*head == NULL || ((*head)->numericDate < numericDateTemp)) {
            x= newNode(*head);
            *head = x;
            copysize(x,code,name,surname,address,city,dateOfBirth,cap);
        } else {
            p=(*head)->next;
            x=*head;
            while(p!=NULL && ((p)->numericDate > numericDateTemp)){
                x=p;
                p=p->next;
            }
            x->next=newNode(p);
            x=x->next;
            copysize(x,code,name,surname,address,city,dateOfBirth,cap);
        }
        if (fPtr==stdin)
            break;
    }

}

command menu (char insertion[], link head){
    char choice[255];

    if(head==NULL)
        printf("\n-nessun dato presente in memoria\n");
    else
        printf("\n-in memoria sono presenti dei dati\n");
    printf("inserire scelta menu'\n");
    /*svuoto il buffer della tastiera (utile solo nel caso l'utente abbia inserito l'anagrafica da tastiera e non da file)*/
    fflush(stdin);
    gets(insertion);
    sscanf(insertion,"%s",choice);
    /*le possibili scelte del menù sono elencate tramite il comando help, come in tutte le command line*/
    if(!strcmp(choice,"inserimento"))
        return acquisition;
    if(!strcmp(choice,"fine"))
        return end;
    if(!strcmp(choice,"help"))
        return showhelp;
    /*se non ci sono dati in memoria esco precocemente dal menù*/
    if (head==NULL &&(!strcmp(choice,"cerca") || !strcmp(choice,"elimina") || !strcmp(choice,"stampa")))
        return nodata;
    if(!strcmp(choice,"cerca"))
        return search;
    if(!strcmp(choice,"elimina"))
        return delete;
    if(!strcmp(choice,"stampa"))
        return print_usr;
    return error;
}

void operation(command menuChoice, char stringInserted[],link *head){
    char genericString[255]; //sacrifico la leggibilità in funzione di una migliore gestione dello spazio: ho una stringa al posto di 6
    char secondDate[11];
    FILE *fPtr=NULL;
    link x=NULL, father=NULL; //link, I'm your father

    /*in tutti i casi mi serve solo la seconda stringa inserita dall'utente; non ho trovato alcun modo "pulito" di farlo
     * quindi uso due volte la stessa variabile*/
    switch (menuChoice){
        case acquisition:
            sscanf(stringInserted,"%s %s", genericString, genericString);
            /*se l'utente vuole inserire da tastiera richiamo la funzione di creazione ma con stdin come puntatore a file*/
            if (!strcmp(genericString,"tastiera")){
                printf("inserire stringa di anagrafica\n");
                newPerson(head, stdin);
            } else{
                if ((fPtr=fopen(genericString,"r"))==NULL){
                    printf("errore, file non trovato\n");
                    return;
                }
                newPerson(head,fPtr);
                fclose(fPtr);
            }

            break;

        case error:
            printf("errore, comando non riconosciuto, inserire help per visualizzare la lista dei comandi\n");
            break;

        case search:
            sscanf(stringInserted,"%s %s", genericString,genericString);
            x=searchElement(*head,genericString,NULL);
            /*la funzione di ricerca restituisce il nodo padre del nodo cercato, quindi devo incrementarlo*/
            x=x->next;
            if (x==NULL)
                printf("elemento non trovato");
            else
                /*come per l'inserimento per la stampa a video basta avviare la funzione di stampa con stdout come puntaore*/
                printPerson(stdout,x);
            break;

        case print_usr:
            sscanf(stringInserted,"%s %s", genericString, genericString);
            /*se l'utente vuole stampare a video fPtr è uguale a stdout, così posso usare la stessa funzione di stampa in entrambi i casi*/
            if (!strcmp(genericString,"video"))
                fPtr=stdout;
            else
                fPtr=fopen(genericString,"w");
            x=*head;
            do{
                printPerson(fPtr,x);
                if (x->next!=NULL)
                    x=x->next;
            } while (x->next!=NULL);
            if (fPtr!=stdout) //se l'utente vuole stampare a video non devo "chiudere" stdout, altrimenti non posso più stampare a video
                fclose(fPtr);
            break;

        case delete:
            sscanf(stringInserted,"%s %s %s",genericString,genericString,secondDate);
            if (genericString[0]=='A') {
                /*utilizzo sempre la stessa funzione di ricerca che restituisce il puntatore al nodo padre*/
                father = searchElement( *head, genericString, NULL);
                x=father->next;
                if(x==NULL) {
                    printf("Il codice cercato \"%s\" non e' associato a nessun dato anagrafico presente in memoria\n",genericString);
                    break;
                }
                printPerson(stdout,x);
                /*eliminazione del nodo*/
                father->next=father->next->next;
                free(x);
            }
            else {
                father = searchElement(*head,genericString,secondDate);
                if (father==NULL){
                    printf("nessun dato anagrafico trovato fra il giorno %s ed il giorno %s\n",genericString,secondDate);
                    break;
                }
                x=father->next;
                /*eliminazione di tutti i nodi compresi fra le due date, funzione iterata finche tutti i nodi sono stati eliminati (father==null)
                 * oppure si è giunti al nodo finale (x==null)*/
                while (x!=NULL) {
                    father=searchElement(x, genericString, secondDate);
                    if (father==NULL) //tutti i dati necessari sono stati eliminati (non mi piace molto usare il break, trovare alternativa)
                        break;
                    x=father->next;
                    printPerson(stdout,x);
                    father->next=father->next->next;
                    free(x);
                    x=father->next;
                }
            }
            break;
        case nodata:
            printf("impossibile eseguire l'operazione desiderata, nessun dato in memoria\n");
            break;
        case showhelp:
            printf("--------------------------------------------------------------------------------------------------\n");
            printf("inserire: \n-\"inserimento\" seguito dal nome del file con relativa estensione (tastiera per acquisire da tastiera\n"
                   "-\"ricerca\" seguito dal codice cercato\n-\"stampa\" per stampare seguito dal nome del file (video per stampare a schermo)\n"
                   "-\"elimina\" per cancellare le anagrafiche di una o piu' persone\n\tseguito da un codice per cancellare una sola anagrafica"
                   "\n\tseguito da due date per cancellare tutte le anagrafiche comprese in quell'intervallo\n"
                   "-\"help\" per mostrare questa schermata e \"fine\" per interrrompere l'esecuzione\n");
            printf("--------------------------------------------------------------------------------------------------\n");
            break;

    }

}

link searchElement (link head,char stringToCompare[], char finalDate[]){//attenzione, ritorna il nodo padre
    link x;
    int numericInitialDate;
    int numericFinalDate;
    /*la funzione riconosce autonomamente quando è inserita una data e quando un codice, avrei potuto compiere questo controllo anche fuori*/
    if (stringToCompare[0]=='A' || finalDate==NULL){
        /*ciclo for finche il nodo non è l'ultimo (nodo figlio==null) oppure il nodo cercato (nodo figlio==null)*/
        for ( x=head ; x->next!=NULL && (strcmp(stringToCompare,x->next->code)) ; x=x->next);
        return x; //ritorno del nodo padre
    } else{
        numericInitialDate=DateInt(stringToCompare);
        numericFinalDate=DateInt(finalDate);
        /*ciclo for finche il nodo non è l'ultimo (nodo figlio==null) oppure la sua data esula dall'intervallo di date*/
        for ( x=head ; x->next!=NULL; x=x->next){
            if ((numericInitialDate < x->next->numericDate) && (x->next->numericDate < numericFinalDate)) {
                return x;
            }
        }
    }
    return NULL;
}

void copysize(link x, char *code,char *name, char *surname, char *address, char *city, char *date, int cap){
    /*tramite una serie di strdup posso caricare esattamente in memoria le stringhe, senza sovrallocare*/
    x->cap = cap;
    x->date = strdup(date);
    x->code = strdup(code);
    x->name = strdup(name);
    x->surname = strdup(surname);
    x->address = strdup(address);
    x->city = strdup(city);
    x->numericDate = DateInt(date);

}