#include <stdio.h>

typedef struct {
    int *insieme;
    int elementi;
} Moltiplicativo;

int principio_moltiplicativo(int pos, int numeroInsiemi, Moltiplicativo *insiemi, int counter, int *sol) {

    if (pos >= numeroInsiemi) {
        printf("{");
        for (int i = 0; i < numeroInsiemi; i++) {
            printf("%d ", sol[i]);
        }
        printf("} ");
        return counter + 1;
    }

    for (int j = 0; j < insiemi[pos].elementi; j++) {
        sol[pos] = insiemi[pos].insieme[j];
        counter = principio_moltiplicativo(pos + 1, numeroInsiemi, insiemi, counter, sol);
    }

    return counter;
}

int dispSemplici(int *mark, int pos, int counter, int *sol, int k, int n, int *insieme) {
    size_t i;
    if (pos >= k) {
        printf("{");
        for (i = 0; i < k; i++) {
            printf("%d ");
        }
        printf("} ");
        return counter + 1;
    }

    for (i = 0; i < n; ++i) {
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[pos] = insieme[i];
            counter = dispSemplici(mark, pos + 1, counter, sol, k, n, insieme);
            mark[i] = 0;
        }
    }
    return counter;
}

int combinazioniSemplici(int pos, int start, int k, int counter, int n, int *sol, int *insieme) {
    int i;
    if (pos >= k) {
        printf("{");
        for (i = 0; i < k; i++) {
            printf("%d ");
        }
        printf("} ");
        return counter + 1;
    }

    for (i = start; i < n; i++) {
        sol[pos] = insieme[i];
        combinazioniSemplici(pos + 1, i + 1, k, counter, n, sol, insieme);
    }
    return counter;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}