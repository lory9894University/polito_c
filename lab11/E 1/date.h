//
// Created by lorenzodentis on 03/01/2019.
//

#ifndef E_1_DATE_H
#define E_1_DATE_H
typedef struct date_t{
    int year, month, day;
    int numericDate;
}dateType;
dateType charToDate(char *letteralDate);
#endif //E_1_DATE_H
