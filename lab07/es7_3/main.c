#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 256
#define SMALLCHAR 51
#define dbg 1

typedef enum {newPlayerList=0, newPlayer,deletePlayer ,newItemList, equipItem, unequipItem,emptyMem,stats,help, error,end} choice;
typedef struct {
    char name[SMALLCHAR],type[SMALLCHAR];
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
void addPlayer(struct players* playersList,char *inputLine,char *inputFile);
choice menu(char inputLine[],struct players playersList,equipableItem itemWrapper);
void operation(choice userChoice, struct players *playersList, char *inputLine,equipableItem *itemWrapper);
void playerEliminination(struct players* playerslist,char *playercode);
void itemEquip (struct players *playerslist,char *playerCode,char *itemName, equipableItem *itemWrapper);
void itemUnequip (struct players *playerslist,char *playerCode,char *itemName);
void statsCalculation(struct players *playerslist,char *playerCode, equipableItem *itemWrapper);
link playerSearch(struct players *playersList, char *playerCode); //ritorna il puntatore al padre del nodo cercato
/*definizione funzioni più semplici*/
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
    currentCharacter->gearInUse=0;
    currentCharacter->gearEquipped=malloc(sizeof(item)*8); //quando poi servirà verrà allocato dinamicamente
}
void copyItem(link currentCharacter,item itemToEquipy){

    strcpy(currentCharacter->gearEquipped[currentCharacter->gearInUse-1].name,itemToEquipy.name);
    currentCharacter->gearEquipped[currentCharacter->gearInUse-1].hp=itemToEquipy.hp;
    currentCharacter->gearEquipped[currentCharacter->gearInUse-1].mp=itemToEquipy.mp;
    currentCharacter->gearEquipped[currentCharacter->gearInUse-1].atk=itemToEquipy.atk;
    currentCharacter->gearEquipped[currentCharacter->gearInUse-1].def=itemToEquipy.def;
    currentCharacter->gearEquipped[currentCharacter->gearInUse-1].mag=itemToEquipy.mag;
    currentCharacter->gearEquipped[currentCharacter->gearInUse-1].spr=itemToEquipy.spr;

}
void newItemVector(equipableItem *itemWrapper, char *inputFile){
    FILE *fPtr;

    if ((fPtr=fopen(inputFile,"r"))==NULL) {
        printf("errore, file non trovato\n");
        return;
    }
    fscanf(fPtr,"%d",&itemWrapper->numberOfItem);
    itemWrapper->itemList=(item *)malloc(sizeof(item)*itemWrapper->maxNumberOfItem);
    for (int i = 0; i <itemWrapper->numberOfItem ; i++) {
        fscanf(fPtr,"%s %s %d %d %d %d %d %d", itemWrapper->itemList[i].name,itemWrapper->itemList[i].type, &itemWrapper->itemList[i].hp,&itemWrapper->itemList[i].mp,&itemWrapper->itemList[i].atk,&itemWrapper->itemList[i].def,&itemWrapper->itemList[i].mag,&itemWrapper->itemList[i].spr);
    }
fclose(fPtr);
}

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
#if dbg
    if (!strcmp(inputLine,"p"))
         strcpy(inputLine,"carica personaggi pg.txt");
    if (!strcmp(inputLine,"o"))
        strcpy(inputLine,"carica oggetti inventario.txt");
#endif
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
    if (!strcmp(userChoice,"elimina")) {
        if (playersList.head == NULL)
            return emptyMem;
        return deletePlayer;
    }
    if((!strcmp(userChoice,"statistiche")||!strcmp(userChoice,"rimuovi")||!strcmp(userChoice,"aggiungi")) && (playersList.head==NULL || itemWrapper.itemList==NULL))
        return emptyMem;
    if (!strcmp(userChoice,"statistiche"))
        return stats;
    if (!strcmp(userChoice,"aggiungi"))
        return equipItem;
    if (!strcmp(userChoice,"rimuovi"))
        return unequipItem;
    if (!strcmp(userChoice,"fine"))
        return end;
    return error;
}
void operation(choice userChoice, struct players *playersList, char *inputLine,equipableItem *itemWrapper){
    char itemName[MAXCHAR];

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
            inputLine=inputLine+9;
            strcpy(itemName,inputLine+7);
            inputLine[6]='\0';
            itemEquip(playersList,inputLine,itemName,itemWrapper);
            break;
        case unequipItem:
            inputLine=inputLine+8;
            strcpy(itemName,inputLine+7);
            inputLine[6]='\0';
            itemUnequip(playersList,inputLine,itemName);
            break;
        case stats:
            inputLine=inputLine+12;
            statsCalculation(playersList,inputLine,itemWrapper);
            break;
    }
}
void addPlayer(struct players* playersList,char *inputLine,char *inputFile){
    FILE *fptr;
    char name[SMALLCHAR], class[SMALLCHAR], id[SMALLCHAR];
    int hp, mp, atk, def, mag,spr;

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
    if (father==playerslist->head) {//è il primo elemento in lista
        playerslist->head=playerslist->head->next;
        free(father);
        printf("personaggio eliminato\n");
        return;
    }
    if (father==NULL){   //in realtà non è il nodo padre ad essere null, ma la funzione playerSearch ritorna null come valore di cotrollo
        printf("nessun giocatore con codice %s trovato\n",playercode);
    } else{
        x=father->next;
        if(x->next==NULL) //ultimo elemento in lista, devo aggiornare tail
            playerslist->tail=father;
        father->next=father->next->next;
        free(x);
        printf("personaggio eliminato\n");
        return;
    }
}
link playerSearch(struct players *playersList, char *playerCode){
    link father;

    if (playersList->head==NULL) {
        printf("non ci sono personaggi in memoria"); //credo sia ridondante questo controllo, lo mantengo solo per completezza della funzione
        return NULL;
    }
    if (!strcmp(playersList->head->id,playerCode))
        return playersList->head;
    for (father=playersList->head; father->next!=NULL && (strcmp(playerCode,father->next->id)!=0);father=father->next);
    if (father->next==NULL && (strcmp(playerCode,father->id)!=0)) {
        printf("personaggio non trovato\n");
        return NULL;
    }
    return father;
} //todo potrebbe essere buggata
void statsCalculation(struct players *playerslist,char *playerCode, equipableItem *itemWrapper){
    link x;
    int Ihp=0, Imp=0, Iatk=0, Idef=0, Imag=0,Ispr=0,i;

    x=playerSearch(playerslist,playerCode);
    x=x->next;
    for (i=0; i<x->gearInUse; i++){
        Ihp+=x->gearEquipped[i].hp;
        Imp+=x->gearEquipped[i].mp;
        Iatk+=x->gearEquipped[i].atk;
        Idef+=x->gearEquipped[i].def;
        Imag+=x->gearEquipped[i].mag;
        Ispr+=x->gearEquipped[i].spr;
    }
    Ihp+=x->hp;
    if (Ihp<1)
        Ihp=1;
    Imp+=x->mp;
    if (Imp<1)
        Imp=1;
    Iatk+=x->atk;
    if (Iatk<1)
        Iatk=1;
    Idef+=x->def;
    if (Idef<1)
        Idef=1;
    Imag+=x->mag;
    if (Imag<1)
        Imag=1;
    Ispr+=x->spr;
    if (Ispr<1)
        Ispr=1;
    printf("%s %s %s %d %d %d %d %d %d",x->id,x->name,x->class,Ihp,Imp,Iatk,Idef,Imag,Ispr);
}
void itemEquip (struct players *playerslist,char *playerCode,char *itemName, equipableItem *itemWrapper){
    link x;
    int i;

    x=playerSearch(playerslist,playerCode);
    if (x==NULL){
        return;
    }
    x=x->next;
    if (x->gearInUse>=8){
        printf("stai trasportando troppo peso\n"); //così, per rimanere in tema
        return;
    }
    for (i = 0; i <x->gearInUse ; i++) {
        if(!strcmp(x->gearEquipped[i].name,itemName)){
            printf("oggetto gia' equipaggiato\n");
            return;
        }
    }
    for (i=0; i<itemWrapper->numberOfItem; i++) {
        if(!strcmp(itemWrapper->itemList[i].name,itemName)){
            x->gearInUse++;
            copyItem(x,itemWrapper->itemList[i]);
            printf("l'oggetto e' stato equipaggiato\n");
            return;
        }
    }
    printf("oggetto non equipaggiabile\n");
}
void itemUnequip (struct players *playerslist,char *playerCode,char *itemName){
    link x;
    int i;

    x=playerSearch(playerslist,playerCode);
    if (x==NULL)
        return;
    x=x->next;

    for (i=0; i<x->gearInUse; i++) {
        if(!strcmp(x->gearEquipped[i].name,itemName))
            break;
    }
    if (i==x->gearInUse-1) {
        if (!strcmp(x->gearEquipped[i].name,itemName)) {
            x->gearInUse--;
            printf("oggetto rimosso\n");
            return;
        } else{
            printf("elemento non equipaggiato\n");
            return;
        }
    }
    i++;
    while(i<x->gearInUse) {
        x->gearEquipped[i-1]=x->gearEquipped[i];
    }
    x->gearInUse--;
    printf("oggetto rimosso\n");
}
//todo rimane da risolvere in problema crash fclose oggetti e fare una seria fase di testing