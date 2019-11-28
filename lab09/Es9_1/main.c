#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef struct activity_ {
    int s, f;
} activity;

int activityDuration(activity a) {
    return a.f - a.s;
}

void activityDisposition(int n, activity *v); //wrapper
int LISfind(int *predecessor, activity *v, int n, int *last);

void LISprint(activity *val, int predecessor[], int i, int printingQueque);

/*definizione funzioni più semplici*/
void swap(activity *e1, activity *e2) {
    activity swap;

    swap.s = (*e1).s;
    (*e1).s = (*e2).s;
    (*e2).s = swap.s;
    swap.f = (*e1).f;
    (*e1).f = (*e2).f;
    (*e2).f = swap.f;
}

void sorting(activity *v, int n) {
    int min;
    /*usando un selection sort se i dati sono già ordinati l'operazione è O(1)
     * non è necessario un controllo*/
    for (int i = 0; i < n; i++) {
        min = i;
        for (int j = i + 1; j <= n; j++) {
            if (v[j].s <= v[min].s)
                min = j;
        }
        swap(&v[i], &v[min]);
    }
}

activity *acquisition(int *n) {
    int i;
    FILE *fPtr;
    activity *v;

    if ((fPtr = fopen("att1.txt", "r")) == NULL) {
        printf("errore, file non trovato\n");
        exit(1);
    }
    fscanf(fPtr, "%d\n", n);
    v = malloc((*n) * sizeof(*v));
    for (i = 0; i < *n; i++)
        fscanf(fPtr, "%d %d\n", &v[i].s, &v[i].f);

    /*ordinamento secondo tempo di inizio*/
    sorting(v, *n);
    fclose(fPtr);
    return v;
}

int main() {
    int n;
    activity *v;

    v = acquisition(&n);
    activityDisposition(n, v);

    return 0;
}

void activityDisposition(int n, activity *v) {
    int *predecessor, maxDuration, last = 1, printingQueque = 0;

    predecessor = malloc(n * sizeof(int));
    maxDuration = LISfind(predecessor, v, n, &last);
    printf("la durata complessiva delle operazioni e' %d\n", maxDuration);
    printf("una sequenza che massimizza tale durata e'\n{");
    LISprint(v, predecessor, last, printingQueque); //poteva anche essere scritta iterativa e non ricorsiva
    printf("}\n");

    free(predecessor);
}

int LISfind(int *predecessor, activity *v, int n, int *last) {
    int maxDuration = 1, *L;

    /*L vettore della durata locale*/
    L = malloc(n * sizeof(int));
    /*prima soluzione fittizia*/
    L[0] = v[0].f - v[0].s;
    predecessor[0] = -1;

    for (int i = 1; i < n; i++) {
        L[i] = v[i].f - v[i].s;
        /*non è detto che la LIS esista quindi predecessor viene settato a -1, se non viene modificato la lis ha lunghezza 1*/
        predecessor[i] = -1;
        for (int j = 0; j < i; j++) {
            //controllo di sovrapposizione e di incremento della durata massima
            if ((v[j].f <= v[i].s) && (v[i].f - v[i].s + L[j] >
                                       L[i])) { //se la seconda inizia <= fine della prima e se il loro tempo di esecuzione migliora il tempo con L[i]
                /*effettivo incremento della durata mac*/
                L[i] = L[j] + v[i].f - v[i].s;
                /*assegnazione dell'indice j al vettore contanente l'indice dell'elemento precedente*/
                predecessor[i] = j;
            }
            if (maxDuration < L[i]) {
                maxDuration = L[i];
                *last = i; //TODO l'ultimo elemento i (da cui partirà la stampa)
            }
        }
    }
    free(L);

    return maxDuration;
}

void LISprint(activity *val, int *predecessor, int i, int printingQueque) {
    if (predecessor[i] == -1) {
        printf("%d %d, ", val[i].s, val[i].f);
        return;
    }
    LISprint(val, predecessor, predecessor[i], printingQueque + 1);
    printf("%d %d", val[i].s, val[i].f);
    if (printingQueque) //finezza per stampare la virgola solo se serve
        printf(", ");
    /*partendo dall'ultimo elemento della LIS Maggioritaria la ripercorre al contrario
     * (grazie al vettore predecessor finchè non arriva al primo elemento avente predecessore -1)
     * giunta a tal punto li stampa*/
}