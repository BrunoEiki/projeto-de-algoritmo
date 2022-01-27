#include <stdio.h>

#define tamanho 100

/* prototipo de fila (FIFO) */
int lista[tamanho];

static int fronte = 0;
static int tras = 0;

/* se fronte ou tras for maior que o tamanho da fila, resetar */
void remover() {
    if (fronte < sizeof(lista)/sizeof(lista[0]) - 1) {
        fronte++;
    } else {
        fronte = 0;
    }
}

void inserir(int val) {
    lista[tras] = val;
    if (tras < sizeof(lista)/sizeof(lista[0]) - 1) {
        tras++;
    }
    else {
         tras = 0;
    }
}
  
int main() {
    int cartas;
    int carta;

    while(1) {
        scanf("%d", &cartas);
        carta = 1;
        if (cartas == 0) break;
        /* insere as n cartas */
        while (carta <= cartas) {
            inserir(carta);
            carta++;
        }
        printf("Discarded cards: ");
        /* (tras - fonte) = ao tamanho da lista. Mais eficiente que dividir os sizeof, 
        pois usa apenas subtracao*/
        while ((tras - fronte) > 1) {
            /* tamanho igual a 2 sinaliza que a fila esta no ultimo loop, e por isso
            printa o valor da carta com linebreak*/
            if ((tras - fronte) != 2) {
                printf("%d, ", lista[fronte]);
            } else {
                printf("%d\n", lista[fronte]);
            }
            /* retira o topo e coloca o novo topo no fundo da fila*/
            remover();
            inserir(lista[fronte]);
            remover();
        }
        printf("Remaining card: %d\n", lista[fronte]);
        /* reseta para começar do inicio da fila. Os valores do loop x continuam na
        fila, mas isso eh irrelevante, pois no loop x+1 os valores vao ser substituidos*/
        tras = 0;
        fronte = 0;
    }
    return 0;
}