//
// Created by lorenzodentis on 09/01/2019.
//
#include "rating.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
struct rtBst_t{
    quotation root;
    int quotationNr;
};
quotation newLeaf(quotation r,quotation l,char *date, float num, float den){
    quotation x=malloc(sizeof(*x));
    x->right=r;
    x->left=l;
    x->date=charToDate(date);
    x->den=den;
    x->num=num;
    return x;
}
char* bstRoot(transaction *raw, int dim){ //TODO o è geniale o tremendamente stupido
    int maxDate=0,minDate, averageDate,bestApprox=0,i;

    for (i = 0; i < dim; i++) {
        if (raw[i].nrDate>maxDate)
            maxDate=raw[i].nrDate;
    }
    minDate=raw[0].nrDate;
    for (i = 0; i <dim ; i++) {
        if (raw[i].nrDate<minDate)
            minDate=raw[i].nrDate;
    }
    averageDate=(maxDate+minDate)/2;
    for (i = 0; i <dim ; i++) {
        if(abs(raw[i].nrDate-averageDate)<abs(raw[bestApprox].nrDate-averageDate))
            bestApprox=i;
    }
    return raw[bestApprox].date;
}
rtBst BSTCreation(transaction *raw, int dim){
    quotation head;
    rtBst bst=malloc(sizeof(*bst));
    char* root;

    root=bstRoot(raw,dim);
    head=newLeaf(NULL,NULL,root,0,0);
    head->date=charToDate(root);
    bst->quotationNr=1;
    bst->root=head;
    return bst;
} //caso particolare in cui il bst non esiste ancora
quotation bstSearchR(quotation x,int key){
    if (x==NULL || (x->date.numericDate==key)){
        return x;
    }
    if (x->date.numericDate < key){
        return bstSearchR(x->right,key);
    } else{
        return bstSearchR(x->left,key);
    }
}
quotation quotationSearch(rtBst bst, char* key){
    int nrKey;
    int year, month, day;

    sscanf(key,"%d/%d/%d",&year,&month,&day);
    nrKey= year * 10000 + month * 100 + day;
    return bstSearchR(bst->root,nrKey);
}
quotation leafInsert(transaction raw,quotation x,char *date, float num, float den){
    if (x==NULL)
        return newLeaf(NULL,NULL,date,num,den);
    if (raw.nrDate<x->date.numericDate){
        x->left=leafInsert(raw,x->left,date,num,den);
    } else{
        x->right=leafInsert(raw,x->right,date,num,den);
    }
    return x;
}
void middlElemnt(quotation middleElement, quotation x,int middle,int actual){ //TODO magari nelle slides è più efficiente
    if (x==NULL)
        return;
    middlElemnt(middleElement,x->left,middle,actual);
    actual++;
    if (actual==middle) {
        *middleElement=*x;
        return;
    }
    middlElemnt(middleElement,x->right,middle,actual);
}
void bstBalance(rtBst bst){
    int middleValue;
    quotation newRoot;

    middleValue=(bst->quotationNr)/2;
    middlElemnt(newRoot,bst->root,middleValue,0);
}
void rawToBst(transaction *raw, int dim,rtBst bst){
    int i;
    quotation x=NULL;

    for (i = 0; i <dim ; ++i) {
        if ((x=bstSearchR(bst->root,raw[i].nrDate))!=NULL){
            x->den=x->den+raw[i].quantity;
            x->num=x->num+(raw[i].value * x->den);
        }else{
            bst->quotationNr++;
            leafInsert(raw[i],bst->root,raw[i].date,(raw[i].value * raw[i].quantity),raw[i].quantity);
        }
    }
}
dateType minDateFindR(quotation x){
    if (x->left==NULL)
        return x->date;
    else
        return minDateFindR(x->left);
}
dateType maxDateFindR(quotation x){
    if (x->right==NULL)
        return x->date;
    else
        return maxDateFindR(x->right);
}
dateType maxDateFind(rtBst bst){
    return maxDateFindR(bst->root);
}
dateType minDateFind(rtBst bst) {
    return minDateFindR(bst->root);
}

void ratingCalculation(quotation x){
    x->rating= x->num/x->den;
}
void recursivePrint(quotation x,int data1,int data2,float *ratingMin, float *ratingMax){
    if (x==NULL || x->date.numericDate<data1 || x->date.numericDate>data2)
        return;
    recursivePrint(x->left,data1,data2,ratingMin,ratingMax);
    if (x->date.numericDate>=data1 && x->date.numericDate<=data2){
        ratingCalculation(x);
        if (x->rating > *ratingMax)
            *ratingMax=x->rating;
        if (x->rating < *ratingMin)
            *ratingMin=x->rating;
    }
    recursivePrint(x->right,data1,data2,ratingMin,ratingMax);

}
void bstExploration(rtBst bst,dateType minDate,dateType maxDate){
    float ratingMin,ratingMax=0;
    if (bst->root==NULL){
        printf("nessuna quotazione per questo titolo\n");
        return;
    }
    ratingCalculation(bst->root);
    ratingMin=bst->root->rating;
    recursivePrint(bst->root,minDate.numericDate,maxDate.numericDate,&ratingMin,&ratingMax);
    printf("quotazione minima: %f, quotazione massima: %f\n",ratingMin,ratingMax);
}