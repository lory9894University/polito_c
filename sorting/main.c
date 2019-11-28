#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define dimensioni 10

void swap(int *vet1, int *vet2) {
    int swap;

    swap = *vet1;
    *vet1 = *vet2;
    *vet2 = swap;
}


void selectionsort(int *vet, int dim) {
    int max = 0;

    for (int i = 0; i < dim; i++) {
        max = i;
        for (int j = i + 1; j < dim; j++) {
            if (vet[max] > vet[j])
                max = j;
        }
        swap(&vet[max], &vet[i]);
    }

}

void insertionsort(int *vet, int dim) { //TODO accidenti non va
    int temp;
    int j;
    for (int i = 1; i < dim; i++) {
        temp = vet[i];
        for (j = i - 1; j > 0 && vet[j] < vet[i]; j--) {
            swap(&vet[j], &vet[j + 1]);
        }
        swap(&temp, &vet[j]);
    }
}

void boublesort(int *vet, int dim) { //si chiama exchange sort

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (vet[j] > vet[j + 1])
                swap(&vet[j], &vet[j + 1]);
        }
    }

}

void countingsort(int *vet, int dim) {
    int i, occorrenze = 0;
    int *sol, *occ;
    sol = calloc(dim, sizeof(int));
    for (i = 0; i < dim; i++) {
        if (vet[i] > occorrenze)
            occorrenze = vet[i];
    }
    occ = calloc(occorrenze, sizeof(int));
    for (i = 0; i < dim; i++) {
        occ[vet[i]]++;
    }
    for (i = 0; i < occorrenze; i++) {
        occ[i] += occ[i - 1];
    }
    for (i = 0; i < dim; i++) {
        sol[occ[vet[i]]] = vet[i];
        occ[vet[i]]--;
    }
    for (i = 0; i < dim; i++) {
        vet[i] = sol[i];
    }
}

void shellsort(int *vet, int dim) {
    int i, j, h, n;

    h = 1;
    n = dim + 1;

    while (h < (n / 3)) {
        h = 3 * h + 1;
    }

    while (h >= 1) {
        for (i = h; i < dim; i++) {
            for (j = i; j >= h; j -= h) {
                if (vet[j] < vet[j - h])
                    swap(&vet[j], &vet[j - h]);
            }
        }
        h = h / 3;
    }
}

/*ricorsivi*/
int partition(int *vet, int l, int r) {
    int pivot = vet[r];

    for (int i = l; i < r; i++) {
        if (vet[i] <= pivot) {
            swap(&vet[l], &vet[i]);
            l++;
        }
    }
    swap(&vet[l], &vet[r]);
    return l;

}

void qisort(int *vet, int l, int r) {
    int x;

    if (r <= l)
        return;
    x = partition(vet, l, r);
    qisort(vet, l, x - 1);
    qisort(vet, x + 1, r);

}

void quicksort(int *vet, int dim) { //wrapper
    qisort(vet, 0, dim);
}

void merge(int *vet, int l, int r, int q) {
    int aux[dimensioni], i, j, k;

    i = l;
    j = q + 1;
    for (k = l; k <= r; k++) {
        if (i > q) { //gli elementi nel sottovettore sinistro sono finiti
            aux[k] = vet[j]; //scrivo nel vettore ausiliario tutti gli elementi del sottovettore destro
            j++;
        } else if (j > r) {
            aux[k] = vet[i];
            i++;
        } else if (vet[i] <= vet[j]) {
            aux[k] = vet[i];
            i++;
        } else {
            aux[k] = vet[j];
            j++;
        }

    }
    for (k = l; k <= r; k++) {
        vet[k] = aux[k];
    }
}

void mergeS(int *vet, int l, int r) {
    int x = (l + r) / 2;

    if (r <= l)
        return;

    mergeS(vet, x + 1, r);
    mergeS(vet, l, x);
    merge(vet, l, r, x);
}

void mergesort(int *vet, int dim) { //wrapper
    mergeS(vet, 0, dim);
}

int main(int argc, char **argv) {
    char s = 's';
    int vet[dimensioni];
    int dim = dimensioni;

    for (int i = 0; i < dimensioni; i++) {
        vet[i] = rand();
    }
    for (int i = 0; i < dim; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
    s = argv[1][1];
    switch (s) {
        case 'h':
            shellsort(vet, dim);
            break;
        case 'q':
            quicksort(vet, dim);
            break;

        case 's':
            selectionsort(vet, dim);
            break;

        case 'm':
            mergesort(vet, dim);
            break;

        case 'b':
            boublesort(vet, dim);
            dim = dimensioni;
            break;

        case 'c':
            countingsort(vet, dim);
            break;

        case 'i':
            insertionsort(vet, dim);
            break;
    }

    for (int i = 0; i < dim; i++) {
        printf("%d ", vet[i]);
    }
    return 0;
}

