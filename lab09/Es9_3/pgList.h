//
// Created by lorenzodentis on 12/12/2018.
//

#ifndef ES9_3_PGLIST_H
#define ES9_3_PGLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PG.h"
#include "equipArray.h"
#include "invArray.h"

typedef struct playersList *players;
typedef struct singleCharacter *link;

link newNode(link next);

void addPlayer(players *playersList, char *inputLine, char *inputFile);

void playerEliminination(players *playersList, char *playercode);

link playerSearch(players *playersList, char *playerCode); //ritorna il puntatore al padre del nodo cercato
void
copysize(link currentCharacter, char *name, char *class, char *id, int hp, int mp, int atk, int def, int mag, int spr);

void statsCalculation(players *playerslist, char *playerCode);

void itemEquip(players *playerslist, char *playerCode, char *itemName, equipableItem itemWrapper);

void playerPrint(char *code, players *playerslist);

void itemUnequip(players *playerslist, char *playerCode, char *itemName);

players playerListInit();

int emptyPg(players playersList);

void pgFree(link character);

void pgListFree(players playersList);

#endif //ES9_3_PGLIST_H
