#include <stdio.h>
#include <string.h>
#include "date.h"
#include "stock.h"
#define S 3

typedef enum comando_t{acquisition, end,name, error, add,totalQ,intervalQ,dateQ}command;
command menu (int* mem);
void choice(command action,stockList *stoks);
int main() {
    command action=0;
    stockList stoks;
    int mem=0;


    setbuf(stdout,0);
    while (action!=end){
        action=menu(&mem);
        choice(action,&stoks);
    }
    return 0;
}
command menu (int* mem){
    char choice[256]="acquisizione";

    printf("inserire scelta tra:\n"
           "[acquisizione][cerca titolo][quotazione in data] [quotazioni in intervallo] (o anche quotazioni totali) [fine]\n");
    fflush(stdin);
    gets(choice);
    if (!strcmp(choice,"acquisizione")){
        if (*mem)
            return add;
        else{
   	    *mem=1;
            return acquisition;
	}
    }
    if (!strcmp(choice,"fine")){
        return end;
    }
    if (!strcmp(choice,"cerca titolo")){
        return name;
    }
    if (!strcmp(choice,"quotazioni in intervallo")){
        return intervalQ;
    }
    if (!strcmp(choice,"quotazione in data")){
        return dateQ;
    }
    return error;
}
void choice(command action,stockList *stoks){
    char genName[256]="input.txt", stockName[256];
    stock stockFound;

    switch (action){
        case dateQ:
            printf("inserire il nome del titolo\n");
            scanf("%s",stockName);
            printf("inserire data\n");
            scanf("%s",genName);
            stockFound=stockSearch(stockName,*stoks);
            dateSearch(stockFound,genName);
            break;
        case intervalQ:
            printf("inserire il nome del titolo\n");
            scanf("%s",stockName);
            printf("inserire intervallo, tutte per le quotazioni totali\n");
            fflush(stdin);
            gets(genName);
            stockFound=stockSearch(stockName,*stoks);
            intervalSearch(stockFound,genName);

            break;
        case acquisition:
            printf("inserire nome file\n");
            //scanf("%s",genName);
            *stoks=stockListCreation(genName);
            break;
        case add:
            printf("inserire nome file\n");
            scanf("%s",genName);
            stockListAdd(*stoks,genName);
            break;
        case name:
            printf("inserire il nome del titolo cercato\n");
            scanf("%s",genName);
            if (stockSearch(genName,*stoks)!=NULL)
                printf("titolo presente in memoria\n");
            else
                printf("titolo non presente in memoria\n");
            break;
        case end:
            stockListFree(*stoks);
            break;
        default:
            printf("comando non riconosciuto\n");
            break;
    }
}