//
// Created by lorenzodentis on 03/01/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "date.h"
dateType charToDate(char *letteralDate){
    dateType date;

    sscanf(letteralDate,"%d/%d/%d",&date.year,&date.month,&date.day);
    date.numericDate=date.year*10000+date.month*100+date.day;
    return date;
}