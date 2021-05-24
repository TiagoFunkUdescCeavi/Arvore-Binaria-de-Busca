#ifndef ARVORE_PRIVADA_H
#define ARVORE_PRIVADA_H

#include "arvore_publica.h"

/**
 * Fiz com as duas structs para evitar que o aplicativo opere os nós.
 * Ele opera apenas a árvore.
 **/
typedef struct No{
    void * dado;
    struct No * pai;
    struct No * esquerdo;
    struct No * direito;
} No;

typedef struct Arvore{
    No * raiz;
    int tamInfo;
} Arvore;

// testaVaziaABB verifica se a arvore esta vazia
int testaVaziaABB(pABB p);

// destroiNos destroi os dados e nos das arvores
int destroiNos(No *noRemover);

// freeNo libera o no e dados da memoria
void freeNo(No* noRemover);

// buscaNo retorna o no buscado da arvore
// cmp é a função de comparar >= 0 vai para direita, < 0 vai para esquerda
// cmpI retorna 1 se é igual e retorna 0 se é diferente
No* buscaNo(No *raiz, void *item, int (*cmp)(void *p1, void *p2), int (* cmpI)(void *p1, void *p2));


void erd(No *n, void (*processa)(void *p));

void red(No *n, void (*processa)(void *p));

void dre(No *n, void (*processa)(void *p));



#endif