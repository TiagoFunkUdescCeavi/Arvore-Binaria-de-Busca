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
          int* dado = novo;
          printf("insereABB ATUAL == FALSE %d\n", *dado);
            atual = criarNo(pp->tamInfo);
            memcpy(atual->dado, novo, pp->tamInfo);
            if (filho_vai_esquerda == TRUE)
            {
                printf("filho_vai_esquerda == TRUE %d\n", *dado);
                pai->esquerdo = atual;
            }
            else if (filho_vai_esquerda == FALSE)
            {
                printf("filho_vai_esquerda == FALSE %d\n", *dado);
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

int removeABB(pABB p, void *item, int (* cmp)(void *p1, void *p2), int (* cmpI)(void *p1, void *p2)) {

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
        } else if (n->pai == NULL)
        {
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

    free(noRemover->dado);
    noRemover->dado = NULL;
    free(noRemover);
    noRemover = NULL;

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
