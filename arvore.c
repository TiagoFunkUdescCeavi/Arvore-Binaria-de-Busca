#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "arvore_privada.h"

#define TRUE 1
#define FALSE 0

pABB criaABB(int tamInfo){
    pABB pp = malloc( sizeof( struct Arvore ) );
    pp->tamInfo = tamInfo;
    // A raiz esta vazia.
    return pp; 
}

No * criarNo( int tamInfo ){
    No * n = malloc( sizeof( No ) );
    n->dado = malloc( tamInfo );
    return n;
}

int insereABB(pABB pp, void *novo, int (* cmp)(void *p1, void *p2)){
    if( pp == FALSE ){
        return FALSE;
    }

    if( pp->raiz == FALSE ){
        pp->raiz = criarNo( pp->tamInfo );
        memcpy( pp->raiz->dado, novo, pp->tamInfo );
        return TRUE;
    }

    int filho_vai_esquerda = -1;
    No * pai = 0;
    No * atual = pp->raiz;
    do{
        if( atual == FALSE ){
            atual = criarNo( pp->tamInfo );
            memcpy( atual->dado, novo, pp->tamInfo );
            if( filho_vai_esquerda == TRUE ){
                pai->esquerdo = atual;
            }else if( filho_vai_esquerda == FALSE ){
                pai->direito = atual;
            }
            return TRUE;
        }
        pai = atual;
        if( (*cmp)( novo, atual->dado ) > 0 ){
            atual = atual->direito;
            filho_vai_esquerda = FALSE;
        }else{
            atual = atual->esquerdo;
            filho_vai_esquerda = TRUE;
        }
    }while( 1 );
}

void erd( No * n, void (* processa)(void *p) ){
    if (n != FALSE) {
      erd(n->esquerdo, processa);
      (*processa) (n->dado);
      erd(n->direito, processa); 
   }
}

void red( No * n, void (* processa)(void *p) ){
    if (n != FALSE) {
        (*processa) (n->dado);
        red(n->esquerdo, processa);
        red(n->direito, processa); 
   }
}

void dre( No * n, void (* processa)(void *p) ){
    if (n != FALSE) {
        dre(n->esquerdo, processa);
        dre(n->direito, processa);
        (*processa) (n->dado);
   }
}

int percursoEmOrdem(pABB pp, void (* processa)(void *p) ){
    if( pp == FALSE ){
        return FALSE;
    }
    if( pp->raiz == FALSE ){
        return FALSE;
    }

    erd( pp->raiz, processa );
    return TRUE;
}

int percursoPreOrdem(pABB pp, void (* processa)(void *p)){
    if( pp == FALSE ){
        return FALSE;
    }
    if( pp->raiz == FALSE ){
        return FALSE;
    }

    red( pp->raiz, processa );
    return TRUE;
}

int percursoPosOrdem(pABB pp, void (* processa)(void *p)){
    if( pp == FALSE ){
        return FALSE;
    }
    if( pp->raiz == FALSE ){
        return FALSE;
    }

    dre( pp->raiz, processa );
    return TRUE;
}