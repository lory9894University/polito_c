#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adj.h"
#define dbg 1
typedef enum choice_t {adjaList,coupleAdjCheck,print,help,error,end,egg} choices;
choices menu();
void operation (choices choice,adjList *list,int *adjListFlag, adjMatrix matrix, indexTable table);
void Egg();
int main(int argc,char **argv) {
    indexTable table;
    graphEdges graph;
    rowsSaved tmpEdges;
    int adjListFlag=0;
    choices choice=error;
    adjMatrix adjacencies;
    adjList listWrapper;

#ifdef dbg
    setbuf(stdout,0);
#endif

    if (argc!=2) {
        printf("argomento inserito non corretto\ninserire il nome del programma e [nomefile]");
    }
    /*fase di acquisizione*/
    tmpEdges=rawAcquisition(argv[1]); //acquisizione "sporca" che va a salvare i dati in un vettore di struct (tmpEdges)
    table=tableOrganization(tmpEdges);
    graph=edgesOrganization(tmpEdges,table);
    //auxiliarFree(tmpEdges);
    //free(tmpEdges);
    adjacencies=adjMatrixCreation(graph,table);
    /*fine acquisizione*/
    operation(help,&listWrapper,&adjListFlag,adjacencies,table);
    while (choice!=end){
        choice=menu();
        operation(choice,&listWrapper,&adjListFlag,adjacencies,table);
    }
    tableFree(table);
    free(table);
    return 0;
}

choices menu (){
    choices c;
    char choice[256];

    fflush(stdin);
    gets(choice);
    if (!strcmp(choice,"stampa"))
        return print;
    if (!strcmp(choice,"lista adiacenze"))
        return adjaList;
    if (!strcmp(choice,"adiacenza a coppie"))
        return coupleAdjCheck;
    if (!strcmp(choice,"help"))
        return help;
    if (!strcmp(choice,"fine"))
        return end;
    if (!strcmp(choice,"buon Natale"))
        return egg;
    return error;
}

void operation(choices choice,adjList *list, int *adjListFLag,adjMatrix matrix , indexTable table){
    char v1[30],v2[30],v3[30],row[90];

    switch (choice){
        case print:
            printAdj(matrix,table);
            break;
        case adjaList:
            *adjListFLag=1;
            *list=adjListCreation(matrix);
            break;
        case coupleAdjCheck:
            printf("inserire i nomi dei tre calcolatori sulla stessa riga \n");
            gets(row);
            sscanf(row,"%s %s %s",v1,v2,v3);
            if (adjListFLag){
                if (adjCheckList(v1,v2,v3,*list,table))
                    printf("gli elementi sono adiacenti\n");
                else
                    printf("gli elementi non sono adiacenti\n");
            } else{
                if (adjCheckMatrix(v1,v2,v3,matrix,table))
                    printf("gli elementi sono adiacenti\n");
                else
                    printf("gli elementi non sono adiacenti\n");
            }
            break;
        case help:
            printf("stampa per stampare\nlista adiacenze per creare la lista adj\nadiacenza a coppie per la verifica della completezza"
                   " del sottografo\nhelp per aprire questa schermata\n");
            /*è orribile ma non è la parte importante del programma*/
            break;
        case end:
            break;
        case egg:
            Egg();
            break;
        default:
            printf("errore comando non riconosciuto\n");
            break;
    }
}
void Egg(){
    int i, bianchi, asterischi, altezza=30;

    bianchi=0;
    asterischi=0;
    for(i=1;i<altezza;i=i+2)
    {
        while(bianchi<(altezza-i)/2)
        {
            printf(" ");
            bianchi++;
        }
        while(asterischi<i)
        {
            printf("*");
            asterischi++;
        }
        printf("\n");
        bianchi=0;
        asterischi=0;
    }

    printf("\t  merry APA\n");
}