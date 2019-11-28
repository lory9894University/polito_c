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
    quotation z;
};
/*riempimento del BST*/
char* bstRoot(transaction *raw, int dim){
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
quotation newLeaf(quotation r,quotation l,char *date, float num, float den){
    quotation x=malloc(sizeof(*x));
    x->right=r;
    x->left=l;
    x->date=charToDate(date);
    x->den=den;
    x->num=num;
    x->subTree=1;
    return x;
}
rtBst BSTCreation(transaction *raw, int dim){
    quotation head;
    rtBst bst=malloc(sizeof(*bst));
    char* root;

    root=bstRoot(raw,dim);
    bst->z=newLeaf(NULL,NULL,"",0,0);
    head=newLeaf(bst->z,bst->z,root,0,0);
    head->date=charToDate(root);
    bst->quotationNr=1;
    bst->root=head;
    return bst;
} //caso particolare in cui il bst non esiste ancora
quotation bstSearchR(quotation x,int key,quotation z){
    if (x==z || (x->date.numericDate==key)){
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
quotation leafInsert(transaction raw,quotation x,char *date, float num, float den, quotation z){
    if (x==z)
        return newLeaf(z,z,date,num,den);
    if (raw.nrDate<x->date.numericDate){
        x->left=leafInsert(raw,x->left,date,num,den,z);
    } else{
        x->right=leafInsert(raw,x->right,date,num,den,z);
    }
    (x->subTree)++;
    return x;
}
void rawToBst(transaction *raw, int dim,rtBst bst){
    int i;
    quotation x=NULL;

    for (i = 0; i <dim ; ++i) {
        if ((x=bstSearchR(bst->root,raw[i].nrDate,bst->z))!=bst->z){
            x->den=x->den+raw[i].quantity;
            x->num=x->num+(raw[i].value * x->den);
        }else{
            bst->quotationNr++;
            leafInsert(raw[i],bst->root,raw[i].date,(raw[i].value * raw[i].quantity),raw[i].quantity,bst->z);
        }
    }
}
/*fine riempimento BST*/

/*calcolo delle quotazioni*/
dateType minDateFindR(quotation x,quotation z){
    if (x->left==z)
        return x->date;
    else
        return minDateFindR(x->left,z);
}
dateType maxDateFindR(quotation x,  quotation z){
    if (x->right==z)
        return x->date;
    else
        return maxDateFindR(x->right,z);
}
dateType maxDateFind(rtBst bst){
    return maxDateFindR(bst->root,bst->z);
}
dateType minDateFind(rtBst bst) {
    return minDateFindR(bst->root,bst->z);
}
void ratingCalculation(quotation x){
    x->rating= x->num/x->den;
}
void recursiveRating(quotation x,int data1,int data2,float *ratingMin, float *ratingMax, quotation z){
    if (x==z || x->date.numericDate<data1 || x->date.numericDate>data2)
        return;
    recursiveRating(x->left,data1,data2,ratingMin,ratingMax,z);
    if (x->date.numericDate>=data1 && x->date.numericDate<=data2){
        ratingCalculation(x);
        if (x->rating > *ratingMax)
            *ratingMax=x->rating;
        if (x->rating < *ratingMin)
            *ratingMin=x->rating;
    }
    recursiveRating(x->right,data1,data2,ratingMin,ratingMax,z);

}
void bstExploration(rtBst bst,dateType minDate,dateType maxDate){
    float ratingMin,ratingMax=0;
    if (bst->root==NULL){ //bst vuoto
        printf("nessuna quotazione per questo titolo\n");
        return;
    }
    ratingCalculation(bst->root);
    ratingMin=bst->root->rating;
    recursiveRating(bst->root,minDate.numericDate,maxDate.numericDate,&ratingMin,&ratingMax,bst->z);
    printf("quotazione minima: %f, quotazione massima: %f\n",ratingMin,ratingMax);
}
/*fine calcolo delle quotazioni*/

/*ribilanciamento*/
quotation rotR(quotation father){
    quotation x=father->left;
    father->left=x->right;
    x->right=father;
    x->subTree=father->subTree;
    father->subTree=father->right->subTree + father->left->subTree +1;
    return x;
}
quotation rotL(quotation father){
    quotation x=father->right;
    father->right=x->left;
    x->left=father;
    x->subTree=father->subTree;
    father->subTree=father->left->subTree + father->right->subTree +1;
    return x;

}
quotation partR(quotation h, int r) {
    int t = h->left->subTree;

    if (t > r) {
        h->left = partR(h->left, r);
        h = rotR(h);
    }
    if (t < r) {
        h->right = partR(h->right, r-t-1);
        h = rotL(h);
    }
    return h;
}
void bstBalance(rtBst bst){
    int middleValue;

    middleValue=(bst->quotationNr+1)/2;
    partR(bst->root,middleValue);
}
int longhestPath(quotation x,quotation z){
    if (x->subTree==1)
        return 1;
    if (x->left==z)
        return longhestPath(x->right,z) +1;
    if (x->right==z)
        return longhestPath(x->left,z) +1;
    if (x->left->subTree > x->right->subTree){
        return longhestPath(x->left,z) +1;
    } else{
        return longhestPath(x->right,z) +1;
    }
}
int shortestPath(quotation x,quotation z){
    if (x->subTree==1 || x->left==z || x->right==z)
        return 1;
    if (x->left->subTree < x->right->subTree){
        return shortestPath(x->left,z) +1;
    } else{
        return shortestPath(x->right,z) +1;
    }
}
void needPartition(rtBst bst,int S){
    if (longhestPath(bst->root,bst->z) - shortestPath(bst->root,bst->z) >= S){
        bstBalance(bst);
    }
}
/*fine ribilanciamento*/