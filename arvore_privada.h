#ifndef ARVORE_PRIVADA_H
#define ARVORE_PRIVADA_H

#include "arvore_publica.h"

/**
 * Fiz com as duas structs para evitar que o aplicativo opere os nós.
 * Ele opera apenas a árvore.
 **/

typedef struct No{
    void * dado;
    struct No * esquerdo;
    struct No * direito;
} No;

typedef struct Arvore{
    No * raiz;
    int tamInfo;
} Arvore;


#endif