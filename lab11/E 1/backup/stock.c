//
// Created by lorenzodentis on 09/01/2019.
//
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stock.h"
#include "rating.h"
struct stock_t{
    char name[20];
    int transactionNr;
    rtBst quotations;
    stock next;
}; //titolo di borsa
struct stockList_t{
    stock head;
    int stockNr;
}; //lista di titoli
stock newNode(stock next){
    stock x=malloc(sizeof(*x));
    x->next=next;
    return x;
}
void transacAcq(FILE *fPtr, int transactionNrTmp,stock x,int memorized){
    int j;
    int year, month, day;
    transaction *transVect = malloc(sizeof(struct transaction_t) * transactionNrTmp);
    for (j = 0; j < transactionNrTmp; j++) {
        /*caricamento in una struttura dati non raffinata*/
        fscanf(fPtr, "%s %s %f %d", transVect[j].date, transVect[j].time, &transVect[j].value,
               &transVect[j].quantity);
        sscanf(transVect[j].date, "%d/%d/%d", &year, &month, &day);
        transVect[j].nrDate = year * 10000 + month * 100 + day;
    }
    if (!memorized)
        x->quotations=BSTCreation(transVect,transactionNrTmp);
    rawToBst(transVect,transactionNrTmp,x->quotations);
    /*caricamento delle quotazioni nel BST*/
    free(transVect);

}
stock stockAdd(stockList listWrapper, char* nameTmp,int transactionNrTmp){
    stock x,swap;

    x = listWrapper->head;
    while (x->next != NULL) {
        if (strcmp(x->next->name, nameTmp) > 0)
            break;
        x = x->next;
    }
    swap = x->next;
    x->next = newNode(swap);
    x = x->next;
    strcpy(x->name, nameTmp);
    x->transactionNr = transactionNrTmp;
    return x;
}
stockList stockListCreation(char *filename) {
    stockList listWrapper = malloc(sizeof(*listWrapper));
    stock x;
    FILE *fPtr;
    int i;
    char nameTmp[20];
    int transactionNrTmp;

    if ((fPtr = fopen(filename, "r")) == NULL) {
        printf("errore,file non trovato\n");
        exit(1);
    }
    listWrapper->head = NULL;
    fscanf(fPtr, "%d", &listWrapper->stockNr);
    for (i = 0; i < listWrapper->stockNr; i++) {
        fscanf(fPtr, "%s %d", nameTmp, &transactionNrTmp);
        if (listWrapper->head == NULL) { //1° caso, caso particolare
            x = newNode(NULL);
            strcpy(x->name, nameTmp);
            x->transactionNr = transactionNrTmp;
            listWrapper->head = x;
        } else {
            x=stockAdd(listWrapper, nameTmp, transactionNrTmp);
        }
        transacAcq(fPtr,transactionNrTmp,x,0);
    }
    fclose(fPtr);
    return listWrapper;
}
stock stockSearch(char *name, stockList list){
    stock found;
    int i;

    for (i = 0, found=list->head; i <list->stockNr && strcmp(name,found->name)!=0 ; i++, found=found->next);
    return found;
}
void stockListAdd(stockList list,char *filename){
    FILE *fPtr;
    int transactionNrTmp,stockNr;
    char stockName[20];
    int i;
    stock newStock;

    if ((fPtr=fopen(filename,"r"))==NULL){
        printf("errore,file non trovato\n");
        exit(1);
    }
    fscanf(fPtr,"%d",&stockNr);
    for (i = 0; i <stockNr ; i++) {
        fscanf(fPtr,"%s %d",stockName,&transactionNrTmp);
        if ((newStock=stockSearch(stockName,list))==NULL) {
            list->stockNr++;
            newStock=stockAdd(list, stockName,transactionNrTmp);
            transacAcq(fPtr,transactionNrTmp,newStock,0);
        }
        else{
            transacAcq(fPtr,transactionNrTmp,newStock,1);
        }
    }
    fclose(fPtr);
}
void stockListFree(stockList list){

}
void intervalSearch(stock stockFound, char *input){
    char date1[11],date2[11];
    if (stockFound==NULL){
        printf("impossibile trovare il titolo cercato\n");
        return;
    }
    if(!strcmp(input,"tutte")){
        bstExploration(stockFound->quotations,minDateFind(stockFound->quotations),maxDateFind(stockFound->quotations));
    } else{
        if (strlen(input)!=23){
            printf("comando non riconosciuto\n");
            return;
        }
        sscanf(input,"%s %s",date1,date2);
        bstExploration(stockFound->quotations,charToDate(date1),charToDate(date2));
    }
}
void dateSearch(stock stockFound, char *date){
    quotation x;
    x=quotationSearch(stockFound->quotations,date);
    x->rating=x->num/x->den;
    printf("data: %d/%d/%d quotazione: %f\n",x->date.year,x->date.month,x->date.day,x->rating);
}