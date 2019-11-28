#include <stdio.h>

#include <stdlib.h>

#define N 8
#define FLOAT 8
#define DOUBLE 11
#define LONGDOUBLE 15

int findEndian();// ritorna 1(true) se si utilizza il metodo big edian
void format(int n, int dim); //funzione per la formattazione dell'output
void stampaCodifica(void *p, int size, int bigEndian);

int main() {
    float af;
    double ad;
    long double ald;

    int bigEndian= findEndian();

    printf("Dimensione dato di tipo float: %d\n", sizeof(af));
    printf("Dimensione dato di tipo double: %d\n", sizeof(ad));
    printf("Dimensione dato di tipo long double: %d\n", sizeof(ald));

    printf("Inserisci un numero, per la notazione esponenziale usare \"parte intera\".\"mantissa\"E\"esponente\" : ");
    scanf("%f", &af);
    ad = (double)af;
    ald = (long double)af;

    printf("\n tipo di dato float: \n");
    stampaCodifica((void *)&af, sizeof(af), bigEndian);
    printf("\n tipo di dato double:\n");
    stampaCodifica((void *)&ad,sizeof(ad),bigEndian);
    printf("\n tipo di dato long double:\n");
    stampaCodifica((void *)&ald,sizeof(ald),bigEndian);

    return 0;
}

int findEndian(){
    int i=0x1234; //perchè 0x1234? perchè è l'unico modo in cui il mi pc riconosce il fatto di essere little endian
    void *pn = &i;
    char *p =(char *) pn;

    return !(*p == '4');
}

void stampaCodifica(void *p, int size, int bigEndian) {
    unsigned char *k;
    int increase;
    int i = 0;
    int power, j;

    if (bigEndian == 1) { //il puntatore viene settato alla cella di memoria con valore minore
        k = p;
        increase = 1;
    } else { //il puntatore viene settato alla cella di memoria con valore maggiore
        k = p+(size-1);
        increase = -1;
    }

    while (i < size*N) {  //size*N in modo da scorrere tutte le locazioni di memoria occupate dal mio dato
        // trova la potenza di 2 massima
        for (power=1, j= 0; 2*power<=*k; power=power*2, j++);    //trasformazione in binario tramite il metodo delle potenze decrescenti di 2
        /*avrei preferito usare il metodo delle divisioni con resto ma ho avuto qualche serio problema con il pc */

        while (power>0) {
            format(i, size); //funzione che si occupa di formattare in maniera ottimale l'output in modo da distinguere i vari bit

            if (N - j -1 != 0) {
                /*controllo quanti 0 precedono il primo 1 e li stampo*/
                printf("0");
                j++;
            } else {

                if (power <= *k) {  //se il valore nel byte preso in analisi è maggiore della potenza di due (power) il programma scrive 1 e "riporta"
                    printf("1");
                    k = k - power;
                } else
                    printf("0");
                power = power/2;
            }

            (i)++;
        }
        k += increase; //incremento o decremento del puntatore (a seconda della codifica Endian del calcolatore)
    }

    printf("\n");
}

void format(int n, int dim){

        if (n == 0) {
            printf("bit di segno:\n");
        }else if (n==1){
            printf("\n bit dell'esponente:\n");
        }else{
            switch (dim) {
                case 4:
                    if (n == FLOAT+1)
                        printf("\n bit della mantissa:\n");
                    break;
                case 8:
                    if (n == DOUBLE+1)
                        printf("\n bit della mantissa:\n");
                    break;
                case 16:
                    if (n == LONGDOUBLE+1)
                        printf("\n bit della mantissa:\n");
                    break;
            }
        }
    }
/*LONG DOUBLE viene gestito in maniera errata dal mio processore, ho deciso che nonostante l'impegno e la voglia fosse controproducente
 * cercare di risolvere anche questo problema (oltre al problema del char non castato in maniera corretta)*/