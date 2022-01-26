#include <stdio.h>
#include <stdlib.h>

/*Pilha e algumas Operações Básicas*/
struct pilha {
        int tamanhomaximo;
        int top;        
        int *lista;
    };
struct pilha *criarPilha(int tamanho){
     /* reserva um espaço no heap para guardar a stack e retorna o endereço */
    struct pilha *pont = (struct pilha*)malloc(sizeof(struct pilha));

    pont->tamanhomaximo = tamanho;
    pont->top = -1;
    pont->lista = (int*)malloc(sizeof(int) * tamanho);
    return pont;
};
  
int checarVazia(struct pilha *pont) {
    return pont->top == -1;
}

int checarCheia(struct pilha *pont) {
    return pont->top == pont->tamanhomaximo-1;
}

void push(struct pilha *pont, int valor) {
    if (checarCheia(pont)) {
        printf("overflow");
        exit(EXIT_FAILURE);
    }
  /* valor é atribuido a posição atual do top e top aumenta em 1 */
    pont->top++;
    pont->lista[pont->top] = valor;
}

int acessarTopo(struct pilha *pont) {
    if (!checarVazia(pont)) {
        return pont->lista[pont->top];
    }
    else {
        exit(EXIT_FAILURE);
    }
}

int pop(struct pilha *pont) {
    if(checarVazia(pont)) {
        exit(EXIT_FAILURE);
    }
    return pont->lista[pont->top--];
}



int main() {
  /* flag0 indica quando o usuário insere 0 como input. flag1 indica quando há apenas 1 único vagão em A. Em ambos os casos, isso sinaliza o término da sequência atual */
    int n, i, j, flag0, flag1;
    int A[1000];
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        while (1) {
            j = 1;
            flag = 0;
            flag1 = 0;
            struct pilha *pont = criarPilha(1000);
          /* armazena os vagões que vem de A na ordem forncecida pelo usuário */
            i = 1;
            while (i <= n) {
                scanf("%d", &A[i]);
              /* caso o usuário digite 0, terminar sequência atual */
                if (A[i] == 0) {
                  /* linha vazia que separa um bloco de vagões do outro*/
                    printf("\n");
                    flag = 1;
                    break;
                }
                i++;
            }
          /* j serve para adicionar elementos de 1 a n para pilha, enquanto i acompanha quantos vagões de A já "passaram" para B */
            i = 1;
            while (1) {
                if (i > n) break;
                if (flag1 == 1) break;
                if (flag == 1) break;
                while(1) {
                  /* topo igual ao vagão de A, retirar o topo */
                    if (!checarVazia(pont) && acessarTopo(pont) == A[i]) {
                        pop(pont);
                        break;
                      /* quando não houver correspondência, adicionar o próximo vagão na pilha à cada loop em ordem crescente (1, 2, ..., n) */
                    } else if (j <= n) {
                        push(pont, j);
                        j++;
                      /* se o novo topo for igual ao vagão de A, retirar topo */
                        if (acessarTopo(pont) == A[i]) {
                            pop(pont);
                            break;
                        } 
                      /* se houver 1 único vagão vindo de A, flag1 = 1*/
                    } else {
                        flag1 = 1;
                        break;
                    }
                }
                i++;
            }
            if (flag == 1) break;
          /* Pilha vazia indica que todos os vagões de A passaram para B*/
            if (checarVazia(pont)) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
