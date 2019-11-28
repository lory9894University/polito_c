#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 255

typedef enum {newPlayerList=0, newPlayer,deletePlayer ,newItemList, equipItem, unequipItem,emptyMem,stats,help, error,end} choice;
typedef struct {
    char *name;
    int hp, mp, atk, def, mag,spr;
} item;
typedef struct {
    item* itemList;
    int numberOfItem;
    int maxNumberOfItem;
}equipableItem;
typedef struct character * link;
typedef struct character{
    char *name, *class, *id;
    int hp, mp, atk, def, mag,spr;
    item *gearEquipped;
    int gearInUse; //niente altro che la lunghezza di gear equipped
    link next;
}character;
struct players{
    link head;
    link tail;
    int numberOfPlayer;
};

link newNode(link next){
    link x;
    x=malloc(sizeof(*x));
    x->next=next;
}
void addPlayer(struct players* playersList,char *inputline,char *inputFile);
choice menu(char inputLine[],struct players playersList,equipableItem itemWrapper);
void operation(choice userChoice, struct players *playersList, char *inputLine,equipableItem *itemWrapper);
void copysize(link currentCharacter,char *name,char *class,char *id,int hp,int mp,int atk,int def,int mag,int spr){
    currentCharacter->name=strdup(name);
    currentCharacter->id=strdup(id);
    currentCharacter->class=strdup(class);
    currentCharacter->hp=hp;
    currentCharacter->mp=mp;
    currentCharacter->atk=atk;
    currentCharacter->def=def;
    currentCharacter->mag=mag;
    currentCharacter->spr=spr;
}
void newItemVector(equipableItem *itemWrapper, char *inputFile){
    FILE *fptr;
    char name[50];

    if ((fptr=fopen(inputFile,"r"))==NULL) {
        printf("errore, file non trovato\n");
        return;
    }
    fscanf(fptr,"%d",&itemWrapper->numberOfItem);
    itemWrapper->itemList=(item *)malloc(sizeof(item));
    for (int i = 0; i <itemWrapper->numberOfItem ; i++) {
        fscanf(fptr,"%s %d %d %d %d %d %d", name, &itemWrapper->itemList[i].hp,&itemWrapper->itemList[i].mp,&itemWrapper->itemList[i].atk,&itemWrapper->itemList[i].def,&itemWrapper->itemList[i].mag,&itemWrapper->itemList[i].spr);
        itemWrapper->itemList[i].name=strdup(name);
    }
    fclose(fptr);
}
void playerEliminination(struct players* playerslist,char *playercode); //creare una Playersearch? mi serve anche poi
void itemEquip (); //magari mettere anche l'uneqiup
void statsCalculation(struct players *playerslist,char *playerCode, equipableItem *itemWrapper );
link playerSearch(struct players *playersList, char *playerCode); //ritorna il puntatore al padre del nodo cercato

int main() {
    char inputLine[MAXCHAR];
    equipableItem itemWrapper;
    struct players playersList;
    choice userChoice=error;

    itemWrapper.itemList=NULL;
    setbuf(stdout,0);
    /*inizializzazione della lista personaggi*/
    playersList.head=NULL;
    playersList.tail=NULL;
    playersList.numberOfPlayer=0;
    while (userChoice!=end) {
        userChoice = menu(inputLine, playersList,itemWrapper);
        operation(userChoice, &playersList, inputLine,&itemWrapper);
    }
    return 0;
}
choice menu(char inputLine[],struct players playersList,equipableItem itemWrapper){
    char userChoice[MAXCHAR];

    printf("\n");
    if (playersList.head==NULL)
        printf("-nessun personaggio presente in memoria\n");
    else
        printf("-in memoria sono presenti dei personaggi\n");
    if (itemWrapper.itemList==NULL)
        printf("-nessun oggetto presente in memoria\n");
    else
        printf("-in memoria sono presenti degli oggetti\n");
    fflush(stdin);
    printf("inserire scelta\n");
    gets(inputLine);
    if (!strcmp(inputLine,"q"))
        strcpy(inputLine,"carica personaggi pg.txt");
    printf("\n");
    sscanf(inputLine,"%s",userChoice);
    if (!strcmp(userChoice,"help"))
        return help;
    if (!strcmp(userChoice,"carica")){
        sscanf(inputLine,"%s %s",userChoice,userChoice);
        if (!strcmp(userChoice,"personaggi")){
            return newPlayerList;
        } else if(!strcmp(userChoice,"oggetti")){
            return newItemList;
        }

        return error;
    }
    if(!strcmp(userChoice,"nuovo")) {
        sscanf(inputLine,"%s %s",userChoice,userChoice);
        if (!strcmp(userChoice, "personaggio"))
            return newPlayer;
        else{
            /*possibile aggiunta di un oggetto non prevista dalla consegna*/
        }
        return error;
    }
    if((!strcmp(userChoice,"statistiche")||!strcmp(userChoice,"rimuovi")||!strcmp(userChoice,"elimina")) && playersList.head==NULL)
        return emptyMem;
    if (!strcmp(userChoice,"statistiche"))
        return stats;
    if (!strcmp(userChoice,"aggiungi"))
        return equipItem;
    if (!strcmp(userChoice,"rimuovi"))
        return unequipItem;
    if (!strcmp(userChoice,"elimina"))
        return deletePlayer;
    if (!strcmp(userChoice,"fine"))
        return end;
    return error;
}
void operation(choice userChoice, struct players *playersList, char *inputLine,equipableItem *itemWrapper){
    char trash[MAXCHAR], filename[MAXCHAR],pgId[MAXCHAR];

    switch (userChoice){
        case help:
            printf("----------------------------------------------------------------------------------------------------------------\n");
            printf("inserire il comando desiderato:\n\n\t\"carica\" [[personaggi] | [oggetti]] [nomefile.txt]\n\t\t-personaggi per inserire un elenco di personaggi dal file \"nomefile.txt\"\n\t\t"
                   "-oggetti per inserire un elenco di oggetti dal file \"nomefile.txt\"\n\n"
                   "\t\"nuovo personaggio\" [codice] [nome] [classe] [hp] [mp] [atk] [def] [mag] [spr] per inserire un singolo personaggio\n\n"
                   "\t\"elimina\" [codice_personaggio] per cancellare un personaggio dalla memoria\n\n\t\"aggiungi\" [codice_personaggio] [nome_oggetto] per inserire nell'inventario di un PG tale oggetto\n\n"
                   "\t\"rimuovi\" [codice_personaggio] [nome_oggetto] per togliere dall'inventario del PG tale oggetto\n\n\t\"statistiche\" per calcolare le statistiche di un personaggio tenendo in considerazione i suoi parametri base\n\te "
                   "l'equipaggiamento corrente.\n");
            printf("----------------------------------------------------------------------------------------------------------------\n");
            break;
        case end:
            break;
        case emptyMem:
            if ((*playersList).head==NULL)
                printf("aggiungere personaggi in memoria prima di effettuare questa operazione\n");
            if (itemWrapper->itemList==NULL)
                printf("aggiungere oggetti in memoria prima di effettuare questa operazione\n");
            break;
        case error:
            printf("comando non riconosciuto, digitare help per la lista dei comandi\n");
            break;
        case newPlayerList:
            inputLine=inputLine+18;  //l'unico comando inseribile dall'utente per giungere a questo case è "carica personaggi" ed ha 18 caratteri
            addPlayer(playersList,inputLine,inputLine);
            break;
        case newPlayer:
            inputLine=inputLine+17; //l'unico comando inseribile dall'utente per giungere a questo case è "nuovo personaggio" ed ha 17 caratteri
            addPlayer(playersList,inputLine,"tastiera");
            break;
        case newItemList:
            inputLine=inputLine+15;  //l'unico comando inseribile dall'utente per giungere a questo case è "carica oggetti" ed ha 15 caratteri
            newItemVector (itemWrapper, inputLine);
            break;
        case deletePlayer:
            inputLine=inputLine+8; //ormai si capisce la logica
            playerEliminination(playersList,inputLine);
            break;
        case equipItem:
            break;
        case unequipItem:
            break;
        case stats:
            break;
    }
}
void addPlayer(struct players* playersList,char *inputLine,char *inputFile){
    FILE *fptr;
    char name[MAXCHAR], class[MAXCHAR], id[MAXCHAR];
    int hp, mp, atk, def, mag,spr;
    char trash[MAXCHAR];

    if (!strcmp(inputFile,"tastiera")){
        sscanf(inputLine,"%s %s %s %d %d %d %d %d %d",id,name,class,&hp,&mp,&atk,&def,&mag,&spr);
        if (playersList->head==NULL) {
            playersList->tail= newNode(NULL);
            playersList->head = playersList->tail;
            playersList->numberOfPlayer++;
        }else {
            playersList->tail->next = newNode(NULL);
            playersList->tail=playersList->tail->next;
            playersList->numberOfPlayer++;
        }
        copysize(playersList->tail,name,class,id,hp,mp,atk,def,mag,spr);
        return;
    }else{
        if ((fptr=fopen(inputFile,"r"))==NULL){
            printf("errore, file non trovato\n");
            return;
        }
        do{
            fscanf(fptr,"%s %s %s %d %d %d %d %d %d",id,name,class,&hp,&mp,&atk,&def,&mag,&spr);
            if (playersList->head==NULL) {
                playersList->tail= newNode(NULL);
                playersList->head = playersList->tail;
                playersList->numberOfPlayer++;
            }else {
                playersList->tail->next = newNode(NULL);
                playersList->tail = playersList->tail->next;
                playersList->numberOfPlayer++;
            }
            copysize(playersList->tail,name,class,id,hp,mp,atk,def,mag,spr);

        }while (!feof(fptr));
        fclose(fptr);
    }
}

void playerEliminination(struct players* playerslist,char *playercode){
    link father,x;

    father=playerSearch(playerslist,playercode);
    if (father->next==NULL){  //oppure quando i=numberOfPlayer -1
        printf("nessun giocatore con codice %s trovato\n",playercode);
    } else{
        x=father->next;
        if(x->next==NULL) //ultimo elemento in lista, devo aggiornare tail
            playerslist->tail=father;
        father->next=father->next->next;
        free(x);
    }
}

link playerSearch(struct players *playersList, char *playerCode){
    link x,father;

    if (playersList->head==NULL)
        return NULL;
    for (father=playersList->head, x=father->next; x==NULL || !strcmp(playerCode,x->id);father=father->next,x=x->next){

    }

    return father;
}