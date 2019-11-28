//
// Created by lorenzodentis on 05/12/2018.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PG.h"
#include "Item.h"
link newNode(link next){
    link x;
    x=malloc(sizeof(*x));
    x->next=next;
}
void playerListInit(players *playersList){
    /*inizializzazione della lista personaggi*/
    playersList->head=NULL;
    playersList->tail=NULL;
    playersList->numberOfPlayer=0;
}
int emptyPg(players playersList){
    if (playersList.head==NULL)
        return 1;
    return 0;
}
void addPlayer(players* playersList,char *inputLine,char *inputFile){
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
void playerEliminination(players* playerslist,char *playercode){
    link father,x;

    father=playerSearch(playerslist,playercode);
    if (father==NULL)
        return;
    if (father==playerslist->head) {//è il primo elemento in lista
        playerslist->head=playerslist->head->next;
        free(father);
        printf("personaggio eliminato\n");
        return;
    }
    x=father->next;
    if(x->next==NULL) //ultimo elemento in lista, devo aggiornare tail
            playerslist->tail=father;
    father->next=father->next->next;
    pgFree(x);
    printf("personaggio eliminato\n");
    return;

}
link playerSearch(players *playersList, char *playerCode) {
    link father;

    if (playersList->head == NULL) {
        printf("non ci sono personaggi in memoria"); //credo sia ridondante questo controllo, lo mantengo solo per completezza della funzione
        return NULL;
    }
    if (!strcmp(playersList->head->id, playerCode))
        return playersList->head;
    for (father = playersList->head;
         father->next != NULL && (strcmp(playerCode, father->next->id) != 0); father = father->next);
    if (father->next == NULL && (strcmp(playerCode, father->id) != 0)) {
        printf("nessun personaggio con codice %s trovato\n", playerCode);
        return NULL;
    }
    return father;
}
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
    currentCharacter->gearEquipped=(item **)malloc(sizeof(item*)*8); //quando poi servirà verrà allocato dinamicamente
}
void statsCalculation(players *playerslist,char *playerCode){
    link x;
    int Ihp=0, Imp=0, Iatk=0, Idef=0, Imag=0,Ispr=0,i;

    x=playerSearch(playerslist,playerCode);
    if (x==NULL)
        return;
    x=x->next;
    for (i=0; i<x->gearInUse; i++){
        Ihp+=x->gearEquipped[i]->hp;
        Imp+=x->gearEquipped[i]->mp;
        Iatk+=x->gearEquipped[i]->atk;
        Idef+=x->gearEquipped[i]->def;
        Imag+=x->gearEquipped[i]->mag;
        Ispr+=x->gearEquipped[i]->spr;
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
    printf("id:%s nome:%s classe:%s\n-ha le seguenti statistiche:\n\thp:%d mp:%d atk:%d def:%d mag:%d spr:%d\n",x->id,x->name,x->class,Ihp,Imp,Iatk,Idef,Imag,Ispr);
}
void itemEquip (players *playerslist,char *playerCode,char *itemName,equipableItem *itemWrapper){
    link x;
    int itemPosition;

    x=playerSearch(playerslist,playerCode);
    if (x==NULL)
        return;

    x=x->next;
    if (x->gearInUse>=8){
        printf("stai trasportando troppo peso\n"); //così, per rimanere in tema
        return;
    }
    if (itemSearch(itemName,x->gearEquipped,x->gearInUse)!=-1){ //ricerco l'oggetto nell'inventario
        printf("oggetto gia' equipaggiato\n");
        return;
    }
    if ((itemPosition=itemSearch(itemName,itemWrapper->itemList,itemWrapper->numberOfItem))!=-1){
        x->gearEquipped[x->gearInUse]=itemWrapper->itemList[itemPosition];
        x->gearInUse++;
        printf("l'oggetto e' stato equipaggiato\n");
        return;
    }
    printf("oggetto non equipaggiabile\n");
}
void playerPrint(char *code,players *playerslist){
    link x=playerSearch(playerslist,code);

    if (x==NULL)
        return;
    x=x->next;
    statsCalculation(playerslist,code);
    if (x->gearInUse == 0) {
        printf("non ha alcun oggetto equipaggiato\n");
        return;
    }
    printf("sta trasportando:\n");
    for (int i = 0; i <x->gearInUse ; i++) {
        itemPrint(*x->gearEquipped[i]);
    }
}
void itemUnequip (players *playerslist,char *playerCode,char *itemName){
    link x;
    int itemPosition;

    x=playerSearch(playerslist,playerCode);
    if (x==NULL)
        return;
    x=x->next;

    if ((itemPosition=itemSearch(itemName,x->gearEquipped,x->gearInUse))==-1){
        printf("oggetto non presente nell'inventario\n");
        return;
    }
    if (itemPosition==x->gearInUse){ //l'elemento è l'ultimo trovato
        x->gearInUse--;
        printf("oggetto rimosso\n");
        return;
    }
    itemPosition++;
    while(itemPosition<x->gearInUse) {
        x->gearEquipped[itemPosition-1]=x->gearEquipped[itemPosition];
        itemPosition++;
    }
    x->gearInUse--;
    printf("oggetto rimosso\n");
}
void pgFree(link character){
    itemFree(character->gearEquipped,character->gearInUse);
}
void pgListFree(players playersList){
    int i;
    link parent,x;

    parent=playersList.head;
    if (parent==NULL) //se la lista è vuota non si fa alcuna free
        return;
    x=parent->next;
    for (i = 0; i <playersList.numberOfPlayer-1 ; i++) {
        pgFree(parent);
        parent=x;
        x=x->next;
    }
}