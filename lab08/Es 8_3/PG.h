//
// Created by lorenzodentis on 05/12/2018.
//

#ifndef ES_8_3_PG_H
#define ES_8_3_PG_H
#include "Item.h"

typedef struct singleCharacter * link;
typedef struct singleCharacter{
    char *name, *class, *id;
    int hp, mp, atk, def, mag,spr;
    item **gearEquipped; //vettore di puntatori a tipo item
    int gearInUse; //niente altro che la lunghezza di gear equipped
    link next;
}character;
typedef struct playersList{
    link head;
    link tail;
    int numberOfPlayer;
}players;

link newNode(link next);
void addPlayer(players* playersList,char *inputLine,char *inputFile);
void playerEliminination(players* playerslist,char *playercode);
link playerSearch(players *playersList, char *playerCode); //ritorna il puntatore al padre del nodo cercato
void copysize(link currentCharacter,char *name,char *class,char *id,int hp,int mp,int atk,int def,int mag,int spr);
void statsCalculation(players *playerslist,char *playerCode);
void itemEquip (players *playerslist,char *playerCode,char *itemName,equipableItem *itemWrapper);
void playerPrint(char *code,players *playerslist);
void itemUnequip (players *playerslist,char *playerCode,char *itemName);
void playerListInit(players *playersList);
int emptyPg(players playersList);
void pgFree(link character);
void pgListFree(players playersList);
#endif

