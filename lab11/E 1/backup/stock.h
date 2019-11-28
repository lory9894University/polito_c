//
// Created by lorenzodentis on 09/01/2019.
//
#include <stdio.h>
#ifndef E_1_STOCK_H
#define E_1_STOCK_H
typedef struct stock_t * stock;
typedef struct stockList_t * stockList;

stockList stockListCreation(char *filename);
stock stockSearch(char *name, stockList list);
void stockListFree(stockList list);
void stockListAdd(stockList list,char *filename);
void intervalSearch(stock stockFound, char *input);
void dateSearch(stock stockFound, char *date);
#endif //E_1_STOCK_H
