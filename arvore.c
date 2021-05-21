#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "arvore_privada.h"

#define TRUE 1
#define FALSE 0

pABB criaABB(int tamInfo)
{
    pABB pp = malloc(sizeof(struct Arvore));
    pp->tamInfo = tamInfo;
    pp->raiz = NULL;
    // A raiz esta vazia.
    return pp;
}

No *criarNo(int tamInfo)
{
    No *n = malloc(sizeof(No));
    n->dado = malloc(tamInfo);
    n->direito = n->esquerdo = NULL;
    return n;
}

int insereABB(pABB pp, void *novo, int (*cmp)(void *p1, void *p2))
{
    if (pp == FALSE)
    {
        return FALSE;
    }

    if (pp->raiz == FALSE)
    {
        pp->raiz = criarNo(pp->tamInfo);
        pp->raiz->pai = NULL;
        memcpy(pp->raiz->dado, novo, pp->tamInfo);
        return TRUE;
    }

    int filho_vai_esquerda = -1;
    No *pai = 0;
    No *atual = pp->raiz;
    do
    {
        if (atual == FALSE)
        {
            atual = criarNo(pp->tamInfo);
            memcpy(atual->dado, novo, pp->tamInfo);
            if (filho_vai_esquerda == TRUE)
            {
                pai->esquerdo = atual;
            }
            else if (filho_vai_esquerda == FALSE)
            {
                pai->direito = atual;
            }
            atual->pai = pai;
            return TRUE;
        }
        pai = atual;
        if ((*cmp)(novo, atual->dado) >= 0)
        {
            atual = atual->direito;
            filho_vai_esquerda = FALSE;
        }
        else
        {
            atual = atual->esquerdo;
            filho_vai_esquerda = TRUE;
        }
    } while (1);
}

void freeNo(No* noRemover) {
  free(noRemover->dado);
  free(noRemover);
  noRemover = NULL;
}

int removeABB(pABB p, void *item, int (* cmp)(void *p1, void *p2), int (* cmpI)(void *p1, void *p2)) {
  No* noRemover = buscaNo(p->raiz, item, cmp, cmpI);
  if (noRemover == NULL) { // não encontra item
    return FALSE;
  }

  No* paiRemover = noRemover->pai;
  if (paiRemover == NULL) {
    // removendo raiz

    if (noRemover->esquerdo == NULL && noRemover->direito == NULL) {
      freeNo(noRemover);
      p->raiz = NULL;
      return TRUE;
    }

    if (noRemover->esquerdo == NULL) {
      // TEM SOMENTE NO A DIREITA
      noRemover->direito->pai = NULL;
      p->raiz = noRemover->direito;
      freeNo(noRemover);
      return TRUE;
    }

    No* esquerdaMaisAdireita = noRemover->esquerdo;
    while (esquerdaMaisAdireita->direito != NULL) {
      esquerdaMaisAdireita = esquerdaMaisAdireita->direito;
    }

    if (esquerdaMaisAdireita->pai != noRemover) {
      if (esquerdaMaisAdireita->esquerdo == NULL) {
        esquerdaMaisAdireita->pai->direito = NULL;
      } else {
        esquerdaMaisAdireita->pai->direito = esquerdaMaisAdireita->esquerdo;
        esquerdaMaisAdireita->esquerdo->pai = esquerdaMaisAdireita->pai;
      }
    }

    if (noRemover->esquerdo != esquerdaMaisAdireita) {
      // quando o no esquerdaMaisAdireita é filho do noRemover
      esquerdaMaisAdireita->esquerdo = noRemover->esquerdo;
      if (esquerdaMaisAdireita->esquerdo != NULL) {
        esquerdaMaisAdireita->esquerdo->pai = esquerdaMaisAdireita;
      }
    }

    if (noRemover->direito != esquerdaMaisAdireita) {
      // quando o no esquerdaMaisAdireita é filho do noRemover
      esquerdaMaisAdireita->direito = noRemover->direito;
      if (esquerdaMaisAdireita->direito != NULL) {
        esquerdaMaisAdireita->direito->pai = esquerdaMaisAdireita;
      }
    }

    esquerdaMaisAdireita->pai = NULL;
    p->raiz = esquerdaMaisAdireita;
    freeNo(noRemover);

    return TRUE;
  }

  if (noRemover->direito == NULL && noRemover->esquerdo == NULL) {
    // nenhum filho
    if (paiRemover->direito != NULL && cmpI(paiRemover->direito->dado, noRemover->dado) == TRUE) {
      paiRemover->direito = NULL;
    } else {
      paiRemover->esquerdo = NULL;
    }
    freeNo(noRemover);
    return TRUE;
  }

  if (noRemover->direito != NULL && noRemover->esquerdo != NULL) {
    // dois filhos
    No* esquerdaMaisAdireita = noRemover->esquerdo;
    while (esquerdaMaisAdireita->direito != NULL) {
      esquerdaMaisAdireita = esquerdaMaisAdireita->direito;
    }

    if (noRemover->esquerdo != esquerdaMaisAdireita) {
      // quando o no esquerdaMaisAdireita é filho do noRemover
      esquerdaMaisAdireita->esquerdo = noRemover->esquerdo;
      esquerdaMaisAdireita->esquerdo->pai = esquerdaMaisAdireita;
    }

    if (noRemover->direito != esquerdaMaisAdireita) {
      // quando o no esquerdaMaisAdireita é filho do noRemover
      esquerdaMaisAdireita->direito = noRemover->direito;
      esquerdaMaisAdireita->direito->pai = esquerdaMaisAdireita;
    }

    // limpa o pai do no a esquerda mais a direita
    // esquerdaMaisAdireita é o nó que vais substituir o noRemover
    esquerdaMaisAdireita->pai->direito = NULL;

    esquerdaMaisAdireita->pai = paiRemover;

    if (paiRemover->direito != NULL && cmpI(paiRemover->direito->dado, noRemover->dado) == TRUE) {
      // noRemover veio da direita
      paiRemover->direito = esquerdaMaisAdireita;
    } else {
      // noRemover veio da esquerda
      paiRemover->esquerdo = esquerdaMaisAdireita;
    }

    freeNo(noRemover);
    return TRUE;
  }

  // SOMENTE UM FILHO
  if (noRemover->esquerdo == NULL) {
    // tem o no da direita
    // não tem o noRemover->esquerda
    if (paiRemover->direito != NULL && cmpI(paiRemover->direito->dado, noRemover->dado) == TRUE) {
      paiRemover->direito = noRemover->direito;
    } else {
      paiRemover->esquerdo = noRemover->direito;
    }
    noRemover->direito->pai = paiRemover;
    freeNo(noRemover);
    return TRUE;
  }

  // tem o no da esquerda
  // não tem o noRemover->direita
  if (paiRemover->direito != NULL && cmpI(paiRemover->direito->dado, noRemover->dado) == TRUE) {
    paiRemover->direito = noRemover->esquerdo;
  } else {
    paiRemover->esquerdo = noRemover->esquerdo;
  }
  noRemover->esquerdo->pai = paiRemover;
  freeNo(noRemover);

  return TRUE;
}

void erd(No *n, void (*processa)(void *p))
{
    if (n != FALSE)
    {
        erd(n->esquerdo, processa);
        (*processa)(n->dado);
        if (n->pai != NULL) {
          printf(" = pai: ");
          (*processa)(n->pai->dado);
          printf("\n--\n");
        } else if (n->pai == NULL) {
          printf(" é raiz\n");
        }

        erd(n->direito, processa);
    }
}

void red(No *n, void (*processa)(void *p))
{
    if (n != FALSE)
    {
        (*processa)(n->dado);
        if (n->pai != NULL) {
          printf("\nprocessa pai ");
          (*processa)(n->pai->dado);
          printf("--\n");
        }
        red(n->esquerdo, processa);
        red(n->direito, processa);
    }
}

void dre(No *n, void (*processa)(void *p))
{
    if (n != FALSE)
    {
        dre(n->esquerdo, processa);
        dre(n->direito, processa);
        (*processa)(n->dado);
    }
}

int percursoEmOrdem(pABB pp, void (*processa)(void *p))
{
    if (pp == FALSE)
    {
        return FALSE;
    }
    if (pp->raiz == FALSE)
    {
        return FALSE;
    }

    erd(pp->raiz, processa);
    return TRUE;
}

int percursoPreOrdem(pABB pp, void (*processa)(void *p))
{
    if (pp == FALSE)
    {
        return FALSE;
    }
    if (pp->raiz == FALSE)
    {
        return FALSE;
    }

    red(pp->raiz, processa);
    return TRUE;
}

int percursoPosOrdem(pABB pp, void (*processa)(void *p))
{
    if (pp == FALSE)
    {
        return FALSE;
    }
    if (pp->raiz == FALSE)
    {
        return FALSE;
    }

    dre(pp->raiz, processa);
    return TRUE;
}

int testaVaziaABB(pABB p)
{
    if (p == NULL || !p) {
        return TRUE;
    } else {
        return FALSE;
    }
}

No* buscaNo(No *raiz, void *item, int (*cmp)(void *p1, void *p2), int (* cmpI)(void *p1, void *p2)) {
  No *atual = raiz;
  while (atual != NULL)
  {
      if ((*cmpI)(item, atual->dado)) // elemento encontrado
          return atual;
      else if ((*cmp)(item, atual->dado) > 0)
      {
          atual = atual->direito;
      }
      else
      {
          atual = atual->esquerdo;
      }
  }
  return NULL;
}

int buscaABB(pABB p, void *item, int (*cmp)(void *p1, void *p2), int (*cmpI)(void *p1, void *p2))
{
    if (testaVaziaABB(p))
        return FALSE;
    else
    {
      if (buscaNo(p->raiz, item, cmp, cmpI) != NULL)
      {
        return TRUE;
      }

    }
    return FALSE;
}

int destroiNos(No *noRemover)
{
    if (noRemover == NULL || !noRemover) {
      return TRUE;
    }

    if (noRemover->esquerdo != NULL && noRemover->esquerdo)
        destroiNos(noRemover->esquerdo);
    if (noRemover->direito != NULL && noRemover->direito)
        destroiNos(noRemover->direito);

    if (noRemover->dado != NULL) {
      free(noRemover->dado);
      noRemover->dado = NULL;
    }

    if (noRemover != NULL) {
      free(noRemover);
      noRemover = NULL;
    }

    return TRUE;
}

int reiniciaABB(pABB p) {
  if (!testaVaziaABB(p)) {
    destroiNos(p->raiz);
    p->raiz = NULL;
  }
  return TRUE;
}

int destroiABB(pABB pp)
{

    if (testaVaziaABB(pp)) {
      return TRUE;
    }

    if (pp->raiz != NULL) {
      destroiNos(pp->raiz);
    }
    free(pp);
    pp = NULL;

    return TRUE;
}
