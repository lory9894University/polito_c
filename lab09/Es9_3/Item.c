//
// Created by lorenzodentis on 05/12/2018.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void itemPrint(item itemToPrint) {
    printf("\t-nome:%s tipo:%s hp:%d mp:%d atk:%d def:%d mag:%d spr:%d\n", itemToPrint.name, itemToPrint.type,
           itemToPrint.hp, itemToPrint.mp, itemToPrint.atk, itemToPrint.def, itemToPrint.mag, itemToPrint.spr);
}
