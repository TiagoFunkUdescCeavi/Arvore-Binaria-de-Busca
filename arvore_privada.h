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

int testaVaziaABB(pABB p);
int destroiNos(No *noRemover);
No* buscaNo(No *raiz, void *item, int (*cmp)(void *p1, void *p2), int (* cmpI)(void *p1, void *p2));


#endif