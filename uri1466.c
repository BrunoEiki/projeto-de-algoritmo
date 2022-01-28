#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX_FILA 500

struct nodo {
    int chave;
    struct nodo *esq;
    struct nodo *dir;
};

/* Evitar que a maquina defina implicitamente o tipo do retorno */
struct nodo** criaFila(int*, int*);
void enfileirar(struct nodo**, int*, struct nodo*);
struct nodo* desfileirar(struct nodo**, int*);

/* reserva espaco no heap para 1 struct nodo. O resto sera referenciado
a partir dos ponteiros esq e dir */
struct nodo *criaNodo(int valor) {
    struct nodo *raiz = (struct nodo*)malloc(sizeof(struct nodo));
    raiz->chave = valor;
    return raiz;
}

/* insere nodos na arvore de busca binaria de acordo com
as regras: menor para a esquerda, maior para a direita.*/
void inserir(struct nodo *nodo, int valor) {
    /* como o input vem em 1 unica linha foi preciso criar
    o nodo antes com um valor arbitrario. Depois que o valor real
    for colocado, ele substitui o -1 */
    if (nodo->chave == -1) {
        nodo->chave = valor;
    }
    if (valor < nodo->chave){
        if (nodo->esq == NULL) {
            nodo->esq = criaNodo(valor);
        }
        else {
            /* recursividade. Quando precisa-se inserir um nodo num nivel baixo,
            o programa chama a si mesmo ate encontrar um nodo que nao possui filhos*/
            inserir(nodo->esq, valor);
        }
    }
    if (valor > nodo->chave){
        if (nodo->dir == NULL) {
            nodo->dir = criaNodo(valor);
        } else {
            inserir(nodo->dir, valor);
        }
    }
}

/* Faz a varredura da arvore (BFS: breadht-first search) */
void levelOrderTransversal(struct nodo *raiz, int c) {
    int fundo, frente = 0;
    struct nodo **fila = criaFila(&frente, &fundo);
    struct nodo *nodo_temp = raiz;
    
    while (nodo_temp) {
        /* guarda os nodos do nivel a+1 na fila, onde "a" eh o nivel do nodo_temp 
        sempre comecando pelo mais a esquerda*/
        if (nodo_temp->esq){
            enfileirar(fila, &fundo, nodo_temp->esq);
        }
        if (nodo_temp->dir) {
            enfileirar(fila, &fundo, nodo_temp->dir);
        }
        if (c == 1) {    /* no penultimo loop, printar o ultimo nodo com newline e sair */
            printf("%d\n", nodo_temp->chave);
            break;
        }
        printf("%d ", nodo_temp->chave);
        nodo_temp = desfileirar(fila, &frente); /* seleciona os nodos da fila em direcao top-bottom */
        c--;
    }
}

    /* A **fila é uma lista composta de ponteiros, que apontam para outros ponteiros, 
    os quais apontam para structs nodo localizados no heap. Seu tamanho é igual a 
    quantidade de elementos da fila vezes o tamanho de um nodo */
struct nodo **criaFila(int *frente, int *fundo) {
    struct nodo **fila = (struct nodo**)malloc(sizeof(struct nodo*) * TAM_MAX_FILA);
    *frente = *fundo = 0;
    return fila;
}

void enfileirar(struct nodo **fila, int *fundo, struct nodo *novo_nodo) {
    fila[*fundo] = novo_nodo;
    (*fundo)++;
}

struct nodo *desfileirar(struct nodo **fila, int *frente) {
    (*frente)++;
    return (fila[*frente - 1]);
}

int main() {
    /* n: num de testes
       c: tamanho da arvore
       k: valores a serem inseridos 
       i e j: contar os loops*/
    int n, c, k;
    int i = 1;
    int j = 1;
    scanf("%d", &n);
    while (i <= n) {
        scanf("%d", &c);
        struct nodo *raiz = criaNodo(-1);
      /* insere os c valores nos nodos */
        while (j <= c) {
            scanf("%d", &k);
            inserir(raiz, k);
            j++;
        }
        printf("Case %d:\n", i);
        levelOrderTransversal(raiz, c);
        printf("\n");
        i++;
        j = 1;
    }
    return 0;
}
  