#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned int num;
    int res, count=0, i,size=1;
    int *vector=malloc(sizeof(int));
    scanf("%d",&num);
    while (num>1){
        if (count>= size){
            size*=2;
            vector= realloc(vector,size * sizeof(int));
        }
        res = num & 1;
        vector[count]=res;
        num >>=1;
        count++;
    }
    vector[count]=num;
    for (i = count; i >=0 ; i--) {
        printf("%d",vector[i]);
    }
    return 0;
}