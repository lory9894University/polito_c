#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgList.h"

#define MAXCHAR 256
#define SMALLCHAR 51
#define dbg 0

typedef enum {
    newPlayerList = 0,
    newPlayer,
    deletePlayer,
    newItemList,
    equipItem,
    unequipItem,
    emptyMem,
    stats,
    help,
    printPLayer,
    error,
    end
} choice;

choice menu(char inputLine[], players playersList, equipableItem itemWrapper);

void operation(choice userChoice, players *playersList, char *inputLine, equipableItem *itemWrapper);

void showHelp();

int main() {
    char inputLine[MAXCHAR];
    equipableItem itemWrapper;
    players playersList;
    choice userChoice = error;

    itemWrapper = itemInit(); //wrapper del vettore degli oggetti equipaggiabili
#if dbg
    setbuf(stdout,0);
#endif
    playersList = playerListInit(); //wrapper della lista di PG
    showHelp(); //visualizza l'help alla prima esecuzione
    while (userChoice != end) {
        userChoice = menu(inputLine, playersList, itemWrapper);
        operation(userChoice, &playersList, inputLine, &itemWrapper);
    }
    /*liberazione di tutta la mem allocata*/
    itemWrapperFree(itemWrapper);
    pgListFree(playersList);
    free(itemWrapper);
    free(playersList);
    return 0;
}

choice menu(char inputLine[], players playersList, equipableItem itemWrapper) {
    char userChoice[MAXCHAR];

    printf("\n");
    if (emptyPg(playersList))
        printf("-nessun personaggio presente in memoria\n");
    else
        printf("-in memoria sono presenti dei personaggi\n");
    if (emptyItem(itemWrapper))
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
    sscanf(inputLine, "%s", userChoice);
    if (!strcmp(userChoice, "help"))
        return help;
    if (!strcmp(userChoice, "carica")) {
        sscanf(inputLine, "%s %s", userChoice, userChoice);
        if (!strcmp(userChoice, "personaggi")) {
            return newPlayerList;
        } else if (!strcmp(userChoice, "oggetti")) {
            return newItemList;
        }

        return error;
    }
    if (!strcmp(userChoice, "nuovo")) {
        sscanf(inputLine, "%s %s", userChoice, userChoice);
        if (!strcmp(userChoice, "personaggio"))
            return newPlayer;
        else {
            /*possibile aggiunta di un oggetto non prevista dalla consegna*/
        }
        return error;
    }
    if (!strcmp(userChoice, "elimina")) {
        if (emptyPg(playersList) == -1)
            return emptyMem;
        return deletePlayer;
    }
    if ((!strcmp(userChoice, "statistiche") || !strcmp(userChoice, "rimuovi") || !strcmp(userChoice, "aggiungi") ||
         !strcmp(userChoice, "visualizza")) && (emptyItem(itemWrapper) || emptyPg(playersList)))
        return emptyMem;
    if (!strcmp(userChoice, "visualizza"))
        return printPLayer;
    if (!strcmp(userChoice, "statistiche"))
        return stats;
    if (!strcmp(userChoice, "aggiungi"))
        return equipItem;
    if (!strcmp(userChoice, "rimuovi"))
        return unequipItem;
    if (!strcmp(userChoice, "fine"))
        return end;
    return error;
}

void operation(choice userChoice, players *playersList, char *inputLine, equipableItem *itemWrapper) {
    char itemName[MAXCHAR];

    switch (userChoice) {
        case help:
            showHelp();
            break;
        case end:
            break;
        case emptyMem:
            if (emptyPg(*playersList))
                printf("aggiungere personaggi in memoria prima di effettuare questa operazione\n");
            if (emptyItem(*itemWrapper))
                printf("aggiungere oggetti in memoria prima di effettuare questa operazione\n");
            break;
        case error:
            printf("comando non riconosciuto, digitare help per la lista dei comandi\n");
            break;
        case newPlayerList:
            inputLine = inputLine +
                        18;  //l'unico comando inseribile dall'utente per giungere a questo case è "carica personaggi" ed ha 18 caratteri
            addPlayer(playersList, inputLine, inputLine);
            break;
        case newPlayer:
            inputLine = inputLine +
                        17; //l'unico comando inseribile dall'utente per giungere a questo case è "nuovo personaggio" ed ha 17 caratteri
            addPlayer(playersList, inputLine, "tastiera");
            break;
        case newItemList:
            inputLine = inputLine +
                        15;  //l'unico comando inseribile dall'utente per giungere a questo case è "carica oggetti" ed ha 15 caratteri
            newItemVector(itemWrapper, inputLine);
            break;
        case deletePlayer:
            inputLine = inputLine + 8; //ormai si capisce la logica
            playerEliminination(playersList, inputLine);
            break;
        case printPLayer:
            inputLine = inputLine + 11;
            playerPrint(inputLine, playersList);
            break;
        case equipItem:
            inputLine = inputLine + 9;
            strcpy(itemName, inputLine + 7);
            inputLine[6] = '\0';
            itemEquip(playersList, inputLine, itemName, *itemWrapper);
            break;
        case unequipItem:
            inputLine = inputLine + 8;
            strcpy(itemName, inputLine + 7);
            inputLine[6] = '\0';
            itemUnequip(playersList, inputLine, itemName);
            break;
        case stats:
            inputLine = inputLine + 12;
            statsCalculation(playersList, inputLine);
            break;
    }
}

void showHelp() {
    /* non era necessario creare una funzione per un printf, però così è comodo da modificare*/
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("inserire il comando desiderato:\n\n\t\"carica\" [[personaggi] | [oggetti]] [nomefile.txt]\n\t\t-personaggi per inserire un elenco di personaggi dal file \"nomefile.txt\"\n\t\t"
           "-oggetti per inserire un elenco di oggetti dal file \"nomefile.txt\"\n\n"
           "\t\"nuovo personaggio\" [codice] [nome] [classe] [hp] [mp] [atk] [def] [mag] [spr] per inserire un singolo personaggio\n\n"
           "\t\"elimina\" [codice_personaggio] per cancellare un personaggio dalla memoria\n\n\t\"aggiungi\" [codice_personaggio] [nome_oggetto] per inserire nell'inventario di un PG tale oggetto\n\n"
           "\t\"rimuovi\" [codice_personaggio] [nome_oggetto] per togliere dall'inventario del PG tale oggetto\n\n\t\"statistiche\" per calcolare le statistiche di un personaggio tenendo in considerazione i suoi parametri base\n\te "
           "l'equipaggiamento corrente.\n\t\"visualizza\" [codice_personaggio] per visualizzare le caratteristiche di un personaggio ed il suo equipaggiamento\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
}
